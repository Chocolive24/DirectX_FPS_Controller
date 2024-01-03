#pragma once

#include <vector>

struct Vec2 {
  float x = 0, y = 0;
};

struct Vec3 {
  float x = 0, y = 0, z = 0;

  Vec3 operator+(Vec3 v) { return Vec3{x + v.x, y + v.y, z + v.z}; }
};

struct Vertex {
  Vec3 position;
  Vec2 uv;
  Vec3 color;
};

struct CubeColors {
  Vec3 front_color;
  Vec3 top_color;
  Vec3 back_color;
  Vec3 bottom_color;
  Vec3 right_color;
  Vec3 left_color;
};

class GeometryBuilder {
public:
  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;

  void GenerateQuad(Vec3 right_up, Vec3 rigth_down, Vec3 left_down,
                    Vec3 left_up);
  //void GenerateCube(Vec3 color) noexcept;
  void GenerateCube(Vec3 pos, CubeColors cube_colors) noexcept;
};

