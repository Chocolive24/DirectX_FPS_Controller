//#include "chunk.h"
//
//BlockType Chunk::GetBlockAt(int x, int y, int z) { 
//  if (x < 0 || x >= kWidth || y < 0 || y >= kHeight || z < 0 ||
//      z >= kDepth) {
//    return BlockType::kAir;
//  }
//
//  const auto index = z * kDepth * kHeight + y * kWidth + x;
//  if (index < 0 || index >= blocks_.size()) {
//    return BlockType::kAir;
//  }
//
//  return blocks_[index];
//}
//
//void Chunk::SetBlockAt(int x, int y, int z, BlockType type) {
//  const auto index = z * kDepth * kHeight + y * kWidth + x;
//
//  if (index < 0 || index >= blocks_.size()) {
//    return;
//  }
//
//  blocks_[index] = type;
//}
//
//static constexpr std::array<DirectX::XMINT3, 10> kNeighbourTiles = {
//    DirectX::XMINT3(1, 0, 0), DirectX::XMINT3(-1, 0, 0),  // right, left
//    DirectX::XMINT3(1, 1, 0), DirectX::XMINT3(-1, 1, 0),  // right-up, left-up
//    DirectX::XMINT3(0, 2, 0), DirectX::XMINT3(0, -1, 0),  // up, down
//    DirectX::XMINT3(0, 0, 1), DirectX::XMINT3(0, 0, -1),  // front, back
//    DirectX::XMINT3(0, 1, 1), DirectX::XMINT3(0, 1, -1)   // front-up, back-up
//};
//
//static constexpr auto max_limit = (std::numeric_limits<float>::max)();
//static constexpr auto lowest_limit = (std::numeric_limits<float>::lowest)();
//
//float max_pos_x = max_limit;
//float min_pos_x = lowest_limit;
//
//float max_pos_y = max_limit;
//float min_pos_y = lowest_limit;
//
//float max_pos_z = max_limit;
//float min_pos_z = lowest_limit;
//
//// Get the player position in grid space.
//const DirectX::XMINT3 normalized_pos(
//    std::floor(DirectX::XMVectorGetX(player.position()) + 0.5f),
//    std::floor(DirectX::XMVectorGetY(player.position()) + 0.5f),
//    std::floor(DirectX::XMVectorGetZ(player.position()) + 0.5f));
//
//for (const auto& neighbour : Map::kNeighbourTiles) {
//  const DirectX::XMINT3 tile_pos(normalized_pos.x + neighbour.x,
//                                 normalized_pos.y + neighbour.y,
//                                 normalized_pos.z + neighbour.z);
//
//  const auto tile = map.GetBlockAt(tile_pos.x, tile_pos.y, tile_pos.z);
//
//  if (tile != BlockType::kAir && tile != BlockType::kWaterSurface &&
//      tile != BlockType::kWaterDeep) {
//    // Look the direction of the neighbour to set the correct max pos.
//    const int x_direction =
//        (neighbour.x > 0) ? 1 : ((neighbour.x < 0) ? -1 : 0);
//    const int y_direction =
//        (neighbour.y > 0) ? 1 : ((neighbour.y < 0) ? -1 : 0);
//    const int z_direction =
//        (neighbour.z > 0) ? 1 : ((neighbour.z < 0) ? -1 : 0);
//
//    if (x_direction != 0) {
//      max_pos_x = (x_direction > 0) ? normalized_pos.x + 0.4f : max_pos_x;
//      min_pos_x = (x_direction < 0) ? normalized_pos.x - 0.4f : min_pos_x;
//    } else if (z_direction != 0) {
//      max_pos_z = (z_direction > 0) ? normalized_pos.z + 0.4f : max_pos_z;
//      min_pos_z = (z_direction < 0) ? normalized_pos.z - 0.4f : min_pos_z;
//    } else if (y_direction != 0) {
//      max_pos_y = (y_direction > 0) ? normalized_pos.y + 0.4f : max_pos_y;
//      min_pos_y = (y_direction < 0) ? normalized_pos.y - 0.4f : min_pos_y;
//    }
//  }
//}
//
//const auto tile_at_player_pos =
//    map.GetBlockAt(normalized_pos.x, normalized_pos.y, normalized_pos.z);
//
//player.is_in_water = tile_at_player_pos == BlockType::kWaterSurface ||
//                     tile_at_player_pos == BlockType::kWaterDeep;
//
//static float current_gravity;
//static ForceMode gravity_mode;
//
//current_gravity = player.is_in_water ? kWaterGravity : kGravity;
//gravity_mode = player.is_in_water ? ForceMode::kImpulse : ForceMode::kForce;
//
//if (DirectX::XMVectorGetY(player.velocity()) > -100.f) {
//  player.ApplyForce(DirectX::XMVECTOR{0.f, current_gravity, 0.f}, gravity_mode);
//}
//
//player.Update(dt_count);
//
//const auto player_pos_x = DirectX::XMVectorGetX(player.position());
//const auto player_pos_y = DirectX::XMVectorGetY(player.position());
//const auto player_pos_z = DirectX::XMVectorGetZ(player.position());
//
//if (player_pos_y <= min_pos_y) {
//  player.set_velocity(DirectX::XMVectorSetY(player.velocity(), 0.f));
//  player.is_grounded = true;
//}
//
//player.set_position(DirectX::XMVectorSetX(player.position(),
//                                          std::clamp(player_pos_x, min_pos_x,
//                                                     max_pos_x)));
//
//player.set_position(DirectX::XMVectorSetY(player.position(),
//                                          std::clamp(player_pos_y, min_pos_y,
//                                                     max_pos_y)));
//
//player.set_position(DirectX::XMVectorSetZ(player.position(),
//                                          std::clamp(player_pos_z, min_pos_z,
//                                                     max_pos_z)));