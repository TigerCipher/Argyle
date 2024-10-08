﻿// ------------------------------------------------------------------------------
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
// File Name: Texture.h
// Date File Created: 08/18/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "Common.h"

namespace argyle::graphics
{
class texture
{
public:
    texture() { m_uuid = utl::uuid::generate_and_store(); }
    texture(std::string path) : m_path(std::move(path)) { m_uuid = utl::uuid::generate_and_store(); }
    ~texture();

    bool load(const std::string& path, bool flip = true);
    bool load(bool flip = true);
    void unload();

    void bind(u32 slot = 0) const;

    constexpr u32 id() const { return m_id; }
    constexpr i32 width() const { return m_width; }
    constexpr i32 height() const { return m_height; }

    static void activate_slot(u32 slot);

private:
    u32         m_id = invalid_id_u32;
    u32         m_uuid{};
    i32         m_width{};
    i32         m_height{};
    std::string m_path{};
};
} // namespace argyle::graphics
