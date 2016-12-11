
#include <string.h>
#include <assert.h>
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

void get_masked_slice(word_t * dst, word_t * src, int bit)
{
    // data
    bs_get_slice(src, dst, bit);
    // mask
    bs_get_slice(src, dst, bit + 1);
}

void expand_key_pipeline(word_t * rk, uint8_t * _key)
{
    // TODO integrate this better
    uint8_t key[KEY_SCHEDULE_SIZE];
    word_t zero[WORDS_PER_BLOCK];
    memmove(key,_key,BLOCK_SIZE/8);
    memset(zero,0,sizeof(zero));
    memset(rk,0,BLOCK_SIZE * WORD_SIZE / 8);

    expand_key(key);

    word_t * rk1 = (word_t *) (key + 16);
    word_t * rk2 = (word_t *) (key + 32);
    word_t * rk3 = (word_t *) (key + 48);
    word_t * rk4 = (word_t *) (key + 64);
    word_t * rk5 = (word_t *) (key + 80);
    word_t * rk6 = (word_t *) (key + 96);
    word_t * rk7 = (word_t *) (key + 112);
    word_t * rk8 = (word_t *) (key + 128);
    word_t * rk9 = (word_t *) (key + 144);
    word_t * rk10 = (word_t *) (key + 160);

    /*bs_add_slice(rk,NULL);*/
    bs_add_slice(rk,rk10);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk9);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk8);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk7);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk6);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk5);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk4);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk3);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk2);
    bs_add_slice(rk,NULL);
    bs_add_slice(rk,rk1);
}

void aesm_ctr_encrypt(uint8_t * outputb, uint8_t * inputb, uint8_t * maskb, size_t size, uint8_t * key, uint8_t * iv)
{
    word_t rk[BLOCK_SIZE];
    word_t iv_copy[WORDS_PER_BLOCK];
    word_t state[BLOCK_SIZE];
    
    memset(outputb,0,size);
    memmove(iv_copy,iv,BLOCK_SIZE/8);

    expand_key_pipeline(rk, key);

    int offset = 0;

    int blocks = size / (BLOCK_SIZE/8);
    memset(state, 0, sizeof(state));
    if (size % (BLOCK_SIZE/8))
    {
        blocks++;
    }

    int i,j = 0;

    // run pipeline
    for (i = 0; i < blocks; i++)
    {

        if (i > (BS_DATA_ROUNDS-1))
        {
            get_masked_slice((word_t*)(outputb + offset), state, 18);
            offset += 16;
        }

        bs_add_slice(state, (word_t*)maskb);

        for (j=0; j < WORDS_PER_BLOCK; j++)
        {
            ((word_t*)maskb)[j] ^= iv_copy[j] ^ ((word_t*)key)[j];
        }
        INC_CTR((uint8_t *)iv_copy,1);

        bs_add_slice(state, (word_t*)maskb);

        maskb += BLOCK_SIZE/8;

        bs_apply_sbox(state);
        bs_shiftrows(state);
        bs_mixcolumns(state);

        bs_addroundkey(state,rk);

    }

    int leftover = MIN(i,BS_DATA_ROUNDS);

    // advance pipeline if it is not full
    for (; i < BS_DATA_ROUNDS; i++)
    {
        bs_add_slice(state, NULL);
        bs_add_slice(state, NULL);

        bs_apply_sbox(state);
        bs_shiftrows(state);
        bs_mixcolumns(state);

        bs_addroundkey(state,rk);
    }

    while(leftover--)
    {
        {
            get_masked_slice((word_t*)(outputb + offset), state, 18);
            offset += 16;
        }

        bs_add_slice(state, NULL);
        bs_add_slice(state, NULL);

        bs_apply_sbox(state);
        bs_shiftrows(state);
        bs_mixcolumns(state);
        bs_addroundkey(state,rk);

    }


    while(offset--)
    {
        outputb[offset] ^= inputb[offset];
    }

}




