cmake_minimum_required(VERSION 3.13)
project(component2  VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(component3 source/component3.cpp
)

if (NOT(TARGET component2::component2))
        find_package(Component1 REQUIRED)
        find_package(Component2 REQUIRED)
endif()


target_compile_options(component3 PUBLIC ${COMPILATION_FLAGS} -DSPDLOG_ACTIVE_LEVEL=${LOG_VERBOSITY})
target_link_libraries(component3 PUBLIC component2)
target_link_libraries(component3 PUBLIC ${LINK_SANITIZER})




#Set target properties
target_include_directories(component3
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)

install(TARGETS component3 DESTINATION bin)