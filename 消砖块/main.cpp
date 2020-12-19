#include "tools.h"
#include "map.h"
#include "controller.h"
#include "game.h"

//增加物品
//增加随时间推移球速变快
//增加生命
int main()
{
	system("title 平板支撑 V1.2（正式版）");
	HideCursor();
	system("mode con cols=120 lines=30");//改变宽高
	while(1)
		Game();

	return 0;
}