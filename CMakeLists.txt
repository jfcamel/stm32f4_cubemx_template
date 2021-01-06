cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJ ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJ})

SET(PREFIX arm-none-eabi)
SET(CMAKE_C_COMPILER ${PREFIX}-gcc)
SET(CMAKE_CXX_COMPILER ${PREFIX}-g++)
SET(CMAKE_ASM_COMPILER ${PREFIX}-as)
SET(CMAKE_OBJCPY ${PREFIX}-objcopy)

set(CPU "-mcpu=cortex-m4")
set(FPU "-mfpu=fpv4-sp-d16")
set(FLOAT-ABI "-mfloat-abi=hard")
set(MCU "${CPU} -mthumb ${FPU} ${FLOAT-ABI}")

set(DEBUG "-g1")
set(OPTIMIZE "-Os")

set(CMAKE_C_FLAGS "${MCU} ${OPTIMIZE} ${DEBUG} -ffunction-sections -fdata-sections -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -fpermissive -fexceptions -fnon-call-exceptions -fno-rtti -fno-use-cxa-atexit -fno-common")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_FLAGS} -T${CMAKE_CURRENT_LIST_DIR}/STM32F411RETx_FLASH.ld  --specs=nano.specs -Wl,--gc-sections")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_FLAGS} -T${CMAKE_CURRENT_LIST_DIR}/STM32F411RETx_FLASH.ld  --specs=rdimon.specs -u _scan_float -u _printf_float -Wl,--gc-sections")

set(C_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/stm32f4xx_it.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_exti.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/system_stm32f4xx.c
  )

set(ASM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f411xe.s
  )

set_property(SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f411xe.s PROPERTY LANGUAGE C)

add_executable(${PROJ}
  ${C_SOURCES}
  ${ASM_SOURCES}
  )

target_include_directories(${PROJ} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc/
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include/
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include/
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/
  )

target_compile_definitions(${PROJ} PRIVATE
  -DUSE_FULL_LL_DRIVER
  -DHSE_VALUE=25000000
  -DHSE_STARTUP_TIMEOUT=100
  -DLSE_STARTUP_TIMEOUT=5000
  -DLSE_VALUE=32768
  -DEXTERNAL_CLOCK_VALUE=12288000
  -DHSI_VALUE=16000000
  -DLSI_VALUE=32000
  -DVDD_VALUE=3300
  -DPREFETCH_ENABLE=1
  -DINSTRUCTION_CACHE_ENABLE=1
  -DDATA_CACHE_ENABLE=1
  -DSTM32F411xE
  )

target_link_libraries(${PROJ}
  -lm -lnosys
  )

add_custom_target(${PROJ}.bin ALL
  COMMAND
  ${CMAKE_OBJCPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJ} ${CMAKE_CURRENT_BINARY_DIR}/${PROJ}.bin
  )

add_dependencies(${PROJ}.bin ${PROJ})

include_directories(test)
