#include "UI/button.h"
#include <iostream>

Button::Button()
{
}

void Button::Render(sf::RenderWindow* window)
{
	Widget::Render(window);

	if (m_FrontSprite)
		window->draw(*m_FrontSprite);
}

void Button::SetSize(const sf::Vector2f& size) noexcept
{
	Widget::SetSize(size);
}

void Button::SetPosition(const sf::Vector2f& pos) noexcept
{
	Widget::SetPosition(pos);

	if (m_NormSprite) m_NormSprite->setPosition(pos);
	if (m_HoverSprite) m_HoverSprite->setPosition(pos);
	if (m_PressSprite) m_PressSprite->setPosition(pos);
}

void Button::OnMouseEnter() noexcept
{
	m_FrontSprite = m_HoverSprite.get();
}

void Button::OnMouseLeave() noexcept
{
	m_FrontSprite = m_NormSprite.get();
}

void Button::OnPress() noexcept
{
	m_FrontSprite = m_PressSprite.get();
}

void Button::OnRelease() noexcept
{
	m_FrontSprite = m_NormSprite.get();

	if (m_CallBackFunc)
		m_CallBackFunc();
}

//void Button::SetCallback(std::function<void()> func)
//{
//	m_CallBackFunc = std::move(func);
//}

void Button::SetNormalVisual(const sf::Texture& texture)
{
	m_NormSprite = std::make_unique<sf::Sprite>(texture);
	m_NormSprite->setPosition(m_Pos);

	m_FrontSprite = m_NormSprite.get(); // Default visual
}

void Button::SetHoverVisual(const sf::Texture& texture)
{
	m_HoverSprite = std::make_unique<sf::Sprite>(texture);
	m_HoverSprite->setPosition(m_Pos);
}

void Button::SetPressVisual(const sf::Texture& texture)
{
	m_PressSprite = std::make_unique<sf::Sprite>(texture);
	m_PressSprite->setPosition(m_Pos);
}
