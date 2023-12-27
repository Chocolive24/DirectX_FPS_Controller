#include "camera.h"
#include <iostream>

void Camera::Begin(DirectX::XMFLOAT3 start_pos) noexcept {
  position = DirectX::XMLoadFloat3(&start_pos);

  DirectX::XMFLOAT3 front_val(0.f, 0.f, -1.f);
  front_dir = DirectX::XMLoadFloat3(&front_val);

  DirectX::XMFLOAT3 up_val(0.f, 1.f, 0.f);
  up_dir = DirectX::XMLoadFloat3(&up_val);

  DirectX::XMFLOAT3 right_val(1.f, 0.f, 0.f);
  right_dir = DirectX::XMLoadFloat3(&right_val);

  DirectX::XMFLOAT3 w_up_val(0.f, 1.f, 0.f);
  world_up = DirectX::XMLoadFloat3(&w_up_val);
}

void Camera::Update(const float dt) noexcept { 
  Rotate(dt);
  //Move(dt);
  const auto focus_position = DirectX::XMVectorAdd(position, front_dir);
  view_matrix = DirectX::XMMatrixLookAtRH(position, focus_position, up_dir);
}

void Camera::Move(const float dt) noexcept { 
  if (Input::state.w) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(front_move, speed * dt));
  }
  if (Input::state.s) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(front_move, -speed * dt));
  }
  if (Input::state.a) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(right_move, -speed * dt));
  }
  if (Input::state.d) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(right_move, speed * dt));
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

void Camera::Rotate(const float dt) noexcept {

  float deltaMultiplier = sensitivity * dt;

  yaw += Input::state.mouse_delta_x * deltaMultiplier;
  pitch -= Input::state.mouse_delta_y * deltaMultiplier;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;
  
  UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() noexcept {
  DirectX::XMFLOAT3 new_front;
  new_front.x = cos(DirectX::XMConvertToRadians(yaw)) * 
                cos(DirectX::XMConvertToRadians(pitch));
  new_front.y = sin(DirectX::XMConvertToRadians(pitch));
  new_front.z = sin(DirectX::XMConvertToRadians(yaw)) * 
                cos(DirectX::XMConvertToRadians(pitch));

  DirectX::XMVECTOR v_new_front = DirectX::XMLoadFloat3(&new_front);
  front_dir = DirectX::XMVector3Normalize(v_new_front);

  DirectX::XMFLOAT3 new_front_move(new_front.x, 0, new_front.z);
  front_move = DirectX::XMLoadFloat3(&new_front_move);

  // normalize the vectors, because their length gets closer to 0 the more you
  // look up or down which results in slower movement
  right_dir = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(front_dir, world_up));
  up_dir = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(right_dir, front_dir));

  DirectX::XMFLOAT3 new_rigth_move(DirectX::XMVectorGetX(right_dir), 0,
                                   DirectX::XMVectorGetZ(right_dir));
  right_move = DirectX::XMLoadFloat3(&new_rigth_move);
}
