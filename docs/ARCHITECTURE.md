# Montaigne Engine: Systemic Software Architecture Specification
This document provides a low-level structural analysis of the core subsystems driving the Montaigne Engine framework. Written entirely in Modern C++20 and Core Profile OpenGL 3.3, the engine enforces strict memory hygiene, custom spatial linear algebra math primitives, and broad-phase optimization routines to maximize efficiency on hardware targets.

---## 🗺️ High-Level System Topological Map

[ User Keyboard/Mouse Input ]
│
▼
[ Engine::ProcessInput ] ───► Calculates Ray Vectors (Phase H & J)
│
▼
[ Engine::Run ]
│
├──► [ spatialGrid.Clear() & Insert() ] (Phase F)
│
├──► [ Kinematic Physics Update Loop ] (Phase C & G)
│ └──► [ spatialGrid.GetPotentialColliders ]
│
└──► [ Hardware Graphics Pipeline ] (Phase A, D, P & R)
└──► [ glDrawArrays Pipeline Instances ]


---

## 🛠️ Deep-Dive Subsystem Specifications

### 1. Spatial Mathematical Linear Algebra Foundation
The engine rejects external black-box matrix mathematics libraries (such as GLM), relying instead on standard custom array structures layout definitions defined in `include/MontaigneMath.hpp`:
- **`Vec3` Primitives**: Enforces strict contiguous 3-element float memory alignments for raw 3D translation offsets.
- **Row-Major `Mat4` Fields**: Utilizes a 16-element linear float array (`float m`) designed for uniform transformations. Translation, scaling, and rotation operations evaluate via row-major index mapping arrays, providing predictable pointer alignments when piped down to OpenGL vertex array registries.

### 2. Broad-Phase Spatial Partitioning Network (`SpatialGrid`)
To avoid performance drops associated with brute-force collision testing ($O(N^2)$ algorithm complexities), `include/SpatialGrid.hpp` implements a custom spatial hashing lookup grid map table:
- **Quantization Logic**: Floating-point world vector coordinates are parsed through a spatial calculation pass:
  $$f(x, y, z) = \left( \lfloor \frac{x}{\text{cellSize}} \rfloor, \lfloor \frac{y}{\text{cellSize}} \rfloor, \lfloor \frac{z}{\text{cellSize}} \rfloor \right)$$
- **Data Pooling Allocation**: Maps a 3D integer coordinate tuple (`std::tuple<int, int, int>`) directly to a dynamic vector array pool of active entity addresses (`std::vector<Entity*>`).
- **Neighborhood Evaluation Sweeping**: Kinematic stacking pipelines sweep a localized $3\times3\times3$ cell matrix neighborhood mask on each frame loop pass, reducing computation routines down to high-speed constant time lookups ($O(N)$ efficiency).

### 3. Dynamic Memory Hygiene & Lifespan Garbage Collector
To prevent runtime dangling reference errors and resource leak paths across active entity lookups, `src/Engine.cpp` enforces a multi-tiered tracking map container array layer (`std::map<int, Entity> entities`):
- **Lifecycle Expiration Passes**: Cube instances generated past their allocated allocation thresholds increment a floating lifetime ticker (`currentEntity.lifetime += deltaTime`).
- **Underworld Boundary Intercept Flags**: Elements drifting past critical dimensional thresholds ($Y < -20.0\text{f}$) are appended to isolated identification vectors (`deadEntityIDs`), allowing the engine to execute clean `.erase()` memory cellular sweeps right outside the active loop iterations.

### 4. Broad-Phase Assisted Raycast Intersector & Face Placement Math
The targeting pipelines fuse input tracking and spatial network allocations simultaneously inside `Engine::ProcessInput()`:
- **Laser Path Step Stepping**: Tracks Left and Right Mouse clicks natively on the GPU thread. Increments a sampling coordinate vector along the camera look vector direction using linear vector steps:
  $$\vec{P}_{\text{sample}} = \vec{P}_{\text{camera}} + (\vec{D}_{\text{normalized}} \times \text{distance})$$
- **Target Cell Lookups**: At each step slice, the position coordinates are piped into `spatialGrid.GetEntitiesAtPosition(finalPoint)`, restricting bounding box logic testing exclusively to elements tracking within that exact cell volume slot.
- **Voxel Axis Delta Structural Extrusion**: On Right-Click intersections, the builder evaluates normalized offset differences against the block's physical center bounding face scales:
  $$\Delta_{\text{axis}} = \frac{|P_{\text{sample}} - P_{\text{block}}|}{\text{Scale}_{\text{block}}}$$
  The highest delta scalar factor isolates the exact face surface entry alignment (Top, Bottom, North, South, East, West), injecting a brand-new snapped cube instance flush against that precise matrix edge boundary interface.

### 5. High-Visibility Hardware Fallback Texture Generators
To guarantee public execution stability, `include/AssetLoader.hpp` handles asset parsing streams protectively:
- **Procedural Backup Matrix Mapping**: If file pointer queries fail to map image assets (`models/floor.png`), the loader allocates an automated 4-pixel fallback array memory block inside raw RAM space.
- **Nearest-Neighbour Texture Binding**: Compiles a sharp 2x2 magenta/black checkerboard texture asset handle straight into active GPU memory layers, bypassing file absence drops with zero runtime stability compromises.

---

## 🎨 GPU Shader Uniform Pipeline Integration

### Vertex Pipeline (`src/shader.vert`)
Receives model, view, and perspective matrix registers, passing vertex locations down. Additionally, it reads individual primitive scalar variables (`ao_top_bot_north` and `ao_south_east_west`) populated frame by frame by the grid checks, interpolating uniform face shadows down to the fragment raster step.

### Fragment Pipeline (`src/shader.frag`)
Gathers the camera space position vectors, diffuse light properties, and interpolated face ambient occlusion attributes. Applies vector dot product math to evaluate lighting shading properties, multiplying final material texture fragment colors seamlessly by your custom **Frankenstein seam contact shadow modifiers**.

------------------------------
