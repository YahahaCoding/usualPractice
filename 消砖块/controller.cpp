#include "controller.h"

int Key_Scan(int shakeofftime, int longpresstime, int frequency)
{
	char keyvalue = 0;

	if (_kbhit())
		keyvalue = _getch();

	return keyvalue;
}

int BoatController(int keyvalue, int reset)
{
	static Object boat(21, 22);
	int boatXY;

	DrawBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
	switch(keyvalue){
	case KEYLEFT:
		if (boat.GetObjectPosition_X() >= 7) {
			ClearBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
			boat.SetObjectPosition(boat.GetObjectPosition_X() - 1, boat.GetObjectPosition_Y());
			DrawBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
		}
		break;

	case KEYRIGHT:
		if (boat.GetObjectPosition_X() <= 35) {
			ClearBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
			boat.SetObjectPosition(boat.GetObjectPosition_X() + 1, boat.GetObjectPosition_Y());
			DrawBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
		}			
		break;

	case KEYUP:
		if (boat.GetObjectPosition_Y() >= 22) {
			ClearBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
			boat.SetObjectPosition(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y() - 1);
			DrawBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
		}
		break;

	case KEYDOWN:
		if (boat.GetObjectPosition_Y() <= 24) {
			ClearBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
			boat.SetObjectPosition(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y() + 1);
			DrawBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
		}
		break;
	}
	if (reset == 1) {
		ClearBoat(boat.GetObjectPosition_X(), boat.GetObjectPosition_Y());
		boat.SetObjectPosition(21, 22);
	}
	boatXY = boat.GetObjectPosition_X() | (boat.GetObjectPosition_Y() << 8);

	return boatXY;
}

