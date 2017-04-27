
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable//, private sf::NonCopyable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update(float dt) = 0;
};
