
#include "integrators/euler.hpp"


template VECTORTEMPLATE
void euler_solver(
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
    tVec coord = y_0;
    tVec velocity = dy_0;
    tVec acceleration = f(coord, velocity, time);

    if(memorize) pathmem -> push ( 0, time, coord, velocity, acceleration );

    for (std::size_t i=1; i<max_iterations; i++) {
        acceleration = f(coord, velocity, time);

        coord = coord + velocity * dt;
        velocity = velocity + acceleration * dt;
        time = time + dt;

        if(memorize) pathmem -> push ( i, time, coord, velocity, acceleration );
    }

};
//*/