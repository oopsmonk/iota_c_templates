cmake_minimum_required(VERSION 3.11)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(my_app DESCRIPTION "My IOTA Client")

# for embear_logger
add_definitions(-DLOGGER_ENABLE)

enable_language(C)
enable_testing()

# fetch iota.c
include(FetchContent)
FetchContent_Declare(
  iota.c
  GIT_REPOSITORY http://github.com/iotaledger/iota.c.git
  GIT_TAG e260967bd3a9088fa03d20c1517930e23f1de591
)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
    macro(FetchContent_MakeAvailable NAME)
        FetchContent_GetProperties(${NAME})
        if(NOT ${NAME}_POPULATED)
            FetchContent_Populate(${NAME})
            add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
        endif()
    endmacro()
endif()

message(STATUS "Fetching iota.c")
FetchContent_MakeAvailable(iota.c)

# fetch external libs
include(ExternalProject)

# libs in the sandbox
link_directories("${CMAKE_INSTALL_PREFIX}/lib")

# your source files
add_executable(my_app "my_app.c")

target_include_directories(my_app PRIVATE
  "${PROJECT_SOURCE_DIR}"
  "${CMAKE_INSTALL_PREFIX}/include"
  "${CMAKE_INSTALL_PREFIX}/include/cjson"
  "${iota.c_SOURCE_DIR}"
)

target_link_libraries(my_app PUBLIC
  cclient
  cjson
  http_parser
  common
  logger
  keccak
  mbedtls
  mbedcrypto
  mbedx509
)

if(WIN32)
target_link_libraries(my_app PUBLIC
  ws2_32
  ssp
)
endif(WIN32)
