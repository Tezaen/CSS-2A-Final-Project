#ifndef CAR_H
#define CAR_H
#include <SFML/Graphics.hpp>

const int num=7; //checkpoints
int points[num][2] = {300, 400,
                      2570,1500,
                      2580,2380,
                      2600,3060,
                      1570,2500,
                      1500,2300,
                      500, 2500};
class Car
{
    public:
        Car() {speed=2; angle=0; n=0;};
        void carmove()
           {
            x += sin(angle) * speed;
            y -= cos(angle) * speed;
           }
        void findTarget()
          {
            float i=points[n][0];
            float j=points[n][1];
            float beta = angle-atan2(i-x,-j+y); //turning to the next checkpoint for enemy cars
            if (sin(beta)<0)
                angle+=0.005*speed;
            else
                angle-=0.005*speed;
            if ((x-i)*(x-i)+(y-j)*(y-j)<25*25)
                n=(n+1)%num;
           }

        float x,y,speed,angle; int n;

};

#endif // CAR_H
