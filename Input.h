#pragma once
#include <windows.h>
#include <windowsx.h>

namespace Input
{
  struct State {
	bool w;
	bool a;
	bool s;
	bool d;
	bool l_shift;
	bool space;
    bool key_1;
    bool key_2;
	
	bool mouse_relative;
	int mouse_x;
	int mouse_y;
	int old_mouse_x;
	int old_mouse_y;
	int mouse_delta_x;
	int mouse_delta_y; 
  };

  extern State state;

  void ProcessInputs(UINT msg, WPARAM wparam, LPARAM lparam);
  void UpdateMouseRelativeState(const HWND& window, RECT rect, POINT center);
 };

