SET(_CPPUTEST_SOURCES
  $ENV{CPPUTEST_HOME}/src/CppUTest/CommandLineArguments.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/CommandLineTestRunner.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/JUnitTestOutput.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/MemoryLeakDetector.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/MemoryLeakWarningPlugin.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestTestingFixture.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/Utest.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/SimpleString.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestRegistry.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestOutput.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TeamCityTestOutput.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestFilter.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestHarness_c.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestMemoryAllocator.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestResult.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/SimpleMutex.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestPlugin.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTest/TestFailure.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/CodeMemoryReportFormatter.cpp
  # $ENV{CPPUTEST_HOME}/src/CppUTestExt/IEEE754ExceptionsPlugin.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MemoryReportAllocator.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MemoryReportFormatter.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MemoryReporterPlugin.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockNamedValue.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockSupport_c.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockExpectedCallsList.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/OrderedTest.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockExpectedCall.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockSupport.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockActualCall.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockFailure.cpp
  $ENV{CPPUTEST_HOME}/src/CppUTestExt/MockSupportPlugin.cpp
  )

SET(CPPUTEST_SOURCES
  ${_CPPUTEST_SOURCES}
  $ENV{CPPUTEST_HOME}/src/Platforms/Iar/UtestPlatform.cpp
  )

SET(INCLUDES_CPPUTEST
  $<BUILD_INTERFACE:$ENV{CPPUTEST_HOME}/include>
  )

set(TEST_SOURCES
  ${C_SOURCES_COMMON}
  ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f411xe.s
  ${CMAKE_CURRENT_SOURCE_DIR}/Src/app_test_c.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Src/main.cpp
  )

set(TEST_ASM_SOURCES
  ${CMAKE_SOURCE_DIR}/startup_stm32f411xe.s
  )

set_property(SOURCE
  ${CMAKE_SOURCE_DIR}/startup_stm32f411xe.s PROPERTY LANGUAGE C
  )

add_executable(${PROJ}-test
  ${TEST_ASM_SOURCES}
  ${TEST_SOURCES}
  ${CPPUTEST_SOURCES}
  )

target_include_directories(${PROJ}-test PRIVATE
  ${INCLUDES_COMMON}
  ${INCLUDES_CPPUTEST}
  ${CMAKE_CURRENT_LIST_DIR}/Inc/
  )

target_compile_definitions(${PROJ}-test PRIVATE
  ${DEFINITIONS_COMMON}
  )

target_link_libraries(${PROJ}-test
  -lm -lnosys
  )

target_link_options(${PROJ}-test
  PRIVATE "-T${CMAKE_SOURCE_DIR}/STM32F411RETx_FLASH.ld"
  PRIVATE "--specs=rdimon.specs"
  PRIVATE "-u _scan_float"
  PRIVATE "-u _printf_float"
  PRIVATE "-Wl,--gc-sections")

add_custom_target(${PROJ}-test.bin ALL
  COMMAND
  ${CMAKE_OBJCPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJ}-test ${CMAKE_CURRENT_BINARY_DIR}/${PROJ}-test.bin
  )

add_dependencies(${PROJ}-test.bin ${PROJ}-test)
