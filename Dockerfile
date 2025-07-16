# ------------------------------------------------------------------------------
# Builder stage
# ------------------------------------------------------------------------------
FROM ubuntu:22.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /build

# Copy source code
COPY . /build/

# Configure and build the project
RUN mkdir -p build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DBUILD_SHARED_LIBS=OFF && \
    cmake --build . -j$(nproc) && \
    cmake --install . --prefix /install

# ------------------------------------------------------------------------------
# Test stage
# ------------------------------------------------------------------------------
FROM builder AS test

# Build with tests enabled (but don't run yet)
RUN mkdir -p build_test && cd build_test && \
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -DBUILD_SHARED_LIBS=OFF && \
    cmake --build . -j$(nproc)

# Set working directory and default command to run tests
WORKDIR /build/build_test
CMD ["sh", "-c", "echo '==================== Running Tests ====================' && ctest --output-on-failure --verbose && echo '==================== Tests Complete ==================='"]

# ------------------------------------------------------------------------------
# Runtime stage
# ------------------------------------------------------------------------------
FROM ubuntu:22.04 AS runtime

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    curl \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd --create-home --shell /bin/bash meshuser

# Copy the built application
COPY --from=builder /install/bin/MeshProcessor /usr/local/bin/MeshProcessor

# Switch to non-root user
USER meshuser
WORKDIR /home/meshuser

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD curl -f http://localhost:8080/health || exit 1

# Expose port
EXPOSE 8080

# Start the application
CMD ["/usr/local/bin/MeshProcessor"] 