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
  bool is_grounded = false;
  bool is_in_water = false;

  void Begin(DirectX::XMFLOAT3 start_pos) noexcept;
  void Update(float dt) noexcept;

  void ApplyForce(DirectX::XMVECTOR force, ForceMode force_mode) noexcept;

  [[nodiscard]] PlayerMode mode() const noexcept { return mode_; };
  [[nodiscard]] DirectX::XMVECTOR position() const noexcept { return position_; };
  [[nodiscard]] DirectX::XMVECTOR velocity() const noexcept { return velocity_; };
  [[nodiscard]] DirectX::XMVECTOR front_view() const noexcept { return front_view_; };
  [[nodiscard]] DirectX::XMVECTOR up_view() const noexcept { return up_view_; };

  void set_position(DirectX::XMVECTOR position) noexcept { position_ = position; };
  void set_velocity(DirectX::XMVECTOR velocity) noexcept { velocity_ = velocity; };

private:
  static constexpr DirectX::XMFLOAT3 null_vector = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

  PlayerMode mode_ = PlayerMode::kCreative;

  DirectX::XMVECTOR position_;
  DirectX::XMVECTOR velocity_;
  DirectX::XMVECTOR front_view_;
  DirectX::XMVECTOR up_view_;

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