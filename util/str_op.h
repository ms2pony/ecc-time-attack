#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/**
 * @brief
 *
 * @param str
 * @param div 用于分割的字符串
 * @param flag 1表示左，除去左边的部分，0表示右，除去右边的部分
 * @return int 返回0表示失败，返回1表示成功
 * @require
 */
int str_modify(char *str, char div, int flag);