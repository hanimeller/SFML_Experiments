#include "UI/button.h"
#include <iostream>

void Button::Render()
{
	Widget::Render();

	if (m_FrontSprite)
		window.draw(*m_FrontSprite);

	//window.draw(debugShape);
}

void Button::SetSize(sf::Vector2f size) noexcept
{
	Widget::SetSize(size);

	auto updateSprite = [this](sf::Sprite* sprite)
		{
			if (!sprite)
				return;

			sf::Vector2u texSize = sprite->getTexture().getSize();
			float origW = static_cast<float>(texSize.x);
			float origH = static_cast<float>(texSize.y);

			int width = std::min(static_cast<int>(m_Size.x), static_cast<int>(origW));
			int height = std::min(static_cast<int>(m_Size.y), static_cast<int>(origH));
			sprite->setTextureRect({ {0, 0}, {width, height} });

			sf::Vector2f centerPos;
			centerPos.x = m_Pos.x + (m_Size.x - static_cast<float>(width)) / 2.0f;
			centerPos.y = m_Pos.y + (m_Size.y - static_cast<float>(height)) / 2.0f;
			sprite->setPosition(centerPos);
		};

	updateSprite(m_NormSprite.get());
	updateSprite(m_HoverSprite.get());
	updateSprite(m_PressSprite.get());
}

void Button::SetPosition(const sf::Vector2f& pos) noexcept
{
	Widget::SetPosition(pos);

	if (!m_NormSprite)
		return;

	sf::Vector2f centerPos;
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

bool Button::IsOnResizeCorner(int x, int y) noexcept
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
		return true;
	}

	return false;
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
