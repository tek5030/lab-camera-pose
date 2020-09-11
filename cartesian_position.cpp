#include "cartesian_position.h"

Eigen::Vector3d CartesianPosition::toVector()
{
  // Todo 2.1: Implement this correctly.
  return Eigen::Vector3d::Zero();
}

std::istream& operator>>(std::istream& is, CartesianPosition& pos)
{
  is >> pos.x
     >> pos.y
     >> pos.z;

  if (!is)
  {
    throw std::runtime_error("Could not read CartiesianPosition data");
  }

  return is;
}

std::ostream& operator<<(std::ostream& os, const CartesianPosition& pos)
{
  os << "x: " << pos.x << "\n"
     << "y: " << pos.y << "\n"
     << "z: " << pos.z << "\n";

  return os;
}
