cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
  set(IS_SUBDIRECTORY OFF)
else()
  set(IS_SUBDIRECTORY ON)
endif()

set(OUTPUT "ResourceGenerator")
project(${OUTPUT} VERSION 5.3)
set(CMAKE_CXX_STANDARD 20)
if(MSVC)
  set(WARNINGS "/W4")
  if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    set(OPTIMIZATIONS "/MTd" "/Od")
    set(LINKER_FLAGS "/INCREMENTAL:NO" "/NODEFAULTLIB:MSVCRTD")
  else()
    set(OPTIMIZATIONS "/MT" "/O2")
    set(LINKER_FLAGS "/INCREMENTAL:NO" "/NODEFAULTLIB:MSVCRT")
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(
    WARNINGS
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Wconversion"
    "-Wshadow"
    "-Wundef"
    "-Wclobbered"
    "-Wdeprecated"
    "-Wmultichar"
    "-Wuninitialized"
    "-Wunreachable-code"
    "-Wstrict-aliasing"
    "-Wreturn-type"
    "-Wtype-limits"
    "-Wformat-security"
    "-Wpointer-arith"
    "-Wmaybe-uninitialized"
    "-Wempty-body"
    "-Wdouble-promotion"
    "-Wcast-qual"
    "-Wcast-align"
    "-Wfloat-equal"
    "-Wlogical-op"
    "-Wduplicated-cond"
    "-Wshift-overflow=2"
    "-Wformat=2"
  )
  if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    set(OPTIMIZATIONS "-g" "-Og")
  else()
    set(OPTIMIZATIONS "-s" "-O3")
  endif()
  set(LINKER_FLAGS "-static" "-static-libgcc" "-static-libstdc++")
endif()
set(PROGRAM_INCLUDE_DIR "program/include")
set(PROGRAM_SOURCE_DIR "program/source")
set(EXTERNAL_INCLUDE_DIR "external/include")
set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/${PROGRAM_INCLUDE_DIR}")
set(
  SYSTEM_INCLUDE_DIRS
  "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_INCLUDE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_INCLUDE_DIR}/stb"
)
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${PROGRAM_SOURCE_DIR}/*.cpp")
set(BUILD_SHARED_LIBS OFF)

add_executable("${OUTPUT}")
target_include_directories("${OUTPUT}" PRIVATE "${INCLUDE_DIRS}")
target_include_directories("${OUTPUT}" SYSTEM PRIVATE "${SYSTEM_INCLUDE_DIRS}")
target_sources("${OUTPUT}" PRIVATE "${SOURCE_FILES}")
target_compile_options("${OUTPUT}" PRIVATE "${WARNINGS}" "${OPTIMIZATIONS}")
target_link_options("${OUTPUT}" PRIVATE "${LINKER_FLAGS}")

if(NOT "${IS_SUBDIRECTORY}")
  set(COMPILE_COMMANDS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json")
  set(COMPILE_COMMANDS_INDEX 0)
  file(WRITE "${COMPILE_COMMANDS_FILE}" "[\n")
  foreach(SRC ${SOURCE_FILES})
    list(LENGTH SOURCE_FILES NUM_SOURCE_FILES)
    get_filename_component(SRC_EXT "${SRC}" EXT)
    if("${SRC_EXT}" MATCHES "cpp")
      file(
        APPEND
        "${COMPILE_COMMANDS_FILE}"
        "  {\n    \"directory\": \"${CMAKE_CURRENT_SOURCE_DIR}\",\n    \"file\": \"${SRC}\",\n    \"command\": \"clang++ -std=c++${CMAKE_CXX_STANDARD} -Wall -Wextra -Wpedantic -Wconversion -Wshadow-all -Wundef -Wdeprecated -Wtype-limits -Wcast-qual -Wcast-align -Wfloat-equal -Wparentheses -Wunreachable-code-aggressive -Wformat=2 "
      )
    else()
      file(
        APPEND
        "${COMPILE_COMMANDS_FILE}"
        "  {\n    \"directory\": \"${CMAKE_CURRENT_SOURCE_DIR}\",\n    \"file\": \"${SRC}\",\n    \"command\": \"clang "
      )
    endif()
    foreach(DIR ${INCLUDE_DIRS})
      file(APPEND "${COMPILE_COMMANDS_FILE}" "-I\\\"${DIR}\\\" ")
    endforeach()
    foreach(DIR ${SYSTEM_INCLUDE_DIRS})
      file(APPEND "${COMPILE_COMMANDS_FILE}" "-isystem\\\"${DIR}\\\" ")
    endforeach()
    file(APPEND "${COMPILE_COMMANDS_FILE}" "-c \\\"${SRC}\\\"\"\n  }")
    math(EXPR COMPILE_COMMANDS_INDEX "${COMPILE_COMMANDS_INDEX} + 1")
    if(NOT "${COMPILE_COMMANDS_INDEX}" EQUAL "${NUM_SOURCE_FILES}")
      file(APPEND "${COMPILE_COMMANDS_FILE}" ",\n")
    else()
      file(APPEND "${COMPILE_COMMANDS_FILE}" "\n]")
    endif()
  endforeach()

  set(FORMAT "Format")
  set(FORMAT_MARKER_DIR "${CMAKE_CURRENT_BINARY_DIR}/FormatMarkers")
  set(FORMAT_MARKERS "")
  file(
    GLOB FORMAT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROGRAM_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROGRAM_INCLUDE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROGRAM_INCLUDE_DIR}/*.inl"
  )
  foreach(FILE ${FORMAT_FILES})
    get_filename_component(FILE_NAME "${FILE}" NAME)
    set(FORMAT_FILE "${FORMAT_MARKER_DIR}/${FILE_NAME}.format")
    add_custom_command(
      OUTPUT "${FORMAT_FILE}"
      COMMAND clang-format -i "${FILE}"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${FORMAT_MARKER_DIR}"
      COMMAND "${CMAKE_COMMAND}" -E touch "${FORMAT_FILE}"
      DEPENDS "${FILE}"
    )
    list(APPEND FORMAT_MARKERS "${FORMAT_FILE}")
  endforeach()
  add_custom_target("${FORMAT}" DEPENDS "${FORMAT_MARKERS}")
  add_dependencies("${OUTPUT}" "${FORMAT}")
endif()
