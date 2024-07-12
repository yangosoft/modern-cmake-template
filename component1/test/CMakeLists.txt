include(CTest)
include(Catch)


add_executable(testcomponent1 testcomponent1.cpp)

target_include_directories( testcomponent1
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../source>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

target_link_libraries(testcomponent1 PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(testcomponent1)

