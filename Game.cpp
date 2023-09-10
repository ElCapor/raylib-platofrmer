#include "Game.hpp"
#include "LayoutManager.h"
// to do : move this to a better place
LayoutManager* LayoutManager::instance = nullptr;


Game::Game()
{
    this->g_GameManager = new GameManager();
}


bool Game::Initialize()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Game");
    
    SetTargetFPS(60);
    
    // init the custom classes
    LayoutManager::GetInstance()->Init();
    this->g_GameManager->Initialize();

    return true;
}

void Game::Update()
{
    // Update HUD first
    LayoutManager::GetInstance()->Update();
    // Update scenes
    this->g_GameManager->GetCurrentScene()->Update();
}

void Game::Render()
{
    // draw everything here
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // draw the ui before the game
    LayoutManager::GetInstance()->Draw();
    this->g_GameManager->GetCurrentScene()->Draw();

    EndDrawing();
}
void Game::Run()
{
    this->Initialize();
    while (!WindowShouldClose())
    {
        this->Update();
        this->Render();
    }
    CloseWindow();
}

Game::~Game()
{
    
}