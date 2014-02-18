/*
 * CYME, License
 * 
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne 
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef CYME_TEST_HEADER_HPP
#define CYME_TEST_HEADER_HPP

#define BOOST_TEST_MODULE math
//#define BOOST_TEST_MAIN
//#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "cyme/cyme.hpp"
#include <boost/mpl/list.hpp>
#include <boost/cstdint.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/test/floating_point_comparison.hpp>

#define RELATIVE_ERROR 0.001

namespace cyme {
    namespace test {

    static boost::random::uniform_real_distribution<float>    Randomfloat  = boost::random::uniform_real_distribution<float>(-70,70);
    static boost::random::uniform_real_distribution<double>   Randomdouble = boost::random::uniform_real_distribution<double>(-700,700);
    static boost::random::mt19937    rng;

    template<class T>
    T GetRandom();

    template<>
    float GetRandom<float>(){
        return Randomfloat(rng);
    }

    template<>
    double GetRandom<double>(){
        return Randomdouble(rng);
    }

    template<class Ba, class Bb> // m and n are differents into the block that why I passe like argument
    void init(Ba& block_a, Bb& block_b){
        for(std::size_t i=0; i<block_a.size(); ++i)
            for(std::size_t j=0; j<block_a.size_block(); ++j){
                typename Ba::value_type random = GetRandom<typename Ba::value_type>();
                block_a(i,j) = random;
                block_b(i,j) = random;
            }
    }

    template<class Ba, class Bb>
    void check(Ba const& block_a, Bb const& block_b){
        for(std::size_t i=0; i<block_a.size(); ++i)
            for(std::size_t j=0; j<block_a.size_block(); ++j)
                BOOST_CHECK_CLOSE(block_a(i,j), block_b(i,j), RELATIVE_ERROR);
    }

    template<class T, std::size_t m, memory::order o>
    struct data{
        typedef T value_type;
        static const std::size_t n = m;
        static const std::size_t size = 16/sizeof(T); // for SIMD SSE
        static const memory::order order = o;
    };

    template<class T, std::size_t M, std::size_t N, memory::order O>
    struct data_block{
        typedef T value_type;
        static const std::size_t m = M;
        static const std::size_t n = N;
        static const memory::order order = O;
    };

    typedef boost::mpl::list<boost::int32_t,boost::int64_t,float,double> full_test_types;

    typedef boost::mpl::list<
                                data<float,14,memory::AoS>,
                                data<float,14,memory::AoSoA>,
                                data<double,14,memory::AoS>,
                                data<double,14,memory::AoSoA>
                            > floating_point_test_types;
    //max 20 elements, because MPL must emulate variadic template
    typedef boost::mpl::list<
                                data_block<float,2,2,memory::AoSoA>,
                                data_block<double,3,2,memory::AoS>,
                                data_block<float,4,2,memory::AoSoA>,
                                data_block<double,5,2,memory::AoSoA>,

                                data_block<float,2,3,memory::AoSoA>,
                                data_block<double,3,3,memory::AoS>,
                                data_block<float,4,3,memory::AoSoA>,
                                data_block<double,5,3,memory::AoSoA>,

                                data_block<float,2,4,memory::AoSoA>,
                                data_block<double,3,4,memory::AoS>,
                                data_block<float,4,4,memory::AoSoA>,
                                data_block<double,5,4,memory::AoSoA>,

                                data_block<float,2,5,memory::AoSoA>,
                                data_block<double,3,5,memory::AoS>,
                                data_block<float,4,5,memory::AoSoA>,
                                data_block<double,5,5,memory::AoSoA>,

                                data_block<float,2,6,memory::AoSoA>,
                                data_block<double,3,6,memory::AoS>,
                                data_block<float,4,6,memory::AoSoA>,
                                data_block<double,5,6,memory::AoSoA>

                            > floating_point_torture_list;

    typedef boost::mpl::list<
                                data_block<float,6,15,memory::AoS>,
                                data_block<float,7,13,memory::AoSoA>,
                                data_block<float,8,11,memory::AoS>,
                                data_block<double,9,9,memory::AoS>,
                                data_block<double,10,7,memory::AoSoA>,
                                data_block<double,11,5,memory::AoSoA>
                            > floating_point_block_types;




    } // end namespace test
} // end namespace CYME

#endif // CYME_TEST_HEADER_HPP
