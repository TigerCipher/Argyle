﻿// ------------------------------------------------------------------------------
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
// File Name: GLCore
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "GLCore.h"
#include "Common.h"


#include <gl/glew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "ArgyleCore.lib")

namespace argyle::gl
{

namespace
{
window::window_desc* win_desc = nullptr;
} // anonymous namespace

namespace core
{

bool init(window::window_desc* desc)
{
    if (win_desc)
    {
        LOG_WARN("OpenGL renderer already initialized");
        return false;
    }
    win_desc = desc;
    if (!win_desc)
    {
        LOG_FATAL("Window description not set");
        return false;
    }
    LOG_INFO("Initializing OpenGL renderer");

    if (!glfwInit())
    {
        LOG_FATAL("Failed to initialize glfw");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow((i32) desc->width, (i32) desc->height, desc->title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        LOG_FATAL("Failed to create window");
        return false;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        LOG_FATAL("Failed to initialize glew");
        return false;
    }

    desc->handle = window;

    // Log OpenGL and device information
    LOG_INFO("GLFW Version: {}", glfwGetVersionString());
    LOG_INFO("OpenGL Version: {}", (char*) glGetString(GL_VERSION));
    LOG_INFO("OpenGL Vendor: {}", (char*) glGetString(GL_VENDOR));
    LOG_INFO("OpenGL Renderer: {}", (char*) glGetString(GL_RENDERER));
    LOG_INFO("GLSL Version: {}", (char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

    LOG_INFO("OpenGL renderer Initialized");
    return true;
}

void shutdown()
{
    if (!win_desc->handle)
    {
        LOG_WARN("OpenGL renderer not initialized, no need to shutdown");
        return;
    }
    LOG_INFO("Shutting down OpenGL renderer");
    glfwDestroyWindow((GLFWwindow*) win_desc->handle);
    glfwTerminate();
    LOG_INFO("OpenGL renderer shutdown");
}

void update_window()
{
    if (!win_desc->handle)
    {
        LOG_ERROR("OpenGL renderer not initialized, cannot update window");
        return;
    }
    glfwSwapBuffers((GLFWwindow*) win_desc->handle);
    glfwPollEvents();
}

bool is_window_open()
{
    return !glfwWindowShouldClose((GLFWwindow*) win_desc->handle);
}

window::window_desc* get_window_desc()
{
    return win_desc;
}

} // namespace core

void clear_color(const f32 r, const f32 g, const f32 b, const f32 a /* = 1.0f */)
{
    ARGYLE_ASSERT(r >= 0.0f && r <= 1.0f, "red must be between 0 and 1");
    ARGYLE_ASSERT(g >= 0.0f && g <= 1.0f, "green must be between 0 and 1");
    ARGYLE_ASSERT(b >= 0.0f && b <= 1.0f, "blue must be between 0 and 1");
    ARGYLE_ASSERT(a >= 0.0f && a <= 1.0f, "alpha must be between 0 and 1");
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}


} // namespace argyle::gl