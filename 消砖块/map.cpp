#include "map.h"

void MapManage::Wall()
{
	int x;
	int y;

	Scene drawmap;
	for (x = 0; x < 48; x += 6) {
		drawmap.DrawBlock(x, 0);
	}
	for (y = 4; y < 24; y += 4) {
		drawmap.DrawBlock(0, y);
		drawmap.DrawBlock(42, y);
	}
/*	for (x = 0; x < 48; x += 6) {
		drawmap.DrawBlock(x, 24);
	}*/
}
void MapManage::GradeTips(int grade)
{
	using namespace std;

	SetConsoleColor((ConsoleForegroundColor)enmCFC_Black, (ConsoleBackGroundColor)enmCBC_White);
	SetCursorPosition(49, 19);
	cout << "当前得分：" << grade << endl;
	SetConsoleColor((ConsoleForegroundColor)enmCFC_White, (ConsoleBackGroundColor)enmCBC_Black);
}

void MapManage::TopTips()
{
	using namespace std;

	SetCursorPosition(49, 10);
	cout << "按键操作：" << endl;
	SetCursorPosition(49, 11);
	cout << "↑↓←→操控你的" << endl;
	SetCursorPosition(49, 12);
	cout << "小船板坚持下去吧！" << endl;
	SetCursorPosition(49, 13);
	cout << "按下空格发动直线冲击！" << endl;
}

void MapManage::GameResult()
{
	using namespace std;
	int x;
	int y;

	Scene drawmap;
	for (x = 0; x < 48; x += 6) {
		drawmap.DrawBlock(x, 0);
	}
	for (y = 4; y < 24; y += 4) {
		drawmap.DrawBlock(0, y);
		drawmap.DrawBlock(42, y);
	}
	for (x = 0; x < 48; x += 6) {
		drawmap.DrawBlock(x, 24);
	}

	SetCursorPosition(20, 12);
	cout << "游戏结束，是否再来一局？" << endl;
	SetCursorPosition(20, 15);
	cout << "Y/N" << endl;
}

void MapManage::GameName()
{
	using namespace std;

	SetCursorPosition(20, 10);
	cout << "消方块" << endl;
}

void MapManage::StartAction(int *flag)
{
	using namespace std;

	int buf[6] = {((24<<8) | 2), ((22 << 8) | 4), ((22 << 8) | 2),((22 << 8) | 4), ((20 << 8) | 2), ((22 << 8) | 4)};
	static int index;

	SetCursorPosition(20, 5);
	cout << "■■■■■■" << endl;
	if (*flag == 1) {
		ClearBall(buf[index] >> 8, buf[index] & 0xff);
		index++;
		if (index > 5) {
			index = 0;
		}
		DrawBall(buf[index] >> 8, buf[index] & 0xff);
		*flag = 0;
	}
}

void MapManage::StartInterface(int *flag)
{
	using namespace std;
	
	static int first;

	if (first == 0) {
		SetCursorPosition(20, 15);
		cout << "press any key to start game" << endl;
		MapManage::GameName();
		first = 1;
	}
	MapManage::StartAction(flag);
}