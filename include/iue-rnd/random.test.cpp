/// @file
/// @brief Test for iue::rnd::UniformValue, iue::rnd::UniformTriangle, and
/// iue::rnd::UniformCircle

#include <cassert> // assert
#include <numeric> // std::accumulate
#include <vector>  // std::vector

#include "iue-rnd/random.hpp" // iue::rnd::UniformValue, iue::rnd::UniformTriangle, iue::rnd::UniformCircle

#include "iue-num/numerics.hpp" // iue::num::isclose

int main() {

  { // random value
    std::vector<double> items;

    auto gen = iue::rnd::UniformValue(1.0, 2.0);
    size_t N = 1e5;
    for (auto n = 0U; n != N; ++n)
      items.push_back({gen()});

    // mean
    auto get_value = [](double sum, const double &value) {
      return sum + value;
    };
    auto mean = std::accumulate(items.begin(), items.end(), 0.0, get_value) /
                items.size();
    assert(iue::num::isclose(mean, 1.5, 1e3 / N));
  }

  { // random circle
    std::vector<iue::rnd::Circle> items;

    // generate random circles
    iue::rnd::Vec2d min = {1, 1};
    iue::rnd::Vec2d max = {2, 2};
    auto gen = iue::rnd::UniformCircle(min, max, 1, 2);
    size_t N = 1e5;
    for (auto n = 0U; n != N; ++n)
      items.push_back({gen()});

    // r_mean
    auto get_r = [](double sum, const iue::rnd::Circle &circ) {
      const auto &[c, r] = circ;
      return sum + r;
    };
    auto r_mean =
        std::accumulate(items.begin(), items.end(), 0.0, get_r) / items.size();
    assert(iue::num::isclose(r_mean, 1.5, 1e3 / N));

    // cx_mean
    auto get_cx = [](double sum, const iue::rnd::Circle &circ) {
      const auto &[c, r] = circ;
      return sum + c[0];
    };
    auto cx_mean =
        std::accumulate(items.begin(), items.end(), 0.0, get_cx) / items.size();
    assert(iue::num::isclose(cx_mean, 1.5, 1e3 / N));

    // cy_mean
    auto get_cy = [](double sum, const iue::rnd::Circle &circ) {
      const auto &[c, r] = circ;
      return sum + c[1];
    };
    auto cy_mean =
        std::accumulate(items.begin(), items.end(), 0.0, get_cy) / items.size();
    assert(iue::num::isclose(cy_mean, 1.5, 1e3 / N));
  }

  { // random triangle
    std::vector<iue::rnd::Triangle> items;

    // generate random circles
    iue::rnd::Vec2d min = {1, 1};
    iue::rnd::Vec2d max = {2, 2};
    auto gen = iue::rnd::UniformTriangle(min, max, 1, 2);
    size_t N = 1e5;
    for (auto n = 0U; n != N; ++n)
      items.push_back({gen()});

    // abcx_mean
    auto get_x = [](double sum, const iue::rnd::Triangle &tri) {
      const auto &[a, b, c] = tri;
      return sum + a[0] + b[0] + c[0];
    };
    auto abcx_mean = std::accumulate(items.begin(), items.end(), 0.0, get_x) /
                     items.size() / 3.0;
    assert(iue::num::isclose(abcx_mean, 1.5, 1e3 / N));

    // abcx_mean
    auto get_y = [](double sum, const iue::rnd::Triangle &tri) {
      const auto &[a, b, c] = tri;
      return sum + a[1] + b[1] + c[1];
    };
    auto abcy_mean = std::accumulate(items.begin(), items.end(), 0.0, get_y) /
                     items.size() / 3.0;
    assert(iue::num::isclose(abcy_mean, 1.5, 1e3 / N));
  }

  return 0;
}
