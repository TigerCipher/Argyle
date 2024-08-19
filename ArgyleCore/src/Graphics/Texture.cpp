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
// File Name: Texture.h
// Date File Created: 08/18/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Texture.h"

#define INCLUDE_GL
#include "GLCore.h"
#include <SOIL2/SOIL2.h>

namespace argyle::graphics
{

texture::~texture()
{
    unload();
}

bool texture::load(const std::string& path, bool flip)
{
    m_path       = path;
    i32 channels = 0;
    u8* data     = SOIL_load_image(path.c_str(), &m_width, &m_height, &channels, SOIL_LOAD_RGBA);
    if (!data)
    {
        LOG_ERROR("[{}] Failed to load texture: {}", m_uuid, path);
        return false;
    }

    // Flip texture vertically if requested (by default because SOIL loads them upside down)
    if (flip)
    {
        for (i32 y = 0; y < m_height / 2; ++y)
        {
            for (i32 x = 0; x < m_width * channels; ++x)
            {
                const u8 temp                                     = data[y * m_width * channels + x];
                data[y * m_width * channels + x]                  = data[(m_height - y - 1) * m_width * channels + x];
                data[(m_height - y - 1) * m_width * channels + x] = temp;
            }
        }
    }

    i32 format = GL_RGB;
    if (channels == 4)
    {
        format = GL_RGBA;
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(data);
    LOG_INFO("[{}] Loaded texture: {}", m_uuid, path);
    return true;
}

bool texture::load(bool flip)
{
    return load(m_path, flip);
}

void texture::unload()
{
    if (m_id != invalid_id_u32)
    {
        LOG_DEBUG("[{}] Unloading texture {}", m_uuid, m_path);
        GL_CALL(glDeleteTextures(1, &m_id));
        m_id = invalid_id_u32;
    }
}

void texture::bind(u32 slot) const
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id));
}

void texture::activate_slot(u32 slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
}

} // namespace argyle::graphics