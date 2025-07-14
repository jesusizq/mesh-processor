# Mesh Processor

The `mesh-processor` is a high-performance C++ microservice designed to handle heavy geometric processing tasks. Currently, it focuses on triangulating 2D polygons, with a scalable architecture to support additional mesh-related operations in the future.

It exposes a simple HTTP API to receive polygon data and return the triangulated mesh.

## Prerequisites

### For Local Build

- C++17 compatible compiler (e.g., GCC, Clang)
- CMake 3.16 or higher
- Git (for cloning and managing submodules)

### For Docker

- Docker
- Docker Compose

## Project Structure

The `mesh-processor` follows a layered architecture for maintainability and scalability:

- **Controllers**: Handle HTTP requests and responses (e.g., `TriangulationController`).
- **Services**: Encapsulate business logic (e.g., `TriangulationService`).
- **Utilities**: Provide common functionality like JSON parsing (`JsonUtils`) and response handling (`ResponseHandler`).
- **Application**: The `MeshProcessorApp` wires everything together and runs the HTTP server.
- **External Libraries**: Includes `libtriangulation` (for core geometry operations), `cpp-httplib` (HTTP server), `nlohmann/json` (JSON parsing), and `spdlog` (logging).

## Build and Run

### Local Development

1. **Clone the repository and initialize submodules:**

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

4. **Run Tests (Optional):**

   If tests are included, you can run them after building:

   ```bash
   ctest --output-on-failure
   ```

## API Documentation

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

**Success Response (200 OK):**

The response is a JSON array of triangles. Each triangle is an array of 3 points, and each point is an array of two numbers `[x, y]`.

_Example:_

```json
[
  [
    [100, 100],
    [200, 100],
    [150, 200]
  ]
]
```

**Error Responses:**

- `400 Bad Request`: If the request body is not valid JSON or the polygon data is malformed.
- `500 Internal Server Error`: If an error occurs during the triangulation process.

## Future Enhancements

The architecture is designed to easily accommodate additional endpoints for other mesh processing tasks. New services and controllers can be added without modifying the core application structure.
