#include "game.h"

int timer1 = 0;
int timer2 = 0;
int timer3 = 0;
int timer4 = 0;
int timer5 = 0;

void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	timer1++;
	timer2++;
	timer3++;
	timer4++;
	timer5++;
}

void onTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) {
	case 0:
		timer1++;
		timer2++;
		timer3++;
		break;
	}
}

void Game()
{
	using namespace std;
	int i, boatXY, choice, skillstate;
	MapManage map;
	int gameresult;
	static int reset, startflag;
	static int firsttime;
	static int grade;
	int graderecord;
	int collision = 0;
	MSG   msg;
	static int ballflag, CDflag, skillflag, bricksflag, actionflag;
	static int m_ntimer;

	static int BrickBuff[1000] = {(6<<8)|105, 0};
	int* p = BrickBuff;
	
	if (m_ntimer == 0) {
		SetTimer(0, 0, 1, &TimerProc);
		m_ntimer = 1;
	}
	while (startflag == 0) {
		if (timer5 >= 50) {
			actionflag = 1;
			timer5 = 0;
		}
		map.StartInterface(&actionflag);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_TIMER)
			{
				DispatchMessage(&msg);
			}
		}
		if ((_kbhit()) != 0) {
			system("cls");
			startflag = 1;
		}
	}

	if (firsttime == 0) {
		SetConsoleColor((ConsoleForegroundColor)enmCFC_White, (ConsoleBackGroundColor)enmCBC_Black);
		CreateBricks(p);
		map.GradeTips(grade);
		map.Wall();
		map.TopTips();
//		system("mode con cols=120 lines=30");//¸Ä±ä¿í¸ß
		firsttime = 1;
		CDflag = 1;
	}
	BrickController(0, 0, 0, p, reset, &bricksflag);

	if (timer1 >= 6) {
		ballflag = 1;
		timer1 = 0;
	}
	if (CDflag == 1) {
		timer2 = 0;
	}
	if (timer2 >= 2000) {
		CDflag = 1;
		timer2 = 0;
	}
	if (skillflag == 0) {
		timer3 = 0;
	}
	if (timer3 >= 500) {
		skillflag = 0;
		timer3 = 0;
	}
	if (timer4 >= 600) {
		bricksflag = 1;
		timer4 = 0;
	}
	i = Key_Scan(5000, 100000, 30000);
	skillstate = PowerUpSkill(i, reset, &CDflag, &skillflag);
	//system("cls");
	graderecord = grade;
	boatXY = BoatController(i, reset);
	gameresult = BallController((boatXY & 0xff), (boatXY >> 8), reset, skillstate, p, &ballflag, &grade);
	reset = 0;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_TIMER)
		{
			DispatchMessage(&msg);
		}
	}
	if (grade != graderecord) {
		map.GradeTips(grade);
	}
	if (grade >= 100) {
		gameresult = GAMEOVER;
		SetCursorPosition(20, 10);
		cout << "¹§Ï²Äã£¡ÓÎÏ·Ê¤Àû£¡£¡" << endl;

	}
	if (gameresult == GAMEOVER) {
		map.GameResult();
		choice = getch();
		while ((choice != Y_KEY) && (choice != N_KEY)) {
			choice = getch();
		}
		switch (choice) {
		case Y_KEY:
			reset = 1;
			system("cls");
			firsttime = 0;
			DelectBricks(p);
			grade = 0;
			break;

		case N_KEY:
			system("cls");
			SetCursorPosition(20, 12);
			cout << "ÓÒÉÏ½Çºì²æ¹Ø±Õ" << endl;
			while (1)
			{
			}
			break;
		}
		choice = 0;
	}
}