#include <SFML/Graphics.hpp>
#include "UI/widget.h"
#include "UI/ui.h"
#include "UI/button.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), sf::String("Main Window"), sf::State::Windowed);

	UI::UiManager& uiManager = UI::UiManager::Instance();

	sf::Texture normTexture;
	if (!normTexture.loadFromFile("../resource/image/button.jpg"))
		return -1;
	sf::Texture hoverTexture;
	if (!hoverTexture.loadFromFile("../resource/image/buttonHover.jpg"))
		return -1;
	sf::Texture pressTexture;
	if (!pressTexture.loadFromFile("../resource/image/buttonPress.jpg"))
		return -1;

	auto f = [](const char* s, int x, float y)
		{
			std::cout << '\n' << s << x << y;
		};

	Button btn;
	btn.SetCallback(f, "asdqwe", 5, 3.f);

	btn.SetNormalVisual(normTexture);
	btn.SetHoverVisual(hoverTexture);
	btn.SetPressVisual(pressTexture);
	btn.SetPosition({ 100.f, 100.f });

	uiManager.AddWidget(&btn);

	while (window.isOpen())
	{
		while (std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (const auto& moveEvent = event->getIf<sf::Event::MouseMoved>())
			{
				uiManager.OnMouseMove(moveEvent->position.x, moveEvent->position.y);
			}

			if (const auto& pressEvent = event->getIf<sf::Event::MouseButtonPressed>())
			{
				uiManager.OnMousePress(pressEvent->position.x, pressEvent->position.y, pressEvent->button);
			}

			if (const auto& releaseEvent = event->getIf<sf::Event::MouseButtonReleased>())
			{
				uiManager.OnMouseRelease(releaseEvent->position.x, releaseEvent->position.y, releaseEvent->button);
			}
		}


		window.clear(sf::Color::Yellow);

		uiManager.RenderAllWidgets(&window);

		window.display();
	}

	return 0;
}