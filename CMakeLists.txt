cmake_minimum_required(VERSION 4.0)
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
  set(IS_SUBDIRECTORY OFF)
else()
  set(IS_SUBDIRECTORY ON)
endif()

set(OUTPUT "SimpleGameEngine")
project(${OUTPUT} VERSION 0.0.0)
set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/program/include")
set(
  SYSTEM_INCLUDE_DIRS
  "${CMAKE_CURRENT_BINARY_DIR}/external/SDL2/include"
  "${CMAKE_CURRENT_BINARY_DIR}/external/SDL2/include-config-${CMAKE_BUILD_TYPE_LOWER}"
  "${CMAKE_CURRENT_BINARY_DIR}/external/SDL2/include-config-${CMAKE_BUILD_TYPE_LOWER}/SDL2"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/glm/include"
)
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/program/include/*.*")
file(
  GLOB SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/program/source/*.*"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/*.*"
)
source_group("Header Files" FILES "${HEADER_FILES}")
source_group("Source Files" FILES "${SOURCE_FILES}")
add_link_options("$<$<CONFIG:Release>:/INCREMENTAL:NO>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(FORCE_STATIC_VCRT ON)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory("external/SDL2")
add_subdirectory("external/SDL_mixer")
set(SDL2_LIBRARIES "SDL2::SDL2-static" "SDL2_mixer::SDL2_mixer-static")

add_subdirectory("external/ResourceGenerator")
set(RESOURCE_POSTFIXES "_shader_source" "_texture_data")
set(RESOURCE_HPP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/program/include/resource.hpp")
set(RESOURCE_CPP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/program/source/resource.cpp")
file(GLOB ASSET_FILES "asset/**/*.*")
source_group("Asset Files" FILES ${ASSET_FILES})
if(NOT "${RESOURCE_CPP_FILE}" IN_LIST SOURCE_FILES)
  list(APPEND SOURCE_FILES "${RESOURCE_CPP_FILE}")
endif()
add_custom_command(
  OUTPUT "${RESOURCE_HPP_FILE}"
  COMMAND ResourceGenerator ${RESOURCE_POSTFIXES} ${ASSET_FILES} "${RESOURCE_HPP_FILE}"
  DEPENDS "${ASSET_FILES}"
)
add_custom_command(
  OUTPUT "${RESOURCE_CPP_FILE}"
  COMMAND ResourceGenerator ${RESOURCE_POSTFIXES} ${ASSET_FILES} "${RESOURCE_CPP_FILE}"
  DEPENDS "${ASSET_FILES}"
)
add_custom_target("GenerateResources" DEPENDS "${RESOURCE_CPP_FILE}" "${RESOURCE_HPP_FILE}")

add_executable("${OUTPUT}")
target_include_directories("${OUTPUT}" PRIVATE "${INCLUDE_DIRS}")
target_include_directories("${OUTPUT}" SYSTEM PRIVATE "${SYSTEM_INCLUDE_DIRS}")
target_sources("${OUTPUT}" PRIVATE "${HEADER_FILES}" "${SOURCE_FILES}")
target_compile_options("${OUTPUT}" PRIVATE "/W4")
target_link_libraries("${OUTPUT}" PRIVATE "${SDL2_LIBRARIES}")
add_dependencies("${OUTPUT}" "GenerateResources")

if(NOT "${IS_SUBDIRECTORY}")
  set(FORMAT_MARKER_DIR "${CMAKE_CURRENT_BINARY_DIR}/FormatMarkers")
  set(FORMAT_MARKERS "")
  file(GLOB FORMAT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/program/**/*.*")
  list(REMOVE_ITEM FORMAT_FILES "${RESOURCE_HPP_FILE}" "${RESOURCE_CPP_FILE}")
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
  add_custom_target("Format" DEPENDS "${FORMAT_MARKERS}")
  add_dependencies("${OUTPUT}" "Format")

  set(COMPILE_COMMANDS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json")
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
endif()
