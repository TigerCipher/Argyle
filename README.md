# Argyle Engine
---
Argyle Engine is a game engine written in C++ and OpenGL. It is designed to be a simple and easy to use engine for creating 2D games. The engine is still in development and is not yet ready for use.

Currently, the focus is on Windows, however Linux may be supported in the future. There are no plans at the moment to support other rendering APIs such as DirectX or MacOS.

---

This project uses VCPKG. Building in visual studio with the supplied project files will install the needed dependencies. But first you must ensure that you have VCPKG installed and that the VCPKG_ROOT environment variable is set to the root directory of VCPKG.

To add a new dependency, use the following command within the project it will be used for.
```
vcpkg add port <dependency name>
```
Example:
```
Microsoft Windows [Version 10.0.22631.3958]
(c) Microsoft Corporation. All rights reserved.

D:\Argyle\ArgyleCore>vcpkg add port glfw3
Succeeded in adding ports to vcpkg.json file.
```

To create the vcpkg manifest file for new projects if needed, run the following command in the project directory.
```
vcpkg new --application
```