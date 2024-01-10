#include "ParticleSystem.h"

void ParticleSystem::Begin(int max_particles, float spawn_time) {
  positions_.reserve(max_particles);
  velocities_.reserve(max_particles);
  life_times_.reserve(max_particles);
  spawn_time_ = spawn_time;
}

void ParticleSystem::Update(float dt) {
  if (elapsed_time_ >= spawn_time_) {
    //SpawnParticle(DirectX::XMFLOAT3(0.f, 0.f, 0.f),
    //              DirectX::XMFLOAT3(0.f, 1.f, 0.f), 2.f);
    elapsed_time_ = 0.f;
  }

  elapsed_time_ += dt;

  for (std::size_t i = 0; i < positions_.size(); i++) {
    if (life_times_[i] <= 0.f) {
      DestroyParticle(i);
      continue;
    }

    positions_[i].x += velocities_[i].x * dt;
    positions_[i].y += velocities_[i].y * dt;
    positions_[i].z += velocities_[i].z * dt;

    life_times_[i] -= dt;
  }
}

void ParticleSystem::SpawnParticle(DirectX::XMFLOAT3 pos,
                                   DirectX::XMFLOAT3 vel, float life_time) {
  positions_.push_back(pos);
  velocities_.push_back(vel);
  life_times_.push_back(life_time);
}

void ParticleSystem::DestroyParticle(int index) { 
  positions_.erase(positions_.begin() + index);
  velocities_.erase(velocities_.begin() + index);
  life_times_.erase(life_times_.begin() + index);
}
