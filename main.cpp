#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "include/structs/structs.hpp"
#include "include/integrators/integrators.hpp"


# define COSMOS_VERSION "0.1a"

// G = 6.6743 × 10^-11 
// M = 5.9722 × 10^24
// GM = 39.86025446 * 10^13 = *10^5

Vec<double, 3> f(Vec<double, 3> y, Vec<double, 3> dy, double t){
    auto v = y;
    v.normalize();
    auto p = y.sqlength();
    v *= - (39.86025446 * 1e13) / (p); //1e14 * -3.986004418 / (p); 6.6743 * 1.9882 * (1e25)
    //if (y.get_coord(1) > 0)         v.set_coord(1, -9);
    //else if (y.get_coord(1) < 0)    v.set_coord(1, 9);
    return v;
}
//*/

int main(){
    std::cout<<"COSMOS:: v"<<COSMOS_VERSION<<std::endl;

    auto memo = new PathMemory<size_t, double, Vec<double, 3>, Vec<double, 3>, Vec<double, 3>>();
    
    auto r = Vec<double, 3>::filled(0);
    r.set_coord(1, 6378100+408000);// 6378100+408000
                // 35800000
    auto v = Vec<double, 3>::filled(0);
    v.set_coord(0, 7664.078);// 7664.078
    size_t N = 750000;

    std::cout<<r<<std::endl;
    std::cout<<v<<std::endl;

    predictor_corrector_solver<double, 3, double>(
        &f,
        v,
        r,
        -0.01,
        N,
        true,
        memo
    );
    
    std::cout<<"OUTPUT::"<<std::endl;
    std::cout<<memo -> size()<<std::endl;
    std::ofstream output;
    output.open("./output/minus-predcorr.txt");
    output << std::fixed << std::setprecision(16);
    for(size_t i=0; i<N; i++)
        output<<memo -> get_record(i)<<std::endl;
    output.close();//*/

    std::cout<<"Ready"<<std::endl;
    return 0;
}