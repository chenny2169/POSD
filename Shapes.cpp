#include "include/Shapes.h"

double sumOfArea(const std::vector<Shape *> & shapes) {

    double total =0;

    for (Shape *shapePoint: shapes)
        total += shapePoint->area();

    return total;

}

double sumOfPerimeter(const std::vector<Shape *> & shapes){

    double total = 0;

    for (Shape *shapePoint: shapes)
        total += shapePoint->perimeter();

    return total;

}

Shape* theLargestArea(const std::vector<Shape *> & shapes){

    Shape *largestShape = nullptr;
    double largestArea = 0;

    for (Shape *shapePoint: shapes)
        if(shapePoint->area() >= largestArea){
            largestArea = shapePoint->area();
            largestShape = shapePoint;
        }

    return largestShape;

}

double distanceOfVertexs(const vertex vertex_1, const vertex vertex_2) {
    double diff_X, diff_Y, distance;

    diff_X = vertex_1.x - vertex_2.x;
    diff_Y = vertex_1.y - vertex_2.y;

    distance = sqrt(((diff_X * diff_X) + (diff_Y * diff_Y)));

    return distance;
}

void sortByDecreasingPerimeter(std::vector<Shape *> & shapes) {
    // use the shakeSort
    int left = 0;
    int right = shapes.size()-1;
    int shift = 0;
    Shape *temp;

    while(left < right){
        for(int i = left; i < right; i++) {
            if(shapes[i]->perimeter() < shapes[i+1]->perimeter()){
                temp = shapes[i];
                shapes[i] = shapes[i+1];
                shapes[i+1] = temp;
                shift = i;
            }
        }
        right = shift;
        for(int i = right; i > left; i--){
            if(shapes[i]->perimeter() > shapes[i-1]->perimeter()){
                temp = shapes[i];
                shapes[i] = shapes[i-1];
                shapes[i-1] = temp;
                shift = i;
            }
        }
        left = shift;
    }
}

void increasingPerimeterSort(std::list<Shape *> * shapeList) {
    double maxPerimeter = 0;
    int ifCount = 0;
    for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        if(((*it) -> perimeter()) > maxPerimeter){
            maxPerimeter = (*it) -> perimeter();
            (*shapeList).push_back(*it);
            ifCount++;
//            (*shapeList).pop_front();
        }
    }
    for(int i = 0; i < ifCount; i++){
        (*shapeList).pop_front();
    }
}

void increasingAreaSort(std::list<Shape *> * shapeList) {
    double maxArea = 0;
    int ifCount = 0;
    for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        if(((*it) -> area()) > maxArea){
            maxArea = (*it) -> area();
            (*shapeList).push_back(*it);
            ifCount++;
//            (*shapeList).pop_front();
        }
    }
    for(int i = 0; i < ifCount; i++){
        (*shapeList).pop_front();
    }
}

void increasingCompactnessSort(std::list<Shape *> * shapeList) {
    double maxCompactness = 0;
    int ifCount = 0;
    for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
        if((((*it) -> area()) / ((*it) -> perimeter())) > maxCompactness){
            maxCompactness = ((*it) -> area()) / ((*it) -> perimeter());
            (*shapeList).push_back(*it);
            ifCount++;
//            (*shapeList).pop_front();
        }
    }
    for(int i = 0; i < ifCount; i++){
        (*shapeList).pop_front();
    }
}
