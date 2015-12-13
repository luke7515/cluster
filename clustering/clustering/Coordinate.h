#ifndef __COORDINATE__
#define __COORDINATE__
#include <iostream>


class coordinate{
public:
	int id;

	float* points;
	coordinate* parent;
	coordinate();
	~coordinate();
	int dim;
	int Weight;
	int rank; 
};
class coordinateSet{
public:
	coordinateSet(float** points, int dim, int num);
	~coordinateSet();
	coordinate** pointSets;  //this is coordinates!
	void Union(coordinate* x, coordinate* y);
	coordinate* FindPoint(coordinate* node);
	int dim;
	int num;
	void print();
};

#endif