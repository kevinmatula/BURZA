# BURZA

**A 3D game engine written in C++, built for low-polygon sprites and environments.**

---

## Overview

BURZA is a lightweight, retro-inspired 3D engine designed around the constraints and aesthetics of PS1-era rendering: low-poly geometry, sprite-driven scenes, and a rendering pipeline tuned for a gritty, posterized look.

---

## Stack & Concepts

| Category | Details |
|---|---|
| **Language / API** | C++, OpenGL 3.3 (Core Profile), SDL3 |
| **Build System** | CMake (primary), with a touch of Makefile |
| **Libraries** | [Glad](https://glad.dav1d.de/) (v1), [GLM](https://github.com/g-truc/glm), [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) |
| **Techniques** | Posterization, RAII, ECS, OOP |

---

## References

- [docs.gl](https://docs.gl/)
- [Khronos OpenGL Wiki](https://www.khronos.org/opengl/wiki/)
- *Fix Your Timestep!* — Glenn Fiedler
- [Rendering a PS1-Style Scene](https://www.hawkjames.com/indiedev/update/2022/06/02/rendering-ps1.html) — hawkjames.com
- [dustmite](https://www.youtube.com/@dustmite-c) — YouTube (C programming)
