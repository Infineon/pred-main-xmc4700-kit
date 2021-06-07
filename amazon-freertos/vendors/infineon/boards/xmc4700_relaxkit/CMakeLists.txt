# Set variables.
set(xmc4700_dir "${AFR_VENDORS_DIR}/infineon/boards/xmc4700_relaxkit")
set(xmc4700_ports_dir "${xmc4700_dir}/ports")
set(xmclib_dir "${AFR_VENDORS_DIR}/infineon/XMCLib/2.2.0")
set(xmc4700_dave_dir "${AFR_ROOT_DIR}/projects/infineon/xmc4700_relaxkit/dave4/aws_demos/Dave/Generated")
set(afr_lib_dir "${AFR_ROOT_DIR}/libraries")


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CONFIG_USE_OPTIGA STREQUAL "TRUST_X")
    set(optiga_dir "${AFR_VENDORS_DIR}/infineon/secure_elements/optiga_trust_x")
elseif(CONFIG_USE_OPTIGA STREQUAL "TRUST_M")
    set(optiga_dir "${AFR_VENDORS_DIR}/infineon/secure_elements/optiga_trust_m")
endif()

if(AFR_IS_TESTING)
    set(xmc4700_aws_dir "${xmc4700_dir}/aws_tests")
else()
    set(xmc4700_aws_dir "${xmc4700_dir}/aws_demos")
endif()

#Tool chain specific check
if(NOT ${AFR_TOOLCHAIN} STREQUAL "arm-gcc")
   if(NOT AFR_METADATA_MODE)
       message( FATAL_ERROR "The toolchain is not supported." )
   endif()
endif()

# -------------------------------------------------------------------------------------------------
# Amazon FreeRTOS Console metadata
# -------------------------------------------------------------------------------------------------

afr_set_board_metadata(ID "Infineon-XMC4700-Relax-Kit")
afr_set_board_metadata(DISPLAY_NAME "XMC4700 Relax Kit")
afr_set_board_metadata(DESCRIPTION "Development kit for ARM Cortex-M4 based XMC4700 MCU")
afr_set_board_metadata(VENDOR_NAME "Infineon")
afr_set_board_metadata(FAMILY_NAME "XMC4x00")
afr_set_board_metadata(CODE_SIGNER "null")
afr_set_board_metadata(DATA_RAM_MEMORY "352KB")
afr_set_board_metadata(PROGRAM_MEMORY "2MB")
afr_set_board_metadata(SUPPORTED_IDE "DAVE")
afr_set_board_metadata(RECOMMENDED_IDE "DAVE")
afr_set_board_metadata(IDE_DAVE_NAME "DAVE")
afr_set_board_metadata(IDE_DAVE_COMPILER "GCC")
if ((CONFIG_USE_OPTIGA STREQUAL "TRUST_X") OR (CONFIG_USE_OPTIGA STREQUAL "TRUST_M"))
afr_set_board_metadata(KEY_IMPORT_PROVISIONING "FALSE")
else()
afr_set_board_metadata(KEY_IMPORT_PROVISIONING "TRUE")
endif()
afr_set_board_metadata(IS_ACTIVE "TRUE")
afr_set_board_metadata(IDE_DAVE_PROJECT_LOCATION "${AFR_ROOT_DIR}/projects/infineon/xmc4700_relaxkit/dave4/aws_demos")
afr_set_board_metadata(AWS_DEMOS_CONFIG_FILES_LOCATION "${AFR_ROOT_DIR}/vendors/infineon/boards/xmc4700_relaxkit/aws_demos/config_files")

# -------------------------------------------------------------------------------------------------
# Compiler settings
# -------------------------------------------------------------------------------------------------
afr_mcu_port(compiler)


#Set defined symbols for compiler and assembler
set( defined_symbols
     XMC4700_F144x2048
     PRINTF_INCLUDE_CONFIG_H
)

