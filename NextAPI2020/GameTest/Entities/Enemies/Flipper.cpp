#include "stdafx.h"
#include "Flipper.h"

Flipper::Flipper(Vec2 position, Vec2 sectionTop, Vec2 sectionBack, Vec2 section, float adjustment)
{

	m_isAlive = true;
	m_hurtOnTouch = true;
	m_hitRadius = 3.0f;
	m_adjustment = adjustment;

	PopulateStops(position, sectionTop, sectionBack, section);
}

Flipper::~Flipper()
{
}

void Flipper::Update(float deltaTime)
{
}

void Flipper::Draw()
{
}

void Flipper::GetShot()
{
}
