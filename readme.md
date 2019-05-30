### Ideal Use Cases
  * Code that has frequent use of asm (as inline or .asm module) in conjunction with intrinsic code.
  * Projects that emit statically-generated or JIT functions.
  * ... and for anyone who just prefers assembly language's abbreviated mnemonics.

### Benefits vs. Intel Instrinsics `(__mm_*)`
  * Fixes numerous issues with Intel's intrinsics definitions
  * Provides some additional cross-platform framework
  * Uses iSSE/AVX nstruction names with "i_" prefix (i.e. `i_addps(dest, regA, regB)`)
    - removes need to look up both SSE/AVX instruction reference and cross-reference that with 
	  the Intel Intrinsic reference
  * Removes need to micro-manage integer/float/double domain types
    - operation type is determined by the mnemonic
    - just use `__m128` for everything!

### Benefits vs. Inline Assembly
  * Compatible with MSVC/GCC/CLANG/ICC
  * Non-destructive 3-operand syntax (dest = src1 op src2)
  * Register-allocation handled by the compiler
  * Compiler optimizations -- constant folding, peephole, etc.

Example Usage:

```
include <iostream>
include "sse_intrinsics.h"

using namespace std;

__declspec(align(16)) float arr1[4] = { 123.4f, 567.8f, 910.1f, 121.3f };
__declspec(align(16)) float arr2[4] = { 151.6f, 718.1f, 192.0f, 212.2f };

int main()
{
    __m128 a, b;

	i_divps (a, arr2, arr1);
	i_pslld (b, a, 3);
	i_mulps (a, a, b);
	i_addss (a, a, b);
	i_psrld (arr1, a, 7);
	i_pslld (arr2, b, 2);
	
	cout << arr1[0] << ", " << arr1[1] << ", " << arr1[2] << ", " << arr1[3] << endl;
	cout << arr2[0] << ", " << arr2[1] << ", " << arr2[2] << ", " << arr2[3] << endl;
}
```
