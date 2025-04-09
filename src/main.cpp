#include "raylib.h"
#include <iostream>
#include "Game.h"

#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion


Color DARK_BLUE = { 44, 44, 127, 255 };
const Color LIGHT_BLUE = { 59, 85, 162, 255 };
double lastUpdateTime = 0;

bool EventTrigger(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main(void)
{

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(500, 620, "raylib [core] example - basic window");
	SetTargetFPS(60);

	Font gameFont = LoadFontEx(RESOURCES_PATH "Fonts/monogram.ttf", 64, 0, 0);

	Game game = Game();

#pragma region imgui
	rlImGuiSetup(true);

	//you can use whatever imgui theme you like!
	//ImGui::StyleColorsDark();
	//imguiThemes::yellow();
	//imguiThemes::gray();
	imguiThemes::green();
	//imguiThemes::red();
	//imguiThemes::embraceTheDarkness();


	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.FontGlobalScale = 2;

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		//style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.5f;
		//style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
	}

#pragma endregion



	while (!WindowShouldClose())
	{

		game.HandleInput();
		if (EventTrigger(0.2))
		{
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(DARK_BLUE);
		DrawTextEx(gameFont, "Score", { 365, 15 }, 38, 2, WHITE);
		DrawTextEx(gameFont, "Next", { 370, 175 }, 38, 2, WHITE);
		if (game.gameOver)
		{
			DrawTextEx(gameFont, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
		}
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, LIGHT_BLUE);

		char scoreText[10] = {};
		sprintf(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(gameFont, scoreText, 38, 2);

		DrawTextEx(gameFont, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);


		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, LIGHT_BLUE);
#pragma region imgui
		rlImGuiBegin();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
#pragma endregion
		
		game.Draw();
		


#pragma region imgui
		rlImGuiEnd();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
#pragma endregion

		EndDrawing();
	}


#pragma region imgui
	rlImGuiShutdown();
#pragma endregion



	CloseWindow();

	return 0;
}