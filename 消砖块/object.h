#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "tools.h"

class Object {
public:
	Object(int m_x, int m_y);
	int GetObjectPosition_X();
	int GetObjectPosition_Y();
	void SetObjectPosition(int m_x, int m_y);

private:
	int x;
	int y;
};

void DrawBoat(int m_x, int m_y);
void ClearBoat(int m_x, int m_y);
void DrawBall(int m_x, int m_y);
void ClearBall(int m_x, int m_y);

#endif
