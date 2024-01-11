#include <am.h>
#include <amdev.h>
#include <klib.h>
#include <klib-macros.h>

#include <string.h>
#include "my_bmp.c"

#define SIDE 16

static int w, h;  // Screen size

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
static const char *key_names[] = { AM_KEYS(KEYNAME) };

static inline void puts(const char *s) {
  for (; *s; s++) putch(*s);
}

void print_key() {
  AM_INPUT_KEYBRD_T event = { .keycode = AM_KEY_NONE };
  ioe_read(AM_INPUT_KEYBRD, &event);
  if (event.keycode != AM_KEY_NONE && event.keydown) {
    puts("Key pressed: ");
    puts(key_names[event.keycode]);
    puts("\n");
    if (strncmp(key_names[event.keycode], "ESCAPE", 6) == 0)
    {
      // printf("keycode = %d, ESC\n", event.keycode);
      halt(0);
    }
  }
}

static void draw_tile(int x, int y, int w, int h, uint32_t color) {
  uint32_t pixels[w * h]; // WARNING: large stack-allocated memory
  AM_GPU_FBDRAW_T event = {
    .x = x, .y = y, .w = w, .h = h, .sync = 1,
    .pixels = pixels,
  };
  for (int i = 0; i < w * h; i++) {
    pixels[i] = color;
  }
  ioe_write(AM_GPU_FBDRAW, &event);
}

void splash() {
  AM_GPU_CONFIG_T info = {0};
  ioe_read(AM_GPU_CONFIG, &info);
  w = info.width;
  h = info.height;

  for (int x = 0; x * SIDE <= w; x ++) {
    for (int y = 0; y * SIDE <= h; y++) {
      if ((x & 1) ^ (y & 1)) {
        draw_tile(x * SIDE, y * SIDE, SIDE, SIDE, 0xffffff); // white
      }
    }
  }
}

static void draw_part_bmp(int x, int y, int w, int h, const unsigned char *bmp_pixel)
{
  // uint32_t pixels[w * h]; // WARNING: large stack-allocated memory
  uint32_t pixel;
  AM_GPU_FBDRAW_T event = {
      .x = x,
      .y = y,
      .w = w,
      .h = h,
      .sync = 1,
      // .pixels = pixels,
      .pixels = &pixel,
  };
  // pixel = 0xffffff;
  pixel = (*bmp_pixel << 16) + (*(bmp_pixel + 1) << 8) + *(bmp_pixel + 2);
  // pixel = ((*(bmp_pixel + 2)) << 16) + ((*(bmp_pixel + 1)) << 8) + *(bmp_pixel);
  // printf("%X ", pixel);

  ioe_write(AM_GPU_FBDRAW, &event);
}

void draw_bmp()
{
  const int bmp_head_len = __Mascaloona_Bliss_4_3__640x480__bmp_len - bmp_h * bmp_w * bmp_bits / 8;
  AM_GPU_CONFIG_T info = {0};
  ioe_read(AM_GPU_CONFIG, &info);
  // w = 16;
  // h = 16;
  w = info.width;
  h = info.height;
  // printf("w = %d, h = %d, bmp_head_len = %d\n", w, h, bmp_head_len);
  const unsigned char *bmp_start_pixel = __Mascaloona_Bliss_4_3__640x480__bmp + bmp_head_len;
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      draw_part_bmp(x, h - y - 1, 1, 1, bmp_start_pixel + (y * w + x) * 3);
    }
  }
}

// Operating system is a C program!
int main(const char *args) {
  ioe_init();

  puts("mainargs = \"");
  puts(args);  // make run mainargs=xxx
  puts("\"\n");

  draw_bmp();
  // splash();

  puts("Press any key to see its key code...\n");
  while (1) {
    print_key();
  }
  return 0;
}
