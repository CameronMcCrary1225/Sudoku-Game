#pragma once
#include <vector>
#include <iostream>
using namespace std;

#ifndef SUDOKUGENERATION_H
#define SUDOKUGENERATION_H

class sudokugeneration {
public:
	bool generatecompletedsudoku(vector<vector<int>> &sudoku, vector<vector<int>>& sudoku2);
	void shuffleVector(vector<int>& vector);
	void removeHalfSudoku(vector<vector<int>>& sudoku);
	void reducetodifficulty(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2, int difficulty);
	vector<int> rowoptions(vector<vector<int>> sudoku, int i, int j);
	vector<int> columnoptions(vector<vector<int>> sudoku, int i, int j);
	vector<int> matrixoptions(vector<vector<int>> sudoku, int i, int j);
	int countoptions(vector<vector<int>> sudoku, int i, int j);
	int countsingleoptions(vector<vector<int>> sudoku);
private:
};

#endif

