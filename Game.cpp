#include "Game.h"
#include "Constants.h"



namespace GameDev2D
{
	Game::Game()
	{
		m_ship = new Ship(this);
		//Creates 20 asteroids or what ever you re assign the size to before compiling
		for (int i = 0; i < NUM_ASTEROIDS; i++)
		{
			Asteroid* asteroid = new Asteroid();
			this->m_asteroids.push_back(asteroid);
		}
		m_Bullet = new Bullet(Vector2(0,0), Vector2(0,0), this);
	}

	Game::~Game()
	{

	}

	void Game::OnUpdate(float delta)
	{
		m_ship->OnUpdate(delta);
		m_Bullet->OnUpdate(delta);

		for (int i = 0; i < m_asteroids.size(); i++)
		{
			Asteroid* asteroid = this->m_asteroids.at(i);
			asteroid->OnUpdate(delta); // basically, ask each rock to draw itself
		}

	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();

		//Render your Sprites and SpriteFonts here

		//Renders the ship (There is only one so we don't need a loop)
		this->m_ship->OnRender(batchRenderer);
		this->m_Bullet->OnRender(batchRenderer);

		//Goes through each asteroid and renders it
		for (int i = 0; i < this->m_asteroids.size(); i++)
		{
			Asteroid* asteroid = this->m_asteroids.at(i);
			asteroid->OnRender(batchRenderer); // basically, ask each rock to draw itself
		}

		batchRenderer.EndScene();
	}

	void Game::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		this->m_ship->OnKeyEvent(keyCode, keyState);//Handles key events for the ship
	}

	void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
	{

	}

	void Game::OnMouseMovedEvent(float mouseX, float mouseY)
	{

	}
	 
	void Game::CreateNewBullet()
	{
		Bullet* bullet = new Bullet(m_Bullet->GetPosition(), m_Bullet->GetVelocity(), this);
	}



	//void Game::SpawnBullet(const Vector2& position, const Vector2& velocity)
	//{
	//	//Ensure the laser pointer is null
	//	if (m_bullet == nullptr)
	//	{
	//		//Create a new laser object on the heap
	//		m_bullet = new Bullet(position, velocity);
	//	}
	//}
}