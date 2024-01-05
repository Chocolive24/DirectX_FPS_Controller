#pragma once

#include "Input.h"

#include <DirectXMath.h>

class Player {
public:
  DirectX::XMVECTOR position;
  DirectX::XMVECTOR front_view;
  DirectX::XMVECTOR up_view;

  bool isGrounded = false;

  void Begin(DirectX::XMFLOAT3 start_pos) noexcept;
  void Update(float dt) noexcept;

private:
  DirectX::XMVECTOR right_view_;
  DirectX::XMVECTOR front_move_;
  DirectX::XMVECTOR right_move_;
  DirectX::XMVECTOR world_front_;
  DirectX::XMVECTOR world_up_;
  DirectX::XMVECTOR world_right_;

  float yaw_ = -90.f, pitch_ = 0.f;
  float view_sensitivity_ = 15.f;
  float move_speed_ = 10.f;

  void Move(float dt) noexcept;
  void RotateView(float dt) noexcept;
  void UpdateVectors() noexcept;
};