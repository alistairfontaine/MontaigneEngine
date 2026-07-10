#ifndef SPATIAL_GRID_HPP
#define SPATIAL_GRID_HPP

#include <map>
#include <vector>
#include <tuple>
#include <cmath>
#include "Entity.hpp"

struct SpatialGrid {
    float cellSize;

    // Maps a 3D grid cell coordinate tuple (x, y, z) to a list of entity pointers inside it
    std::map<std::tuple<int, int, int>, std::vector<Entity*>> cells;

    SpatialGrid(float size = 2.0f) : cellSize(size) {}

    // Converts a floating world position vector into raw integer grid indices
    std::tuple<int, int, int> Quantize(const Vec3& pos) const {
        return {
            static_cast<int>(std::floor(pos.x / cellSize)),
            static_cast<int>(std::floor(pos.y / cellSize)),
            static_cast<int>(std::floor(pos.z / cellSize))
        };
    }

    void Clear() {
        cells.clear();
    }

    void Insert(Entity* entity) {
        if (!entity) return;
        auto cellCoord = Quantize(entity->position);
        cells[cellCoord].push_back(entity);
    }

    // Fetches all entity pointers inside the target entity's cell and its immediate neighbors
    std::vector<Entity*> GetPotentialColliders(Entity* entity) const {
        std::vector<Entity*> potentials;
        if (!entity) return potentials;

        auto centerCell = Quantize(entity->position);
        int cx = std::get<0>(centerCell);
        int cy = std::get<1>(centerCell);
        int cz = std::get<2>(centerCell);

        // Sweep a 3x3x3 cell neighborhood mask
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                for (int z = -1; z <= 1; ++z) {
                    auto neighborKey = std::make_tuple(cx + x, cy + y, cz + z);
                    auto it = cells.find(neighborKey);
                    if (it != cells.end()) {
                        for (Entity* e : it->second) {
                            if (e->id != entity->id) { // Don't match self
                                potentials.push_back(e);
                            }
                        }
                    }
                }
            }
        }
        return potentials;
    }
};

#endif // SPATIAL_GRID_HPP
