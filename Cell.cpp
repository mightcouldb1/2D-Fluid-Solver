#include "Cell.h"
#include <cstddef>

Cell2D::Cell2D()
  : _pressure(0.0f),
    _isLiquid(false),
    _hasAllNeighbors(false)
{
  // Initialize array data members.
  for (unsigned i = 0; i < C2D_DIM; ++i) {
    _velocity[i] = 0.0f;
    _stagedVelocity[i] = 0.0f;
  }
  for (unsigned i = 0; i < C2D_NEI; ++i) {
    _neighbor[i] = NULL;
  }
}
