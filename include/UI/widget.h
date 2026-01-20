#pragma once
#include <SFML/Graphics.hpp>

static std::string GetButtonName(const sf::Mouse::Button& button)
{
	switch (button)
	{
	case sf::Mouse::Button::Left: return std::string("Left");
	case sf::Mouse::Button::Right: return std::string("Right");
	case sf::Mouse::Button::Middle: return std::string("Middle");
	}

	return std::string();
}

class Widget
{
public:
	Widget();
	virtual ~Widget() = default;

	virtual void Render(sf::RenderWindow* window);
	void CheckHover(int x, int y) noexcept;

	virtual void OnMouseEnter() noexcept;
	virtual void OnMouseLeave() noexcept;
	virtual void OnMouseMove(int x, int y) noexcept;

	virtual void OnPress() noexcept;
	virtual void OnRelease() noexcept;
	void CheckPress(int x, int y, const sf::Mouse::Button& button) noexcept;
	void CheckRelease(int x, int y, const sf::Mouse::Button& button) noexcept;

	virtual void SetSize(const sf::Vector2f& size) noexcept;
	virtual void SetPosition(const sf::Vector2f& pos) noexcept;

protected:
	sf::RectangleShape m_Shape{};
	sf::Vector2f m_Size{};
	sf::Vector2f m_Pos{};
	bool bHovered{ false };
	bool bPressed{ false };

	bool IsOverlap(int x, int y) noexcept;
};
