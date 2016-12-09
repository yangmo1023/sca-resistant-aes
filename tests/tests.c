#include <stdint.h>
#include <stdlib.h>
#include "../utils.h"
#include "../aes.h"

#ifdef TEST_FOOTPRINT
#define printf(fmt, ...) (0)
#define fprintf(f,fmt, ...) (0)
#else
#include <stdio.h>
#endif

void aes_ecb_test()
{
    uint8_t key_vector[16] = "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";
    uint8_t pt_vector[16] =  "\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a";
    uint8_t m_vector[512] =  
    {216, 217, 211, 129, 127, 201, 175, 140, 119, 171, 185, 223, 156, 38, 233, 207, 
        135, 212, 139, 41, 160, 234, 97, 195, 156, 223, 4, 52, 244, 167, 4, 167, 
        14, 154, 233, 232, 58, 223, 195, 221, 28, 128, 175, 68, 82, 11, 114, 160, 
        185, 246, 141, 148, 21, 69, 64, 132, 11, 65, 148, 27, 79, 218, 63, 183, 
        133, 1, 16, 19, 239, 0, 198, 134, 208, 29, 88, 28, 164, 40, 245, 33, 
        58, 181, 87, 190, 68, 57, 29, 40, 100, 246, 9, 152, 163, 112, 10, 110, 
        61, 20, 185, 211, 124, 195, 134, 6, 167, 59, 58, 159, 20, 4, 187, 199, 
        113, 103, 152, 115, 177, 123, 175, 6, 109, 191, 250, 252, 183, 208, 56, 246, 
        58, 6, 107, 210, 3, 24, 230, 132, 21, 184, 12, 147, 148, 88, 37, 197, 
        135, 62, 9, 143, 81, 51, 95, 251, 249, 2, 112, 179, 169, 241, 37, 18, 
        2, 65, 161, 97, 111, 2, 153, 225, 45, 187, 75, 69, 133, 170, 81, 198, 
        92, 69, 197, 85, 83, 48, 44, 250, 61, 77, 58, 89, 154, 109, 145, 31, 
        57, 95, 216, 51, 41, 120, 18, 202, 106, 34, 109, 20, 74, 137, 213, 148, 
        173, 164, 56, 86, 212, 83, 133, 16, 248, 202, 240, 192, 240, 114, 168, 94, 
        83, 13, 178, 237, 159, 135, 217, 217, 100, 38, 145, 140, 111, 209, 201, 51, 
        111, 139, 211, 216, 111, 1, 182, 105, 141, 122, 238, 19, 135, 86, 248, 39, 
        243, 2, 148, 246, 2, 244, 138, 29, 43, 198, 67, 45, 49, 124, 38, 43, 
        43, 176, 163, 13, 52, 101, 75, 183, 10, 101, 60, 149, 214, 4, 214, 56, 
        166, 89, 65, 79, 113, 224, 156, 184, 28, 177, 34, 143, 60, 203, 58, 29, 
        216, 46, 107, 223, 119, 113, 43, 95, 154, 44, 163, 186, 143, 100, 223, 193, 
        129, 237, 97, 150, 122, 188, 154, 28, 101, 74, 218, 239, 48, 249, 127, 51, 
        205, 252, 73, 30, 9, 232, 52, 155, 114, 146, 113, 121, 200, 2, 112, 200, 
        208, 245, 167, 142, 32, 217, 53, 124, 229, 96, 201, 198, 20, 197, 59, 84, 
        204, 195, 75, 224, 26, 221, 90, 69, 100, 68, 234, 211, 133, 27, 32, 129, 
        55, 147, 233, 160, 119, 104, 195, 67, 226, 246, 88, 19, 234, 158, 231, 167, 
        184, 236, 35, 16, 161, 197, 79, 254, 115, 157, 51, 22, 192, 25, 173, 73, 
        212, 31, 63, 5, 211, 156, 87, 121, 213, 245, 35, 122, 152, 141, 243, 51, 
        88, 8, 0, 252, 173, 88, 0, 202, 233, 130, 168, 153, 241, 211, 238, 201, 
        102, 255, 119, 95, 12, 117, 13, 67, 45, 16, 170, 143, 28, 241, 234, 27, 
        242, 95, 119, 37, 181, 89, 137, 178, 196, 230, 227, 233, 9, 91, 188, 4, 
        238, 56, 43, 147, 197, 11, 116, 157, 107, 221, 213, 147, 166, 114, 85, 20, 
        57, 19, 199, 240, 71, 69, 149, 138, 79, 206, 163, 218, 209, 62, 255, 147
    };

    uint8_t ct_vector[16] =  "\x3a\xd7\x7b\xb4\x0d\x7a\x36\x60\xa8\x9e\xca\xf3\x24\x66\xef\x97";
    uint8_t output[16];
    uint8_t input[16];
    
    printf("AES ECB\n");

    aesm_ecb_encrypt(output, pt_vector, m_vector, 16,key_vector);


    printf("cipher text: \n");
    dump_hex(output, 16);

    //aes_ecb_decrypt(input, output, 16, key_vector);

    //printf("plain text: \n");
    //dump_hex((uint8_t * )input,16);

    /*if (memcmp(pt_vector, input, 16) != 0)*/
    /*{*/
        /*fprintf(stderr,"error: decrypted ciphertext is not the same as the input plaintext\n");*/
        /*exit(1);*/
    /*}*/
    //else 
        if (memcmp(ct_vector, output, 16) != 0)
    {
        fprintf(stderr,"error: ciphertext is not the same as the test vector\n");
        exit(1);
    }
    else
    {
        printf("ECB passes test vector\n\n");
    }
}

