/*
 * Homework 5 CIE
 * Name: Joseph Krueger
 * Date: 10/23/22
 * Description: Make additions to Bejeweled game including sounds, fonts,
 * timer, score tracking, and my own personal feature.
 * Personal Feature: Welcome screen with instructions that prompts
 * the user to make a choice of how many unique gems will be used. The game
 * then runs using this value to determine how many gems are used. Also includes
 * end screen which displays the final score when the game ends.
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <chrono>

using namespace sf;

// initializing tile size and offset
int ts = 54; //tile size
Vector2i offset(48, 24);

// initial countdown value
const int INITIAL_TIME = 5000;

// Piece class - stores everything related to each gem
class Piece {
public:
    Piece() {
        match = 0;
        alpha = 255;
        x = 0;
        y = 0;
        col = 10;
        row = 10;
        kind = 0;
        match = 0;
        alpha = 255;
    }

    // setters
    void setX(const int val){x = val;}
    void setY(const int val){y = val;}
    void setCol(const int val){col = val;}
    void setRow(const int val){row = val;}
    void setKind(const int val){kind = val;}
    void setMatch(const int val){match = val;}
    void setAlpha(const int val){alpha = val;}

    // getters
    int getX() const {return x;}
    int getY() const {return y;}
    int getCol() const {return col;}
    int getRow() const {return row;}
    int getKind() const {return kind;}
    int getMatch() const {return match;}
    int getAlpha() const {return alpha;}

private:
    int x=0, y=0, col=0, row=0, kind=0, match=0, alpha=0;
};
// initializing grid
Piece grid[10][10];

// Description: swap two pieces in the game grid
// Input: p1 and p2 are Piece objects pass-by-value to swap
// Output: updated grid of pieces
void swap(Piece p1, Piece p2) {
    int tmp = p1.getCol();
    p1.setCol(p2.getCol());
    p2.setCol(tmp);
    tmp = p1.getRow();
    p1.setRow(p2.getRow());
    p2.setRow(tmp);
    grid[p1.getRow()][p1.getCol()] = p1;
    grid[p2.getRow()][p2.getCol()] = p2;
}

// Description: Initializes the grid
// Inputs: Number of unique gems chosen by user
// Outputs: Initialized grid (resets game)
void initGrid(int numUniqueGems)
{
    // randomizing the sprite shape (Piece) and initializing grid
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            // Setting the number of kind possibilities to user selection of unique gems
            // 3 options if '3' was selected in welcome screen
            // 4 options if '4' was selected in welcome screen
            // 5 options if '5' was selected in welcome screen
            grid[i][j].setKind(rand()%numUniqueGems);
            grid[i][j].setCol(j);
            grid[i][j].setRow(i);
            grid[i][j].setX(j*ts);
            grid[i][j].setY(i * ts);
        }
    }
}

//===============================
// Main Function driver
//===============================
int main() {
    srand(time(0));

    // loading textures
    Texture t1, t2;
    if (!t1.loadFromFile("images/background.png")) { return EXIT_FAILURE; }
    if (!t2.loadFromFile("images/gems.png")) { return EXIT_FAILURE; }

    // creating sprite object
    Sprite background(t1), gems(t2);

    // Welcome window
    RenderWindow welcome(VideoMode(740, 480), "Welcome to the game!");
    bool gameStart = false; // Bool that is true if user selects choice of unique gems
    std::string choiceTitle; // Title changes based on user selection
    int numGems; // number of unique gems chosen by user in welcome screen

    // Loading in welcome font
    /*
     * Marlboro by Dieter Steffmann, https://www.1001freefonts.com/marlboro.font,
     * License: Free
     */
    sf::Font welcomeFont;
    if (!welcomeFont.loadFromFile("fonts/Marlboro.ttf"))
    {
        return EXIT_FAILURE;
    }
    //===========================================================================
    /*
     * MY FEATURE PART 1: Welcome Window with instructions
     */
    //===========================================================================
    while(welcome.isOpen())
    {
        // instructions and choice text to be displayed on screen
        sf::Text instructionText;
        sf::Text choiceText;

        // Setting the text for instructions
        instructionText.setCharacterSize(45);
        instructionText.setFont(welcomeFont);
        instructionText.setString("Welcome to the Game!\n"
                              "Instructions: Click two gems to swap\n"
                              "places. When the specific number of\n"
                              "gems are matched, they will disappear\n"
                              "giving you points. Click 'R' to reset\n"
                              "the grid. Get as many points as you\n"
                              "can before the time runs out!\n");

        instructionText.setFillColor(sf::Color::Green);

        //===========================================================================
        /*
         * MY FEATURE PART 2: User Choice for how many unique gems will be in the game
         */
        //===========================================================================
        // Setting the text for choices
        choiceText.setPosition(0, 325);
        choiceText.setCharacterSize(45);
        choiceText.setFont(welcomeFont);
        choiceText.setString("Press '3' for 3 unique gems,\n"
                                  "'4' for 4 unique gems,\n"
                                  "or '5' for 5 unique gems");

        choiceText.setFillColor(sf::Color::Blue);

        // event loop
        Event e;
        while (welcome.pollEvent(e)) {
            // if window is closed, don't start the game (keep gameStart = false)
            if (e.type == Event::Closed) {
                welcome.close();
            }

            // Checking user selection
            if (e.type == Event::KeyPressed)
            {
                // Switch statement which checks if user selects '3', '4', or '5':
                // if user selects '3', set numGems to 3 and start game
                // if user selects '4', set numGems to 4 and start game
                // if user selects '5', set numGems to 5 and start game
                switch (e.key.code)
                {
                    case sf::Keyboard::Num3:
                        numGems = 3;
                        choiceTitle = "3-Gem-Match";
                        gameStart = true;
                        welcome.close();
                        break;
                    case sf::Keyboard::Num4:
                        numGems = 4;
                        choiceTitle = "4-Gem-Match";
                        gameStart = true;
                        welcome.close();
                        break;
                    case sf::Keyboard::Num5:
                        numGems = 5;
                        choiceTitle = "5-Gem-Match";
                        gameStart = true;
                        welcome.close();
                        break;
                }
            }
        }
        // draw instructions to screen
        welcome.draw(instructionText);
        welcome.draw(choiceText);
        welcome.display();
    }

    // loading in sound
    /*
     * Magic Wand by Timbre, https://freesound.org/people/Timbre/sounds/221683/,
     * License: Attribution Noncommercial 4.0 License
     */
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sounds/magicSound.flac"))
    {
        return EXIT_FAILURE;
    }

    // Loading sound buffer
    sf::Sound magicSound;
    magicSound.setBuffer(buffer);

    // Loading in game score/time font
    /*
     * Alex Brush by TypeSETit, https://www.1001freefonts.com/alex-brush.font,
     * License: Public Domain
     */
    sf::Font font;
    if (!font.loadFromFile("fonts/font.ttf"))
    {
        return EXIT_FAILURE;
    }

    // bool which is set to true if game ends (not when window is closed)
    bool endGame = false;
    
    // if the user made a valid selection in welcome window, start the game
    if (gameStart)
    {
        // rendering window
        RenderWindow app(VideoMode(740, 480), choiceTitle);
        app.setFramerateLimit(60);

        // Initialize grid
        initGrid(numGems);

        int x0, y0, x, y;
        int click = 0;
        Vector2i pos;
        bool isSwap = false, isMoving = false;

        // setting initial score to 0
        int score = 0;
        // setting initial time to 3000
        int time = INITIAL_TIME;

        // Loop runs while app is open
        while (app.isOpen()) {

            Event e;
            // If window is closed, close the game
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }

                // if user clicks, swap positions
                if (e.type == Event::MouseButtonPressed) {
                    if (e.key.code == Mouse::Left) {
                        if (!isSwap && !isMoving) { click++; }
                        pos = Mouse::getPosition(app) - offset;
                    }
                }

                // Restart game if 'R' is pressed
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::R) {
                        score = 0;
                        time = INITIAL_TIME;
                        initGrid(numGems);
                    }
                }
            }

            // Detecting mouse click
            if (click == 1) {
                x0 = pos.x / ts + 1;
                y0 = pos.y / ts + 1;
            }
            if (click == 2) {
                x = pos.x / ts + 1;
                y = pos.y / ts + 1;
                if (abs(x - x0) + abs(y - y0) == 1) {
                    swap(grid[y0][x0], grid[y][x]);
                    isSwap = 1;
                    click = 0;
                } else { click = 1; }
            }

            // Match finding
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    if (grid[i][j].getKind() == grid[i + 1][j].getKind()) {
                        if (grid[i][j].getKind() == grid[i - 1][j].getKind()) {
                            for (int n = -1; n <= 1; n++) {
                                // incrementing match count if matches with piece to right
                                grid[i + n][j].setMatch(grid[i+n][j].getMatch()+1);
                            }
                        }
                    }

                    if (grid[i][j].getKind() == grid[i][j + 1].getKind()) {
                        if (grid[i][j].getKind() == grid[i][j - 1].getKind()) {
                            for (int n = -1; n <= 1; n++) {
                                // incrementing match count if matches with piece above
                                grid[i][j + n].setMatch(grid[i][j+n].getMatch()+1);
                            }
                        }
                    }
                }
            }

            // Moving animation
            isMoving = false;
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    Piece &p = grid[i][j];
                    int dx, dy;
                    for (int n = 0; n < 4; n++)   // 4 - speed
                    {
                        dx = p.getX() - p.getCol() * ts;
                        dy = p.getY() - p.getRow() * ts;
                        // updating location of pieces
                        if (dx) { p.setX(p.getX() - dx / abs(dx)); }
                        if (dy) { p.setY(p.getY() - dy / abs(dy)); }
                    }
                    if (dx || dy) {
                        isMoving = 1;
                    }
                }
            }

            // Deleting animation
            if (!isMoving) {
                for (int i = 1; i <= 8; i++) {
                    for (int j = 1; j <= 8; j++) {
                        if (grid[i][j].getMatch()) {
                            if (grid[i][j].getAlpha() > 10) {
                                // when pieces are done moving, remove the matching ones
                                grid[i][j].setAlpha(grid[i][j].getAlpha()-10);
                                isMoving = true;
                            }
                        }
                    }
                }
            }

            // Update score
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    score += grid[i][j].getMatch();
                }
            }

            // Swapping pieces when there is no match
            if (isSwap && !isMoving) {
                if (!score) { swap(grid[y0][x0], grid[y][x]); }
                isSwap = 0;
            }

            // Updating the grid
            if (!isMoving) {
                for (int i = 8; i > 0; i--) {
                    for (int j = 1; j <= 8; j++) {
                        if (grid[i][j].getMatch()) {
                            for (int n = i; n > 0; n--) {
                                if (!grid[n][j].getMatch()) {
                                    // swapping pieces if they do not match (won't remove)
                                    swap(grid[n][j], grid[i][j]);
                                    break;
                                }
                            }
                        }
                    }
                };

                // Updating each Piece on grid
                for (int j = 1; j <= 8; j++) {
                    for (int i = 8, n = 0; i > 0; i--) {
                        if (grid[i][j].getMatch()) {
                            // like before, randomize number of gems based on user input
                            grid[i][j].setKind(rand()%numGems);
                            grid[i][j].setY(-ts * n++);
                            grid[i][j].setMatch(0);
                            grid[i][j].setAlpha(255);
                            magicSound.play();
                        }
                    }
                }
            }


            // Drawing screen
            app.draw(background);

            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    Piece p = grid[i][j];
                    gems.setTextureRect(IntRect(p.getKind() * 49, 0, 49, 49));
                    gems.setColor(Color(255, 255, 255, p.getAlpha()));
                    gems.setPosition(p.getX(), p.getY());
                    gems.move(offset.x - ts, offset.y - ts);
                    app.draw(gems);
                }
            }

            // displaying score + time
            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setCharacterSize(36);
            scoreText.setFillColor(sf::Color::Blue);
            // If time is less than 500, color it red to show user is low on time
            if (time < 500){scoreText.setFillColor(sf::Color::Red);}
            scoreText.setString("Time: \n"+std::to_string(time)+"\n"+"Score: \n"+std::to_string(score));
            scoreText.setPosition(500.f, 275.f);

            app.draw(scoreText);
            app.display();

            // if time has run out, end game
            if (time <= 1){
                endGame = true;
                app.close();
                break;
            }
            
            // else, decrement timer
            time-=1;
        }

        //===========================================================================
        /*
         * MY FEATURE PART 3: End Game Window displaying final score
         */
        //===========================================================================
        // if game ends because player ran out of time
        if (endGame)
        {
            RenderWindow endGame(VideoMode(740, 480), "Game Over");

            // rendering end game window
            while(endGame.isOpen()) {
                Event e;
                while (endGame.pollEvent(e)) {
                    // if window is closed, end game
                    if (e.type == Event::Closed) {
                        endGame.close();
                    }
                }

                // Setting the text for end game message
                sf::Text endMessage;
                endMessage.setPosition(0, 0);
                endMessage.setCharacterSize(50);
                endMessage.setFont(welcomeFont);
                endMessage.setString("Game over.\n"
                                     "Your final score was: "+std::to_string(score));

                endMessage.setFillColor(sf::Color::Green);

                // display end game words to string
                // draw instructions to screen
                endGame.draw(endMessage);
                endGame.display();
            }
        }
    }

    return 0;
}
