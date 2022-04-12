#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
int str_modify(char *str, char div, int flag)
{
    /*
    除去str中div前的数据
    1.找到对应下标
    2.开始除去str中div前的数据，包括div
     */
    if (flag == 1)
    {
        // 1.找到对应下标
        int index = 0;
        while (str[index] != div)
        {
            index++;
        }
        // 2.开始除去str中div前的数据，包括div
        int i = 0;
        while (str[++index])
        {
            str[i++] = str[index];
        }
        str[i] = '\0';
    }
    else if (flag == 0)
    {
        //除去右边的部分
        // todo
    }
    else
    {
        printf("flag的值非法！\n");
        return 0;
    }

    return 1;
}