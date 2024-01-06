#include "geometry_builder.h"

void GeometryBuilder::Begin(std::size_t vertex_alloc_size,
                            std::size_t index_alloc_size) {
  vertices.reserve(vertex_alloc_size);
  indices.reserve(index_alloc_size);
}

void GeometryBuilder::GenerateQuad(Vec3 right_up, Vec3 rigth_down,
                                   Vec3 left_down, Vec3 left_up) {
  vertices.push_back({right_up, {25.f, 25.f}, {1, 0, 0}});
  vertices.push_back({rigth_down, {25.f, 0.0f}, {0, 1, 0}});
  vertices.push_back({left_down, {0.0f, 0.0f}, {0, 0, 1}});
  vertices.push_back({left_up, {0.0f, 25.f}, {0.5, 0.8, 0.5}});

  indices = {0, 1, 2, 0, 3, 2};
}

//void GeometryBuilder::GenerateCube(Vec3 color) noexcept {
//    // Create vertices.
//  constexpr int kVertexCount = 24;
//  std::vector<Vertex> cube_vertices;
//  cube_vertices.reserve(kVertexCount);
//  cube_vertices = {
//      // Front face - counterclockwise.
//      // right up
//      Vertex{Vec3{0.5f, 0.5f, 0.5f}, 
//             Vec2(1.0f, 1.0f), color},
//      // left up
//      Vertex{Vec3(-0.5f, 0.5f, 0.5f),
//             Vec2(0.0f, 1.0f),
//             color,},
//      // left down
//      Vertex{Vec3(-0.5f, -0.5f, 0.5f),
//             Vec2(0.0f, 0.0f),
//             color},
//      // right down
//      Vertex{Vec3(0.5f, -0.5f, 0.5f),
//             Vec2(1.0f, 0.0f),
//             color},
//
//      // Up face - counterclockwise.
//      // right up
//      Vertex{Vec3(0.5f, 0.5f, -0.5f),
//             Vec2(1.0f, 1.0f),
//             color},
//      // left up
//      Vertex{Vec3(-0.5f, 0.5f, -0.5f),
//             Vec2(0.0f, 1.0f),
//             color},
//      // left down
//      Vertex{Vec3(-0.5f, 0.5f, 0.5f),
//             Vec2(0.0f, 0.0f),
//             color},
//      // right down
//      Vertex{Vec3(0.5f, 0.5f, 0.5f),
//             Vec2(1.0f, 0.0f),
//             color},
//
//      // Back face - clockwise.
//      // left up
//      Vertex{Vec3(0.5f, 0.5f, -0.5f),
//             Vec2(1.0f, 1.0f),
//             color},
//      // left down
//      Vertex{Vec3(0.5f, -0.5f, -0.5f),
//          Vec2(1.0f, 0.0f),
//          color},
//      // right down
//      Vertex{Vec3(-0.5f, -0.5f, -0.5f),
//             Vec2(0.0f, 0.0f),
//             color},
//      // right up
//      Vertex{Vec3(-0.5f, 0.5f, -0.5f),
//             Vec2(0.0f, 1.0f),
//             color},
//
//      // Down face clockwise.
//      // left up
//      Vertex{Vec3(0.5f, -0.5f, -0.5f),
//             Vec2(1.0f, 1.0f), color},
//      // left down
//      Vertex{Vec3(0.5f, -0.5f, 0.5f), Vec2(1.0f, 0.0f), color},
//      // right down
//      Vertex{Vec3(-0.5f, -0.5f, 0.5f), Vec2(0.0f, 0.0f), color},
//      // right up
//      Vertex{Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f, 1.0f), color},
//
//      // Right face - counterclockwise.
//      // right up
//      Vertex{Vec3(0.5f, 0.5f, -0.5f), Vec2(1.0f, 1.0f), color},
//      // left up
//      Vertex{Vec3(0.5f, 0.5f, 0.5f), Vec2(0.0f, 1.0f), color},
//      // left down
//      Vertex{Vec3(0.5f, -0.5f, 0.5f), Vec2(0.0f, 0.0f), color},
//      // right down
//      Vertex{Vec3(0.5f, -0.5f, -0.5f), Vec2(1.0f, 0.0f), color},
//
//      // Left face - clockwise.
//      // left up
//      Vertex{Vec3(-0.5f, 0.5f, -0.5f), Vec2(0.0f, 1.0f), color},
//      // left down
//      Vertex{Vec3(-0.5f, -0.5f, -0.5f), Vec2(0.0f, 0.0f), color},
//      // right up
//      Vertex{Vec3(-0.5f, 0.5f, 0.5f), Vec2(1.0f, 1.0f), color},
//      // right down
//      Vertex{Vec3(-0.5f, -0.5f, 0.5f), Vec2(1.0f, 0.0f), color},
//  };
//
//  vertices.insert(vertices.end(), cube_vertices.begin(), cube_vertices.end());
//
//  // Create indices.
//  constexpr int kIndiceCount = 36;
//  std::vector<uint32_t> cube_indices;
//  cube_indices.reserve(kIndiceCount);
//  cube_indices = {
//      0,  1,  3,  1,  2,  3,   // Front face
//      4,  5,  7,  5,  6,  7,   // Up face.
//      8,  9,  11, 11, 9,  10,  // Back face.
//      12, 13, 15, 15, 13, 14,  // Down face.
//      16, 17, 19, 17, 18, 19,  // Right face.
//      20, 21, 22, 22, 21, 23,  // Left face.
//  };
//
//  indices.insert(indices.begin(), cube_indices.begin(), cube_indices.end());
//}

