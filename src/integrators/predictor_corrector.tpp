
#include "include/integrators/predictor_corrector.hpp"


template VECTORTEMPLATE
void predictor_corrector_solver(
    Vec<T, N, R> (*f)(Vec<T, N, R>, Vec<T, N, R>, T),
    Vec<T, N, R> dy_0,
    Vec<T, N, R> y_0,
    T dt,
    size_t max_iterations/*=100000*/,
    bool memorize/*=false*/,
    PathMemory<std::size_t, T, Vec<T, N, R>, Vec<T, N, R>, Vec<T, N, R>> *pathmem/*=NULL*///std::nullptr_t
) {
    typedef Vec<T, N, R> tVec;

    T time = 0;

    tVec pred_velocity = dy_0;
    tVec pred_coord    = y_0;

    tVec coord = y_0; //corrected
    tVec velocity = dy_0; //corrected

    tVec last_velocity = dy_0; //corrected

    tVec acceleration = f(coord, velocity, time);

    if(memorize) pathmem -> push ( 0, time, coord, velocity, acceleration);

    for (std::size_t i=1; i<max_iterations; i++) {
        acceleration = f(coord, velocity, time);
        
        pred_velocity = velocity + acceleration * dt;
        pred_coord    = coord + pred_velocity * dt;

        last_velocity = velocity;
        velocity = velocity + (acceleration + f(pred_coord, pred_velocity, time+dt)) / 2 * dt;

        coord = coord + (velocity + last_velocity) / 2 * dt;

        
        time = time + dt;

        if(memorize) pathmem -> push ( i, time, coord, velocity, acceleration);
    }

};
//*/