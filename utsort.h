#ifndef EXP_H
#define EXP_H
#include <iterator>
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"


TEST (Sort, sortByIncreasingPerimeter) {
    std::list<Shape *> sList;
    std::list<Shape *> * shapeList = &sList;
    Shape* rec = new Rectangle(1, 1, 1, 1, "r");
	Shape* cir = new Circle(1, 1, 1, "c");
	Shape* tri = new Triangle({0, 0}, {0, 1}, {1, 0}, "t");
	double perimeterExpected[] = {3.41421, 4, 6.28319};
	int assertCount = 0;

	sList.push_back(rec);
	sList.push_back(cir);
	sList.push_back(tri);

	Sort::sortByIncreasingPerimeter(shapeList);

    for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        std::cout<<"compactness:"<<(*it) -> perimeter()<<std::endl;
        ASSERT_NEAR(perimeterExpected[assertCount], (*it) -> perimeter(), 0.00001);
        assertCount++;
    }
}

TEST (Sort, sortByDecreasingPerimeter) {
	std::list<Shape *> sList;
	std::list<Shape *> * shapeList = &sList;
	Shape* rec = new Rectangle(1, 1, 1, 1, "r");
	Shape* cir = new Circle(1, 1, 1, "c");
	Shape* tri = new Triangle({0, 0}, {0, 1}, {1, 0}, "t");
	double perimeterExpected[] = {6.28319, 4, 3.41421};
	int assertCount = 0;

    sList.push_back(rec);
	sList.push_back(cir);
	sList.push_back(tri);

	Sort::sortByDecreasingPerimeter(shapeList);

	for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        ASSERT_NEAR(perimeterExpected[assertCount], (*it) -> perimeter(), 0.00001);
        assertCount++;
	}
}

TEST (Sort, sortByIncreasingArea) {
	std::list<Shape *> sList;
	std::list<Shape *> * shapeList = &sList;
	Shape* rec = new Rectangle(1, 1, 1, 1, "r");
	Shape* cir = new Circle(1, 1, 1, "c");
	Shape* tri = new Triangle({0, 0}, {0, 1}, {1, 0}, "t");
	double areaExpected[] = {0.5, 1, 3.14159};
	int assertCount = 0;


	sList.push_back(rec);
	sList.push_back(cir);
	sList.push_back(tri);

	Sort::sortByIncreasingArea(shapeList);

	for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        ASSERT_NEAR(areaExpected[assertCount], (*it) -> area(), 0.00001);
        assertCount++;
	}
}

TEST (Sort, sortByDecreasingArea) {
	std::list<Shape *> sList;
	std::list<Shape *> * shapeList = &sList;
	Shape* rec = new Rectangle(1, 1, 1, 1, "r");
	Shape* cir = new Circle(1, 1, 1, "c");
	Shape* tri = new Triangle({0, 0}, {0, 1}, {1, 0}, "t");
	double areaExpected[] = {3.14159, 1, 0.5};
	int assertCount = 0;

	sList.push_back(rec);
	sList.push_back(cir);
	sList.push_back(tri);

	Sort::sortByDecreasingArea(shapeList);

	for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        ASSERT_NEAR(areaExpected[assertCount], (*it) -> area(), 0.00001);
        assertCount++;
	}
}

TEST (Sort, sortByIncreasingCompactness) {
    std::list<Shape *> sList;
	std::list<Shape *> * shapeList = &sList;
	Shape* rec = new Rectangle(1, 1, 1, 1, "r");
	Shape* cir = new Circle(1, 1, 1, "c");
	Shape* tri = new Triangle({0, 0}, {0, 1}, {1, 0}, "t");
	double compactnessExpected[] = {0.146447, 0.25, 0.5};
	int assertCount = 0;


	sList.push_back(rec);
	sList.push_back(cir);
	sList.push_back(tri);

	Sort::sortByIncreasingCompactness(shapeList);

	for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        ASSERT_NEAR(compactnessExpected[assertCount], ((*it) -> area()) / ((*it) -> perimeter()), 0.00001);
        assertCount++;
	}
}

#endif