void GeometryBuilder::GenerateBlock(Vec3 pos, BlockType tile_type) noexcept {
  Vec4 color(1, 1, 1, 1);
  Vec3 scale_up(1, 1, 1);
  Vec3 scale_down(1, 1, 1);
  BlockFaceUV up_uv;
  BlockFaceUV down_uv;
  BlockFaceUV side_uv;

  switch (tile_type) {
    case BlockType::kAir:
      break;
    case BlockType::kGrass:
      up_uv = {
        .left_down = Vec2(kBlockPixelSize * kTopGrassTexPosX * kTexRatio, 
                          kBlockPixelSize * kSolidBlockTexPosY * kTexRatio),
        .left_up = Vec2(kBlockPixelSize * kTopGrassTexPosX * kTexRatio, 1),
        .right_up = Vec2(kBlockPixelSize * (kTopGrassTexPosX + 1) * kTexRatio, 1),
        .right_down = Vec2(kBlockPixelSize * (kTopGrassTexPosX + 1) * kTexRatio,
                           kBlockPixelSize * kSolidBlockTexPosY * kTexRatio)
      };
      side_uv = {
        .left_down = Vec2(kBlockPixelSize * kSideGrassTexPosX * kTexRatio, 
                          kBlockPixelSize * kSolidBlockTexPosY * kTexRatio),
        .left_up = Vec2(kBlockPixelSize * kSideGrassTexPosX * kTexRatio, 1),
        .right_up = Vec2(kBlockPixelSize * (kSideGrassTexPosX + 1) * kTexRatio, 1),
        .right_down = Vec2(kBlockPixelSize * (kSideGrassTexPosX + 1) * kTexRatio,
                           kBlockPixelSize * kSolidBlockTexPosY  * kTexRatio)
      };
      down_uv = {
        .left_down = Vec2(kBlockPixelSize * kDirtTexPosX * kTexRatio, 
                          kBlockPixelSize * kSolidBlockTexPosY  * kTexRatio),
        .left_up = Vec2(kBlockPixelSize * kDirtTexPosX * kTexRatio, 1),
        .right_up = Vec2(kBlockPixelSize * (kDirtTexPosX + 1) * kTexRatio, 1),
        .right_down = Vec2(kBlockPixelSize * (kDirtTexPosX + 1) * kTexRatio,
                           kBlockPixelSize * kSolidBlockTexPosY  * kTexRatio)
      };
      break;
    case BlockType::kDirt:
      up_uv = {
        .left_down = Vec2(kBlockPixelSize * kDirtTexPosX * kTexRatio, 
                          kBlockPixelSize * kSolidBlockTexPosY  * kTexRatio),
        .left_up = Vec2(kBlockPixelSize * kDirtTexPosX * kTexRatio, 1),
        .right_up = Vec2(kBlockPixelSize * (kDirtTexPosX + 1) * kTexRatio, 1),
        .right_down = Vec2(kBlockPixelSize * (kDirtTexPosX + 1) * kTexRatio,
                           kBlockPixelSize * kSolidBlockTexPosY  * kTexRatio)};
      down_uv = up_uv;
      side_uv = up_uv;
      break;
    case BlockType::kStone:
      up_uv = {
        .left_down = Vec2(kBlockPixelSize * kStoneTexPosX * kTexRatio, 
                          kBlockPixelSize * kSolidBlockTexPosY  * kTexRatio),
        .left_up = Vec2(kBlockPixelSize * kStoneTexPosX * kTexRatio, 1),
        .right_up = Vec2(kBlockPixelSize * (kStoneTexPosX + 1) * kTexRatio, 1),
        .right_down = Vec2(kBlockPixelSize * (kStoneTexPosX + 1) * kTexRatio,
                           kBlockPixelSize * kSolidBlockTexPosY  * kTexRatio)};
      down_uv = up_uv;
      side_uv = up_uv;
      break;
    case BlockType::kWaterSurface:
      color = Vec4(1, 1, 1, 0.8f);
      scale_up = Vec3(1.f, 0.8f, 1.f);

      up_uv = {
        .left_down = Vec2(kBlockPixelSize * kWaterTexPosX * kTexRatio,
                          kBlockPixelSize * kWaterTexPosY * kTexRatio),
        .left_up = Vec2(kBlockPixelSize * kWaterTexPosX * kTexRatio,
                        kBlockPixelSize * (kWaterTexPosY + 1) * kTexRatio),
        .right_up = Vec2(kBlockPixelSize * (kWaterTexPosX + 1) * kTexRatio,
                         kBlockPixelSize * (kWaterTexPosY + 1) * kTexRatio),
        .right_down = Vec2(kBlockPixelSize * (kWaterTexPosX + 1) * kTexRatio,
                           kBlockPixelSize * kWaterTexPosY * kTexRatio)
      };
      down_uv = up_uv;
      side_uv = up_uv;
      break;
    case BlockType::kWaterDeep:
      color = Vec4(1, 1, 1, 0.1f);
      up_uv = {
        .left_down = Vec2(kBlockPixelSize * kWaterTexPosX * kTexRatio,
                          kBlockPixelSize * kWaterTexPosY * kTexRatio),
        .left_up = Vec2(kBlockPixelSize * kWaterTexPosX * kTexRatio,
                        kBlockPixelSize * (kWaterTexPosY + 1) *kTexRatio),
        .right_up = Vec2(kBlockPixelSize * (kWaterTexPosX + 1) * kTexRatio,
                         kBlockPixelSize * (kWaterTexPosY + 1) * kTexRatio),
        .right_down = Vec2(kBlockPixelSize * (kWaterTexPosX + 1) * kTexRatio,
                           kBlockPixelSize * kWaterTexPosY * kTexRatio)
      };
      down_uv = up_uv;
      side_uv = up_uv;
      break;
    default:
      break;
  }

  const uint32_t indice_offset = vertices.size();

  // Create vertices.
  constexpr int kVertexCount = 24;
  std::vector<Vertex> cube_vertices;
  cube_vertices.reserve(kVertexCount);
  cube_vertices = {
    // Front face - counterclockwise.
    // right up
    Vertex{Vec3{0.5f * scale_up.x, 0.5f * scale_up.y, 0.5f * scale_up.z} + pos,
           side_uv.right_up, color},
    // left up
    Vertex{Vec3{-0.5f * scale_up.x, 0.5f * scale_up.y, 0.5f * scale_up.z} + pos,
           side_uv.left_up, color},
    // left down
    Vertex{Vec3{-0.5f * scale_down.x, -0.5f * scale_down.y, 0.5f * scale_down.z} + pos,
           side_uv.left_down, color},
    // right down
    Vertex{Vec3{0.5f * scale_down.x, -0.5f * scale_down.y, 0.5f * scale_down.z} + pos,
           side_uv.right_down, color},

    // Up face - counterclockwise.
    // right up
    Vertex{Vec3{0.5f * scale_up.x, 0.5f * scale_up.y, -0.5f * scale_up.z} + pos,
          up_uv.right_up, color},
    // left up
    Vertex{Vec3{-0.5f * scale_up.x, 0.5f * scale_up.y, -0.5f * scale_up.z} + pos,
          up_uv.left_up, color},
    // left down
    Vertex{Vec3{-0.5f * scale_up.x, 0.5f * scale_up.y, 0.5f * scale_up.z} + pos,
          up_uv.left_down, color},
    // right down
    Vertex{Vec3{0.5f * scale_up.x, 0.5f * scale_up.y, 0.5f * scale_up.z} + pos,
          up_uv.right_down, color},

    // Back face - clockwise.
    // left up
    Vertex{Vec3{0.5f * scale_up.x, 0.5f * scale_up.y, -0.5f * scale_up.z} + pos,
          side_uv.right_up, color},
    // left down
    Vertex{Vec3{0.5f * scale_down.x, -0.5f * scale_down.y, -0.5f * scale_down.z} + pos,
             side_uv.right_down, color},
    // right down
    Vertex{Vec3{-0.5f * scale_down.x, -0.5f * scale_down.y, -0.5f * scale_down.z} + pos,
             side_uv.left_down, color},
    // right up
    Vertex{Vec3{-0.5f * scale_up.x, 0.5f * scale_up.y, -0.5f * scale_up.z} + pos,
          side_uv.left_up, color},

    // Down face clockwise.
    // left up
    Vertex{Vec3{0.5f * scale_down.x, -0.5f * scale_down.y, -0.5f * scale_down.z} + pos,
             down_uv.right_up, color},
    // left down
    Vertex{Vec3{0.5f * scale_down.x, -0.5f * scale_down.y, 0.5f * scale_down.z} + pos,
          down_uv.right_down, color},
    // right down
    Vertex{Vec3{-0.5f * scale_down.x, -0.5f * scale_down.y, 0.5f * scale_down.z} + pos,
             down_uv.left_down, color},
    // right up
    Vertex{Vec3{-0.5f * scale_down.x, -0.5f * scale_down.y, -0.5f * scale_down.z} + pos,
             down_uv.left_up, color},

    // Right face - counterclockwise.
    // right up
    Vertex{Vec3{0.5f * scale_up.x, 0.5f * scale_up.y, -0.5f * scale_up.z} + pos,
          side_uv.right_up, color},
    // left up
    Vertex{Vec3{0.5f * scale_up.x, 0.5f * scale_up.y, 0.5f * scale_up.z} + pos,
          side_uv.left_up, color},
    // left down
    Vertex{Vec3{0.5f * scale_down.x, -0.5f * scale_down.y, 0.5f * scale_down.z} + pos,
          side_uv.left_down, color},
    // right down
    Vertex{Vec3{0.5f * scale_down.x, -0.5f * scale_down.y, -0.5f * scale_down.z} + pos,
             side_uv.right_down, color},

    // Left face - clockwise.
    // left up
    Vertex{Vec3{-0.5f * scale_up.x, 0.5f * scale_up.y, -0.5f * scale_up.z} + pos,
          side_uv.left_up, color},
    // left down
    Vertex{Vec3{-0.5f * scale_down.x, -0.5f * scale_down.y, -0.5f * scale_down.z} + pos,
             side_uv.left_down, color},
    // right up
    Vertex{Vec3{-0.5f * scale_up.x, 0.5f * scale_up.y, 0.5f * scale_up.z} + pos,
          side_uv.right_up, color},
    // right down
      Vertex{Vec3{-0.5f * scale_down.x, -0.5f * scale_down.y, 0.5f * scale_down.z} + pos,
             side_uv.right_down, color}
  };

  for (const auto& vertex : cube_vertices) {
    vertices.push_back(vertex);
  }

  // Create indices.
  constexpr int kIndiceCount = 36;
  std::vector<uint32_t> cube_indices;
  cube_indices.reserve(kIndiceCount);
  cube_indices = {
      indice_offset + 0,  indice_offset + 1,  indice_offset + 3,  
      indice_offset + 1,  indice_offset + 2,  indice_offset + 3,   // Front face

      indice_offset + 4,  indice_offset + 5,  indice_offset + 7,  
      indice_offset + 5,  indice_offset + 6,  indice_offset + 7,   // Up face.

      indice_offset + 8,  indice_offset + 9,  indice_offset + 11, 
      indice_offset + 11, indice_offset + 9,  indice_offset + 10,  // Back face.

      indice_offset + 12, indice_offset + 13, indice_offset + 15, 
      indice_offset + 15, indice_offset + 13, indice_offset + 14,  // Down face.

      indice_offset + 16, indice_offset + 17, indice_offset + 19, 
      indice_offset + 17, indice_offset + 18, indice_offset + 19,  // Right face.

      indice_offset + 20, indice_offset + 21, indice_offset + 22, 
      indice_offset + 22, indice_offset + 21, indice_offset + 23,  // Left face.
  };

  for (const auto& indice : cube_indices) {
    indices.push_back(indice);
  }
}