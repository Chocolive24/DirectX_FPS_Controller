#pragma once

#include "Input.h"

#include <DirectXMath.h>

class Camera {
public:
  DirectX::XMVECTOR position;
  DirectX::XMVECTOR front;
  DirectX::XMVECTOR up;
  DirectX::XMVECTOR right;
  DirectX::XMVECTOR world_front;
  DirectX::XMVECTOR world_up;
  DirectX::XMVECTOR world_right;

  DirectX::XMMATRIX view_matrix;
  
  float yaw = -90.f, pitch = 0.f;
  float sensitivity = 15.f;
  float speed = 3.f;
  
  void Begin(DirectX::XMFLOAT3 start_pos) noexcept;
  void Update() noexcept;
  void UpdateCameraVectors() noexcept;
  void Move() noexcept;
  void Rotate() noexcept;
};
