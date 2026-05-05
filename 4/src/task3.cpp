/// @file
/// @brief Task3: implementation

#include <filesystem> // std::filesystem::path
#include <iostream>   // std::vector
#include <vector>     // std::cout

#include "task2.hpp" // task2::BBox, task2::Circle, task2::Triangle

#include "task2.misc.hpp" // task2::operator<<, task2::isclose

#include "task3.hpp"      // task3::render_something
#include "task3.misc.hpp" // task3::render_wrapper

#include "iue-rnd/random.hpp" // iue::rnd::UniformValue, iue::rnd::UniformCircle, iue::rnd::UniformTriangle

/// @todo Include additional standard library headers as needed

namespace task3
{

    /// @todo Implement function 'render_something' as declared and specified in task3.hpp
    /// Implementation Hints:
    /// 1. You can plot whatever you want, but you need to plot at least 200 primitives!
    /// 2. You can view .svg-files using your web browser (or installing a VSCode extension to preview SVGs)
    /// 3. Use the provided function 'task3::render_wrapper' from 'task3.misc.hpp' to plot task2::BBox, task2::Circle,
    ///    task2::Triangle to a SVG-file
    /// 4. The idea is that you make use of the functionality (scale/translate/rotate) you implemented in task2
    /// 5. Optional: you can make use of the random Generators in 'iue-rnd/random.hpp' to obtain random values,
    ///    circles, and triangles
    int render_something(std::filesystem::path filepath)
    {
        // Vectors to store generated primitives (Container für die grafischen Objekte)
        std::vector<task2::BBox> bboxes;
        std::vector<task2::Circle> circles;
        std::vector<task2::Triangle> triangles;

        auto gen_pos = iue::rnd::UniformValue(-20.0, 20.0);
        auto gen_size = iue::rnd::UniformValue(0.1, 2.0);
        auto gen_angle = iue::rnd::UniformValue(0.0, 6.2831853);

        // 1. Generate 100 Circles (100 Kreise generieren und transformieren)
        for (int i = 0; i < 100; ++i)
        {
            task2::Circle c = {{0.0, 0.0}, gen_size()};
            // Transform the circle (Kreis skalieren, rotieren und verschieben)
            c = c.scale({0.0, 0.0}, 1.5);
            c = c.rotate({0.0, 0.0}, gen_angle());
            c = c.translate({gen_pos(), gen_pos()});
            circles.push_back(c);
        }

        // 2. Generate 50 BBoxes (50 Bounding Boxes generieren und transformieren)
        for (int i = 0; i < 50; ++i)
        {
            double size = gen_size();
            task2::BBox b = {{-size/2, -size/2}, {size/2, size/2}};
            // BBox doesn't have rotate, so scale and translate (Skalieren und verschieben)
            b = b.scale({0.0, 0.0}, 1.2);
            b = b.translate({gen_pos(), gen_pos()});
            bboxes.push_back(b);
        }

        // 3. Generate 60 Triangles (60 Dreiecke generieren und transformieren)
        for (int i = 0; i < 60; ++i)
        {
            double s = gen_size();
            task2::Vec2d a = {0.0, s};
            task2::Vec2d b = {-s, -s};
            task2::Vec2d c = {s, -s};
            task2::Triangle t = {{a, b, c}};
            // Transform the triangle (Dreieck transformieren)
            t = t.scale({0.0, 0.0}, 0.8);
            t = t.rotate({0.0, 0.0}, gen_angle());
            t = t.translate({gen_pos(), gen_pos()});
            triangles.push_back(t);
        }

        // Render everything to SVG (Alles in die SVG Datei zeichnen)
        auto [bbmin, bbmax] = task3::render_wrapper(filepath, bboxes, circles, triangles);
        std::cout << "Rendered objects bounding box: " << task2::BBox{bbmin, bbmax} << "\n";
        
        // Return total count, must be >= 200 (Gesamtzahl zurückgeben)
        return triangles.size() + bboxes.size() + circles.size();
    }

} // namespace task3
