#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "map.h"
#include "object.h"
#include "tools.h"
#include "checkpoint.h"
#include <conio.h>
#include <stdlib.h>

#define BOATLENTH   6
#define LEFTLIMIT   6
#define RIGHTLIMIT  42
#define UPPERLIMIT  4
#define LOWWERLIMIT 20

typedef enum {
	KEY_IDLE_TRIGGER_STATE,
	KEY_SHAKEOFF_STATE,
	KEY_SHORT_TO_LONG_STATE,
	KEY_LONG_PRESS_STATE,
}Key_State;

typedef enum {
	KEYLEFT = 75,
	KEYRIGHT = 77,
	KEYUP = 72,
	KEYDOWN = 80,
}KeyBoard_Value;

typedef enum {
	KEY_PRESS_NULL,
	KEY_PRESS_UP,
	KEY_PRESS_LEFT,
	KEY_PRESS_DOWN,
	KEY_PRESS_RIGHT,
	KEY_PRESS_OK,
	KEY_PRESS_CANCEL,
	KEY_PRESS_ADD,
	KEY_PRESS_SUBTRACT,
	KEY_PRESS_UP_LONG,
	KEY_PRESS_LEFT_LONG,
	KEY_PRESS_DOWN_LONG,
	KEY_PRESS_RIGHT_LONG,
	KEY_PRESS_OK_LONG,
	KEY_PRESS_CANCEL_LONG,
	KEY_PRESS_ADD_LONG,
	KEY_PRESS_SUB_LONG,
}Key_Value;

typedef enum {
	LEFTUPPER = 10,
	RIGHTUPPER,
	LEFTDOWN,
	RIGHTDOWN,
	UP,
	DOWN,
}Ball_Direction;

int BallController(int boat_x, int boat_y, int reset, int keyvalue, int *buff, int *flag, int *grade);
int BoatController(int keyvalue, int reset);
int Key_Scan(int shakeofftime, int longpresstime, int frequency);
void BrickController(int collision, int ball_x, int ball_y, int* p, int reset, int *flag);
void BrickLives(int* p, int reset, int *flag);
void ClearAllBricks(int* p);
void ClearBricks(int *p, int i);
void DisplayBricks(int* p);
int PowerUpSkill(int keyvalue, int reset, int *CDflag, int *skillflag);

#endif