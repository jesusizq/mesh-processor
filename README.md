# Mesh Processor

The `mesh-processor` is a high-performance C++ microservice designed to handle heavy geometric processing tasks. Currently, it focuses on triangulating 2D polygons with **advanced self-intersection handling**, using a combination of the Clipper2 library for intersection resolution and the ear clipping algorithm for triangulation.

It exposes a simple HTTP API to receive polygon data and return both resolved vertices and triangulated indices that can be used for wireframe visualization or mesh rendering.

## Features

- **Self-Intersecting Polygon Support**: Automatically detects and resolves self-intersections using Clipper2
- **High-Performance Triangulation**: Uses the optimized ear clipping algorithm for simple polygons
- **Robust Architecture**: Layered design with clear separation of concerns
- **Comprehensive API**: Returns both resolved vertices and triangle indices
- **Fully Tested**: Comprehensive test suite with CI/CD integration

## Prerequisites

### For Local Build

- C++17 compatible compiler (e.g., GCC, Clang)
- CMake 3.16 or higher
- Git (for cloning and managing submodules)

## Project Structure

The `mesh-processor` follows a layered architecture for maintainability and scalability:

- **Controllers**: Handle HTTP requests and responses (e.g., `TriangulationController`, `HealthController`).
- **Services**: Encapsulate business logic (e.g., `TriangulationService`).
- **Utilities**: Provide common functionality like JSON parsing (`JsonUtils`) and response handling (`ResponseHandler`).
- **Application**: The `MeshProcessorApp` wires everything together and runs the HTTP server.
- **External Libraries**:
  - `libtriangulation` (core geometry operations with self-intersection support)
  - `Clipper2` (intersection resolution for self-intersecting polygons)
  - `cpp-httplib` (HTTP server)
  - `nlohmann/json` (JSON parsing)
  - `spdlog` (logging)

## Build and Run

1. **Initialize submodules:**

   ```bash
   git submodule update --init --recursive
   ```

2. **Configure and build the project:**

   ```bash
   mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build . -j$(nproc)
   ```

   If you want to build tests, you can use the following command:

   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON && cmake --build . -j$(nproc)
   ```

3. **Run the service:**

   ```bash
   ./app/MeshProcessor
   ```

   The server will start on port 8080 by default.

   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
   cmake --build . -j$(nproc)
   ```

   If tests are included, you can run them after building:

   ```bash
   ctest --output-on-failure
   ```

## API Documentation

### `GET /health`

Health check endpoint for monitoring service status.

### `POST /triangulate`

This endpoint accepts a JSON array of 2D points that define a polygon and returns a triangulated version of that polygon.

**Request Body:**

The request body must be a JSON array of points. Each point is represented as an array of two numbers `[x, y]`.

_Example:_

```json
[
  [100, 100],
  [200, 100],
  [150, 200]
]
```
