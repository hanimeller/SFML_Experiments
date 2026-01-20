#include "UI/ui.h"
#include "UI/widget.h"

void UI::UiManager::AddWidget(Widget* w) noexcept
{
	if (w)
		m_Widgets.insert(w);
}

void UI::UiManager::RemoveWidget(Widget* w)
{
	m_Widgets.erase(w);
}

void UI::UiManager::RenderAllWidgets(sf::RenderWindow* window)
{
	for (const auto& w : m_Widgets)
	{
		w->Render(window);
	}
}

void UI::UiManager::OnMouseMove(int x, int y)
{
	for (const auto& w : m_Widgets)
	{
		w->CheckHover(x, y);
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
}
