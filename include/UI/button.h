#pragma once

#include "UI/widget.h"

class Button : public Widget
{
protected:
	sf::Sprite* m_FrontSprite{ nullptr };
	std::unique_ptr<sf::Sprite> m_NormSprite;
	std::unique_ptr<sf::Sprite> m_HoverSprite;
	std::unique_ptr<sf::Sprite> m_PressSprite;

public:
	using Widget::Widget;
	explicit Button(sf::RenderWindow& w);

	void Render() override;

	void SetSize(sf::Vector2f size) noexcept override;
	void SetPosition(const sf::Vector2f& pos) noexcept override;

	void OnMouseEnter() noexcept override;
	void OnMouseLeave() noexcept override;
	void OnMouseMove(int x, int y) noexcept override;
	void OnPress(const sf::Mouse::Button& button) noexcept override;
	void OnRelease() noexcept override;

	void SetNormalVisual(const sf::Texture& texture);
	void SetHoverVisual(const sf::Texture& texture);
	void SetPressVisual(const sf::Texture& texture);
};