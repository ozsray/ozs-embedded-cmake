# set cmake minimum required
cmake_minimum_required(VERSION 3.16)

# set cmake system name
set(CMAKE_SYSTEM_NAME Generic)

# build static libraries for compiler checks to avoid executable linking
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# toolchain installation directories for each host platform
set(TOOLCHAIN_DIR_WIN   "C:/path/to/wch-gcc")
set(TOOLCHAIN_DIR_LINUX "/path/to/wch-gcc")
set(TOOLCHAIN_DIR_MAC   "/path/to/wch-gcc")

# config
set(C_LANGUAGE_STANDARD "gnu99")
# set(C_LANGUAGE_STANDARD "gnu11")
# set(C_LANGUAGE_STANDARD "gnu17")

set(CXX_LANGUAGE_STANDARD "gnu++11")
# set(CXX_LANGUAGE_STANDARD "gnu++14")
# set(CXX_LANGUAGE_STANDARD "gnu++17")

# set(NEWLIB_OPTION "")
set(NEWLIB_OPTION "--specs=nano.specs")

# set(DEBUG_LEVEL "g0")
# set(DEBUG_LEVEL "g1")
set(DEBUG_LEVEL "g2")
# set(DEBUG_LEVEL "g3")

# set(OPTIMIZATION_LEVEL "O0")
set(OPTIMIZATION_LEVEL "O1")
# set(OPTIMIZATION_LEVEL "O2")
# set(OPTIMIZATION_LEVEL "O3")
# set(OPTIMIZATION_LEVEL "Os")
# set(OPTIMIZATION_LEVEL "Og")
# set(OPTIMIZATION_LEVEL "Ofast")

set(PROJECT_NAME "ch32v203x6")
set(TARGET_MAP   "${PROJECT_NAME}.map")
set(TARGET_ELF   "${PROJECT_NAME}.elf")
set(TARGET_HEX   "${PROJECT_NAME}.hex")
set(TARGET_BIN   "${PROJECT_NAME}.bin")
set(TARGET_LST   "${PROJECT_NAME}.lst")

set(COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../common")

set(LINK_FILE  "${CMAKE_CURRENT_SOURCE_DIR}/Ld/Link.ld")

set(START_FILE "${COMMON_DIR}/Startup/startup_ch32v20x_D6.S")

set(COMPILE_DEFINITIONS
    # add compile define
    DEBUG=2
)

set(INCLUDE_DIRS
    "${COMMON_DIR}/Core"
    "${COMMON_DIR}/Peripheral/inc"
    "${COMMON_DIR}/Debug"
    "${CMAKE_CURRENT_SOURCE_DIR}/User"
    # add include dirs
)

set(SOURCE_FILES
    "${START_FILE}"
    "${COMMON_DIR}/Core/core_riscv.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_adc.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_bkp.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_can.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_crc.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_dbgmcu.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_dma.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_exti.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_flash.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_gpio.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_i2c.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_iwdg.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_misc.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_opa.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_pwr.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_rcc.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_rtc.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_spi.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_tim.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_usart.c"
    "${COMMON_DIR}/Peripheral/src/ch32v20x_wwdg.c"
    "${COMMON_DIR}/Debug/debug.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/User/system_ch32v20x.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/User/ch32v20x_it.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/User/main.c"
    # add source files
)

set(EXTRA_LIBS
    # add extra libraries
)

# set toolchian to compile
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(TOOLCHAIN_CONFIG_VARIABLE "TOOLCHAIN_DIR_WIN")
    set(TOOLCHAIN_DIR "${TOOLCHAIN_DIR_WIN}")
    set(TOOLCHAIN_SUFFIX ".exe")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(TOOLCHAIN_CONFIG_VARIABLE "TOOLCHAIN_DIR_LINUX")
    set(TOOLCHAIN_DIR "${TOOLCHAIN_DIR_LINUX}")
    set(TOOLCHAIN_SUFFIX "")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(TOOLCHAIN_CONFIG_VARIABLE "TOOLCHAIN_DIR_MAC")
    set(TOOLCHAIN_DIR "${TOOLCHAIN_DIR_MAC}")
    set(TOOLCHAIN_SUFFIX "")
else()
    message(FATAL_ERROR "Unsupported host system ${CMAKE_HOST_SYSTEM_NAME}")
endif()

set(TOOLCHAIN_PREFIX   "riscv-none-embed-")
set(TOOLCHAIN_COMPILE  "${TOOLCHAIN_DIR}/bin/${TOOLCHAIN_PREFIX}")

set(CMAKE_C_COMPILER   "${TOOLCHAIN_COMPILE}gcc${TOOLCHAIN_SUFFIX}")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_COMPILE}g++${TOOLCHAIN_SUFFIX}")
set(CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}")
set(CMAKE_OBJCOPY      "${TOOLCHAIN_COMPILE}objcopy${TOOLCHAIN_SUFFIX}")
set(CMAKE_OBJDUMP      "${TOOLCHAIN_COMPILE}objdump${TOOLCHAIN_SUFFIX}")
set(CMAKE_SIZE         "${TOOLCHAIN_COMPILE}size${TOOLCHAIN_SUFFIX}")
set(CMAKE_AR           "${TOOLCHAIN_COMPILE}ar${TOOLCHAIN_SUFFIX}")

