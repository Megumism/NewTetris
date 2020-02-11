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

	char op = NULL;//玩家操作
	bool opLegal;
	bool settled = true; //是否落下
	bool gaming = true;
	int cube,pos;//方块种类,方块姿态
	//初始化地图
	for (int i = 0; i < 240; i++) {
		map[i] = -1;
	}

	do {
		//生成方块
		if (settled) {
			cube = rand() % 7; 
			pos = rand() % 4;
			switch (cube)
			{
			case 0://O
				map[24] = map[25] = map[34] = map[35] = 0;
				break;
			case 1://I
				map[4] = map[14] = map[24] = map[34] = 0;
				break;
			case 2://T
				map[24] = map[33] = map[34] = map[35] = 0;
				break;
			case 3://J
				map[14] = map[24] = map[34] = map[33] = 0;
				break;
			case 4://L
				map[14] = map[24] = map[34] = map[35] = 0;
				break;
			case 5://S
				map[25] = map[26] = map[34] = map[35] = 0;
				break;
			case 6://Z
				map[23] = map[24] = map[34] = map[35] = 0;
				break;
			}
			settled = false;
		}

		/*if (settled) {
			map[32] = map[33] = map[23] = map[13] =map[3] =map[2] = 0;
			settled = false;
		}*/
		
		op = NULL;//清除操作缓存
		opLegal = true;//初始化用户输入合法性
		if (_kbhit() && (op = _getch()))//判断是否输入
			switch (op)
			{
			case 'a':case 'A':
				for (int i = 239; i >= 0 && opLegal; i--) {//合法性判定
					if (i % 10 == 0 && map[i] == 0) opLegal = false;
					else if(map[i] == 0 && map[i - 1] == 1 ) opLegal = false;
				}
				for (int i = 0; i < 240 && opLegal; i++) {//左移
					if (map[i] == 0) swap(map[i], map[i - 1]);
				}
				break;
			case 'd':case 'D':
				for (int i = 0; i < 240 && opLegal; i++) {//合法性判定
					if (i % 10 == 9 && map[i] == 0) opLegal = false;
					else if (map[i] == 0 && map[i + 1] == 1) opLegal = false;
				}
				for (int i = 239; i >= 0 && opLegal; i--) {//右移
					if (map[i] == 0) swap(map[i], map[i + 1]);
				}
				break;
			case'w':case'W':
				break;
			case's': case 'S':
				break;
			}

		do {
			//下落合法性判断
			if (!settled)
				for (int i = 239; i >= 0 && !settled; i--) {
					if (map[i] == 0&&i>=230) settled = true;
					else if (map[i] == 0 && map[i + 10] == 1) settled = true;
				}
			//若落地则固化！
			if (settled) {
				for (int i = 0; i < 240; i++) {
					if (map[i] == 0) map[i] = 1;
				}
			}		
			//下落
			for (int i = 229; i >= 0; i--) {
				if (map[i] == 0) {
					swap(map[i], map[i + 10]);
				}
			}
		} while (!settled && (op == 's' || op == 'S'));

		//消除
		for (int i = 23; i >= 4 && settled; i--) {
			bool cutoff=true;
			for (int j = 0; j < 10; j++) {
				if (map[i * 10 + j] == -1) cutoff = false;
			}				
			if (cutoff) {
				for (int j = 0; j < 10; j++) {
					map[i * 10 + j] = -1;//消除一层
				}
				for (int ix = i * 10 + 9; ix >= 50; ix--) {//消除后落下
					swap(map[ix], map[ix - 10]);
				}
				i++;
			}
		}

		//死亡判定
		for (int i = 30; i < 40; i++) {
			if (map[i] == 1) gaming = false;
		}
		
		Sleep(300);
		mapPrint();
	} while (gaming);
	return 0;
}