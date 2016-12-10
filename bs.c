
#include <string.h>
#include "bs.h"
#include "../app.h"

#if (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) ||\
        defined(__amd64__) || defined(__amd32__)|| defined(__amd16__)
#define bs2le(x) (x)
#define bs2be(x) (x)
#elif (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) ||\
            (defined(__sparc__))
#define bs2le(x) __builtin_bswap_wordsize(x)
#define bs2be(x) __builtin_bswap_wordsize(x)
#else
#error "endianness not supported"
#endif

word_t rands[]= 
{0xf97aee9c, 0x710a96ee, 0xb0c1264a, 0x15306359, 0x6823bb0e, 0x94f7d62e, 0x1fa8de31, 0xc7c5d251, 0xce984ee9, 0x7f3f5c56, 0xf3078d01, 0x730c33a1, 0xc7fc760b, 0xd16b7e34, 0x1c457dfa, 0x2b9e1b1d, 
    0xd0a9ac71, 0xb1e2751a, 0xe1796abf, 0xdc25dd7e, 0x4b0bfd89, 0xe553d24f, 0x3b83ae47, 0x1ea87e2d, 0x7cd34659, 0x316cd3cd, 0x357b0592, 0xcba0217e, 0xbbb53b3e, 0x58ee9764, 0x617b2add, 0x94ce3d3e, 
    0xa5f15189, 0x23108512, 0x3d3ea3e1, 0x1d4f05b3, 0x387a80b8, 0x1fc3c75e, 0x8abf659e, 0x45a1e634, 0x17e1be47, 0xdd2dda5f, 0x30f645da, 0xb3e07619, 0x98627f2e, 0xfccb7c68, 0x94c4dbe8, 0xbcda38a7, 
    0xe6d6272b, 0x7de871ba, 0x5282847, 0xc287f2f2, 0x1858d421, 0xa3e20402, 0x350b1d4c, 0x20ca949f, 0x7c5f3ca0, 0x4da7675d, 0xe6ff4de1, 0x832dc32e, 0xbbc09ada, 0x6655f6d1, 0x6c431417, 0xef278ccd, 
    0xfb6a03d0, 0xfa34230a, 0x7e9758d2, 0xa4cc8686, 0x39a40824, 0x8837a35f, 0xead7ff47, 0x75a52c1d, 0x41235de5, 0x43c5ade3, 0x9da9ad42, 0x200b2b75, 0xfe0cd133, 0x11120807, 0x88e485e1, 0x63097d7, 
    0xf612fbe8, 0x58c13e0b, 0x73e56694, 0xb564660f, 0x763ac8e2, 0x7c2fb63a, 0x9597f423, 0xd77de499, 0xf4af5fac, 0xd9714af2, 0x5f94b2d4, 0xf8418a49, 0xfc36bd51, 0xf6e15ebb, 0xe0bde94e, 0x586e0c3a, 
    0x84bdde62, 0x1e21497f, 0x3e0b4eef, 0xb6a6fdac, 0x143d4e8e, 0x9a6664ba, 0xff8d70d, 0x7713a350, 0x4bcc070c, 0x69fd1fb4, 0x3c2b217, 0x935ec1df, 0xd900e075, 0xd01723a5, 0xd47ecf3e, 0xc17b7a6d, 
    0x722379c0, 0x6d7bd2d8, 0xd53df081, 0xa0434dea, 0x5cdcc3a5, 0x8469a2c6, 0x1a038c61, 0x3afa50f0, 0x466f1555, 0xbd96cb0a, 0x18210bc, 0xb7f3d321, 0x36f87572, 0xa8ef57ea, 0xbf748899, 0xbeadf5, 
    0x193247fb, 0x7c9a47d1, 0xacf72cd5, 0x21aa3227, 0xa317d3bc, 0x936622f8, 0x4c9c5363, 0x3b5a43e6, 0x72a3f9cd, 0x8057796d, 0x81760670, 0x53b21652, 0x2f049e92, 0x8b6046ad, 0xca4af2fc, 0x193cd5fe, 
    0x9bf9d7dc, 0x9dfb7590, 0xe1efe1c3, 0xb004731f, 0x46b2ab23, 0x88156806, 0x9d1d40c5, 0xe5bb12a1, 0x2aa64d28, 0x3d9e0ae, 0x534d4a93, 0xca430730, 0x9d7ed18a, 0xc404ccdb, 0x82d18219, 0x845c8e6a, 
    0x5bf92f94, 0x72b65aa9, 0xb4dee515, 0x6e32da06, 0xef166883, 0x5df5eded, 0x7d95b77, 0x6a9643b6, 0xdd6ac607, 0x1875ebca, 0x956e2cda, 0xb95bffbd, 0x3f6f2dc6, 0x48961ea6, 0xe99881df, 0x3c7c3eb3, 
    0x24ee5a54, 0x78049378, 0xa0fc632e, 0x4cf46404, 0xfe0cd0df, 0x2892e6c9, 0xd604e054, 0xc58ae080, 0x787d1b6, 0xa28341d5, 0x78f3050d, 0x9db4b0f1, 0xd95124fb, 0xaec73e14, 0x4455fb85, 0xacd66ea0, 
    0x379287f6, 0x9100294b, 0xc48be2dd, 0x87cea4ec, 0x9e815514, 0xc4f73821, 0x866f15ec, 0x3265d874, 0x49ed7b8, 0xc36ce00a, 0x1f8f5999, 0x44328ab, 0x4305c687, 0x95e4feef, 0xa38f34a6, 0xe524f878, 
    0x1759a00, 0x69469352, 0x8a4669c, 0x9cf2ac41, 0xd5a0f6e9, 0xc2112de7, 0xf3eea854, 0x739500e5, 0x9ea08a5f, 0xabab6b19, 0xdacc7a6a, 0xc340e801, 0x3b416c1c, 0x814e2ced, 0x5bc4fb4, 0x11b6b726, 
    0xfc48a74, 0x1aeb9f9d, 0xcf7d852a, 0xabd96771, 0xccea39a0, 0x501f9c59, 0x71fbf780, 0x8c42a138, 0x9d36e346, 0x2d7e4e05, 0xd02f9e1c, 0x656732f4, 0xa574999e, 0xc0fd40a6, 0xebbe98cd, 0xa7e2b982, 
    0xe2728dae, 0x7664af8f, 0xd3c232a5, 0xa24ff608, 0xa8a584de, 0xf54d0fec, 0x70d35338, 0x15507e00, 0xb2705993, 0x1c70b7f, 0xe73c690c, 0x1e5635a6, 0xc00a0c6f, 0x939cb9c7, 0x7db9b2ca, 0x2515c6c7, 
};


#define bs_applymask(x,y) bs_addroundkey(x,y)

void bs_addroundkey(word_t * B, word_t * rk)
{
    int i;
    for (i = 0; i < BLOCK_SIZE; i++)
        B[i] ^= rk[i];
}

void bs_apply_sbox(word_t * input, word_t * mask)
{
    int i;
    /*bs_applymask(input, mask);*/
    for(i=0; i < BLOCK_SIZE; i+=8)
    {
        bs_sbox(input+i, mask + i);
    }
    /*bs_applymask(input, mask);*/
}

void bs_apply_sbox_rev(word_t * input)
{
    int i;
    for(i=0; i < BLOCK_SIZE; i+=8)
    {
        bs_sbox_rev(input+i);
    }
}

/*July 2011*/
/*Straight-line program for AES s box*/

/*Input is U[0], U[1],...,U[7]*/
/*Output is S[0], S[1],...,S[7]*/
// http://cs-www.cs.yale.edu/homes/peralta/CircuitStuff/CMT.html
void bs_sbox_rev(word_t U[8])
{
    word_t W[8];
    word_t
        T1,T2,T3,T4,T5,T6,T8,
        T9,T10,T13,T14,T15,T16,
        T17,T18,T19,T20,T22,T23,T24,
        T25, T26, T27;

    word_t
        M1,M2,M3,M4,M5,M6,M7,M8,
        M9,M10,M11,M12,M13,M14,M15,
        M16,M17,M18,M19,M20,M21,M22,
        M23,M24,M25,M26,M27,M28,M29,
        M30,M31,M32,M33,M34,M35,M36,
        M37,M38,M39,M40,M41,M42,M43,
        M44,M45,M46,M47,M48,M49,M50,
        M51,M52,M53,M54,M55,M56,M57,
        M58,M59,M60,M61,M62,M63;

    word_t
        P0,P1,P2,P3,P4,P5,P6,P7,P8,
        P9,P10,P11,P12,P13,P14,
        P15,P16,P17,P18,P19,P20,
        P21,P22,P23,P24,P25,P26,
        P27,P28,P29;

    word_t Y5,
        R5, R13, R17, R18, R19;


    T23 = U[7] ^ U[4];
    T22 = ~(U[6] ^ U[4]);
    T2 = ~(U[7] ^ U[6]);
    T1 = U[4] ^ U[3];
    T24 = ~(U[3] ^ U[0]);
    R5 = U[1] ^ U[0];
    T8 = ~(U[6] ^ T23);
    T19 = T22 ^ R5;
    T9 = ~(U[0] ^ T1);
    T10 = T2 ^ T24;
    T13 = T2 ^ R5;
    T3 = T1 ^ R5;
    T25 = ~(U[5] ^ T1);
    R13 = U[6] ^ U[1];
    T17 = ~(U[5] ^ T19);
    T20 = T24 ^ R13;
    T4 = U[3] ^ T8;
    R17 = ~(U[5] ^ U[2]);
    R18 = ~(U[2] ^ U[1]);
    R19 = ~(U[5] ^ U[3]);
    Y5 = U[7] ^ R17;
    T6 = T22 ^ R17;
    T16 = R13 ^ R19;
    T27 = T1 ^ R18;
    T15 = T10 ^ T27;
    T14 = T10 ^ R18;
    T26 = T3 ^ T16;
    M1 = T13 & T6;
    M2 = T23 & T8;
    M3 = T14 ^ M1;
    M4 = T19 & Y5;
    M5 = M4 ^ M1;
    M6 = T3 & T16;
    M7 = T22 & T9;
    M8 = T26 ^ M6;
    M9 = T20 & T17;
    M10 = M9 ^ M6;
    M11 = T1 & T15;
    M12 = T4 & T27;
    M13 = M12 ^ M11;
    M14 = T2 & T10;
    M15 = M14 ^ M11;
    M16 = M3 ^ M2;
    M17 = M5 ^ T24;
    M18 = M8 ^ M7;
    M19 = M10 ^ M15;
    M20 = M16 ^ M13;
    M21 = M17 ^ M15;
    M22 = M18 ^ M13;
    M23 = M19 ^ T25;
    M24 = M22 ^ M23;
    M25 = M22 & M20;
    M26 = M21 ^ M25;
    M27 = M20 ^ M21;
    M28 = M23 ^ M25;
    M29 = M28 & M27;
    M30 = M26 & M24;
    M31 = M20 & M23;
    M32 = M27 & M31;
    M33 = M27 ^ M25;
    M34 = M21 & M22;
    M35 = M24 & M34;
    M36 = M24 ^ M25;
    M37 = M21 ^ M29;
    M38 = M32 ^ M33;
    M39 = M23 ^ M30;
    M40 = M35 ^ M36;
    M41 = M38 ^ M40;
    M42 = M37 ^ M39;
    M43 = M37 ^ M38;
    M44 = M39 ^ M40;
    M45 = M42 ^ M41;
    M46 = M44 & T6;
    M47 = M40 & T8;
    M48 = M39 & Y5;
    M49 = M43 & T16;
    M50 = M38 & T9;
    M51 = M37 & T17;
    M52 = M42 & T15;
    M53 = M45 & T27;
    M54 = M41 & T10;
    M55 = M44 & T13;
    M56 = M40 & T23;
    M57 = M39 & T19;
    M58 = M43 & T3;
    M59 = M38 & T22;
    M60 = M37 & T20;
    M61 = M42 & T1;
    M62 = M45 & T4;
    M63 = M41 & T2;
    P0 = M52 ^ M61;
    P1 = M58 ^ M59;
    P2 = M54 ^ M62;
    P3 = M47 ^ M50;
    P4 = M48 ^ M56;
    P5 = M46 ^ M51;
    P6 = M49 ^ M60;
    P7 = P0 ^ P1;
    P8 = M50 ^ M53;
    P9 = M55 ^ M63;
    P10 = M57 ^ P4;
    P11 = P0 ^ P3;
    P12 = M46 ^ M48;
    P13 = M49 ^ M51;
    P14 = M49 ^ M62;
    P15 = M54 ^ M59;
    P16 = M57 ^ M61;
    P17 = M58 ^ P2;
    P18 = M63 ^ P5;
    P19 = P2 ^ P3;
    P20 = P4 ^ P6;
    P22 = P2 ^ P7;
    P23 = P7 ^ P8;
    P24 = P5 ^ P7;
    P25 = P6 ^ P10;
    P26 = P9 ^ P11;
    P27 = P10 ^ P18;
    P28 = P11 ^ P25;
    P29 = P15 ^ P20;
    U[7] = P13 ^ P22;
    U[6] = P26 ^ P29;
    U[5] = P17 ^ P28;
    U[4] = P12 ^ P22;
    U[3] = P23 ^ P27;
    U[2] = P19 ^ P24;
    U[1] = P14 ^ P23;
    U[0] = P9 ^ P16;
}

