#include <iostream>
#include <algorithm>
#include "Coordinate.h"

using namespace std;

coordinate::coordinate(): parent(NULL), dim(0), rank(1), Weight(0), id(0){
	points = NULL;
}
coordinate::~coordinate(){
	////not done yet
	//delete parent;
	delete[] points;
}
coordinateSet::coordinateSet(float** points, int dim, int num): num(num), dim(dim){
	pointSets = new coordinate*[num];
	for (int i = 0; i < num; i++){
		pointSets[i] = new coordinate();
		pointSets[i]->parent = pointSets[i];
		pointSets[i]->dim = dim;
		pointSets[i]->points = points[i];
		pointSets[i]->id = i + 1;
	}
}
coordinateSet::~coordinateSet(){
	//not done yet
	for (int i = 0; i < num; i++){
		delete pointSets[i];
	}
	delete[] pointSets;
}
coordinate* coordinateSet::FindPoint(coordinate* node){

	while (node->parent != node){
		node = node->parent;
	}
	return node;
}
void coordinateSet::Union(coordinate* x, coordinate* y){
	coordinate* xRep = FindPoint(x);
	coordinate* yRep = FindPoint(y);
	if (xRep != yRep){
		if (yRep->rank > xRep->rank){
			xRep->parent = yRep;
			yRep->rank = max(yRep->rank, xRep->rank + 1);
			yRep->Weight += (xRep->Weight + 1);
		}
		else{
			yRep->parent = xRep;
			xRep->rank = max(xRep->rank, yRep->rank + 1);
			xRep->Weight += (yRep->Weight + 1);
		}
	}

}
void coordinateSet::print(){
	for (int i = 0; i < num; i++){
		cout << i << " (";
		for (int j = 0; j < pointSets[i]->dim; j++){
			if (j < pointSets[i]->dim - 1){
				cout << pointSets[i]->points[j] << ", ";
			}
			else{
				cout << pointSets[i]->points[j];
			}
		}
		cout << ")" << endl;
	}
}