#ifndef JKR_DATA_VOXEL_HPP
#define JKR_DATA_VOXEL_HPP

#include "jkr/types/common.hpp"

using voxel_t = int8;

namespace voxel {
  enum id : voxel_t {
    EMPTY,
    PRIMAL_RED,
    PRIMAL_GREEN,
    PRIMAL_BLUE,
    PRIMAL_WHITE
  };
};

#endif
