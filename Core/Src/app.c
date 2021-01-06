#include "app.h"

#include <stdio.h>

int16_t app_init(void) {
  printf("app initialized\n");

  return 0;
}

int16_t app_process(void) {
  printf("Hello world\n");

  return 0;
}

