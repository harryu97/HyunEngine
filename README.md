# HyunEngine
A 3D game engine built from the scratch with C++ and modern OpenGL.

This project is for educational purpose focusing on learning engine architecture and rendering pipeline.
It is still under active development.


<img width="1170" height="633" alt="2026-01-28-230728_hyprshot" src="https://github.com/user-attachments/assets/630ef04d-255d-4a79-b43a-1410ed41f92f" />

## Project Goals
- Learning engine architecture and rendering pipeline
- Implement custom memory management and resource manager
- Built ECS systems

## Tech Stack

- C++ 17
- OpenGL 3.3
- Bullet Physics
- MiniAudio
- JSON

---

## Project Structure
```
HyunEngine/
├── engine/
│   ├── core/           # Application loop, timing, input
│   ├── scene/          # GameObject, Component, Transform hierarchy
│   ├── graphics/       # Renderer, Mesh, Material, Shader, Texture
│   ├── physics/        # PhysicsWorld, RigidBody, Colliders
│   ├── audio/          # AudioEngine, AudioSource, AudioListener
│   ├── assets/         # AssetManager, GLTFLoader, TextureLoader
│   └── memory/         # Custom allocators (in progress)
│
├── shaders/            # GLSL vertex and fragment shaders
└── assets/
    ├── models/         # .gltf test assets
    ├── textures/       # Sample textures
    └── audio/          # Test audio files
```
---

## Features

### Graphics & Rendering
- OpenGL abstraction Layer
- Render Queue and Graphics API system

### Physics (Bullet)
- Rigid body dynamics
- Collision detection
- Kinematic controller
- 
### Memory Management & Resource Manager
- Custom Allocator
- Implement resource manager

**Current State:** Transitioning from mixed raw/smart pointers to a custom handle-based system for better control and learning.

---


## Building

### Build Steps
```bash
git clone https://github.com/harryu97/HyunEngine.git
cd HyunEngine
mkdir build && cd build
cmake ..
make -j
./myapp
```
---

## Roadmap

### Phase 1: Memory Management and resource manager (Current)
- Replace raw pointers with smart pointers
- Create resource manager as singleton

### Phase 2: Rendering Pipeline
- Work on more detailed rendering system
- Adding skybox

---

## Current Issue

- Mixed use of raw pointers and smart pointers (refactoring in progress)
- In progress to change raw pointers to smart pointers for better memory management
