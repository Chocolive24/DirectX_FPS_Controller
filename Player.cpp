#include "Player.h"
#include <iostream>

void Player::Begin(DirectX::XMFLOAT3 start_pos) noexcept {
  position = DirectX::XMLoadFloat3(&start_pos);

  DirectX::XMFLOAT3 front_val(0.f, 0.f, -1.f);
  front_view = DirectX::XMLoadFloat3(&front_val);

  DirectX::XMFLOAT3 up_val(0.f, 1.f, 0.f);
  up_view = DirectX::XMLoadFloat3(&up_val);

  DirectX::XMFLOAT3 right_val(1.f, 0.f, 0.f);
  right_view = DirectX::XMLoadFloat3(&right_val);

  DirectX::XMFLOAT3 w_front_val(0.f, 0.f, 1.f);
  world_front = DirectX::XMLoadFloat3(&w_front_val);

  DirectX::XMFLOAT3 w_up_val(0.f, 1.f, 0.f);
  world_up = DirectX::XMLoadFloat3(&w_up_val);

  DirectX::XMFLOAT3 w_rigth_val(1.f, 0.f, 0.f);
  world_right = DirectX::XMLoadFloat3(&w_rigth_val);
}

void Player::Update(const float dt) noexcept {
  RotateView(dt);
  Move(dt);
}

void Player::Move(const float dt) noexcept {

  if (Input::state.w) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(front_move, speed * dt));
  }
  if (Input::state.s) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(front_move, -speed * dt));
  }
  if (Input::state.a) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(right_move, -speed * dt));
  }
  if (Input::state.d) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(right_move, speed * dt));
  }
  if (Input::state.l_shift) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(world_up, -speed * dt));
  }
  if (Input::state.space) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(world_up, speed * dt));
  }
}

void Player::RotateView(const float dt) noexcept {
  float deltaMultiplier = view_sensitivity * dt;

  yaw += Input::state.mouse_delta_x * deltaMultiplier;
  pitch -= Input::state.mouse_delta_y * deltaMultiplier;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  UpdateVectors();
}

void Player::UpdateVectors() noexcept {
  // Update view vectors.
  DirectX::XMFLOAT3 new_front_view;
  new_front_view.x = cos(DirectX::XMConvertToRadians(yaw)) *
                cos(DirectX::XMConvertToRadians(pitch));
  new_front_view.y = sin(DirectX::XMConvertToRadians(pitch));
  new_front_view.z = sin(DirectX::XMConvertToRadians(yaw)) *
                cos(DirectX::XMConvertToRadians(pitch));

  DirectX::XMVECTOR v_new_front_view = DirectX::XMLoadFloat3(&new_front_view);
  front_view = DirectX::XMVector3Normalize(v_new_front_view);

  // normalize the vectors, because their length gets closer to 0 the more you
  // look up or down which results in slower movement
  right_view =
      DirectX::XMVector3Normalize(DirectX::XMVector3Cross(front_view, world_up));
  up_view = DirectX::XMVector3Normalize(
      DirectX::XMVector3Cross(right_view, front_view));

  // Update movement vectors.
  DirectX::XMFLOAT3 new_front_move;
  new_front_move.x = cos(DirectX::XMConvertToRadians(yaw));
  new_front_move.y = 0.f;
  new_front_move.z = sin(DirectX::XMConvertToRadians(yaw));

  front_move = DirectX::XMLoadFloat3(&new_front_move);

  right_move = DirectX::XMVector3Normalize(
      DirectX::XMVector3Cross(front_move, world_up));
}