if ((CONFIG_USE_OPTIGA STREQUAL "TRUST_X") OR (CONFIG_USE_OPTIGA STREQUAL "TRUST_M"))
set( defined_symbols 
     ${defined_symbols}
     USE_CMDLIB_WITH_RTOS
     MBEDTLS_ECDSA_SIGN_ALT
     MBEDTLS_ECDSA_VERIFY_ALT
     MBEDTLS_ECDH_COMPUTE_SHARED_ALT
     MBEDTLS_ECDH_GEN_PUBLIC_ALT
     PAL_OS_HAS_EVENT_INIT
#     CONFIG_USE_OPTIGA
	 MBEDTLS_CONFIG_FILE="optiga_mbedtls_config.h"
)
endif()

if (CONFIG_USE_OPTIGA STREQUAL "TRUST_X")
set( defined_symbols 
     ${defined_symbols}
     CONFIG_USE_OPTIGA_TRUSTX
)
elseif(CONFIG_USE_OPTIGA STREQUAL "TRUST_M")
set( defined_symbols 
     ${defined_symbols}
     CONFIG_USE_OPTIGA_TRUSTM
)
endif()



# Compiler defined symbols.
target_compile_definitions(
    AFR::compiler::mcu_port
    INTERFACE
    ${defined_symbols}
)

#Set Compiler Debug options
set( compiler_debug_options "-g" "-gdwarf-2")

#Set compiler warnings level
set( compiler_warnings "-Wall" )

#Set compiler optimization level
set( compiler_optimization_options "-O2" "-fomit-frame-pointer" "-ffunction-sections" "-fdata-sections" "-ffreestanding" "-fno-builtin" "-fno-common")

#Set ARM GCC options
set( compiler_arm_options "-mfloat-abi=softfp" "-mcpu=cortex-m4" "-mfpu=fpv4-sp-d16" "-mthumb")

#Set other compiler options and flags
set( compiler_misc_options
     "-std=c99"
     "-c"
     "-fmessage-length=0"
)

#All compiler options
set( compiler_flags
     ${compiler_debug_options}
     ${compiler_warnings}
     ${compiler_optimization_options}
     ${compiler_arm_options}
     ${compiler_misc_options}
     "-pipe" )
target_compile_options(
    AFR::compiler::mcu_port
    INTERFACE
        $<$<COMPILE_LANGUAGE:C>:${compiler_flags}>
)


#All assembler options
set( assembler_flags
     "-x"
     "assembler-with-cpp"
     ${compiler_debug_options}
     ${compiler_warnings}
     ${compiler_optimization_options}
     ${compiler_arm_options}
     ${compiler_misc_options}
)
target_compile_options(
    AFR::compiler::mcu_port
    INTERFACE
        $<$<COMPILE_LANGUAGE:ASM>:${assembler_flags}>
)


#Linker script path
if ((CONFIG_USE_OPTIGA STREQUAL "TRUST_X") OR (CONFIG_USE_OPTIGA STREQUAL "TRUST_M"))
set( linker_script "${xmc4700_dir}/XMC4700x2048.ld" )
else()
set( linker_script "${xmc4700_dir}/XMC4700x2048_EEPROM.ld" )
endif()

#All linker options
set( linker_flags
     "-T" ${linker_script}
     "-nostartfiles"
     "-Xlinker"
     "--gc-sections"
     "-specs=nano.specs"
     "-specs=nosys.specs"
     "-Wl,-Map,aws_demos.map"
     ${compiler_arm_options}
     ${compiler_debug_options}
)

target_link_options(
    AFR::compiler::mcu_port
    INTERFACE
        ${linker_flags}
)

#Linker libraries
set(linker_libs
    "m"
)
target_link_libraries(
    AFR::compiler::mcu_port
    INTERFACE
        ${linker_libs}
)

# -------------------------------------------------------------------------------------------------
# Kernel and Amazon FreeRTOS portable layers
# -------------------------------------------------------------------------------------------------

# Kernel
afr_mcu_port(kernel)

#Driver source files
afr_glob_src(driver_src DIRECTORY "${xmclib_dir}/drivers/src")
afr_glob_src(cmsis_driver_src DIRECTORY "${xmclib_dir}/CMSIS/Driver/Source")