static int rand_indx = 0;

void SAND(word_t p1, word_t p2, word_t q1, word_t q2, word_t * z1, word_t * z2)
{
    //return (r1^(p2&q2)^(p2&q1)) ^ ( r1^(p1&q1)^(p1&q2))
    word_t r1 = rands[((rand_indx++) & 0xff)];
    word_t n1p1 = p1 & q1;
    word_t n1p2 = p2 & q2;

    word_t n2p1 = p1 & q2;
    word_t n2p2 = p2 & q1;

    word_t n3p1 = n1p1 ^ n2p1 ^ r1;
    word_t n3p2 = n1p2 ^ n2p2 ^ r1;

    *z1 = n3p1;
    *z2 = n3p2;

}

void bs_sbox(word_t Up1[8], word_t Up2[8])
{
    word_t S[8];
    word_t
        T1p1,T2p1,T3p1,T4p1,T5p1,T6p1,T7p1,T8p1,
        T9p1,T10p1,T11p1,T12p1,T13p1,T14p1,T15p1,T16p1,
        T17p1,T18p1,T19p1,T20p1,T21p1,T22p1,T23p1,T24p1,
        T25p1, T26p1, T27p1;


    word_t
        M1p1,M2p1,M3p1,M4p1,M5p1,M6p1,M7p1,M8p1,
        M9p1,M10p1,M11p1,M12p1,M13p1,M14p1,M15p1,
        M16p1,M17p1,M18p1,M19p1,M20p1,M21p1,M22p1,
        M23p1,M24p1,M25p1,M26p1,M27p1,M28p1,M29p1,
        M30p1,M31p1,M32p1,M33p1,M34p1,M35p1,M36p1,
        M37p1,M38p1,M39p1,M40p1,M41p1,M42p1,M43p1,
        M44p1,M45p1,M46p1,M47p1,M48p1,M49p1,M50p1,
        M51p1,M52p1,M53p1,M54p1,M55p1,M56p1,M57p1,
        M58p1,M59p1,M60p1,M61p1,M62p1,M63p1;

    word_t
        L0p1,L1p1,L2p1,L3p1,L4p1,L5p1,L6p1,L7p1,L8p1,
        L9p1,L10p1,L11p1,L12p1,L13p1,L14p1,
        L15p1,L16p1,L17p1,L18p1,L19p1,L20p1,
        L21p1,L22p1,L23p1,L24p1,L25p1,L26p1,
        L27p1,L28p1,L29p1;

    word_t
        T1p2,T2p2,T3p2,T4p2,T5p2,T6p2,T7p2,T8p2,
        T9p2,T10p2,T11p2,T12p2,T13p2,T14p2,T15p2,T16p2,
        T17p2,T18p2,T19p2,T20p2,T21p2,T22p2,T23p2,T24p2,
        T25p2, T26p2, T27p2;


    word_t
        M1p2,M2p2,M3p2,M4p2,M5p2,M6p2,M7p2,M8p2,
        M9p2,M10p2,M11p2,M12p2,M13p2,M14p2,M15p2,
        M16p2,M17p2,M18p2,M19p2,M20p2,M21p2,M22p2,
        M23p2,M24p2,M25p2,M26p2,M27p2,M28p2,M29p2,
        M30p2,M31p2,M32p2,M33p2,M34p2,M35p2,M36p2,
        M37p2,M38p2,M39p2,M40p2,M41p2,M42p2,M43p2,
        M44p2,M45p2,M46p2,M47p2,M48p2,M49p2,M50p2,
        M51p2,M52p2,M53p2,M54p2,M55p2,M56p2,M57p2,
        M58p2,M59p2,M60p2,M61p2,M62p2,M63p2;

    word_t
        L0p2,L1p2,L2p2,L3p2,L4p2,L5p2,L6p2,L7p2,L8p2,
        L9p2,L10p2,L11p2,L12p2,L13p2,L14p2,
        L15p2,L16p2,L17p2,L18p2,L19p2,L20p2,
        L21p2,L22p2,L23p2,L24p2,L25p2,L26p2,
        L27p2,L28p2,L29p2;



    T1p1 = Up1[7] ^ Up1[4];
    T1p2 = Up2[7] ^ Up2[4];
    T2p1 = Up1[7] ^ Up1[2];
    T2p2 = Up2[7] ^ Up2[2];
    T3p1 = Up1[7] ^ Up1[1];
    T3p2 = Up2[7] ^ Up2[1];
    T4p1 = Up1[4] ^ Up1[2];
    T4p2 = Up2[4] ^ Up2[2];
    T5p1 = Up1[3] ^ Up1[1];
    T5p2 = Up2[3] ^ Up2[1];
    T6p1 = T1p1 ^ T5p1;
    T6p2 = T1p2 ^ T5p2;
    T7p1 = Up1[6] ^ Up1[5];
    T7p2 = Up2[6] ^ Up2[5];
    T8p1 = Up1[0] ^ T6p1;
    T8p2 = Up2[0] ^ T6p2;
    T9p1 = Up1[0] ^ T7p1;
    T9p2 = Up2[0] ^ T7p2;
    T10p1 = T6p1 ^ T7p1;
    T10p2 = T6p2 ^ T7p2;
    T11p1 = Up1[6] ^ Up1[2];
    T11p2 = Up2[6] ^ Up2[2];
    T12p1 = Up1[5] ^ Up1[2];
    T12p2 = Up2[5] ^ Up2[2];
    T13p1 = T3p1 ^ T4p1;
    T13p2 = T3p2 ^ T4p2;
    T14p1 = T6p1 ^ T11p1;
    T14p2 = T6p2 ^ T11p2;
    T15p1 = T5p1 ^ T11p1;
    T15p2 = T5p2 ^ T11p2;
    T16p1 = T5p1 ^ T12p1;
    T16p2 = T5p2 ^ T12p2;
    T17p1 = T9p1 ^ T16p1;
    T17p2 = T9p2 ^ T16p2;
    T18p1 = Up1[4] ^ Up1[0];
    T18p2 = Up2[4] ^ Up2[0];
    T19p1 = T7p1 ^ T18p1;
    T19p2 = T7p2 ^ T18p2;
    T20p1 = T1p1 ^ T19p1;
    T20p2 = T1p2 ^ T19p2;
    T21p1 = Up1[1] ^ Up1[0];
    T21p2 = Up2[1] ^ Up2[0];
    T22p1 = T7p1 ^ T21p1;
    T22p2 = T7p2 ^ T21p2;
    T23p1 = T2p1 ^ T22p1;
    T23p2 = T2p2 ^ T22p2;
    T24p1 = T2p1 ^ T10p1;
    T24p2 = T2p2 ^ T10p2;
    T25p1 = T20p1 ^ T17p1;
    T25p2 = T20p2 ^ T17p2;
    T26p1 = T3p1 ^ T16p1;
    T26p2 = T3p2 ^ T16p2;
    T27p1 = T1p1 ^ T12p1;
    T27p2 = T1p2 ^ T12p2;

    /*M1p1 = T13p1 & T6p1;*/
    /*M1p2 = T13p2 & T6p2;*/
    SAND(T13p1,T13p2,T6p1,T6p2,&M1p1,&M1p2);

    /*M2p1 = T23p1 & T8p1;*/
    /*M2p2 = T23p2 & T8p2;*/
    SAND(T23p1,T23p2,T8p1,T8p2,&M2p1,&M2p2);

    M3p1 = T14p1 ^ M1p1;
    M3p2 = T14p2 ^ M1p2;

    /*M4p1 = T19p1 & Up1[0];*/
    /*M4p2 = T19p2 & Up2[0];*/
    SAND(T19p1,T19p2,Up1[0],Up2[0],&M4p1,&M4p2);

    M5p1 = M4p1 ^ M1p1;
    M5p2 = M4p2 ^ M1p2;

    /*M6p1 = T3p1 & T16p1;*/
    /*M6p2 = T3p2 & T16p2;*/
    SAND(T3p1,T3p2,T16p1,T16p2,&M6p1,&M6p2);
    /*M7p1 = T22p1 & T9p1;*/
    /*M7p2 = T22p2 & T9p2;*/
    SAND(T22p1,T22p2,T9p1,T9p2,&M7p1,&M7p2);
    
    M8p1 = T26p1 ^ M6p1;
    M8p2 = T26p2 ^ M6p2;

    /*M9p1 = T20p1 & T17p1;*/
    /*M9p2 = T20p2 & T17p2;*/
    SAND(T20p1,T20p2,T17p1,T17p2,&M9p1,&M9p2);

    M10p1 = M9p1 ^ M6p1;
    M10p2 = M9p2 ^ M6p2;

    /*M11p1 = T1p1 & T15p1;*/
    /*M11p2 = T1p2 & T15p2;*/
    SAND(T1p1,T1p2,T15p1,T15p2,&M11p1,&M11p2);
    /*M12p1 = T4p1 & T27p1;*/
    /*M12p2 = T4p2 & T27p2;*/
    SAND(T4p1,T4p2,T27p1,T27p2,&M12p1,&M12p2);

    M13p1 = M12p1 ^ M11p1;
    M13p2 = M12p2 ^ M11p2;

    /*M14p1 = T2p1 & T10p1;*/
    /*M14p2 = T2p2 & T10p2;*/
    SAND(T2p1,T2p2,T10p1,T10p2,&M14p1,&M14p2);

    M15p1 = M14p1 ^ M11p1;
    M15p2 = M14p2 ^ M11p2;
    M16p1 = M3p1 ^ M2p1;
    M16p2 = M3p2 ^ M2p2;
    M17p1 = M5p1 ^ T24p1;
    M17p2 = M5p2 ^ T24p2;
    M18p1 = M8p1 ^ M7p1;
    M18p2 = M8p2 ^ M7p2;
    M19p1 = M10p1 ^ M15p1;
    M19p2 = M10p2 ^ M15p2;
    M20p1 = M16p1 ^ M13p1;
    M20p2 = M16p2 ^ M13p2;
    M21p1 = M17p1 ^ M15p1;
    M21p2 = M17p2 ^ M15p2;
    M22p1 = M18p1 ^ M13p1;
    M22p2 = M18p2 ^ M13p2;
    M23p1 = M19p1 ^ T25p1;
    M23p2 = M19p2 ^ T25p2;
    M24p1 = M22p1 ^ M23p1;
    M24p2 = M22p2 ^ M23p2;

    /*M25p1 = M22p1 & M20p1;*/
    /*M25p2 = M22p2 & M20p2;*/
    SAND(M22p1,M22p2,M20p1,M20p2,&M25p1,&M25p2);
    
    M26p1 = M21p1 ^ M25p1;
    M26p2 = M21p2 ^ M25p2;
    M27p1 = M20p1 ^ M21p1;
    M27p2 = M20p2 ^ M21p2;
    M28p1 = M23p1 ^ M25p1;
    M28p2 = M23p2 ^ M25p2;

    /*M29p1 = M28p1 & M27p1;*/
    /*M29p2 = M28p2 & M27p2;*/
    SAND(M28p1,M28p2,M27p1,M27p2,&M29p1,&M29p2);
    /*M30p1 = M26p1 & M24p1;*/
    /*M30p2 = M26p2 & M24p2;*/
    SAND(M26p1,M26p2,M24p1,M24p2,&M30p1,&M30p2);
    /*M31p1 = M20p1 & M23p1;*/
    /*M31p2 = M20p2 & M23p2;*/
    SAND(M20p1,M20p2,M23p1,M23p2,&M31p1,&M31p2);
    /*M32p1 = M27p1 & M31p1;*/
    /*M32p2 = M27p2 & M31p2;*/
    SAND(M27p1,M27p2,M31p1,M31p2,&M32p1,&M32p2);

    M33p1 = M27p1 ^ M25p1;
    M33p2 = M27p2 ^ M25p2;

    /*M34p1 = M21p1 & M22p1;*/
    /*M34p2 = M21p2 & M22p2;*/
    SAND(M21p1,M21p2,M22p1,M22p2,&M34p1,&M34p2);
    /*M35p1 = M24p1 & M34p1;*/
    /*M35p2 = M24p2 & M34p2;*/
    SAND(M24p1,M24p2,M34p1,M34p2,&M35p1,&M35p2);

    M36p1 = M24p1 ^ M25p1;
    M36p2 = M24p2 ^ M25p2;
    M37p1 = M21p1 ^ M29p1;
    M37p2 = M21p2 ^ M29p2;
    M38p1 = M32p1 ^ M33p1;
    M38p2 = M32p2 ^ M33p2;
    M39p1 = M23p1 ^ M30p1;
    M39p2 = M23p2 ^ M30p2;
    M40p1 = M35p1 ^ M36p1;
    M40p2 = M35p2 ^ M36p2;
    M41p1 = M38p1 ^ M40p1;
    M41p2 = M38p2 ^ M40p2;
    M42p1 = M37p1 ^ M39p1;
    M42p2 = M37p2 ^ M39p2;
    M43p1 = M37p1 ^ M38p1;
    M43p2 = M37p2 ^ M38p2;
    M44p1 = M39p1 ^ M40p1;
    M44p2 = M39p2 ^ M40p2;
    M45p1 = M42p1 ^ M41p1;
    M45p2 = M42p2 ^ M41p2;

    /*M46p1 = M44p1 & T6p1;*/
    /*M46p2 = M44p2 & T6p2;*/
    SAND(M44p1,M44p2,T6p1,T6p2,&M46p1,&M46p2);
    /*M47p1 = M40p1 & T8p1;*/
    /*M47p2 = M40p2 & T8p2;*/
    SAND(M40p1,M40p2,T8p1,T8p2,&M47p1,&M47p2);
    /*M48p1 = M39p1 & Up1[0];*/
    /*M48p2 = M39p2 & Up2[0];*/
    SAND(M39p1,M39p2,Up1[0],Up2[0],&M48p1,&M48p2);
    /*M49p1 = M43p1 & T16p1;*/
    /*M49p2 = M43p2 & T16p2;*/
    SAND(M43p1,M43p2,T16p1,T16p2,&M49p1,&M49p2);
    /*M50p1 = M38p1 & T9p1;*/
    /*M50p2 = M38p2 & T9p2;*/
    SAND(M38p1,M38p2,T9p1,T9p2,&M50p1,&M50p2);
    /*M51p1 = M37p1 & T17p1;*/
    /*M51p2 = M37p2 & T17p2;*/
    SAND(M37p1,M37p2,T17p1,T17p2,&M51p1,&M51p2);
    /*M52p1 = M42p1 & T15p1;*/
    /*M52p2 = M42p2 & T15p2;*/
    SAND(M42p1,M42p2,T15p1,T15p2,&M52p1,&M52p2);
    /*M53p1 = M45p1 & T27p1;*/
    /*M53p2 = M45p2 & T27p2;*/
    SAND(M45p1,M45p2,T27p1,T27p2,&M53p1,&M53p2);
    /*M54p1 = M41p1 & T10p1;*/
    /*M54p2 = M41p2 & T10p2;*/
    SAND(M41p1,M41p2,T10p1,T10p2,&M54p1,&M54p2);
    /*M55p1 = M44p1 & T13p1;*/
    /*M55p2 = M44p2 & T13p2;*/
    SAND(M44p1,M44p2,T13p1,T13p2,&M55p1,&M55p2);
    /*M56p1 = M40p1 & T23p1;*/
    /*M56p2 = M40p2 & T23p2;*/
    SAND(M40p1,M40p2,T23p1,T23p2,&M56p1,&M56p2);
    /*M57p1 = M39p1 & T19p1;*/
    /*M57p2 = M39p2 & T19p2;*/
    SAND(M39p1,M39p2,T19p1,T19p2,&M57p1,&M57p2);
    /*M58p1 = M43p1 & T3p1;*/
    /*M58p2 = M43p2 & T3p2;*/
    SAND(M43p1,M43p2,T3p1,T3p2,&M58p1,&M58p2);
    /*M59p1 = M38p1 & T22p1;*/
    /*M59p2 = M38p2 & T22p2;*/
    SAND(M38p1,M38p2,T22p1,T22p2,&M59p1,&M59p2);
    /*M60p1 = M37p1 & T20p1;*/
    /*M60p2 = M37p2 & T20p2;*/
    SAND(M37p1,M37p2,T20p1,T20p2,&M60p1,&M60p2);
    /*M61p1 = M42p1 & T1p1;*/
    /*M61p2 = M42p2 & T1p2;*/
    SAND(M42p1,M42p2,T1p1,T1p2,&M61p1,&M61p2);
    /*M62p1 = M45p1 & T4p1;*/
    /*M62p2 = M45p2 & T4p2;*/
    SAND(M45p1,M45p2,T4p1,T4p2,&M62p1,&M62p2);
    /*M63p1 = M41p1 & T2p1;*/
    /*M63p2 = M41p2 & T2p2;*/
    SAND(M41p1,M41p2,T2p1,T2p2,&M63p1,&M63p2);

    L0p1 = M61p1 ^ M62p1;
    L0p2 = M61p2 ^ M62p2;
    L1p1 = M50p1 ^ M56p1;
    L1p2 = M50p2 ^ M56p2;
    L2p1 = M46p1 ^ M48p1;
    L2p2 = M46p2 ^ M48p2;
    L3p1 = M47p1 ^ M55p1;
    L3p2 = M47p2 ^ M55p2;
    L4p1 = M54p1 ^ M58p1;
    L4p2 = M54p2 ^ M58p2;
    L5p1 = M49p1 ^ M61p1;
    L5p2 = M49p2 ^ M61p2;
    L6p1 = M62p1 ^ L5p1;
    L6p2 = M62p2 ^ L5p2;
    L7p1 = M46p1 ^ L3p1;
    L7p2 = M46p2 ^ L3p2;
    L8p1 = M51p1 ^ M59p1;
    L8p2 = M51p2 ^ M59p2;
    L9p1 = M52p1 ^ M53p1;
    L9p2 = M52p2 ^ M53p2;
    L10p1 = M53p1 ^ L4p1;
    L10p2 = M53p2 ^ L4p2;
    L11p1 = M60p1 ^ L2p1;
    L11p2 = M60p2 ^ L2p2;
    L12p1 = M48p1 ^ M51p1;
    L12p2 = M48p2 ^ M51p2;
    L13p1 = M50p1 ^ L0p1;
    L13p2 = M50p2 ^ L0p2;
    L14p1 = M52p1 ^ M61p1;
    L14p2 = M52p2 ^ M61p2;
    L15p1 = M55p1 ^ L1p1;
    L15p2 = M55p2 ^ L1p2;
    L16p1 = M56p1 ^ L0p1;
    L16p2 = M56p2 ^ L0p2;
    L17p1 = M57p1 ^ L1p1;
    L17p2 = M57p2 ^ L1p2;
    L18p1 = M58p1 ^ L8p1;
    L18p2 = M58p2 ^ L8p2;
    L19p1 = M63p1 ^ L4p1;
    L19p2 = M63p2 ^ L4p2;
    L20p1 = L0p1 ^ L1p1;
    L20p2 = L0p2 ^ L1p2;
    L21p1 = L1p1 ^ L7p1;
    L21p2 = L1p2 ^ L7p2;
    L22p1 = L3p1 ^ L12p1;
    L22p2 = L3p2 ^ L12p2;
    L23p1 = L18p1 ^ L2p1;
    L23p2 = L18p2 ^ L2p2;
    L24p1 = L15p1 ^ L9p1;
    L24p2 = L15p2 ^ L9p2;
    L25p1 = L6p1 ^ L10p1;
    L25p2 = L6p2 ^ L10p2;
    L26p1 = L7p1 ^ L9p1;
    L26p2 = L7p2 ^ L9p2;
    L27p1 = L8p1 ^ L10p1;
    L27p2 = L8p2 ^ L10p2;
    L28p1 = L11p1 ^ L14p1;
    L28p2 = L11p2 ^ L14p2;
    L29p1 = L11p1 ^ L17p1;
    L29p2 = L11p2 ^ L17p2;
    Up1[7] = L6p1 ^ L24p1;
    Up2[7] = L6p2 ^ L24p2;
    Up1[6] = ~(L16p1 ^ L26p1);
    Up2[6] =  (L16p2 ^ L26p2);
    Up1[5] = ~(L19p1 ^ L28p1);
    Up2[5] =  (L19p2 ^ L28p2);
    Up1[4] = L6p1 ^ L21p1;
    Up2[4] = L6p2 ^ L21p2;
    Up1[3] = L20p1 ^ L22p1;
    Up2[3] = L20p2 ^ L22p2;
    Up1[2] = L25p1 ^ L29p1;
    Up2[2] = L25p2 ^ L29p2;
    Up1[1] = ~(L13p1 ^ L27p1);
    Up2[1] =  (L13p2 ^ L27p2);
    Up1[0] = ~(L6p1 ^ L23p1);
    Up2[0] =  (L6p2 ^ L23p2);
}