int BallController(int boat_x, int boat_y, int reset, int skillstate, int *buff, int *flag, int *grade)
{
	//static int timer = 0;
	static Object ball(23, 10);
	static int balldirection = UP;
	int i;
	int gameresult = 1;
	int testX, testY;
	static int firsttime;

	if (skillstate == 1) {
		if (firsttime == 1) {
			if (balldirection != UP)
				balldirection = UP;
			firsttime = 0;
		}
	}
	else if (skillstate == 0) {
		firsttime = 1;
	}
/*	if ((balldirection == UP) && (skillstate != 1)) {
		balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
	}*/
/*	else if ((balldirection == DOWN) && (skillstate != 1)) {
		balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
	}*/
	if (*flag == 1) {
		for (i = 0; i <= BOATLENTH; i++) {
			if (ball.GetObjectPosition_X() == (boat_x + i) && ball.GetObjectPosition_Y() == boat_y - 1) {
				if ((ball.GetObjectPosition_X() == (boat_x + 2) ||
					ball.GetObjectPosition_X() == (boat_x + 3))
					&& ball.GetObjectPosition_Y() == boat_y - 1)
				{
					if (balldirection == LEFTDOWN)
						balldirection = UP;
					else if (balldirection == RIGHTDOWN)
						balldirection = UP;
					else if (balldirection == DOWN)
						balldirection = UP;
				}
				else {
					if (balldirection == LEFTDOWN)
						balldirection = LEFTUPPER;
					else if (balldirection == RIGHTDOWN)
						balldirection = RIGHTUPPER;
					else if ((balldirection == DOWN) && (skillstate != 1))
						balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
					else if ((balldirection == DOWN) && (skillstate == 1))
						balldirection = UP;
				}
			}
			else if (ball.GetObjectPosition_X() == (boat_x - 1) && ball.GetObjectPosition_Y() == boat_y - 1) {
				if (balldirection == RIGHTDOWN)
					balldirection = LEFTUPPER;
			}
			else if (ball.GetObjectPosition_X() == (boat_x + 7) && ball.GetObjectPosition_Y() == boat_y - 1) {
				if (balldirection == LEFTDOWN)
					balldirection = RIGHTUPPER;
			}
		}

		for (i = 0; i < 1000; i++) {
			if ((*(buff + i) & 0xff) >= 104) {
				if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) - 2)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 100))) {
					if (balldirection == RIGHTUPPER) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) - 1)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 100))) {
					if (balldirection == RIGHTUPPER) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) - 1)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == RIGHTUPPER) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) - 1)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == RIGHTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) - 2)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == RIGHTUPPER) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) - 2)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == RIGHTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 6)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = RIGHTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 6)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == LEFTDOWN) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 6)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == LEFTDOWN) {
						balldirection = RIGHTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
/*				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 6)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = RIGHTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTUPPER) {
						balldirection = LEFTDOWN;
						ClearBricks(buff, i);
					}

					else if ((balldirection == UP) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate == 1)) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 6)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == LEFTDOWN) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate == 1)) {
						balldirection = UP;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
					}
				}*/
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 5)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTUPPER) {
						balldirection = RIGHTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					/*else if (balldirection == UP) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}*/

					else if ((balldirection == UP) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate == 1)) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 5)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == LEFTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate == 1)) {
						balldirection = UP;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 4)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTUPPER) {
						balldirection = RIGHTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					/*else if (balldirection == UP) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}*/

					else if ((balldirection == UP) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate == 1)) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 4)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == LEFTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate == 1)) {
						balldirection = UP;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 3)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTUPPER) {
						balldirection = RIGHTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					/*else if (balldirection == UP) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						ClearBricks(buff, i);
					}*/

					else if ((balldirection == UP) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate == 1)) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 3)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == LEFTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate == 1)) {
						balldirection = UP;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 2)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
				if (balldirection == LEFTUPPER) {
					balldirection = LEFTDOWN;
					testX = *(buff + i) >> 8;
					testY = *(buff + i) & 0xff;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				else if (balldirection == RIGHTUPPER) {
					balldirection = RIGHTDOWN;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				/*else if (balldirection == UP) {
					balldirection = DOWN;
					testX = *(buff + i) >> 8;
					testY = *(buff + i) & 0xff;
					ClearBricks(buff, i);
				}*/

				else if ((balldirection == UP) && (skillstate != 1)) {
					balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				else if ((balldirection == UP) && (skillstate == 1)) {
					balldirection = DOWN;
					testX = *(buff + i) >> 8;
					testY = *(buff + i) & 0xff;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 2)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
				if (balldirection == LEFTDOWN) {
					balldirection = LEFTUPPER;
					testX = *(buff + i) >> 8;
					testY = *(buff + i) & 0xff;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				else if (balldirection == RIGHTDOWN) {
					balldirection = RIGHTUPPER;
					testX = *(buff + i) >> 8;
					testY = *(buff + i) & 0xff;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				else if ((balldirection == DOWN) && (skillstate == 1)) {
					balldirection = UP;
					testX = *(buff + i) >> 8;
					testY = *(buff + i) & 0xff;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				else if ((balldirection == DOWN) && (skillstate != 1)) {
					balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
					*grade = *grade + 1;
					ClearBricks(buff, i);
				}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 1)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTUPPER) {
						balldirection = RIGHTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate == 1)) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8) + 1)) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == LEFTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate == 1)) {
						balldirection = UP;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8))) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) + 1 - 100))) {
					if (balldirection == LEFTUPPER) {
						balldirection = LEFTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTUPPER) {
						balldirection = RIGHTDOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTDOWN - LEFTDOWN + 1)) + LEFTDOWN;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == UP) && (skillstate == 1)) {
						balldirection = DOWN;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
				else if (((ball.GetObjectPosition_X() == (*(buff + i) >> 8))) && (ball.GetObjectPosition_Y() == ((*(buff + i) & 0xff) - 1 - 100))) {
					if (balldirection == LEFTDOWN) {
						balldirection = LEFTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if (balldirection == RIGHTDOWN) {
						balldirection = RIGHTUPPER;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate == 1)) {
						balldirection = UP;
						testX = *(buff + i) >> 8;
						testY = *(buff + i) & 0xff;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
					else if ((balldirection == DOWN) && (skillstate != 1)) {
						balldirection = (rand() % (RIGHTUPPER - LEFTUPPER + 1)) + LEFTUPPER;
						*grade = *grade + 1;
						ClearBricks(buff, i);
					}
				}
			}
		}

		if (ball.GetObjectPosition_X() <= 6 || ball.GetObjectPosition_X() >= 41) {
			switch (balldirection) {
			case LEFTUPPER:
				balldirection = RIGHTUPPER;
				break;

			case LEFTDOWN:
				balldirection = RIGHTDOWN;
				break;

			case RIGHTUPPER:
				balldirection = LEFTUPPER;
				break;

			case RIGHTDOWN:
				balldirection = LEFTDOWN;
				break;
			}
		}

		if (ball.GetObjectPosition_Y() <= 4) {
			switch (balldirection) {
			case LEFTUPPER:
				balldirection = LEFTDOWN;
				break;

			case LEFTDOWN:
				balldirection = LEFTUPPER;
				break;

			case RIGHTUPPER:
				balldirection = RIGHTDOWN;
				break;

			case RIGHTDOWN:
				balldirection = RIGHTUPPER;
				break;

			case UP:
				balldirection = DOWN;
				break;
			}
		}

		ClearBall(ball.GetObjectPosition_X(), ball.GetObjectPosition_Y());
		switch (balldirection) {
		case LEFTUPPER:
			ball.SetObjectPosition(ball.GetObjectPosition_X() - 1, ball.GetObjectPosition_Y() - 1);
			break;

		case LEFTDOWN:
			ball.SetObjectPosition(ball.GetObjectPosition_X() - 1, ball.GetObjectPosition_Y() + 1);
			break;

		case RIGHTUPPER:
			ball.SetObjectPosition(ball.GetObjectPosition_X() + 1, ball.GetObjectPosition_Y() - 1);
			break;

		case RIGHTDOWN:
			ball.SetObjectPosition(ball.GetObjectPosition_X() + 1, ball.GetObjectPosition_Y() + 1);
			break;

		case UP:
			ball.SetObjectPosition(ball.GetObjectPosition_X(), ball.GetObjectPosition_Y() - 1);
			break;

		case DOWN:
			ball.SetObjectPosition(ball.GetObjectPosition_X(), ball.GetObjectPosition_Y() + 1);
			break;
		}

		*flag = 0;
	}
	if (reset == 1) {
		ball.SetObjectPosition(23, 10);
		balldirection = UP;
	}
	DrawBall(ball.GetObjectPosition_X(), ball.GetObjectPosition_Y());
	if (ball.GetObjectPosition_Y() >= 26) {
		gameresult = 0;
	}

	return gameresult;
}

