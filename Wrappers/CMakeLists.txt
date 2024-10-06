project(UnifiedJsonWrapperLib CXX)

#
# Add target sources
#
set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Src/NlohmannJsonWrapper.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

#
# Target properties
#
set(CMAKE_POSITION_INDEPENDENT_CODE True)

#
# Include directories
#
target_include_directories(${PROJECT_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Includes")

#
# add third party dependencies
#
find_package(Boost REQUIRED COMPONENTS json)
find_package(nlohmann_json REQUIRED)

#
# link libraries
#
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::json
                                              nlohmann_json::nlohmann_json)
