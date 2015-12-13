#include <iostream>
#include "Coordinate.h"
#include "kdtree.h"
#include "DBScan.h"
#include <crtdbg.h>
using namespace std;

int main(){
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(268);
	float** pt = new float*[11];
	for (int i = 0; i < 11; i++){
		pt[i] = new float[5];
	}
	pt[0][0] = 0;
	pt[0][1] = 5.2;
	pt[0][2] = 9;
	pt[0][3] = 0;
	pt[0][4] = 1;
	pt[1][0] = 1;
	pt[1][1] = 6.44;
	pt[1][2] = 3;
	pt[1][3] = 4;
	pt[1][4] = 6;
	pt[2][0] = 2;
	pt[2][1] = 5;
	pt[2][2] = 8;
	pt[2][3] = 3;
	pt[2][4] = 2;
	pt[3][0] = 4;
	pt[3][1] = 1;
	pt[3][2] = 1;
	pt[3][3] = 5;
	pt[3][4] = 8;
	pt[4][0] = 2;
	pt[4][1] = 6;
	pt[4][2] = 1;
	pt[4][3] = 0;
	pt[4][4] = 0;
	pt[5][0] = 4;
	pt[5][1] = 5;
	pt[5][2] = 6;
	pt[5][3] = 7;
	pt[5][4] = 4;
	pt[6][0] = 32;
	pt[6][1] = 1;
	pt[6][2] = 3;
	pt[6][3] = 5;
	pt[6][4] = 6;
	pt[7][0] = 4;
	pt[7][1] = 6.1;
	pt[7][2] = 1.4;
	pt[7][3] = 1.12;
	pt[7][4] = 14;
	pt[8][0] = 5;
	pt[8][1] = 3.6;
	pt[8][2] = 3.9;
	pt[8][3] = 7.32;
	pt[8][4] = 3;
	pt[9][0] = 6;
	pt[9][1] = 4.12;
	pt[9][2] = 4;
	pt[9][3] = 4.5;
	pt[9][4] = 1;
	pt[10][0] = 7;
	pt[10][1] = 1.1;
	pt[10][2] = 1.24;
	pt[10][3] = 7;
	pt[10][4] = 6;


	//coordinateSet* temp = new coordinateSet(pt, 2, 11);
	kdtree* temp = new kdtree(pt, 5, 11);
	temp->Sets->print();
	cout << endl;
	temp->MakeTree();
	temp->SortById();
	DBScan myDB(temp, 5, 2);
	myDB.run();
	delete temp;

	delete[] pt;
	//delete myDB;
	_CrtDumpMemoryLeaks();
	return 0;
}