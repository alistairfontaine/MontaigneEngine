# Montaigne Engine

Montaigne Engine is a custom, low-level 3D sandbox engine written from scratch in modern C++20 and OpenGL. Built with a strict focus on memory safety, defensive coding protocols, and optimal pointer data constraints, this project contains no massive commercial engines or black-box wrappers—every transformation matrix, physical intersection check, and memory sweeper pass is manually written and compiled natively.

## 🛠️ The Ultimate Rescue Compilation Chain
If the runtime ever scrambles, matrix calculations collapse, or unexpected memory errors try to freeze your workspace, execute this exact unbroken production pipeline string directly inside your Linux shell terminal to force a clean cache swap, link the graphics binaries, and deploy the safe engine baseline:

```bash
g++ -std=c++20 -Wall -Wextra -Iinclude -c src/Engine.cpp -o src/Engine.o && g++ -std=c++20 -Wall -Wextra -Iinclude -c src/main.cpp -o src/main.o && g++ src/Engine.o src/main.o -o bin/montaigne -lGL -lglfw -lGLEW && ./bin/montaigne
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

### 4. Interactive Target Deletion Loop
- **3D Raycast Vector Laser Sweeper Pass:** Tracks click commands natively on the GPU thread. Steps an invisible sampling point out up to 20 meters along the camera look vector direction using fine-tuned linear transformations to locate, identify, and destroy dynamic blocks instantly on impact lock.

---

## 🎮 Game Engine Controls

- **`W` / `A` / `S` / `D`:** Smooth first-person camera-relative grid navigation.
- **`Spacebar`:** Upward vertical velocity jump impulse force.
- **`Mouse Look`:** Absolute high-sensitivity pitch/yaw rotation view vectors.
- **`E` Key:** Generate falling skull block particle instances right ahead of your gaze.
- **`Left Mouse Button (LMB)`:** Fires an interactive raycast picker laser to blast custom blocks out of memory.
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
- [ ] **Phase I: Broad-Phase Spatial Partitioning Integration for the Raycaster (Next Operation)**
- [ ] Phase J: Real-time Raycast 3D Visual Debugger Trail Particle Indicators
- [ ] Phase K: Structural sandbox voxel editing (Flush right-click block placement)

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
Compilation Code: g++ -std=c++20 -Wall -Wextra -Iinclude -c src/Engine.cpp -o src/Engine.o && g++ -std=c++20 -Wall -Wextra -Iinclude -c src/main.cpp -o src/main.o && g++ src/Engine.o src/main.o -o bin/montaigne -lGL -lglfw -lGLEW && ./bin/montaigne
