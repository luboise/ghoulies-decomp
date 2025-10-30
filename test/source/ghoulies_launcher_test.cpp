#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float3.hpp>

#include "graphics/graphics.hpp"

using Catch::Approx;
using Catch::Matchers::WithinAbs;

TEST_CASE("Camera directions are correct.", "Camera")
{
  graphics::Camera cam {};

  REQUIRE(cam.Left() == glm::vec3 {-1, 0, 0});
  // Make it lean forwards

  cam.rotation.x += 1;

  // Leaning forwards shouldn't affect left vector
  REQUIRE(cam.Left() == glm::vec3 {-1, 0, 0});

  // When facing left, this->Left() should point backwards
  cam.rotation = glm::vec3 {0, glm::pi<float>() / 2, 0};

  const auto left = cam.Left();

  REQUIRE_THAT(left.x, WithinAbs(0, 0.001));
  REQUIRE_THAT(left.y, WithinAbs(0, 0.001));
  REQUIRE_THAT(left.z, WithinAbs(-1, 0.001));

  // cam.rotation =
}
