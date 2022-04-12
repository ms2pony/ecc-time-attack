/*
固定各种参数，密钥d，签名对r,s，甚至是随机数k 来测试../attack/attack.c采集的数据是否满足等式
s = Mod(k_inv*(Hm+r*d), modulo)
modulo为曲线的n，r和s为ecdsa签名对(r,s)，k_inv为随机数k的逆，d为私钥
 */

/*
测试用例1：k=0xbd8aa9a9e9bdde9ff29189e175b6b2 r=0xd7efe745af09925fe6816b95beb58c50
s=0x4386b6a111c9950c13ff63ccc913521b m=0x00050f1e29fc00e141563c38f0757a53
d=0x4ae8f8b5db094b87a7df7f965f2518f4 modulo = 0xFFFFFFFE0000000075A30D1B9038A115
pubkey=0x03af8a1c7a4e9887d7b85b82e3701fc191 不符合预期
 */

/*
测试用例2：{"k":0x46671a64922b026e2172f210e143982c,"len":127,
"r":0xc28a9fbffa22cfaf799254163d129ec7,"s":0xb240000968ba0eb437fac255728cbc49,"t":886780,
"m":0x0f75ec22c69339b45a88139bb0f45812}
d=0x4ae8f8b5db094b87a7df7f965f2518f4 modulo = 0xFFFFFFFE0000000075A30D1B9038A115
pubkey=0x03af8a1c7a4e9887d7b85b82e3701fc191 不符合预期
 */

/**
 * @file a.c
 */
#include <ecc.h>
#include <stdio.h>
#include <stdlib.h>
#include <convert.h>
#include <convert.h>
#include <str_op.h>

unsigned long long get_cpu_cycle()
{
    unsigned long lo, hi;
    __asm__ __volatile__(
        "rdtsc"
        : "=a"(lo), "=d"(hi));
    return (unsigned long long)hi << 32 | lo;
}

void doSign(uint8_t p_hash[], uint8_t p_privateKey[ECC_BYTES])
{
    /**
     * @brief 签名一次，并测量时间，记录相关信息
     *
     * @require
     */
    char buf[ECC_BYTES * 5];
    unsigned long long t1, t2;
    uint8_t p_signature[ECC_BYTES * 2];

    t1 = get_cpu_cycle();
    ecdsa_sign1(p_privateKey, p_hash, p_signature);
    t2 = get_cpu_cycle();

    // 输出信息到sign.log
    FILE *sign_file = fopen("sign.log", "a"); //"a"，代表追加

    array2Num(buf, p_signature, ECC_BYTES); // r，大端模式
    fprintf(sign_file, "%s,", buf);
    array2Num(buf, p_signature + ECC_BYTES, ECC_BYTES); // s，大端模式
    fprintf(sign_file, "%s,", buf);
    fprintf(sign_file, "%lld,", t2 - t1); //签名时间
    array2Num(buf, p_hash, 16);           // 哈希值，大端模式，16字节，表示截断低位4字节
    fprintf(sign_file, "%s\n", buf);
    fclose(sign_file);
}

void display_num()
{
}

int main()
{
    char buf[ECC_BYTES * 5];

    char *str_pubkey = "03af8a1c7a4e9887d7b85b82e3701fc191";
    char *str_privkey = "4ae8f8b5db094b87a7df7f965f2518f4";
    // 固定公钥和私钥
    uint8_t p_publicKey[ECC_BYTES + 1] = {0};
    uint8_t p_privateKey[ECC_BYTES] = {0};
    str2bin_b(p_publicKey, str_pubkey, ECC_BYTES + 1);
    str2bin_b(p_privateKey, str_privkey, ECC_BYTES);

    //记录公钥和私钥
    FILE *key_file = fopen("key.txt", "w");
    array2Num(buf, p_publicKey, ECC_BYTES + 1);
    fprintf(key_file, "Public Key:\n%s\n", buf);
    array2Num(buf, p_privateKey, ECC_BYTES);
    fprintf(key_file, "Private Key:\n%s\n", buf);
    fclose(key_file);

    char *str_msg = "0x00050f1e29fc00e141563c38f0757a53";
    // char *str_msg = "0x0f75ec22c69339b45a88139bb0f45812";
    uint8_t msgList[50];
    str2bin_b(msgList, str_msg, 16);

    doSign(msgList, p_privateKey);
}