#ifndef SFMATH_H
#define SFMATH_H

/**
 * A Vector representation somewhat in the style of the IBM/Sony Vectormath library.
 */
class Vector2 {
public:
  inline Vector2(const float, const float);
  inline Vector2(const Vector2 &);
  inline const float getX() const;
  inline const float getY() const;

  inline const Vector2 operator +( const Vector2 &) const;
  inline const Vector2 operator *( float) const;

private:
  float m_x, m_y;
};

inline Vector2::Vector2 (const float x, const float y) : m_x(x), m_y(y) {}

inline Vector2::Vector2 (const Vector2 &v) : m_x(v.m_x), m_y(v.m_y) {}

inline const float Vector2::getX() const {
  return m_x;
}

inline const float Vector2::getY() const {
  return m_y;
}

inline const Vector2 Vector2::operator +( const Vector2 & vec ) const {
  return Vector2(
		 m_x + vec.m_x,
		 m_y + vec.m_y
		 );
}

inline const Vector2 Vector2::operator *( float scalar ) const {
  return Vector2(
		 m_x * scalar,
		 m_y * scalar
		 );
}

/**
 * A Point representation somewhat in the style of the IBM/Sony Vectormath library.
 */
class Point2 {
public:
  inline Point2(const float, const float);
  inline Point2(const Vector2 &);
  inline Point2(const Point2 &);
  inline const float getX() const;
  inline const float getY() const;
private:
  float m_x, m_y;
};

inline Point2::Point2 (const float x, const float y) : m_x(x), m_y(y) {}

inline Point2::Point2 (const Vector2 & v) : m_x(v.getX()), m_y(v.getY()) {}

inline Point2::Point2 (const Point2 & p) : m_x(p.m_x), m_y(p.m_y) {}

inline const float Point2::getX() const {
  return m_x;
}

inline const float Point2::getY() const {
  return m_y;
}

/*
 * Useful functions
 */

inline static float projection( const Point2 & pnt, const Vector2 & unitVec ) {
  float result;
  result =  ( pnt.getX() * unitVec.getX() );
  result += ( pnt.getY() * unitVec.getY() );
  return result;
}

static const Vector2 xAxis() {
  return Vector2(1.0f, 0.0f);
}

static const Vector2 yAxis() {
  return Vector2(0.0f, 1.0f);
}


#endif
