#include "game.h"
void menu()
{
	printf("***********************\n");
	printf("*1.play         0.exit*\n");
	printf("***********************\n");
}
//������Ϸ
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
		printf("��ѡ��>");
		scanf("%d", &input);
		system("cls");
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ��");
			break;
		default:
			printf("���������������룡");
			break;
		}
	} while (input);
}
int main()
{
	text();
	return 0;
}