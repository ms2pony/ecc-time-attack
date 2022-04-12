// fscanf的用法演示
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *filePath = "/home/tam/github/ecc-time-attack/out/temp/message.txt";
    FILE *msg_file;
    char str[100];

    if ((msg_file = fopen(filePath, "r")) == NULL)
    {
        printf("Fail to open file!\n");
        return -1; //获取失败
    };

    fscanf(msg_file, "%[^\n] ", str);
    fscanf(msg_file, "%[^\n] ", str);

    fclose(msg_file);

    //除去str中逗号","前的数据
    // 1.找到","对应下标
    int comma_index = 0;
    while (str[comma_index] != ',')
    {
        comma_index++;
    }
    // 2.开始除去str中逗号","前的数据，包括逗号
    int i = 0;
    while (str[++comma_index])
    {
        str[i++] = str[comma_index];
    }
    str[i] = '\0';

    printf("%s\n", str);
    // printf("%d\n", sizeof(int));
    // printf("%c\n", str[comma_index]);

    //使用atoi将大数字符串转为一系列int类型组成的大数，该大数是大端存放
    //一个int类型数对应8个字符，且应从低位开始遍历
    //低位应该放在高位内存上
    unsigned int bn_bigend[5] = {0}; //存放16字节长度的大数
    // i 对应下标的元素此时为"\0"
    int k = 4;
    char buf[50] = "";
    char *str1;
    for (int j = strlen(str) - 8; j >= 0 || k >= 0; j -= 8)
    {
        if (k > 0)
        {
            //以复制的形式遍历每8个字节
            str1 = str + j;
            strcpy(buf, str1);
            buf[8] = '\0';
            sscanf(buf, "%x", &bn_bigend[k--]);
            // bn_bigend[k] = atoi(buf);
        }
        else
        {
            strcpy(buf, str);
            buf[j + 8] = '\0';
            sscanf(buf, "%x", &bn_bigend[k--]);
        }
    }

    return 0;
}