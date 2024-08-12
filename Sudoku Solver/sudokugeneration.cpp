#include "sudokugeneration.h"
#include "sudokusolving.h"
#include <vector>
#include <random>
#include <algorithm>
#include "raylib.h"
using namespace std;

bool sudokugeneration::generatecompletedsudoku(vector<vector<int>> &sudoku, vector<vector<int>>& sudoku2){

	if (checkifsolved(sudoku)) {
		return true;
	}
	else {
		vector<int> numbertotry = { 1,2,3,4,5,6,7,8,9 };
		shuffleVector(numbertotry);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (sudoku[i][j] == 0) {
					for (int num : numbertotry) {
						if (validmove(sudoku, i, j, num)) {
							sudoku[i][j] = num;
							if (generatecompletedsudoku(sudoku, sudoku2)) {
								return true;
							}
							sudoku[i][j] = 0;
						}
					}
					return false;
				}
			}
		}
	}
	return false;
	sudoku2 = sudoku;
}

void sudokugeneration::shuffleVector(vector<int>& vector) {
	random_device rd;
	mt19937 g(rd());
	shuffle(vector.begin(), vector.end(), g);
}

void sudokugeneration::removeHalfSudoku(vector<vector<int>>& sudoku)
{
	for (int k = 0; k < 50; k++) {
		int i = rand() % 9;
		int j = rand() % 9;
		if (sudoku[i][j] != 0) {
			sudoku[i][j] = 0;
		}
	}
}

void sudokugeneration::reducetodifficulty(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2, int difficulty)
{
	int easyoptions = rand() % 5 + 2;
	int targetsingleoptions = (difficulty == 1) ? easyoptions : 0;
	int initialsingleoptions = countsingleoptions(sudoku);
	while (countsingleoptions(sudoku) > targetsingleoptions) {
		int row = rand() % 9;
		int col = rand() % 9;
		if (sudoku[row][col] != 0) {
			sudoku[row][col] = 0;
		}
	}
	if (difficulty == 1) {
		while (countsingleoptions(sudoku) < targetsingleoptions) {
			bool restored = false;
			for (int row = 0; row < 9 && !restored; ++row) {
				for (int col = 0; col < 9 && !restored; ++col) {
					if (sudoku[row][col] == 0 && sudoku2[row][col] != 0) {
						sudoku[row][col] = sudoku2[row][col];
						restored = true;
					}
				}
			}
			if (!restored) {
				break;
			}
		}
	}
	if (difficulty == 2) {
		int numToRemove = rand() % 29 + 10; // Remove 10-25 additional numbers
		int removedCount = 0;
		while (removedCount < numToRemove) {
			int row = rand() % 9;
			int col = rand() % 9;
			if (sudoku[row][col] != 0) {
				sudoku[row][col] = 0;
				removedCount++;
			}
		}
	}

}

vector<int> sudokugeneration::rowoptions(vector<vector<int>> sudoku, int i, int j)
{
	vector<int> verification = { 1,2,3,4,5,6,7,8,9 };
	for (int k = 0; k < 9; k++) {
		if (sudoku[i][k] != 0) {
			auto it = find(verification.begin(), verification.end(), sudoku[i][k]);
			if (it != verification.end()) {
				verification.erase(it);
			}
		}
	}
	return verification;
}

vector<int> sudokugeneration::columnoptions(vector<vector<int>> sudoku, int i, int j)
{
	vector<int> verification = { 1,2,3,4,5,6,7,8,9 };
	for (int k = 0; k < 9; k++) {
		if (sudoku[k][j] != 0) {
			auto it = find(verification.begin(), verification.end(), sudoku[k][j]);
			if (it != verification.end()) {
				verification.erase(it);
			}
		}
	}
	return verification;
}

vector<int> sudokugeneration::matrixoptions(vector<vector<int>> sudoku, int i, int j)
{
	vector<int> verification = { 1,2,3,4,5,6,7,8,9 };
	int matrix = identifymatrix(i, j);
	int rowstart = (matrix / 3) * 3;
	int columnstart = (matrix % 3) * 3;
	for (int row = rowstart; row < rowstart + 3; row++) {
		for (int col = columnstart; col < columnstart + 3; col++) {
			if (sudoku[row][col] != 0) {
				auto it = find(verification.begin(), verification.end(), sudoku[row][col]);
				if (it != verification.end()) {
					verification.erase(it);
				}
			}
		}
	}
	return verification;
}

int sudokugeneration::countoptions(vector<vector<int>> sudoku, int i, int j)
{
	vector<int> options;
	vector<int> rowopt = rowoptions(sudoku, i, j);
	vector<int> colopt = columnoptions(sudoku, i, j);
	vector<int> matrixopt = matrixoptions(sudoku, i, j);

	options.insert(options.end(), rowopt.begin(), rowopt.end());
	options.insert(options.end(), colopt.begin(), colopt.end());
	options.insert(options.end(), matrixopt.begin(), matrixopt.end());

	sort(options.begin(), options.end());
	options.erase(unique(options.begin(), options.end()), options.end());
	return options.size();
}

int sudokugeneration::countsingleoptions(vector<vector<int>> sudoku)
{
	int count = 0;
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			if (sudoku[row][col] == 0 && countoptions(sudoku, row, col) == 1) {
				count++;
			}
		}
	}
	return count;
}