#include <math.h>
#include "structs/vec.hpp"


//template<
//    typename T,
//    const size_t N,
//    typename R
//>

template VECTORTEMPLATE
Vec<T, N, R>::Vec(T val[N]) {
    for(size_t i=0; i<N; i++) this->dat[i] = val[i];
}

template VECTORTEMPLATE
Vec<T, N, R>::Vec() {}

template VECTORTEMPLATE
Vec<T, N, R>::~Vec() {}


template VECTORTEMPLATE
void Vec<T, N, R>::set_coord(size_t index, T val) {
    this->dat[index] = val; 
}


template VECTORTEMPLATE
T Vec<T, N, R>::get_coord(size_t index) { 
    return this->dat[index];  
}

template VECTORTEMPLATE
Vec<T, N, R> Vec<T, N, R>::filled(T val) { 
    Vec<T, N, R> v;
    for (size_t i =0; i<N; i++) v.set_coord(i, val);
    return v;  
}


template VECTORTEMPLATE
T Vec<T, N, R>::length(){
    T r = 0;

    for(size_t i=0; i<N; i++){
        r += this->dat[i]*this->dat[i];
    }

    return sqrt(r);
}

template VECTORTEMPLATE
T Vec<T, N, R>::sqlength(){
    T r = 0;
    for(size_t i=0; i<N; i++){
        r += this->dat[i]*this->dat[i];
    }
    return r;
}

template VECTORTEMPLATE
void Vec<T, N, R>::normalize(){
    (*this) /= this->length();
}

template VECTORTEMPLATE
Vec<T, N, R> Vec<T, N, R>::operator+(Vec<T, N, R> other) { //TODO
    Vec<T, N, R> v = *this;
    for(size_t i=0; i<N;i++) v.dat[i] = this->dat[i] + other.get_coord(i);
    return v;
}

template VECTORTEMPLATE
Vec<T, N, R> Vec<T, N, R>::operator-(Vec<T, N, R> other) { //TODO
    Vec<T, N, R> v = *this;
    for(size_t i=0; i<N;i++) v.dat[i] = this->dat[i] - other.get_coord(i);
    return v;
}

template VECTORTEMPLATE
Vec<T, N, R> Vec<T, N, R>::operator*(T other) { //TODO
    Vec<T, N, R> v = *this;
    for(size_t i=0; i<N;i++) v.dat[i] = this->dat[i] * other;
    return v;
}

template VECTORTEMPLATE
Vec<T, N, R> Vec<T, N, R>::operator/(T other) { //TODO
    Vec<T, N, R> v = *this;
    for(size_t i=0; i<N;i++) v.dat[i] = this->dat[i] / other;
    return v;
}

template VECTORTEMPLATE
void Vec<T, N, R>::operator+=(Vec<T, N, R> other) { //TODO
    for(size_t i=0; i<N;i++) this->dat[i] += other.get_coord(i);
}

template VECTORTEMPLATE
void Vec<T, N, R>::operator-=(Vec<T, N, R> other) { //TODO
    for(size_t i=0; i<N;i++) this->dat[i] -= other.get_coord(i);
}

template VECTORTEMPLATE
void Vec<T, N, R>::operator*=(T other) { //TODO
    for(size_t i=0; i<N;i++) this->dat[i] *= other;
}

template VECTORTEMPLATE
void Vec<T, N, R>::operator/=(T other) { //TODO
    for(size_t i=0; i<N;i++) this->dat[i] /= other;
}


template VECTORTEMPLATE
std::ostream& operator<<(std::ostream& os, Vec<T, N, R> & v){
    os << "(";
    for (size_t i=0; i<N; i++ ) os <<v.get_coord(i)<<( i<N-1 ? "; ":"");
    os << ")";
    return os;
}