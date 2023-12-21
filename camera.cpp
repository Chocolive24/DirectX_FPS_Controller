#include "camera.h"
#include <iostream>

void Camera::Begin(DirectX::XMFLOAT3 start_pos) noexcept {
  position = DirectX::XMLoadFloat3(&start_pos);

  DirectX::XMFLOAT3 front_val(0.f, 0.f, -1.f);
  front = DirectX::XMLoadFloat3(&front_val);

  DirectX::XMFLOAT3 up_val(0.f, 1.f, 0.f);
  up = DirectX::XMLoadFloat3(&up_val);

  DirectX::XMFLOAT3 right_val(1.f, 0.f, 0.f);
  right = DirectX::XMLoadFloat3(&right_val);

  DirectX::XMFLOAT3 w_up_val(0.f, 1.f, 0.f);
  world_up = DirectX::XMLoadFloat3(&w_up_val);
}

void Camera::Update() noexcept { 
  Rotate();
  Move();
  auto focus_position = DirectX::XMVectorAdd(position, front);
  view_matrix = DirectX::XMMatrixLookAtRH(position, focus_position, up);
}

void Camera::Move() noexcept { 
  if (Input::w_pressed) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(front, speed * 0.016f));
  }
  if (Input::s_pressed) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(front, -speed * 0.016f));
  }
  if (Input::a_pressed) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(right, -speed * 0.016f));
  }
  if (Input::d_pressed) {
    position = DirectX::XMVectorAdd(position,
        DirectX::XMVectorScale(right, speed * 0.016f));
  }
  if (Input::l_shift_pressed) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(world_up, -speed * 0.016f));
  }
  if (Input::space_pressed) {
    position = DirectX::XMVectorAdd(
        position, DirectX::XMVectorScale(world_up, speed * 0.016f));
  }
}

void Camera::Rotate() noexcept {

float deltaMultiplier = sensitivity * 0.016f;

  yaw += Input::mouse_delta_x * deltaMultiplier;
  pitch -= Input::mouse_delta_y * deltaMultiplier;

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
  front = DirectX::XMVector3Normalize(v_new_front);

  // normalize the vectors, because their length gets closer to 0 the more you
  // look up or down which results in slower movement
  right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(front, world_up));
  up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(right, front));
}
