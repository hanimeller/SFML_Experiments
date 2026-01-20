#pragma once

#include "UI/widget.h"
#include <functional>

class Button : public Widget
{
protected:
	sf::Sprite* m_FrontSprite{ nullptr };
	std::unique_ptr<sf::Sprite> m_NormSprite;
	std::unique_ptr<sf::Sprite> m_HoverSprite;
	std::unique_ptr<sf::Sprite> m_PressSprite;

	std::function<void()> m_CallBackFunc;

public:
	Button();

	template <typename F, typename... Args>
	void SetCallback(F&& func, Args&&... args)
	{
		auto lambda = [=]() mutable
			{
				func(args...);
			};

		m_CallBackFunc = std::move(lambda);
	}

	//void SetCallback(std::function<void()> func);

	void Render(sf::RenderWindow* window) override;

	void SetSize(const sf::Vector2f& size) noexcept;
	void SetPosition(const sf::Vector2f& pos) noexcept;

	void OnMouseEnter() noexcept override;
	void OnMouseLeave() noexcept override;
	void OnPress() noexcept override;
	void OnRelease() noexcept override;

	void SetNormalVisual(const sf::Texture& texture);
	void SetHoverVisual(const sf::Texture& texture);
	void SetPressVisual(const sf::Texture& texture);
};