void bs_transpose(word_t * blocks)
{
    word_t transpose[BLOCK_SIZE];
    memset(transpose, 0, sizeof(transpose));
    bs_transpose_dst(transpose,blocks);
    memmove(blocks,transpose,sizeof(transpose));
}

void bs_transpose_dst(word_t * transpose, word_t * blocks)
{
    int i,k;
    word_t w;
    for(k=0; k < WORD_SIZE; k++)
    {
        int bitpos = ONE << k;
        for (i=0; i < WORDS_PER_BLOCK; i++)
        {
            w = bs2le(blocks[k * WORDS_PER_BLOCK + i]);
            int offset = i << MUL_SHIFT;

#ifndef UNROLL_TRANSPOSE
            int j;
            for(j=0; j < WORD_SIZE; j++)
            {
                // TODO make const time
                transpose[offset + j] |= (w & (ONE << j)) ? bitpos : 0;
            }
#else

            transpose[(offset)+ 0 ] |= (w & (ONE << 0 )) ? (bitpos) : 0;
            transpose[(offset)+ 1 ] |= (w & (ONE << 1 )) ? (bitpos) : 0;
            transpose[(offset)+ 2 ] |= (w & (ONE << 2 )) ? (bitpos) : 0;
            transpose[(offset)+ 3 ] |= (w & (ONE << 3 )) ? (bitpos) : 0;
            transpose[(offset)+ 4 ] |= (w & (ONE << 4 )) ? (bitpos) : 0;
            transpose[(offset)+ 5 ] |= (w & (ONE << 5 )) ? (bitpos) : 0;
            transpose[(offset)+ 6 ] |= (w & (ONE << 6 )) ? (bitpos) : 0;
            transpose[(offset)+ 7 ] |= (w & (ONE << 7 )) ? (bitpos) : 0;
#if WORD_SIZE > 8
            transpose[(offset)+ 8 ] |= (w & (ONE << 8 )) ? (bitpos) : 0;
            transpose[(offset)+ 9 ] |= (w & (ONE << 9 )) ? (bitpos) : 0;
            transpose[(offset)+ 10] |= (w & (ONE << 10)) ? (bitpos) : 0;
            transpose[(offset)+ 11] |= (w & (ONE << 11)) ? (bitpos) : 0;
            transpose[(offset)+ 12] |= (w & (ONE << 12)) ? (bitpos) : 0;
            transpose[(offset)+ 13] |= (w & (ONE << 13)) ? (bitpos) : 0;
            transpose[(offset)+ 14] |= (w & (ONE << 14)) ? (bitpos) : 0;
            transpose[(offset)+ 15] |= (w & (ONE << 15)) ? (bitpos) : 0;
#endif
#if WORD_SIZE > 16
            transpose[(offset)+ 16] |= (w & (ONE << 16)) ? (bitpos) : 0;
            transpose[(offset)+ 17] |= (w & (ONE << 17)) ? (bitpos) : 0;
            transpose[(offset)+ 18] |= (w & (ONE << 18)) ? (bitpos) : 0;
            transpose[(offset)+ 19] |= (w & (ONE << 19)) ? (bitpos) : 0;
            transpose[(offset)+ 20] |= (w & (ONE << 20)) ? (bitpos) : 0;
            transpose[(offset)+ 21] |= (w & (ONE << 21)) ? (bitpos) : 0;
            transpose[(offset)+ 22] |= (w & (ONE << 22)) ? (bitpos) : 0;
            transpose[(offset)+ 23] |= (w & (ONE << 23)) ? (bitpos) : 0;
            transpose[(offset)+ 24] |= (w & (ONE << 24)) ? (bitpos) : 0;
            transpose[(offset)+ 25] |= (w & (ONE << 25)) ? (bitpos) : 0;
            transpose[(offset)+ 26] |= (w & (ONE << 26)) ? (bitpos) : 0;
            transpose[(offset)+ 27] |= (w & (ONE << 27)) ? (bitpos) : 0;
            transpose[(offset)+ 28] |= (w & (ONE << 28)) ? (bitpos) : 0;
            transpose[(offset)+ 29] |= (w & (ONE << 29)) ? (bitpos) : 0;
            transpose[(offset)+ 30] |= (w & (ONE << 30)) ? (bitpos) : 0;
            transpose[(offset)+ 31] |= (w & (ONE << 31)) ? (bitpos) : 0;
#endif
#if WORD_SIZE > 32
            transpose[(offset)+ 32] |= (w & (ONE << 32)) ? (bitpos) : 0;
            transpose[(offset)+ 33] |= (w & (ONE << 33)) ? (bitpos) : 0;
            transpose[(offset)+ 34] |= (w & (ONE << 34)) ? (bitpos) : 0;
            transpose[(offset)+ 35] |= (w & (ONE << 35)) ? (bitpos) : 0;
            transpose[(offset)+ 36] |= (w & (ONE << 36)) ? (bitpos) : 0;
            transpose[(offset)+ 37] |= (w & (ONE << 37)) ? (bitpos) : 0;
            transpose[(offset)+ 38] |= (w & (ONE << 38)) ? (bitpos) : 0;
            transpose[(offset)+ 39] |= (w & (ONE << 39)) ? (bitpos) : 0;
            transpose[(offset)+ 40] |= (w & (ONE << 40)) ? (bitpos) : 0;
            transpose[(offset)+ 41] |= (w & (ONE << 41)) ? (bitpos) : 0;
            transpose[(offset)+ 42] |= (w & (ONE << 42)) ? (bitpos) : 0;
            transpose[(offset)+ 43] |= (w & (ONE << 43)) ? (bitpos) : 0;
            transpose[(offset)+ 44] |= (w & (ONE << 44)) ? (bitpos) : 0;
            transpose[(offset)+ 45] |= (w & (ONE << 45)) ? (bitpos) : 0;
            transpose[(offset)+ 46] |= (w & (ONE << 46)) ? (bitpos) : 0;
            transpose[(offset)+ 47] |= (w & (ONE << 47)) ? (bitpos) : 0;
            transpose[(offset)+ 48] |= (w & (ONE << 48)) ? (bitpos) : 0;
            transpose[(offset)+ 49] |= (w & (ONE << 49)) ? (bitpos) : 0;
            transpose[(offset)+ 50] |= (w & (ONE << 50)) ? (bitpos) : 0;
            transpose[(offset)+ 51] |= (w & (ONE << 51)) ? (bitpos) : 0;
            transpose[(offset)+ 52] |= (w & (ONE << 52)) ? (bitpos) : 0;
            transpose[(offset)+ 53] |= (w & (ONE << 53)) ? (bitpos) : 0;
            transpose[(offset)+ 54] |= (w & (ONE << 54)) ? (bitpos) : 0;
            transpose[(offset)+ 55] |= (w & (ONE << 55)) ? (bitpos) : 0;
            transpose[(offset)+ 56] |= (w & (ONE << 56)) ? (bitpos) : 0;
            transpose[(offset)+ 57] |= (w & (ONE << 57)) ? (bitpos) : 0;
            transpose[(offset)+ 58] |= (w & (ONE << 58)) ? (bitpos) : 0;
            transpose[(offset)+ 59] |= (w & (ONE << 59)) ? (bitpos) : 0;
            transpose[(offset)+ 60] |= (w & (ONE << 60)) ? (bitpos) : 0;
            transpose[(offset)+ 61] |= (w & (ONE << 61)) ? (bitpos) : 0;
            transpose[(offset)+ 62] |= (w & (ONE << 62)) ? (bitpos) : 0;
            transpose[(offset)+ 63] |= (w & (ONE << 63)) ? (bitpos) : 0;
#endif
#endif
                // constant time:
                //transpose[(i<<MUL_SHIFT)+ j] |= (((int64_t)((w & (ONE << j)) << (WORD_SIZE-1-j)))>>(WORD_SIZE-1)) & (ONE<<k);
        }
    }
}