void DisplayBricks(int *p)
{
	int i;
	Scene k;

	for (i = 0; i < 1000; i++) {
		if (((*(p + i) & 0xff) >= 104) && ((*(p + i)>>8) != 0)) {
			k.DrawBrick(*(p + i) >> 8, (*(p + i) & 0xff) - 100, i);
		}
	}
}

void ClearBricks(int *p, int i)
{
	using namespace std;

	SetConsoleColor((ConsoleForegroundColor)enmCFC_Black, (ConsoleBackGroundColor)enmCBC_Black);
	SetCursorPosition(*(p + i) >> 8, (*(p + i) & 0xff) - 100);
	cout << "███" << endl;
	*(p+i) = 0;
	SetConsoleColor((ConsoleForegroundColor)enmCFC_White, (ConsoleBackGroundColor)enmCBC_Black);
}

void ClearAllBricks(int *p)
{
	using namespace std;

	int i;
	Scene k;

	for (i = 0; i < 1000; i++) {
		SetConsoleColor((ConsoleForegroundColor)enmCFC_Black, (ConsoleBackGroundColor)enmCBC_Black);
		if ((*(p + i) & 0xff) >= 104) {
			SetCursorPosition(*(p + i) >> 8, (*(p + i) & 0xff) - 100);
			cout << "███" << endl;
		}
	}
	SetConsoleColor((ConsoleForegroundColor)enmCFC_White, (ConsoleBackGroundColor)enmCBC_Black);
}

void BrickLives(int *p, int reset, int *flag)
{
	static int timer_bricks;
	int index;
	static int firsttime = 0;

	if (reset == 1)
		firsttime = 0;
	if (firsttime == 0) {
		DisplayBricks(p);
		firsttime++;
	}
	if (*flag == 1) {
		ClearAllBricks(p);
		for (index = 0; index < 1000; index++) {
			*(p + index) = ((*(p + index) & 0xff00)) | ((*(p + index) & 0xff) + 1);		
		}
		DisplayBricks(p);
		*flag = 0;
	}
}

void BrickController( int collision, int ball_x, int ball_y, int *p, int reset, int *flag)
{
	BrickLives(p, reset, flag);
}

int PowerUpSkill(int keyvalue, int reset, int *CDflag, int *skillflag)
{
	using namespace std;

	static int state = 0;;
	static int timer, cdflag;
	static int CDtime = 200001;

	if (*CDflag == 1) {//冷却完成
		if (keyvalue == 32) {//发动技能
			state = 1;
			*skillflag = 1;
			*CDflag = 0;//进入冷却
		}
		if (cdflag == 0) {
			SetCursorPosition(49, 16);
			cout << "                  " << endl;
			SetCursorPosition(49, 16);
			cout << "直线冲击冷却完成！" << endl;
			cdflag = 1;
		}
	}
	if (*CDflag == 0) {
//		CDtime++;
		if (cdflag == 1) {
			SetCursorPosition(49, 16);
			cout << "                " << endl;
			SetCursorPosition(49, 16);
			cout << "直线冲击冷却中！" << endl;
			cdflag = 0;
		}
	}

	if (*skillflag == 1) {
		state = 1;
	}
	else if (*skillflag == 0) {
		state = 0;
	}
	if (reset == 1) {
		state = 0;
		*skillflag = 0;
		*CDflag = 1;
	}

	return state;
}

void AttackBricks()
{

}