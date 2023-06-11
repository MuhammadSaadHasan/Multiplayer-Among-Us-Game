#include <sstream>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
using namespace sf;


//use this to compile the code
//g++ -o a2 a2.cpp -lsfml-graphics -lsfml-window -lsfml-system -pthread -lX11


class player
{
    public:
        int x;
        int y;
        int dir;
        int score;
        int n;
        player(int X, int Y)
        {
            x = X;
            y = Y;
            dir = 0;
            score = 0;
        }
};
player player1(50,50), player2(100,50);


void Tick1(){
    if (player1.dir == 0 && (player1.y < (player1.n*50)))
        player1.y += 50;
    if (player1.dir == 1 && (player1.x > 50))
        player1.x -= 50;
    if (player1.dir == 2 && (player1.x < (player1.n*50)))
        player1.x += 50;
    if (player1.dir == 3 && (player1.y > 50))
        player1.y -= 50;}
void Tick2(){
    if (player2.dir == 0 && (player2.y < (player2.n*50)))
        player2.y += 50;
    if (player2.dir == 1 && (player2.x > 50))
        player2.x -= 50;
    if (player2.dir == 2 && (player2.x < (player2.n*50)))
        player2.x += 50;
    if (player2.dir == 3 && (player2.y > 50))
        player2.y -= 50;}
void *player1movement(void *arg){


    Clock clock;
    float timer = 0, delay = 0.08;

    while (true)
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        bool check = false;
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            player1.dir = 2;
            check = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            player1.dir = 1;
            check = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            player1.dir = 3;
            check = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player1.dir = 0;
            check = true;
        }

        if (timer > delay && check == true)
        {
            timer = 0;
            Tick1();
        }
    }

    return NULL;
}
void *player2movement(void *arg){

    Clock clock;
    float timer = 0, delay = 0.08;

    while (true)
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        bool check = false;
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            player2.dir = 1;
            check = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            check = true;
            player2.dir = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            player2.dir = 3;
            check = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player2.dir = 0;
            check = true;
        }

        if (timer > delay && check == true)
        {
            timer = 0;
            Tick2();
        }

    }

    return NULL;}

int GetRandomNumber()
{
    srand(time(0));
    int n = rand()%(99-10) + 10;
    n *= 6;
    n = 566/n;
    n = n%25;
    if(n < 10)
    {n += 10;}
    return n;
}


