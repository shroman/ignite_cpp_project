cmake_minimum_required (VERSION 3.3)
project(Records)

set(RECORDS_VERSION_MAJOR 1)
set(RECORDS_VERSION_MINOR 0)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/push.cpp ${PROJECT_SOURCE_DIR}/src/push-server.cpp)

#set(CMAKE_CXX_COMPILER g++-6)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(/usr/lib/jvm/java-8-oracle/include/)
include_directories(/usr/lib/jvm/java-8-oracle/include/linux/)
include_directories(/usr/local/include/)
#include_directories(/usr/local/include/ignite/)
#include_directories($ENV{IGNITE_HOME}/platforms/cpp/common/include/ignite/)
include_directories($ENV{IGNITE_HOME}/platforms/cpp/common/os/linux/include/)
include_directories($ENV{IGNITE_HOME}/platforms/cpp/jni/include/)
include_directories($ENV{IGNITE_HOME}/platforms/cpp/core/include/)

#add_library(Records STATIC ${SOURCES})

#find_library(LIB_IGNITE NAMES libignite)
#find_library(LIB_IGNITE_JNI NAMES libignite-jni)

#add_executable(records ${PROJECT_SOURCE_DIR}/src/push.cpp)
#add_executable(records ${PROJECT_SOURCE_DIR}/src/push-server.cpp)

#library search directories
link_directories(/usr/local/lib)
link_directories(/usr/lib/jvm/java-8-oracle/jre/lib/amd64/server)

foreach(appsrc ${SOURCES})
    # message("--- " ${appsrc})
    string(REPLACE ".cpp" "" apps ${appsrc})
    string(REPLACE "${PROJECT_SOURCE_DIR}/src/" "" app ${apps})
    message("--- " ${app})

    add_executable(${app} ${appsrc})
    target_link_libraries(${app} -lrt -ldl -lm -lpthread -rdynamic)
    target_link_libraries(${app} "/usr/lib/jvm/java-8-oracle/jre/lib/amd64/server/libjvm.so")
    target_link_libraries(${app} "/usr/local/lib/libignite.so")
    target_link_libraries(${app} "/usr/local/lib/libignite-common.so")
    target_link_libraries(${app} "/usr/local/lib/libignite-jni.so")
    target_link_libraries(${app} "/usr/local/lib/libignite-binary.so")
endforeach()

#enable_testing()

#add_subdirectory(test)
