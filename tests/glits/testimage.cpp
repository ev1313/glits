#include <catch.hpp>

#include "glits/glits.hpp"
#include "x11window.hpp"

TEST_CASE("glits/testimage.cpp", "general tests") {
  x11::X11Window wnd(600, 400);
  wnd.open();

  SECTION("clear color framebuffer test") {
    glClearColor(0.4f, 0.5f, 0.6f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    REQUIRE(glits::check_framebuffer("../testdata/framebuffer_empty.png", 0.01f, 0.01f, GLITS_GENERATE_TESTS));
  }

  SECTION("quad test") {
    glClearColor(0.4f, 0.5f, 0.6f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
    REQUIRE(glits::check_framebuffer("../testdata/framebuffer_quad.png", 0.01f, 0.01f, GLITS_GENERATE_TESTS));
  }
}
