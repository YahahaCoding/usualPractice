#include "tools.h"
#include "map.h"
#include "controller.h"
#include "game.h"

//������Ʒ
//������ʱ���������ٱ��
//��������
int main()
{
	system("title ƽ��֧�� V1.2����ʽ�棩");
	HideCursor();
	system("mode con cols=120 lines=30");//�ı���
	while(1)
		Game();

	return 0;
}