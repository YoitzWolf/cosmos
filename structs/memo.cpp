#include "memo.hpp"

//int main(){
//    return 0;
//}

template <class ... Types>
void PathMemory<Types...>::push(Types... res){
    this->data.push_back(std::make_tuple(res...));
}


template <class ... Types>
PathMemory<Types...>::PathMemory(){}

template <class ... Types>
PathMemory<Types...>::~PathMemory(){}


template <class ... Types>
size_t  PathMemory<Types...>::size(){
    return this->data.size();
}

template <class ... Types>
std::tuple<Types...> PathMemory<Types...>::get_record(size_t i){
    return this -> data[i];
}