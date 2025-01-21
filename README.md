# Fully Ray Tracer V1

## Introduction
Fully Ray Tracer is an offline ray tracing renderer developed in C++. It uses the Eigen library to support vector operations and the OpenCV library to display the rendering process and results. The remaining code relies solely on native C++ functionalities. The project's structure is inspired by the book ["Ray Tracing in One Weekend"](https://github.com/RayTracing/raytracing.github.io)

## Scene
- **Objects**: Currently, the scene includes interactable spherical objects only.

## Ray Tracing
- **Algorithm**: Implements the path-tracing algorithm for realistic rendering.

## Acceleration Structure
- **BVH Trees**: Utilizes Bounding Volume Hierarchy (BVH) trees to accelerate the rendering process.

## Device
- **CPU-based**: Operates on CPU with a simple thread pool for management.

## Rendering Effects
![Rendering Sample](https://github.com/FriendlyNeighborWang/Fully_Ray_Tracer/blob/master/Fully_Ray_Tracer/output.jpg?raw=true)

## Future Work
- **Complex Scenes**: Plan to implement interaction among various complex structures in the scene and introduce external models.
- **GPU Rendering**: Aiming to utilize CUDA for rendering on GPU to enhance performance.
- **Advanced PBR Effects**: Plans to implement a wider variety of Physically Based Rendering (PBR) effects and acceleration algorithms.
