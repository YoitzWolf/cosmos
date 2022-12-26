#include <iostream>
#include "include/structs/memo.hpp"

//int main(){
//    return 0;
//}



template <class ... Types>
void PathMemory<Types...>::push(Types... res){
    this->data.push_back(std::make_tuple(res...));
}


//template <class ... Types>
//PathMemory<Types...>::PathMemory(){}
//template <class ... Types>
//PathMemory<Types...>::~PathMemory(){}


template <class ... Types>
size_t  PathMemory<Types...>::size(){
    return this->data.size();
}

template <class ... Types>
std::tuple<Types...> PathMemory<Types...>::get_record(size_t i){
    if (i >= this->data.size()){ std::cout<<"INVALLID INDEX: "<<i<<" "<<this->data.size()<<std::endl;}
    return this -> data[i];
}


template<typename ...Ts, size_t ...Is>
  std::ostream & ost_tuple_impl(std::ostream& os, std::tuple<Ts...> tuple, std::index_sequence<Is...>)
  {
      //static_assert(sizeof...(Is)==sizeof...(Ts),"Indices must have same number of elements as tuple types!");
      //static_assert(sizeof...(Ts)>0, "Cannot insert empty tuple into stream.");
      auto last = sizeof...(Ts); // assuming index sequence 0,...,N-1
      return ((os << std::get<Is>(tuple) << (Is != last-1 ? ", " : "")),...);
  }

template<typename ...Ts>
std::ostream & operator<<(std::ostream& os, const std::tuple<Ts...> & tuple) {
    return ost_tuple_impl(os<<"", tuple, std::index_sequence_for<Ts...>{});
}



//template class PathMemory<unsigned long long, double, Vec<double, 3ull, double>, Vec<double, 3ull, double>, Vec<double, 3ull, double> >;