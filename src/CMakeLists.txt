set(CMAKE_CXX_STANDARD 23)
if (NOT MSVC)
    message(FATAL_ERROR "The only supported compiler for the project is MSVC")
endif()

if (MSVC)
    add_compile_options(/W4 /fp:fast /experimental:module /wd4201)
    add_compile_definitions(VC_EXTRALEAN)
    add_link_options(/SUBSYSTEM:windows /ENTRY:mainCRTStartup)
    if(CMAKE_BUILD_TYPE EQUAL Release)
        add_compile_options(/MT /O2)
    endif()
    if(CMAKE_BUILD_TYPE EQUAL Debug)
        add_compile_options(/MTd /fsanitize=address)
    endif()
endif ()

#########################################
# OpenGL
#########################################
find_package(OpenGL REQUIRED)

#########################################
# cleanNES Executable Target Setup
#########################################
add_executable(cleanNES)
target_sources(cleanNES PRIVATE
        main.cpp
        renderer/Color.cpp
        renderer/Color.tpp
        renderer/OpenGL.cpp
        renderer/Renderer.cpp
        renderer/Scene.cpp
        renderer/Texture.cpp
        renderer/Win32OpenGLRenderingProcessor.cpp
        window/Win32Window.cpp)
message(STATUS "OpenGL Libraries: ${OPENGL_LIBRARIES}")
target_link_libraries(cleanNES PRIVATE spdlog::spdlog ${OPENGL_LIBRARIES})