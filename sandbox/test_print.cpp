/*
 * Cyme - test_print.cpp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

 #include <iostream>
 #include <vector>

 #include <cyme/cyme.h>

 #include <boost/chrono.hpp>

 #include <boost/function.hpp>
 #include <boost/bind.hpp>

 #include <boost/accumulators/accumulators.hpp>
 #include <boost/accumulators/statistics/stats.hpp>
 #include <boost/accumulators/statistics/mean.hpp>
 #include <boost/accumulators/statistics/variance.hpp>

 #include <boost/mpl/for_each.hpp>
 #include <boost/mpl/vector.hpp>
 #include <boost/mpl/push_back.hpp>
 #include <functional>

 #include <algorithm>

 template<class T>
 struct synapse{
     typedef T value_type;
     static const size_t value_size = 18;
 };

 typedef cyme::array<synapse<float>,1024, cyme::AoS> block_f_aos;
 typedef cyme::array<synapse<float>,1024, cyme::AoSoA> block_f_aosoa;
 typedef cyme::array<synapse<double>,1024, cyme::AoS> block_d_aos;
 typedef cyme::array<synapse<double>,1024, cyme::AoSoA> block_d_aosoa;


 typedef cyme::vector<synapse<float>, cyme::AoS> vector_f_aos;
 typedef cyme::vector<synapse<float>, cyme::AoSoA> vector_f_aosoa;
 typedef cyme::vector<synapse<double>, cyme::AoS> vector_d_aos;
 typedef cyme::vector<synapse<double>, cyme::AoSoA> vector_d_aosoa;

 using namespace boost::accumulators;


 typedef boost::mpl::vector< block_f_aos, block_f_aosoa, block_d_aos, block_d_aosoa > array_list;
 //typedef boost::mpl::vector< vector_f_aos, vector_f_aosoa, vector_d_aos, vector_d_aosoa > vector_list;
 typedef boost::mpl::vector<vector_d_aosoa> vector_list;


 template<class Ba>
 void init(Ba& block_a){
     for(size_t i=0; i<block_a.size(); ++i)
         for(size_t j=0; j<block_a.size_block(); ++j){
             typename Ba::value_type random = 10*drand48();
             block_a(i,j) = random;
         }
 }

 template<class Ba, class Bb>
 void init(Ba& block_a, Bb& block_b){
     for(size_t i=0; i<block_a.size(); ++i)
         for(size_t j=0; j<block_a.size_block(); ++j){
       //    typename Ba::value_type random = 10*std::pow(-1,rand())*drand48();
             typename Ba::value_type random = 876.76786; // 10*drand48();
             block_a(i,j) = random;
             block_b(i,j) = random;
         }
 }

 template<class Ba, class Bb>
 void check(Ba & block_a, Bb & block_b){
     std::cout.precision(2*sizeof(typename Ba::value_type));

     for(size_t i=0; i<block_a.size(); ++i)
         for(size_t j=0; j<block_a.size_block(); ++j)
             std::cout << block_a(i,j)  << " " << block_b(i,j) << " " << block_a(i,j) - block_b(i,j) << std::endl;
 }

 void print( boost::accumulators::accumulator_set<double, stats<tag::mean, tag::variance> >const& acc, std::string name){
     std::cout.precision(2);
     std::cout.setf(std::ios::scientific, std::ios::floatfield);
     std::cout << "bench: " << name <<" " << extract_result< tag::mean >(acc)
                            << " [s], variance " << extract_result< tag::variance >(acc)
                            << ", standard deviation " << sqrt(extract_result< tag::variance >(acc)) << std::endl;
 }


 struct Na{
     typedef double value_type;


     template<class T, cyme::order O>
     static inline void cnrn_functions(T& W){
         //cnrn_states(W);
       log_functions(W);
     }

     template<class T>
     static inline void log_functions(T& W){
       T const & R = W;
       W[1] = log(R[1]);
       W[2] = log(R[2]);
       W[3] = log2(R[3]);
       W[4] = log2(R[4]);
       W[5] = log10(R[5]);
       W[6] = log10(R[6]);
     };


     template<class T>
     static inline void cnrn_rates(T& W){
         T const & R = W;
         W[8]  = (0.182*(R[16]+35.0)) / (1.0 - (exp((-R[16]-35.0)/9.0)));
         W[9]  = (-0.124*(R[16]+35.0))/ (1.0 - (exp((R[16]+35.0)/9.0)));
         W[6]  = R[8]/(R[8]+R[9]);
         W[7]  = 1.0/(R[8]+R[9]);
         W[12] = (0.024*(R[16]+50.0))  /(1.0-(exp((-R[16]-50.0)/5.0)));
         W[13] = (-0.0091*(R[16]+75.0))/(1.0-(exp((R[16]+75.0)/5.0)));
         W[10] = 1.0/(1.0+exp(R[16]+65.0)/6.2);
         W[11] = 1.0/(R[12]+R[13]);
     };

     template<class T>
     static inline void cnrn_states(T& W){
         const double dt = 0.01;
        T const & R = W;
        cnrn_rates(W);
        W[3] += (1.-exp(dt*(-1.0/R[7] )))*(-(R[6] /R[7]) /(-1.0/R[7]) -R[3]);
        W[4] += (1.-exp(dt*(-1.0/R[11])))*(-(R[10]/R[11])/(-1.0/R[11])-R[4]);
     }
/*
     template<class iterator, cyme::order O>
     static inline  cyme::serial<value_type,O> cnrn_current(iterator it, value_type t = value_type()){
         (*it)[16] = t;
         (*it)[2] = (*it)[0] * (*it)[3] * (*it)[3] * (*it)[3] * (*it)[4];
         (*it)[1] = (*it)[2] * ((*it)[16] - (*it)[5]);
         return cyme::serial<value_type,O> ((*it)[1]);
     }

     template<class iterator>
     static inline void cnrn_initmodel(iterator it){
         (*it)[4] = 0. ; // TO DO, (*it)[4] ^= (*it)[4] XOR, or basic set up to 0 <--------------------------------- TIM
         (*it)[3] = 0. ;
         cnrn_rates(it);
         (*it)[3] = (*it)[6];
         (*it)[4] = (*it)[10];
     }

     template<class iterator, cyme::order O>
     static inline void cnrn_cur(iterator it){
         double _v=-33.33; // _v voltage fron a node random number
         cyme::serial<value_type,O> tmp  = cnrn_current<iterator, O>(it, _v + 0.001);
         cyme::serial<value_type,O> tmp2 = cnrn_current<iterator, O>(it, _v);
 //        tmp() -= tmp2();
         (*it)[17] = tmp;
         (*it)[17] = (*it)[17]/0.001;
     }

*/
     template<class iterator>
     static inline void cnrn_state(iterator it){
         cnrn_states(it);
     }
     const static size_t value_size = 18;
 };


 template<class mechanism, class container = cyme::vector<mechanism, cyme::AoSoA> > // should use cyme container there
 class pack{
 public:
     typedef typename mechanism::value_type value_type;

     explicit pack(size_t s, size_t value):cont(s,value){ // vector constructor
     }

     explicit pack():cont(){ // array constructor
     }

     void execution(){
         for(typename container::iterator it = cont.begin(); it < cont.end(); ++it)
             m.template cnrn_functions<typename container::storage_type, container::order_value>(*it);
     }

     value_type& operator()(size_t i, size_t j){
         return cont(i,j);
     }

     std::size_t size(){
         return cont.size();
     }

     std::size_t size_block(){
         return cont.size_block();
     }

 private:
     container cont;
     mechanism m;
 };

 class stack{
 public:
     typedef boost::function<void(void)> base_type; // pointer to function
     stack(){

     }

     void push_back(base_type const& f){
         s.push_back(f); // fill up the stack
     }

     void flush(){
         for(std::vector<base_type>::iterator it = s.begin(); it < s.end(); ++it)
             (*it)(); // execute cnrn_functions
     }
 private:
     std::vector<base_type> s;
 };


 int main(){
     stack s;

     pack<Na,cyme::vector<Na, cyme::AoSoA> > a(256,0); // pack 16384 synapse, AoSoA
     pack<Na,cyme::vector<Na, cyme::AoS> > b(256,0); // pack 16384 synapse, AoSoA

     init(a,b);

     s.push_back(boost::bind(&pack<Na,cyme::vector<Na, cyme::AoSoA> >::execution,&a)); // fill up the stack
     s.push_back(boost::bind(&pack<Na,cyme::vector<Na, cyme::AoS> >::execution,&b)); // fill up the stack

     boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
     s.flush(); // execute the stack
     boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
     std::cout << " sec " << sec.count() << std::endl;

     check(a,b);
 }

