/// @file
/// @brief Test for iue::svg::XMLTag

#include "iue-svg/tags.hpp" // iue::svg::XMLTag, iue::svg::svg, iue::svg::circle, iue::svg::polygon, iue::svg::, iue::svg::text

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cout, std::endl
#include <string>   // std::string

struct Value {
  int a = 1;
};

int main() {

  { // w/ default attributes
    auto svg = iue::svg::svg({0, 0}, {100, 100});
    auto group = iue::svg::group();
    auto text = iue::svg::text({{50, 50}, "text"});
    auto circle = iue::svg::circle({{50, 50}, 0.5});
    auto polygon = iue::svg::polygon({{50, 50}, {52, 51}, {51, 52}, {78, 100}});

    std::cout << svg.open() << std::endl;
    std::cout << group.open() << std::endl;
    std::cout << text.open() << std::endl;
    std::cout << text.text() << std::endl;
    std::cout << text.close() << std::endl;
    std::cout << circle.open() << std::endl;
    std::cout << circle.close() << std::endl; 
    std::cout << polygon.open() << std::endl;
    std::cout << polygon.close() << std::endl;    
    std::cout << group.close() << std::endl;
    std::cout << svg.close() << std::endl;
  }

  { // w/ custom attributes
    iue::svg::Attributes attributes;
    attributes.insert({"stroke-width", std::to_string(10)});
    attributes.insert({"stroke", "green"});
    attributes.insert({"fill", "blue"});
    attributes.insert({"invalid-attribute", "no check is performed"});    
    auto svg = iue::svg::svg({0, 0}, {100, 100});
    auto group = iue::svg::group(attributes);
    auto text = iue::svg::text({{50, 50}, "text"}, attributes);
    auto circle = iue::svg::circle({{50, 50}, 0.5}, attributes);
    auto polygon = iue::svg::polygon({{50, 50}, {52, 51}, {51, 52}, {78, 100}}, attributes);

    std::cout << svg.open() << std::endl;
    std::cout << group.open() << std::endl;
    std::cout << text.open() << std::endl;
    std::cout << text.text() << std::endl;
    std::cout << text.close() << std::endl;
    std::cout << circle.open() << std::endl;
    std::cout << circle.close() << std::endl;
    std::cout << polygon.open() << std::endl;
    std::cout << polygon.close() << std::endl;    
    std::cout << group.close() << std::endl;
    std::cout << svg.close() << std::endl;    
  }

  return EXIT_SUCCESS;
}