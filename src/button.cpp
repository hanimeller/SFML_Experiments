#include "UI/button.h"
#include <iostream>

void Button::Render()
{
	Widget::Render();

	if (m_FrontSprite)
		window.draw(*m_FrontSprite);
}

void Button::SetSize(const sf::Vector2f& size) noexcept
{
	Widget::SetSize(size);

	if (m_NormSprite)
	{
		const auto& spriteRect = m_NormSprite->getGlobalBounds();
		int width = std::min(m_Size.x, spriteRect.size.x);
		int height = std::min(m_Size.y, spriteRect.size.y);

		sf::IntRect newSizeRect({0, 0}, {width, height});

		if (m_NormSprite)
		{
			m_NormSprite->setTextureRect(newSizeRect);
		}
	}

	if (m_HoverSprite)
	{
		const auto& spriteRect = m_HoverSprite->getGlobalBounds();
		int width = std::min(m_Size.x, spriteRect.size.x);
		int height = std::min(m_Size.y, spriteRect.size.y);

		sf::IntRect newSizeRect({ 0, 0 }, { width, height });

		if (m_HoverSprite) m_HoverSprite->setTextureRect(newSizeRect);
	}
	if (m_PressSprite)
	{
		const auto& spriteRect = m_PressSprite->getGlobalBounds();
		int width = std::min(m_Size.x, spriteRect.size.x);
		int height = std::min(m_Size.y, spriteRect.size.y);

		sf::IntRect newSizeRect({ 0, 0 }, { width, height });

		if (m_PressSprite) m_PressSprite->setTextureRect(newSizeRect);
	}
}

void Button::SetPosition(const sf::Vector2f& pos) noexcept
{
	Widget::SetPosition(pos);

	sf::Vector2f centerPos = pos;
	const auto& spriteRect = m_NormSprite->getGlobalBounds();
	centerPos.x = pos.x + ((m_Size.x / 2) - spriteRect.size.x / 2);
	centerPos.y = pos.y + ((m_Size.y / 2) - spriteRect.size.y / 2);

	if (m_NormSprite) m_NormSprite->setPosition(centerPos);
	if (m_HoverSprite) m_HoverSprite->setPosition(centerPos);
	if (m_PressSprite) m_PressSprite->setPosition(centerPos);
}

void Button::OnMouseEnter() noexcept
{
	m_FrontSprite = m_HoverSprite.get();
}

void Button::OnMouseLeave() noexcept
{
	m_FrontSprite = m_NormSprite.get();
	debugShape.setPosition({ 0.f, 0.f });
	window.setMouseCursor(std::move(sf::Cursor(sf::Cursor::Type::Arrow)));
}

void Button::OnMouseMove(int x, int y) noexcept
{
	sf::Vector2f corner = std::move(GetCorner(
		ECorner::RIGHT_BOTTOM, m_Pos, m_Size));

	corner.x -= 12.5f;
	corner.y -= 12.5f;

	if (
		(x >= corner.x && x < (corner.x + 12.5f))
		&&
		(y >= corner.y && y < (corner.y + 12.5f))
		)
	{
		debugShape.setPosition(corner);
		window.setMouseCursor(std::move(sf::Cursor(sf::Cursor::Type::SizeBottomRight)));
	}
	else
	{
		debugShape.setPosition({ 0.f, 0.f });
		window.setMouseCursor(std::move(sf::Cursor(sf::Cursor::Type::Arrow)));
	}
}

void Button::OnPress() noexcept
{
	m_FrontSprite = m_PressSprite.get();
}

void Button::OnRelease() noexcept
{
	m_FrontSprite = m_HoverSprite.get();

	if (m_CallBackFunc)
		m_CallBackFunc();
}

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
