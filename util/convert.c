#include "convert.h"

int array2Num(char *bn, uint8_t a[], int size)
{

    // sprintf(bn, "0x%02x", a[size - 1]);
    sprintf(bn, "0x%02x", a[0]);
    // for (int i = size - 2, count = 0; i >= 0; i--, count += 2)
    for (int i = 1, count = 0; i < size; i++, count += 2)
    {
        sprintf(bn + 4 + count, "%02x", a[i]);
    }
    return 0;
}

void test_array2Num_b()
{
    // limb大端序，字节序为小端
    uint64_t a[] = {0xe09f86f6ff99a4a5, 0x23bb82c8347aa73e};
    uint64_t b[] = {0x62af9116c88ea33c, 0x1722190bb9471119};

    uint8_t *c = (uint8_t *)a;

    char str[60];
    array2Num(str, c, 16);
    printf("%s\n", str);
}

//测试`array2Num`函数
void test_array2Num()
{
    uint64_t a[2] = {0x9238, 0x1234};
    uint8_t *b = (uint8_t *)a;
    int size = 2 * 8;
    char buf[16 * 5];
    array2Num(buf, b, size);
    printf("%s\n", buf);
}

/**
 * @brief 功能与array2Num一样，但输入的数组a为小端模式
 *
 * @param bn
 * @param a
 * @param size
 * @return int
 * @require
 */
int array2Num_l(char *bn, uint8_t a[], int size)
{

    sprintf(bn, "0x%02x", a[size - 1]);
    for (int i = size - 2, count = 0; i >= 0; i--, count += 2)
    {
        sprintf(bn + 4 + count, "%02x", a[i]);
    }
    return 0;
}

void str2bin_b(uint8_t num_bin[], char *str, int num_size)
{
    //使用sscanf将大数字符串转为一系列uint8_t类型组成的大数num_bin，该大数是大端存放
    //一个int类型数对应8个字符，且应从低位开始遍历
    //低位应该放在高位内存上
    // uint8_t num_bin[]; //存放num_size字节长度的大数
    // i 对应下标的元素此时为"\0"
    // int k = 4;
    int index = num_size - 1;
    char buf[50] = "";
    char *str1;
    // for (int j = strlen(str) - 8; j >= 0 || num_size >= 0; j -= 8)
    for (int j = strlen(str) - 2; j >= 0 || index >= 0; j -= 2)
    {
        if (j >= 0)
        {
            //以复制的形式遍历每8个字节
            str1 = str + j;
            strcpy(buf, str1);
            buf[2] = '\0';
            sscanf(buf, "%hhx", &num_bin[index--]);
        }
        else if (j == -1) // str中只剩一个字符了
        {
            strcpy(buf, str);
            buf[j + 2] = '\0';
            sscanf(buf, "%hhx", &num_bin[index--]);
        }
        // str小于num_size的期望大小，不能填满数组num_bin
        else
        { // str中没有字符了，但num_bin还未填满
            num_bin[index--] = 0;
        }
    }
}

int array2Num_l_64(char *bn, uint64_t a[], int size)
{
    sprintf(bn, "0x%016lx", a[size - 1]);
    for (int i = size - 2, count = 0; i >= 0; i--, count += 16)
    {
        sprintf(bn + 18 + count, "%016lx", a[i]);
    }
    return 0;
}

void test_array2Num_l_64()
{
    // limb小端序，字节序为小端
    uint64_t a[] = {0xe09f86f6ff, 0x23bb82c8347aa73e};

    char str[60];
    array2Num_l_64(str, a, 2);
    printf("%s\n", str);
}

// int main()
// {
//     // test_array2Num_b();
//     // test_array2Num();
//     test_array2Num_l_64();
// }