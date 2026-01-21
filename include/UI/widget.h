#pragma once
#include <SFML/Graphics.hpp>

enum class ECorner : uint8_t
{
	LEFT_TOP,
	LEFT_BOTTOM,
	RIGHT_TOP,
	RIGHT_BOTTOM
};

static std::string GetButtonName(const sf::Mouse::Button& button) noexcept
{
	switch (button)
	{
	case sf::Mouse::Button::Left: return std::string("Left");
	case sf::Mouse::Button::Right: return std::string("Right");
	case sf::Mouse::Button::Middle: return std::string("Middle");
	}

	return std::string();
}

static sf::Vector2f GetCorner(
	ECorner c,
	const sf::Vector2f& pos,
	const sf::Vector2f& size) noexcept
{
	sf::Vector2f result;

	switch (c)
	{
	case ECorner::LEFT_TOP:
		result.x = pos.x;
		result.y = pos.y;
		break;
	case ECorner::LEFT_BOTTOM:
		result.x = pos.x;
		result.y = pos.y + size.y;
		break;
	case ECorner::RIGHT_TOP:
		result.x = pos.x + size.x;
		result.y = pos.y;
		break;
	case ECorner::RIGHT_BOTTOM:
		result.x = pos.x + size.x;
		result.y = pos.y + size.y;
		break;
	}

	return result;
}

class Widget
{
public:
	explicit Widget(sf::RenderWindow& w);
	virtual ~Widget() = default;

	virtual void Render();
	void CheckHover(int x, int y) noexcept;

	virtual void OnMouseEnter() noexcept;
	virtual void OnMouseLeave() noexcept;
	virtual void OnMouseMove(int x, int y) noexcept;

	virtual void OnPress() noexcept;
	virtual void OnRelease() noexcept;
	void CheckPress(int x, int y, const sf::Mouse::Button& button) noexcept;
	void CheckRelease(int x, int y, const sf::Mouse::Button& button) noexcept;

	virtual bool IsOnResizeCorner(int x, int y) noexcept { return false; }

	virtual void SetSize(sf::Vector2f size) noexcept;
	virtual void SetPosition(const sf::Vector2f& pos) noexcept;
	virtual sf::Vector2f GetPosition() { return m_Pos; }

protected:
	sf::RenderWindow& window;
	sf::RectangleShape m_Shape{};
	sf::RectangleShape debugShape{};
	sf::Vector2f m_Size{};
	sf::Vector2f m_Pos{};
	bool bHovered{ false };
	bool bPressed{ false };

	bool IsOverlap(int x, int y) noexcept;
};
