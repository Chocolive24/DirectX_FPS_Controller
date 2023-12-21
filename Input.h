#pragma once
#include <windows.h>
#include <windowsx.h>

namespace Input
{
  extern bool w_pressed;
  extern bool a_pressed;
  extern bool s_pressed;
  extern bool d_pressed;
  extern bool l_shift_pressed;
  extern bool space_pressed;

  extern int mouse_x;
  extern int mouse_y;
  extern int old_mouse_x;
  extern int old_mouse_y;
  extern int mouse_delta_x;
  extern int mouse_delta_y;

  void ProcessInputs(UINT msg, WPARAM wparam, LPARAM lparam);
};

