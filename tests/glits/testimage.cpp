#include <catch.hpp>

#include "x11window.hpp"
#include "glits/glits.hpp"

TEST_CASE("glits/testimage.cpp", "general tests") {
  x11::X11Window wnd(600,400);
  wnd.open();

  SECTION("clear color framebuffer test") {
    glClearColor(0.4f, 0.5f, 0.6f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    REQUIRE(glits::check_framebuffer("../testdata/framebuffer_empty.png", 0.01f, 0.01f));
  }
}
