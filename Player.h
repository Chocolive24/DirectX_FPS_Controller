#pragma once

#include "Input.h"

#include <DirectXMath.h>

class Player {
public:
  DirectX::XMVECTOR position;
  DirectX::XMVECTOR front_view;
  DirectX::XMVECTOR up_view;
  DirectX::XMVECTOR right_view;
  DirectX::XMVECTOR front_move;
  DirectX::XMVECTOR right_move;
  DirectX::XMVECTOR world_front;
  DirectX::XMVECTOR world_up;
  DirectX::XMVECTOR world_right;

  float yaw = -90.f, pitch = 0.f;
  float view_sensitivity = 15.f;
  float speed = 3.f;

  bool isGrounded = false;

  void Begin(DirectX::XMFLOAT3 start_pos) noexcept;
  void Update(float dt) noexcept;
  void Move(float dt) noexcept;
  void RotateView(float dt) noexcept;
  void UpdateVectors() noexcept;
};
