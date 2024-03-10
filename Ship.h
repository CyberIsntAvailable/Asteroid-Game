#pragma once

#include <GameDev2D.h>
//#include "Game.h" //This blows up the game


namespace GameDev2D
{
	class Game;
	class Bullet;
	class Ship
	{
	public:
		Ship(Game* game);
		~Ship();

		//Write game logic in the Update method
		void OnUpdate(float delta);

		//Render game objects in the Draw method
		void OnRender(BatchRenderer& batchRenderer);

		//Input event methods
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);

		float DegreetoRadian(float degree);

	private:
		std::vector<Vector2> m_pointShip;
		Vector2 m_position;
		Vector2 m_scale;
		Vector2 m_velocity;
		float m_angle;
		bool m_IsThrusting;
		bool m_IsThrustingBack;
		bool m_IsTurningLeft;
		bool m_IsTurningRight;

		Audio m_Jet;

		Bullet* m_Bullet;
		Game* m_Game;
	};
}
