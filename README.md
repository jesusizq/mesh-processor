# Mesh Processor

The `mesh-processor` is a C++ microservice responsible for performing heavy geometric processing tasks. Currently, its primary function is to triangulate 2D polygons.

It exposes a simple HTTP API to receive polygon data and return the triangulated mesh.

## Prerequisites

### For Local Build

- C++17 compatible compiler (e.g., GCC, Clang)
- CMake 3.16 or higher
- Git

### For Docker

- Docker
- Docker Compose

## Build and Run

### Local Development

1.  **Clone the repository and initialize submodules:**

    ```bash
    git clone <repository-url>
    cd mesh-processor
    git submodule update --init --recursive
    ```

2.  **Configure and build the project:**

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

3.  **Run the service:**
    ```bash
    ./src/mesh_processor
    ```
    The server will start on port 8080.

### Using Docker

1.  **Build and run the service using Docker Compose:**
    ```bash
    docker-compose up --build
    ```
    The service will be available at `http://localhost:8080`.

## API Documentation

### `POST /triangulate`

This endpoint accepts a JSON array of 2D points that define a polygon and returns a triangulated version of that polygon.

**Request Body:**

The request body must be a JSON array of points. Each point is an object with `x` and `y` numeric coordinates.

_Example:_

```json
[
  { "x": 100, "y": 100 },
  { "x": 200, "y": 100 },
  { "x": 150, "y": 200 }
]
```

**Success Response (200 OK):**

The response is a JSON array of triangles. Each triangle is an array of 3 points, and each point is an object with `x` and `y` coordinates.

_Example:_

```json
[
  [
    { "x": 100, "y": 100 },
    { "x": 200, "y": 100 },
    { "x": 150, "y": 200 }
  ]
]
```

**Error Responses:**

- `400 Bad Request`: If the request body is not valid JSON.
- `500 Internal Server Error`: If an error occurs during the triangulation process.