int main()
{
    XInitThreads();   
    int n = GetRandomNumber();
    printf("Value of n = %d\n", n);
    char **arr = new char*[n];
    for(int i = 0; i < n; i++) {
        arr[i] = new char[n];
        for(int j = 0; j < n; j++)
        {
                arr[i][j] = 'w';
        }
    }
    int cherry_count = 0;

    while(cherry_count < n*3)
    {
        int rand_i = rand()%n, rand_j = rand()%n;
        arr[rand_i][rand_j] = 'c';
        cherry_count++;    
    }
    if(arr[0][1] == 'c')
    {
        arr[0][1] = 'w';
        cherry_count--;
    }
    if(arr[0][2] == 'c')
    {
        arr[0][2] = 'w';
        cherry_count--;
    }

    

    
    RenderWindow window(VideoMode((n*50)+100, (n*50)+100), "Assignment 2!");
    window.setFramerateLimit(60);
    Texture t1,t2,b,r,m,w1,w2,tie;
    t1.loadFromFile("images/player1.png");
    t2.loadFromFile("images/player2.png");
    b.loadFromFile("images/white.png");
    r.loadFromFile("images/cherry.png");
    m.loadFromFile("images/menu.png");
    w1.loadFromFile("images/p1winner.png");
    w2.loadFromFile("images/p2winner.png");
    tie.loadFromFile("images/itsatie.png");


    Sprite sprite1(t1), sprite2(t2), background(b), cherry(r), menu(m), winner1(w1), winner2(w2), tieDraw(tie);

    Clock clock;
    float timer = 0, delay = 1;

    sf::Font font;

    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Text p1,p2,scoreP1,scoreP2, WinnerMessage, itsAtieMessage;

    WinnerMessage.setFont(font);
    WinnerMessage.setCharacterSize(80);
    WinnerMessage.setFillColor(sf::Color::White);
    WinnerMessage.setString("WINNER");

    itsAtieMessage.setFont(font);
    itsAtieMessage.setCharacterSize(15);
    itsAtieMessage.setFillColor(sf::Color::White);
    itsAtieMessage.setString("Its a tie lol");

    p1.setFont(font);
    p1.setCharacterSize(25);
    p1.setFillColor(sf::Color::Red);
    p1.setString("Player 1:");

    p2.setFont(font);
    p2.setCharacterSize(25);
    p2.setFillColor(sf::Color::Blue);
    p2.setString("Player 2:");

    scoreP1.setFont(font);
    scoreP1.setCharacterSize(25);
    scoreP1.setFillColor(sf::Color::White);

    scoreP2.setFont(font);
    scoreP2.setCharacterSize(25);
    scoreP2.setFillColor(sf::Color::White);

    srand(time(0));
    

    player1.n = player2.n = n;
    
    pthread_t play1,play2;
    pthread_create(&play1, NULL, player1movement, NULL);
    pthread_create(&play2, NULL, player2movement, NULL);


    bool menucheck = true, winner = false;
        int count = 0;

    
    
    while (window.isOpen())
    {
        count = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n;j++)
                if(arr[i][j] == 'w')
                    count++;

        if(count == n*n)
        {
            sleep(3);
            while(true)
            {
                window.clear();
                Event e;
                while (window.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        window.close();
                    else if (Keyboard::isKeyPressed(Keyboard::Escape))
                        window.close();
                    else if (Keyboard::isKeyPressed(Keyboard::P))
                        menucheck = false;
                }
                if(player1.score > player2.score)
                {
                    winner1.setPosition((window.getSize().x - winner1.getLocalBounds().width) / 2, (window.getSize().y - winner1.getLocalBounds().height) / 2);
                    window.draw(winner1);
                    WinnerMessage.setPosition(200,0);
                    window.draw(WinnerMessage);
                }
                else if(player2.score > player1.score)
                {
                    winner2.setPosition((window.getSize().x - winner2.getLocalBounds().width) / 2, (window.getSize().y - winner2.getLocalBounds().height) / 2);
                    window.draw(winner2);
                    WinnerMessage.setPosition(200,0);
                    window.draw(WinnerMessage);
                }
                else 
                {
                    tieDraw.setPosition((window.getSize().x - tieDraw.getLocalBounds().width) / 2, (window.getSize().y - tieDraw.getLocalBounds().height) / 2);
                    window.draw(tieDraw);
                    itsAtieMessage.setPosition(180,350);
                    window.draw(itsAtieMessage);
                }
                window.display();
            }
        }

        while(menucheck == true)
        {

            window.clear();
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                else if (Keyboard::isKeyPressed(Keyboard::Escape))
                    window.close();
                else if (Keyboard::isKeyPressed(Keyboard::P))
                    menucheck = false;
            }
            menu.setPosition((window.getSize().x - menu.getLocalBounds().width) / 2, (window.getSize().y - menu.getLocalBounds().height) / 2);
            window.draw(menu);
            window.display();

        }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            else if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        if (timer > delay)
            timer = 0;


        window.clear();
        for(int i = 0; i<n;i++)
        {
            for(int j = 0; j<n;j++)
            {
                if(arr[i][j] == 'w')
                {
                    background.setPosition((j*50)+50, (i*50)+50);  window.draw(background);
                }
                else if(arr[i][j]  == 'c')
                {
                    cherry.setPosition((j*50)+50, (i*50)+50);  window.draw(cherry);
                    if((abs(i-round(((player1.y-50)/50))) <= 0.75 && abs(j-round(((player1.x-50)/50))) <= 0.75 ))  
                    {
                        arr[i][j] = 'w';
                        player1.score++;
                    } 
                    if(abs(i-round(((player2.y-50)/50))) <= 0.75 && abs(j-round(((player2.x-50)/50))) <= 0.75 )
                    {
                        arr[i][j] = 'w';
                        player2.score++;              
                    }
                    
                }
            
            }
        }

        sprite1.setPosition(player1.x, player1.y);
        window.draw(sprite1);
        sprite2.setPosition(player2.x, player2.y);
        window.draw(sprite2);


        p1.setPosition(0,0);
        window.draw(p1);

        scoreP1.setPosition(120, 0);
        scoreP1.setString(std::to_string(player1.score));
        window.draw(scoreP1);


        p2.setPosition(200,0);
        window.draw(p2);

        scoreP2.setPosition(310, 0);
        scoreP2.setString(std::to_string(player2.score));
        window.draw(scoreP2);

        window.display();
        
    }
    
    pthread_join(play1, NULL);                     
    pthread_join(play2, NULL);

    return 0;
}
