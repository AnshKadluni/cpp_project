#ifndef PARTICLE2_H
#define PARTICLE2_H

class Particle2 {
    private:
        double* pos;
        double* vel; 
        double mass;
    public:
        const double drag = 0.0001;
        // size of window
        const double HEIGHT = 400;
        const double WIDTH = 400;

        // constructors
        Particle2();
        Particle2(double pos[2], double vel[2], double mass);

        // methods
        double* get_pos() {return pos;}
        double* get_vel() {return vel;}
        
        void update(double dt, double* other_pos, double* other_vel);

        void change_vel(double* new_vel);

        // deconstructor
        ~Particle2();
};

#endif