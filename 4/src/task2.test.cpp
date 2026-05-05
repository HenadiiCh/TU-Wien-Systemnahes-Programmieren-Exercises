/// @file
/// @brief Task2: tests

#include "task2.hpp" // task2::BBox, task2::Circle, task2::Triangle

#include "task2.misc.hpp" // task2::operator<<, task2::isclose

#include <cassert>  // assert
#include <cmath>    // NAN
#include <iostream> // std::cout, std::endl
#include <numbers>  // std::numbers::pi

int main()
{

    using namespace task2;

    { /// demo: using of functionality provided in 'task2.misc.hpp'
        BBox box = {{1, 2}, {3, 4}};
        Circle circle = {{1, 2}, 3};
        Triangle triangle = {Vec2d{0, 0}, Vec2d{1, 0}, Vec2d{1, 1}};
        std::cout << "printing demo:" << std::endl;
        std::cout << box << std::endl;
        std::cout << circle << std::endl;
        std::cout << triangle << std::endl;
        std::cout << "isclose demo:" << std::endl;
        std::cout << isclose(box, box) << std::endl;
    }

    /// ======= BBox  =============================

    { // testing function 'BBox::scale'
        BBox box = {Vec2d{-10, 10}, Vec2d{10, 10}};
        box = box.scale({-10, 0}, 2);
        BBox expected = {Vec2d{-10, 20}, Vec2d{30, 20}};
        assert(isclose(box, expected));
    }

    { // testing function 'BBox::translate'
        BBox box = {Vec2d{-10, 10}, Vec2d{10, 10}};
        box = box.translate({-10, 0});
        BBox expected = {Vec2d{-20, 10}, Vec2d{0, 10}};
        assert(isclose(box, expected));
    }

    { // testing function 'BBox::check_invariants'
        BBox box1 = {{NAN, 10}, {20, 20}};
        assert(!box1.check_invariants());
        BBox box2 = {{30, 10}, {20, 20}};
        assert(!box2.check_invariants());
        BBox box3 = {{-100, 10}, {20, 20}};
        assert(box3.check_invariants());
    }

    /// ======= Circle  =============================

    { // testing function 'Circle::bbox'
        Circle c = {{10, 10}, 1};
        BBox box = {{9, 9}, {11, 11}};
        assert(isclose(c.bbox(), box));
    }

    { // testing function 'Circle::scale'
        Circle c = {{10, 10}, 1};
        c = c.scale({0, 10}, 2);
        Circle expected = {{20, 10}, 2};
        assert(isclose(c, expected));
    }

    { // testing function 'Circle::rotate'
        Circle c = {{10, 10}, 1};
        c = c.rotate({0, 10}, std::numbers::pi);
        Circle expected = {{-10, 10}, 1};
        assert(isclose(c, expected));
    }

    { // testing function 'Circle::translate'
        Circle c = {{10, 10}, 1};
        c = c.translate({-20, -20});
        Circle expected = {{-10, -10}, 1};
        assert(isclose(c, expected));
    }

    { // testing function 'Circle::check_invariants'
        Circle c1 = {{10, 10}, -2};
        assert(!c1.check_invariants());
        Circle c2 = {{NAN, 10}, 1};
        assert(!c2.check_invariants());
        Circle c3 = {{-10, -10}, 1};
        assert(c3.check_invariants());
    }

    /// ======= Triangle  =============================

    { // testing function 'Triangle::bbox'
        Triangle t = {Vec2d{10, 10}, Vec2d{10, 20}, Vec2d{20, 10}};
        BBox box = {{10, 10}, {20, 20}};
        assert(isclose(t.bbox(), box));
    }

    { // testing function 'Triangle::scale'
        Triangle t = {Vec2d{10, 10}, Vec2d{10, 20}, Vec2d{20, 10}};
        t = t.scale({10, 20}, 2);
        Triangle e = {Vec2d{10, 0}, Vec2d{10, 20}, Vec2d{30, 0}};
        assert(isclose_permute(t, e));
    }

    { // testing function 'Triangle::rotate'
        Triangle t = {Vec2d{10, 10}, Vec2d{10, 20}, Vec2d{20, 10}};
        t = t.rotate({10, 20}, -std::numbers::pi / 2);
        Triangle e = {Vec2d{10, 20}, Vec2d{0, 20}, Vec2d{0, 10}};
        assert(isclose_permute(t, e));
    }

    { // testing function 'Triangle::translate'
        Triangle t = {Vec2d{10, 10}, Vec2d{10, 20}, Vec2d{20, 10}};
        t = t.translate({-10, -10});
        Triangle e = {Vec2d{0, 0}, Vec2d{0, 10}, Vec2d{10, 0}};
        assert(isclose_permute(t, e));
    }

    { // testing function 'Triangle::check_invariants'
        Triangle t1 = {Vec2d{NAN, 10}, Vec2d{10, 20}, Vec2d{20, 10}};
        assert(!t1.check_invariants());
        Triangle t2 = {Vec2d{0, 10}, Vec2d{10, 20}, Vec2d{20, 10}};
        assert(t2.check_invariants());
        Triangle t3 = {Vec2d{0, 10}, Vec2d{0, 10}, Vec2d{20, 10}};
        assert(!t3.check_invariants());
    }

    std::cout << "task2.test.cpp: all asserts passed" << std::endl;

    return 0;
}
