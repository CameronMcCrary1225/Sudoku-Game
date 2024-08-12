#include "sudokusolving.h"
#include <iostream>
#include <vector>
using namespace std;

bool checkifsolved(const vector < vector<int>>& sudoku)
{

	for (int i = 0; i < 9; ++i) {
		if (!verifyrow(sudoku, i)) {
			return false;
		}
	}
	for (int j = 0; j < 9; ++j) {
		if (!verifycolumn(sudoku, j)) {
			return false;
		}
	}
	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			if (!verifymatrix(sudoku, i, j)) {
				return false;
			}
		}
	}
	return true;
}

bool verifyrow(const vector < vector<int>>& sudoku, int row)
{
	vector<int> verification = { 1,2,3,4,5,6,7,8,9 };

	for (int num : sudoku[row]) {
		auto it = find(verification.begin(), verification.end(), num);
		if (it != verification.end()) {
			verification.erase(it);
		}
		else {
			return false;
		}
	}
	return verification.empty();

}

bool verifycolumn(const vector < vector<int>>& sudoku, int column)
{
	vector<int> verification = { 1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < 9; i++){
		int num = sudoku[i][column];
		auto it = find(verification.begin(), verification.end(), num);
		if (it != verification.end()) {
			verification.erase(it);
		}
		else {
			return false;
		}
	}
	return verification.empty();
}

int identifymatrix(int row, int column)
{
	int matrixrow = row / 3;
	int matrixcolumn = column / 3;
	return matrixrow * 3 + matrixcolumn;
}

bool verifymatrix(const vector < vector<int>>& sudoku,int row, int column)
{
	int matrixnum = identifymatrix(row, column);
	int startRow = matrixnum / 3 * 3;
	int startColumn = matrixnum % 3 * 3;
	vector<int> verification = { 1,2,3,4,5,6,7,8,9 };

	for (int i = startRow; i < startRow + 3; ++i) {
		for (int j = startColumn; j < startColumn + 3; ++j) {
			int num = sudoku[i][j];
			auto it = find(verification.begin(), verification.end(), num);
			if (it != verification.end()) {
				verification.erase(it);
			}
			else {
				return false;
			}
		}
	}
	return verification.empty();
}

void printRowStatus(const vector<vector<int>>& sudoku) {
	cout << "Sudoku Status:" << endl;
	for (const auto& row : sudoku) {
		for (int num : row) {
			cout << num << " ";
		}
		cout << endl;
	}
}

void printColumnStatus(const vector<vector<int>>& sudoku) {
	cout << "Column Status:" << endl;
	for (int j = 0; j < sudoku[0].size(); ++j) {
		cout << "Column " << j + 1 << ": ";
		for (const auto& row : sudoku) {
			cout << row[j] << " ";
		}
		cout << endl;
	}
}

void printMatrixStatus(const vector<vector<int>>& sudoku) {
	cout << "Matrix Status:" << endl;
	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			cout << "Matrix starting at (" << i << ", " << j << "): ";
			for (int m = i; m < i + 3; ++m) {
				for (int n = j; n < j + 3; ++n) {
					cout << sudoku[m][n] << " ";
				}
			}
			cout << endl;
		}
	}
}
bool validmove(const vector<vector<int>>& sudoku, int row, int column, int value) {
	for (int i = 0; i < 9; i++) {
		if (sudoku[row][i] == value) {
			return false;
		}
	}
	for (int j = 0; j < 9; j++) {
		if (sudoku[j][column] == value) {
			return false;
		}
	}
	int matrixnum = identifymatrix(row, column);
	int startRow = matrixnum / 3 * 3;
	int startColumn = matrixnum % 3 * 3;
	for (int k = startRow; k < startRow + 3; k++) {
		for (int x = startColumn; x < startColumn + 3; x++) {
			if (sudoku[k][x] == value){
				return false;
			}
		}
	}
	return true;
}

bool solvesudoku(vector<vector<int>>& sudoku)
{
	if (checkifsolved(sudoku)) {
		return true;
	}
	else {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (sudoku[i][j] == 0) {
					for (int k = 1; k <= 9; k++) {
						if (validmove(sudoku, i, j, k)) {
							sudoku[i][j] = k;
							if (solvesudoku(sudoku)) {
								return true;
							}
							sudoku[i][j] = 0;
						}
					}
					return false;
				}
			}
		}
		return false;
	}
}

void resetsudoku(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2)
{
	sudoku = sudoku2;
	return;
}
