
#ifndef WRAPPER_HANDLER_H
#define WRAPPER_HANDLER_H

#define TYPE void*
#define DEFINE_CLS_TYPE(type) typedef void* type;

//#define CLS_TYPE

#define TYPE void*
#define CONSTRUCTOR_SIG_CLS(t, ...) ##t create##t(##t, ##__VA_ARGS__)


#define CONSTRUCTOR_IMP_CLS(...) \
     CONSTRUCTOR_IMP_CLS(TYPE, ##__VA_ARGS__) {\
          return new TYPE() \
     }\


#endif //WRAPPER_HANDLER_H
