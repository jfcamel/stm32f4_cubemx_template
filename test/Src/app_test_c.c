#include "CppUTest/TestHarness_c.h"

#include "app.h"


TEST_GROUP_C_SETUP(app_test)
{
};

TEST_GROUP_C_TEARDOWN(app_test)
{
};

TEST_C(app_test, test_application_flow)
{
  CHECK_EQUAL_C_INT(0, app_init());
  CHECK_EQUAL_C_INT(0, app_process());
};

