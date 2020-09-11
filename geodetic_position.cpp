#include "geodetic_position.h"

std::istream& operator>>(std::istream& is, GeodeticPosition& pos)
{
  is >> pos.latitude
     >> pos.longitude
     >> pos.altitude;

  if (!is)
  {
    throw std::runtime_error("Could not read GeodeticPosition data");
  }

  return is;
}

std::ostream& operator<<(std::ostream& os, const GeodeticPosition& pos)
{
  os << "Latitude:  " << pos.latitude << "\n"
     << "Longitude: " << pos.longitude << "\n"
     << "Altitude:  " << pos.altitude << "\n";

  return os;
}
