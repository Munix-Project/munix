
#ifndef KERNEL_INCLUDE_VA_LIST_H_
#define KERNEL_INCLUDE_VA_LIST_H_

typedef __builtin_va_list va_list;
#define va_start(ap,last) __builtin_va_start(ap, last)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap,type) __builtin_va_arg(ap,type)
#define va_copy(dest, src) __builtin_va_copy(dest,src)

#endif /* KERNEL_INCLUDE_VA_LIST_H_ */
