#pragma once

#include <DirectXMath.h>

#include <array>
#include <vector>

enum class BlockType {
  kAir,
  kGrass,
  kDirt,
  kStone,
  kWaterSurface,
  kWaterDeep,
};

class Map {
 public:
  static constexpr uint32_t kMapWidth = 128;
  static constexpr uint32_t kMapHeight = 128;
  static constexpr uint32_t kMapDepth = 128;
  static constexpr uint64_t kMapSize = kMapWidth * kMapHeight * kMapDepth;

  static constexpr std::array<DirectX::XMINT3, 10> kNeighbourTiles = {
      DirectX::XMINT3(1, 0, 0), DirectX::XMINT3(-1, 0, 0),  // right, left
      DirectX::XMINT3(1, 1, 0), DirectX::XMINT3(-1, 1, 0),  // right-up, left-up
      DirectX::XMINT3(0, 2, 0), DirectX::XMINT3(0, -1, 0),  // up, down
      DirectX::XMINT3(0, 0, 1), DirectX::XMINT3(0, 0, -1),  // front, back
      DirectX::XMINT3(0, 1, 1), DirectX::XMINT3(0, 1, -1)   // front-up, back-up
  };

  void Begin();
  float Noise2D(float x, float y);

  /*
  * @brief GenerateTerrain is a method that creates all the type of block in the map 
  * using 2D Perlin Noise with Fractal Brownian Motion to apply a smooth randomness.
  */
  void GenerateTerrain(float amplitude, float frequency, std::uint8_t octaves);

  BlockType GetBlockAt(int x, int y, int z);
  BlockType GetBlockAtIndex(int index) { 
    if (index < 0 || index >= map_.size()) {
      return BlockType::kAir;
    }

    return map_[index];
  }
  void SetBlockAt(int x, int y, int z, BlockType type);

 private:
  std::vector<BlockType> map_;

  static constexpr std::uint16_t kPermutationCount = 256;
  static constexpr std::array<std::uint8_t, 2 * kPermutationCount> permutation_ = {
      151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,
      225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190,
      6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117,
      35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136,
      171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158,
      231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,  46,
      245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209,
      76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159, 86,
      164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123, 5,
      202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,
      58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,
      154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253,
      19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
      228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,
      145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157, 184,
      84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,
      222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156,
      180, 
      151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233,
      7,   225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,
      190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203,
      117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125,
      136, 171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146,
      158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,
      46,  245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,
      209, 76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159,
      86,  164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123,
      5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,
      16,  58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,
      44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,
      253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246,
      97,  228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,
      51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157,
      184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205,
      93,  222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,
      156, 180
  };

  void CreatePermutationArray() noexcept;
  DirectX::XMFLOAT2 GetConstantVector(int v) const noexcept;
  float Fade(float t) const noexcept;
  float Lerp(float t, float a1, float a2);
  double Grad(int hash, double x, double y);
};
