#include "raylib.h"
#include <iostream>
#include "sudokusolving.h"
#include <vector>
#include "interface.h"
#include "sudokugeneration.h"
#include <ctime>
#include "campaign.h"
using namespace std;

double timer = 0;

int main(void)
{
    srand(time(nullptr));
    const int rows = 9;
    const int columns = 9;
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tooltip Example");

    // Tooltip text
    const char* tooltipText = "Hover over a square and press a number";

    // Timer variables
    double timer = 0;
    const double tooltipDuration = 10.0; // Duration of the tooltip in seconds
    bool showTooltip = true;

    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose())
    {
        double frameTime = GetFrameTime();
        timer += frameTime;

        // Check if it's time to hide the tooltip
        if (timer >= tooltipDuration)
        {
            showTooltip = false;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the tooltip if it should be shown
        if (showTooltip)
        {
            DrawText(tooltipText, 10, 10, 20, GRAY);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    vector<vector<int>> sudoku = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    vector<vector<int>> sudoku2 =  sudoku; // doesn't change so you can reset back to original value
    const int userinteraction = 200;
    InitWindow(900 + userinteraction, 900, "sudoku");
    SetTargetFPS(60);

    Interface interface;
    sudokugeneration sudokugeneration;
    campaign campaignobj;

    while (!WindowShouldClose()) {
        double time = GetFrameTime();
        Vector2 mouseposition = GetMousePosition();
        if (mouseposition.x >= 0 && mouseposition.x <= 900 &&
            mouseposition.y >= 0 && mouseposition.y <= 900) {
            interface.HandlesudokuInput(sudoku);
        }
        else {
            interface.HandleInterfaceInput(sudoku, sudoku2, campaignobj);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        interface.Draw(sudoku);
        interface.checkcolor(sudoku);
        if (checkifsolved(sudoku)) {
            DrawRectangle(910, 790, 180, 100, GREEN);
            if (campaignobj.oncampaign) {
                campaignobj.currentlevel++;
                sudoku = campaignobj.loadcurrentlevel();
            }
        }
        else {
            DrawRectangle(910, 790, 180, 100, RED);
            timer += time;
        }
        DrawText(("timer: " + to_string(timer)).c_str(), 910, 770, 20, WHITE);
        EndDrawing();
    }
    return 0;
}