if ((CONFIG_USE_OPTIGA STREQUAL "TRUST_X") OR (CONFIG_USE_OPTIGA STREQUAL "TRUST_M"))
#Trust X/M source files
afr_glob_src(trustx_src DIRECTORY "${optiga_dir}/optiga" RECURSE)

if (CONFIG_USE_OPTIGA STREQUAL "TRUST_X")
afr_glob_src(trustx_examples DIRECTORY "${optiga_dir}/examples" RECURSE)
endif()

if (CONFIG_USE_OPTIGA STREQUAL "TRUST_M")
afr_glob_src(trustx_pal_src DIRECTORY "${optiga_dir}/pal/xmc4700_freertos" RECURSE)
afr_glob_src(trustx_examples DIRECTORY "${optiga_dir}/examples" RECURSE)
afr_glob_src(trustx_mbedtls_port_src DIRECTORY "${optiga_dir}/examples/mbedtls_port" RECURSE)
afr_glob_src(trustx_utils_src DIRECTORY "${optiga_dir}/examples/utilities")

set( trustx_pal_src
     ${trustx_pal_src} 
     "${optiga_dir}/pal/pal_crypt_mbedtls.c"
)
endif()

endif()

#Source files specific to compiler
set(compiler_src
    "${AFR_KERNEL_DIR}/portable/GCC/ARM_CM4F/port.c"
    "${AFR_KERNEL_DIR}/portable/GCC/ARM_CM4F/portmacro.h"
    "${xmclib_dir}/CMSIS/Infineon/XMC4700_series/Source/system_XMC4700.c"
    "${xmclib_dir}/CMSIS/Infineon/XMC4700_series/Source/GCC/startup_XMC4700.S"
)

target_sources(
    AFR::kernel::mcu_port
    INTERFACE
       "${AFR_KERNEL_DIR}/portable/MemMang/heap_4.c"
        ${compiler_src}
        ${driver_src}
        ${cmsis_driver_src}
        ${trustx_src}
#        ${trustx_examples}
        ${trustx_utils_src}
        ${trustx_mbedtls_port_src}
        ${trustx_pal_src} 

)

