#include "object.h"

Object::Object(int m_x, int m_y)
{
	this->x = m_x;
	this->y = m_y;
}

int Object::GetObjectPosition_X()
{
	return this->x;
}

int Object::GetObjectPosition_Y()
{
	return this->y;
}

void Object::SetObjectPosition(int m_x, int m_y)
{
	this->x = m_x;
	this->y = m_y;
}

void DrawBoat(int m_x, int m_y)
{	
	using namespace std;

	SetCursorPosition(m_x, m_y);
	cout << "¡ö¡ö¡ö¡ö¡ö¡ö" << endl;
}

void ClearBoat(int m_x, int m_y)
{
	using namespace std;

	SetCursorPosition(m_x, m_y);
	cout << "            " << endl;
}

void DrawBall(int m_x, int m_y)
{
	using namespace std;

	SetCursorPosition(m_x, m_y);
	cout << "¡ñ" << endl;
}

void ClearBall(int m_x, int m_y)
{
	using namespace std;

	SetCursorPosition(m_x, m_y);
	cout << "  " << endl;
}