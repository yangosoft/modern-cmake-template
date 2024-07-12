include(CTest)
include(Catch)


add_executable(testcomponent2 testcomponent2.cpp)

target_include_directories( testcomponent2
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../source>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

target_link_libraries(testcomponent2 PRIVATE component1::component1 Catch2::Catch2WithMain)
catch_discover_tests(testcomponent2)

