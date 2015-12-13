#ifndef __KDTREE__
#define __KDTREE__
#include <iostream>
#include "Coordinate.h"
using namespace std;

class kNode{
public:
	bool isCoordinate;
	float data;
	coordinate* point;
	kNode* left;
	kNode* right;
	kNode(float data);
	~kNode();

};

class coordinateNode{
public:
	coordinateNode(coordinate* data);
	coordinateNode* next;
	coordinate* data;
	~coordinateNode();
};

class coordinateStack{
public:
	coordinateNode* Header;
	int size;
	coordinateStack();
	void push(coordinateNode* node);
	coordinateNode* pop();
	~coordinateStack();
};
class kdtree{
public:
	kdtree();
	~kdtree();
	kdtree(float** points, int dim, int num);
	void getNeighbors(coordinate* queryPoint, int radius);
	coordinateSet* Sets;
	kNode* root;
	void MakeTree();
	void MakeTree_slave(kNode* &node, int k, int left, int right);
	void Swap(int x, int y);
	int getMedianIndex(int left, int right, int k, int center);
	void getNeighbors_slave(coordinate* queryPoint, int radius, int k, kNode* node, float* distance);
	void SortById();
	void justSwap(int x, int y);
	coordinateStack* N;
};


#endif