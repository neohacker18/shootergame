#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <math.h>
#include <iostream>
#include <vector>
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 3
int globalScore=0;

class Bullet
{
public:
    Sprite shape;
    Texture *texture;
    Bullet(Texture *texture, Vector2f pos)
    {
        this->texture = texture;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.5, 0.5);
        this->shape.setPosition(pos);
    }
    ~Bullet() {}
};
class Player
{
public:
    Sprite shape;
    Texture *texture;
    int HP;
    int HPMax;
    std::vector<Bullet> bullets;
    Player(Texture *texture)
    {
        this->HPMax = 10;
        this->HP = this->HPMax;

        this->texture = texture;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.2, 0.2);
    }
    ~Player() {}
};
class Enemy
{
public:
    int HP;
    int HPMax;
    Sprite shape;
    Texture *texture;
    Enemy(Texture *texture, Vector2u windowSize)
    {
        this->HPMax = rand() % 3 + 1;
        this->HP = HPMax;
        this->texture = texture;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.1, 0.1);
        this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
    }
    ~Enemy() {}
};

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

Menu::Menu(float width, float height)
{

    if (!font.loadFromFile("textures/Times New Roman 400.ttf"))
    {
        // handle error
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setCharacterSize(36);
    menu[0].setPosition(1000 / 2.0f, 500 / 2.0f);
    menu[0].setStyle(sf::Text::Bold | sf::Text::Underlined);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setCharacterSize(36);

    menu[1].setStyle(sf::Text::Bold | sf::Text::Underlined);
    // menu[1].setPosition(sf::Vector2f(width / 1.8, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    menu[1].setPosition(1000 / 2.0f, 800 / 2.0f);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    // menu[2].setPosition(sf::Vector2f(width / 1.8, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
    menu[2].setCharacterSize(36);

    menu[2].setPosition(1000 / 2.0f, 1100 / 2.0f);
    menu[2].setStyle(sf::Text::Bold | sf::Text::Underlined);

    selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

class Death
{
public:
    Death(float width, float height);
    ~Death();
    int Pscore = 0;
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text death[MAX_NUMBER_OF_ITEMS];
};

Death::Death(float width, float height)
{

    if (!font.loadFromFile("textures/Times New Roman 400.ttf"))
    {
        // handle error
    }

    death[0].setFont(font);
    death[0].setFillColor(sf::Color::Red);
    death[0].setString("Play Again");
    death[0].setCharacterSize(36);
    death[0].setPosition(900 / 2.0f, 700 / 2.0f);
    death[0].setStyle(sf::Text::Bold | sf::Text::Underlined);

    death[1].setFont(font);
    death[1].setFillColor(sf::Color::White);
    death[1].setString("Exit");
    death[1].setCharacterSize(36);

    death[1].setPosition(1000 / 2.0f, 900 / 2.0f);
    death[1].setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    death[2].setFont(font);
    death[2].setFillColor(sf::Color::White);
    death[2].setString("Your Score: "+std::to_string(globalScore));
    death[2].setCharacterSize(50);
    death[2].setPosition(800 / 2.0f, 300 / 2.0f);
    death[2].setStyle(sf::Text::Bold);

    selectedItemIndex = 0;
}

Death::~Death()
{
}

void Death::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(death[i]);
    }
}

