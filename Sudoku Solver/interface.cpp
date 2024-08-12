#include "interface.h"
#include "raylib.h"
#include "vector"
#include "string"
#include <iostream>
#include "sudokugeneration.h"
#include "campaign.h"
using namespace std;

extern double timer;

Interface::Interface() {

}

void Interface::Draw(const vector<vector<int>>& sudoku) {
	for (int row = 0; row < numrows; row++) {
		for (int column = 0; column < numcolumns; column++) {
			DrawRectangle(column * boxsize + 1, row * boxsize + 1, boxsize-1,boxsize-1, WHITE);
			int num = sudoku[row][column];
			if (num != 0) {
				DrawText(to_string(num).c_str(), column * boxsize + boxsize / 2 - 10, row * boxsize + boxsize / 2 - 10, 20, BLACK);
			}
		}
	}
    Rectangle solvebuttonrec = { 910, 10, 180, 100 };
    Button solvebutton(solvebuttonrec, "Solve", false);
    solvebutton.Draw();
    Rectangle resetbuttonrec = {910, 120, 180, 100};
    Button resetbutton(resetbuttonrec, "Reset", false);
    resetbutton.Draw();
    Rectangle generateeasy = { 910, 230, 180, 100 };
    Button generateeasybutton(generateeasy, "Easy Sudoku", false);
    generateeasybutton.Draw();
    Rectangle generatehard = { 910, 340, 180, 100 };
    Button generatehardbutton(generatehard, "Hard Sudoku", false);
    generatehardbutton.Draw();
    Rectangle hint = { 910, 450, 180, 100 };
    Button hintbutton(hint, "Hint", false);
    hintbutton.Draw();
    Rectangle campaign = { 910, 560, 180, 100 };
    Button campaignbutton(campaign, "Campaign", false);
    campaignbutton.Draw();
}

void Interface::HandlesudokuInput(vector<vector<int>>& sudoku) {
    int numberInput = -1;
    if (IsKeyDown(KEY_ZERO)) {
        numberInput = '0';
    }
    else if (IsKeyDown(KEY_ONE)) {
        numberInput = '1';
    }
    else if (IsKeyDown(KEY_TWO)) {
        numberInput = '2';
    }
    else if (IsKeyDown(KEY_THREE)) {
        numberInput = '3';
    }
    else if (IsKeyDown(KEY_FOUR)) {
        numberInput = '4';
    }
    else if (IsKeyDown(KEY_FIVE)) {
        numberInput = '5';
    }
    else if (IsKeyDown(KEY_SIX)) {
        numberInput = '6';
    }
    else if (IsKeyDown(KEY_SEVEN)) {
        numberInput = '7';
    }
    else if (IsKeyDown(KEY_EIGHT)) {
        numberInput = '8';
    }
    else if (IsKeyDown(KEY_NINE)) {
        numberInput = '9';
    }
    Vector2 cursorPosition = GetMousePosition();
    int column = static_cast<int>(cursorPosition.x / boxsize);
    int row = static_cast<int>(cursorPosition.y / boxsize);
    if (row >= 0 && row < numrows && column >= 0 && column < numcolumns && numberInput >= '0' && numberInput <= '9') {
        sudoku[row][column] = numberInput - '0';
    }
}

void Interface::HandleInterfaceInput(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2, campaign& campaignobj)
{
    sudokugeneration generator;
    for (const auto& button : buttons) {
        Vector2 cursorposition = GetMousePosition();
        bool currentbutton = CheckCollisionPointRec(cursorposition, button.size);
        if ( currentbutton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (button.name == "Solve") {
                solvesudoku(sudoku);
            }
            if (button.name == "Reset") {
                resetsudoku(sudoku, sudoku2);
                timer = 0;
            }
            if (button.name == "Easy Sudoku") {
                timer = 0;
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        sudoku[i][j] = 0;
                    }
                }
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        sudoku2[i][j] = sudoku[i][j];
                    }
                }
                generator.generatecompletedsudoku(sudoku, sudoku2);
                generator.removeHalfSudoku(sudoku);
                generator.reducetodifficulty(sudoku, sudoku2, 1);
                sudoku2 = sudoku;
            }
            if (button.name == "Hard Sudoku") {
                timer = 0;
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        sudoku[i][j] = 0;
                    }
                }
                generator.generatecompletedsudoku(sudoku,sudoku2);
                generator.removeHalfSudoku(sudoku);
                generator.reducetodifficulty(sudoku, sudoku2, 2);
                sudoku2 = sudoku;
            }
            if (button.name == "Hint") {
                getrandomhint(sudoku, sudoku2); //hints dont work in campaign
            }
            if (button.name == "Campaign") {
                campaignobj.oncampaign = true;
                sudoku = campaignobj.loadcurrentlevel();

            }
        }
    }
}

void Interface::getrandomhint(vector<vector<int>>& sudoku, vector<vector<int>>& sudoku2)
{
    if (!checkifsolved(sudoku)) {
        int row;
        int column;
        do {
            row = rand() % 9;
            column = rand() % 9;
        } while (sudoku[row][column] != 0);
        vector<vector<int>> sudoku3 = sudoku2;
        solvesudoku(sudoku3);
        sudoku[row][column] = sudoku3[row][column];
    }
}

void Interface::checkcolor(vector<vector<int>>& sudoku)
{
    for (int i = 0; i < 9; i++) {
        if (!verifyrowduplicates(sudoku, i)) {
            DrawRectangle(0, i * boxsize, 9 * boxsize, boxsize, redwrong);
        }
    }
    for (int j = 0; j < 9; j++) {
        if (!verifycolumndpulicates(sudoku, j)) {
            DrawRectangle(j * boxsize, 0, boxsize, 9 * boxsize, redwrong);
        }
    }
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!verifymatrixduplicates(sudoku, i, j)) {
                DrawRectangle(j * boxsize, i * boxsize, 3 * boxsize, 3 * boxsize, redwrong);
            }
        }
    }

}

Interface::Button::Button(Rectangle size, string name, bool clicked) : size(size), name(name), clicked(false)
{
}

void Interface::Button::Draw()
{
    DrawRectangleRounded(size, .1f, 0, WHITE);
    DrawText(name.c_str(), size.x + size.width / 2 - MeasureText(name.c_str(), 20) / 2,
        size.y + size.height / 2 - 10, 20, BLACK);
}

bool Interface::verifyrowduplicates(const vector<vector<int>>& sudoku, int row)
{
    vector<bool> seen(10, false); 
    for (int num : sudoku[row]) {
        if (num != 0) { 
            if (seen[num]) {
                return false;
            }
            else {
                seen[num] = true;
            }
        }
    }
    return true; 
}

bool Interface::verifycolumndpulicates(const vector<vector<int>>& sudoku, int column)
{
    vector<bool> seen(10, false);

    for (int i = 0; i < 9; i++) {
        int num = sudoku[i][column];
        if (num != 0) { 
            if (seen[num]) {
                return false; 
            }
            else {
                seen[num] = true; 
            }
        }
    }
    return true; 
}

bool Interface::verifymatrixduplicates(const vector<vector<int>>& sudoku, int row, int column)
{
    int matrixnum = identifymatrix(row, column);
    int startRow = matrixnum / 3 * 3;
    int startColumn = matrixnum % 3 * 3;
    vector<bool> seen(10, false);

    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startColumn; j < startColumn + 3; ++j) {
            int num = sudoku[i][j];
            if (num != 0) {
                if (seen[num]) {
                    return false;
                }
                else {
                    seen[num] = true;
                }
            }
        }
    }
    return true;
}