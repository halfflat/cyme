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

#ifndef CYME_SIMD_H
#define CYME_SIMD_H

namespace memory{
    /** \cond I do not need this part in the doc*/
    enum simd {normal = sizeof(void*), sse = 16, avx = 32, qpx = 32, mic = 64}; //sizeof(void*) = 8 on 64 bits machine

// In C++0x the macro __cplusplus will be set to a value that differs from (is greater than) the current 199711L (ISO rules)
// Be carefull could change in the futur ...
#if (__cplusplus > 199711L)
    constexpr static simd __GETSIMD__() {return __CYME_SIMD_VALUE__;} //default value, given by pp e.g. -Dsse,
#else
    #define __GETSIMD__() __CYME_SIMD_VALUE__ // This is a shame but I can not use c++11
#endif

    enum order {AoS, AoSoA};
    
    template<class T, order O>
    struct stride;
    
    // just stride using meta-function
    template<class T>
    struct stride<T,AoS>{
        static inline std::size_t helper_stride(){return 1;}
    };

    template<class T>
    struct stride<T,AoSoA>{
        static inline std::size_t helper_stride(){return __GETSIMD__()/sizeof(T);}
    };
    /** \endcond I do not need this part in the doc*/
    
} //end namespace


#endif
