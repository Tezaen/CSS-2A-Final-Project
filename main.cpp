/****
Roober Cruz, Ras Hipolito, Eleazar Rico
CSS-2A
Top-Down Racing Game
May 15, 2019
Top Down Racing Games:
Our project is a top-down racing game that features you, the player, and five other cars that move fixed on a track.
The cars have hitboxes and can collide with each other. Once a car passes the finish line, the program ends.
****/

#include <SFML/Graphics.hpp>
#include "Car.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include "GameSong.h"
#include <string>
using namespace sf;
using namespace std;

int main()
{
    RenderWindow app(VideoMode(640, 480), "Car Racing Game!");
	app.setFramerateLimit(60);

    Texture t1,t2,t3, t4;
    t1.loadFromFile("images/mushroomcup2.png");
    t2.loadFromFile("images/ChuyRacer.png");
    t3.loadFromFile("images/redLine.png");
    t4.loadFromFile("images/speedometer.png");
    t1.setSmooth(true);
    t2.setSmooth(true);
    t3.setSmooth(true);
    t4.setSmooth(true);

    Sprite sBackground(t1), sCar(t2), sLine(t3), sHud(t4);
    sBackground.scale(2,2);


    sCar.setOrigin(22, 22);//sprite position
    float R=22;

    //this section allows music to play
    Music mus;
    GameSong s;
    string backgroundMusic = s.getSongs();
    mus.openFromFile(backgroundMusic);
    mus.setLoop(true);
    mus.play();


    const int N=6;
    Car car[N];
    for(int i=0;i<N;i++)//declaration of the starting position of the opponents and speed.
    {
      car[i].x=300+i*50;
      car[i].y=1700+i*80;
      car[i + 1].speed=9+i;
    }

    float speed=0,angle=0;
    float maxSpeed=14.0;
    float acc=0.4, dec=0.3;
    float turnSpeed=0.08;

    int offsetX=0,offsetY=0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        bool Up=0,Right=0,Down=0,Left=0;
        if (Keyboard::isKeyPressed(Keyboard::Up)) Up=1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) Right=1;
        if (Keyboard::isKeyPressed(Keyboard::Down)) Down=1;
        if (Keyboard::isKeyPressed(Keyboard::Left)) Left=1;

        //player car movement
        if (Up && speed<maxSpeed){
            if (speed < 0) {speed += dec;}
            else  {speed += acc;}
        }
        if (Down && speed>-maxSpeed){
            if (speed > 0) {speed -= dec;}
            else  {speed -= acc;}
        }
        if (!Up && !Down){
            if (speed - dec > 0) {speed -= dec;}
            else if (speed + dec < 0) {speed += dec;}
            else {speed = 0;}
        }
        if (Right && speed!=0)  {angle += turnSpeed * speed/maxSpeed;}
        if (Left && speed!=0)   {angle -= turnSpeed * speed/maxSpeed;}

        car[0].speed = speed;
        car[0].angle = angle;

        for(int i=0;i<N;i++)
            car[i].carmove();//Car turning

        for(int i=1;i<N;i++)
            car[i].findTarget();//Car finding the checkpoints

        //collision
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                int a=0, b=0;
                while (a*a+b*b<4*R*R)
                 {
                   car[i].x+=a/10.0;//forces the car to leave the other car sprite
                   car[i].x+=b/10.0;//
                   car[j].x-=a/10.0;//
                   car[j].y-=b/10.0;//
                   a = car[i].x-car[j].x;
                   b = car[i].y-car[j].y;
                   if (!a && !b) {
                    break;
                   }
                 }
            }
        }

        app.clear(Color::White);

        if (car[0].x>320) {offsetX = car[0].x-320;}//avoids showing the offscreen area
        if (car[0].y>240) {offsetY = car[0].y-240;}//avoids showing the offscreen area

        if (offsetX > 2230) {offsetX -= (offsetX - 2230);}//avoids showing the offscreen area
        if (offsetY > 3150) {offsetY -= (offsetY - 3150);}//avoids showing the offscreen area


        sBackground.setPosition(-offsetX,-offsetY); //sets background static
        app.draw(sBackground);//draws background
        sLine.setPosition(-offsetX - 500, -offsetY + 2500);//sets finish Line
        app.draw(sLine);

        Color colors[10] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White, Color::Black};
        sHud.setPosition(500, 350);
        app.draw(sHud);


        for(int i=0;i<N;i++)//Turning for cars
        {
            sCar.setPosition(car[i].x-offsetX,car[i].y-offsetY);
            sCar.setRotation(car[i].angle*180/3.141593);
            sCar.setColor(colors[i]);
            app.draw(sCar);
            if(sCar.getGlobalBounds().intersects(sLine.getGlobalBounds()))
            {
                cout << "Car number " << i + 1 << " passes the line!" << endl;
            }
        }


        app.display();
    }

    return 0;
}
