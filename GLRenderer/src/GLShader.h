// ------------------------------------------------------------------------------
//
// Argyle
// Copyright 2024 Matthew Rogers
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// File Name: GLShader.h
// Date File Created: 08/03/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "Graphics/Shader.h"

namespace argyle::gl
{

struct vertex_attribute
{
    i32  location   = -1;
    i32  count      = -1;
    u32  type       = invalid_id_u32;
    bool normalized = false;
};

class shader : public graphics::shader
{
public:
    shader(const std::string& name) : graphics::shader(name) {}
    ~shader() override;

    // Loads the shader from vertex and fragment files based on the name. I.e name.vert and name.frag
    bool load();
    // Sets the sources of the shader. Do not use with load()
    bool set_source(const std::string& vertex, const std::string& fragment);

    void use() override;
    void unuse() override;

    void destroy() override;

    void set_bool(const char* name, bool value) const override;
    void set_int(const char* name, i32 value) const override;
    void set_float(const char* name, f32 value) const override;

    void set_vec2(const char* name, const glm::vec2& value) const override;
    void set_vec2(const char* name, f32 x, f32 y) const override;

    void set_vec3(const char* name, const glm::vec3& value) const override;
    void set_vec3(const char* name, f32 x, f32 y, f32 z) const override;

    void set_vec4(const char* name, const glm::vec4& value) const override;
    void set_vec4(const char* name, f32 x, f32 y, f32 z, f32 w) const override;

    void set_mat2(const char* name, const glm::mat2& mat) const override;
    void set_mat3(const char* name, const glm::mat3& mat) const override;
    void set_mat4(const char* name, const glm::mat4& mat) const override;

    void bind_attribute(const std::string& name, const void* pointer, bool normalized = false) const;

protected:
    bool compile() override;

private:
    u32 m_id{};
    i32 m_total_stride{};

    std::unordered_map<std::string, vertex_attribute> m_attributes{};
    std::unordered_map<u32, std::string>              m_sources{};

    static u32 s_bound_shader;
};

} // namespace argyle::gl