//#include "errs.hpp"

//#include <boost/outcome.hpp>
#include <stdlib.h>
#include <type_traits>
//#include <system_error>
//namespace outcome = BOOST_OUTCOME_V2_NAMESPACE;


#pragma once

#ifndef VEC
    #define VEC

#ifndef VECTORTEMPLATE
    #define VECTORTEMPARGS typename T, const size_t N, typename R
    #define VECTORTEMPLATE <VECTORTEMPARGS>
#endif

template<
    typename T,
    const size_t N,
    typename R = typename std::enable_if<std::is_arithmetic<T>::value, T>::type// true
>
class Vec {
    private:
        T dat[N];

    public:
        Vec(T dat[N]);
        Vec();
        ~Vec();

        static Vec<T, N, R> filled(T val);

        T get_coord(size_t index);
        T& at(const size_t index);

        void set_coord(size_t index, T val);

        Vec<T, N, R> operator+(Vec<T, N, R> other);
        Vec<T, N, R> operator-(Vec<T, N, R> other);

        Vec<T, N, R> operator*(T other);
        Vec<T, N, R> operator/(T other);

        void operator+=(Vec<T, N, R> other);
        void operator-=(Vec<T, N, R> other);
        void operator*=(T other);
        void operator/=(T other);        

};

template VECTORTEMPLATE
std::ostream& operator<<(std::ostream& os, const Vec<T, N, R> & v);

#endif