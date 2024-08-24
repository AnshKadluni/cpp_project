#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Particle2.h"
#include <cmath>

using namespace sf;
using namespace std;


int main(void) {
    // size of window
    const double HEIGHT = 400;
    const double WIDTH = 400;
    // origin of screen at (WIDTH/2, HEIGHT/2)

    // initial postion
    const double x0 = -100;
    const double y0 = 0;

    const double x1_0 = 100;
    const double y1_0 = 0;

    //setting initial position and velocity
    double pos[2] = {x0, y0};
    double vel[2] = {10, 10};

    double pos2[2] = {x1_0, y1_0};
    double vel2[2] = {-10, 10};

    Particle2 particle(pos, vel, 1);
    Particle2 particle2(pos2, vel2, 1);
    
    // showing window
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Simulation");

    // setting postion of window
    window.setPosition(Vector2i(1920/2 - WIDTH/2, 1080/2 - HEIGHT/2));

    // creating circles
    CircleShape shape(10.f);
    CircleShape shape2(10.f);

    shape.setFillColor(Color::Blue);
    shape.setOrigin(Vector2f(10, 10));

    shape2.setFillColor(Color::Red);
    shape2.setOrigin(Vector2f(10, 10));

    // setting postion of circle to intial position
    shape.setPosition(Vector2f(x0, y0));
    shape2.setPosition(Vector2f(x1_0, y1_0));

    // dt for updating each iteration
    long long dt = 0;
    const int div_const = 100000000;

    while (window.isOpen()) {

        particle.update((double)dt/div_const, particle2.get_pos(), particle2.get_vel()); // updating everything
        particle2.update((double)dt/div_const, particle.get_pos(), particle.get_vel());

        // start timer for interation
        dt = 0; 
        auto begin = std::chrono::high_resolution_clock::now();

        // CODE
        double* curr_pos = particle.get_pos();
        double* curr_vel = particle.get_vel();

        double* curr_pos2 = particle2.get_pos();
        double* curr_vel2 = particle2.get_vel();

        if (sqrt(pow(curr_pos[0] - curr_pos2[0], 2) + pow(curr_pos[1] - curr_pos2[1], 2)) <= 10) {
            double c1 = ((curr_vel[0] - curr_vel2[0])*(curr_pos[0] - curr_pos2[0]) + (curr_vel[1] - curr_pos2[1])*(curr_pos[1] - curr_pos2[1]))/sqrt(pow(curr_pos[0] - curr_pos2[0], 2) + pow(curr_pos[1] - curr_pos2[1], 2));
            double c2 = ((- curr_vel[0] + curr_vel2[0])*( - curr_pos[0] + curr_pos2[0]) + ( - curr_vel[1] + curr_pos2[1])*( - curr_pos[1] + curr_pos2[1]))/sqrt(pow(curr_pos[0] - curr_pos2[0], 2) + pow(curr_pos[1] - curr_pos2[1], 2));
            
            curr_vel[0] = curr_vel[0] - c1*(curr_pos[0] - curr_pos2[0]);
            curr_vel[1] = curr_vel[1] - c1*(curr_pos[1] - curr_pos2[1]);
            
            curr_vel2[0] = curr_vel2[0] + c2*(curr_pos[0] - curr_pos2[0]);
            curr_vel2[1] = curr_vel2[1] + c2*(curr_pos[1] - curr_pos2[1]);
        }

        Vector2f pose = shape.getPosition();
        pose.x = curr_pos[0];
        pose.y = curr_pos[1];
        
        Vector2f pose2 = shape2.getPosition();
        pose2.x = curr_pos2[0];
        pose2.y = curr_pos2[1];

        particle.change_vel(curr_vel);
        particle2.change_vel(curr_vel2);


        shape.setPosition(pose);
        shape2.setPosition(pose2);

        

        // CODE

        // checking is window is closed
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // updating window
        window.clear();
        window.draw(shape);
        window.draw(shape2);
        window.display();

        // calculating time of interation
        auto end = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    }
}