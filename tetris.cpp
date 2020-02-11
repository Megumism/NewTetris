#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

char mapCache[401] = { ' ' };
int map[240];

void mapPrint() {
	for (int i = 40; i < 240; i++) {
		if (map[i] == -1) {
			mapCache[(i - 40) * 2 + 1] = mapCache[(i - 40) * 2] = ' ';
		}
		if (map[i] == 0) {
			mapCache[(i - 40) * 2 + 1] = mapCache[(i - 40) * 2] = '0';
		}
		if (map[i] == 1) {
			mapCache[(i - 40) * 2 + 1] = mapCache[(i - 40) * 2] = '1';
		}
	}
	system("cls");
	printf(mapCache);
}

int main()
{
	system("mode con:cols=20 lines=20"); //设置控制台大小
	srand(time(NULL));          //初始化随机种子

	char op;//玩家操作
	bool settled = false; //是否落下
	bool game = true;
	int cube = rand() % 7;//方块种类
	int pos = rand() % 4;//方块姿态

	for (int i = 0; i < 240; i++) {
		map[i] = -1;
	}
		map[52] = map[53] = map[54] = map[63] = 0;

	do {
		//下落合法性判断
		if (!settled)
			for (int i = 239; i > 229; i--) {
				if (map[i] == 0) settled = true;
			}
		if(!settled)
			for (int i = 229; i >= 0; i--) {
				if (map[i] == 0 && map[i + 10] == 1) settled = true;
			}
		if (settled) {//若落地固化！
			for (int i = 0; i < 240; i++) {
				if (map[i] == 0) map[i] = 1;
			}
		}
		//下落
		for (int i = 229; i >= 40; i--) {
			if (map[i] == 0) {
				swap(map[i], map[i + 10]);
			}
		}
		//if (_kbhit() && (op = _getch()))//判断是否输入
		Sleep(300);
		mapPrint();
	} while (game);
	return 0;
}