#Include directories specific to compiler
set(compiler_includes
    "${AFR_KERNEL_DIR}/portable/GCC/ARM_CM4F"
)
set( board_includes
    "${xmclib_dir}/CMSIS/Include"
    "${xmclib_dir}/drivers/inc"
    "${xmclib_dir}/CMSIS/Infineon/XMC4700_series/Include"
    "${xmclib_dir}/CMSIS/Driver/Include"
    "${xmclib_dir}/third_party/printf"
    "${xmc4700_aws_dir}/config_files"

    "${xmc4700_aws_dir}/application_code"
    "${xmc4700_aws_dir}/application_code/drivers"
    "${xmc4700_aws_dir}/application_code/drivers/components"
    "${xmc4700_aws_dir}/application_code/drivers/components/led"
    "${xmc4700_aws_dir}/application_code/drivers/components/micro"
    "${xmc4700_aws_dir}/application_code/drivers/mux"
    "${xmc4700_aws_dir}/application_code/drivers/mux/i2c_mux"
    "${xmc4700_aws_dir}/application_code/drivers/mux/spi_mux"
    "${xmc4700_aws_dir}/application_code/drivers/mux/spi_mux/LTC4332"
    "${xmc4700_aws_dir}/application_code/drivers/sensors"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/DPS368"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/DPS368/corelib"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/IM69D"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x/TLE4964/corelib"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x/TLx4966/corelib"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x/TLx4966/pal"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE4997"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLI4971"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLV493D/corelib"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLV493D/corelib/util"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/pal"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLE_AW2B6"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLE_AW2B6/driver"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLV_A1B6"
    "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLV_A1B6/driver"
    "${xmc4700_aws_dir}/application_code/drivers/wireless"
    "${xmc4700_aws_dir}/application_code/drivers/wireless/inventek"
    "${xmc4700_aws_dir}/application_code/drivers/wireless/modem"
    "${xmc4700_aws_dir}/application_code/infineon_code"
    "${xmc4700_aws_dir}/application_code/misc"
    "${xmc4700_aws_dir}/application_code/misc/converting"
    "${xmc4700_aws_dir}/application_code/misc/dbg"
    "${xmc4700_aws_dir}/application_code/misc/delay"
    "${xmc4700_aws_dir}/application_code/misc/fft"
    "${xmc4700_aws_dir}/application_code/misc/fifo"
    "${xmc4700_aws_dir}/application_code/misc/float_to_string"
    "${xmc4700_aws_dir}/application_code/misc/json"
    "${xmc4700_aws_dir}/application_code/misc/statistic"
    "${xmc4700_aws_dir}/application_code/test"
    "${xmc4700_aws_dir}/application_code/test/dps368_test"
    "${xmc4700_aws_dir}/application_code/test/json_sensor_test"
    "${xmc4700_aws_dir}/application_code/test/test_task"
    "${xmc4700_aws_dir}/application_code/test/tle4964_test"
    "${xmc4700_aws_dir}/application_code/test/tli493d_test"
    "${xmc4700_aws_dir}/application_code/test/tlx4966_test"

    "${xmc4700_dave_dir}"
    "${xmc4700_dave_dir}/ADC_MEASUREMENT_ADV"
    "${xmc4700_dave_dir}/ANALOG_IO"
    "${xmc4700_dave_dir}/CAPTURE"
    "${xmc4700_dave_dir}/CLOCK_XMC4"
    "${xmc4700_dave_dir}/CMSIS_DSP"
    "${xmc4700_dave_dir}/CMSIS_DSP/Include"
    "${xmc4700_dave_dir}/CMSIS_DSP/PrivateInclude"
    "${xmc4700_dave_dir}/CPU_CTRL_XMC4"
    "${xmc4700_dave_dir}/DIGITAL_IO"
    "${xmc4700_dave_dir}/GLOBAL_ADC"
    "${xmc4700_dave_dir}/GLOBAL_CCU4"
#   "${xmc4700_dave_dir}/GLOBAL_DMA"
    "${xmc4700_dave_dir}/I2C_MASTER"
    "${xmc4700_dave_dir}/I2S_CONFIG"
    "${xmc4700_dave_dir}/INTERRUPT"
    "${xmc4700_dave_dir}/PIN_INTERRUPT"
    "${xmc4700_dave_dir}/SPI_MASTER"
    "${xmc4700_dave_dir}/UART"

    "${xmclib_dir}/Newlib"
    "${xmclib_dir}/third_party/printf"

    "${xmc4700_ports_dir}/wifi"
    "${afr_lib_dir}/abstractions/wifi/include"
    "${afr_lib_dir}/abstractions/secure_sockets/include"

    "${AFR_ROOT_DIR}/demos/network_manager"
    "${AFR_ROOT_DIR}/libraries/abstractions/platform/include"
    "${AFR_ROOT_DIR}/libraries/3rdparty/tinycbor"
    "${AFR_ROOT_DIR}/libraries/freertos_plus/standard/tls/include"
    

)

if ((CONFIG_USE_OPTIGA STREQUAL "TRUST_X") OR (CONFIG_USE_OPTIGA STREQUAL "TRUST_M"))
set( board_includes
     ${board_includes}
     "${optiga_dir}"
     "${optiga_dir}/examples/optiga/include"
     "${optiga_dir}/examples/utilities"
     "${optiga_dir}/examples/tools/protected_update_data_set/include"
     "${optiga_dir}/examples/tools/protected_update_data_set/include/pal"
     "${optiga_dir}/optiga/include"
     "${optiga_dir}/optiga/include/optiga"
     "${optiga_dir}/optiga/include/optiga/cmd"
     "${optiga_dir}/optiga/include/optiga/comms"
     "${optiga_dir}/optiga/include/optiga/pal"
     "${optiga_dir}/optiga/include/optiga/common"
     "${optiga_dir}/optiga/include/optiga/ifx_i2c"
     "${optiga_dir}/pal/xmc4700_freertos"
     "${AFR_VENDORS_DIR}/infineon/secure_elements/pkcs11"
)
endif()

