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

    template<>
    inline typename simd_trait<double,memory::avx>::register_type _mm_load1<double,memory::avx>(typename simd_trait<double,memory::avx>::register_type xmm0, typename simd_trait<double,memory::avx>::value_type a){
        return (xmm0 = _mm256_broadcast_sd(&a)); 
    }
   
    template<>
    inline typename simd_trait<double,memory::avx>::register_type _mm_load<double,memory::avx>(typename simd_trait<double,memory::avx>::register_type xmm0, typename simd_trait<double,memory::avx>::const_pointer a){
        return (xmm0 = _mm256_load_pd(a)); 
    }

    template<>
    void _mm_store<double,memory::avx>(typename simd_trait<double,memory::avx>::register_type xmm0, typename simd_trait<double,memory::avx>::pointer a){
        _mm256_store_pd(a,xmm0); 
    }
   
    template<>
    inline typename simd_trait<double,memory::avx>::register_type _mm_mul<double,memory::avx>(typename simd_trait<double,memory::avx>::register_type xmm0, typename simd_trait<double,memory::avx>::register_type xmm1){
        return (xmm0 = _mm256_mul_pd(xmm0, xmm1));
    };
   
    template<>
    inline typename simd_trait<double,memory::avx>::register_type _mm_div<double,memory::avx>(typename simd_trait<double,memory::avx>::register_type xmm0, typename simd_trait<double,memory::avx>::register_type xmm1){
        return (xmm0 = _mm256_div_pd(xmm0, xmm1));
    };
   
    template<>
    inline typename simd_trait<double,memory::avx>::register_type _mm_add<double,memory::avx>(typename simd_trait<double,memory::avx>::register_type xmm0, typename simd_trait<double,memory::avx>::register_type xmm1){
        return (xmm0 = _mm256_add_pd(xmm0, xmm1));
    };
   
    template<>
    inline typename simd_trait<double,memory::avx>::register_type _mm_fma<double,memory::avx>(typename simd_trait<double,memory::avx>::register_type xmm0, typename simd_trait<double,memory::avx>::register_type xmm1, typename simd_trait<double,memory::avx>::register_type xmm2){
        return (xmm0 = _mm256_fmadd_pd(xmm0, xmm1, xmm2));
    };
   
    template<>
    typename simd_trait<float,memory::avx>::register_type _mm_load1<float,memory::avx>(typename simd_trait<float,memory::avx>::register_type xmm0, typename simd_trait<float,memory::avx>::value_type a){
        return (xmm0 = _mm256_broadcast_ss(&a)); 
    }
   
    template<>
    typename simd_trait<float,memory::avx>::register_type _mm_load<float,memory::avx>(typename simd_trait<float,memory::avx>::register_type xmm0, typename simd_trait<float,memory::avx>::const_pointer a){
        return (xmm0 = _mm256_load_ps(a)); 
    }

    template<>
    void _mm_store<float,memory::avx>(typename simd_trait<float,memory::avx>::register_type xmm0, typename simd_trait<float,memory::avx>::pointer a){
        _mm256_store_ps(a,xmm0); 
    }
   
    template<>
    inline typename simd_trait<float,memory::avx>::register_type _mm_mul<float,memory::avx>(typename simd_trait<float,memory::avx>::register_type xmm0, typename simd_trait<float,memory::avx>::register_type xmm1){
        return (xmm0 = _mm256_mul_ps(xmm0, xmm1));
    }
   
    template<>
    inline typename simd_trait<float,memory::avx>::register_type _mm_div<float,memory::avx>(typename simd_trait<float,memory::avx>::register_type xmm0, typename simd_trait<float,memory::avx>::register_type xmm1){
        return (xmm0 = _mm256_div_ps(xmm0, xmm1));
    };
   
    template<>
    inline typename simd_trait<float,memory::avx>::register_type _mm_add<float,memory::avx>(typename simd_trait<float,memory::avx>::register_type xmm0, typename simd_trait<float,memory::avx>::register_type xmm1){
        return (xmm0 = _mm256_add_ps(xmm0, xmm1));
    };

    template<>
    inline typename simd_trait<float,memory::avx>::register_type _mm_fma<float,memory::avx>(typename simd_trait<float,memory::avx>::register_type xmm0, typename simd_trait<float,memory::avx>::register_type xmm1, typename simd_trait<float,memory::avx>::register_type xmm2){
        return (xmm0 = _mm256_fmadd_ps(xmm0, xmm1, xmm2));
    };
} //end namespace 

#endif 
