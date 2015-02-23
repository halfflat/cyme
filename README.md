# cyme
Framework to facilitate SIMD programming, without any tedious SIMD intrinsics.

Compilation:

 -D__CYME_SIMD_VALUE__=sse -msse4.1 + optional -D__FMA__
 -D__CYME_SIMD_VALUE__=avx -msvx+ optional -D__FMA__
 -D__CYME_SIMD_VALUE__=qpx -D__FMA__

Know issues:

- BG/Q it looks like a bug may appear with division (Newton-Raphson).

DEBUG mode:

1) the core engine test: core_operator_bracket_torture - the division
part fail (Newton-Raphson):

365     it_AoS = block_a.begin();
366     for(; it_AoS != block_a.end(); ++it_AoS)
367         (*it_AoS)[0]   = (((((*it_AoS)[1] /(*it_AoS)[2])/(*it_AoS)[3])/(*it_AoS)[4])/(*it_AoS)[5]);
368
369     it_AoSoA_w = block_b.begin();
370     it_AoSoA_r = block_b.begin();
371     for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
372         (*it_AoSoA_w)[0] = (((((*it_AoSoA_r)[1]/(*it_AoSoA_r)[2])/(*it_AoSoA_r)[3])/(*it_AoSoA_r)[4])/(*it_AoSoA_r)[5]);

It fails for an unroll of 2 and double only if the number of successive
division is larger than 3. I check the corresponding wrapper __mm__rec() and
_mm_nfma(), I do not find any issues. It works for float. Test works if I
perform the normal division

Sqrt fails also because it is built over Newton-Raphson

2) the validity test also fail for an unroll of 2

RELEASE:

The serial test unroll 4 fails, again for the division. It is very wierd
as the operator /= call the system division and not Newton-Raphson


Release 1.2.0

- Add new elementary function (sqrt)
- Fix bug in log
- Better DAG construction for operations with scalar operations
- Better catch of the FMA
- Simplification of the template expression when I mix float/double, implement unity concept
- Prepare for open source release
- Ameliorate CMake during the installation, configuration file is created with the needed define

Release 1.1.0

- Add new elementary function (pow/log)
- Ameliorate the tree creation by distinction Read/Write operators - const/ non const
- better DAG construction for --

Release 1.0.0

- First release oc cyme

