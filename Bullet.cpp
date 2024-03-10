#include "Bullet.h"
#include "Constants.h"
#include "Game.h"

namespace GameDev2D
{

	Bullet::Bullet(const Vector2& position, const Vector2& velocity, Game* game) :
		m_Position(5,5),
		m_Velocity(5,5)
	{
		float radiansPerSide = 2.0f * (float)M_PI / (float)4;
		
		m_Game = game;

		//Make the bullet
		for (int i = 0; i < 4; i++)
		{
			float angle = i * radiansPerSide;

			Vector2 tempPoint = Vector2(cos(angle), sin(angle)) * 5;

			this->m_bulletPoints.push_back(tempPoint);
		}
		//Add one last point to connect back to the first point and create a connected loop
		this->m_bulletPoints.push_back(this->m_bulletPoints[0]);
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::OnUpdate(float delta)
	{
		this->m_Position = this->m_Position + this->m_Velocity;

		//Teleports asteroids to the opposite side of the screen if it hits a side
		if (m_Position.y > (float)GetScreenHeight())
		{
			this->m_Position.y = 0;
		}
		else if (m_Position.y < 0)
		{
			this->m_Position.y = (float)GetScreenHeight();
		}
		else if (m_Position.x > (float)GetScreenWidth())
		{
			this->m_Position.x = 0;
		}
		else if (m_Position.x < 0)
		{
			this->m_Position.x = (float)GetScreenWidth();
		}
	}

	void Bullet::OnRender(BatchRenderer& batchRenderer)
	{
		//Renders the line strip for the pointer instance
		batchRenderer.RenderLineStrip(m_bulletPoints, ColorList::LightGray, 2.0f, m_Position, 0);
	}

	Vector2 Bullet::GetPosition()
	{
		return m_Position;
	}

	Vector2 Bullet::GetVelocity()
	{
		return m_Velocity;
	}

	void Bullet::SpawnBullet(const Vector2& position, const Vector2& velocity)
	{
		this->m_Position = position;
		this->m_Velocity = velocity;

		m_Game->CreateNewBullet();
	}
}

//#include "Bullet.h"
//
//namespace GameDev2D
//{
//	Bullet::Bullet(const Vector2& position, const Vector2& velocity)
//	{
//		float radiansPerSide = 2.0f * (float)M_PI / 4.0f;
//		m_Position = { 0 , 0 };
//
//
//		for (int i = 0; i < 4; i++)
//		{
//			float angle = i * radiansPerSide;
//
//			Vector2 point = Vector2(cos(angle), sin(angle)) * 5;
//
//			this->m_bulletPoints.push_back(point);
//		}
//		//Add one last point to connect back to the first point and create a connected loop
//		this->m_bulletPoints.push_back(this->m_bulletPoints[0]);
//	}
//
//	Bullet::~Bullet()
//	{
//	}
//	void Bullet::OnUpdate(float delta)
//	{
//		m_Position += m_Velocity * delta;
//
//		//Teleports asteroids to the opposite side of the screen if it hits a side
//		if (m_Position.y > (float)GetScreenHeight())
//		{
//			this->m_Position.y = 0;
//		}
//		else if (m_Position.y < 0)
//		{
//			this->m_Position.y = (float)GetScreenHeight();
//		}
//		else if (m_Position.x > (float)GetScreenWidth())
//		{
//			this->m_Position.x = 0;
//		}
//		else if (m_Position.x < 0)
//		{
//			this->m_Position.x = (float)GetScreenWidth();
//		}
//	}
//
//	void Bullet::OnRender(BatchRenderer& batchRenderer)
//	{
//	}
//
//	Vector2 Bullet::GetPosition()
//	{
//		return m_Position;
//	}
//
//}
//