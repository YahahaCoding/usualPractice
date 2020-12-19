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
	cout << "��ǰ�÷֣�" << grade << endl;
	SetConsoleColor((ConsoleForegroundColor)enmCFC_White, (ConsoleBackGroundColor)enmCBC_Black);
}

void MapManage::TopTips()
{
	using namespace std;

	SetCursorPosition(49, 10);
	cout << "����������" << endl;
	SetCursorPosition(49, 11);
	cout << "���������ٿ����" << endl;
	SetCursorPosition(49, 12);
	cout << "С��������ȥ�ɣ�" << endl;
	SetCursorPosition(49, 13);
	cout << "���¿ո񷢶�ֱ�߳����" << endl;
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
	cout << "��Ϸ�������Ƿ�����һ�֣�" << endl;
	SetCursorPosition(20, 15);
	cout << "Y/N" << endl;
}

void MapManage::GameName()
{
	using namespace std;

	SetCursorPosition(20, 10);
	cout << "������" << endl;
}

void MapManage::StartAction(int *flag)
{
	using namespace std;

	int buf[6] = {((24<<8) | 2), ((22 << 8) | 4), ((22 << 8) | 2),((22 << 8) | 4), ((20 << 8) | 2), ((22 << 8) | 4)};
	static int index;

	SetCursorPosition(20, 5);
	cout << "������������" << endl;
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