#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#define COLUMNS 30
#define ROWS 30

#define CELL_WIDTH 10
#define CELL_HEIGHT 10

#define ALIVE 1
#define DEAD 0

#define CHANCE_TO_LIVE 10 //in % change of cells to be alive in the beggining board
#define COLOR 0, 128, 128 //color of the cells in rbb

// get the desktop (screen) dimensions
sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

// set the window dimensions to match the desktop size
int windowWidth = desktopMode.width;
int windowHeight = desktopMode.height;

//these variables will be used to center the field on the screen and define where to start drawing the field
int x_start = (windowWidth - CELL_WIDTH * COLUMNS) / (2 * CELL_WIDTH);
int y_start = (windowHeight - CELL_HEIGHT * ROWS) / (2 * CELL_HEIGHT);


// create the window using the desktop size
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");

sf::RectangleShape cell(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));

std::vector<std::vector<int>> matrix(COLUMNS, std::vector<int>(ROWS, 0));
std::vector<std::vector<int>> nextgen_matrix(COLUMNS, std::vector<int>(ROWS, 0));


//define what a cell looks like
int drawCell(int i, int j) {
    cell.setFillColor(sf::Color(COLOR));
    cell.setPosition(i * CELL_WIDTH, j * CELL_HEIGHT);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Black);

    return 0;
}

//will draw the cell as black
int deleteCell(int i, int j) {
    cell.setFillColor(sf::Color::Black);
    cell.setPosition(i * CELL_WIDTH, j * CELL_HEIGHT);

    return 0;
}

//will draw the field one time and define a random start of dead and alive cells
int drawField() {

    for (int i = x_start; i < COLUMNS + x_start; i++) {
        for (int j = y_start; j < ROWS + y_start; j++) {

            drawCell(i, j);

            float chanceToDraw = static_cast<float>(std::rand() % 100);
            
            if (chanceToDraw < CHANCE_TO_LIVE) {
                window.draw(cell);
                matrix[i - x_start][j - y_start] = ALIVE;
            }
            else {
                matrix[i - x_start][j - y_start] = DEAD;
            }
        }
    }
    
    window.display();

    return 0;
}

//gets the number of alive neighbours around a cell
int getNeighbours(int col, int row) {

    int res = 0;
        
    for (int i = col - 1; i <= col + 1; i++) {
        for (int j = row - 1; j <= row + 1; j++) {

            if (i-x_start >= 0 && i-x_start < COLUMNS && j-y_start >= 0 && j-y_start < ROWS && (i != col || j != row)) {

                if (matrix[i-x_start][j-y_start] == ALIVE) {
                    res++;
                }
            }
        }
    }

    return res;
}

// will get the next generation of cells in a matrix that will be drawn after
int getNextGen() {

    int alive_neighbours = 0;

    for (int i = x_start; i < COLUMNS + x_start; i++) {
        for (int j = y_start; j < ROWS + y_start; j++) {

            alive_neighbours = getNeighbours(i, j);
            
            if (alive_neighbours <= 1 || alive_neighbours >= 4) {

                nextgen_matrix[i - x_start][j - y_start] = DEAD;
            }

            else if (alive_neighbours == 2 || alive_neighbours == 3) {

                nextgen_matrix[i-x_start][j-y_start] = ALIVE;
            }

        }
    }

    return 0;
}

//will draw the next gen matrix and update the old one
int drawNextGen() {

    for (int i = x_start; i < COLUMNS + x_start; i++) {
        for (int j = y_start; j < ROWS + y_start; j++) {
            matrix[i - x_start][j - y_start] = nextgen_matrix[i - x_start][j - y_start];

            if (matrix[i - x_start][j - y_start] == ALIVE) {
                drawCell(i, j);
                window.draw(cell);
            }
            else {
                deleteCell(i, j);
				window.draw(cell);
            }
        }

    }

    window.display();

    return 0;
}

int main() {

    int paused = 0;
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


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            window.clear();
            drawField();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) paused = 1; 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) paused = 0;

        if (!paused) {
            getNextGen();
            drawNextGen();
        }
    }
    return EXIT_SUCCESS;
}