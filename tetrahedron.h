#include "platonic_solid.h"

class Tetrahedron : public PlatonicSolid
{
public:
  Tetrahedron() : PlatonicSolid(
  {
    {  1.0,  1.0,  1.0 }, // 0
    { -1.0, -1.0,  1.0 }, // 1
    {  1.0, -1.0, -1.0 }, // 2
    { -1.0,  1.0, -1.0 }, // 3
  },
  {
    { 0, 1, 2 },
    { 0, 3, 1 },
    { 0, 2, 3 },
    { 1, 3, 2 }
  }){}
};
