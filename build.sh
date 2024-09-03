#!/bin/bash

g++ main.cpp glad.c game.cpp cube.cpp plane.cpp shader.cpp camera.cpp baseTerrain.cpp \
    faultFormation.cpp triangle_list.cpp imgui/imgui.cpp imgui/imgui_demo.cpp \
    imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp \
    backends/imgui_impl_glfw.cpp backends/imgui_impl_opengl3.cpp \
    -lm -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 \
    -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor \
    -Iimgui/ -Ibackends/ -DIMGUI_IMPL_OPENGL_LOADER_GLAD
