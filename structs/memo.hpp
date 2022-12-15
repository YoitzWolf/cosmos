#include <vector>
#include <tuple>
#include "vec.hpp"


#ifndef MEMOHPP
    #define MEMOHPP

template <class ... Types>
class PathMemory{
    private:
        std::vector< std::tuple<Types...> > data;
    public:
        PathMemory();
        ~PathMemory();
        void push(Types... res);
        
        std::tuple<Types...> get_record(size_t i);
        size_t size();

        //void dump(std::ostream &os);

};

/*template <class ... Types>
std::ostream& operator<<(std::ostream &os, const PathMemory<Types...> &memo) {
    return os << memo.data;
}
*/

template<typename ...Ts, size_t ...Is>
  std::ostream & ost_tuple_impl(std::ostream& os, std::tuple<Ts...> tuple, std::index_sequence<Is...>)
  {
      //static_assert(sizeof...(Is)==sizeof...(Ts),"Indices must have same number of elements as tuple types!");
      //static_assert(sizeof...(Ts)>0, "Cannot insert empty tuple into stream.");
      auto last = sizeof...(Ts); // assuming index sequence 0,...,N-1
      return ((os << std::get<Is>(tuple) << (Is != last-1 ? "; " : "]")),...);
  }

template<typename ...Ts>
std::ostream & operator<<(std::ostream& os, const std::tuple<Ts...> & tuple) {
    return ost_tuple_impl(os<<"[", tuple, std::index_sequence_for<Ts...>{});
}


#endif