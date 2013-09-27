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

#ifndef COREBLURON_SIMD_WRAPPER_AVX_HPP
#define COREBLURON_SIMD_WRAPPER_AVX_HPP

namespace numeric{
    // QPX does not support float 
    template<class T>
    inline  simd_trait<T,memory::qpx>::register_type _mm_load1<T,memory::qpx>( simd_trait<T,memory::qpx>::register_type xmm0,  simd_trait<T,memory::qpx>::value_type a){
        return (xmm0 = vec_lds(0L,&a)); 
    }
   
    template<class T>
    inline  simd_trait<T,memory::qpx>::register_type _mm_load<T,memory::qpx>( simd_trait<T,memory::qpx>::register_type xmm0,  simd_trait<T,memory::qpx>::const_pointer a){
        return (xmm0 = vec_ld(0L,a)); 
    }

    template<class T>
    void _mm_store<T,memory::qpx>( simd_trait<T,memory::qpx>::register_type xmm0,  simd_trait<T,memory::qpx>::pointer a){
        vec_st(xmm0,0L,a);
    }
   
    template<class T>
    inline  simd_trait<T,memory::qpx>::register_type _mm_mul<T,memory::qpx>( simd_trait<T,memory::qpx>::register_type xmm0,  simd_trait<T,memory::qpx>::register_type xmm1){
        return (xmm0 = vec_mul(xmm0, xmm1));
    };
   
    template<class T>
    inline  simd_trait<T,memory::qpx>::register_type _mm_div<T,memory::qpx>( simd_trait<T,memory::qpx>::register_type xmm0,  simd_trait<T,memory::qpx>::register_type xmm1){
        return (xmm0 = vec_swdiv(xmm0, xmm1));
    };
   
    template<class T>
    inline  simd_trait<T,memory::qpx>::register_type _mm_add<T,memory::qpx>( simd_trait<T,memory::qpx>::register_type xmm0,  simd_trait<T,memory::qpx>::register_type xmm1){
        return (xmm0 = vec_add(xmm0, xmm1));
    };

} //end namespace 

#endif 
