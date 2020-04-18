#include "stdafx.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "App/app.h"

InputManager::InputManager(GameManager *gameManager, LevelManager *levelManager, Player *player)
{
	m_gameManager = gameManager;
	m_levelManager = levelManager;
	m_player = player;
}

void InputManager::Update(float deltaTime)
{

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		m_levelManager->GetCurrentLevel()->MoveRight();
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		m_levelManager->GetCurrentLevel()->MoveLeft();
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{

	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{

	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{

	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{

	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{

	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{

	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{

	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{

	}
}

InputManager::~InputManager()
{
}
