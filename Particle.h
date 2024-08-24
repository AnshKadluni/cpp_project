#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
    private:
        double point_pos[2] = {0, 0};
        double point_vel[2] = {0, 0};
    
    public:
        const double gravity = -10;
        const double drag_force_c = 0.0001; // k <= 1/v_0

        void update(double dt) {
            point_vel[1] -= gravity*dt;
            point_vel[0] -= drag_force_c*point_vel[0]*point_vel[0];

            point_pos[1] += point_vel[1]*dt;
            point_pos[0] += point_vel[0]*dt;
        }

        void change_momentum() {
            point_vel[1] = -0.7*point_vel[1];
        }

        double* get_pos() {return point_pos;}

        double* get_vel() {return point_vel;}

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

#endif 