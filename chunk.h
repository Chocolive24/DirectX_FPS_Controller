#pragma once

#include <cstdint>

#include <array>
#include <memory>

enum class BlockType : std::uint8_t {
  kAir,
  kGrass,
  kDirt,
  kStone,
  kWaterSurface,
  kWaterDeep,
};

class Chunk {
public:
  static constexpr std::uint8_t kWidth = 16;
  static constexpr std::uint8_t kHeight = 16;
  static constexpr std::uint8_t kDepth = 16;
  static constexpr std::uint16_t kSize = kWidth * kHeight * kDepth; 

  Chunk() = default;
  ~Chunk() = default;

  BlockType GetBlockAt(int x, int y, int z);
  void SetBlockAt(int x, int y, int z, BlockType type);

private:
  std::array<BlockType, kSize> blocks_ = {};
};
