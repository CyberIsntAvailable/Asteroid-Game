#pragma once

#include <GameDev2D.h>


namespace GameDev2D
{
	class Asteroid
	{
	public:
		Asteroid();
		~Asteroid();

		//Write game logic in the Update method
		void OnUpdate(float delta);

		//Render game objects in the Draw method
		void OnRender(BatchRenderer& batchRenderer);


		float DegreetoRadian(float degree);
	private:
		std::vector<Vector2> m_asteroidPoints; // m_asteroids is a vector of pointers. each pointer in the vector points to ONE asteroid
		Vector2 m_Position;
		Vector2 m_Direction;
		Vector2 m_Velocity;
		float m_Rotation;
		float m_AngularVelocity;
		float m_Angle = 0.0f;
	};
}
