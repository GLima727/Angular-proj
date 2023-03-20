#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>

#define SELF_SIZE 10

//#define M_PI atan(1) * 4

#define RIGHT 0.0
#define BOTTOM_RIGHT 45.0
#define BOTTOM 90.0
#define BOTTOM_LEFT 135.0
#define LEFT 180.0
#define TOP_LEFT 225.0
#define TOP 270.0
#define TOP_RIGHT 315.0

//define what a cell looks like
int drawSelf(sf::RenderWindow *window, sf::CircleShape self , sf::Color color, sf::Vector2f position) {

    self.setPosition(position.x, position.y);
    self.setFillColor(color);
    (*window).draw(self);

    return 0;
}

sf::Vector2f moveSelf(sf::RenderWindow* window, sf::Sprite background, sf::CircleShape self, sf::Color color, sf::Vector2f position, int distance, float angle, float speed) {

    float dx = speed * std::cos(angle * M_PI / 180.f);
    float dy = speed * std::sin(angle * M_PI / 180.f);

    while (distance >= 0) {

        position.x += dx;
        position.y += dy;

        distance -= fabs(dx) + fabs(dy); 
        std::cout << "distance" << distance << std::endl;

        //(*window).draw(background);
        drawSelf(window, self, color, position);

        (*window).display();
        (*window).clear();
    }

    return position;
}
int main() {

    // get the desktop (screen) dimensions
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // set the window dimensions to match the desktop size
    int windowWidth = desktopMode.width;
    int windowHeight = desktopMode.height;

    // create the window using the desktop size
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");

    sf::Texture texture;

    if (!texture.loadFromFile("./space.jpg"))
    {
        std::cout << "Error Loading Texture" << std::endl;
    }

    sf::Sprite background(texture);

    sf::CircleShape self(SELF_SIZE + 20);

    sf::CircleShape self2(SELF_SIZE+ 40);

    sf::CircleShape self3(SELF_SIZE + 50);

    std::cout << "windowWidth: " << windowWidth << "windowheight" << windowHeight << std::endl;

    sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));

    sf::Vector2f center((windowWidth / 2) - SELF_SIZE, (windowHeight / 2) - SELF_SIZE);
    sf::Vector2f center2((windowWidth / 2) - SELF_SIZE + 30, (windowHeight / 2) - SELF_SIZE + 30);
    sf::Vector2f center3((windowWidth / 2) - SELF_SIZE + 50, (windowHeight / 2) - SELF_SIZE + 50);

    sf::Vector2f position = center;
    

    int toggle = 1;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();

                break;

            case sf::Event::KeyPressed:
                if (sf::Keyboard::Key::Up == event.key.code)
                {
                    view.move(sf::Vector2f(0, -1));
                }
                else if (sf::Keyboard::Key::Down == event.key.code)
                {
                    view.move(sf::Vector2f(0, 5));
                }
                else if (sf::Keyboard::Key::Left == event.key.code)
                {
                    view.move(sf::Vector2f(-1, 0));
                }
                else if (sf::Keyboard::Key::Right == event.key.code)
                {
                    view.move(sf::Vector2f(1, 0));
                }
                break;
            }

        }


        for (int i = 0; i <= 100; i += 1) {
            float lol = static_cast<float>(std::rand() % 360);          

			position = moveSelf(&window,background, self, sf::Color::Blue, position, 10, lol, 1);
            center2 = moveSelf(&window,background, self2, sf::Color::Red, center2, 10, lol + 100, 1);
                        center3 = moveSelf(&window,background, self3, sf::Color::Green, center3, 10, -lol, 1);


		}
        // for (int i = 0; i <= 100; i += 1) {
        //     float lol = static_cast<float>(std::rand() % 360);
		// 	position = moveSelf(&window,background, self2, sf::Color::Red, position, 20, lol, 0.1);
            
		// }
        window.setView(view);

    }
    return EXIT_SUCCESS;
}