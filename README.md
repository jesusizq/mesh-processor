# Mesh Processor

The `mesh-processor` is a high-performance C++ microservice designed to handle heavy geometric processing tasks. Currently, it focuses on triangulating 2D polygons using the ear clipping algorithm, with a scalable architecture to support additional mesh-related operations in the future.

It exposes a simple HTTP API to receive polygon data and return triangulated indices that can be used for wireframe visualization or mesh rendering.

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

- **Controllers**: Handle HTTP requests and responses (e.g., `TriangulationController`, `HealthController`).
- **Services**: Encapsulate business logic (e.g., `TriangulationService`).
- **Utilities**: Provide common functionality like JSON parsing (`JsonUtils`) and response handling (`ResponseHandler`).
- **Application**: The `MeshProcessorApp` wires everything together and runs the HTTP server.
- **External Libraries**: Includes `libtriangulation` (for core geometry operations), `cpp-httplib` (HTTP server), `nlohmann/json` (JSON parsing), and `spdlog` (logging).

## Build and Run

### Docker Build (Recommended)

The mesh-processor is designed to run as a containerized service:

```bash
# From project root
make up                          # Start all services
# or
make build-mesh-processor       # Build only mesh-processor
make mesh-processor-up          # Start only mesh-processor

# Direct Docker commands
docker compose up mesh-processor
```

The service will be available at `http://localhost:8080`.

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

**Response (200 OK):**

Returns service health information in JSON format.

_Example:_

```json
{
  "service": "mesh-processor",
  "status": "healthy",
  "timestamp": 1752585972,
  "version": "1.0.0"
}
```

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

The response is a JSON array of triangulated indices. Each set of 3 consecutive indices represents one triangle, where each index refers to a point in the original input array.

_Example:_

```json
[0, 1, 2]
```

This indicates that the triangle is formed by connecting the 1st, 2nd, and 3rd points from the input array (using 0-based indexing).

**Error Responses:**

- `400 Bad Request`: If the request body is not valid JSON or the polygon data is malformed.
- `500 Internal Server Error`: If an error occurs during the triangulation process.

## Future Enhancements

The architecture is designed to easily accommodate additional endpoints for other mesh processing tasks. New services and controllers can be added without modifying the core application structure.
