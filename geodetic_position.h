#pragma once

#include <iostream>

/// \brief Geodetic position
struct GeodeticPosition
{
  double latitude;  /// Latitude in degrees.
  double longitude; /// Longitude in degrees.
  double altitude;  /// Altitude in meters.
};

/// \brief Operator for reading data from stream.
std::istream& operator>>(std::istream& is, GeodeticPosition& pos);

/// \brief Operator for printing data to stream.
/// Meant for showing data, and is not compatible with the reader.
std::ostream& operator<<(std::ostream& os, const GeodeticPosition& pos);
