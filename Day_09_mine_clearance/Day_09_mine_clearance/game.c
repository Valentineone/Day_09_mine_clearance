#include "game.h"
void InitBoard(char array[ROWS][ROWS], int rows, int  cols,char el)
{
	int i = 0;
	int j = 0;
	for(i = 0;i<rows;i++)
	{
		for (j = 0; j < cols; j++)
		{
			array[i][j] = el;
		}
	}
}
void SetMine(char mine[ROWS][COLS], int row, int col,int count)
{
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}
void ShowBoard(char array[ROWS][COLS], int row, int  col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < col; i++)
	{
		if (i == 0)
		{
			printf("     %d  ", i + 1);
		}

		else
		{
			printf(" %-2d ", i + 1);
		}

	}
	printf("\n");
	for (i = 0; i < col; i++)
	{
		if (i == 0)
		{
			printf("    ___");
		}
		else
		{
			printf("____");
		}

	}
	printf("\n");
	for (i = 0; i < row; i++)
	{
		printf("%2d", i + 1);
		for (j = 0; j < col; j++)
		{
			if (j == 0)
			{
				printf(" | %c |", array[i + 1][j + 1]);
			}
			else
			{
				printf(" %c |", array[i + 1][j + 1]);
			}

		}
		printf("\n");
		if (i == row - 1)
		{
			for (i = 0; i < col; i++)
			{
				if (i == 0)
				{
					printf("   ￣￣");
				}
				else
				{
					printf("￣￣");
				}

			}
			printf("\n");
		}
		else
		{
			for (j = 0; j < col; j++)
			{
				if (j == 0)
				{
					printf("   |");
				}
				{
					printf("---|");
				}
			}
			printf("\n");
		}

	}
}
int flag_count = 0;
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int i = 0;//遍历雷区使用的变量
	int j = 0;
	int x = 0;//排雷是用的坐标
	int y = 0;
	int input = 0;//判断是否要继续游戏
	int count = 0;
	while (count < row*col - MINE_COUNT&&flag_count != MINE_COUNT)
	{
		count = 0;
		static int flag = 0;
		ShowBoard(show, row, col);
		printf("扫雷（输入横坐标x、及纵坐标y）:>");
		scanf("%d %d", &x, &y);
		system("cls");
		if (x<1 || x>row || y<1 || y>col)//保证输入坐标在雷盘上
		{
			printf("非法输入！请重新输入：>");
			continue;
		}
		else
		{	//把flag++放在&&的前面是因为测试时候还是出现除第一次排雷踩到雷第一次未检测出，是因为把mine[x][y] == '1'放到前面如果第一次mine[x][y] == '1'为假后边也不执行，flag仍为0，从而导致出错
			if ( flag++ == 0 && mine[x][y] == '1')//第一次排雷一定不会被炸死，flag++是保证第一次踩到雷是在排雷过程中错误的修改雷的位置
			{
				int m = 0;
				int n = 0;
				while (1)
				{
					m = rand() % row + 1;
					n = rand() % col + 1;
					if (mine[m][n] != '1')
					{
						mine[m][n] = '1';
						break;
					}
				}
			}
			else if (mine[x][y] == '1')
			{
				ShowBoard(show, row, col);
				printf("啊哈哈，你被炸死了！");
				printf("真正的雷区是这样的！\n");
				ShowBoard(mine, row, col);
				goto again;
			}
			else if (mine[x][y] == '0')
			{
				int around_count = CountAround(mine, x, y);
				if (around_count == 0)
				{
					SweepMine(mine, show, x, y);
					ShowBoard(show, ROW, COL);
					//用来判断是否未排查和已做标记的部分是否已达到雷的总个数,放在这个位置的原因是，可能会有扫到空白区域一下经过扩展就能扫出所有非雷地区
					for (i = 1; i <= row; i++)
					{
						for (j = 1; j <= col; j++)
						{
							if (show[i][j] != '*' && show[i][j] != 'M')//当标记区域的个数和剩余未标记未知区域的个数只和为雷的总个数时，排雷结束，判断输赢
							{
								count++;
							}
						}
					}
					if (count == MINE_COUNT)
					{
						break;
					}
					else
					{
						count = 0;//为下次判断之前重置count的值，避免count被重复累加
					}
				}
				else
				{
					show[x][y] = (char)around_count + '0';
					ShowBoard(show, ROW, COL);

					for (i = 1; i <= row; i++)
					{
						for (j = 1; j <= col; j++)
						{
							if (show[i][j] != '*' && show[i][j] != 'M')//当标记区域的个数和剩余未标记未知区域的个数只和为雷的总个数时，排雷结束，判断输赢
							{
								count++;
							}
						}
					}
					if (count == MINE_COUNT)
					{
						break;
					}
					else
					{
						count = 0;//为下次判断之前重置count的值，避免count被重复累加
					}

				}
				FlagMine(show);
				if (flag_count == MINE_COUNT)
				{
					break;//如果直接标记完了，就直接跳出，不需要判断是否把所有非雷都排查出来，玩家提前结束游戏
				}

				//这一段和上面扩展下面的判断是同一段，用来判断是否未排查和已做标记的部分是否已达到雷的总个数，用count侧面反映，显然在一遍排查之后要测量一遍count的数量用来判断是否可以结束，这段并不多余
				for (i = 1; i <= row; i++)
				{
					for (j = 1; j <= col; j++)
					{
						if (show[i][j] != '*' && show[i][j] != 'M')//当标记区域的个数和剩余未标记未知区域的个数只和为雷的总个数时，排雷结束，判断输赢
						{
							count++;
						}
					}
				}

				//ShowBoard(mine, ROW, COL);
				//ShowBoard(show, ROW, COL);
			}
		}
	
	}
	if (flag_count == MINE_COUNT)
	{
		for (i = 1; i <= row; i++)
		{
			for (j = 1; j <= col; j++)
			{
				if(mine[i][j] == '1' && show[i][j] == 'M')
				{
					flag_count--;
				}
			}
		}
		if (flag_count == 0)
		{
			printf("你已经标记完所有雷，恭喜你！你赢了！\n");
		}
		else
		{
			printf("你标记的雷并不正确！挑战失败！\n");
			printf("真正的雷区是这样的！\n");
			ShowBoard(mine, row, col);
		}
	}
	else
	{
		printf("你已经排完所有非雷地区，剩下的全是雷，恭喜你！你赢了！\n");
		printf("雷区是这个样子！\n");
		ShowBoard(mine, row, col);
	}
	again:
	printf("你是否想继续游戏？\n");
	printf("************************\n");
	printf("*     1.不过瘾          *\n");
	printf("*     0.不想玩了        *\n");
	printf("************************\n");
	do
	{
		printf("输入您的选择：>\n");
		scanf("%d", &input);
		if (input == 0)
		{
			exit(0);
		}
		else if(input == 1)
		{
			break;
		}
		else
		{
			printf("非法输入！");
		}
	} while (1);
	system("cls");
}
void FlagMine(char show[ROWS][COLS])
{
	int input = 0;
	printf("你是否想标记雷？\n");
	do
	{
		printf("1.想   2.不是很想，我要继续\n");
		scanf("%d", &input);
		if (input == 2)
		{
			system("cls");
		}
		switch (input)
		{
		case 1:
			Flag(show);
			if (flag_count == MINE_COUNT)
			{
				return;
			}
			printf("你是否还想标记雷？\n");
			
			break;
		case 2:
			break;
		default:
			printf("非法输入！重新输入：>\n");
		}
	} while (input == 1 || !(input == 2));
}
void Flag(char show[ROWS][COLS])
{
	int x = 0;
	int y = 0;
	do
	{
		printf("请输入你想标记雷的坐标：>");
		scanf("%d %d", &x, &y);
		system("cls");
		if (x<1 || x>ROW || y<1 || y>COL)
		{
			ShowBoard(show, ROW, COL);
			printf("非法输入！请重新输入：>\n");
			continue;
		}
		else if(show[x][y] != '*')//如果该坐标已被排查，重新输入
		{
			ShowBoard(show, ROW, COL);
			printf("此处已排查，请重新输入！\n");
			continue;
		}
		else
		{
			break;
		}
	} while (1);
	show[x][y] = 'M';
	flag_count++;
	
	//system("cls");
	ShowBoard(show, ROW, COL);
	
}
int CountAround(char mine[ROWS][COLS],int x,int y)
{
	int sum = 0;
	sum = mine[x - 1][y] + mine[x - 1][y - 1] + mine[x][y - 1] + mine[x + 1][y - 1] + mine[x + 1][y] + mine[x + 1][y + 1] + mine[x][y + 1] + mine[x - 1][y + 1] - 8 * '0';
	return sum ;
}

