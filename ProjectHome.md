This is a single header file which wraps x86-32/x64 SSE intrinsics into functions which have a naming convention identical to SSE/AVX asm except with a "i`_`" prefix.  Via use of this wrapper, a single mnemonic can be used for all asm and intrinsic code in a project. It was developed by programmers who were tired of trying to memorize/use/re-read the bulky intrinsic API normally provided by Intel/AMD, and then having to cross-reference it with the more familiar SSE/AVX asm mnemonics.

Ideal Usage Scenarios:
  * Code that has frequent use of asm (as inline or .asm module) in conjunction with intrinsic code.
  * Projects that emit statically-generated or JIT functions.
  * ... and for anyone who just prefers assembly language's abbreviated mnemonics.

Benefits:
  * Compatible with MSVC/GCC/ICC
  * Uses instructions real names with "i`_`" prefix (i.e. i\_addps(dest, regA, regB))
  * Non-destructive 3-operand syntax (dest = src1 op src2)
  * Can freely mix between integer/float/double instructions (same as via assembler)
  * Reg-allocation handled by the compiler - good for code being built for both x32 and x64 platforms.
  * Compiler can perform further optimizations on the intrinsics -- constant folding, peephole, etc.
  * More portable than inline asm.

Disclaimer:
  * If you're already familiar with the Intel/AMD intrinsics, and have never touched assembly code in your life, then this probably won't be helpful to you.


Example Usage:
```
#include <iostream>
#include "sse_intrinsics.h"
using namespace std;

__declspec(align(16)) float arr1[4] = { 123.4f, 567.8f, 910.1f, 121.3f };
__declspec(align(16)) float arr2[4] = { 151.6f, 718.1f, 192.0f, 212.2f };

int main() {
    __m128   a, b;
    i_divps (a, *(__m128*)arr2, *(__m128*)arr1);
    i_pslld (b, a, 3);
    i_mulps (a, a, b);
    i_addss (a, a, b);
    i_psrld (*(__m128*)arr1, a, 7);
    i_pslld (*(__m128*)arr2, b, 2);
    cout << arr1[0] << ", " << arr1[1] << ", " << arr1[2] << ", " << arr1[3] << endl;
    cout << arr2[0] << ", " << arr2[1] << ", " << arr2[2] << ", " << arr2[3] << endl;
}
```

Note: The above example doesn't do anything particularly useful, but shows how to use the intrinsic wrapper with some common sse instructions.