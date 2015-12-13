#include <iostream>
#include "DBScan.h"

using namespace std;

DBScan::DBScan(){

}
DBScan::DBScan(kdtree *kdtree, float epsilon, int minpoints){
	for (int i = 0; i < kdtree->Sets->num; i++){
		coordinate* temp = kdtree->Sets->pointSets[i];
		coordinateStack *newStack = new coordinateStack();
		kdtree->N = newStack;
		kdtree->getNeighbors(temp, epsilon);
		if (kdtree->N->size >= minpoints){
			while (kdtree->N->size > 0){
				coordinateNode* deleting = kdtree->N->pop();
				kdtree->Sets->Union(temp, deleting->data);
				deleting->next = NULL;
				delete deleting;

			}
		}
		delete newStack;
	}
	temp = kdtree;
}
void DBScan::run(){
	for (int i = 0; i < temp->Sets->num; i++){
		if (temp->Sets->pointSets[i]->Weight != 0 ||temp->Sets->FindPoint(temp->Sets->pointSets[i]) != temp->Sets->pointSets[i]){
			cout << temp->Sets->pointSets[i]->id << " " << temp->Sets->FindPoint(temp->Sets->pointSets[i])->id << endl;

		}
		else{
			cout << temp->Sets->pointSets[i]->id << " " << -1 << endl;
		}
	}
	//delete temp.N;
}
DBScan::~DBScan(){

}