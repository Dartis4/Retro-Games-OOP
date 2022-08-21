#ifndef VELOCITY_H
#define VELOCITY_H

#include "point.h"

class Velocity
{
private:
   float dx;
   float dy;

public:
   Velocity()
   {
      dx = 0.0;
      dy = 0.0;
   }

   Velocity(float dx, float dy)
   {
      this->dx = dx;
      this->dy = dy;
   }

   friend bool operator == (const Velocity& lhs, const Velocity& rhs);
   friend bool operator != (const Velocity& lhs, const Velocity& rhs);

   float getDx() const { return dx; }
   float getDy() const { return dy; }

   void setDx(float dx) { this->dx = dx; }
   void setDy(float dy) { this->dy = dy; }

   void addDx(float dx) { this->dx += dx; }
   void addDy(float dy) { this->dy += dy; }

   void add(const Velocity& other);

   void advancePoint(Point& point);
};

inline Velocity operator + (const Velocity& lhs, const Velocity& rhs)
{
   return Velocity(lhs.getDx() + rhs.getDx(),
      lhs.getDy() + rhs.getDy());
}

inline bool operator == (const Velocity& lhs, const Velocity& rhs)
{
   if (abs(lhs.dx - rhs.dx) < 0.001 && abs(lhs.dy - rhs.dy) < 0.001)
      return true;
   return false;
}

inline bool operator != (const Velocity& lhs, const Velocity& rhs)
{
   return !(lhs == rhs);
}

#endif /* velocity_h */
