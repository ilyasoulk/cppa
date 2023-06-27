#include "include/prime_lib.hh"


prime_number_range::iterator::iterator(const prime_number_range& range, std::size_t curr)
    : range(range), curr(curr)
    {}

int prime_number_range::iterator::operator*() const{
    return range.prime_numbers[curr];
}

prime_number_range::iterator prime_number_range::iterator::operator++(){
    curr++; // PSC safety / segfault risk
    return *this;
}

bool prime_number_range::iterator::operator!=(const prime_number_range::iterator other) const{
    return curr != other.curr;
}

bool prime_number_range::iterator::operator==(const prime_number_range::iterator other) const  {
    return !(*this != other); // PSC ...
}

prime_number_range::iterator prime_number_range::begin(){
    return iterator(*this);
}

prime_number_range::iterator prime_number_range::end(){
    return iterator(*this, prime_numbers.size());
}


prime_number_range::prime_number_range(std::size_t count)
    : count_(count)
    {
        std::size_t X = 0, i = 2;
        bool flag;
        while(X < count){
            flag = true;
            for(std::size_t j = 2; j <= std::sqrt(i); j++){ // PSC prefer ++j, compute sqrt outside of loop
                if (i%j == 0){
                    flag = false;
                    break;
                }
            }
            if(flag){
                prime_numbers.push_back(i);
                X++;
            }
            i++;
        }
    }