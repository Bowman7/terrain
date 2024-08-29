#!/bin/bash

g++ main.cpp glad.c game.cpp cube.cpp plane.cpp shader.cpp camera.cpp baseTerrain.cpp faultFormation.cpp triangle_list.cpp -lm -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
