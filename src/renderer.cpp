#include "renderer.h"

namespace sp9k {
    void Renderer::renderTexture(std::string texName, sf::Vector2f pos) {
        sf::Sprite sprite;

        sprite.setTexture(textureCache.getTexture(texName));
        sprite.setPosition(pos);
         
        window.draw(sprite);
    }

    void Renderer::renderTextureCentered(std::string texName, sf::Vector2f pos) {
        sf::Sprite sprite;

        auto &tex = textureCache.getTexture(texName);
        sprite.setTexture(tex);
        sprite.setPosition(pos);
        sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
         
        window.draw(sprite);
    }

} // namespace sp9k
