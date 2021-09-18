#include "Platform/Platform.hpp"

#define PLAYER_TEXTURE_FILE "content/images/Player.png"
#define FONT_FILE "content/fonts/F25_Bank_Printer/F25_Bank_Printer.ttf"

class Player
{
public:
	Player() :
		texture(),
		sprite(),
		isMovingUp(false),
		isMovingDown(false),
		isMovingLeft(false),
		isMovingRight(false),
		speed(50.f)
	{
		if (texture.loadFromFile(PLAYER_TEXTURE_FILE))
		{
			sprite.setTexture(texture);
		}
		else
		{
			std::cout << "Error loading player texture" << std::endl;
		}
	}

public:
	sf::Texture texture;
	sf::Sprite sprite;

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

	void showFps(sf::Time time)
	{
		char cstr[15];
		snprintf(cstr, 15, "FPS: %f", 1.f / time.asSeconds());
		fps.setString(cstr);
	}

private:
	util::Platform platform;
	sf::Texture mPlayerTexture;

	sf::RenderWindow mWindow;
	Player mPlayer;

	const sf::Time TimePerFrame;
	const uint32_t MaxUpdates;

	sf::Text fps;
	sf::Font font;
};

Game::Game() :
	mWindow(sf::VideoMode(640, 480), "SFML_Game0"),
	TimePerFrame(sf::seconds(1.f / 60.f)),
	MaxUpdates(10)
{
	//
	// Loading font to be used by onscreen text (to display fps)
	//
	font.loadFromFile(FONT_FILE);

	//
	// Configuring fps text
	//
	fps.setFont(font);
	fps.setFillColor(sf::Color::Red);
	fps.setCharacterSize(16);

	//
	// Placing Player object in the world
	//
	mPlayer.sprite.setPosition(100.f, 100.f);
}

void Game::run()
{
	uint32_t numUpdates = 0;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		//
		// Taking Fixed Time Steps
		//
		timeSinceLastUpdate += clock.restart();

		showFps(timeSinceLastUpdate);

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);

			//
			// Avoiding spiral of death
			//
			numUpdates++;
			if (numUpdates > MaxUpdates)
			{
				break;
			}
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

	mPlayer.sprite.move(movement);
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
	mWindow.draw(fps);
	mWindow.draw(mPlayer.sprite);
	mWindow.display();
}

int main()
{
	Game game;
	game.run();

	return 0;
}
