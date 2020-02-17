#include "solid.h"

class UVSphere : public Solid
{
private:
  const int MIN_LAT_LNG{4};
  const int MAX_LAT_LNG{32};
  int lat_lng{MIN_LAT_LNG};

  // methods
  void generate_sphere();

public:
  UVSphere(int);
  void increase();
  void decrease();
};
