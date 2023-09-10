#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP
#include "Scene.h"
#include <raylib.h>
#include <pugixml.hpp>
// the main menu of the game
class MainMenuScene : public Scene
{
public:
	void Load() override;
	void Update() override;
	void Draw() override;
	void Unload() override;
};

#endif // !MAINMENUSCENE_HPP
