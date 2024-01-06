#pragma once

#include "input.h"

#include <DirectXMath.h>

class Camera {
public:
  DirectX::XMVECTOR position;
  DirectX::XMVECTOR front_dir;
  DirectX::XMVECTOR up_dir;
  DirectX::XMVECTOR right_dir;
  DirectX::XMVECTOR front_move;
  DirectX::XMVECTOR right_move;
  DirectX::XMVECTOR world_up;

  DirectX::XMMATRIX view_matrix;
  
  float yaw = -90.f, pitch = 0.f;
  float sensitivity = 15.f;
  float speed = 3.f;
  
  void Begin(DirectX::XMFLOAT3 start_pos) noexcept;
  void Update(float dt) noexcept;
  void UpdateCameraVectors() noexcept;
  void Move(float dt) noexcept;
  void Rotate(float dt) noexcept;
};