# report the toolchain configuration location
function(report_toolchain_error DETAIL)
    file(STRINGS "${CMAKE_CURRENT_LIST_FILE}" CONFIG_LINES ENCODING UTF-8)
    set(CONFIG_LINE_NUMBER 0)
    set(CONFIG_LOCATION "${CMAKE_CURRENT_LIST_FILE}")
    foreach(CONFIG_LINE IN LISTS CONFIG_LINES)
        math(EXPR CONFIG_LINE_NUMBER "${CONFIG_LINE_NUMBER} + 1")
        if(CONFIG_LINE MATCHES "^[ \t]*set\\([ \t]*${TOOLCHAIN_CONFIG_VARIABLE}([ \t]|$)")
            set(CONFIG_LOCATION "${CMAKE_CURRENT_LIST_FILE}:${CONFIG_LINE_NUMBER}")
            break()
        endif()
    endforeach()
    message(FATAL_ERROR
        "  ${DETAIL}\n"
        "  The toolchain directory may not be configured correctly.\n"
        "  Edit: ${CONFIG_LOCATION}"
    )
endfunction()

# validate the toolchain directories
if(NOT IS_DIRECTORY "${TOOLCHAIN_DIR}")
    report_toolchain_error("Toolchain directory does not exist: ${TOOLCHAIN_DIR}")
endif()

if(NOT IS_DIRECTORY "${TOOLCHAIN_DIR}/bin")
    report_toolchain_error("Toolchain bin directory does not exist: ${TOOLCHAIN_DIR}/bin")
endif()

# validate the toolchain executables
foreach(TOOL IN ITEMS
    CMAKE_C_COMPILER
    CMAKE_CXX_COMPILER
    CMAKE_ASM_COMPILER
    CMAKE_OBJCOPY
    CMAKE_OBJDUMP
    CMAKE_SIZE
    CMAKE_AR
)
    if(NOT EXISTS "${${TOOL}}" OR IS_DIRECTORY "${${TOOL}}")
        report_toolchain_error("Toolchain executable not found: ${TOOL} = ${${TOOL}}")
    endif()
endforeach()

# define the project and enable C, assembly, and C++
project("${PROJECT_NAME}" LANGUAGES C ASM CXX)

# create the firmware executable target
add_executable("${TARGET_ELF}"
    ${SOURCE_FILES}
)

# common options
set(COMMON_OPTIONS
    "-${OPTIMIZATION_LEVEL}"
    "-${DEBUG_LEVEL}"
    "-march=rv32imacxw"
    "-mabi=ilp32"
    "-msmall-data-limit=8"
    "-msave-restore"
    "-fdata-sections"
    "-ffunction-sections"
    "-fsigned-char"
    "-fno-common"
    "-fmax-errors=20"
    "-fmessage-length=0"
    "-Wall"
)

# compile options
target_compile_options("${TARGET_ELF}" PRIVATE
    ${COMMON_OPTIONS}
    "$<$<COMPILE_LANGUAGE:C,CXX>:${NEWLIB_OPTION}>"
    "$<$<COMPILE_LANGUAGE:C>:-std=${C_LANGUAGE_STANDARD}>"
    "$<$<COMPILE_LANGUAGE:CXX>:-std=${CXX_LANGUAGE_STANDARD}>"
    "$<$<COMPILE_LANGUAGE:CXX>:-fabi-version=0>"
    "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-x assembler-with-cpp>"
)

# link options
target_link_options("${TARGET_ELF}" PRIVATE
    ${COMMON_OPTIONS}
    -T "${LINK_FILE}"
    -nostartfiles
    ${NEWLIB_OPTION}
    --specs=nosys.specs
    "LINKER:--gc-sections"
    "LINKER:-Map,${TARGET_MAP}"
    "LINKER:--print-memory-usage"
)

set_property(TARGET "${TARGET_ELF}" APPEND PROPERTY LINK_DEPENDS "${LINK_FILE}")

# compile definitions
target_compile_definitions("${TARGET_ELF}" PRIVATE
    "$<$<COMPILE_LANGUAGE:C,CXX>:${COMPILE_DEFINITIONS}>"
)

# include directories
target_include_directories("${TARGET_ELF}" PRIVATE
    ${INCLUDE_DIRS}
)

# link libraries
target_link_libraries("${TARGET_ELF}" PRIVATE
    ${EXTRA_LIBS}
)

# generate firmware artifacts and report size
add_custom_command(TARGET "${TARGET_ELF}"
    POST_BUILD
    BYPRODUCTS "${TARGET_HEX}" "${TARGET_BIN}" "${TARGET_LST}" "${TARGET_MAP}"
    COMMAND "${CMAKE_OBJCOPY}" -O ihex   "${TARGET_ELF}" "${TARGET_HEX}"
    COMMAND "${CMAKE_OBJCOPY}" -O binary "${TARGET_ELF}" "${TARGET_BIN}"
    COMMAND "${CMAKE_OBJDUMP}" --all-headers --demangle --disassemble -M xw "${TARGET_ELF}" > "${TARGET_LST}"
    COMMAND "${CMAKE_SIZE}"    --format=berkeley "${TARGET_ELF}"
)
