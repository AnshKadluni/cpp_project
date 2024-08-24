#include "Particle2.h"
#include <cmath>

Particle2::Particle2() {
    this->pos = new double[2];
    this->pos[0] = WIDTH/2;
    this->pos[0] = HEIGHT/2;
    this->vel = new double[2]{0};
    mass = 1;
}

Particle2::Particle2(double pos_new[2], double vel_new[2], double mass_new) {
    this->pos = new double[2];
    this->pos[0] = pos_new[0] + WIDTH/2;
    this->pos[1] = pos_new[1] + HEIGHT/2;
 
    this->vel = new double[2];
    this->vel[0] = vel_new[0];
    this->vel[1] = vel_new[1];

    this->mass = mass_new;
}

void Particle2::update(double dt, double* other_pos, double* other_vel) {
    if (pos[0] >= WIDTH || pos[0] <= 0) {
        vel[0] = -vel[0];
    }
    
    if (pos[1] >= HEIGHT || pos[1] <= 0) {
        vel[1] = -vel[1];
    }
    

    this->pos[0] += this->vel[0]*dt;
    this->pos[1] += this->vel[1]*dt; 
}

void Particle2::change_vel(double* new_vel) {
    vel[0] = new_vel[0];
    vel[1] = new_vel[1];
}

Particle2::~Particle2() {
    delete[] pos;
    delete[] vel;
}