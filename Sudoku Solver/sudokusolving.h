#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
using namespace std;
#ifndef SUDOKUSOLING_H
#define SUDOKUSOLVING_H

const int rows = 9;
const int columns = 9;
//void printsudoku(int sudoku[rows][columns]);
bool checkifsolved(const vector < vector<int>>& sudoku);
bool verifyrow(const vector < vector<int>>& sudoku, int row);
bool verifycolumn(const vector < vector<int>>& sudoku, int column);
int identifymatrix(int row, int column);
bool verifymatrix(const vector < vector<int>>& sudoku, int row, int column);
void printRowStatus(const vector < vector<int>>& sudoku);
void printColumnStatus(const vector < vector<int>>& sudoku);
void printMatrixStatus(const vector < vector<int>>& sudoku);
bool validmove(const vector<vector<int>>& sudoku, int row, int column, int value);
bool solvesudoku(vector<vector<int>>& sudoku);
void resetsudoku(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2);
#endif