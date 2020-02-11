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
	system("mode con:cols=20 lines=20"); //���ÿ���̨��С
	srand(time(NULL));          //��ʼ���������

	char op;//��Ҳ���
	bool opLegal;
	bool settled = true; //�Ƿ�����
	bool game = true;
	int cube = rand() % 7;//��������
	int pos = rand() % 4;//������̬

	for (int i = 0; i < 240; i++) {
		map[i] = -1;
	}
		map[234] = map[224] = map[214] = 1;

	do {
		if (settled) {
			map[52] = map[53] = map[54] = map[63] = 0;
			settled = false;
		}

		//����Ϸ����ж�
		if (!settled)
			for (int i = 239; i >= 0 && !settled; i--) {
				if (map[i] == 0&&i>=230) settled = true;
				else if (map[i] == 0 && map[i + 10] == 1) settled = true;
			}
		if (settled) {//�������̻���
			for (int i = 0; i < 240; i++) {
				if (map[i] == 0) map[i] = 1;
			}
		}
		//����
		for (int i = 229; i >= 40; i--) {
			if (map[i] == 0) {
				swap(map[i], map[i + 10]);
			}
		}

		opLegal = true;

		if (_kbhit() && (op = _getch()))//�ж��Ƿ�����
			switch (op)
			{
			case 'a':case 'A':
				for (int i = 239; i >= 0 && opLegal; i--) {
					if (i % 10 == 0 && map[i] == 0) opLegal = false;
					else if(map[i] == 0 && map[i - 1] == 1 ) opLegal = false;
				}
				for (int i = 0; i < 240 && opLegal; i++) {
					if (map[i] == 0) swap(map[i], map[i - 1]);
				}
				break;
			case 'd':case 'D':
				for (int i = 0; i < 240 && opLegal; i++) {
					if (i % 10 == 9 && map[i] == 0) opLegal = false;
					else if (map[i] == 0 && map[i + 1] == 1) opLegal = false;
				}
				for (int i = 239; i >= 0 && opLegal; i--) {
					if (map[i] == 0) swap(map[i], map[i + 1]);
				}
				break;
			}
		Sleep(300);
		mapPrint();
	} while (game);
	return 0;
}