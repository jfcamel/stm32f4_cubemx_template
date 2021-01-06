#include "CppUTest/CommandLineTestRunner.h"

#include <stdio.h>

#include "app_test_c.h"

extern "C" {
  extern void SystemInit(void);
  extern void initialise_monitor_handles(void);
}

int main()
{
  SystemInit();
  initialise_monitor_handles();

  int ac = 2;
  const char * av_override[] = { "exec", "-v" };
  return RUN_ALL_TESTS(ac, av_override);
}
