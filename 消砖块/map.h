#ifndef _MAP_H_
#define _MAP_H_
#include "tools.h"
#include "object.h"

class MapManage {
public:
	void Wall();
	void TopTips();
	void GameResult();
	void StartAction(int *flag);
	void GameName();
	void StartTips();
	void StartInterface(int *flag);
	void GradeTips(int grade);
};

#endif
