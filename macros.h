#define SELECT_MACRO_NARGS(A1, A2, A3, A4, A5, A6, A7, A8, M, ...) M

#define APPLY_1(x, A1 ) x(A1)
#define APPLY_2(x, A1, ...) APPLY_1(x, A1) APPLY_1(x, __VA_ARGS__)
#define APPLY_3(x, A1, ...) APPLY_1(x, A1) APPLY_2(x, __VA_ARGS__)
#define APPLY_4(x, A1, ...) APPLY_1(x, A1) APPLY_3(x, __VA_ARGS__)
#define APPLY_5(x, A1, ...) APPLY_1(x, A1) APPLY_4(x, __VA_ARGS__)
#define APPLY_6(x, A1, ...) APPLY_1(x, A1) APPLY_5(x, __VA_ARGS__)
#define APPLY_7(x, A1, ...) APPLY_1(x, A1) APPLY_6(x, __VA_ARGS__)
#define APPLY_8(x, A1, ...) APPLY_1(x, A1) APPLY_7(x, __VA_ARGS__)
#define APPLY(x, ...) SELECT_MACRO_NARGS(__VA_ARGS__, \
    APPLY_8, APPLY_7, APPLY_6, APPLY_5, APPLY_4, APPLY_3, APPLY_2, APPLY_1) \
    (x, __VA_ARGS__)
