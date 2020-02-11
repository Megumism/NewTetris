#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

char mapCache[401] = { ' ' };
int map[240];
int cube, pos, core, point=0;//方块种类,方块姿态,方块旋转核心,总分
char op = '0';//玩家操作
bool opLegal;
bool settled = true; //是否落下

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
	printf("point=%d", point);
}
//打印地图
void cubeProduce() {
	if (settled) {
		cube = rand() % 7;
		pos = rand() % 4;
		switch (cube)
		{
		case 0://O
			map[24] = map[25] = map[34] = map[35] = 0; core = 0;
			break;
		case 1://I
			map[4] = map[14] = map[24] = map[34] = 0; core = 0;
			break;
		case 2://T
			map[24] = map[33] = map[34] = map[35] = 0; core = 34;
			break;
		case 3://J
			map[14] = map[24] = map[34] = map[33] = 0; core = 24;
			break;
		case 4://L
			map[14] = map[24] = map[34] = map[35] = 0; core = 24;
			break;
		case 5://S
			map[25] = map[26] = map[34] = map[35] = 0; core = 25;
			break;
		case 6://Z
			map[23] = map[24] = map[34] = map[35] = 0; core = 24;
			break;
		}
		settled = false;
	}
}
//生成方块
void cubeFall() {
	//下落合法性判断
	if (!settled)
		for (int i = 239; i >= 0 && !settled; i--) {
			if (map[i] == 0 && i >= 230) settled = true;
			else if (map[i] == 0 && map[i + 10] == 1) settled = true;
		}
	if (!settled && core) core += 10;
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
}
//方块下落
void cubeRotate() {
	if (core) {
		map[core] = map[core - 11];//四角
		map[core - 11] = map[core + 9];
		map[core + 9] = map[core + 11];
		map[core + 11] = map[core - 9];
		map[core - 9] = map[core];
		map[core] = map[core - 10];//四边
		map[core - 10] = map[core - 1];
		map[core - 1] = map[core + 10];
		map[core + 10] = map[core + 1];
		map[core + 1] = map[core];
		map[core] = 0;
	}
}
//方块旋转
void cubeMove(){
	op = '0';//清除操作缓存
	opLegal = true;//初始化用户输入合法性
	if (_kbhit() && (op = _getch()))//判断是否输入
		switch (op)
		{
		case 'a':case 'A':
			for (int i = 239; i >= 0 && opLegal; i--) {//合法性判定
				if (i % 10 == 0 && map[i] == 0) opLegal = false;
				else if (map[i] == 0 && map[i - 1] == 1) opLegal = false;
			}
			for (int i = 0; i < 240 && opLegal; i++) {//左移
				if (map[i] == 0) swap(map[i], map[i - 1]);
			}
			if (opLegal && core) core--;
			break;
		case 'd':case 'D':
			for (int i = 0; i < 240 && opLegal; i++) {//合法性判定
				if (i % 10 == 9 && map[i] == 0) opLegal = false;
				else if (map[i] == 0 && map[i + 1] == 1) opLegal = false;
			}
			for (int i = 239; i >= 0 && opLegal; i--) {//右移
				if (map[i] == 0) swap(map[i], map[i + 1]);
			}
			if (opLegal && core) core++;
			break;
		case'w':case'W':
			cubeRotate();
			break;
		case's': case 'S':
			do {
				cubeFall();
			} while (!settled);
			break;
		}
}
//方块运动
void cubeErase() {
	for (int i = 23; i >= 4 && settled; i--) {
		bool cutoff = true;
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
			point++;
			i++;//重新扫描
		}
	}
}
//方块消除

int main()
{
	system("mode con:cols=20 lines=21"); //设置控制台大小
	srand(time(NULL));          //初始化随机种子
	bool gaming = true;

	//初始化地图
	for (int i = 0; i < 240; i++) {
		map[i] = -1;
	}

	do {
		cubeProduce();
		cubeMove();
		cubeFall();
		cubeErase();

		//死亡判定
		for (int i = 30; i < 40; i++) {
			if (map[i] == 1) gaming = false;
		}
		
		Sleep(300);
		mapPrint();
	} while (gaming);
	return 0;
}