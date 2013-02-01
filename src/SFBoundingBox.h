#ifndef SFBOUNDINGBOX_H
#define SFBOUNDINGBOX_H

#include <memory>
#include <utility>
#include <ostream>

using namespace std;

#include "SFMath.h"

enum AXIS {X, Y};

class SFBoundingBox {
public:
  SFBoundingBox(const Vector2, const int, const int);
  virtual ~SFBoundingBox();
  void SetCentre(Vector2 &);

  bool CollidesWith(const shared_ptr<SFBoundingBox>);

private:
  shared_ptr<Vector2> centre, extent_x, extent_y;

  pair<float,float> projectOntoAxis(const SFBoundingBox &, enum AXIS);

  friend class SFAsset;
  friend ostream& operator<<(ostream &, const SFBoundingBox &);
};

#endif
