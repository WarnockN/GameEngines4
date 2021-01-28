#include "Game1.h"

//always declare the constructor of parent class when inheriting
Game1::Game1() : GameManager() {
}

Game1::~Game1() {
}

bool Game1::OnCreate() {
	return true;
}

void Game1::Update(const float deltaTime_) {
}

void Game1::Render() {
}
