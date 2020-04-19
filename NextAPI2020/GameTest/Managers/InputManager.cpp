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
	}

	if (m_canShoot) {
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
		{
			m_lastShot = elapsedTime;
			m_canShoot = false;
			m_levelManager->GetCurrentLevel()->SpawnBullet(false, m_levelManager->GetCurrentLevel()->GetSectionTop());
			m_gameManager->AddToScore(10);
			App::PlaySound("TestData\\Test.wav");
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			m_levelManager->GetCurrentLevel()->SpawnEnemy(SPIKE, { 100,100 });
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

InputManager::~InputManager()
{
}
