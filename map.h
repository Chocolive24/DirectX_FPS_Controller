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

  static constexpr uint8_t kMapWidth = 10;
  static constexpr uint8_t kMapHeight = 2;
  static constexpr uint8_t kMapDepth = 10;
  static constexpr uint8_t kMapSize = kMapWidth * kMapHeight * kMapDepth;


  TileType GetTileAt(int x, int y, int z);
  void SetTileAt(int x, int y, int z, TileType type);

 private:
  inline static std::array<TileType, kMapSize> map_;
};
