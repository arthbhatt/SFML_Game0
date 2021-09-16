#include "Platform/Platform.hpp"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

private:
	util::Platform platform;
	sf::Texture mPlayerTexture;

	sf::RenderWindow mWindow;
	sf::CircleShape mPlayer;
};

Game::Game()
{
#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(mWindow.getSystemHandle());
	// Use the screenScalingFactor
	mWindow.create(sf::VideoMode(200.0f * screenScalingFactor, 200.0f * screenScalingFactor), "SFML works!");
	platform.setIcon(mWindow.getSystemHandle());

	mPlayer = sf::CircleShape(mWindow.getSize().x / 2);
	mPlayer.setFillColor(sf::Color::White);

	mPlayerTexture.loadFromFile("content/sfml.png");
	mPlayer.setTexture(&mPlayerTexture);
}

void Game::run()
{
	while (mWindow.isOpen())
	{
		update();
		render();
	}
}

void Game::update()
{
	processEvents();
}

void Game::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

int main()
{
	Game game;
	game.run();

	return 0;
}
