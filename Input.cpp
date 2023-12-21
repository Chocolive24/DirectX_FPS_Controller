#include "Input.h"

namespace Input {

  bool w_pressed = false;
  bool a_pressed = false;
  bool s_pressed = false;
  bool d_pressed = false;
  bool l_shift_pressed = false;
  bool space_pressed = false;

  int mouse_x = 0;
  int mouse_y = 0;
  int old_mouse_x = 0;
  int old_mouse_y = 0;
  int mouse_delta_x = 0;
  int mouse_delta_y = 0;

void Input::ProcessInputs(UINT msg, WPARAM wparam, LPARAM lparam) {
  switch (msg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_KEYDOWN:
      switch (wparam) {
        case VK_ESCAPE:
          PostQuitMessage(0);
          break;
        case 'W':
          w_pressed = true;
          break;
        case 'A':
          a_pressed = true;
          break;
        case 'S':
          s_pressed = true;
          break;
        case 'D':
          d_pressed = true;
          break;
        case VK_SHIFT:
          l_shift_pressed = true;
          break;
        case VK_SPACE:
          space_pressed = true;
          break;
      }
      break;
    case WM_KEYUP:
      switch (wparam) {
        case 'W':
          w_pressed = false;
          break;      
        case 'A':     
          a_pressed = false;
          break;      
        case 'S':     
          s_pressed = false;
          break;      
        case 'D':     
          d_pressed = false;
          break;
        case VK_SHIFT:
          l_shift_pressed = false;
          break;
        case VK_SPACE:
          space_pressed = false;
          break;
      }
      break;
  }
}

}  // namespace Input