if (CONFIG_USE_OPTIGA STREQUAL "TRUST_X")
set( board_includes
     ${board_includes}
     "${optiga_dir}/examples/authenticate_chip"
     "${optiga_dir}/examples/ecdsa_utils"
   
)
elseif (CONFIG_USE_OPTIGA STREQUAL "TRUST_M")
set( board_includes
     ${board_includes}
    #

)

endif()

set(kernel_includes
    ${board_includes}
    ${compiler_includes}
    "${AFR_KERNEL_DIR}/include"
    "$<IF:${AFR_IS_TESTING},${AFR_TESTS_DIR},${AFR_DEMOS_DIR}>/include"
    "${AFR_3RDPARTY_DIR}/mbedtls/include"
    "${xmc4700_aws_dir}/config_files"
)

target_include_directories(
    AFR::kernel::mcu_port
    INTERFACE $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:${kernel_includes}>
)

#Posix
afr_mcu_port(posix)

target_sources(
    AFR::posix::mcu_port
    INTERFACE "${xmc4700_ports_dir}/posix/FreeRTOS_POSIX_portable.h"
)

target_include_directories(
    AFR::posix::mcu_port
    INTERFACE "${xmc4700_ports_dir}/posix"
)

target_link_libraries(
    AFR::posix::mcu_port
    INTERFACE AFR::freertos_plus_posix
)

if (CONFIG_USE_OPTIGA STREQUAL "TRUST_X")
# PKCS11
afr_mcu_port(pkcs11_implementation)
target_sources(
    AFR::pkcs11_implementation::mcu_port
    INTERFACE
        "${AFR_VENDORS_DIR}/infineon/secure_elements/pkcs11/iot_pkcs11_trustx.c"
)
elseif (CONFIG_USE_OPTIGA STREQUAL "TRUST_M")
# PKCS11
afr_mcu_port(pkcs11_implementation)
target_sources(
    AFR::pkcs11_implementation::mcu_port
    INTERFACE
        "${AFR_VENDORS_DIR}/infineon/secure_elements/pkcs11/iot_pkcs11_trustm.c"
)
else()
# PKCS11
afr_mcu_port(pkcs11_implementation DEPENDS AFR::pkcs11_mbedtls)
target_sources(
    AFR::pkcs11_implementation::mcu_port
    INTERFACE
        "${xmc4700_ports_dir}/pkcs11/iot_pkcs11_pal.c"
)
endif()

# WiFi
afr_mcu_port(wifi)
target_sources(
    AFR::wifi::mcu_port
    INTERFACE "${xmc4700_ports_dir}/wifi/iot_wifi.c"
)

# Secure sockets
afr_mcu_port(secure_sockets)
target_link_libraries(
    AFR::secure_sockets::mcu_port
    INTERFACE
        AFR::tls
        AFR::wifi
        AFR::pkcs11
)

target_sources(
    AFR::secure_sockets::mcu_port
    INTERFACE "${xmc4700_ports_dir}/secure_sockets/wifi_secure_sockets.c"
)


# -------------------------------------------------------------------------------------------------
# Amazon FreeRTOS demos and tests
# -------------------------------------------------------------------------------------------------
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

if(AFR_IS_TESTING)
    set(exe_target aws_tests)
else()
    set(exe_target aws_demos)
endif()