void bs_transpose_rev(word_t * blocks)
{
    int i,k;
    word_t w;
    word_t transpose[BLOCK_SIZE];
    memset(transpose, 0, sizeof(transpose));
    for(k=0; k < BLOCK_SIZE; k++)
    {
        w = blocks[k];
        word_t bitpos = bs2be(ONE << (k % WORD_SIZE));
        word_t offset = k / WORD_SIZE;
#ifndef UNROLL_TRANSPOSE
        int j;
        for(j=0; j < WORD_SIZE; j++)
        {
            word_t bit = (w & (ONE << j)) ? (ONE << (k % WORD_SIZE)) : 0;
            transpose[j * WORDS_PER_BLOCK + (offset)] |= bit;
        }
#else
        transpose[0  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 0 )) ? bitpos : 0;
        transpose[1  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 1 )) ? bitpos : 0;
        transpose[2  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 2 )) ? bitpos : 0;
        transpose[3  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 3 )) ? bitpos : 0;
        transpose[4  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 4 )) ? bitpos : 0;
        transpose[5  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 5 )) ? bitpos : 0;
        transpose[6  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 6 )) ? bitpos : 0;
        transpose[7  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 7 )) ? bitpos : 0;
#if WORD_SIZE > 8
        transpose[8  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 8 )) ? bitpos : 0;
        transpose[9  * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 9 )) ? bitpos : 0;
        transpose[10 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 10)) ? bitpos : 0;
        transpose[11 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 11)) ? bitpos : 0;
        transpose[12 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 12)) ? bitpos : 0;
        transpose[13 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 13)) ? bitpos : 0;
        transpose[14 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 14)) ? bitpos : 0;
        transpose[15 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 15)) ? bitpos : 0;
