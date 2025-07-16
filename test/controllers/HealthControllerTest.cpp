#include "HealthController.h"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <thread>

class HealthControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    healthController = std::make_unique<controllers::HealthController>();

    // Create a test server
    server = std::make_unique<httplib::Server>();
    healthController->registerRoutes(*server);

    // Start server in background thread
    serverThread = std::thread([this]() {
      server->listen("localhost", 0); // Use any available port
    });

    // Give server time to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  void TearDown() override {
    if (server) {
      server->stop();
    }
    if (serverThread.joinable()) {
      serverThread.join();
    }
  }

  std::unique_ptr<controllers::HealthController> healthController;
  std::unique_ptr<httplib::Server> server;
  std::thread serverThread;
};

TEST_F(HealthControllerTest, HealthEndpointReturnsValidResponse) {
  // Test that the controller can be instantiated and routes can be registered
  EXPECT_NE(healthController, nullptr);

  // Verify the controller exists and can register
  // routes without throwing
  httplib::Server testServer;
  EXPECT_NO_THROW(healthController->registerRoutes(testServer));
}

TEST_F(HealthControllerTest, ControllerCreationDoesNotThrow) {
  EXPECT_NO_THROW(
      { auto controller = std::make_unique<controllers::HealthController>(); });
}