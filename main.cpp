#include <iostream>
#include <fstream>

#include "structs/structs.hpp"
#include "integrators/integrators.hpp"


# define COSMOS_VERSION "0.1a"

// G = 6.6743 × 10^-11 
// M = 5.9722 × 10^24
// GM = 39.86025446 * 10^13 = *10^5

Vec<double, 3> f(Vec<double, 3> y, Vec<double, 3> dy, double t){
    auto v = y;
    v.normalize();
    auto p = y.sqlength();
    v *= - (6.6743 * 1.9882 * (1e25) ) / (p); //1e14 * -3.986004418 / (p);
    //if (y.get_coord(1) > 0)         v.set_coord(1, -9);
    //else if (y.get_coord(1) < 0)    v.set_coord(1, 9);
    return v;
}
//*/

int main(){
    std::cout<<"COSMOS:: v"<<COSMOS_VERSION<<std::endl;

    auto memo = new PathMemory<size_t, double, Vec<double, 3>, Vec<double, 3>, Vec<double, 3>>();
    
    auto r = Vec<double, 3>::filled(0);
    r.set_coord(1, 6378100+408000   );//432650 35 800 //6371000+408000 //6378100+408000
                // 35800000
    auto v = Vec<double, 3>::filled(0);
    v.set_coord(0, 791000);// 7910 7777.7778 7910
    size_t N = 500000;
    euler_solver<double, 3, double>(
        &f,
        v,
        r,
        0.01,
        N,
        true,
        memo
    );

    //v.set_coord(0, 0);
    //v.set_coord(1, 1);
    //v.set_coord(2, 2);
    std::cout<<r<<std::endl;
    std::cout<<v<<std::endl;

    std::cout<<memo -> size()<<std::endl;
    std::cout<<"OUTPUT::"<<std::endl;
    
    std::ofstream output;
    output.open("./output/sim.txt");

    //output<<"R_0: "<<r<<std::endl;
    //output<<"V_0: "<<v<<std::endl;

    //for(int i=0; i<N; i++)
    //    output<<memo -> get_record(i)<<std::endl;
    //output.close();*/
    return 0;
}