#include "include/Sort.h"
#include "include/Shapes.h"
void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {
	shapeList->sort([](Shape *left, Shape *right) -> bool {
		return left->perimeter() < right->perimeter();
	});
}
void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
	shapeList->sort([](Shape *left, Shape *right) -> bool {
		return left->perimeter() > right->perimeter();
	});
}
void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList) {
	shapeList->sort([](Shape *left, Shape *right) -> bool {
		return left->area() < right->area();
	});
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList) {
	shapeList->sort([](Shape *left, Shape *right) -> bool {
		return left->area() > right->area();
	});
}
  
void Sort:: sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
	shapeList->sort([](Shape *left, Shape *right) -> bool {
		return (left->area() / left->perimeter()) < (right->area() / right->perimeter());
	});
}