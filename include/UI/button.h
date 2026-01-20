#include "UI/widget.h"


class Button : public Widget
{
protected:
	sf::Sprite* m_FrontSprite{ nullptr };
	std::unique_ptr<sf::Sprite> m_NormSprite;
	std::unique_ptr<sf::Sprite> m_HoverSprite;
	std::unique_ptr<sf::Sprite> m_PressSprite;

public:
	Button();

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