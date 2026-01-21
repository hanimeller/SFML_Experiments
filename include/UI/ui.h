#pragma once

#include <unordered_set>
#include <SFML/Graphics.hpp>

class Widget;

//enum class EWidgetType : uint8_t
//{
//    WIDGET,
//    BUTTON,
//    LISTVIEW
//};

namespace UI
{
	class UiManager
	{
    public:

        static UiManager& Instance(sf::RenderWindow* window = nullptr) {
            static std::unique_ptr<UiManager> instance;

            if (!instance) {
                if (window == nullptr) {
                    throw std::runtime_error("First call to getInstance must provide a window pointer!");
                }
                instance.reset(new UiManager(*window));
            }

            return *instance;
        }

        explicit UiManager(sf::RenderWindow& w) : window(w) {}
        ~UiManager() = default;
        UiManager(const UiManager&) = delete;
        UiManager& operator=(const UiManager&) = delete;

        //void CreateWidget(EWidgetType type);
        void AddWidget(Widget* w) noexcept;
        void RemoveWidget(Widget* w);
        void RenderAllWidgets();
        
        void OnMouseMove(int x, int y);
        void OnMousePress(int x, int y, const sf::Mouse::Button& button);
        void OnMouseRelease(int x, int y, const sf::Mouse::Button& button);

        void MouseAttachWidget(Widget* w);

    private:
        sf::RenderWindow& window;
        Widget* m_MouseAttachedWidget{ nullptr };
        std::unordered_set<Widget*> m_Widgets;
	};
}