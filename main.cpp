#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Particle.h"

using namespace sf;
using namespace std;

int main(void) {
    const double HEIGHT = 400;
    const double WIDTH = 400;

    const double x0 = 20;
    const double y0 = 20;

    double pos[2] = {x0, y0};
    double vel[2] = {10, 0};
    Particle p(pos, vel);
    int done = 0;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "SKIBIDI GOONER");

    window.setPosition(Vector2i(1920/2 - WIDTH/2, 1080/2 - HEIGHT/2));

    CircleShape shape(10.f);

    shape.setFillColor(Color::Blue);
    shape.setOrigin(Vector2f(10, 10));

    shape.setPosition(Vector2f(x0, y0));

    long long duration;

    while (window.isOpen()) {

        p.update((double)duration/100000000); // delta time

        duration = 0; 

        auto begin = std::chrono::high_resolution_clock::now();

        Vector2f pose = shape.getPosition();
        pose.x = p.get_pos()[0];
        pose.y = p.get_pos()[1];
        double *curr = p.get_pos();

        //if (done >= 50) {
        //    break;
        //} else if (curr[1] >= HEIGHT/2) { 
        //    curr[1] = HEIGHT/2;
        //    p.change_pos(curr);
        //    p.change_momentum();
        //    done++;
        //} else {
        //    done = 0;
        //}

        if (curr[1] > HEIGHT/2) { 
            curr[1] = HEIGHT/2;
            p.change_pos(curr);
            p.change_momentum();
        }

        shape.setPosition(pose);

        Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();

        auto end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    }
    
    return 0;
}