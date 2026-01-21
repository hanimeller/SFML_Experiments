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

	auto updateSpritePos = [this](sf::Sprite* sprite)
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

	updateSpritePos(m_NormSprite.get());
	updateSpritePos(m_HoverSprite.get());
	updateSpritePos(m_PressSprite.get());
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
	Widget::OnMouseEnter();

	m_FrontSprite = m_HoverSprite.get();
}

void Button::OnMouseLeave() noexcept
{
	Widget::OnMouseLeave();

	m_FrontSprite = m_NormSprite.get();
}

void Button::OnMouseMove(int x, int y) noexcept
{
	Widget::OnMouseMove(x, y);
}

void Button::OnPress() noexcept
{
	Widget::OnPress();

	m_FrontSprite = m_PressSprite.get();
}

void Button::OnRelease() noexcept
{
	Widget::OnRelease();

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
