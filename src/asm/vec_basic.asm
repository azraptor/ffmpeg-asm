%include "x86inc.asm"

SECTION .text

; static void __add_values_sse2(uint8_t *src, const uint8_t *src2)
INIT_XMM sse2
cglobal add_values, 2, 2, 2, src, src2
    movu m0, [srcq]
    movu m1, [src2q]

    paddb m0, m1

    movu [srcq], m0

    RET

; static void __add_values_w_sse2(int16_t *src, const int16_t *src2);
INIT_XMM sse2
cglobal add_values_w, 2, 2, 2, src, src2
    movu m0, [srcq]
    movu m1, [src2q]

    paddw m0, m1

    movu [srcq], m0

    RET

; static void __add_values_dw_sse2(int32_t *src, const int32_t *src2);
INIT_XMM sse2
cglobal add_values_dw, 2, 2, 2, src, src2
    movu m0, [srcq]
    movu m1, [src2q]

    paddd m0, m1

    movu [srcq], m0

    RET

; static void __add_values_qw_sse2(int64_t *src, const int64_t *src2);
INIT_XMM sse2
cglobal add_values_qw, 2, 2, 2, src, src2
    movu m0, [srcq]
    movu m1, [src2q]

    paddq m0, m1

    movu [srcq], m0

    RET
