#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

int main()
{
    system("mode con:cols=10 lines=20"); //设置控制台大小
    srand((unsigned)malloc(1));          //初始化随机种子
    int map[10][24] = {-1};
    char mapCache[201] = {' '};
    bool settled = true; //是否落下
    int cube = rand() % 7;//方块种类
    int pos = rand() % 4;//方块姿态

    do{
        //方块写入
        if (settled){
            switch (cube){
            case 0: //I
                for (int i = 0; i < 4; i++)
                {
                    map[5][i] = 1;
                }
                break;
                // case 1: //L
                // case 2: //J
                // case 3: //O
                // case 4: //T
                // case 5: //S
                // case 6: //Z
                // default:
                //     break;
            }
            settled=false;
        }
        
        //下落合法性检查
        for (int i = 0; i < 9; i++){
            for(int j=23;j>3;j--){
                if(map[i][j]==1&&map[i][j-1]==0||map[i][23]==0){
                    settled=true; 
                }
            }

        }        
        //下落    
        if(!settled){
            for(int i = 0; i < 9; i++){
                for(int j=23;j>3;j--){
                    if(map[i][j]==0){
                        swap(map[i][j],map[i][j+1]);
                    }
                }
            }
        }

    } while (true) ;
    return 0;
}