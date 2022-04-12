#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/**
 * @brief 将数组a中存储的大数(limb序为大端)，转成字符串形式的大数
 *
 * @param bn 输出
 * @param a 类型为uint8_t
 * @param size 数组a的大小
 * @return int
 * @require
 */
int array2Num(char *bn, uint8_t a[], int size);

/**
 * @brief 功能与array2Num一样，但输入的数组a为小端模式
 *
 * @param bn
 * @param a 类型为uint8_t
 * @param size
 * @return int
 * @require
 */
int array2Num_l(char *bn, uint8_t a[], int size);

/**
 * @brief 字符串形式的大数转成二进制存储形式存入数组num_bin，num_bin存储方式为limb大端模式
 * 需要指定数组大小
 *
 * @param num_bin 转换后的大数存放在这个数组中
 * @param str 应为16进制，且无前缀0x
 * @param num_size 转换后的大数的limb的个数，单位为uint8_t
 * @require
 */
void str2bin_b(uint8_t num_bin[], char *str, int num_size);

/**
 * @brief 功能与array2Num一样，但输入的数组a为小端模式，limb为64-bit
 *
 * @param bn
 * @param a 类型为uint64_t
 * @param size
 * @return int
 * @require
 */
int array2Num_l_64(char *bn, uint64_t a[], int size);