#endif
#if WORD_SIZE > 16
        transpose[16 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 16)) ? bitpos : 0;
        transpose[17 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 17)) ? bitpos : 0;
        transpose[18 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 18)) ? bitpos : 0;
        transpose[19 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 19)) ? bitpos : 0;
        transpose[20 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 20)) ? bitpos : 0;
        transpose[21 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 21)) ? bitpos : 0;
        transpose[22 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 22)) ? bitpos : 0;
        transpose[23 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 23)) ? bitpos : 0;
        transpose[24 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 24)) ? bitpos : 0;
        transpose[25 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 25)) ? bitpos : 0;
        transpose[26 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 26)) ? bitpos : 0;
        transpose[27 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 27)) ? bitpos : 0;
        transpose[28 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 28)) ? bitpos : 0;
        transpose[29 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 29)) ? bitpos : 0;
        transpose[30 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 30)) ? bitpos : 0;
        transpose[31 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 31)) ? bitpos : 0;
#endif
#if WORD_SIZE > 32
        transpose[32 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 32)) ? bitpos : 0;
        transpose[33 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 33)) ? bitpos : 0;
        transpose[34 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 34)) ? bitpos : 0;
        transpose[35 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 35)) ? bitpos : 0;
        transpose[36 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 36)) ? bitpos : 0;
        transpose[37 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 37)) ? bitpos : 0;
        transpose[38 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 38)) ? bitpos : 0;
        transpose[39 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 39)) ? bitpos : 0;
        transpose[40 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 40)) ? bitpos : 0;
        transpose[41 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 41)) ? bitpos : 0;
        transpose[42 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 42)) ? bitpos : 0;
        transpose[43 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 43)) ? bitpos : 0;
        transpose[44 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 44)) ? bitpos : 0;
        transpose[45 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 45)) ? bitpos : 0;
        transpose[46 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 46)) ? bitpos : 0;
        transpose[47 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 47)) ? bitpos : 0;
        transpose[48 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 48)) ? bitpos : 0;
        transpose[49 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 49)) ? bitpos : 0;
        transpose[50 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 50)) ? bitpos : 0;
        transpose[51 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 51)) ? bitpos : 0;
        transpose[52 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 52)) ? bitpos : 0;
        transpose[53 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 53)) ? bitpos : 0;
        transpose[54 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 54)) ? bitpos : 0;
        transpose[55 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 55)) ? bitpos : 0;
        transpose[56 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 56)) ? bitpos : 0;
        transpose[57 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 57)) ? bitpos : 0;
        transpose[58 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 58)) ? bitpos : 0;
        transpose[59 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 59)) ? bitpos : 0;
        transpose[60 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 60)) ? bitpos : 0;
        transpose[61 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 61)) ? bitpos : 0;
        transpose[62 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 62)) ? bitpos : 0;
        transpose[63 * WORDS_PER_BLOCK + (offset )] |= (w & (ONE << 63)) ? bitpos : 0;
#endif
#endif
    }
    memmove(blocks,transpose,sizeof(transpose));
}


#define R0          0
#define R1          8
#define R2          16
#define R3          24

#define B0          0
#define B1          32
#define B2          64
#define B3          96

#define R0_shift        (BLOCK_SIZE/4)*0
#define R1_shift        (BLOCK_SIZE/4)*1
#define R2_shift        (BLOCK_SIZE/4)*2
#define R3_shift        (BLOCK_SIZE/4)*3
#define B_MOD           (BLOCK_SIZE)


