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

template <class ... Types>
PathMemory<Types...>::PathMemory(){}

template <class ... Types>
PathMemory<Types...>::~PathMemory(){}


template<typename ...Ts, size_t ...Is>
std::ostream & ost_tuple_impl(std::ostream& os, std::tuple<Ts...> tuple, std::index_sequence<Is...>);

template<typename ...Ts>
std::ostream & operator<<(std::ostream& os, const std::tuple<Ts...> & tuple);

#endif