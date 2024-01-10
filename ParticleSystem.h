#pragma once

#include <DirectXMath.h>

#include <vector>

// struct Particle {
//  float3 pos,
//  float3 vel,
//  float life_time;

// SpawnParticle(Particle, spawn_time);

class ParticleSystem {
public:
  

  void Begin(int max_particles, float spawn_time);
  void Update(float dt);
  void SpawnParticle(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 vel, float life_time);
  void DestroyParticle(int index);

  [[nodiscard]] const std::vector<DirectX::XMFLOAT3> positions() const noexcept {
    return positions_;
  }

private:
  // GeometryBuilder geometry_builder_;
  std::vector<DirectX::XMFLOAT3> positions_;
  std::vector<DirectX::XMFLOAT3> velocities_;
  std::vector<float> life_times_;
  float spawn_time_ = 0.f;
  float elapsed_time_ = 0.f;
};