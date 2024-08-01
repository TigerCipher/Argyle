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
// File Name: Argyle
// Date File Created: 07/31/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Argyle.h"

#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

void argyle::core::test_glfw()
{
    std::cout << "Initializing GLFW...\n";
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }
    std::cout << "GLFW initialized\n";

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, World!", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << '\n';
        // print error
        std::cout << glewGetErrorString(glewInit()) << '\n';
        return;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
