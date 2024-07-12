cmake_minimum_required(VERSION 3.13)
project(component1  VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)





add_library( component1 ${LIBRARY_BUILD}
    source/component1.cpp
    include/components/component1/component1.hpp
)

add_library(component1::component1 ALIAS component1)

target_compile_options(component1 PUBLIC ${COMPILATION_FLAGS} -DSPDLOG_ACTIVE_LEVEL=${LOG_VERBOSITY})
target_link_libraries(component1 PUBLIC ${LINK_SANITIZER})
set_property(TARGET component1 PROPERTY INTERPROCEDURAL_OPTIMIZATION ${ENABLE_LINKER_LTO})

set_target_properties(component1 PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} )

#Set target properties
target_include_directories( component1
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    Component1ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Component1ConfigVersion.cmake.in
            Component1Config.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/components
)


install (TARGETS component1 EXPORT component1-targets 
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
         INCLUDES DESTINATION include/components/component1)

export(EXPORT component1-targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/Component1Targets.cmake"
  NAMESPACE Components::
)


install(EXPORT component1-targets
        FILE Component1Targets.cmake
        NAMESPACE 
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/components
)


install (DIRECTORY include/components 
         DESTINATION include)


install(FILES  ${CMAKE_CURRENT_BINARY_DIR}/Component1Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/Component1ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/components
)

if (${ENABLE_TEST})
add_subdirectory(test)
endif()
