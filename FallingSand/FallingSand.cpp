#include "raylib.h"
#include <iostream>

//game variables
const int w = 1280;
const int h = 720;

const int particleSize = 10;
int grid[w / particleSize][h / particleSize];
int mouseposx;
int mouseposy;

bool hints_enabled = true;
bool grid_enabled = false;
bool FPS_enabled = true;

// It closes the game
void Kill_Game()
{
	EndDrawing();
	CloseWindow();
}

void Restart()
{
	// Clears the grid
	for (int i = 0; i < (w / particleSize); i++)
	{
		for (int j = 0; j < (h / particleSize); j++)
		{
			grid[i][j] = 0;
		}
	}
}

void InitGame()
{
	InitWindow(w, h, "Falling Sand Simulation");
	SetTargetFPS(60);
	Restart();
}

void PaintSand()
{
	if (GetMouseX() < w && GetMouseY() < h)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				grid[(GetMouseX() / particleSize) + i][(GetMouseY() / particleSize) + j] = 1;
			}
		}
	}
}

void PaintWall()
{
	if (GetMouseX() < w && GetMouseY() < h)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				grid[(GetMouseX() / particleSize) + i][(GetMouseY() / particleSize) + j] = 2;
			}
		}
	}
}

int main()
{
	InitGame();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color{ 0, 0, 0, 255 });

		if (IsKeyPressed(KEY_G))
		{
			if (grid_enabled == true)
			{
				grid_enabled = false;
			}
			else
			{
				grid_enabled = true;
			}
		}

		if (IsKeyPressed(KEY_F1))
		{
			if (hints_enabled == true)
			{
				hints_enabled = false;
			}
			else
			{
				hints_enabled = true;
			}
		}

		if (IsKeyPressed(KEY_F))
		{
			if (FPS_enabled == true)
			{
				FPS_enabled = false;
			}
			else
			{
				FPS_enabled = true;
			}
		}

		if (IsKeyPressed(KEY_R))
		{
			Restart();
		}

		//It moves the sand
		for (int i = 0; i < (w / particleSize); i++)
		{
			for (int j = (h / particleSize) - 1; j >= 0; j--)
			{
				if (grid[i][j] == 1 && j < ((h / particleSize) - 1))
				{
					int x = (rand() % 2) + 1;
					if (grid[i][j + 1] == 0)
					{
						std::swap(grid[i][j], grid[i][j + 1]);
					}
					else if (grid[i - 1][j + 1] == 0 && x == 1)
					{
						std::swap(grid[i][j], grid[i-1][j + 1]);
					}
					else if (grid[i + 1][j + 1] == 0 && x == 2)
					{
						std::swap(grid[i][j], grid[i + 1][j + 1]);
					}
				}
			}
		}


		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			PaintSand();
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			PaintWall();
		}
		
		//Grid stuff
		if (grid_enabled == true)
		{
			// Draws a grid, it's very useful, but inefficient.
			for (int i = 0; i < (w / particleSize); i++)
			{
				for (int j = 0; j < (h / particleSize); j++)
				{
					DrawRectangleLines(i * particleSize, j * particleSize, particleSize, particleSize, Color{ 50 ,50 ,50 , 255 });
				}
			}
		}

		//Renderer
		for (int i = 0; i < (w / particleSize); i++)
		{
			for (int j = 0; j < (h / particleSize); j++)
			{
				if (grid[i][j] == 1)
				{
					DrawRectangle(i * particleSize, j * particleSize, particleSize, particleSize, Color{ 225,225,128,255 });
				}
				else if (grid[i][j] == 2)
				{
					DrawRectangle(i * particleSize, j * particleSize, particleSize, particleSize, Color{ 200,200,200,255 });
				}
			}
		}

		if (hints_enabled == true)
		{
			DrawText("Press F1 to toggle hints", 25, 25, 25, Color{ 255,255,255,255 });
			DrawText("Press G to toggle grid", 25, 50, 25, Color{ 255,255,255,255 });
			DrawText("Press F to toggle FPS", 25, 75, 25, Color{ 255,255,255,255 });
			DrawText("Press R to restart the simulation", 25, 100, 25, Color{ 255,255,255,255 });
		}

		if (FPS_enabled)
		{
			DrawFPS(1, 0);
		}

		EndDrawing();
	}

	Kill_Game();

	return 0;
}
