project(UnifiedJsonWrapperApp CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

#
# Create executable
#
add_executable(${PROJECT_NAME} ${SOURCES})

#
# Link libraries
#
target_link_libraries(${PROJECT_NAME} PRIVATE UnifiedJsonWrapperLib)