void Death::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        death[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        death[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Death::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        death[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        death[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int startGame()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Shooter gamee!");
    window.setFramerateLimit(60);

    // loading font
    Font font;
    font.loadFromFile("textures/Times New Roman 400.ttf");

    // making sprites

    // player sprite
    Texture playerTex;
    playerTex.loadFromFile("textures/rocket.png");

    // enemy sprite
    Texture enemyTex;
    enemyTex.loadFromFile("textures/asteroid.jpg");

    // bullets sprite
    Texture bulletTex;
    bulletTex.loadFromFile("textures/bullet.jpg");

    // player initialization
    Player player(&playerTex);
    int shootTimer = 20;
    int Pscore = 0;
    float j = 0;

    // dsiplay health
    Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(20);
    hpText.setFillColor(sf::Color::White);

    // Game over initialization
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setFillColor(Color::White);
    gameOver.setPosition(500, 400);
    gameOver.setString("GAME OVER");

    // score initialization
    Text score;
    score.setFont(font);
    score.setFillColor(Color::White);
    score.setCharacterSize(25);
    score.setPosition(10.f, 10.f);

    // enemy initialization
    int enemyTimer = 0;
    std::vector<Enemy> enemies;

    //-------------------------------------------game starts-------------------------------------------------------//

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // movement of sprite
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            player.shape.move(0.f, -10.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            player.shape.move(-10.f, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player.shape.move(0.f, 10.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            player.shape.move(10.f, 0.f);
        }

        // display of health of player
        hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
        hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));

        // window collision of sprite
        if (player.shape.getPosition().x <= 0) // left
        {
            player.shape.setPosition(0.f, player.shape.getPosition().y);
        }
        if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) // right
        {
            player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
        }
        if (player.shape.getPosition().y <= 0) // top
        {
            player.shape.setPosition(player.shape.getPosition().x, 0.f);
        }
        if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) // bottom
        {
            player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
        }

        // creating bullets on left click of mouse button

        // to delay creation of bullets
        if (shootTimer < 20)
            shootTimer++;

        if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 20)
        {
            player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
            shootTimer = 0;
        }

        // more with bullets
        for (int i = 0; i < player.bullets.size(); i++)
        {
            // move
            player.bullets[i].shape.move(20.f, 0.f);
            // out of window
            if (player.bullets[i].shape.getPosition().x > window.getSize().x)
            {
                player.bullets.erase(player.bullets.begin() + i);
            }
            // enemy collision
            for (int k = 0; k < enemies.size(); k++)
            {
                if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
                {
                    Pscore = Pscore + 10;
                    enemies.erase(enemies.begin() + k);
                    player.bullets.erase(player.bullets.begin() + i);
                    break;
                }
            }
        }

        // score display
        score.setString("Score : " + std::to_string(Pscore));

        // enemies spawning
        if (enemyTimer < 60)
        {
            enemyTimer++;
        }
        if (enemyTimer >= 60)
        {
            enemies.push_back(Enemy(&enemyTex, window.getSize()));
            enemyTimer = 0;
        }

        // movement of asteroids
        for (int i = 0; i < enemies.size(); i++)
        {
            if (Pscore % 100 == 0 && Pscore != 0)
            {
                j = j + 0.1;
            } // speed increase

            enemies[i].shape.move(-3.5 - j, 0);
            if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
            {
                enemies.erase(enemies.begin() + i);
                player.HP = player.HP - 1;
            }
            if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            {
                enemies.erase(enemies.begin() + i);
                player.HP = player.HP - 2;
            }
        }

        window.clear();

        // drawing player
        window.draw(player.shape);
        // drawing enemy
        for (int i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i].shape);
        }
        // drawing bullets
        for (int i = 0; i < player.bullets.size(); i++)
        {
            window.draw(player.bullets[i].shape);
        }
        // draw
        window.draw(hpText);
        window.draw(score);
        // game over
        window.display();
        if (player.HP <= 0)
        {
            window.clear();
            window.display();
            window.close();
        }
    }
    globalScore=Pscore;
    return Pscore;
}

void deathScreen(int Pscore)
{
    sf::RenderWindow splash(sf::VideoMode(1000, 800), "You Died!");
    Sprite sprite;
    Death death(splash.getSize().x, splash.getSize().y);
    Texture texture;
    texture.loadFromFile("textures/deathscreen.jpg");
    Vector2u size = texture.getSize();
    sprite.setTexture(texture);
    sprite.setPosition(-430, 0);
    while (splash.isOpen())
    {
        sf::Event event;

        while (splash.pollEvent(event))
        {

            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    death.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    death.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (death.GetPressedItem())
                    {
                    case 0:
                        std::cout << "Play button has been pressed" << std::endl<<"Your score was "<<Pscore<<std::endl;
                        splash.close();
                        splash.clear();
                        splash.draw(sprite);
                        death.draw(splash);
                        splash.display();
                        startGame();
                        break;
                    case 1:
                        std::cout << "Exit button has been pressed" << std::endl;
                        splash.close();
                        return;
                        break;
                    }

                    break;
                }

                break;
            case sf::Event::Closed:
                splash.close();

                break;
            }
        }

        splash.clear();
        splash.draw(sprite);
        death.draw(splash);
        splash.display();
    }
}

int main()
{

    sf::RenderWindow splash(sf::VideoMode(1000, 800), "Main Menu!");
    Sprite sprite;
    int score = 0;
    Menu menu(splash.getSize().x, splash.getSize().y);
    Texture texture;
    texture.loadFromFile("textures/stars.jpg");
    Vector2u size = texture.getSize();
    sprite.setTexture(texture);
    sprite.setPosition(-70, 40);
    while (splash.isOpen())
    {
        sf::Event event;

        while (splash.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        std::cout << "Play button has been pressed" << std::endl;
                        splash.close();
                        score = startGame();
                        deathScreen(score);
                        break;
                    case 1:
                        std::cout << "Option button has been pressed" << std::endl;

                        break;
                    case 2:
                        splash.close();
                        std::cout << "Exit button has been pressed" << std::endl;
                        return 0;
                        break;
                    }

                    break;
                }

                break;
            case sf::Event::Closed:
                splash.close();

                break;
            }
        }

        splash.clear();
        splash.draw(sprite);
        menu.draw(splash);
        splash.display();
    }
    return 0;
}