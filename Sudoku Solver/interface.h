#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"
#include <vector>
#include <string>
#include "sudokusolving.h"
#include "campaign.h"
using namespace std;


class Interface {
public:

	class Button {
	public:
		Rectangle size;
		string name;
		bool clicked;
		Button(Rectangle size, string name, bool clicked);
		void Draw();
	};
	Interface();
	vector<Button> buttons = { { {910, 10, 180, 100}, "Solve", false },{ {910, 120, 180, 100}, "Reset", false }, { {910, 230, 180, 100}, "Easy Sudoku", false }, { {910, 340, 180, 100}, "Hard Sudoku", false }, {{ 910, 450, 180, 100 }, "Hint", false},{{ 910, 560, 180, 100 }, "Campaign", false}
};
	void Draw(const vector<vector<int>>& sudoku);
	void HandlesudokuInput(vector<vector<int>>& sudoku);
	void HandleInterfaceInput(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2, campaign& campaignobj);
	void getrandomhint(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2);
	void checkcolor(vector<vector<int>>& sudoku);
	bool verifyrowduplicates(const vector<vector<int>>& sudoku, int row);
	bool verifycolumndpulicates(const vector<vector<int>>& sudoku, int column);
	bool verifymatrixduplicates(const vector<vector<int>>& sudoku, int row, int column);
	Color redwrong{ 255, 0, 0, 60 };
private:
	int numrows = 9;
	int numcolumns = 9;
	int boxsize = 100;

};
#endif