void SweepMine(char mine[ROWS][COLS],char show[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	show[x][y] = ' ';
	for (i = x - 1; i <= x + 1 && x + 1 < ROWS && x - 1 >= 0; i++)
	{
		for (j = y - 1; j <= y + 1 && y + 1 < COLS && y - 1 >= 0; j++)
		{

			if (CountAround(mine, i, j) == 0)
			{
				if (show[i][j] == ' ')
				{
					continue;
				}
				SweepMine(mine, show, i, j);
			}
			else
			{
				show[i][j] = (char)CountAround(mine, i, j) + '0';
			}

		}

	}

	//for (i = x - 1; i <= x + 1 && x + 1 < ROWS && x - 1 >= 0; i++)
	//{
	//	for (j = y - 1; j <= y + 1 && y + 1 < COLS && y - 1 >= 0; j++)
	//	//{
	//	//	if (i == x && j == y)
	//	//	{
	//	//		continue;
	//	//	}
	//	//	else
	//	//	{
	//	//		if (CountAround(mine, i, j) == 0)
	//	//		{
	//	//		//	show[i - 1][j] = show[i - 1][j - 1] = show[i][j - 1] = show[i + 1][j - 1] = show[i + 1][j] = show[i + 1][j + 1] = show[i][j + 1] = show[i - 1][j + 1] = ' ';
	//	//			SweepMine(mine,show, i, j);
	//	//		}
	//	//		else
	//	//		{
	//	//			show[i][j] = (char)CountAround(mine, i, j) + '0';
	//	//		}
	//	//	}
	//	//}
	//		show[i][j] = ' ';

	//		
	//}

}

