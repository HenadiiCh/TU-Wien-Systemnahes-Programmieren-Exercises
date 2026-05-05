/// @file
/// @brief Generators for uniform distributions of Values, Circles and Triangles

#pragma once

#include <array>   // std::array
#include <cmath>   // std::sqrt, std::sin, std::cos
#include <numbers> // std::numbers::pi
#include <random>  // std::mt19937, std::uniform_real_distribution
#include <tuple>   // std::tuple

namespace iue::rnd {

using Vec2d = std::array<double, 2>;
using Circle = std::tuple<Vec2d, double>;
using Triangle = std::array<Vec2d, 3>;

///@brief Uniformly distributed pseudorandom floating point values
struct UniformValue {

  std::mt19937 algo;                           ///< Random number generator
  std::uniform_real_distribution<double> dist; ///< Interval and distribution type

  /// @brief Constructs an instance producing random values uniformly distributed over an interval
  /// @param min Lower bound of the interval
  /// @param max Upper bound of the interval
  /// @param seed Seed used to initialize the generator algorithm
  UniformValue(const double min, const double max, const std::size_t seed = 1)
      : algo(seed), dist(min, max) {}

  /// @brief Obtains the next random value using current state of the generator
  /// @return Random value
  double operator()() { return dist(algo); }
};

///@brief Uniformly distributed circles
struct UniformCircle {

  std::mt19937 algo;                        ///< Random number generator
  std::uniform_real_distribution<double> x; ///< Interval and distribution type for the x-coordinate
  std::uniform_real_distribution<double> y; ///< Interval and distribution type for the y-coordinate
  std::uniform_real_distribution<double> r; ///< Interval and distribution type for the r-coordinate

  /// @brief Constructs an instance producing random circles uniformly distributed (center and
  /// radius)
  /// @param c_min Lower bound of the coordinate of the center
  /// @param c_max Upper bound of the coordinate of the center
  /// @param r_min Lower bound of the radius
  /// @param r_max Upper ound of the radius
  /// @param seed Seed used to initialize the generator algorithm
  UniformCircle(const Vec2d& c_min, const Vec2d& c_max, double r_min, double r_max,
                const std::size_t seed = 1)
      : algo(seed), x(c_min[0], c_max[0]), y(c_min[1], c_max[1]), r(r_min, r_max) {}

  /// @brief Obtains the next random circle using current state of the generator
  /// @return Random circle
  std::tuple<std::array<double, 2>, double> operator()() {
    // random center
    Vec2d center = {x(algo), y(algo)};
    // random raidus
    double radius = r(algo);
    // return final configuration
    return {center, radius};
  }
};

///@brief Uniformly distributed triangles
struct UniformTriangle {

  std::mt19937 algo; ///< Random number generators
  std::uniform_real_distribution<double>
      c_x; ///< distribution for the x-coordinate of the circumcircle
  std::uniform_real_distribution<double>
      c_y; ///< distribution for the y-coordinate of the circumcircle
  std::uniform_real_distribution<double> c_r; ///< distribution for the radius of the circumcircle
  std::uniform_real_distribution<double>
      angle120; ///< distribution for the angles of the  corner points
  std::uniform_real_distribution<double>
      angle360; ///< distribution for the random rotation of the triangle

  /// @brief Constructs an instance producing random triangles with
  ///  - uniformly distributed circumcircles, and
  ///  - uniformly distributed corner points w.r.t. three fixed non-overlapping 120-degree segments
  ///  on the unit circle
  /// @param c_min Lower bound of the coordinate of the circumcirle
  /// @param c_max Upper bound of the coordinate of the circumcirle
  /// @param r_min Lower bound of the radius of the circle
  /// @param r_max Upper ound of the radius of the circle
  /// @param seed Seed used to initialize the generator algorithm
  UniformTriangle(const Vec2d& c_min, const Vec2d& c_max, double r_min, double r_max,
                  const std::size_t seed = 1)
      : algo(seed), c_x(c_min[0], c_max[0]), c_y(c_min[1], c_max[1]), c_r(r_min, r_max),
        angle120(0, std::numbers::pi * 2 / 3), angle360(0, std::numbers::pi * 2) {}

  /// @brief Obtains the next random triangle using current state of the generator
  /// @return Random circle
  Triangle operator()() {

    // three points on the unit circle constraint to three 120deg-segments
    // these will be the points of the triangle
    double seg = angle120.max();
    double alpha = seg * 0 + angle120(algo);
    double beta = seg * 1 + angle120(algo);
    double gamma = seg * 2 + angle120(algo);

    Vec2d a = {std::sin(alpha), std::cos(alpha)};
    Vec2d b = {std::sin(beta), std::cos(beta)};
    Vec2d c = {std::sin(gamma), std::cos(gamma)};

    Triangle abc = {a, b, c};

    // random circumcircle center
    Vec2d center = {c_x(algo), c_y(algo)};
    // random circumcircle radius
    double r = c_r(algo);
    // random rotation
    double rot = angle360(algo);

    auto rotate = [rot](const Vec2d& p) -> const Vec2d {
      return {std::cos(rot) * p[0] + (-std::sin(rot)) * p[1],
              std::sin(rot) * p[0] + std::cos(rot) * p[1]};
    };
    auto shift = [center](const Vec2d& p) -> const Vec2d {
      return {p[0] + center[0], p[1] + center[1]};
    };
    auto scale = [r](const Vec2d& p) -> const Vec2d { return {p[0] * r, p[1] * r}; };

    // rotate/scale/shift to final configuration
    for (auto& coord : abc) {
      coord = rotate(coord);
      coord = scale(coord);
      coord = shift(coord);
    }

    // return final configuration
    return {abc};
  }
};

} // namespace iue::rnd
