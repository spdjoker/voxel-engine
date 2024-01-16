#include "chunk.hpp"
#include "jkr/graphics/objects/vao.hpp"
#include "jkr/graphics/objects/vbo.hpp"
#include "jkr/graphics/objects/ebo.hpp"
#include <vector>

Chunk::Chunk(int chunk_x, int chunk_z)
: chunk_x(chunk_x), chunk_z(chunk_z) {
  for (int i = 0; i < VOXEL_COUNT; i++)
    data[i] = voxel::PRIMAL_RED;

  std::vector<uint32> data;
}

void render() {
  
}
