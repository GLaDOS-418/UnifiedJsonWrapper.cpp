project(UnifiedJsonWrapperLibTests CXX)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TestJsonWrapper.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE UnifiedJsonWrapperLib gtest::gtest
                          nlohmann_json::nlohmann_json)

# target_include_directories(${PROJECT_NAME} SYSTEM
#                            PRIVATE ${gtest_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
