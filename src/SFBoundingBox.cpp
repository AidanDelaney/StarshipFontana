#include "SFBoundingBox.h"

SFBoundingBox::SFBoundingBox(const Vector2 centre,
			     const int width,
			     const int height) :
  centre(make_shared<Vector2>(centre)),
  extent_x(make_shared<Vector2>(Vector2(width/2, 0))),
  extent_y(make_shared<Vector2>(Vector2(0, height/2))) {
}

SFBoundingBox::~SFBoundingBox() {
  centre.reset();
  extent_x.reset();
  extent_y.reset();
}

void SFBoundingBox::SetCentre(Vector2 & v) {
  centre = make_shared<Vector2>(v);
}

bool straddles(const pair<float, float> & a, const pair<float, float> & b) {
  return (a.first >= b.first && a.first <= b.second)
    || (a.second >= b.first && a.second <= b.second);
}

pair<float,float> SFBoundingBox::projectOntoAxis(const SFBoundingBox & b, enum AXIS axis) {
  float lo, hi;

  switch (axis) {
  case X:
    {
      Vector2 bx = *b.extent_x;
      lo  = projection( Point2(Vector2(*(b.centre)) + (bx * -1)), xAxis());
      hi  = projection( Point2(Vector2(*(b.centre)) + bx), xAxis());
    }
    break;
  case Y:
    {
      Vector2 by = *b.extent_y;
      lo  = projection( Point2(Vector2(*(b.centre)) + (by * -1)), yAxis());
      hi  = projection( Point2(Vector2(*(b.centre)) + by), yAxis());
    }
    break;
  }

  return make_pair(lo, hi);
}

bool SFBoundingBox::CollidesWith(const shared_ptr<SFBoundingBox> b) {
  pair<float, float> a_x_proj = projectOntoAxis(*this, X),
    a_y_proj = projectOntoAxis(*this, Y),
    b_x_proj = projectOntoAxis(*b, X),
    b_y_proj = projectOntoAxis(*b, Y);

  return (straddles(a_x_proj, b_x_proj)) && (straddles(a_y_proj, b_y_proj));
}

ostream& operator<<(ostream& os, const SFBoundingBox& obj) {
  os << "c:(" << obj.centre->getX() << ", " << obj.centre->getY() << ") w:" << (obj.extent_x->getX()*2) << " h:" << (obj.extent_y->getY()*2);
  return os;
}
