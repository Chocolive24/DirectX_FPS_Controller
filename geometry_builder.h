#pragma once

#include "map.h"

#include <vector>

struct Vec2 {
  float x = 0, y = 0;
};

struct Vec3 {
  float x = 0, y = 0, z = 0;

  Vec3 operator+(Vec3 v) { return Vec3{x + v.x, y + v.y, z + v.z}; }
};

struct Vec4 {
  float x = 0, y = 0, z = 0, w = 0;

  Vec4 operator+(Vec4 v) { return Vec4{x + v.x, y + v.y, z + v.z, w + v.w}; }
};

struct Vertex {
  Vec3 position;
  Vec2 uv;
  Vec4 color;
};

struct BlockFaceUV {
  Vec2 left_down = Vec2(0, 0);
  Vec2 left_up = Vec2(0, 1);
  Vec2 right_up = Vec2(1, 1);
  Vec2 right_down = Vec2(1, 0);
};

struct CubeColors {
  Vec4 front_color;
  Vec4 top_color;
  Vec4 back_color;
  Vec4 bottom_color;
  Vec4 right_color;
  Vec4 left_color;
};

class GeometryBuilder {
public:
  static constexpr std::uint8_t kBlockPixelSize = 16;
  static constexpr std::uint16_t kTextureSize = 256;
  static constexpr float kTexRatio = 1.f / kTextureSize;

  static constexpr std::uint8_t kTopGrassTexPosX = 0;
  static constexpr std::uint8_t kSideGrassTexPosX = 1;
  static constexpr std::uint8_t kDirtTexPosX = 2;
  static constexpr std::uint8_t kStoneTexPosX = 3;
  static constexpr std::uint8_t kSolidBlockTexPosY = 15;

  static constexpr std::uint8_t kWaterTexPosX = 0;
  static constexpr std::uint8_t kWaterTexPosY = 0;

  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;

  void Begin(std::size_t vertex_alloc_size = 0, std::size_t index_alloc_size = 0);

  void GenerateQuad(Vec3 right_up, Vec3 rigth_down, Vec3 left_down,
                    Vec3 left_up);
  //void GenerateCube(Vec3 color) noexcept;
  void GenerateBlock(Vec3 pos, BlockType tile_type) noexcept;
};

