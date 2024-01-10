#include "map.h"

#include <cmath>
#include <random>
#include <iostream>

void Map::Begin() { 
    map_.resize(kMapSize, BlockType::kAir);
    //CreatePermutationArray(); 
}

float Map::Noise2D(float x, float y) {
  int x_int = x;
  int y_int = y;

  float xf = x - x_int;
  float yf = y - y_int;

  const auto top_right_val = DirectX::XMFLOAT2(xf - 1.0, yf - 1.0);
  const auto top_left_val = DirectX::XMFLOAT2(xf, yf - 1.0);
  const auto bottom_right_val = DirectX::XMFLOAT2(xf - 1.0, yf);
  const auto bottom_left_val = DirectX::XMFLOAT2(xf, yf);
  
  const auto top_right = DirectX::XMLoadFloat2(&top_right_val);
  const auto top_left = DirectX::XMLoadFloat2(&top_left_val);
  const auto bottom_right = DirectX::XMLoadFloat2(&bottom_right_val);
  const auto bottom_left = DirectX::XMLoadFloat2(&bottom_left_val);

  // Select a value from the permutation array for each of the 4 corners
  const auto value_top_right = permutation_[permutation_[x_int + 1] + y_int + 1];
  const auto value_top_left = permutation_[permutation_[x_int] + y_int + 1];
  const auto value_bottom_right = permutation_[permutation_[x_int + 1] + y_int];
  const auto value_bottom_left = permutation_[permutation_[x_int] + y_int];

  const auto const_v_t_r = GetConstantVector(value_top_right);
  const auto const_v_t_l = GetConstantVector(value_top_left);
  const auto const_v_b_r = GetConstantVector(value_bottom_right);
  const auto const_v_b_l = GetConstantVector(value_bottom_left);

  const auto const_top_right = DirectX::XMLoadFloat2(&const_v_t_r);
  const auto const_top_left = DirectX::XMLoadFloat2(&const_v_t_l);
  const auto const_bottom_right = DirectX::XMLoadFloat2(&const_v_b_r);
  const auto const_bottom_left = DirectX::XMLoadFloat2(&const_v_b_l);

  const float dot_top_right = DirectX::XMVectorGetX(
      DirectX::XMVector2Dot(top_right, const_top_right));
  const float dot_top_left =
      DirectX::XMVectorGetX(DirectX::XMVector2Dot(top_left, const_top_left));
  const float dot_bottom_right = DirectX::XMVectorGetX(DirectX::XMVector2Dot(
      bottom_right, const_bottom_right));
  const float dot_bottom_left = DirectX::XMVectorGetX(DirectX::XMVector2Dot(
      bottom_left, const_bottom_left));

  const float u = Fade(xf);
  const float v = Fade(yf);

  //int A = permutation_[x_int] + y_int;
  //int B = permutation_[x_int + 1] + y_int;

  //return Lerp(v, 
  //            Lerp(u, Grad(permutation_[A], x, y), 
  //                    Grad(permutation_[B], x - 1, y)),
  //            Lerp(u, Grad(permutation_[A + 1], x, y - 1),
  //                    Grad(permutation_[B + 1], x - 1, y - 1)));
  //  
   
  return Lerp(u,
              Lerp(v, dot_bottom_left, dot_top_left),
              Lerp(v, dot_bottom_right, dot_top_right));
}

void Map::CreatePermutationArray() noexcept { 
  //// Insert numbers from 0 to 255.
  //for (int i = 0; i < kPermutationCount; i++) {
  //  permutation_[i] = i;
  //}

  //// Shuffle the permuation array.
  //std::random_device rd;
  //std::mt19937 mt(rd());

  //for (int i = kPermutationCount - 1; i > 0; i--) {
  //  std::uniform_int_distribution<int> distribution(0, i - 1);
  //  int index = distribution(mt);
  //  std::swap(permutation_[i], permutation_[index]);
  //}

  //// Add 256 more random values from the range 0 to 255.
  //for (int i = 0; i < kPermutationCount; i++) {
  //  permutation_[kPermutationCount + i] = permutation_[i];
  //}
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

double Map::Grad(int hash, double x, double y) {
  int h = hash & 7;
  double u = h < 4 ? x : y;
  double v = h < 4 ? y : x;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void Map::GenerateTerrain(float amplitude, float frequency, std::uint8_t octaves) {
  const auto base_ampl = amplitude, base_freq = frequency;
  for (int z = 0; z < kMapDepth; z++) {
    for (int y = 0; y < kMapHeight; y++) {
      for (int x = 0; x < kMapWidth; x++) {
        float result = 0.0f;
        amplitude = base_ampl;
        frequency = base_freq;

        for (int octave = 0; octave < octaves; octave++) {
          float n = amplitude * Noise2D(x * frequency, z * frequency);

          result += n;

          amplitude *= 0.5f;
          frequency *= 2.0f;
        }

        static constexpr float base_surface = kMapHeight * 0.5f - 4;

        float surface = base_surface + result * 50; // 50

        static constexpr float water_level = 35; //35

        if (y < surface) {
          if (y < surface - 3) {
            SetBlockAt(x, y, z, BlockType::kStone);
          } 
          else if (y < surface - 1) {
            SetBlockAt(x, y, z, BlockType::kDirt);
          }
          else {
            SetBlockAt(x, y, z, BlockType::kGrass);
          }
        } 
        else if (y < water_level) {
          if (y == water_level - 1) {
            SetBlockAt(x, y, z, BlockType::kWaterSurface);
          } 
          else {
            SetBlockAt(x, y, z, BlockType::kWaterDeep);
          } 
          // Set all the dirt and grass downside the water to stone.
          // It's a bit stupid but it's working for now.
          if (GetBlockAt(x, y - 1, z) == BlockType::kGrass) {
            SetBlockAt(x, y - 1, z, BlockType::kStone);
            SetBlockAt(x, y - 2, z, BlockType::kStone);
            SetBlockAt(x, y - 3, z, BlockType::kStone);
          }
         
        }
        else {
          SetBlockAt(x, y, z, BlockType::kAir);
        }
      }
    }
  }
}

BlockType Map::GetBlockAt(int x, int y, int z) {
  if (x < 0 || x >= kMapWidth || y < 0 || y >= kMapHeight || 
      z < 0 || z >= kMapDepth) {
    return BlockType::kAir;
  }

  const auto index = z * kMapDepth * kMapHeight + y * kMapWidth + x;
  if (index < 0 || index >= map_.size()) {
    return BlockType::kAir;
  }

  return map_[index];
}

void Map::SetBlockAt(int x, int y, int z, BlockType type) {
  const auto index = z * kMapDepth * kMapHeight + y * kMapWidth + x;
  if (index < 0 || index >= map_.size()) {
    return;
  }

  map_[index] = type;
}