cmake_minimum_required(VERSION 3.13)
project(component2  VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library( component2 ${LIBRARY_BUILD}
    source/component2.cpp
    include/components/component2/component2.hpp
)

add_library(component2::component2 ALIAS component2)

if (NOT(TARGET component2::component2))
        find_package(Component1 REQUIRED)
endif()


target_compile_options(component2 PUBLIC ${COMPILATION_FLAGS} -DSPDLOG_ACTIVE_LEVEL=${LOG_VERBOSITY})
target_link_libraries(component2 PUBLIC component1::component1)
target_link_libraries(component2 PUBLIC ${LINK_SANITIZER})
set_property(TARGET component2 PROPERTY INTERPROCEDURAL_OPTIMIZATION ${ENABLE_LINKER_LTO})

set_target_properties(component2 PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} )

#Set target properties
target_include_directories( component2
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    Component2ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Component2ConfigVersion.cmake.in
            Component2Config.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/components
)


install (TARGETS component2 EXPORT component2-targets 
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
         INCLUDES DESTINATION include/components/component2)

export(EXPORT component2-targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/Component2Targets.cmake"
  NAMESPACE Components::
)


install(EXPORT component2-targets
        FILE Component2Targets.cmake
        NAMESPACE 
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/components
)


install (DIRECTORY include/components 
         DESTINATION include)


install(FILES  ${CMAKE_CURRENT_BINARY_DIR}/Component2Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/Component2ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/components
)

if (${ENABLE_TEST})
add_subdirectory(test)
endif()
