#define EXPAND(va_args) va_args

#define _NEXT_ARG_(NEXT, ...) NEXT
#define NEXT_ARG(...) EXPAND(_NEXT_ARG_(__VA_ARGS__))