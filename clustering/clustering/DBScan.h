#ifndef __DBSCAN__
#define __DBSCAN__
#include <iostream>
#include "kdtree.h"

class DBScan{
public:
	~DBScan();
	DBScan();
	void run();
	DBScan(kdtree *kdtree, float epsilon, int minpoints);
private: 
	kdtree *temp;
};

#endif