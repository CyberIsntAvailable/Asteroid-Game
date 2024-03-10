#include "Ship.h"
#include "Bullet.h"
#include "Constants.h"

GameDev2D::Ship::Ship(Game* game) :
	m_Jet("Jet")
{
	this->m_Game = game;
	m_Bullet = new Bullet(Vector2(0, 0), Vector2(0, 0), this->m_Game);

	//Initialize all the variables
	m_position = { (float)GetHalfScreenWidth(), (float)GetHalfScreenHeight() };
	this->m_scale = { SHIP_SIZE, SHIP_SIZE };
	this->m_angle = 0.0f;
	this->m_IsThrusting = false;
	this->m_IsThrustingBack = false;
	this->m_IsTurningLeft = false;
	this->m_IsTurningRight = false;

	this->m_pointShip = { Vector2(-1.0f, 0.0f), Vector2(0.0f, 2.0f), Vector2(1.0f, 0.0f), Vector2(0.0f, 1.0f) };
	this->m_pointShip.push_back(this->m_pointShip[0]);
	this->m_pointShip.push_back(this->m_pointShip[1]);

	//Go through each point and scale it to a good size
	for (Vector2& vec : this->m_pointShip)
	{
		vec.x *= this->m_scale.x;
		vec.y *= this->m_scale.y;
	}
}

GameDev2D::Ship::~Ship()
{

}

void GameDev2D::Ship::OnUpdate(float delta)
{
	//If its turning left or right influence the changes accordingly
	if (m_IsTurningLeft)
	{
		this->m_angle = this->m_angle + (ANGULAR_CHANGE * delta);
	}
	else if (m_IsTurningRight)
	{
		this->m_angle = this->m_angle - (ANGULAR_CHANGE * delta);
	}

	//acceleration = direction * rate of acceleration
	Vector2 acceleration = Vector2(sin(DegreetoRadian(-m_angle)), cos(DegreetoRadian(-m_angle))) * RATE_OF_ACCELERATION;

	//Check if its thrusting forward or backward, effect the velocity accordingly
	if (m_IsThrusting)
	{
		this->m_velocity += acceleration * delta; //vf = vi + a * t
	}
	else if (m_IsThrustingBack)
	{
		this->m_velocity -= acceleration * delta; //vf = vi + a * t

	}

	//Finally calcultate the displacement based on how much time has passed from each frame then change the position accordingly
	Vector2 displacement = m_velocity * delta;
	this->m_position += displacement;

	//Cap the velocity if its going too fast
	if (m_velocity.Length() > MAX_SPEED)
	{
		this->m_velocity = m_velocity.Normalized() * MAX_SPEED;
	}

	//If the Ship goes off the screen then teleport it to the other side of the screen
	if (m_position.y > (float)GetScreenHeight())
	{
		this->m_position.y = 0;
	}
	else if (m_position.y < 0)
	{
		this->m_position.y = (float)GetScreenHeight();
	}
	else if (m_position.x > (float)GetScreenWidth())
	{
		this->m_position.x = 0;
	}
	else if (m_position.x < 0)
	{
		this->m_position.x = (float)GetScreenWidth();
	}
}

void GameDev2D::Ship::OnRender(BatchRenderer& batchRenderer)
{
	//Render line strip for ship
	batchRenderer.RenderLineStrip(m_pointShip, ColorList::White, THICKNESS, this->m_position, DegreetoRadian(this->m_angle));
}

void GameDev2D::Ship::OnKeyEvent(KeyCode keyCode, KeyState keyState)
{
	if (IsKeyDown(KeyCode::Space) == true)
	{
		//TODO: Fire Projectiles

		//Fire projectile
		Vector2 direction(cos(m_angle), sin(m_angle));
		Vector2 position = m_position + direction;
		Vector2 velocity = direction * LASER_SPEED;

		m_Bullet->SpawnBullet(position, velocity);
	}



	if (IsKeyDown(KeyCode::Left) == true)
	{
		//Handle gamelogic
		m_IsTurningLeft = true;
	}
	else if (IsKeyDown(KeyCode::Right) == true)
	{
		//Handle gamelogic
		m_IsTurningRight = true;
	}
	else
	{
		//If you let go it stops turning
		m_IsTurningLeft = false;
		m_IsTurningRight = false;
	}

	if (IsKeyDown(KeyCode::Up) == true)
	{
		//Handle gamelogic
		m_IsThrusting = true;
		m_Jet.Play();
	}
	else if (IsKeyDown(KeyCode::Down) == true)
	{
		m_IsThrustingBack = true;
		m_Jet.Play();
	}
	else
	{
		//If you let go it stops thrusting
		m_IsThrusting = false;
		m_IsThrustingBack = false;
		m_Jet.Stop();
	}
}

float GameDev2D::Ship::DegreetoRadian(float degree)// sets any degree to a radian
{
	return (degree / 180.0f) * (float)M_PI;
}
