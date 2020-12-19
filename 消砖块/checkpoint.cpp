#include "checkpoint.h"

void CreateBricks(int* brickarray)
{
	//int BricksXY[1000];
	int i, j, k;
	static int index = 0;
	int randX = 0;
	int randbricks = 0;
	static int checkflag = 0;
	int temp = 0;
	int indexrecord = 0;

	for (i = 0; i < 100; i++) {
		randbricks = (rand() % (10 - 1 + 1)) + 1;
		for (j = 0; j < randbricks; j++) {
			randX = (rand() % (38 - 6 + 1)) + 6;
			checkflag = 0;
			if (indexrecord == 0) {
				*(brickarray + index) = (randX << 8 | (105 - i));
				indexrecord++;
				index++;
			}
			else {
				for (k = 1; k <= indexrecord; k++) {
					temp = *(brickarray + index - k) >> 8;
					if ((randX < temp + 3) && (randX > temp - 3)) {
						checkflag++;
					}
				}
				if (checkflag == 0) {
					*(brickarray + index) = (randX << 8 | (105 - i));
					indexrecord++;
					index++;
				}
			}
		}
		indexrecord = 0;
	}
}

void DelectBricks(int* brickarray)
{
	int i;

	for (i = 0; i <= 1000; i++) {
		*(brickarray + i) = 0;
	}
}