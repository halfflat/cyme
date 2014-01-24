#include <iostream>
#include <algorithm>
#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include "cyme/cyme.hpp"

//#include "iacaMarks.h"

template<class T>
struct synapse{
    typedef T value_type;
    static const int value_size = 18;
};

template<class T>
struct f_compute{
    void operator()(typename T::storage_type& S ){
// C++11 version 
// std::for_each(b.begin(), b.end(), [](my_vector::storage_type& S){S[3] += (1.-exp(0.1*(-1./S[7] )))*((S[6] /S[7]) /(1./S[7]) -S[3]; } );
        S[3] += (1.-exp(0.1*(-1./S[7] )))*((S[6] /S[7]) /(1./S[7]) -S[3]);
        S[4] += (1.-exp(0.1*(-1./S[11])))*((S[10]/S[11])/(1./S[11])-S[4]);
    }
};

template<class T>
struct f_init{
    void operator()(typename T::storage_type& S ){
        for(int i=0;i <T::size_block(); ++i)
            S[i] = drand48();
    }
};

typedef  cyme::vector<synapse<float>, memory::AoS> Vec_f_AoS;
typedef  cyme::vector<synapse<float>, memory::AoSoA> Vec_f_AoSoA;
typedef  cyme::vector<synapse<double>, memory::AoS> Vec_d_AoS;
typedef  cyme::vector<synapse<double>, memory::AoSoA> Vec_d_AoSoA; 

typedef boost::mpl::vector< Vec_f_AoS, Vec_f_AoSoA, Vec_d_AoS, Vec_f_AoSoA > vector_list;

struct test_case{

    template <class T>
    void operator()(T const&){

        T v(0xffffff,0);
        std::for_each(v.begin(), v.end(), f_init<T>() );
        
        boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
            std::for_each(v.begin(), v.end(), f_compute<T>() );
        boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
        
        std::cout << " sec " << sec.count() << std::endl;
    }
};


int main(int argc, char* argv[]){
     boost::mpl::for_each<vector_list>(test_case());
}
