#!/bin/bash

# OpenGL Cube Project - Compilation Script for macOS

echo "Compiling OpenGL Cube Project..."

clang++ \
    -std=c++11 \
    -I./dependencies/include \
    -L./dependencies/library \
    main.cpp \
    Texture.cpp \
    VAO.cpp \
    VBO.cpp \
    EBO.cpp \
    shaderclass.cpp \
    stb.cpp \
    glad.c \
    -lglfw.3.4 \
    -framework OpenGL \
    -framework Cocoa \
    -framework IOKit \
    -framework CoreVideo \
    -o cube_app

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "Run with: ./cube_app"
else
    echo "✗ Compilation failed!"
    exit 1
fi