# xmc4700_aws_dir
afr_glob_src(application_code DIRECTORY "${xmc4700_aws_dir}/application_code")
afr_glob_src(config_src DIRECTORY "${xmc4700_aws_dir}/config_files")
afr_glob_src(led DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/components/led")
afr_glob_src(micro DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/components/micro")
afr_glob_src(i2c_mux DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/mux/i2c_mux")
afr_glob_src(spi_mux DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/mux/spi_mux")
afr_glob_src(ltc4332 DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/mux/spi_mux/LTC4332")
afr_glob_src(sensors DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors")
afr_glob_src(dps368 DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/DPS368")
afr_glob_src(dps368_corelib DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/DPS368/corelib")
afr_glob_src(im69d DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/IM69D")
afr_glob_src(tle496x DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x")
afr_glob_src(tle4964_corelib DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x/TLE4964/corelib")
afr_glob_src(tlx4966_corelib DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x/TLx4966/corelib")
afr_glob_src(tlx4966_pal DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE496x/TLx4966/pal")
afr_glob_src(tle4997 DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLE4997")
afr_glob_src(tli4971 DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLI4971")
afr_glob_src(tlv493_corelib DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLV493D/corelib")
afr_glob_src(tlv493_util DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLV493D/corelib/util")
afr_glob_src(tlx493d DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D")
afr_glob_src(tlx493d_pal DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/pal")
afr_glob_src(tle_aw2b6 DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLE_AW2B6")
afr_glob_src(tle_aw2b6_driver DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLE_AW2B6/driver")
afr_glob_src(tlv_a1b6 DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLV_A1B6")
afr_glob_src(tlv_a1b6_driver DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/sensors/TLx493D/TLV_A1B6/driver")
afr_glob_src(inventek DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/wireless/inventek")
afr_glob_src(modem DIRECTORY "${xmc4700_aws_dir}/application_code/drivers/wireless/modem")
afr_glob_src(board_src DIRECTORY "${xmc4700_aws_dir}/application_code/infineon_code")
afr_glob_src(misc DIRECTORY "${xmc4700_aws_dir}/application_code/misc")
afr_glob_src(converting DIRECTORY "${xmc4700_aws_dir}/application_code/misc/converting")
afr_glob_src(dbg DIRECTORY "${xmc4700_aws_dir}/application_code/misc/dbg")
afr_glob_src(delay DIRECTORY "${xmc4700_aws_dir}/application_code/misc/delay")
afr_glob_src(fft DIRECTORY "${xmc4700_aws_dir}/application_code/misc/fft")
afr_glob_src(fifo DIRECTORY "${xmc4700_aws_dir}/application_code/misc/fifo")
afr_glob_src(float_to_string DIRECTORY "${xmc4700_aws_dir}/application_code/misc/float_to_string")
afr_glob_src(json DIRECTORY "${xmc4700_aws_dir}/application_code/misc/json")
afr_glob_src(statistic DIRECTORY "${xmc4700_aws_dir}/application_code/misc/statistic")
afr_glob_src(test DIRECTORY "${xmc4700_aws_dir}/application_code/test")
afr_glob_src(dps368_test DIRECTORY "${xmc4700_aws_dir}/application_code/test/dps368_test")
afr_glob_src(json_test DIRECTORY "${xmc4700_aws_dir}/application_code/test/json_sensor_test")
afr_glob_src(test_task DIRECTORY "${xmc4700_aws_dir}/application_code/test/test_task")
afr_glob_src(tle4964_test DIRECTORY "${xmc4700_aws_dir}/application_code/test/tle4964_test")
afr_glob_src(tli493d_test DIRECTORY "${xmc4700_aws_dir}/application_code/test/tli493d_test")
afr_glob_src(tlx4966_test DIRECTORY "${xmc4700_aws_dir}/application_code/test/tlx4966_test")

# xmc4700_dave_dir
afr_glob_src(dave DIRECTORY "${xmc4700_dave_dir}")
afr_glob_src(adc_adv DIRECTORY "${xmc4700_dave_dir}/ADC_MEASUREMENT_ADV")
afr_glob_src(analog DIRECTORY "${xmc4700_dave_dir}/ANALOG_IO")
afr_glob_src(capture DIRECTORY "${xmc4700_dave_dir}/CAPTURE")
afr_glob_src(clock DIRECTORY "${xmc4700_dave_dir}/CLOCK_XMC4")
afr_glob_src(cmsis_dsp DIRECTORY "${xmc4700_dave_dir}/CMSIS_DSP" RECURSE)
afr_glob_src(cpu_ctrl DIRECTORY "${xmc4700_dave_dir}/CPU_CTRL_XMC4")
afr_glob_src(digital DIRECTORY "${xmc4700_dave_dir}/DIGITAL_IO")
afr_glob_src(adc DIRECTORY "${xmc4700_dave_dir}/GLOBAL_ADC")
afr_glob_src(ccu4 DIRECTORY "${xmc4700_dave_dir}/GLOBAL_CCU4")
# afr_glob_src(dma DIRECTORY "${xmc4700_dave_dir}/GLOBAL_DMA")
afr_glob_src(i2c DIRECTORY "${xmc4700_dave_dir}/I2C_MASTER")
afr_glob_src(i2s DIRECTORY "${xmc4700_dave_dir}/I2S_CONFIG")
afr_glob_src(interrupt DIRECTORY "${xmc4700_dave_dir}/INTERRUPT")
afr_glob_src(pin_interrupt DIRECTORY "${xmc4700_dave_dir}/PIN_INTERRUPT")
afr_glob_src(spi DIRECTORY "${xmc4700_dave_dir}/SPI_MASTER")
afr_glob_src(uart DIRECTORY "${xmc4700_dave_dir}/UART")

# xmclib_dir
afr_glob_src(newlib DIRECTORY "${xmclib_dir}/Newlib")
afr_glob_src(printf DIRECTORY "${xmclib_dir}/third_party/printf")


# Do not add demos or tests if they're turned off.
if(AFR_ENABLE_DEMOS OR AFR_ENABLE_TESTS)
    add_executable(
        ${exe_target}

        ${application_code}
        ${config_src}

        ${led}
        ${micro}
        ${i2c_mux}
        ${spi_mux}
        ${ltc4332}
        ${sensors}
        ${dps368}
        ${dps368_corelib}
        ${im69d}
        ${tle496x}
        ${tle4964_corelib}
        ${tlx4966_corelib}
        ${tlx4966_pal}
        ${tle4997}
        ${tli4971}
        ${tlv493_corelib}
        ${tlv493_util}
        ${tlx493d}
        ${tlx493d_pal}
        ${tle_aw2b6}
        ${tle_aw2b6_driver}
        ${tlv_a1b6}
        ${tlv_a1b6_driver}
        ${inventek}
        ${modem}
        ${board_src}
        ${misc}
        ${converting}
        ${dbg}
        ${delay}
        ${fft}
        ${fifo}
        ${float_to_string}
        ${json}
        ${statistic}
        ${test}
        ${dps368_test}
        ${json_test}
        ${test_task}
        ${tle4964_test}
        ${tli493d_test}
        ${tlx4966_test}
   
        ${dave}
        ${adc_adv}
        ${analog}
        ${capture}
        ${clock}
        ${cmsis_dsp}
        ${cpu_ctrl}
        ${digital}
        ${adc}
        ${ccu4}
#       ${dma}
        ${i2c}
        ${i2s}
        ${interrupt}
        ${pin_interrupt}
        ${spi}
        ${uart}

        ${newlib}
        ${printf}
        
        ${linker_script}
        #"${xmc4700_aws_dir}/application_code/main.c"
    )

    target_link_libraries(
        ${exe_target}
        PRIVATE
            AFR::dev_mode_key_provisioning
            AFR::wifi
            AFR::utils
    )

    if(AFR_METADATA_MODE)
        return()
    endif()

    find_program(gcc_objectcopy arm-none-eabi-objcopy)
    find_program(gcc_size arm-none-eabi-size)

    if(NOT gcc_objectcopy )
        message(FATAL_ERROR "Cannot find arm-none-eabi-objcopy.")
    endif()

    set(output_file "$<TARGET_FILE_DIR:${exe_target}>/${exe_target}.hex")

    add_custom_command(
        TARGET ${exe_target} POST_BUILD
        COMMAND "${gcc_objectcopy}" -O ihex "$<TARGET_FILE:${exe_target}>" "${output_file}"
        COMMAND "${gcc_size}" "$<TARGET_FILE:${exe_target}>"
    )

    add_custom_command(
        TARGET ${exe_target} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy "${output_file}" "${CMAKE_BINARY_DIR}"
    )
endif()