void bs_shiftrows(word_t * B)
{
    word_t Bp_space[BLOCK_SIZE];
    word_t * Bp = Bp_space;
    word_t * Br0 = B + 0;
    word_t * Br1 = B + 32;
    word_t * Br2 = B + 64;
    word_t * Br3 = B + 96;
    uint8_t offsetr0 = 0;
    uint8_t offsetr1 = 32;
    uint8_t offsetr2 = 64;
    uint8_t offsetr3 = 96;


    int i;
    for(i=0; i<4; i++)
    {
        Bp[B0 + 0] = Br0[0];
        Bp[B0 + 1] = Br0[1];
        Bp[B0 + 2] = Br0[2];
        Bp[B0 + 3] = Br0[3];
        Bp[B0 + 4] = Br0[4];
        Bp[B0 + 5] = Br0[5];
        Bp[B0 + 6] = Br0[6];
        Bp[B0 + 7] = Br0[7];
        Bp[B1 + 0] = Br1[0];
        Bp[B1 + 1] = Br1[1];
        Bp[B1 + 2] = Br1[2];
        Bp[B1 + 3] = Br1[3];
        Bp[B1 + 4] = Br1[4];
        Bp[B1 + 5] = Br1[5];
        Bp[B1 + 6] = Br1[6];
        Bp[B1 + 7] = Br1[7];
        Bp[B2 + 0] = Br2[0];
        Bp[B2 + 1] = Br2[1];
        Bp[B2 + 2] = Br2[2];
        Bp[B2 + 3] = Br2[3];
        Bp[B2 + 4] = Br2[4];
        Bp[B2 + 5] = Br2[5];
        Bp[B2 + 6] = Br2[6];
        Bp[B2 + 7] = Br2[7];
        Bp[B3 + 0] = Br3[0];
        Bp[B3 + 1] = Br3[1];
        Bp[B3 + 2] = Br3[2];
        Bp[B3 + 3] = Br3[3];
        Bp[B3 + 4] = Br3[4];
        Bp[B3 + 5] = Br3[5];
        Bp[B3 + 6] = Br3[6];
        Bp[B3 + 7] = Br3[7];

        offsetr0 = (offsetr0 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;
        offsetr1 = (offsetr1 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;
        offsetr2 = (offsetr2 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;
        offsetr3 = (offsetr3 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;

        Br0 = B + offsetr0;
        Br1 = B + offsetr1;
        Br2 = B + offsetr2;
        Br3 = B + offsetr3;

        Bp += 8;
    }
    memmove(B,Bp_space,sizeof(Bp_space));
}


void bs_shiftrows_rev(word_t * B)
{
    word_t Bp_space[BLOCK_SIZE];
    word_t * Bp = Bp_space;
    word_t * Br0 = Bp + 0;
    word_t * Br1 = Bp + 32;
    word_t * Br2 = Bp + 64;
    word_t * Br3 = Bp + 96;
    uint8_t offsetr0 = 0;
    uint8_t offsetr1 = 32;
    uint8_t offsetr2 = 64;
    uint8_t offsetr3 = 96;


    int i;
    for(i=0; i<4; i++)
    {
        Br0[0] = B[B0 + 0];
        Br0[1] = B[B0 + 1];
        Br0[2] = B[B0 + 2];
        Br0[3] = B[B0 + 3];
        Br0[4] = B[B0 + 4];
        Br0[5] = B[B0 + 5];
        Br0[6] = B[B0 + 6];
        Br0[7] = B[B0 + 7];
        Br1[0] = B[B1 + 0];
        Br1[1] = B[B1 + 1];
        Br1[2] = B[B1 + 2];
        Br1[3] = B[B1 + 3];
        Br1[4] = B[B1 + 4];
        Br1[5] = B[B1 + 5];
        Br1[6] = B[B1 + 6];
        Br1[7] = B[B1 + 7];
        Br2[0] = B[B2 + 0];
        Br2[1] = B[B2 + 1];
        Br2[2] = B[B2 + 2];
        Br2[3] = B[B2 + 3];
        Br2[4] = B[B2 + 4];
        Br2[5] = B[B2 + 5];
        Br2[6] = B[B2 + 6];
        Br2[7] = B[B2 + 7];
        Br3[0] = B[B3 + 0];
        Br3[1] = B[B3 + 1];
        Br3[2] = B[B3 + 2];
        Br3[3] = B[B3 + 3];
        Br3[4] = B[B3 + 4];
        Br3[5] = B[B3 + 5];
        Br3[6] = B[B3 + 6];
        Br3[7] = B[B3 + 7];

        offsetr0 = (offsetr0 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;
        offsetr1 = (offsetr1 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;
        offsetr2 = (offsetr2 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;
        offsetr3 = (offsetr3 + BLOCK_SIZE/16 + BLOCK_SIZE/4) & 0x7f;

        Br0 = Bp + offsetr0;
        Br1 = Bp + offsetr1;
        Br2 = Bp + offsetr2;
        Br3 = Bp + offsetr3;

        B += 8;
    }
    memmove(B - 8 * 4,Bp_space,sizeof(Bp_space));
}


#define A0  0
#define A1  8
#define A2  16
#define A3  24

// Does shift rows and mix columns in same step
void bs_shiftmix(word_t * B)
{
    word_t Bp_space[BLOCK_SIZE];
    word_t * Bp = Bp_space;

    word_t * Br0 = B + 0;
    word_t * Br1 = B + 32;
    word_t * Br2 = B + 64;
    word_t * Br3 = B + 96;

    uint8_t offsetr0 = 0;
    uint8_t offsetr1 = 32;
    uint8_t offsetr2 = 64;
    uint8_t offsetr3 = 96;

        Br0 = B + offsetr0;
        Br1 = B + offsetr1;
        Br2 = B + offsetr2;
        Br3 = B + offsetr3;


    int i;
    for (i = 0; i < 4; i++)
    {
        // B0
        //            2*A0        2*A1              A1           A2           A3
        word_t of =Br0[R0+7]^ Br1[R1+7];
        Bp[A0+0] =                         Br1[R1+0] ^ Br2[R2+0] ^ Br3[R3+0] ^ of;
        Bp[A0+1] = Br0[R0+0] ^ Br1[R1+0] ^ Br1[R1+1] ^ Br2[R2+1] ^ Br3[R3+1] ^ of;
        Bp[A0+2] = Br0[R0+1] ^ Br1[R1+1] ^ Br1[R1+2] ^ Br2[R2+2] ^ Br3[R3+2];
        Bp[A0+3] = Br0[R0+2] ^ Br1[R1+2] ^ Br1[R1+3] ^ Br2[R2+3] ^ Br3[R3+3] ^ of;
        Bp[A0+4] = Br0[R0+3] ^ Br1[R1+3] ^ Br1[R1+4] ^ Br2[R2+4] ^ Br3[R3+4] ^ of;
        Bp[A0+5] = Br0[R0+4] ^ Br1[R1+4] ^ Br1[R1+5] ^ Br2[R2+5] ^ Br3[R3+5];
        Bp[A0+6] = Br0[R0+5] ^ Br1[R1+5] ^ Br1[R1+6] ^ Br2[R2+6] ^ Br3[R3+6];
        Bp[A0+7] = Br0[R0+6] ^ Br1[R1+6] ^ Br1[R1+7] ^ Br2[R2+7] ^ Br3[R3+7];

        //            A0            2*A1        2*A2        A2       A3
        of = Br1[R1+7] ^ Br2[R2+7];
        Bp[A1+0] = Br0[R0+0]                         ^ Br2[R2+0] ^ Br3[R3+0] ^ of;
        Bp[A1+1] = Br0[R0+1] ^ Br1[R1+0] ^ Br2[R2+0] ^ Br2[R2+1] ^ Br3[R3+1] ^ of;
        Bp[A1+2] = Br0[R0+2] ^ Br1[R1+1] ^ Br2[R2+1] ^ Br2[R2+2] ^ Br3[R3+2];
        Bp[A1+3] = Br0[R0+3] ^ Br1[R1+2] ^ Br2[R2+2] ^ Br2[R2+3] ^ Br3[R3+3] ^ of;
        Bp[A1+4] = Br0[R0+4] ^ Br1[R1+3] ^ Br2[R2+3] ^ Br2[R2+4] ^ Br3[R3+4] ^ of;
        Bp[A1+5] = Br0[R0+5] ^ Br1[R1+4] ^ Br2[R2+4] ^ Br2[R2+5] ^ Br3[R3+5];
        Bp[A1+6] = Br0[R0+6] ^ Br1[R1+5] ^ Br2[R2+5] ^ Br2[R2+6] ^ Br3[R3+6];
        Bp[A1+7] = Br0[R0+7] ^ Br1[R1+6] ^ Br2[R2+6] ^ Br2[R2+7] ^ Br3[R3+7];

        //            A0             A1      2*A2        2*A3         A3
        of = Br2[R2+7] ^ Br3[R3+7];
        Bp[A2+0] = Br0[R0+0] ^ Br1[R1+0]                         ^ Br3[R3+0] ^ of;
        Bp[A2+1] = Br0[R0+1] ^ Br1[R1+1] ^ Br2[R2+0] ^ Br3[R3+0] ^ Br3[R3+1] ^ of;
        Bp[A2+2] = Br0[R0+2] ^ Br1[R1+2] ^ Br2[R2+1] ^ Br3[R3+1] ^ Br3[R3+2];
        Bp[A2+3] = Br0[R0+3] ^ Br1[R1+3] ^ Br2[R2+2] ^ Br3[R3+2] ^ Br3[R3+3] ^ of;
        Bp[A2+4] = Br0[R0+4] ^ Br1[R1+4] ^ Br2[R2+3] ^ Br3[R3+3] ^ Br3[R3+4] ^ of;
        Bp[A2+5] = Br0[R0+5] ^ Br1[R1+5] ^ Br2[R2+4] ^ Br3[R3+4] ^ Br3[R3+5];
        Bp[A2+6] = Br0[R0+6] ^ Br1[R1+6] ^ Br2[R2+5] ^ Br3[R3+5] ^ Br3[R3+6];
        Bp[A2+7] = Br0[R0+7] ^ Br1[R1+7] ^ Br2[R2+6] ^ Br3[R3+6] ^ Br3[R3+7];

        //             A0          2*A0           A1       A2      2*A3
        of = Br0[R0+7] ^ Br3[R3+7];
        Bp[A3+0] = Br0[R0+0] ^             Br1[R1+0] ^ Br2[R2+0]             ^ of;
        Bp[A3+1] = Br0[R0+1] ^ Br0[R0+0] ^ Br1[R1+1] ^ Br2[R2+1] ^ Br3[R3+0] ^ of;
        Bp[A3+2] = Br0[R0+2] ^ Br0[R0+1] ^ Br1[R1+2] ^ Br2[R2+2] ^ Br3[R3+1];
        Bp[A3+3] = Br0[R0+3] ^ Br0[R0+2] ^ Br1[R1+3] ^ Br2[R2+3] ^ Br3[R3+2] ^ of;
        Bp[A3+4] = Br0[R0+4] ^ Br0[R0+3] ^ Br1[R1+4] ^ Br2[R2+4] ^ Br3[R3+3] ^ of;
        Bp[A3+5] = Br0[R0+5] ^ Br0[R0+4] ^ Br1[R1+5] ^ Br2[R2+5] ^ Br3[R3+4];
        Bp[A3+6] = Br0[R0+6] ^ Br0[R0+5] ^ Br1[R1+6] ^ Br2[R2+6] ^ Br3[R3+5];
        Bp[A3+7] = Br0[R0+7] ^ Br0[R0+6] ^ Br1[R1+7] ^ Br2[R2+7] ^ Br3[R3+6];

        Bp += BLOCK_SIZE/4;

        offsetr0 = (offsetr0 + BLOCK_SIZE/4) & 0x7f;
        offsetr1 = (offsetr1 + BLOCK_SIZE/4) & 0x7f;
        offsetr2 = (offsetr2 + BLOCK_SIZE/4) & 0x7f;
        offsetr3 = (offsetr3 + BLOCK_SIZE/4) & 0x7f;

        Br0 = B + offsetr0;
        Br1 = B + offsetr1;
        Br2 = B + offsetr2;
        Br3 = B + offsetr3;
    }

    memmove(B,Bp_space,sizeof(Bp_space));
}



void bs_mixcolumns(word_t * B)
{
    word_t Bp_space[BLOCK_SIZE];
    word_t * Bp = Bp_space;
    // to understand this, see
    // https://en.wikipedia.org/wiki/Rijndael_mix_columns
    
    int i = 0;
    for (; i < 4; i++)
    {
    //  of = A0 ^ A1;
    //  A0 = A0 ^ (0x1b & ((signed char)of>>7));

    //// 2 * A0
    //  A0 = A0 ^ (A0 << 1)

    //// + 3 * A1
    //  A0 = A0 ^ (A1)
    //  A0 = A0 ^ (A1<<1)

    //// + A2 + A3
    //  A0 = A0 ^ (A2)
    //  A0 = A0 ^ (A3)
    //          A0.7    A1.7
    word_t of = B[A0+7] ^ B[A1+7];

    //          2*A0     2*A1          A1      A2           A3
    Bp[A0+0] =                     B[A1+0] ^ B[A2+0] ^ B[A3+0] ^ of;
    Bp[A0+1] = B[A0+0] ^ B[A1+0] ^ B[A1+1] ^ B[A2+1] ^ B[A3+1] ^ of;
    Bp[A0+2] = B[A0+1] ^ B[A1+1] ^ B[A1+2] ^ B[A2+2] ^ B[A3+2];
    Bp[A0+3] = B[A0+2] ^ B[A1+2] ^ B[A1+3] ^ B[A2+3] ^ B[A3+3] ^ of;
    Bp[A0+4] = B[A0+3] ^ B[A1+3] ^ B[A1+4] ^ B[A2+4] ^ B[A3+4] ^ of;
    Bp[A0+5] = B[A0+4] ^ B[A1+4] ^ B[A1+5] ^ B[A2+5] ^ B[A3+5];
    Bp[A0+6] = B[A0+5] ^ B[A1+5] ^ B[A1+6] ^ B[A2+6] ^ B[A3+6];
    Bp[A0+7] = B[A0+6] ^ B[A1+6] ^ B[A1+7] ^ B[A2+7] ^ B[A3+7];



    //  of = A1 ^ A2
    //  A1 = A1 ^ (0x1b & ((signed char)of>>7));

    //// A0
    //  A1 = A1 ^ (A0)

    //// + 2 * A1
    //  A1 = A1 ^ (A1 << 1)

    //// + 3 * A2
    //  A1 = A1 ^ (A2)
    //  A1 = A1 ^ (A2<<1)

    //// + A3
    //  A1 = A1 ^ (A3)

    of = B[A1+7] ^ B[A2+7];

    //          A0      2*A1        2*A2      A2        A3
    Bp[A1+0] = B[A0+0]                     ^ B[A2+0] ^ B[A3+0] ^ of;
    Bp[A1+1] = B[A0+1] ^ B[A1+0] ^ B[A2+0] ^ B[A2+1] ^ B[A3+1] ^ of;
    Bp[A1+2] = B[A0+2] ^ B[A1+1] ^ B[A2+1] ^ B[A2+2] ^ B[A3+2];
    Bp[A1+3] = B[A0+3] ^ B[A1+2] ^ B[A2+2] ^ B[A2+3] ^ B[A3+3] ^ of;
    Bp[A1+4] = B[A0+4] ^ B[A1+3] ^ B[A2+3] ^ B[A2+4] ^ B[A3+4] ^ of;
    Bp[A1+5] = B[A0+5] ^ B[A1+4] ^ B[A2+4] ^ B[A2+5] ^ B[A3+5];
    Bp[A1+6] = B[A0+6] ^ B[A1+5] ^ B[A2+5] ^ B[A2+6] ^ B[A3+6];
    Bp[A1+7] = B[A0+7] ^ B[A1+6] ^ B[A2+6] ^ B[A2+7] ^ B[A3+7];
    

    //  of = A2 ^ A3
    //  A2 = A2 ^ (0x1b & ((signed char)of>>7));

    //// A0 + A1
    //  A2 = A2 ^ (A0)
    //  A2 = A2 ^ (A1)

    //// + 2 * A2
    //  A2 = A2 ^ (A2 << 1)

    //// + 3 * A3
    //  A2 = A2 ^ (A3)
    //  A2 = A2 ^ (A3<<1)


    of = B[A2+7] ^ B[A3+7];

    //          A0      A1          2*A2       2*A3         A3
    Bp[A2+0] = B[A0+0] ^ B[A1+0]                     ^ B[A3+0] ^ of;
    Bp[A2+1] = B[A0+1] ^ B[A1+1] ^ B[A2+0] ^ B[A3+0] ^ B[A3+1] ^ of;
    Bp[A2+2] = B[A0+2] ^ B[A1+2] ^ B[A2+1] ^ B[A3+1] ^ B[A3+2];
    Bp[A2+3] = B[A0+3] ^ B[A1+3] ^ B[A2+2] ^ B[A3+2] ^ B[A3+3] ^ of;
    Bp[A2+4] = B[A0+4] ^ B[A1+4] ^ B[A2+3] ^ B[A3+3] ^ B[A3+4] ^ of;
    Bp[A2+5] = B[A0+5] ^ B[A1+5] ^ B[A2+4] ^ B[A3+4] ^ B[A3+5];
    Bp[A2+6] = B[A0+6] ^ B[A1+6] ^ B[A2+5] ^ B[A3+5] ^ B[A3+6];
    Bp[A2+7] = B[A0+7] ^ B[A1+7] ^ B[A2+6] ^ B[A3+6] ^ B[A3+7];
    

    //  A3 = A0 ^ A3
    //  A3 = A3 ^ (0x1b & ((signed char)of>>7));

    //// 3 * A0
    //  A3 = A3 ^ (A0)
    //  A3 = A3 ^ (A0 << 1)

    //// + A1 + A2
    //  A3 = A3 ^ A1
    //  A3 = A3 ^ A2

    //// + 2 * A3
    //  A3 = A3 ^ (A3<<1)

    of = B[A0+7] ^ B[A3+7];

    //        2*A0       A0         A1         A2       2*A3
    Bp[A3+0] = B[A0+0] ^           B[A1+0] ^ B[A2+0]           ^ of;
    Bp[A3+1] = B[A0+1] ^ B[A0+0] ^ B[A1+1] ^ B[A2+1] ^ B[A3+0] ^ of;
    Bp[A3+2] = B[A0+2] ^ B[A0+1] ^ B[A1+2] ^ B[A2+2] ^ B[A3+1];
    Bp[A3+3] = B[A0+3] ^ B[A0+2] ^ B[A1+3] ^ B[A2+3] ^ B[A3+2] ^ of;
    Bp[A3+4] = B[A0+4] ^ B[A0+3] ^ B[A1+4] ^ B[A2+4] ^ B[A3+3] ^ of;
    Bp[A3+5] = B[A0+5] ^ B[A0+4] ^ B[A1+5] ^ B[A2+5] ^ B[A3+4];
    Bp[A3+6] = B[A0+6] ^ B[A0+5] ^ B[A1+6] ^ B[A2+6] ^ B[A3+5];
    Bp[A3+7] = B[A0+7] ^ B[A0+6] ^ B[A1+7] ^ B[A2+7] ^ B[A3+6];
    

    //
    Bp += BLOCK_SIZE/4;
    B  += BLOCK_SIZE/4;
    }


    memmove(B - BLOCK_SIZE,Bp - BLOCK_SIZE,sizeof(Bp_space));
}

void bs_mixcolumns_rev(word_t * B)
{
    // to understand this, see
    // https://en.wikipedia.org/wiki/Rijndael_mix_columns
    // TODO combine with shiftrows for performance on decryption
    word_t Bp_space[BLOCK_SIZE];
    word_t * Bp = Bp_space;

 
    int i = 0;
    for (; i < BLOCK_SIZE / 4; i += BLOCK_SIZE / 16)
    {

    //// state[i][0] = A0*0x0e + A1*0x0b + A2*0x0d + A3*0x09
    // overflow:
                    /* A0 * 0b1110             */   /* A1 * 0b1011     */   /* A2 * 0b1101   */   /* A3 * 0b1001 */
    word_t of0 = (  (B[A0+7] ^ B[A0+6] ^ B[A0+5]) ^ (B[A1 + 7] ^ B[A1+5]) ^ (B[A2+6] ^ B[A2+5]) ^ ( B[A3+5] ));       // 2 bit
    word_t of1 = (            (B[A0+7] ^ B[A0+6]) ^ (            B[A1+6]) ^ (B[A2+7] ^ B[A2+6]) ^ ( B[A3+6] ));       // 3 bit
    word_t of2 = (                      (B[A0+7]) ^ (            B[A1+7]) ^ (          B[A2+7]) ^ ( B[A3+7] ));       // 4 bit

    // inverse:
    //          1110      1011    1101      1001
    // A0 = A0 * 14 + A1 * 11 + A2 * 13 + A3 * 9
    // A0 = A0 * (2+4+8) + A1 * (1+2+8) + A2 * (1+4+8) + A3 * (1+8)

    //         (2*A0   +  4*A0   + 8*A0 )  + (8*A1   +  2*A1   +   A1  ) + ( A2    +   4*A2  +  8*A2 ) + (  A3   + 8*A3)
    Bp[A0+0] =                                                   B[A1+0] ^ B[A2+0]                     ^ B[A3+0]           ^ of0;
    Bp[A0+1] = B[A0+0]                               ^ B[A1+0] ^ B[A1+1] ^ B[A2+1]                     ^ B[A3+1]           ^ of0 ^ of1;
    Bp[A0+2] = B[A0+1] ^ B[A0+0]                     ^ B[A1+1] ^ B[A1+2] ^ B[A2+2] ^ B[A2+0]           ^ B[A3+2]                 ^ of1 ^ of2;
    Bp[A0+3] = B[A0+2] ^ B[A0+1] ^ B[A0+0] ^ B[A1+0] ^ B[A1+2] ^ B[A1+3] ^ B[A2+3] ^ B[A2+1] ^ B[A2+0] ^ B[A3+3] ^ B[A3+0] ^ of0       ^ of2;
    Bp[A0+4] = B[A0+3] ^ B[A0+2] ^ B[A0+1] ^ B[A1+1] ^ B[A1+3] ^ B[A1+4] ^ B[A2+4] ^ B[A2+2] ^ B[A2+1] ^ B[A3+4] ^ B[A3+1] ^ of0 ^ of1;
    Bp[A0+5] = B[A0+4] ^ B[A0+3] ^ B[A0+2] ^ B[A1+2] ^ B[A1+4] ^ B[A1+5] ^ B[A2+5] ^ B[A2+3] ^ B[A2+2] ^ B[A3+5] ^ B[A3+2]       ^ of1 ^ of2;
    Bp[A0+6] = B[A0+5] ^ B[A0+4] ^ B[A0+3] ^ B[A1+3] ^ B[A1+5] ^ B[A1+6] ^ B[A2+6] ^ B[A2+4] ^ B[A2+3] ^ B[A3+6] ^ B[A3+3]             ^ of2;
    Bp[A0+7] = B[A0+6] ^ B[A0+5] ^ B[A0+4] ^ B[A1+4] ^ B[A1+6] ^ B[A1+7] ^ B[A2+7] ^ B[A2+5] ^ B[A2+4] ^ B[A3+7] ^ B[A3+4];



    //// state[i][1] = A0*0x09 + A1*0xe + A2*0x0b + A3*0x0d
    // overflow:
          /* A0 * 0b1001 */   /* A1 * 0b1110             */ /* A2 * 0b101  1     */   /* A3 * 0b1101 */
    of0 = (  (B[A0+5]) ^      (B[A1+7] ^ B[A1+6] ^ B[A1+5]) ^ (B[A2 + 7] ^ B[A2+5]) ^ (B[A3+6] ^ B[A3+5]));       // 2 bit
    of1 = (  (B[A0+6]) ^                (B[A1+7] ^ B[A1+6]) ^ (            B[A2+6]) ^ (B[A3+7] ^ B[A3+6]));       // 3 bit
    of2 = (  (B[A0+7]) ^                          (B[A1+7]) ^ (            B[A2+7]) ^ (          B[A3+7]));       // 4 bit

    // inverse:
    //          1001      1110    1011      1101
    // A1 = A0 * 9 + A1 * 14 + A2 * 11 + A3 * 13
    // A1 = A0 * (1+8) + A1 * (2+4+8) + A2 * (1+2+8) + A3 * (1+4+8)

    //         (1*A0   +  8*A0 ) +(2*A1    +  4*A1   +  8*A1 ) + (1*A2   +  2*A2   +  8*A2 ) + (1*A3   +   4*A3  +  8*A3)
    Bp[A1+0] = B[A0+0] ^                                         B[A2+0] ^                     B[A3+0]                     ^ of0;
    Bp[A1+1] = B[A0+1] ^           B[A1+0]                     ^ B[A2+1] ^ B[A2+0] ^           B[A3+1]                     ^ of0 ^ of1;
    Bp[A1+2] = B[A0+2] ^           B[A1+1] ^ B[A1+0]           ^ B[A2+2] ^ B[A2+1] ^           B[A3+2] ^ B[A3+0]                 ^ of1 ^ of2;
    Bp[A1+3] = B[A0+3] ^ B[A0+0] ^ B[A1+2] ^ B[A1+1] ^ B[A1+0] ^ B[A2+3] ^ B[A2+2] ^ B[A2+0] ^ B[A3+3] ^ B[A3+1] ^ B[A3+0] ^ of0       ^ of2;
    Bp[A1+4] = B[A0+4] ^ B[A0+1] ^ B[A1+3] ^ B[A1+2] ^ B[A1+1] ^ B[A2+4] ^ B[A2+3] ^ B[A2+1] ^ B[A3+4] ^ B[A3+2] ^ B[A3+1] ^ of0 ^ of1;
    Bp[A1+5] = B[A0+5] ^ B[A0+2] ^ B[A1+4] ^ B[A1+3] ^ B[A1+2] ^ B[A2+5] ^ B[A2+4] ^ B[A2+2] ^ B[A3+5] ^ B[A3+3] ^ B[A3+2]       ^ of1 ^ of2;
    Bp[A1+6] = B[A0+6] ^ B[A0+3] ^ B[A1+5] ^ B[A1+4] ^ B[A1+3] ^ B[A2+6] ^ B[A2+5] ^ B[A2+3] ^ B[A3+6] ^ B[A3+4] ^ B[A3+3]             ^ of2;
    Bp[A1+7] = B[A0+7] ^ B[A0+4] ^ B[A1+6] ^ B[A1+5] ^ B[A1+4] ^ B[A2+7] ^ B[A2+6] ^ B[A2+4] ^ B[A3+7] ^ B[A3+5] ^ B[A3+4];


    //// state[i][2] = A0*0x0d + A1*0x09 + A2*0x0e + A3*0x0b
    // overflow:
          /* A1 * 0b1001 */  /* A2 * 0b1110              */ /* A3 * 0b1011      */   /* A0 * 0b1101 */
    of0 = (  (B[A1+5]) ^      (B[A2+7] ^ B[A2+6] ^ B[A2+5]) ^ (B[A3 + 7] ^ B[A3+5]) ^ (B[A0+6] ^ B[A0+5]));       // 2 bit
    of1 = (  (B[A1+6]) ^                (B[A2+7] ^ B[A2+6]) ^ (            B[A3+6]) ^ (B[A0+7] ^ B[A0+6]));       // 3 bit
    of2 = (  (B[A1+7]) ^                          (B[A2+7]) ^ (            B[A3+7]) ^ (          B[A0+7]));       // 4 bit

    // inverse:
    //          1001      1110    1011      1101
    // A2 = A1 * 9 + A2 * 14 + A3 * 11 + A0 * 13
    // A2 = A1 * (1+8) + A2 * (2+4+8) + A3 * (1+2+8) + A0 * (1+4+8)

    //         (1*A1   +  8*A1) + ( 2*A2   +  4*A2   +  8*A2)  + (1*A3      2*A2   +  8*A2) +  (1*A0   +   4*A0  +  8*A0)
    Bp[A2+0] = B[A1+0] ^                                         B[A3+0] ^                     B[A0+0]                     ^ of0;
    Bp[A2+1] = B[A1+1] ^           B[A2+0]                     ^ B[A3+1] ^ B[A3+0] ^           B[A0+1]                     ^ of0 ^ of1;
    Bp[A2+2] = B[A1+2] ^           B[A2+1] ^ B[A2+0]           ^ B[A3+2] ^ B[A3+1] ^           B[A0+2] ^ B[A0+0]                 ^ of1 ^ of2;
    Bp[A2+3] = B[A1+3] ^ B[A1+0] ^ B[A2+2] ^ B[A2+1] ^ B[A2+0] ^ B[A3+3] ^ B[A3+2] ^ B[A3+0] ^ B[A0+3] ^ B[A0+1] ^ B[A0+0] ^ of0       ^ of2;
    Bp[A2+4] = B[A1+4] ^ B[A1+1] ^ B[A2+3] ^ B[A2+2] ^ B[A2+1] ^ B[A3+4] ^ B[A3+3] ^ B[A3+1] ^ B[A0+4] ^ B[A0+2] ^ B[A0+1] ^ of0 ^ of1;
    Bp[A2+5] = B[A1+5] ^ B[A1+2] ^ B[A2+4] ^ B[A2+3] ^ B[A2+2] ^ B[A3+5] ^ B[A3+4] ^ B[A3+2] ^ B[A0+5] ^ B[A0+3] ^ B[A0+2]       ^ of1 ^ of2;
    Bp[A2+6] = B[A1+6] ^ B[A1+3] ^ B[A2+5] ^ B[A2+4] ^ B[A2+3] ^ B[A3+6] ^ B[A3+5] ^ B[A3+3] ^ B[A0+6] ^ B[A0+4] ^ B[A0+3]             ^ of2;
    Bp[A2+7] = B[A1+7] ^ B[A1+4] ^ B[A2+6] ^ B[A2+5] ^ B[A2+4] ^ B[A3+7] ^ B[A3+6] ^ B[A3+4] ^ B[A0+7] ^ B[A0+5] ^ B[A0+4];



    //// state[i][3] = A0*0x0b + A1*0x0d + A2*0x09 + A3*0x0e
    // overflow:
           /* A2 * 0b1001 */  /* A3 * 0b1110             */ /* A0 * 0b1011     */     /* A1 * 0b1101 */
    of0 = (  (B[A2+5]) ^      (B[A3+7] ^ B[A3+6] ^ B[A3+5]) ^ (B[A0 + 7] ^ B[A0+5]) ^ (B[A1+6] ^ B[A1+5]));       // 2 bit
    of1 = (  (B[A2+6]) ^                (B[A3+7] ^ B[A3+6]) ^ (            B[A0+6]) ^ (B[A1+7] ^ B[A1+6]));       // 3 bit
    of2 = (  (B[A2+7]) ^                          (B[A3+7]) ^ (            B[A0+7]) ^ (          B[A1+7]));       // 4 bit

    // inverse:
    //          1001      1110    1011      1101
    // A2 = A2 * 9 + A3 * 14 + A0 * 11 + A1 * 13
    // A2 = A2 * (1+8) + A3 * (2+4+8) + A0 * (1+2+8) + A1 * (1+4+8)

    //         (1*A2   +  8*A2) + ( 2*A3   +  4*A3   +  8*A3)  + (1*A0      2*A0   +  8*A0) +  (1*A1   +   4*A1  +  8*A1)
    Bp[A3+0] = B[A2+0] ^                                         B[A0+0] ^                     B[A1+0]                     ^ of0;
    Bp[A3+1] = B[A2+1] ^           B[A3+0]                     ^ B[A0+1] ^ B[A0+0] ^           B[A1+1]                     ^ of0 ^ of1;
    Bp[A3+2] = B[A2+2] ^           B[A3+1] ^ B[A3+0]           ^ B[A0+2] ^ B[A0+1] ^           B[A1+2] ^ B[A1+0]                 ^ of1 ^ of2;
    Bp[A3+3] = B[A2+3] ^ B[A2+0] ^ B[A3+2] ^ B[A3+1] ^ B[A3+0] ^ B[A0+3] ^ B[A0+2] ^ B[A0+0] ^ B[A1+3] ^ B[A1+1] ^ B[A1+0] ^ of0       ^ of2;
    Bp[A3+4] = B[A2+4] ^ B[A2+1] ^ B[A3+3] ^ B[A3+2] ^ B[A3+1] ^ B[A0+4] ^ B[A0+3] ^ B[A0+1] ^ B[A1+4] ^ B[A1+2] ^ B[A1+1] ^ of0 ^ of1;
    Bp[A3+5] = B[A2+5] ^ B[A2+2] ^ B[A3+4] ^ B[A3+3] ^ B[A3+2] ^ B[A0+5] ^ B[A0+4] ^ B[A0+2] ^ B[A1+5] ^ B[A1+3] ^ B[A1+2]       ^ of1 ^ of2;
    Bp[A3+6] = B[A2+6] ^ B[A2+3] ^ B[A3+5] ^ B[A3+4] ^ B[A3+3] ^ B[A0+6] ^ B[A0+5] ^ B[A0+3] ^ B[A1+6] ^ B[A1+4] ^ B[A1+3]             ^ of2;
    Bp[A3+7] = B[A2+7] ^ B[A2+4] ^ B[A3+6] ^ B[A3+5] ^ B[A3+4] ^ B[A0+7] ^ B[A0+6] ^ B[A0+4] ^ B[A1+7] ^ B[A1+5] ^ B[A1+4];

    Bp += BLOCK_SIZE/4;
    B  += BLOCK_SIZE/4;
    }

    memmove(B - BLOCK_SIZE, Bp - BLOCK_SIZE,sizeof(Bp_space));

}

void bs_expand_key(word_t (* rk)[BLOCK_SIZE], uint8_t * _key)
{
    // TODO integrate this better
    uint8_t key[KEY_SCHEDULE_SIZE];
    memmove(key,_key,BLOCK_SIZE/8);
    expand_key(key);

    int i, j = 0, k, l;
    for (i = 0; i < KEY_SCHEDULE_SIZE; i += (BLOCK_SIZE/8))
    {
        memmove(rk[j], key + i, BLOCK_SIZE / 8);

        for (k = WORDS_PER_BLOCK; k < 128; k += WORDS_PER_BLOCK)
        {
            for (l = 0; l < WORDS_PER_BLOCK; l++)
            {
                rk[j][k + l] = rk[j][l];
            }
        }
        bs_transpose(rk[j]);
        j++;
    }

}

void bs_cipher(word_t state[BLOCK_SIZE], word_t maskb[BLOCK_SIZE], word_t (* rk)[BLOCK_SIZE])
{
    int round;
    bs_transpose(state);

    bs_applymask(state, maskb);

    TRIGGER = 0xff;
    asm("nop");
    asm("nop");
    asm("nop");
    TRIGGER = 0x0;

    bs_addroundkey(state,rk[0]);

    for (round = 1; round < 10; round++)
    {
        bs_apply_sbox(state, maskb);
        
        /*bs_shiftrows(state);*/
        /*bs_mixcolumns(state);*/

        bs_shiftmix(state);
        bs_shiftmix(maskb);
        bs_addroundkey(state,rk[round]);
    }

    bs_apply_sbox(state, maskb);
    bs_shiftrows(state);
    bs_shiftrows(maskb);
    bs_addroundkey(state,rk[10]);

    bs_applymask(state, maskb);

    bs_transpose_rev(state);
}

void bs_cipher_rev(word_t state[BLOCK_SIZE], word_t (* rk)[BLOCK_SIZE])
{
    int round;
    bs_transpose(state);


    bs_addroundkey(state,rk[10]);
    for (round = 9; round > 0; round--)
    {
        bs_shiftrows_rev(state);
        bs_apply_sbox_rev(state);
        bs_addroundkey(state,rk[round]);
        bs_mixcolumns_rev(state);
    }
    bs_shiftrows_rev(state);
    bs_apply_sbox_rev(state);
    bs_addroundkey(state,rk[0]);

    bs_transpose_rev(state);
}



