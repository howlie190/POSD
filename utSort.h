#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <list>

TEST (Sort, sortByIncreasingPerimeter) {
	Sort sort;
	Circle cir1(0, 0, 1, "cir1");
	Circle cir2(2, 3, 10, "cir2");
	Triangle tri1({0, 0}, {3, 0}, {3, 4}, "tri1");
	Rectangle rect1(3, 6, 5, 10, "rect1");
	std::list<Shape *>myList;
	myList.push_back(&cir1);
	myList.push_back(&cir2);
	myList.push_back(&tri1);
	myList.push_back(&rect1);
	sort.sortByIncreasingPerimeter(&myList);
	std::list<Shape *>::iterator it = myList.begin();
	ASSERT_EQ(cir1.name, (*it)->name);
	it++;
	ASSERT_EQ(tri1.name, (*it)->name);
	it++;
	ASSERT_EQ(rect1.name, (*it)->name);
	it++;
	ASSERT_EQ(cir2.name, (*it)->name);
}

TEST (Sort, sortByDecreasingPerimeter) {
	Sort sort;
	Circle cir1(0, 0, 1, "cir1");
	Circle cir2(2, 3, 10, "cir2");
	Triangle tri1({0, 0}, {3, 0}, {3, 4}, "tri1");
	Rectangle rect1(3, 6, 5, 10, "rect1");
	std::list<Shape *>myList;
	myList.push_back(&cir1);
	myList.push_back(&cir2);
	myList.push_back(&tri1);
	myList.push_back(&rect1);
	sort.sortByDecreasingPerimeter(&myList);
	std::list<Shape *>::iterator it = myList.begin();
	ASSERT_EQ(cir2.name, (*it)->name);
	it++;
	ASSERT_EQ(rect1.name, (*it)->name);
	it++;
	ASSERT_EQ(tri1.name, (*it)->name);
	it++;
	ASSERT_EQ(cir1.name, (*it)->name);}

TEST (Sort, sortByIncreasingArea) {
	Sort sort;
	Circle cir1(0, 0, 1, "cir1");
	Circle cir2(2, 3, 10, "cir2");
	Triangle tri1({0, 0}, {3, 0}, {3, 4}, "tri1");
	Rectangle rect1(3, 6, 5, 10, "rect1");
	std::list<Shape *>myList;
	myList.push_back(&cir1);
	myList.push_back(&cir2);
	myList.push_back(&tri1);
	myList.push_back(&rect1);
	sort.sortByIncreasingArea(&myList);
	std::list<Shape *>::iterator it = myList.begin();
	ASSERT_EQ(cir1.name, (*it)->name);
	it++;
	ASSERT_EQ(tri1.name, (*it)->name);
	it++;
	ASSERT_EQ(rect1.name, (*it)->name);
	it++;
	ASSERT_EQ(cir2.name, (*it)->name);

}

TEST (Sort, sortByDecreasingArea) {
	Sort sort;
	Circle cir1(0, 0, 1, "cir1");
	Circle cir2(2, 3, 10, "cir2");
	Triangle tri1({0, 0}, {3, 0}, {3, 4}, "tri1");
	Rectangle rect1(3, 6, 5, 10, "rect1");
	std::list<Shape *>myList;
	myList.push_back(&cir1);
	myList.push_back(&cir2);
	myList.push_back(&tri1);
	myList.push_back(&rect1);
	sort.sortByDecreasingArea(&myList);
	std::list<Shape *>::iterator it = myList.begin();
	ASSERT_EQ(cir2.name, (*it)->name);
	it++;
	ASSERT_EQ(rect1.name, (*it)->name);
	it++;
	ASSERT_EQ(tri1.name, (*it)->name);
	it++;
	ASSERT_EQ(cir1.name, (*it)->name);
}

TEST (Sort, sortByIncreasingCompactness) {
	Sort sort;
	Circle cir1(0, 0, 1, "cir1");
	Circle cir2(2, 3, 10, "cir2");
	Triangle tri1({0, 0}, {3, 0}, {3, 4}, "tri1");
	Rectangle rect1(3, 6, 5, 10, "rect1");
	std::list<Shape *>myList;
	myList.push_back(&cir1);
	myList.push_back(&cir2);
	myList.push_back(&tri1);
	myList.push_back(&rect1);
	sort.sortByIncreasingCompactness(&myList);
	std::list<Shape *>::iterator it = myList.begin();
	ASSERT_EQ(cir1.name, (*it)->name);
	it++;
	ASSERT_EQ(tri1.name, (*it)->name);
	it++;
	ASSERT_EQ(rect1.name, (*it)->name);
	it++;
	ASSERT_EQ(cir2.name, (*it)->name);
}

#endif
