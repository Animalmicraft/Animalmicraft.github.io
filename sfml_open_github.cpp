#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace {
constexpr unsigned int WINDOW_WIDTH = 760;
constexpr unsigned int WINDOW_HEIGHT = 300;
const std::string kHtmlUrl =
    "https://animalmicraft.github.io/laboratorio%20de%20informatica/paginas/index.html";

void openUrl(const std::string& url) {
#if defined(_WIN32)
    std::string command = "start \"\" \"" + url + "\"";
#elif defined(__APPLE__)
    std::string command = "open \"" + url + "\"";
#else
    std::string command = "xdg-open \"" + url + "\"";
#endif

    if (std::system(command.c_str()) != 0) {
        std::cerr << "No se pudo abrir el navegador con la URL: " << url << '\n';
    }
}
}  // namespace

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Abrir HTML de GitHub con SFML");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "No se pudo cargar una fuente del sistema.\n";
        return 1;
    }

    sf::Text title("Mini app SFML", font, 36);
    title.setFillColor(sf::Color::White);
    title.setPosition(220.f, 40.f);

    sf::Text subtitle("Click en el boton o presiona ENTER para abrir tu HTML en GitHub",
                      font, 20);
    subtitle.setFillColor(sf::Color(220, 220, 220));
    subtitle.setPosition(60.f, 105.f);

    sf::RectangleShape button(sf::Vector2f(280.f, 60.f));
    button.setFillColor(sf::Color(36, 128, 255));
    button.setOutlineThickness(2.f);
    button.setOutlineColor(sf::Color::White);
    button.setPosition(240.f, 180.f);

    sf::Text buttonText("Abrir HTML", font, 28);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(295.f, 193.f);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                openUrl(kHtmlUrl);
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                const sf::Vector2f mousePos(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y));

                if (button.getGlobalBounds().contains(mousePos)) {
                    openUrl(kHtmlUrl);
                }
            }
        }

        window.clear(sf::Color(30, 30, 45));
        window.draw(title);
        window.draw(subtitle);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
