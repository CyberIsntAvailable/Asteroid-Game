#pragma once

#include <GameDev2D.h>
#include "ship.h"
#include "Asteroid.h"
#include "Bullet.h"

namespace GameDev2D
{
	class Game
	{
	public:
		Game();
		~Game();

		//Write game logic in the Update method
		void OnUpdate(float delta);

		//Render game objects in the Draw method
		void OnRender(BatchRenderer& batchRenderer);

		//Input event methods
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
		void OnMouseMovedEvent(float mouseX, float mouseY);

		void CreateNewBullet();

	private:
		//Member variables GO HERE 
		Ship* m_ship;
		//Bullet* m_bullet;
		std::vector<Asteroid*> m_asteroids; // m_asteroids is a vector of pointers. each pointer in the vector points to ONE asteroid
		Bullet* m_Bullet;
	};
}
