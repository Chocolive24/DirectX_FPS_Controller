#pragma once

#include "input.h"

#include <DirectXMath.h>

enum class PlayerMode {
  kNone = 0,
  kClassic,
  kCreative
};

enum class ForceMode {
  kForce,
  kImpulse
};

class Player {
public:
  DirectX::XMVECTOR position;
  DirectX::XMVECTOR velocity;
  DirectX::XMVECTOR front_view;
  DirectX::XMVECTOR up_view;

  PlayerMode mode = PlayerMode::kCreative;

  bool is_grounded = false;
  bool is_in_water = false;

  void Begin(DirectX::XMFLOAT3 start_pos) noexcept;
  void Update(float dt) noexcept;

  void ApplyForce(DirectX::XMVECTOR force, ForceMode force_mode) noexcept;

private:
  static constexpr DirectX::XMFLOAT3 null_vector = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

  DirectX::XMVECTOR forces_;
  DirectX::XMVECTOR impulses_;

  DirectX::XMVECTOR move_dir_;
  DirectX::XMVECTOR right_view_;
  DirectX::XMVECTOR front_move_;
  DirectX::XMVECTOR right_move_;
  static constexpr DirectX::XMVECTOR world_front_ = DirectX::XMVECTOR{0, 0, 1};
  static constexpr DirectX::XMVECTOR world_up_ = DirectX::XMVECTOR{0, 1, 0};
  static constexpr DirectX::XMVECTOR world_right_ = DirectX::XMVECTOR{1, 0, 0};

  float yaw_ = -90.f, pitch_ = 0.f;
  float view_sensitivity_ = 15.f;
  float move_speed_ = 7.f;

  void HandlePlayerMode() noexcept;
  void HandleJump() noexcept;
  void HandleMovements() noexcept;
  void RotateView(float dt) noexcept;
  void UpdateVectors() noexcept;
};