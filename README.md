# Montaigne Engine

Montaigne Engine is a custom, low-level 3D sandbox engine written from scratch in modern C++20 and OpenGL. Built with a strict focus on memory safety, defensive coding protocols, and optimal pointer data constraints, this project contains no massive commercial engines or black-box wrappers—every transformation matrix, physical intersection check, and memory sweeper pass is manually written and compiled natively.

## 🛠️ The Ultimate Rescue Compilation Chain
If the runtime ever scrambles, matrix calculations collapse, or unexpected memory errors try to freeze your workspace, execute this exact unbroken production pipeline string directly inside your Linux shell terminal to force a clean cache swap, link the graphics binaries, and deploy the safe engine baseline:

```bash
export DISPLAY=:0 && g++ -std=c++20 -Wall -Wextra -Iinclude -c src/Engine.cpp -o src/Engine.o && g++ -std=c++20 -Wall -Wextra -Iinclude -c src/main.cpp -o src/main.o && g++ src/Engine.o src/main.o -o bin/montaigne -lGL -lglfw -lGLEW && ./bin/montaigne
```

---

## 🚀 Completed Milestones & Architectural Core

### 1. Modern Graphics Pipeline
- **Row-Major MVP Transformation Matrix Setup:** Independent custom implementation of `Mat4` systems supporting Row-Major loops for Translation, Scaling, and Rotation matrices, piping pure pointers seamlessly to the GPU structure handles.
- **Hardware-Accelerated Depth Buffer Buffering:** Strict core profile configurations (`OpenGL 3.3 Core Profile`) supporting accurate 3D visibility sorting.
- **Dynamic Face Normal Blending:** Custom lighting calculations matching ambient strength, specular values, and diffuse reflection maps mapped cleanly to relative camera space vectors.

### 2. Live Multi-Material Texture Asset Arrays
- **Automatic Fallback Loops:** High-integrity file input streams that look for custom target artwork (like `models/floor.png`). If an asset is missing from the directory partition, the `AssetLoader` safely overrides the missing pointer with a temporary, uniform backup color map instead of throwing a black screen crash.
- **Triangulation Engine Handler:** Custom `.obj` parser executing clean face vertex token parsing and quad-to-triangle parsing.

### 3. Kinematic Optimization & Physical Systems
- **Axis-Aligned Bounding Box (AABB) Math Engine:** High-performance collision checking calculations mapping intersection checks safely between dynamic coordinates.
- **Broad-Phase Spatial Partitioning Grid Cell Mapping:** Cuts down intersection workloads from heavy brute-force loops ($O(N^2)$ complexity) down to local constant cell checks ($O(N)$ efficiency) by partitioning entities inside independent 3D virtual coordinate sectors.
- **Dynamic Runtime Memory Garbage Collection Swapper:** Clean memory hygiene routines that monitor entity lifecycles. Spawned items that exist past their lifespans or slide into the underworld void are safely `.erase()` extracted out of the active tracking map arrays to prevent memory leaks and dangling pointers.

### 4. Interactive Target Deletion & Placement Loops
- **Spatial Grid Assisted Raycast Intersector:** Steps an invisible sampling point out along the camera look vector. Queries your active `spatialGrid` maps dynamically to run bounding box checks *only* inside the specific virtual room coordinates the ray physically passes through.
- **Real-time Raycast 3D Visual Debugger Trail Particles:** Captures the laser's coordinates in a frame vector array and draws a bright string of textured tracer dots across the camera sightline on click.
- **Structural Sandbox Voxel Block Placement Engine:** Uses advanced 3D axis delta analysis to pinpoint exactly which side of a box your crosshair is touching, instantly snapping a new structural block flush against that surface on right-click.

---

## 🎮 Game Engine Controls

- **`W` / `A` / `S` / `D`:** Smooth first-person camera-relative grid navigation.
- **`Spacebar`:** Upward vertical velocity jump impulse force.
- **`Mouse Look`:** Absolute high-sensitivity pitch/yaw rotation view vectors.
- **`E` Key:** Generate a falling skull block instance right ahead of your gaze.
- **`Left Mouse Button (LMB)`:** Fires an optimized raycast picker laser to blast custom blocks out of memory.
- **`Right Mouse Button (RMB)`:** Extrudes new voxel blocks perfectly flush against target faces.
- **`Escape`:** Graceful GLFW window closure pass.

---

## 🗺️ Chronological Order of Operations (OOO) Roadmap

- [x] Phase A: Shaders & Spatial Matrix Foundation Abstractions
- [x] Phase B: Modern First-Person Eye View Tracking Layouts
- [x] Phase C: Native Bounding Box (AABB) Intersection Physics & Gravity Hooks
- [x] Phase D: Multi-Material Dynamic Texture Asset Map Arrays
- [x] Phase E: Object-to-Object Physical Stacking Constraints
- [x] Phase F: Broad-Phase Spatial Partitioning Cell Mapping
- [x] Phase G: Dynamic Lifetime Sweeping & Underworld Garbage Collection
- [x] Phase H: Interactive Raycast Picking & Targeted Entity Deletion Loop
- [x] Phase I: Broad-Phase Spatial Partitioning Integration for the Raycaster
- [x] Phase J: Real-time Raycast 3D Visual Debugger Trail Particle Indicators
- [x] Phase K: Structural Sandbox Voxel Block Placement Engine

### 🌌 Advanced Expansion Stack (The Public Release Runway)
- [ ] **Phase L: Persistent Disk Serialization (World Saving/Loading via 'K' Key Input) [Next Operation]**
- [ ] Phase M: Creative Inventory Arrays & Voxel Material Texture Hotbar Selectors
- [ ] Phase N: Procedural Infinite Terrains via Mathematical Perlin Noise Generation Loops
- [ ] Phase O: Public Deployment Optimization (GitHub Release Module & Automated Binary Asset Packaging)

### 🚀 Engine Horizon Stack (Post-Release Core Upgrades)
- [ ] Phase P: Dynamic Voxel Ambient Occlusion (Smooth Vertex Corner Shading Math)
- [ ] Phase Q: Player-to-Voxel AABB Hard-Clipping Physics (Stopping Camera-through-Block clipping)
- [ ] Phase R: Dynamic Day/Night Lighting Cycle (Uniform Vector Sun Path Rotation Shaders)
- [ ] Phase S: Real-Time Diagnostic Engine Profiler (On-Screen FPS & Active Allocations Memory Tracker)

---

## 🔧 Build Requirements & Infrastructure

### Core Stack
- **Language Standard:** C++20
- **Graphics Framework:** OpenGL 3.3 Core Profile
- **Window Management Layer:** GLFW3
- **Extension Wrangler Pipeline:** GLEW
- **Asset Processing Utilities:** stb_image

### System Package Setup (Debian/Ubuntu Linux Partition)
```bash
sudo apt-get update
sudo apt-get install build-essential libglfw3-dev libglew-dev libgl1-mesa-dev
```
