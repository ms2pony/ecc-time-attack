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
    ecdsa_sign(p_privateKey, p_hash, p_signature);
    t2 = get_cpu_cycle();

    // 输出信息到sign.log
    FILE *sign_file = fopen("../out/temp/sign.log", "a"); //"a"，代表追加

    array2Num(buf, p_signature, ECC_BYTES); // r，大端模式
    fprintf(sign_file, "%s,", buf);
    array2Num(buf, p_signature + ECC_BYTES, ECC_BYTES); // s，大端模式
    fprintf(sign_file, "%s,", buf);
    fprintf(sign_file, "%lld,", t2 - t1); //签名时间
    array2Num(buf, p_hash, 16);           // 哈希值，大端模式，16字节，表示截断低位4字节
    fprintf(sign_file, "%s\n", buf);
    fclose(sign_file);
}

int getHashMsg(uint8_t msgList[][50], char *filePath, int num, int size)
{
    /**
     * @brief Get the Hash Msg data
     *
     * @param msgList output 消息哈希值应以大端模式存储在该数组中
     * @param filePath input
     * @param num input
     * @param size 哈希值的大小，单位为字节
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

    char div = ',';
    for (int i = 0; i < num; i++)
    {
        fscanf(msg_file, "%[^\n] ", str); //"%[^\n] "最后一个字符为空格，这个空格不能省略，否则不能无法逐行读取
        str_modify(str, div, 1);
        // printf("%s\n", str);

        str2bin_b(msgList[i], str, 20);
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
    ecc_make_key(p_publicKey, p_privateKey); //生成公钥和私钥，大端模式

    FILE *key_file = fopen("../out/key.txt", "w");

    array2Num(buf, p_publicKey, ECC_BYTES + 1);
    fprintf(key_file, "Public Key:\n%s\n", buf);

    array2Num(buf, p_privateKey, ECC_BYTES);
    fprintf(key_file, "Private Key:\n%s\n", buf);

    fclose(key_file);

    uint8_t msgList[200][50];
    // get hash message
    if (getHashMsg(msgList, "../out/temp/message.txt", 200, 20) == -1)
    {
        printf("Fail to open Hash file!\n");
        exit(1);
    }

    for (int i = 0; i < 50000; i++)
    {
        doSign(msgList[i % 200], p_privateKey);
    }
}