void aes_ctr_test()
{
// Test vector from NIST for 4 input blocks
#define AES_CTR_TESTS_BYTES 64

    uint8_t key_vector[16] =
        "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";

    uint8_t iv_vector[16]  =
        "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff";

    uint8_t pt_vector[AES_CTR_TESTS_BYTES] =
        "\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a"
        "\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51"
        "\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef"
        "\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10"
        ;

    uint8_t ct_vector[AES_CTR_TESTS_BYTES] =
        "\x87\x4d\x61\x91\xb6\x20\xe3\x26\x1b\xef\x68\x64\x99\x0d\xb6\xce"
        "\x98\x06\xf6\x6b\x79\x70\xfd\xff\x86\x17\x18\x7b\xb9\xff\xfd\xff"
        "\x5a\xe4\xdf\x3e\xdb\xd5\xd3\x5e\x5b\x4f\x09\x02\x0d\xb0\x3e\xab"
        "\x1e\x03\x1d\xda\x2f\xbe\x03\xd1\x79\x21\x70\xa0\xf3\x00\x9c\xee"
        ;

    uint8_t output[AES_CTR_TESTS_BYTES];
    uint8_t input[AES_CTR_TESTS_BYTES];

    printf("AES CTR\n");

    aes_ctr_encrypt(output,pt_vector,AES_CTR_TESTS_BYTES,key_vector, iv_vector);

    printf("cipher text: \n");
    dump_hex(output,AES_CTR_TESTS_BYTES);
    
    aes_ctr_decrypt(input,output,AES_CTR_TESTS_BYTES,key_vector, iv_vector);

    printf("plain text: \n");
    dump_hex(input,AES_CTR_TESTS_BYTES);

    if (memcmp(pt_vector, input, AES_CTR_TESTS_BYTES) != 0)
    {
        fprintf(stderr,"error: decrypted ciphertext is not the same as the input plaintext\n");
        exit(1);
    }
    else if (memcmp(ct_vector, output, AES_CTR_TESTS_BYTES) != 0)
    {
        fprintf(stderr,"error: ciphertext is not the same as the test vector\n");
        exit(1);
    }
    else
    {
        printf("CTR passes test vector\n\n");
    }

}


