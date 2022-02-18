#include <ecc.h>
#include <stdio.h>

unsigned long long get_cpu_cycle()
{
    unsigned long lo, hi;
    __asm__ __volatile__(
        "rdtsc"
        : "=a"(lo), "=d"(hi));
    return (unsigned long long)hi << 32 | lo;
}

void doSign()
{
    uint8_t p_publicKey[ECC_BYTES + 1];
    uint8_t p_privateKey[ECC_BYTES];
    ecc_make_key(p_publicKey, p_publicKey); //生成公钥和私钥
}