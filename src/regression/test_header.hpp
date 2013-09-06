/*
 * CoreBluron, License
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

#ifndef COREBLURON_TEST_HEADER_HPP
#define COREBLURON_TEST_HEADER_HPP

#define BOOST_TEST_MODULE math
#define BOOST_TEST_MAIN  

#include <iostream>
#include <stdexcept>
#include "numeric/math/math.hpp"
#include "numeric/math/exp.hpp"
#include <boost/mpl/list.hpp>
#include <boost/cstdint.hpp> 
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/test/floating_point_comparison.hpp>


namespace corebluron {
    namespace test {

    static boost::random::uniform_real_distribution<float>    RandomDouble = boost::random::uniform_real_distribution<float>(-5,5); 
    static boost::random::uniform_real_distribution<double>   Randomfloat  = boost::random::uniform_real_distribution<double>(-5,5); 
    static boost::random::mt19937    rng;

    template<class T>
    T GetRandom();

    template<>
    float GetRandom<float>(){
        return Randomfloat(rng);
    }
   
    template<>
    double GetRandom<double>(){
        return RandomDouble(rng);
    }

    template<class T, std::size_t m>
    struct data{
        typedef T value_type;
        static const std::size_t n = m;
        static const std::size_t size = 16/sizeof(T); // for SIMD SSE
    };

    typedef boost::mpl::list<boost::int32_t,boost::int64_t,float,double> full_test_types;
    typedef boost::mpl::list<
                                data<float,14>,
                                data<double,14>
                            > floating_point_test_types;

    } // end namespace test
} // end namespace corebluron  

#endif // COREBLURON_TEST_HEADER_HPP
