cmake_minimum_required(VERSION 3.21)

project(
  PascalGovernor
  VERSION 1.0
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
  find_program(
    CLANG_TIDY_EXE
    NAMES clang-tidy clang-tidy.exe
    PATHS "${ANDROID_TOOLCHAIN_ROOT}/bin"
    NO_DEFAULT_PATH)

  if(CLANG_TIDY_EXE)
    set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_EXE}")
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
  else()
    message(WARNING "clang-tidy not found in NDK toolchain")
  endif()
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "" FORCE)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT LTO_SUPPORTED OUTPUT LTO_ERROR)

file(GLOB_RECURSE PASCAL_SOURCES CONFIGURE_DEPENDS "src/*.c")

list(REMOVE_ITEM PASCAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

add_library(pascal STATIC ${PASCAL_SOURCES})

target_include_directories(pascal PUBLIC "${CMAKE_SOURCE_DIR}/include")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(
    pascal
    PRIVATE -O3
            -ffunction-sections
            -fdata-sections
            -fvisibility=hidden
            -fno-math-errno
            -fno-strict-aliasing
            -Wall
            -Wextra
            -Werror)

  if(LTO_SUPPORTED)
    set_property(TARGET pascal PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()

else()
  target_compile_definitions(pascal PRIVATE DEBUG)
endif()

add_executable(pascal_gov "src/main.c")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_link_options(pascal_gov PRIVATE -Wl,--gc-sections -Wl,--icf=all -Wl,-s
                      -Wl,--build-id=none)

  if(LTO_SUPPORTED)
    set_property(TARGET pascal_gov PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()
endif()

target_link_libraries(pascal_gov PRIVATE pascal android log m)
