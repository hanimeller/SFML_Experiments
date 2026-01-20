#pragma once

#include <unordered_set>
#include <SFML/Graphics.hpp>

class Widget;

namespace UI
{
	class UiManager
	{
    public:
        static UiManager& Instance()
        {
            static UiManager instance; // thread-safe (C++11)
            return instance;
        }

        UiManager(const UiManager&) = delete;
        UiManager& operator=(const UiManager&) = delete;

        void AddWidget(Widget* w) noexcept;
        void RemoveWidget(Widget* w);
        void RenderAllWidgets(sf::RenderWindow* window);
        
        void OnMouseMove(int x, int y);
        void OnMousePress(int x, int y, const sf::Mouse::Button& button);
        void OnMouseRelease(int x, int y, const sf::Mouse::Button& button);

    private:
        UiManager() = default;
        ~UiManager() = default;

        std::unordered_set<Widget*> m_Widgets;
	};
}