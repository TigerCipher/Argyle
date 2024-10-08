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
// File Name: Main
// Date File Created: 07/31/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Argyle.h"
#include "Graphics/Window.h"

#pragma comment(lib, "ArgyleCore.lib")

using namespace argyle;

enum textures : u16
{
    TEXTURE_TEST = 0
};

void init()
{
    assets::g_textures.load_texture(TEXTURE_TEST, "./assets/textures/face.png");

    assets::g_textures[TEXTURE_TEST]->bind();
}

int main(int argc, char* argv[])
{
    if (core::init("Sandbox", 800, 600))
    {
        init();
        core::run();
        core::shutdown();
        return 0;
    }
    return -1;
}
