#pragma once

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
  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;

  void Begin(std::size_t vertex_alloc_size = 0, std::size_t index_alloc_size = 0);

  void GenerateQuad(Vec3 right_up, Vec3 rigth_down, Vec3 left_down,
                    Vec3 left_up);
  //void GenerateCube(Vec3 color) noexcept;
  void GenerateCube(Vec3 pos, CubeColors cube_colors) noexcept;
};

