#include <SFML/Graphics.hpp>
#include "UI/widget.h"
#include "UI/ui.h"
#include "UI/button.h"
#include "UI/listview.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), sf::String("Main Window"), sf::State::Windowed);

	UI::UiManager& uiManager = UI::UiManager::Instance(&window);

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

	Button btn{window};
	btn.SetCallback(f, "asdqwe", 5, 3.f);

	btn.SetNormalVisual(normTexture);
	btn.SetHoverVisual(hoverTexture);
	btn.SetPressVisual(pressTexture);
	btn.SetSize({ 250.f, 250.f });
	btn.SetPosition({ 25.f, 100.f });

	uiManager.AddWidget(&btn);


	while (window.isOpen())
	{
		while (std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (const auto& resizeEvent = event->getIf<sf::Event::Resized>())
			{
				sf::Vector2f centerPos{
					static_cast<float>(resizeEvent->size.x / 2),
					static_cast<float>(resizeEvent->size.y / 2) };
				sf::Vector2f size = {
					static_cast<float>(resizeEvent->size.x),
					static_cast<float>(resizeEvent->size.y) };

				sf::View newView({std::move(centerPos), std::move(size)});

				window.setView(std::move(newView));
			}

			if (const auto& moveEvent = event->getIf<sf::Event::MouseMoved>())
			{
				uiManager.OnMouseMove(uiManager.DragStartPos, moveEvent->position.x, moveEvent->position.y);
			}

			if (const auto& pressEvent = event->getIf<sf::Event::MouseButtonPressed>())
			{
				uiManager.DragStartPos = pressEvent->position;
				uiManager.OnMousePress(pressEvent->position.x, pressEvent->position.y, pressEvent->button);
			}

			if (const auto& releaseEvent = event->getIf<sf::Event::MouseButtonReleased>())
			{
				uiManager.OnMouseRelease(releaseEvent->position.x, releaseEvent->position.y, releaseEvent->button);
				uiManager.DragStartPos = sf::Vector2i();
			}
		}


		window.clear(sf::Color(47, 0, 64));

		uiManager.RenderAllWidgets(&window);

		window.display();
	}

	return 0;
}