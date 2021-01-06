#include "CppUTest/TestHarness_c.h"

TEST_GROUP_C_WRAPPER(app_test)
{
  TEST_GROUP_C_SETUP_WRAPPER(app_test);
  TEST_GROUP_C_TEARDOWN_WRAPPER(app_test);
};

TEST_C_WRAPPER(app_test, test_application_flow);


