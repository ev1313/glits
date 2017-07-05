#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <stdexcept>

namespace x11 {
class X11Window
{
private:
  // X-related stuff
  Display* m_display;
  Window m_rootwnd;
  GLint m_attributes[23] = {GLX_DRAWABLE_TYPE,
                            GLX_WINDOW_BIT,
                            GLX_RENDER_TYPE,
                            GLX_RGBA_BIT,
                            GLX_X_VISUAL_TYPE,
                            GLX_TRUE_COLOR,
                            GLX_RED_SIZE,
                            8,
                            GLX_GREEN_SIZE,
                            8,
                            GLX_BLUE_SIZE,
                            8,
                            GLX_ALPHA_SIZE,
                            8,
                            GLX_DEPTH_SIZE,
                            24,
                            GLX_STENCIL_SIZE,
                            8,
                            GLX_DOUBLEBUFFER,
                            True,
                            None};

  XVisualInfo* m_visualinfo;
  Colormap m_colormap;
  XSetWindowAttributes m_swa;
  Window m_window;
  GLXContext m_glcontext;
  XWindowAttributes m_gwa;

  Atom m_atomWmDeleteWindow;
  // End of X related stuff

  unsigned int m_width;
  unsigned int m_height;
  double delta = 0.0;
  double sleeptime = 0.0;
  timespec prev;
  timespec current;

protected:
  // ancestors shall override these methods
  virtual void init();
  // the ancestor should call the handle function in this class, too,
  // as it handles the close calls & resizing
  virtual void handle(XEvent event);

  virtual void handleevents();

public:
  // create the class. call open() afterwards
  X11Window(unsigned int width, unsigned int height);

  ~X11Window();

  // initializes the X Window & creates an OpenGL context
  void open();

  // mainloop does event handling & calls render/swap
  void poll();
  void swap();

  // getters
  unsigned int getheight() const { return m_height; }

  unsigned int getwidth() const { return m_width; }
};
}
