#include "include/structs/structs.hpp"

#ifndef EULERHPP
    #define EULERHPP

/**
 * @brief
 * Uses PathMemory as Pattern (iteration, x (wich used as dx), y(x), y'(x), y''(x))
 * 
*/
template VECTORTEMPLATE
void euler_solver(
    Vec<T, N, R> (*f)(Vec<T, N, R>, Vec<T, N, R>, T),
    Vec<T, N, R> dy_0,
    Vec<T, N, R> y_0,
    T dt,
    size_t max_iterations=100000,
    bool memorize=false,
    PathMemory<std::size_t, T, Vec<T, N, R>, Vec<T, N, R>, Vec<T, N, R>> *pathmem=NULL//std::nullptr_t
);

#include "src/integrators/euler.tpp"
#endif