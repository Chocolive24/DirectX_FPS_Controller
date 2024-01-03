#include "map.h"

#include <cmath>
#include <random>

void Map::Begin() { CreatePermutationArray(); }

float Map::Noise2D(float x, float y) {
  int floored_x = static_cast<int>(std::floor(x)) & 255;
  int floored_y = static_cast<int>(std::floor(y)) & 255;

  float xf = x - std::floor(x);
  float yf = y - std::floor(y);

  const auto top_right_val = DirectX::XMFLOAT2(xf - 1.0, yf - 1.0);
  const auto top_left_val = DirectX::XMFLOAT2(xf, yf - 1.0);
  const auto bottom_right_val = DirectX::XMFLOAT2(xf - 1.0, yf);
  const auto bottom_left_val = DirectX::XMFLOAT2(xf, yf);
  
  const auto top_right = DirectX::XMLoadFloat2(&top_right_val);
  const auto top_left = DirectX::XMLoadFloat2(&top_left_val);
  const auto bottom_right = DirectX::XMLoadFloat2(&bottom_right_val);
  const auto bottom_left = DirectX::XMLoadFloat2(&bottom_left_val);

  // Select a value from the permutation array for each of the 4 corners
  const auto value_top_right = permutation_[permutation_[floored_x + 1] + floored_y + 1];
  const auto value_top_left = permutation_[permutation_[floored_x] + floored_y + 1];
  const auto value_bottom_right = permutation_[permutation_[floored_x + 1] + floored_y];
  const auto value_bottom_left = permutation_[permutation_[floored_x] + floored_y];

  const auto const_v_t_r = GetConstantVector(value_top_right);
  const auto const_v_t_l = GetConstantVector(value_top_left);
  const auto const_v_b_r = GetConstantVector(value_bottom_right);
  const auto const_v_b_l = GetConstantVector(value_bottom_left);

  const auto const_top_right = DirectX::XMLoadFloat2(&const_v_t_r);
  const auto const_top_left = DirectX::XMLoadFloat2(&const_v_t_l);
  const auto const_bottom_right = DirectX::XMLoadFloat2(&const_v_b_r);
  const auto const_bottom_left = DirectX::XMLoadFloat2(&const_v_b_l);

  const float dot_top_right = DirectX::XMVectorGetX(DirectX::XMVector2Dot(top_right, const_top_right));
  const float dot_top_left =
      DirectX::XMVectorGetX(DirectX::XMVector2Dot(top_left, const_top_left));
  const float dot_bottom_right = DirectX::XMVectorGetX(DirectX::XMVector2Dot(
      bottom_right, const_bottom_right));
  const float dot_bottom_left = DirectX::XMVectorGetX(DirectX::XMVector2Dot(
      bottom_left, const_bottom_left));

  const float u = Fade(xf);
  const float v = Fade(yf);

  return Lerp(u,
              Lerp(v, dot_bottom_left, dot_top_left),
              Lerp(v, dot_bottom_right, dot_top_right));
}

void Map::CreatePermutationArray() noexcept { 
  // Insert numbers from 0 to 255.
  for (int i = 0; i < kPermutationCount; i++) {
    permutation_[i] = i;
  }

  // Shuffle the permuation array.
  std::random_device rd;
  std::mt19937 mt(rd());

  for (int i = kPermutationCount - 1; i > 0; i--) {
    std::uniform_int_distribution<int> distribution(0, i - 1);
    int index = distribution(mt);
    std::swap(permutation_[i], permutation_[index]);
  }

  // Add 256 more random values from the range 0 to 255.
  for (int i = 0; i < kPermutationCount; i++) {
    permutation_[kPermutationCount + i] = permutation_[i];
  }
}

DirectX::XMFLOAT2 Map::GetConstantVector(int v) const noexcept {
  // v is the value from the permutation table.
  const auto h = v & 3;
  switch (h) {
    case 0:
      return DirectX::XMFLOAT2(1.0, 1.0);
    case 1:
      return DirectX::XMFLOAT2(-1.0, 1.0);
    case 2:
      return DirectX::XMFLOAT2(-1.0, -1.0);
    default:
      return DirectX::XMFLOAT2(1.0, -1.0);
  }
}

float Map::Fade(float t) const noexcept {
  return ((6 * t - 15) * t + 10) * t * t * t;
}

float Map::Lerp(float t, float a1, float a2) { 
    return a1 + t * (a2 - a1); 
}

float Map::FractalBrownianMotion(float x, float y, int num_octaves) {
  float result = 0.0f;
  float amplitude = 1.0f;
  float frequency = 0.005f;

  for (int octave = 0; octave < num_octaves; octave++) {
    float n = amplitude * Noise2D(x * frequency, y * frequency);
    
    result += n;

    amplitude *= 0.5f;
    frequency *= 2.0f;
  }

  // Transform the range to [0.0, 1.0], supposing that the range of Noise2D is
  // [-1.0, 1.0]
  result += 1.0;
  result *= 0.5;

  return result;
}

TileType Map::GetTileAt(int x, int y, int z) {
  if (x < 0 || x >= kMapWidth || y < 0 || y >= kMapHeight || 
      z < 0 ||z >= kMapDepth) {
    return TileType::kNone;
  }

  const auto index = z * kMapDepth * kMapHeight + y * kMapWidth + x;
  if (index < 0 || index >= map_.size()) {
    return TileType::kNone;
  }

  return map_[index];
}

void Map::SetTileAt(int x, int y, int z, TileType type) {
  const auto index = z * kMapDepth * kMapHeight + y * kMapWidth + x;
  if (index < 0 || index >= map_.size()) {
    return;
  }

  map_[index] = type;
}


