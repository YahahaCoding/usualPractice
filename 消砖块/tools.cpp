#include "tools.h"

void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

void SetCursorPosition(const int x, const int y)
{
	COORD position;
	position.X = x * 2;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Scene::DrawBlock(int x, int y)
{	
	using namespace std;

	SetCursorPosition(x, y);
	cout << "■■■■■■" << endl;
	SetCursorPosition(x, y+1);
	cout << "■        ■" << endl;
	SetCursorPosition(x, y+2);
	cout << "■        ■" << endl;
	SetCursorPosition(x, y+3);
	cout << "■■■■■■" << endl;
}

void Scene::DrawLine(int x, int y, int direction)
{
	using namespace std;

	SetCursorPosition(x, y);
	switch(direction){
	case HORIZONTAL:
		cout << "—" << endl;
		break;

	case VERTICAL:
		cout << "|" << endl;
		break;

	case LEFT_OBLIQUE:
		cout << "╲" << endl;
		break;

	case RIGHT_OBLIQUE:
		cout << "╱" << endl;
		break;
	}
}

void SetConsoleColor(ConsoleForegroundColor foreColor, ConsoleBackGroundColor backColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, foreColor | backColor);
}

void Scene::DrawBrick(int x, int y, int index)
{
	using namespace std;

	SetCursorPosition(x, y);
	if ((index % 3) == 0) {
		SetConsoleColor((ConsoleForegroundColor)enmCFC_Yellow, (ConsoleBackGroundColor)enmCBC_Black);
		cout << "███" << endl;
	}
	else if ((index % 3) == 1) {
		SetConsoleColor((ConsoleForegroundColor)enmCFC_Green, (ConsoleBackGroundColor)enmCBC_Black);
		cout << "███" << endl;
	}
	else if ((index % 3) == 2) {
		SetConsoleColor((ConsoleForegroundColor)enmCFC_Red, (ConsoleBackGroundColor)enmCBC_Black);
		cout << "███" << endl;
	}
	SetConsoleColor((ConsoleForegroundColor)enmCFC_White, (ConsoleBackGroundColor)enmCBC_Black);
}
