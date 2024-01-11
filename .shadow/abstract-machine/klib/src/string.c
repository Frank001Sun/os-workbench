#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  assert(s != NULL);
  const char *s_tail = s;
  for (; *s_tail; s_tail++)
    ;
  return s_tail - s;
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  assert(dst != NULL);
  assert(src != NULL);
  for (; *src; src++, dst++)
    *dst = *src;
  return dst;
  panic("Not implemented");
}

char *strncpy(char *dst, const char *src, size_t n) {
  assert(dst != NULL);
  assert(src != NULL);
  for (; *src && n; src++, dst++, n--)
    *dst = *src;
  return dst;
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  assert(dst != NULL);
  assert(src != NULL);
  strcpy(dst + strlen(dst), src);
  panic("Not implemented");
}

int strcmp(const char *s1, const char *s2) {
  assert(s1 != NULL);
  assert(s2 != NULL);
  for (; *s1 == *s2 && *s1; s1++, s2++)
    ;
  return *(unsigned char *)s1 - *(unsigned char *)s2;
  panic("Not implemented");
}

int strncmp(const char *s1, const char *s2, size_t n) {
  assert(s1 != NULL);
  assert(s2 != NULL);
  if (!n--)
    return 0;
  for (; *s1 == *s2 && *s1 && n; s1++, s2++, n--)
    ;
  return *(unsigned char *)s1 - *(unsigned char *)s2;
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  assert(s != NULL);
  unsigned char *_s = s;
  for (; n; n--)
    *_s = c;
  return s;
  panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  assert(dst != NULL);
  assert(src != NULL);
  unsigned char *d = dst;
  const unsigned char *s = src;
  for (; n; n--)
    *(unsigned char *)d++ = *(unsigned char *)s++;
  return dst;
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  assert(out != NULL);
  assert(in != NULL);
  unsigned char *o = out;
  const unsigned char *i = in;
  for (; n; n--)
    *o++ = *i++;
  return out;
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  assert(s1 != NULL);
  assert(s2 != NULL);
  const unsigned char *l = s1;
  const unsigned char *r = s2;
  for (; *l == *r && n; n--, l++, r++)
    ;
  return n ? *l - *r : 0;
  panic("Not implemented");
}

#endif
