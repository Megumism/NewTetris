#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

char mapCache[401] = {' '};
int map[240];
int cube = 1, pos, core, point = 0; //�������࣬������̬��������ת���ģ��ܷ�
char op = '0';                      //��Ҳ���
bool opLegal, settled = true;       //�����Ƿ�Ϸ����Ƿ�����

//��������仯
void cubeAging(bool getOld = true, bool zeroForOld = false)
{
    for (int i = 0; i <= 240; i++)
    {
        if (getOld && map[i] > 0 - zeroForOld && map[i] < 100)
            map[i]++;
        if (!getOld && map[i] > 1)
            map[i]--;
    }
}

//��ӡ��ͼ
void mapPrint()
{
    for (int i = 40; i < 240; i++)
    {
        if (map[i] == -2)
        {
            mapCache[(i - 40) * 2 + 1] = mapCache[(i - 40) * 2] = ':';
        }
        if (map[i] == -1)
        {
            mapCache[(i - 40) * 2 + 1] = mapCache[(i - 40) * 2] = ' ';
        }
        if (map[i] >= 0 && map[i] <= 12)
        {
            mapCache[(i - 40) * 2] = mapCache[(i - 40) * 2 + 1] = '#';
            //mapCache[(i - 40) * 2] = '0'+ map[i]/10;
            //mapCache[(i - 40) * 2 + 1] = '0' + map[i] % 10;
        }
        if (map[i] > 12)
        {
            mapCache[(i - 40) * 2] = mapCache[(i - 40) * 2 + 1] = '$';
            //mapCache[(i - 40) * 2] = '0' + map[i] / 10;
            //mapCache[(i - 40) * 2 + 1] = '0' + map[i] % 10;
        }
    }
    system("cls");
    printf(mapCache);
    printf("point=%d", point);
}

//������ת
void cubeRotate()
{
    if (cube != 0 && cube != 1 && core % 10 != 0 && core % 10 != 9)
    {
        map[core] = map[core - 11]; //�Ľ�
        map[core - 11] = map[core + 9];
        map[core + 9] = map[core + 11];
        map[core + 11] = map[core - 9];
        map[core - 9] = map[core];
        map[core] = map[core - 10]; //�ı�
        map[core - 10] = map[core - 1];
        map[core - 1] = map[core + 10];
        map[core + 10] = map[core + 1];
        map[core + 1] = map[core];
        map[core] = 0;
    }
    if (cube == 1 && ((core % 10 >= 1 && core % 10 <= 7 && map[core - 1] == -1 && map[core + 1] == -1 && map[core + 2] == -1) || (core / 10 <= 22 && map[core + 10] == -1 && map[core - 10] == -1 && map[core - 20] == -1)))
    {
        //�жϺ�����û��λ���Լ��ܲ���ת
        swap(map[core + 1], map[core - 10]);
        swap(map[core - 1], map[core + 10]);
        swap(map[core - 20], map[core + 2]);
    }
}

//���ɷ���
void cubeProduce()
{
    if (settled)
    {
        cube = rand() % 7;
        pos = rand() % 4;
        switch (cube)
        {
        case 0: //O
            map[24] = map[25] = map[34] = map[35] = 0;
            core = 24;
            break;
        case 1: //I
            map[4] = map[14] = map[24] = map[34] = 0;
            core = 24;
            break;
        case 2: //T
            map[24] = map[33] = map[34] = map[35] = 0;
            core = 34;
            break;
        case 3: //J
            map[14] = map[24] = map[34] = map[33] = 0;
            core = 24;
            break;
        case 4: //L
            map[14] = map[24] = map[34] = map[35] = 0;
            core = 24;
            break;
        case 5: //S
            map[25] = map[26] = map[34] = map[35] = 0;
            core = 25;
            break;
        case 6: //Z
            map[23] = map[24] = map[34] = map[35] = 0;
            core = 24;
            break;
        }
        for (int i = pos; i > 0; i--)
        {
            cubeRotate();
        }
        settled = false;
    }
}

