#include "platonic_solid.h"

class Octahedron : public PlatonicSolid {
public:
  Octahedron() : PlatonicSolid(
  {
    {  0.0,  1.0,  0.0 }, // 0
    {  1.0,  0.0,  0.0 }, // 1
    {  0.0,  0.0, -1.0 }, // 2
    { -1.0,  0.0,  0.0 }, // 3
    {  0.0,  0.0,  1.0 }, // 4
    {  0.0, -1.0,  0.0 }, // 5
  },
  {
    { 0, 1, 2 },
    { 0, 2, 3 },
    { 0, 3, 4 },
    { 0, 4, 1 },
    { 5, 2, 1 },
    { 5, 3, 2 },
    { 5, 4, 3 },
    { 5, 1, 4 }
  }){}
};
