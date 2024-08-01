// ------------------------------------------------------------------------------
//
// Argyle
//    Copyright 2024 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: GLInterface
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "GLInterface.h"

#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace
{
GLFWwindow * window;
} // anonymous namespace

bool initialize_glfw()
{
    if(!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    window = glfwCreateWindow(800, 600, "Argyle", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = true;

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    return true;
}

void shutdown_glfw()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void run()
{
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


void get_graphics_interface(argyle::graphics::graphics_interface& gfx_interface)
{
    gfx_interface.initialize = initialize_glfw;

    gfx_interface.shutdown = shutdown_glfw;

    gfx_interface.test_run = run;
}