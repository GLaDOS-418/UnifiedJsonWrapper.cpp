project(UnifiedJsonWrapperApp CXX)

set(APP_BIN_NAME ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

#
# create executable
#
add_executable(${APP_BIN_NAME} ${SOURCES})

#
# add third party dependencies
#
find_package(Boost REQUIRED COMPONENTS json)
find_package(nlohmann_json REQUIRED)

#
# link libraries
#
target_link_libraries(${APP_BIN_NAME} PRIVATE Boost::json
                                              nlohmann_json::nlohmann_json)
