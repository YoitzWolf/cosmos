#include <iostream>
#include "./structs/structs.hpp"
#include "./integrators/integrators.hpp"


# define COSMOS_VERSION "0.1a"


Vec<double, 3> f(Vec<double, 3> y, Vec<double, 3> dy, double t){
    auto v = Vec<double, 3>::filled(0);
    
    if (y.get_coord(1) > 0)         v.set_coord(1, -9);
    else if (y.get_coord(1) < 0)    v.set_coord(1, 9);
    return v;
}


int main(){
    std::cout<<"COSMOS:: v"<<COSMOS_VERSION<<std::endl;

    auto memo = new PathMemory<size_t, double, Vec<double, 3>, Vec<double, 3>, Vec<double, 3>>();
    auto r = Vec<double, 3>::filled(0);
    r.set_coord(1, 100);
    auto v = Vec<double, 3>::filled(0);

    euler_solver<double, 3, double>(
        &f,
        v,
        r,
        1,
        100000,
        true,
        memo
    );

    //v.set_coord(0, 0);
    //v.set_coord(1, 1);
    //v.set_coord(2, 2);
    std::cout<<v.get_coord((size_t)0)<<" "<<v.get_coord((size_t)1)<<" "<<v.get_coord((size_t)2);
    std::cout<<memo -> size()<<std::endl;
    std::cout<<"OUTPUT::"<<std::endl;
    
    for(int i=0; i<100; i++)
        std::cout<<memo -> get_record(i)<<std::endl;
    return 0;
}