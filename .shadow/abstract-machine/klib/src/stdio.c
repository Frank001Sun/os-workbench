#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>


#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  char *s;
  char c;
  int i;
  int index;
  int char_transmitted = 0;
  char number_buffer[16];
  while (*fmt)
    switch (*fmt++)
    {
    case '%': /* formatted output */
      switch (*fmt++)
      {
      case 's': /* string */
        s = va_arg(ap, char *);
        putstr(s);
        char_transmitted += strlen(s);
        break;
      case 'd': /* int */
        i = va_arg(ap, int);
        index = sizeof(number_buffer) - 2;
        number_buffer[index + 1] = '\0';
        for (; i; i /= 10)
        {
          number_buffer[index] = i % 10 + '0';
          index--;
        }
        putstr(&number_buffer[index + 1]);
        char_transmitted += strlen(&number_buffer[index + 1]);
        break;
      case 'x': /* 16-bit */
        i = va_arg(ap, int);
        index = sizeof(number_buffer) - 2;
        number_buffer[index + 1] = '\0';
        for (; i; i /= 16)
        {
          int v = i % 16;
          if (v >= 10)
          {
            number_buffer[index] = v - 10 + 'a';
          }
          else
          {
            number_buffer[index] = v + '0';
          }
          index--;
        }
        putstr("0x");
        putstr(&number_buffer[index + 1]);
        char_transmitted += strlen(&number_buffer[index + 1]);
        break;
      case 'c': /* char */
        /* need a cast here since va_arg only
           takes fully promoted types */
        c = va_arg(ap, int);
        putch(c);
        char_transmitted += 1;
        break;
      default:
        putch('%');
        putch(*(fmt - 1));
        panic("Not implemented");
        break;
      }
      break;
    default:
      putch(*(fmt - 1));
      char_transmitted += 1;
      break;
    }
  va_end(ap);
  return char_transmitted;
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
