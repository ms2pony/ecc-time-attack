/**
 * @file a.c
 */
#include <ecc.h>
#include <stdio.h>
#include <stdlib.h>
#include <bignum.h>

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
    ecdsa_sign(p_privateKey, p_hash, p_signature);
    t2 = get_cpu_cycle();

    // 输出信息到sign.log
    FILE *sign_file = fopen("../out/temp/sign.log", "a"); //"a"，代表追加

    array2Num(buf, p_signature, ECC_BYTES); // r
    fprintf(sign_file, "%s,", buf);
    // fprintf(sign_file, "0x");
    // for (int i = ECC_BYTES - 1; i >= 0; i--)
    // {
    //     fprintf(sign_file, "%x", p_signature[i]); // r
    // }
    // fprintf(sign_file, ",");

    array2Num(buf, p_signature + ECC_BYTES, ECC_BYTES); // s
    fprintf(sign_file, "%s,", buf);
    // fprintf(sign_file, "0x");
    // for (int i = ECC_BYTES * 2 - 1; i >= ECC_BYTES; i--)
    // {
    //     fprintf(sign_file, "%x", p_signature[i]); // s
    // }
    // fprintf(sign_file, ",");

    fprintf(sign_file, "%lld,", t2 - t1); //签名时间

    fprintf(sign_file, "0x%s\n", p_hash);
    // fprintf(sign_file, "%s", p_hash);
    // fprintf(sign_file, "\n");

    fclose(sign_file);
}

int getHashMsg(char msgList[][50], char *filePath, int num, int size)
{
    /**
     * @brief Get the Hash Msg data
     *
     * @param msgList output
     * @param filePath input
     * @param num input
     * @param size sha1值的字节数 input
     * @return int
     * @require
     */
    int msgLen = 8; //默认消息为8bytes
    char str[100];  // 100应该不会溢出
    int strMax;
    FILE *msg_file;
    if ((msg_file = fopen(filePath, "r")) == NULL)
    {
        printf("Fail to open file!\n");
        return -1; //获取失败
    };
    strMax = msgLen * 2 + size * 2 + 2; // +2：逗号和结尾终止符

    for (int i = 0; i < num; i++)
    {
        fscanf(msg_file, "%[^\n] ", str); //"%[^\n] "最后一个字符为空格，这个空格不能省略，否则不能无法逐行读取
        for (int j = msgLen * 2 + 1; j < strMax; j++)
        {
            msgList[i][j - msgLen * 2 - 1] = str[j];
        }
    }

    fclose(msg_file);
    return 0; //获取成功
}

int main()
{
    char buf[ECC_BYTES * 5];
    // Create a public/private key pair
    uint8_t p_publicKey[ECC_BYTES + 1] = {0};
    uint8_t p_privateKey[ECC_BYTES] = {0};
    ecc_make_key(p_publicKey, p_privateKey); //生成公钥和私钥

    FILE *key_file = fopen("../out/key.txt", "w");

    array2Num(buf, p_publicKey, ECC_BYTES + 1);
    fprintf(key_file, "Public Key:\n%s\n", buf);

    array2Num(buf, p_privateKey, ECC_BYTES);
    fprintf(key_file, "Private Key:\n%s\n", buf);

    fclose(key_file);

    char msgList[200][50];
    // get hash message
    if (getHashMsg(msgList, "../out/temp/message.txt", 200, 20) == -1)
    {
        printf("Fail to open Hash file!\n");
        exit(1);
    }

    for (int i = 0; i < 8000; i++)
    {
        doSign(msgList[i % 200], p_privateKey);
    }
}