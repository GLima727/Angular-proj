#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


#define MAX 2040

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    //if (!texture.loadFromFile("cute_image.jpg"))
        //return EXIT_FAILURE;
    sf::Sprite sprite(texture);


    // Create a graphical text to display
    sf::Font font;
    //if (!font.loadFromFile("arial.ttf"))
        //return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);


    // Load a music to play
    sf::Music music;
    //if (!music.openFromFile("nice_music.ogg"))
        //return EXIT_FAILURE;

    // Play the music
    //music.play();

    // Create a square shape with side length of 100 pixels
    sf::RectangleShape square(sf::Vector2f(100.0f, 100.0f));
    square.setFillColor(sf::Color::Red);
    square.setPosition(150.0f, 150.0f);   

    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Blue);


    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        window.draw(text);

        float x = static_cast<float>(std::rand() % 601);
        float y = static_cast<float>(std::rand() % 601);

        float cx = static_cast<float>(std::rand() % 601);
        float cy = static_cast<float>(std::rand() % 601);

        for(int i = 0; i <= MAX; i++){
            window.clear();

            square.setPosition(x, y);
            circle.setPosition(cx,cy);


            window.draw(square);
            window.draw(circle);

        }
        
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}