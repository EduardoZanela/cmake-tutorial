cmake_minimum_required(VERSION 3.20)

project(cmake-tutorial)

include(CTest)
include(FetchContent)
find_package(Git REQUIRED)

set(SCADACOM_LIBRARY_VERSION "729559d5c0e8595d67980a4c188583262185345e" CACHE STRING "Scadacom library version")
set(DEVELOPMENT_SC_LIBS "/sq/scadacom-libraries")
set(BUILD_TESTING OFF)

if(BUILD_TESTING)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

    option(
        INSTALL_GTEST
        "Enable installation of googletest."
        OFF)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

endif()


#set(CMAKE_FIND_ROOT_PATH "/sq/scadacom-libraries/build")
#find_package(sc-libs REQUIRED error_logger)
#set(FETCHCONTENT_FULLY_DISCONNECTED ON)
# FetchContent_GetProperties(sc-libs)
# if (NOT sc-libs_POPULATED)
#     message("not populated")
#     FetchContent_Populate(sc-libs)
#     add_subdirectory(${sc-libs_SOURCE_DIR} ${sc-libs_BINARY_DIR})
# endif()


if(EXISTS "${DEVELOPMENT_SC_LIBS}/CMakeLists.txt")
    message("Using local version") 
    FetchContent_Declare(
        sc-libs
        SOURCE_DIR "${DEVELOPMENT_SC_LIBS}"
    )
    execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
                WORKING_DIRECTORY "${DEVELOPMENT_SC_LIBS}"
                OUTPUT_VARIABLE PACKAGE_GIT_VERSION
                ERROR_QUIET
                OUTPUT_STRIP_TRAILING_WHITESPACE)
    message("Git version ${PACKAGE_GIT_VERSION}")
else()
    FetchContent_Declare(
        sc-libs
        GIT_REPOSITORY "https://git.willowglen.ca/sq/sq-scadacom/scadacom-libraries"
        GIT_TAG "${SCADACOM_LIBRARY_VERSION}"
    )
endif()

FetchContent_MakeAvailable(sc-libs)

add_executable(eduardo src/main.cpp)

target_include_directories(eduardo PUBLIC include)
target_link_libraries(eduardo error_logger)