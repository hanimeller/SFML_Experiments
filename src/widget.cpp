#include "UI/widget.h"
#include "UI/ui.h"
#include <iostream>
#include <iomanip>

Widget::Widget()
{
	m_Shape.setSize({ 75.f, 35.f });
	m_Shape.setPosition({ 2.f, 2.f });
	m_Shape.setFillColor(sf::Color::Transparent);
	m_Shape.setOutlineColor(sf::Color::Green);
	m_Shape.setOutlineThickness(2.f);

	UI::UiManager::Instance().AddWidget(this);
}

bool Widget::IsOverlap(int x, int y) noexcept
{
	sf::Vector2f shapeSize = m_Shape.getSize();
	sf::Vector2f shapePos = m_Shape.getPosition();

	if (
		(x > shapePos.x && x < (shapePos.x + shapeSize.x))
		&&
		(y > shapePos.y && y < (shapePos.y + shapeSize.y))
		)
	{
		return true;
	}
	return false;
}

void Widget::CheckHover(int x, int y) noexcept
{
	bool bIsOverlap = IsOverlap(x, y);
	if (bIsOverlap)
	{
		if (!bHovered)
		{
			OnMouseEnter();
			bHovered = true;
		}
	}
	else
	{
		if (bHovered)
		{
			OnMouseLeave();
			bHovered = false;
		}
	}

	if (bHovered)
		OnMouseMove(x, y);
}

void Widget::OnMouseEnter() noexcept
{
	//std::cout << "\nOnMouseEnter";

	m_Shape.setOutlineColor(sf::Color::Yellow);
}

void Widget::OnMouseLeave() noexcept
{
	//std::cout << "\nOnMouseLeave";

	m_Shape.setOutlineColor(sf::Color::Green);
}

void Widget::OnMouseMove(int x, int y) noexcept
{
	//std::cout << std::setw(20) << "\rOnMouseMove X: " << x << " Y: " << y;
}

void Widget::OnPress() noexcept
{
	std::cout << "\nPress";
	m_Shape.setOutlineColor(sf::Color::Blue);
}

void Widget::OnRelease() noexcept
{
	std::cout << "\nRelease";
	m_Shape.setOutlineColor(sf::Color::Green);
}

void Widget::CheckPress(int x, int y, const sf::Mouse::Button& button) noexcept
{
	//std::cout << '\n' << GetButtonName(button);
	if (IsOverlap(x, y))
	{
		bPressed = true;
		OnPress();
	}
}

void Widget::CheckRelease(int x, int y, const sf::Mouse::Button& button) noexcept
{
	//std::cout << '\n' << GetButtonName(button);
	if (IsOverlap(x, y) && bPressed)
	{
		bPressed = false;
		OnRelease();
	}
}

void Widget::SetSize(const sf::Vector2f& size) noexcept
{
	m_Size = size;
	m_Shape.setSize(size);
}

void Widget::SetPosition(const sf::Vector2f& pos) noexcept
{
	m_Pos = pos;
	m_Shape.setPosition(pos);
}

void Widget::Render(sf::RenderWindow* window)
{
	//window->draw(m_Shape);
}
