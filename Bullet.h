#pragma once

#include <GameDev2D.h>


namespace GameDev2D
{
	class Game;
	class Bullet
	{
	public:
		Bullet(const Vector2& position, const Vector2& velocity, Game* game);
		~Bullet();

		//Write game logic in the Update method
		void OnUpdate(float delta);

		//Render game objects in the Draw method
		void OnRender(BatchRenderer& batchRenderer);

		Vector2 GetPosition();
		Vector2 GetVelocity();
		void SpawnBullet(const Vector2& position, const Vector2& velocity);
	private:
		std::vector<Vector2> m_bulletPoints;
		Vector2 m_Position = {5,5};
		Vector2 m_Velocity = { 5,5 };
		Game* m_Game;
	};
}

