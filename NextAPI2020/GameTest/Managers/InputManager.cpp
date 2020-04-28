#include "stdafx.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "GameManager.h"
#include "App/app.h"

InputManager::InputManager(GameManager *gameManager, LevelManager *levelManager, Player *player)
{
	m_gameManager = gameManager;
	m_levelManager = levelManager;
	m_player = player;
	m_currentTime = 0.0f;
	m_lastMovement = 0.0f;
	m_lastShot = 0.0f;
	m_canMove = true;
	m_canShoot = true;
}

void InputManager::Update(float deltaTime)
{
	switch (m_gameManager->GetCurrentState()) {

		// Start game, Quit, Maybe level select?
	case MENU:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		{
			m_gameManager->StartGame();
		}
		break;

		// Quit, restart, Unpause
	case PAUSED:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		{
			m_gameManager->UnPause();
		}
		break;

		// Fall through: same inputs as gameplay
	case WARPING:

	// Gameplay inputs: move left or right, shoot, superzapper.
	case GAMEPLAY: 
	{

		if (m_player->IsAlive()) 
		{

			float elapsedTime = m_currentTime + deltaTime;

			if (m_canMove) {

				if (App::GetController().GetLeftThumbStickX() > 0.5f)
				{
					m_lastMovement = elapsedTime;
					m_canMove = false;
					m_levelManager->GetCurrentLevel()->MoveRight();
				}

				if (App::GetController().GetLeftThumbStickX() < -0.5f)
				{
					m_lastMovement = elapsedTime;
					m_canMove = false;
					m_levelManager->GetCurrentLevel()->MoveLeft();
				}
			}

			if (m_canShoot) {

				if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, false))
				{
					m_lastShot = elapsedTime;
					m_canShoot = false;
					m_levelManager->GetCurrentLevel()->SpawnBullet(false, m_levelManager->GetCurrentLevel()->GetSectionTop());
					App::PlaySound("TestData\\Test.wav");
				}
				if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
				{
					if (m_player->GetSuper() == 1) {
						m_lastShot = elapsedTime;
						m_canShoot = false;
						m_levelManager->GetCurrentLevel()->SuperZapper();
						m_player->UseSuper();
					}
				}
			}

			if (elapsedTime - m_lastMovement > m_moveDelay) {
				m_canMove = true;
			}

			if (elapsedTime - m_lastShot > m_shootDelay) {
				m_canShoot = true;
			}
			m_currentTime = elapsedTime;
		}

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		{
			m_gameManager->Pause();
		}
		break;
	}

	// Game Over: Back to menu, Restart or Quit
	case GAMEOVER:

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		{
			m_gameManager->StartGame();
		}
		break;
	}
	
}

InputManager::~InputManager()
{
}
