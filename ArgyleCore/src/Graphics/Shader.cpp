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
// File Name: Shader
// Date File Created: 08/17/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Shader.h"

#include "Common.h"
#include "GLCore.h"

#include <fstream>
#include <sstream>
#include <gl/glew.h>

namespace argyle::graphics
{

namespace
{
std::string read_file(const std::string& file)
{
    LOG_DEBUG("Reading shader file: {}", file);
    std::string   source{};
    std::ifstream stream;
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        stream.open(file);
        std::stringstream buffer;
        buffer << stream.rdbuf();
        stream.close();
        source = buffer.str();
    } catch (std::ifstream::failure& e)
    {
        LOG_ERROR("Failed to read shader file [{}]: {}", file, e.what());
        return {};
    }
    return source;
}

bool check_error(u32 id, const std::string& type)
{
    i32  success;
    char info_log[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, nullptr, info_log);
            LOG_ERROR("Shader compilation error: {}", info_log);
            return true;
        }
    } else
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, nullptr, info_log);
            LOG_ERROR("Shader linking error: {}", info_log);
            return true;
        }
    }

    return false;
}

GLenum get_basic_type(u32 type)
{
    switch (type)
    {
    case GL_FLOAT_VEC2:
    case GL_FLOAT_VEC3:
    case GL_FLOAT_VEC4:
    case GL_FLOAT: return GL_FLOAT;
    case GL_INT_VEC2:
    case GL_INT_VEC3:
    case GL_INT_VEC4:
    case GL_INT: return GL_INT;
    case GL_UNSIGNED_INT_VEC2:
    case GL_UNSIGNED_INT_VEC3:
    case GL_UNSIGNED_INT_VEC4:
    case GL_UNSIGNED_INT: return GL_UNSIGNED_INT;
    case GL_BYTE: return GL_BYTE;
    case GL_UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
    case GL_SHORT: return GL_SHORT;
    case GL_UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
    default: return GL_FLOAT;
    }
}

i32 get_attribute_size(u32 type)
{
    switch (type)
    {
    case GL_FLOAT_VEC2:
    case GL_INT_VEC2:
    case GL_UNSIGNED_INT_VEC2: return 2;
    case GL_FLOAT_VEC3:
    case GL_INT_VEC3:
    case GL_UNSIGNED_INT_VEC3: return 3;
    case GL_FLOAT_VEC4:
    case GL_INT_VEC4:
    case GL_UNSIGNED_INT_VEC4: return 4;
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT: return 1;
    default: return 1;
    }
}

i32 get_stride(u32 type)
{
    switch (type)
    {
    case GL_FLOAT_VEC2: return 2 * sizeof(f32);
    case GL_FLOAT_VEC3: return 3 * sizeof(f32);
    case GL_FLOAT_VEC4: return 4 * sizeof(f32);
    case GL_FLOAT: return sizeof(f32);
    case GL_INT_VEC2: return 2 * sizeof(i32);
    case GL_INT_VEC3: return 3 * sizeof(i32);
    case GL_INT_VEC4: return 4 * sizeof(i32);
    case GL_INT: return sizeof(i32);
    case GL_UNSIGNED_INT_VEC2: return 2 * sizeof(u32);
    case GL_UNSIGNED_INT_VEC3: return 3 * sizeof(u32);
    case GL_UNSIGNED_INT_VEC4: return 4 * sizeof(u32);
    case GL_UNSIGNED_INT: return sizeof(u32);
    case GL_BYTE: return sizeof(i8);
    case GL_UNSIGNED_BYTE: return sizeof(u8);
    case GL_SHORT: return sizeof(i16);
    case GL_UNSIGNED_SHORT: return sizeof(u16);
    default: return 0;
    }
}
} // anonymous namespace

u32 shader::s_bound_shader = 0;

shader::~shader()
{
    if (m_id != invalid_id_u32)
    {
        glDeleteProgram(m_id);
    }
}

bool shader::load()
{
    std::string vertex_file   = utl::uuid::get_name(m_uuid) + ".vs";
    std::string frag_file     = utl::uuid::get_name(m_uuid) + ".fs";
    std::string vertex_source = read_file(vertex_file);
    std::string frag_source   = read_file(frag_file);
    if (vertex_source.empty() || frag_source.empty())
    {
        return false;
    }

    m_sources[GL_VERTEX_SHADER]   = vertex_source;
    m_sources[GL_FRAGMENT_SHADER] = frag_source;
    if (!compile())
    {
        return false;
    }

    LOG_INFO("Shader loaded: {}", utl::uuid::get_name(m_uuid));
    return true;
}

bool shader::set_source(const std::string& vertex, const std::string& fragment)
{
    m_sources[GL_VERTEX_SHADER]   = vertex;
    m_sources[GL_FRAGMENT_SHADER] = fragment;
    return compile();
}

void shader::use()
{
    if (s_bound_shader == m_id)
    {
        return;
    }
    GL_CALL(glUseProgram(m_id));
    s_bound_shader = m_id;
}

