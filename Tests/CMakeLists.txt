project(UnifiedJsonWrapperLibTests CXX)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TestJsonWrapper.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(GTest REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE UnifiedJsonWrapperLib
                                              gtest::gtest)

target_include_directories(${PROJECT_NAME} SYSTEM
                           PRIVATE ${gtest_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
