#include <catch.hpp>

#include "glits/glits.hpp"

TEST_CASE("glits/testimage.cpp", "general tests") {

  SECTION("empty framebuffer test") {
    glClearColor(0.4f, 0.5f, 0.6f, 0.5f);

    REQUIRE(glits::check_texture("../testdata/test.png", 1, 1));
  }
}