//��������Ԥ��
void cubePreview()
{
    bool previewed = false;
    int previewing[240];
    for (int i = 0; i < 240 && !settled; i++)
    {
        if (map[i] > -2)
            previewing[i] = map[i];
        if (map[i] == -2)
        { //������ԭ
            map[i] = -1;
            previewing[i] = map[i];
        }
    }
    while (!previewed & !settled)
    {
        for (int i = 239; i >= 0 && !previewed; i--)
        {
            if (previewing[i] == 0 && i >= 230)
                previewed = true;
            else if (previewing[i] == 0 && previewing[i + 10] > 0)
                previewed = true;
            if (previewed)
            { //�������̻���
                for (int i = 239; i >= 0; i--)
                {
                    if (previewing[i] == 0 && map[i] != 0)
                        map[i] = -2;
                }
            }
        }
        for (int i = 229; i >= 0 && !previewed; i--)
        {
            if (previewing[i] == 0)
            {
                previewing[i] = -1;
                previewing[i + 10] = 0;
            }
        }
    }
}

//��������
void cubeFall()
{
    //����Ϸ����ж�
    if (!settled)
        for (int i = 239; i >= 0 && !settled; i--)
        {
            if (map[i] == 0 && i >= 230)
                settled = true;
            else if (map[i] == 0 && map[i + 10] >= 1)
                settled = true;
            if (settled)
            { //�������̻���
                cubeAging(true, true);
            }
        }
    if (!settled && core)
        core += 10;
    //����
    for (int i = 229; i >= 0; i--)
    {
        if (map[i] == 0)
        {
            map[i] = -1;
            map[i + 10] = 0;
        }
    }
}

//�û������뷽���˶�
void cubeMove()
{
    op = '0';                        //�����������
    opLegal = true;                  //��ʼ���û�����Ϸ���
    if (_kbhit() && (op = _getch())) //�ж��Ƿ�����
        switch (op)
        {
        case 'a':
        case 'A':
            for (int i = 239; i >= 0 && opLegal; i--)
            { //�Ϸ����ж�
                if (i % 10 == 0 && map[i] == 0)
                    opLegal = false;
                else if (map[i] == 0 && map[i - 1] >= 1)
                    opLegal = false;
            }
            for (int i = 0; i < 240 && opLegal; i++)
            { //����
                if (map[i] == 0)
                    swap(map[i], map[i - 1]);
            }
            if (opLegal && core)
                core--;
            break;
        case 'd':
        case 'D':
            for (int i = 0; i < 240 && opLegal; i++)
            { //�Ϸ����ж�
                if (i % 10 == 9 && map[i] == 0)
                    opLegal = false;
                else if (map[i] == 0 && map[i + 1] >= 1)
                    opLegal = false;
            }
            for (int i = 239; i >= 0 && opLegal; i--)
            { //����
                if (map[i] == 0)
                    swap(map[i], map[i + 1]);
            }
            if (opLegal && core)
                core++;
            break;
        case 'w':
        case 'W':
            cubeRotate();
            break;
        case 's':
        case 'S':
            do
            {
                cubeFall();
            } while (!settled);
            break;
        }
}

//��������
void cubeErase()
{
    for (int i = 23; i >= 4 && settled; i--)
    {
        bool cutoff = true;
        for (int j = 0; j < 10; j++)
        {
            if (map[i * 10 + j] == -1)
                cutoff = false;
        }
        if (cutoff)
        {
            for (int j = 0; j < 10; j++)
            {
                if (map[i * 10 + j] > 13)
                {
                    map[i * 10 + j] -= 12;
                } //����һ��
                else
                {
                    map[i * 10 + j] = -1;
                    for (int ix = i; ix >= 4; ix--)
                    {
                        swap(map[ix * 10 + j], map[(ix - 1) * 10 + j]);
                    }
                } //����������
            }
            point++;
            i++; //����ɨ��
        }
    }
}

int main()
{
    system("mode con:cols=20 lines=21"); //���ÿ���̨��С
    srand(time(NULL));                   //��ʼ���������
    bool gaming = true;

    //��ʼ����ͼ
    for (int i = 0; i < 240; i++)
    {
        map[i] = -1;
    }
    for (int i = 239; i >= 230; i--)
        map[i] = 13;
    map[234] = -1;

    do
    {
        cubeProduce();
        cubeMove();
        cubeMove();
        cubeFall();
        cubeErase();

        //�����ж�
        for (int i = 30; i < 40; i++)
        {
            if (map[i] >= 1)
                gaming = false;
        }

        Sleep(300);
        cubePreview();
        mapPrint();
    } while (gaming);
    system("cls");
    printf(">>>>>GAME  OVER<<<<<\nYOUR POINT:%d", point);
    return 0;
}