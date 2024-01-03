#pragma once

#include <DirectXMath.h>

#include <array>

enum class TileType {
  kNone = 0,
  kDirt,
};

class Map {
 public:
  static constexpr std::array<DirectX::XMINT3, 10> kNeighbourTiles = {
      DirectX::XMINT3(1, 0, 0), DirectX::XMINT3(-1, 0, 0),  // right, left
      DirectX::XMINT3(1, 1, 0), DirectX::XMINT3(-1, 1, 0),  // right-up, left-up
      DirectX::XMINT3(0, 2, 0), DirectX::XMINT3(0, -1, 0),  // up, down
      DirectX::XMINT3(0, 0, 1), DirectX::XMINT3(0, 0, -1),  // front, back
      DirectX::XMINT3(0, 1, 1), DirectX::XMINT3(0, 1, -1)   // front-up, back-up
  };

  static constexpr uint32_t kMapWidth = 20;
  static constexpr uint32_t kMapHeight = 20;
  static constexpr uint32_t kMapDepth = 20;
  static constexpr uint64_t kMapSize = kMapWidth * kMapHeight * kMapDepth;

  void Begin();
  float Noise2D(float x, float y);
  float FractalBrownianMotion(float x, float y, int num_octaves);

  TileType GetTileAt(int x, int y, int z);
  void SetTileAt(int x, int y, int z, TileType type);

 private:
  static constexpr int kPermutationCount = 256;

  std::array<TileType, kMapSize> map_;
  std::array<int, 2 * kPermutationCount> permutation_;

  void CreatePermutationArray() noexcept;
  DirectX::XMFLOAT2 GetConstantVector(int v) const noexcept;
  float Fade(float t) const noexcept;
  float Lerp(float t, float a1, float a2);


};
