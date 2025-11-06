#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float3.hpp>

#include "graphics/graphics.hpp"

using Catch::Approx;
using Catch::Matchers::WithinAbs;

TEST_CASE("Camera left with Y rotation makes camera turn clockwise.")
{
  graphics::Camera cam {};

  cam.RotateY(90);

  const auto left = cam.Left();

  REQUIRE_THAT(left.x, WithinAbs(0, 0.001));
  REQUIRE_THAT(left.y, WithinAbs(0, 0.001));
  REQUIRE_THAT(left.z, WithinAbs(1, 0.001));
}

TEST_CASE("Camera left with Z rotation makes camera turn clockwise.")
{
  graphics::Camera cam {};

  cam.RotateZ(90);

  const auto left = cam.Left();

  REQUIRE_THAT(left.x, WithinAbs(0, 0.001));
  REQUIRE_THAT(left.y, WithinAbs(-1, 0.001));
  REQUIRE_THAT(left.z, WithinAbs(0, 0.001));
}

TEST_CASE("Camera forwards with X rotation makes camera lean forwards.")
{
  graphics::Camera cam {

  };

  REQUIRE(cam.Forwards() == glm::vec3 {0, 0, 1});

  // In a left handed coordinate system, this makes it lean forwards
  cam.RotateX(90);

  auto fwds {cam.Forwards()};
  REQUIRE_THAT(fwds.x, WithinAbs(0, 0.001));
  REQUIRE_THAT(fwds.y, WithinAbs(-1, 0.001));
  REQUIRE_THAT(fwds.z, WithinAbs(0, 0.001));
}

TEST_CASE("Camera forwards with Y rotation turns clockwise from above.")
{
  graphics::Camera cam {};

  // In a left handed coordinate system, this makes it rotate clockwise in place
  cam.RotateY(90);

  const auto fwds = cam.Forwards();

  REQUIRE_THAT(fwds.x, WithinAbs(1, 0.001));
  REQUIRE_THAT(fwds.y, WithinAbs(0, 0.001));
  REQUIRE_THAT(fwds.z, WithinAbs(0, 0.001));
}
