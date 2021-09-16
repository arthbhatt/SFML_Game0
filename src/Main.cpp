#include "Platform/Platform.hpp"

class Player
{
public:
	Player() :
		isMovingUp(false),
		isMovingDown(false),
		isMovingLeft(false),
		isMovingRight(false),
		speed(5.f)
	{}

public:
	sf::CircleShape shape;
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;

	float speed;
};

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time);
	void render();

	void handlePlayerInput(
		sf::Keyboard::Key,
		bool);

private:
	util::Platform platform;
	sf::Texture mPlayerTexture;

	sf::RenderWindow mWindow;
	sf::Vector2u mWindowSize;
	Player mPlayer;

	const sf::Time TimePerFrame;
};

Game::Game() :
	TimePerFrame(sf::seconds(1.f / 60.f))
{
#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(mWindow.getSystemHandle());
	// Use the screenScalingFactor
	mWindow.create(sf::VideoMode(200.0f * screenScalingFactor, 200.0f * screenScalingFactor), "SFML works!");
	platform.setIcon(mWindow.getSystemHandle());

	mWindowSize = mWindow.getSize();

	mPlayer.shape = sf::CircleShape(mWindowSize.x / 10);
	mPlayer.shape.setFillColor(sf::Color::White);
	mPlayer.shape.setPosition(mWindowSize.x / 10, mWindowSize.x / 10);

	//mPlayerTexture.loadFromFile("content/sfml.png");
	//mPlayer.shape.setTexture(&mPlayerTexture);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		//
		// Taking Fixed Time Steps
		//
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);

	if (mPlayer.isMovingUp)
	{
		movement.y -= mPlayer.speed;
	}
	if (mPlayer.isMovingDown)
	{
		movement.y += mPlayer.speed;
	}
	if (mPlayer.isMovingLeft)
	{
		movement.x -= mPlayer.speed;
	}
	if (mPlayer.isMovingRight)
	{
		movement.x += mPlayer.speed;
	}
	movement *= deltaTime.asSeconds();

	mPlayer.shape.move(movement);
}

void Game::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				mWindow.close();
				break;

			default:
				break;
		}

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Game::handlePlayerInput(
	sf::Keyboard::Key key,
	bool isPressed)
{
	switch (key)
	{
		case sf::Keyboard::W:
			mPlayer.isMovingUp = isPressed;
			break;

		case sf::Keyboard::S:
			mPlayer.isMovingDown = isPressed;
			break;

		case sf::Keyboard::A:
			mPlayer.isMovingLeft = isPressed;
			break;

		case sf::Keyboard::D:
			mPlayer.isMovingRight = isPressed;
			break;

		default:
			break;
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer.shape);
	mWindow.display();
}

int main()
{
	Game game;
	game.run();

	return 0;
}
