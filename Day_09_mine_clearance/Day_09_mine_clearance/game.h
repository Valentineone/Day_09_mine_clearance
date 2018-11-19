#pragma once
#ifndef _GAME__H_
#define _GAME__H_
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS ROW + 2
#define MINE_COUNT 10

void ShowBoard(char array[ROWS][COLS],int row,int  col);
void InitBoard(char array[ROWS][ROWS], int rows, int  cols,char el);
void SetMine(char mine[ROWS][COLS],int row,int col,int count);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS],int row,int col);
int  CountAround(char mine[ROWS][COLS], int x, int y);
void SweepMine(char mine[ROWS][COLS],char show[ROWS][COLS] ,int x, int y);
void FlagMine(char show[ROWS][COLS]);
void Flag(char show[ROWS][COLS]);








#endif // !_GAME__H_

