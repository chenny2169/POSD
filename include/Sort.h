#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "Shapes.h"

class Sort {
	public :
		static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
		    increasingPerimeterSort(shapeList);
//            for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
//                std::cout<<(*it) -> perimeter()<<std::endl;
//            }
		}

  		static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
            increasingPerimeterSort(shapeList);
            (*shapeList).reverse();
//            for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
//                std::cout<<(*it) -> perimeter()<<std::endl;
//            }
		}

  		static void sortByIncreasingArea(std::list<Shape *> * shapeList){
  			increasingAreaSort(shapeList);
//  			for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
//                std::cout<<(*it) -> area()<<std::endl;
//  			}
		}

  		static void sortByDecreasingArea(std::list<Shape *> * shapeList){
  			increasingAreaSort(shapeList);
  			(*shapeList).reverse();
		}

  		static void sortByIncreasingCompactness(std::list<Shape *> * shapeList){
//          area / perimeter
            increasingCompactnessSort(shapeList);
//           for(std::list<Shape*>::iterator it = (*shapeList).begin(); it != (*shapeList).end(); it++){
//                std::cout<<((*it) -> area()) / ((*it) -> perimeter())<<std::endl;
//  			}
		}

};


