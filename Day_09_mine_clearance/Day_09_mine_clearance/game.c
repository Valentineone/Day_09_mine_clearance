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
					printf("   ����");
				}
				else
				{
					printf("����");
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
	int i = 0;//��������ʹ�õı���
	int j = 0;
	int x = 0;//�������õ�����
	int y = 0;
	int input = 0;//�ж��Ƿ�Ҫ������Ϸ
	int count = 0;
	while (count < row*col - MINE_COUNT&&flag_count != MINE_COUNT)
	{
		count = 0;
		static int flag = 0;
		ShowBoard(show, row, col);
		printf("ɨ�ף����������x����������y��:>");
		scanf("%d %d", &x, &y);
		system("cls");
		if (x<1 || x>row || y<1 || y>col)//��֤����������������
		{
			printf("�Ƿ����룡���������룺>");
			continue;
		}
		else
		{	//��flag++����&&��ǰ������Ϊ����ʱ���ǳ��ֳ���һ�����ײȵ��׵�һ��δ����������Ϊ��mine[x][y] == '1'�ŵ�ǰ�������һ��mine[x][y] == '1'Ϊ�ٺ��Ҳ��ִ�У�flag��Ϊ0���Ӷ����³���
			if ( flag++ == 0 && mine[x][y] == '1')//��һ������һ�����ᱻը����flag++�Ǳ�֤��һ�βȵ����������׹����д�����޸��׵�λ��
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
				printf("���������㱻ը���ˣ�");
				printf("�����������������ģ�\n");
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
					//�����ж��Ƿ�δ�Ų��������ǵĲ����Ƿ��Ѵﵽ�׵��ܸ���,�������λ�õ�ԭ���ǣ����ܻ���ɨ���հ�����һ�¾�����չ����ɨ�����з��׵���
					for (i = 1; i <= row; i++)
					{
						for (j = 1; j <= col; j++)
						{
							if (show[i][j] != '*' && show[i][j] != 'M')//���������ĸ�����ʣ��δ���δ֪����ĸ���ֻ��Ϊ�׵��ܸ���ʱ�����׽������ж���Ӯ
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
						count = 0;//Ϊ�´��ж�֮ǰ����count��ֵ������count���ظ��ۼ�
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
							if (show[i][j] != '*' && show[i][j] != 'M')//���������ĸ�����ʣ��δ���δ֪����ĸ���ֻ��Ϊ�׵��ܸ���ʱ�����׽������ж���Ӯ
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
						count = 0;//Ϊ�´��ж�֮ǰ����count��ֵ������count���ظ��ۼ�
					}

				}
				FlagMine(show);
				if (flag_count == MINE_COUNT)
				{
					break;//���ֱ�ӱ�����ˣ���ֱ������������Ҫ�ж��Ƿ�����з��׶��Ų�����������ǰ������Ϸ
				}

				//��һ�κ�������չ������ж���ͬһ�Σ������ж��Ƿ�δ�Ų��������ǵĲ����Ƿ��Ѵﵽ�׵��ܸ�������count���淴ӳ����Ȼ��һ���Ų�֮��Ҫ����һ��count�����������ж��Ƿ���Խ�������β�������
				for (i = 1; i <= row; i++)
				{
					for (j = 1; j <= col; j++)
					{
						if (show[i][j] != '*' && show[i][j] != 'M')//���������ĸ�����ʣ��δ���δ֪����ĸ���ֻ��Ϊ�׵��ܸ���ʱ�����׽������ж���Ӯ
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
			printf("���Ѿ�����������ף���ϲ�㣡��Ӯ�ˣ�\n");
		}
		else
		{
			printf("���ǵ��ײ�����ȷ����սʧ�ܣ�\n");
			printf("�����������������ģ�\n");
			ShowBoard(mine, row, col);
		}
	}
	else
	{
		printf("���Ѿ��������з��׵�����ʣ�µ�ȫ���ף���ϲ�㣡��Ӯ�ˣ�\n");
		printf("������������ӣ�\n");
		ShowBoard(mine, row, col);
	}
	again:
	printf("���Ƿ��������Ϸ��\n");
	printf("************************\n");
	printf("*     1.�����          *\n");
	printf("*     0.��������        *\n");
	printf("************************\n");
	do
	{
		printf("��������ѡ��>\n");
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
			printf("�Ƿ����룡");
		}
	} while (1);
	system("cls");
}
void FlagMine(char show[ROWS][COLS])
{
	int input = 0;
	printf("���Ƿ������ף�\n");
	do
	{
		printf("1.��   2.���Ǻ��룬��Ҫ����\n");
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
			printf("���Ƿ������ף�\n");
			
			break;
		case 2:
			break;
		default:
			printf("�Ƿ����룡�������룺>\n");
		}
	} while (input == 1 || !(input == 2));
}
void Flag(char show[ROWS][COLS])
{
	int x = 0;
	int y = 0;
	do
	{
		printf("�������������׵����꣺>");
		scanf("%d %d", &x, &y);
		system("cls");
		if (x<1 || x>ROW || y<1 || y>COL)
		{
			ShowBoard(show, ROW, COL);
			printf("�Ƿ����룡���������룺>\n");
			continue;
		}
		else if(show[x][y] != '*')//����������ѱ��Ų飬��������
		{
			ShowBoard(show, ROW, COL);
			printf("�˴����Ų飬���������룡\n");
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

