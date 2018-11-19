#include "game.h"
void menu()
{
	printf("***********************\n");
	printf("*1.play         0.exit*\n");
	printf("***********************\n");
}
//测试游戏
void game()
{
	char mine[ROWS][COLS];
	char show[ROWS][COLS];
	InitBoard(show, ROWS, COLS, '*');
	InitBoard(mine, ROWS, COLS, '0');
	SetMine(mine, ROW, COL, MINE_COUNT);
	//ShowBoard(mine, ROW, COL);
	FindMine(mine, show, ROW, COL);
}
	
void text()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		system("cls");
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏！");
			break;
		default:
			printf("输入有误，重新输入！");
			break;
		}
	} while (input);
}
int main()
{
	text();
	return 0;
}