void shader::unuse()
{
    s_bound_shader = 0;
    GL_CALL(glUseProgram(0));
}

void shader::destroy()
{
    glDeleteProgram(m_id);
    m_id = invalid_id_u32;
}

void shader::set_bool(const char* name, bool value) const
{
    glUniform1i(m_uniforms.at(name), (i32) value);
}

void shader::set_int(const char* name, i32 value) const
{
    glUniform1i(m_uniforms.at(name), value);
}

void shader::set_float(const char* name, f32 value) const
{
    glUniform1f(m_uniforms.at(name), value);
}

void shader::set_vec2(const char* name, const glm::vec2& value) const
{
    glUniform2fv(m_uniforms.at(name), 1, &value[0]);
}

void shader::set_vec2(const char* name, f32 x, f32 y) const
{
    glUniform2f(m_uniforms.at(name), x, y);
}

void shader::set_vec3(const char* name, const glm::vec3& value) const
{
    glUniform3fv(m_uniforms.at(name), 1, &value[0]);
}

void shader::set_vec3(const char* name, f32 x, f32 y, f32 z) const
{
    glUniform3f(m_uniforms.at(name), x, y, z);
}

void shader::set_vec4(const char* name, const glm::vec4& value) const
{
    glUniform4fv(m_uniforms.at(name), 1, &value[0]);
}

void shader::set_vec4(const char* name, f32 x, f32 y, f32 z, f32 w) const
{
    glUniform4f(m_uniforms.at(name), x, y, z, w);
}

void shader::set_mat2(const char* name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(m_uniforms.at(name), 1, GL_FALSE, &mat[0][0]);
}

void shader::set_mat3(const char* name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(m_uniforms.at(name), 1, GL_FALSE, &mat[0][0]);
}

void shader::set_mat4(const char* name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(m_uniforms.at(name), 1, GL_FALSE, &mat[0][0]);
}

void shader::bind_attribute(const std::string& name, const void* pointer, bool normalized) const
{
    if (!m_attributes.contains(name))
    {
        LOG_WARN("Attribute {} not found in shader [{}]", name, m_uuid);
        return;
    }
    const auto& [location, count, type, normalized_] = m_attributes.at(name);
    if (location == -1)
    {
        LOG_WARN("Attribute {} not found in shader [{}]", name, m_uuid);
        return;
    }
    glVertexAttribPointer(location, count, type, normalized, m_total_stride, pointer);
    glEnableVertexAttribArray(location);
}

bool shader::compile()
{
    LOG_DEBUG("[{}] Compiling shader: {}", m_uuid, utl::uuid::get_name(m_uuid));
    const char* vsrc = m_sources[GL_VERTEX_SHADER].c_str();
    const char* fsrc = m_sources[GL_FRAGMENT_SHADER].c_str();

    LOG_DEBUG("[{}] Compiling vertex shader", m_uuid);
    // Compile vertex shader
    u32 vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vsrc, nullptr);
    GL_CALL(glCompileShader(vertex));
    if (check_error(vertex, "VERTEX"))
    {
        glDeleteShader(vertex);
        return false;
    }

    LOG_DEBUG("[{}] Compiling fragment shader", m_uuid);
    // Compile fragment shader
    u32 fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fsrc, nullptr);
    GL_CALL(glCompileShader(fragment));
    if (check_error(fragment, "FRAGMENT"))
    {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }

    LOG_DEBUG("[{}] Linking shaders", m_uuid);
    // Link shaders
    m_id = glCreateProgram();
    GL_CALL(glAttachShader(m_id, vertex));
    GL_CALL(glAttachShader(m_id, fragment));
    GL_CALL(glLinkProgram(m_id));
    if (check_error(m_id, "PROGRAM"))
    {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }

    // Cache uniform and attribute names/locations
    i32 count, max_name_length;
    // Uniforms
    glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length);
    glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &count);
    for (i32 i = 0; i < count; ++i)
    {
        std::vector<char> name(max_name_length);
        i32               size;
        u32               type;
        glGetActiveUniform(m_id, i, max_name_length, nullptr, &size, &type, name.data());
        m_uniforms[name.data()] = glGetUniformLocation(m_id, name.data());
        LOG_DEBUG("[{}] Uniform: {} - Location: {}", m_uuid, name.data(), m_uniforms[name.data()]);
    }
    // Attributes
    glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_name_length);
    glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTES, &count);
    for (i32 i = 0; i < count; ++i)
    {
        std::vector<char> name(max_name_length);
        i32               size;
        u32               type;
        glGetActiveAttrib(m_id, i, max_name_length, nullptr, &size, &type, name.data());
        m_attributes[name.data()] = { glGetAttribLocation(m_id, name.data()), get_attribute_size(type), get_basic_type(type) };
        m_total_stride += get_stride(type);
        LOG_DEBUG("[{}] Attribute: {} - Location: {}", m_uuid, name.data(), m_attributes[name.data()].location);
    }

    // Clean up
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    LOG_INFO("[{}] Shader compiled successfully - stored as program {}", m_uuid, m_id);
    return true;
}

}