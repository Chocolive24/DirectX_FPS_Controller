#include "Input.h"

namespace Input {

 State state{};

  void Input::ProcessInputs(UINT msg, WPARAM wparam, LPARAM lparam) {
   switch (msg) {
     case WM_MOUSEMOVE: {
       Input::state.mouse_x = GET_X_LPARAM(lparam);
       Input::state.mouse_y = GET_Y_LPARAM(lparam);
       break;
     }
     case WM_LBUTTONDOWN:
       state.mouse_relative = true;
       ShowCursor(FALSE);
       break;
     case WM_KEYDOWN:
       switch (wparam) {
         case VK_ESCAPE:
           state.mouse_relative = false;
           ShowCursor(TRUE);
           break;
         case 'W':
           Input::state.w = true;
           break;
         case 'A':
           Input::state.a = true;
           break;
         case 'S':
           Input::state.s = true;
           break;
         case 'D':
           Input::state.d = true;
           break;
         case VK_SHIFT:
           Input::state.l_shift = true;
           break;
         case VK_SPACE:
           Input::state.space = true;
           break;
       }
       break;
     case WM_KEYUP:
       switch (wparam) {
         case 'W':
           Input::state.w = false;
           break;
         case 'A':
           Input::state.a = false;
           break;
         case 'S':
           Input::state.s = false;
           break;
         case 'D':
           Input::state.d = false;
           break;
         case VK_SHIFT:
           Input::state.l_shift = false;
           break;
         case VK_SPACE:
           Input::state.space = false;
           break;
       }
       break;
   }
  }

  void UpdateMouseRelativeState(const HWND& window, RECT rect, POINT center) {
   // Calculate mouse delta
   Input::state.mouse_delta_x = Input::state.mouse_x - Input::state.old_mouse_x;
   Input::state.mouse_delta_y = Input::state.mouse_y - Input::state.old_mouse_y;

   GetClientRect(window, &rect);
   center.x = (rect.left + rect.right) / 2;
   center.y = (rect.top + rect.bottom) / 2;

   //  Update previous mouse position
   Input::state.old_mouse_x =
       Input::state.mouse_relative ? center.x : Input::state.mouse_x;
   Input::state.old_mouse_y =
       Input::state.mouse_relative ? center.y : Input::state.mouse_y;

   if (Input::state.mouse_relative) {
     ClientToScreen(window, &center);
     SetCursorPos(center.x, center.y);
   }
  }

}  // namespace Input