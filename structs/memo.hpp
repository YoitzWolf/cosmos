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

#endif