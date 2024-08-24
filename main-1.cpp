#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Particle {
    private:
        double point_pos[2] = {0, 0};
        double point_vel[2] = {0, 0};
    
    public:
        const double gravity = -5;
        const double drag_force_c = -0.1; // k <= 1/v_0

        void update(double dt) {
            point_vel[1] -= gravity*dt;
            point_vel[0] += drag_force_c*point_vel[0]*point_vel[0];

            point_pos[1] += point_vel[1]*dt;
            point_pos[0] += point_vel[0]*dt;
        }

        void change_momentum() {
            point_vel[1] = -1*point_vel[1];
        }

        double* get_pos() {return point_pos;}

        void change_pos(double new_pos[2]) {
            point_pos[0] = new_pos[0];
            point_pos[1] = new_pos[1];
        }

        Particle(double pos[2], double vel[2]);
};

Particle::Particle(double pos[2], double vel[2]) {
        point_pos[0] = pos[0];
        point_pos[1] = pos[1];
        
        point_vel[0] = vel[0];
        point_vel[1] = vel[1];
}

int main(void) {
    const double HEIGHT = 400;
    const double WIDTH = 400;

    double pos[2] = {WIDTH/2, 20};
    double vel[2] = {0, 0};
    Particle p(pos, vel);
    int done = 0;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "SFML works!");

    window.setPosition(Vector2i(1920/2 - WIDTH/2, 1080/2 - HEIGHT/2));

    CircleShape shape(10.f);

    shape.setFillColor(Color::Blue);
    shape.setOrigin(Vector2f(10, 10));

    shape.setPosition(Vector2f(WIDTH/2, 20));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        p.update(0.05); // delta time 

        Vector2f pose = shape.getPosition();
        pose.x = p.get_pos()[0];
        pose.y = p.get_pos()[1];
        double *curr = p.get_pos();

        if (done >= 50) {
            break;
        } else if (curr[1] >= HEIGHT/2) { 
            curr[1] = HEIGHT/2;
            p.change_pos(curr);
            p.change_momentum();
            done++;
        } else {
            done = 0;
        }

        shape.setPosition(pose);

        window.clear();
        window.draw(shape);
        window.display();
    }
    
    return 0;
}