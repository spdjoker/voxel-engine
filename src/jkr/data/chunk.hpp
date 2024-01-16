#ifndef JKR_DATA_CHUNK_HPP
#define JKR_DATA_CHUNK_HPP 

#include "voxel.hpp"

class Chunk {
  static constexpr int32 CHUNK_SIZE = 16;
  static constexpr int32 VOXEL_COUNT = CHUNK_SIZE * CHUNK_SIZE;

  unsigned int vao;
  unsigned int vbo;

  voxel_t data[VOXEL_COUNT];
  int chunk_x;
  int chunk_z;

public:
  Chunk(int chunk_x, int chunk_z);

  void render();
};

#endif
