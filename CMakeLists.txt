cmake_minimum_required(VERSION 3.15)
project(SFML_Experiments)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config_upper)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_SOURCE_DIR}/bin)
endforeach()

set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SHD_DIR ${CMAKE_SOURCE_DIR}/shader)

include_directories(${INC_DIR})
link_directories(${LIB_DIR})

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${INC_DIR}/*.hpp" "${INC_DIR}/*.h")
file(GLOB_RECURSE SHADER "${SHD_DIR}/*.vert" "${SHD_DIR}/*.frag" "${SHD_DIR}/*.glsl")

source_group(TREE "${INC_DIR}" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${SRC_DIR}" PREFIX "Source Files" FILES ${SOURCES})
source_group(TREE "${SHD_DIR}" PREFIX "Shader Files" FILES ${SHADER})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${SHADER})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})