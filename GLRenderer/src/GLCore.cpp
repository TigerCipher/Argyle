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
// File Name: GLCore
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "GLCore.h"
#include "Common.h"
#include "GLShader.h"


#include <gl/glew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "ArgyleCore.lib")

namespace argyle::gl
{

namespace
{
window::window_desc* win_desc = nullptr;
shader* test_shader;

// Simple test shader
const char* vertex_shader_source = R"(
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 outColor;

void main()
{
    outColor = aColor;
    gl_Position = vec4(aPos, 1.0);
}

)";

const char* fragment_shader_source = R"(
#version 460 core

out vec4 FragColor;

in vec3 outColor;

void main()
{
    FragColor = vec4(outColor, 1.0);
}

)";

u32 VAO, VBO;

struct vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

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

    test_shader = new shader("test_shader");

    if(!test_shader->set_source(vertex_shader_source, fragment_shader_source))
    {
        LOG_FATAL("Failed to set shader source");
        return false;
    }

    // create vao and vbo with simple triangle
    vertex vertices[] = {
        { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
    };

    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glGenBuffers(1, &VBO));
    GL_CALL(glBindVertexArray(VAO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(vertex), vertices, GL_STATIC_DRAW));
    test_shader->bind_attribute("aPos", (void*)offsetof(vertex, position));
    test_shader->bind_attribute("aColor", (void*)offsetof(vertex, color));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindVertexArray(0));

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
    delete test_shader;
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

void render()
{
    test_shader->use();
    GL_CALL(glBindVertexArray(VAO));
    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CALL(glBindVertexArray(0));
    test_shader->unuse();
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