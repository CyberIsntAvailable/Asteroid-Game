
#include "Asteroid.h"
#include "Constants.h"

GameDev2D::Asteroid::Asteroid()
{
	//Initialize members
	int NUM_SIDES = Math::RandomInt(5, 11);//create a random number of sides for the asteroid so that every asteroid looks different
	this->m_Rotation = Math::RandomFloat(0, 2) * (float)M_PI;//Rotation
	this->m_AngularVelocity = Math::RandomFloat(-0.5, 0.5) * (float)M_PI;//Rotation speed
	this->m_Velocity.x = Math::RandomFloat(-2.5, 2.5);
	this->m_Velocity.y = Math::RandomFloat(-2.5, 2.5);
	float randAngle = Math::RandomFloat(0, 360);//Pick a random angle for the asteroid to fly in direction wise
	m_Direction = Vector2(sin(DegreetoRadian(randAngle)), cos(DegreetoRadian(randAngle)));
	float radiansPerSide = 2.0f * (float)M_PI / (float)NUM_SIDES;
	this->m_Position = { 0, 0 };
	int randomSide = Math::RandomInt(0, 3);//pick which side the asteroid spawn in

	//Check which side the asteroid should spawn in and sets the position to a random spot on that side
	if (randomSide == 0)
	{
		this->m_Position.y = 40;
		this->m_Position.x = Math::RandomFloat(40, (float)GetScreenWidth() - 40);
	}
	else if (randomSide == 1)
	{
		this->m_Position.x = 40;
		this->m_Position.y = Math::RandomFloat(40, (float)GetScreenWidth() - 40);
	}
	else if (randomSide == 2)
	{
		this->m_Position.y = (float)GetScreenHeight() - 40;
		this->m_Position.x = Math::RandomFloat(40, (float)GetScreenWidth() - 40);
	}
	else if (randomSide == 3)
	{
		this->m_Position.x = (float)GetScreenWidth() - 40;
		this->m_Position.y = Math::RandomFloat(40, (float)GetScreenHeight() - 40);
	}

	//Make the asteroid
	for (int i = 0; i < NUM_SIDES; i++)
	{
		float angle = i * radiansPerSide;

		Vector2 point = Vector2(cos(angle), sin(angle)) * Math::RandomFloat(15, 35);

		this->m_asteroidPoints.push_back(point);
	}
	//Add one last point to connect back to the first point and create a connected loop
	this->m_asteroidPoints.push_back(this->m_asteroidPoints[0]);
}

GameDev2D::Asteroid::~Asteroid()
{
	//Doesn't do anything cause we ain't destroying the asteroids yet
}

void GameDev2D::Asteroid::OnUpdate(float delta)
{
	this->m_Position = this->m_Position + this->m_Direction * this->m_Velocity;

	m_Angle = m_Angle + (m_Rotation * m_AngularVelocity * delta);


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

void GameDev2D::Asteroid::OnRender(BatchRenderer& batchRenderer)
{
	//Renders the line strip for the pointer instance
	batchRenderer.RenderLineStrip(m_asteroidPoints, ColorList::LightGray, 2.0f, m_Position, m_Angle);
}

float GameDev2D::Asteroid::DegreetoRadian(float degree)//Sets any degree number to a radian number
{
	return (degree / 180.0f) * (float)M_PI;
}