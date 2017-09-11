
#include <string.h>
#include "aes.h"
#include "bs.h"
#include "utils.h"

void aesm_ecb_encrypt(uint8_t * outputb, uint8_t * inputb, uint8_t * maskb, size_t size, uint8_t * key)
{
    word_t input_space[BLOCK_SIZE];
    word_t rk[11][BLOCK_SIZE];

    memset(outputb,0,size);
    word_t * state = (word_t *)outputb;

    bs_expand_key(rk, key);

    int i,j;

    while (size > 0)
    {
        if (size < BS_BLOCK_SIZE/2)
        {
            memset(input_space,0,BS_BLOCK_SIZE);

            for(i = 0; i < (size/WORD_SIZE + size % WORD_SIZE); i += 2)
            {
                memmove(input_space + (i * WORDS_PER_BLOCK), inputb, BLOCK_SIZE/8);
                memmove(input_space + (i * WORDS_PER_BLOCK + WORDS_PER_BLOCK), maskb, BLOCK_SIZE/8);

                maskb += BLOCK_SIZE/8;
                inputb += BLOCK_SIZE/8;

                for (j = 0; j < WORDS_PER_BLOCK; j++)
                {
                    input_space[ i * WORDS_PER_BLOCK + j] ^= input_space[ i * WORDS_PER_BLOCK + WORDS_PER_BLOCK + j];
                }

            }

            bs_cipher(input_space, rk);

            for(i = 0; i < WORD_SIZE; i += 2)
            {
                for (j = 0; j < WORDS_PER_BLOCK; j++)
                {
                    input_space[ i * WORDS_PER_BLOCK + j] ^= input_space[ i * WORDS_PER_BLOCK + WORDS_PER_BLOCK + j];
                }
            }


            memmove(outputb, input_space, size);
            size = 0;
            state += size;
        }
        else
        {
            for(i = 0; i < WORD_SIZE; i += 2)
            {
                memmove(input_space + (i * WORDS_PER_BLOCK), inputb, BLOCK_SIZE/8);
                memmove(input_space + (i * WORDS_PER_BLOCK + WORDS_PER_BLOCK), maskb, BLOCK_SIZE/8);

                maskb += BLOCK_SIZE/8;
                inputb += BLOCK_SIZE/8;

                for (j = 0; j < WORDS_PER_BLOCK; j++)
                {
                    input_space[ i * WORDS_PER_BLOCK + j] ^= input_space[ i * WORDS_PER_BLOCK + WORDS_PER_BLOCK + j];
                }

            }

            bs_cipher(state, rk);
            size -= BS_BLOCK_SIZE;
            state += BS_BLOCK_SIZE;
            for(i = 0; i < WORD_SIZE; i += 2)
            {
                for (j = 0; j < WORDS_PER_BLOCK; j++)
                {
                    input_space[ i * WORDS_PER_BLOCK + j] ^= input_space[ i * WORDS_PER_BLOCK + WORDS_PER_BLOCK + j];
                }
            }
        }

    }
}

void aes_ecb_decrypt(uint8_t * outputb, uint8_t * inputb, size_t size, uint8_t * key)
{
    word_t input_space[BLOCK_SIZE];
    word_t rk[11][BLOCK_SIZE];

    memset(outputb,0,size);
    word_t * state = (word_t *)outputb;
    
    bs_expand_key(rk, key);

    while (size > 0)
    {
        if (size < BS_BLOCK_SIZE)
        {
            memset(input_space,0,BS_BLOCK_SIZE);
            memmove(input_space, inputb, size);
            bs_cipher_rev(input_space,rk);
            memmove(outputb, input_space, size);
            size = 0;
            state += size;
        }
        else
        {
            memmove(state,inputb,BS_BLOCK_SIZE);
            bs_cipher_rev(state,rk);
            size -= BS_BLOCK_SIZE;
            state += BS_BLOCK_SIZE;
        }

    }
}

static void INC_CTR(uint8_t * ctr, uint8_t i)
{
    ctr += BLOCK_SIZE/8 - 1;
    uint8_t n = *(ctr);
    *ctr += i;
    while(*ctr < n)
    {
        ctr--;
        n = *ctr;
        (*ctr)++;
    }
}

void aesm_ctr_encrypt(uint8_t * outputb, uint8_t * inputb, uint8_t * maskb, size_t size, uint8_t * key, uint8_t * iv)
{
    word_t rk[11][BLOCK_SIZE];
    word_t ctr[BLOCK_SIZE];
    uint8_t iv_copy[BLOCK_SIZE/8];
    
    memset(outputb,0,size);
    memset(ctr,0,sizeof(ctr));
    memmove(iv_copy,iv,BLOCK_SIZE/8);

    word_t * state = (word_t *)outputb;
    bs_expand_key(rk, key);

    do
    {
        int chunk = MIN(size, BS_BLOCK_SIZE/2);
        int blocks = chunk / (BLOCK_SIZE/8);
        if (chunk % (BLOCK_SIZE/8))
        {
            blocks++;
        }

        int i,j;
        for (i = 0; i < blocks*2; i += 2)
        {
            memmove(ctr + (i * WORDS_PER_BLOCK), iv_copy, BLOCK_SIZE/8);
            memmove(ctr + (i * WORDS_PER_BLOCK + WORDS_PER_BLOCK), maskb, BLOCK_SIZE/8);
            maskb += BLOCK_SIZE/8;
            for (j = 0; j < WORDS_PER_BLOCK; j++)
            {
                ctr[ i * WORDS_PER_BLOCK + j] ^= ctr[ i * WORDS_PER_BLOCK + WORDS_PER_BLOCK + j];
            }

            INC_CTR(iv_copy,1);
        }

        bs_cipher(ctr,rk);

        for (i = 0; i < blocks*2; i += 2)
        {
            for (j = 0; j < WORDS_PER_BLOCK; j++)
            {
                ctr[ i * WORDS_PER_BLOCK + j] ^= ctr[ i * WORDS_PER_BLOCK + WORDS_PER_BLOCK + j];
            }
        }

        size -= chunk;

        uint8_t * ctr_p = (uint8_t *) ctr;
        for (i = 0; i < blocks; i += 1)
        {
            int j = WORDS_PER_BLOCK;
            while(j--)
            {
                *((word_t*)outputb) = *((word_t*)ctr_p) ^ *((word_t*)inputb);
                outputb += WORD_SIZE/8;
                ctr_p += WORD_SIZE/8;
                inputb += WORD_SIZE/8;
            }
            // skip mask
            ctr_p += BLOCK_SIZE/8;
        }

    }
    while(size);

}




