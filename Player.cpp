#include "player.h"

#include <iostream>

void Player::Begin(DirectX::XMFLOAT3 start_pos) noexcept {
  position_ = DirectX::XMLoadFloat3(&start_pos);

  velocity_ = DirectX::XMLoadFloat3(&null_vector);
  forces_ = DirectX::XMLoadFloat3(&null_vector);
  impulses_ = DirectX::XMLoadFloat3(&null_vector);

  DirectX::XMFLOAT3 front_val(0.f, 0.f, -1.f);
  front_view_ = DirectX::XMLoadFloat3(&front_val);

  DirectX::XMFLOAT3 up_val(0.f, 1.f, 0.f);
  up_view_ = DirectX::XMLoadFloat3(&up_val);

  DirectX::XMFLOAT3 right_val(1.f, 0.f, 0.f);
  right_view_ = DirectX::XMLoadFloat3(&right_val);
}

void Player::Update(const float dt) noexcept {
  HandlePlayerMode();

  RotateView(dt);
  
  HandleJump();
  HandleMovements();

  // a = F / m (mass of the player is 1 to simplify the physics).
  // = > a = F
  velocity_ = DirectX::XMVectorAdd(velocity_, DirectX::XMVectorScale(forces_, dt));
  velocity_ = DirectX::XMVectorAdd(velocity_, impulses_);

  position_ = DirectX::XMVectorAdd(position_, DirectX::XMVectorScale(velocity_, dt));

  // Remove the impulses from the velocity.
  velocity_ = DirectX::XMVectorSubtract(velocity_, impulses_);

  // Reset physics vectors.
  move_dir_ = DirectX::XMLoadFloat3(&null_vector);
  forces_ = DirectX::XMLoadFloat3(&null_vector);
  impulses_ = DirectX::XMLoadFloat3(&null_vector);
}

void Player::HandleJump() noexcept {
  if (Input::state.space && mode_ == PlayerMode::kClassic) {
    if (is_grounded && !is_in_water) {
      ApplyForce(DirectX::XMVECTOR{0, 1700.f, 0}, ForceMode::kForce);
      is_grounded = false;
    } else if (is_in_water) {
      move_dir_ = DirectX::XMVectorAdd(move_dir_, world_up_);
      // pas bien car monte pas assez haut en sortant de l'eau si j'appuie aussi
      // sur W.
    }
  }
}

void Player::HandlePlayerMode() noexcept {
  if (Input::state.key_1) {
    mode_ = PlayerMode::kClassic;
  }
  if (Input::state.key_2) {
    mode_ = PlayerMode::kCreative;
    velocity_ = DirectX::XMLoadFloat3(&null_vector);
    forces_ = DirectX::XMLoadFloat3(&null_vector);
  }
}

void Player::HandleMovements() noexcept {
  if (Input::state.w) {
    move_dir_ = DirectX::XMVectorAdd(move_dir_, front_move_);
  }
  if (Input::state.s) {
    move_dir_ = DirectX::XMVectorAdd(move_dir_, DirectX::XMVectorNegate(front_move_));
  }
  if (Input::state.a) {
    move_dir_ = DirectX::XMVectorAdd(move_dir_, DirectX::XMVectorNegate(right_move_));
  }
  if (Input::state.d) {
    move_dir_ = DirectX::XMVectorAdd(move_dir_, right_move_);
  }

  if (mode_ == PlayerMode::kCreative)
  {
    if (Input::state.l_shift) {
      move_dir_ =
          DirectX::XMVectorAdd(move_dir_, DirectX::XMVectorNegate(world_up_));
    }
    if (Input::state.space) {
      move_dir_ = DirectX::XMVectorAdd(move_dir_, world_up_);
    }
  }

  ApplyForce(DirectX::XMVectorScale(DirectX::XMVector3Normalize(move_dir_),
                                    move_speed_), ForceMode::kImpulse);
}

void Player::RotateView(const float dt) noexcept {
  static constexpr float pitch_limit = 89.f;

  yaw_ += Input::state.mouse_delta_x * view_sensitivity_ * dt;
  pitch_ -= Input::state.mouse_delta_y * view_sensitivity_ * dt;

  if (pitch_ > pitch_limit) pitch_ = pitch_limit;
  if (pitch_ < -pitch_limit) pitch_ = -pitch_limit;

  UpdateVectors();
}

void Player::UpdateVectors() noexcept {
  // Update view vectors.
  DirectX::XMFLOAT3 new_front_view;
  new_front_view.x = cos(DirectX::XMConvertToRadians(yaw_)) *
                cos(DirectX::XMConvertToRadians(pitch_));
  new_front_view.y = sin(DirectX::XMConvertToRadians(pitch_));
  new_front_view.z = sin(DirectX::XMConvertToRadians(yaw_)) *
                cos(DirectX::XMConvertToRadians(pitch_));

  DirectX::XMVECTOR v_new_front_view = DirectX::XMLoadFloat3(&new_front_view);
  front_view_ = DirectX::XMVector3Normalize(v_new_front_view);

  // normalize the vectors, because their length gets closer to 0 the more you
  // look up or down which results in slower movement
  right_view_ =
      DirectX::XMVector3Normalize(DirectX::XMVector3Cross(front_view_, world_up_));
  up_view_ = DirectX::XMVector3Normalize(
      DirectX::XMVector3Cross(right_view_, front_view_));

  // Update movement vectors.
  DirectX::XMFLOAT3 new_front_move;
  new_front_move.x = cos(DirectX::XMConvertToRadians(yaw_));
  new_front_move.y = 0.f;
  new_front_move.z = sin(DirectX::XMConvertToRadians(yaw_));

  front_move_ = DirectX::XMLoadFloat3(&new_front_move);

  right_move_ = DirectX::XMVector3Normalize(
                DirectX::XMVector3Cross(front_move_, world_up_));
}

void Player::ApplyForce(DirectX::XMVECTOR force,
                        ForceMode force_mode) noexcept {
  switch (force_mode) {
    case ForceMode::kForce:
      forces_ = DirectX::XMVectorAdd(forces_, force);
      break;
    case ForceMode::kImpulse:
      impulses_ = DirectX::XMVectorAdd(impulses_, force);
      break;
    default:
      break;
  }
}