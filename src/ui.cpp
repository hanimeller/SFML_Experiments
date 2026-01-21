#include "UI/ui.h"
#include "UI/widget.h"
#include <iostream>
#include <iomanip>

//void UI::UiManager::CreateWidget(EWidgetType type)
//{
//}

void UI::UiManager::AddWidget(Widget* w) noexcept
{
	if (w)
		m_Widgets.insert(w);
}

void UI::UiManager::RemoveWidget(Widget* w)
{
	m_Widgets.erase(w);
}

void UI::UiManager::RenderAllWidgets()
{
	for (const auto& w : m_Widgets)
	{
		w->Render();
	}
}

void UI::UiManager::OnMouseMove(int x, int y)
{
	for (const auto& w : m_Widgets)
	{
		w->CheckHover(x, y);
	}

	if (m_MouseAttachedWidget)
	{
		sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
		sf::Vector2f widgetPos = m_MouseAttachedWidget->GetPosition();

		float newWidth = (float)currentMousePos.x - widgetPos.x;
		float newHeight = (float)currentMousePos.y - widgetPos.y;

		if (newWidth < 0) newWidth = 0;
		if (newHeight < 0) newHeight = 0;

		m_MouseAttachedWidget->SetSize({ newWidth, newHeight });
	}
}

void UI::UiManager::OnMousePress(int x, int y, const sf::Mouse::Button& button)
{
	// clamp
	if (x < 0) x = 0;
	if (y < 0) y = 0;

	for (const auto& w : m_Widgets)
	{
		w->CheckPress(x, y, button);

		if (!m_MouseAttachedWidget)
		{
			if (w->IsOnResizeCorner(x, y))
				m_MouseAttachedWidget = w;
		}
	}
}

void UI::UiManager::OnMouseRelease(int x, int y, const sf::Mouse::Button& button)
{
	// clamp
	if (x < 0) x = 0;
	if (y < 0) y = 0;

	for (const auto& w : m_Widgets)
	{
		w->CheckRelease(x, y, button);
	}

	if (m_MouseAttachedWidget)
		m_MouseAttachedWidget = nullptr;
}

void UI::UiManager::MouseAttachWidget(Widget* w)
{
	if (!w)
		return;

	m_MouseAttachedWidget = w;
}
