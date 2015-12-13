#include <iostream>
#include "kdtree.h"
using namespace std;



kNode::kNode(float data): data(data), isCoordinate(false), left(NULL), right(NULL), point(NULL){
	
}
kNode::~kNode(){
	//not done yet

	delete left;
	delete right;
	//right = NULL;

	//delete point;

}
kdtree::kdtree(){

}
kdtree::~kdtree(){
	delete Sets;

	delete root;
	//delete N;
}
kdtree::kdtree(float** points, int dim, int num):root(NULL), N(NULL){
	Sets = new coordinateSet(points, dim, num);

}
bool distanceCheck(float* array, int radius, int dim){
	float distance = 0;
	for (int i = 0; i < dim; i++){
		distance += array[i];
	}
	if (distance > radius*radius){
		return false;
	}
	return true;
}
void kdtree::getNeighbors(coordinate* queryPoint, int radius){
	float* distance = new float[Sets->dim];
	for (int i = 0; i < Sets->dim; i++){
		distance[i] = 0;
	}
	int k = 0;

	getNeighbors_slave(queryPoint, radius, k, root, distance);
	delete[] distance;
}
void kdtree::getNeighbors_slave(coordinate* queryPoint, int radius, int k, kNode* node, float* distance){

	int depth = k % (Sets->dim);
	if (!node->isCoordinate){
		if (queryPoint->points[depth] <= node->data){
			float* temp = new float[Sets->dim];
			
			for (int i = 0; i < Sets->dim; i++){
				temp[i] = distance[i];
			}
			//temp[0] = distance[0]; temp[1] = distance[1];
			getNeighbors_slave(queryPoint, radius, ++k, node->left, temp);
			delete[]temp;
			distance[depth] = (queryPoint->points[depth] - (node->data))*(queryPoint->points[depth] - (node->data));
			if (distanceCheck(distance, radius, Sets->dim)){
				getNeighbors_slave(queryPoint, radius, k, node->right, distance);
			}
		}
		else{
			float* temp = new float[Sets->dim];			
			for (int i = 0; i < Sets->dim; i++){
				temp[i] = distance[i];
			}
			//temp[0] = distance[0]; temp[1] = distance[1];
			getNeighbors_slave(queryPoint, radius, ++k, node->right, temp);
			delete[] temp;
			distance[depth] = (queryPoint->points[depth] - (node->data))*(queryPoint->points[depth] - (node->data));

			if (distanceCheck(distance, radius, Sets->dim)){
				getNeighbors_slave(queryPoint, radius, k, node->left, distance);
			}
		}

	}
	else{
		for (int i = 0; i < Sets->dim; i++){
			distance[i] = (queryPoint->points[i] - (node->point->points[i]))*(queryPoint->points[i] - (node->point->points[i]));
		}
		if (distanceCheck(distance, radius, Sets->dim) && queryPoint->id != node->point->id){
			//이러면 유니언 해줘야지!
			//유니언이 아니라 잠시 저장 ㄱㄱ
			//Sets->Union(queryPoint, node->point);
			coordinateNode * temp = new coordinateNode(node->point);
			N->push(temp);
		}
		else{
			//이러면 아닌새끼니까 버려!
		}
	}
}
void kdtree::MakeTree(){
	MakeTree_slave(root, 0, 0, Sets->num-1);
}

int kdtree::getMedianIndex(int left, int right, int k, int center){
	int depth = k % (Sets->dim);
	int tright = right;
	int tleft = left-1;
	Swap((left+right)/2, right);
	Sets->pointSets[0]->points[depth];
	Sets->pointSets[1]->points[depth];
	Sets->pointSets[2]->points[depth];
	Sets->pointSets[3]->points[depth];
	Sets->pointSets[4]->points[depth];
	Sets->pointSets[5]->points[depth];
	Sets->pointSets[6]->points[depth];
	Sets->pointSets[7]->points[depth];
	Sets->pointSets[8]->points[depth];
	Sets->pointSets[9]->points[depth];
	Sets->pointSets[10]->points[depth];

	while (true){
		while (tleft<right &&Sets->pointSets[++tleft]->points[depth] < Sets->pointSets[right]->points[depth]){}
		while (tright>0 &&Sets->pointSets[--tright]->points[depth] > Sets->pointSets[right]->points[depth]){}
		if (tleft < tright){
			Swap(tleft, tright);
		}
		else{
			break;
		}
	}
	if (tleft == center){
		Swap(tleft, right);
		return tleft;
	}
	else{
		if (tleft < center){
			Swap(tleft, right);
			return getMedianIndex(tleft+1, right, k, center);

		}
		else{
			Swap(tleft, right);
			return getMedianIndex(left, tleft-1, k, center);

		}
	}
}
void kdtree::MakeTree_slave(kNode* &node, int k, int left, int right){
	if (left < right){

		int mid = getMedianIndex(left, right, k, (left+right)/2);
		//mid = Partition(left, mid, right, k);
		node = new kNode(Sets->pointSets[mid]->points[k%(Sets->dim)]);

		k++;
		MakeTree_slave(node->left, k, left, mid);
		MakeTree_slave(node->right, k, mid + 1, right);
	}
	else{
		node = new kNode(Sets->pointSets[left]->points[k % (Sets->dim)]);
		node->isCoordinate = true;
		node->point = Sets->pointSets[left];
		node->point->parent = node->point;

	}
}
void kdtree::Swap(int x, int y){
	//float* temp = new float[Sets->dim];
	float* temp = Sets->pointSets[x]->points;
	Sets->pointSets[x]->points = Sets->pointSets[y]->points;
	Sets->pointSets[y]->points = temp;
	int tempid = Sets->pointSets[x]->id;
	Sets->pointSets[x]->id = Sets->pointSets[y]->id;
	Sets->pointSets[y]->id = tempid;
	//delete[] temp;
}
void kdtree::justSwap(int x, int y){
	//float* temp = new float[Sets->dim];
	float* temp = Sets->pointSets[x]->points;
	Sets->pointSets[x]->points = Sets->pointSets[y]->points;
	Sets->pointSets[y]->points = temp;
	//delete[] temp;
}
void kdtree::SortById(){
	coordinate** temp = new coordinate*[Sets->num];
	for (int i = 0; i < Sets->num; i++){
		temp[Sets->pointSets[i]->id - 1] = Sets->pointSets[i];
	}

	delete[] Sets->pointSets;
	Sets->pointSets = temp;
}

coordinateNode::coordinateNode(coordinate* data): data(data){
	next = NULL;
}
coordinateNode::~coordinateNode(){
	//not done yet
	//delete data;
	delete next;
}
coordinateStack::coordinateStack(){
	size = 0;
	Header = new coordinateNode(NULL);
}
void coordinateStack::push(coordinateNode* node){
	coordinateNode* temp = Header->next;
	Header->next = node;
	node->next = temp;
	size++;
}
coordinateStack::~coordinateStack(){
	//not done yet
	delete Header;

}
coordinateNode* coordinateStack::pop(){
	coordinateNode* temp = Header->next;
	if (temp != NULL){
		Header->next = temp->next;
	}
	size--;
	return temp;
}