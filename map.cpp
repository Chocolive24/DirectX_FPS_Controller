#include "map.h"

TileType Map::GetTileAt(int x, int y, int z) {
  if (x < 0 || x >= kMapWidth || y < 0 || y >= kMapHeight || 
      z < 0 ||z >= kMapDepth) {
    return TileType::kNone;
  }

  const auto index = z * kMapDepth * kMapHeight + y * kMapWidth + x;
  if (index < 0 || index >= map_.size()) {
    return TileType::kNone;
  }

  return map_[index];
}

void Map::SetTileAt(int x, int y, int z, TileType type) {
  const auto index = z * kMapDepth * kMapHeight + y * kMapWidth + x;
  if (index < 0 || index >= map_.size()) {
    return;
  }

  map_[index] = type;
}
