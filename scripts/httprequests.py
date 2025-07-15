import requests
import json

# The base URL of the mesh processor application
# Make sure the application is running before executing this script.
BASE_URL = "http://localhost:8080"


def test_triangulation_valid_request():
    """
    Tests the /triangulate endpoint with a valid polygon to ensure it
    returns a successful response with the correct data structure.
    """
    print("--- Testing valid triangulation request ---")
    # The endpoint for triangulation. This might need to be adjusted
    # if your routing is set up differently.
    url = f"{BASE_URL}/triangulate"

    # A simple square polygon, same as in the C++ unit tests
    polygon = [[0.0, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]]

    headers = {"Content-Type": "application/json"}

    try:
        print(f"Sending POST request to {url}...")
        response = requests.post(url, data=json.dumps(polygon), headers=headers)

        print(f"Status Code: {response.status_code}")
        assert (
            response.status_code == 200
        ), f"Expected status code 200, got {response.status_code}"

        print(f"Content-Type: {response.headers['Content-Type']}")
        assert (
            "application/json" in response.headers["Content-Type"]
        ), "Content-Type is not application/json"

        response_data = response.json()
        print(f"Response JSON: {json.dumps(response_data, indent=2)}")

        # A square should be triangulated into 2 triangles
        assert isinstance(response_data, list), "Response is not a list"
        assert (
            len(response_data) == 2
        ), f"Expected 2 triangles, got {len(response_data)}"

        # Each triangle should have 3 vertices, and each vertex 2 coordinates
        for triangle in response_data:
            assert isinstance(triangle, list), "Triangle is not a list"
            assert (
                len(triangle) == 3
            ), f"Expected 3 vertices in a triangle, got {len(triangle)}"
            for vertex in triangle:
                assert isinstance(vertex, list), "Vertex is not a list"
                assert (
                    len(vertex) == 2
                ), f"Expected 2 coordinates in a vertex, got {len(vertex)}"

        print("✔️  Valid triangulation test PASSED")

    except requests.exceptions.RequestException as e:
        print(f"❌ Test failed: Could not connect to the server. Is it running? {e}")
    except Exception as e:
        print(f"❌ Test failed with an unexpected error: {e}")


def test_triangulation_invalid_json():
    """
    Tests the /triangulate endpoint with invalid JSON to ensure it
    correctly returns a 400 Bad Request error.
    """
    print("\n--- Testing invalid JSON request ---")
    url = f"{BASE_URL}/triangulate"

    invalid_json_body = "this is not valid json"

    headers = {"Content-Type": "application/json"}

    try:
        print(f"Sending POST request to {url} with invalid JSON...")
        response = requests.post(url, data=invalid_json_body, headers=headers)

        print(f"Status Code: {response.status_code}")
        assert (
            response.status_code == 400
        ), f"Expected status code 400, got {response.status_code}"

        response_data = response.json()
        print(f"Response JSON: {json.dumps(response_data, indent=2)}")

        assert "error" in response_data, "Error message not found in response"
        print("✔️  Invalid JSON test PASSED")

    except requests.exceptions.RequestException as e:
        print(f"❌ Test failed: Could not connect to the server. Is it running? {e}")
    except Exception as e:
        print(f"❌ Test failed with an unexpected error: {e}")


if __name__ == "__main__":
    test_triangulation_valid_request()
    test_triangulation_invalid_json()
