# Montaigne Engine

A custom-built 3D graphics engine written in C++ with OpenGL. This project tracks the journey of building a 3D renderer from the ground up, moving from 2D primitives to a full 3D pipeline capable of rendering and navigating 3D meshes.

## Features
- **3D Pipeline:** Full Model-View-Projection (MVP) matrix integration.
- **Dynamic Navigation:** Fly-through 3D camera system using WASD.
- **Mesh Loading:** Custom OBJ file parser capable of loading vertex and face data.
- **Depth Testing:** Hardware-accelerated depth buffering for accurate 3D visibility.
- **Modular Architecture:** Clean separation of math, input, assets, and rendering logic.

## Roadmap
- [x] Foundation & Shader Abstraction
- [x] Spatial Math & 3D Matrices
- [x] First-Person Camera Navigation
- [x] OBJ Asset Loading
- [ ] Lighting & PBR (Physically Based Rendering)
- [ ] Optimization (Frustum culling, etc.)

## Getting Started
1. Ensure you have `GLEW` and `GLFW` installed.
2. Compile the engine using the provided Makefile.
3. Run the executable from the project root.

## Built With
- C++11
- OpenGL 3.3
- GLFW
- GLEW

## Build Requirements
- C++20 Compiler
- GLFW, GLEW, stb_image

# MontaigneEngine
A lightweight 3D game engine built in C++.

## Features
- **Physics-enabled:** Cube spawning with gravity and floor collision.
- **Interactive Camera:** Flythrough mode with mouse-look and zoom.
- **Rendering:** Texture-mapped 3D models with depth testing.

## Building
1. Install `libglfw3-dev` and `libglew-dev`.
2. Clone the repo: `git clone <url>`
3. Run `make` in the root directory.
4. Run the executable: `./bin/montaigne`

## Controls
- **W/A/S/D:** Fly through the scene.
- **Space:** Spawn a new cube.
- **Mouse:** Rotate camera.
- **Scroll:** Zoom FOV.
