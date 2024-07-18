#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <string>
#include <exception>
#include <type_traits>
#include "macros.h"
#include "structs.h"

template <typename T_Sink, typename T, typename T_Context>
inline std::enable_if_t<std::is_scalar_v<T>>
    sink_to(T_Sink& sink, const T& value, const T_Context& context)
{
    sink(value, context);
}

template <typename T_Sink, typename T, typename T_Context>
inline std::enable_if_t<std::is_scalar_v<typename T::value_type>>
    sink_to(T_Sink& sink, const T& value, const T_Context& context)
{
    for (size_t i = 0; i < value.size(); i++)
    {
        sink(value[i], context.add(std::to_string(i)));
    }
}

#define SINK_MEM_TO(mem) sink_to(sink, s.mem, context.add(#mem));

#define DEFINE_SINKABLE_STRUCT(Type, ...) \
inline void sink_to(auto &sink, const Type &s, const auto &context) \
{ \
    APPLY(SINK_MEM_TO, __VA_ARGS__) \
}

#define STRUCT DEFINE_SINKABLE_STRUCT
#include "structs.def"
#undef STRUCT

struct PathContext
{
    std::string path_;
    PathContext(std::string path) : path_(path) {}
    std::string path() const { return path_; }
    PathContext add(std::string name) const { return PathContext(path() + "/" + name); }
};

struct StdoutSink
{
    template <typename T, typename T_Context>
    void operator() (const T& value, const T_Context& context)
    {
        std::cout << context.path() << ": " << value << std::endl;
    }
};

struct Serializer
{
    Serializer(std::vector<char> &buff) : buff_{buff}, bytes_{} {}

    template <typename T, typename T_Context>
    std::enable_if_t<std::is_scalar_v<T>>
        operator() (const T& value, const T_Context& context)
    {
        // TODO: Add byte swapping
        const size_t value_size = sizeof(value);
        if (bytes_ + value_size <= buff_.size())
        {
            char *p = reinterpret_cast<char*>(buff_.data()) + bytes_;
            memcpy(p, &value, value_size);
            bytes_ += value_size;
        }
        else
        {
            throw std::runtime_error("Buffer too small");
        }
    }

    std::vector<char> &buff_;
    std::size_t bytes_;
};

int main()
{
    ns_2::C c;
    StdoutSink out;
    sink_to(out, c, PathContext("main"));

    std::vector<char> buff(64);
    Serializer serializer_sink(buff);
    sink_to(serializer_sink, c, PathContext("main"));

    for (const int &val : buff)
    {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << val;
    }
    std::cout << std::endl;
}
