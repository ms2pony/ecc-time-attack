// 测试fscanf的用法
#include "convert.h"
#include "str_op.h"

int test_str2bin_b()
{
    /*
    message.txt的每一行数据形如
    ded9862f35ba800c,294124cee09f86f6ff99a4a523bb82c8347aa73e
    70a5899cf7d4f5aa,65ab433ac20b677ec66904893e4febb9c41ef0
    */
    char *filePath = "/home/tam/github/ecc-time-attack/out/temp/message.txt";
    FILE *msg_file;
    char str[100];
    if ((msg_file = fopen(filePath, "r")) == NULL)
    {
        printf("Fail to open file!\n");
        return 0; //获取失败
    };

    /*
    "%[^\n] "中的%[string]叫做扫描集，"%[^\n]"表示遇到换行停止
    别忘了末尾的空格" "，它的作用能让下一次使用fscanf能够读取文件的下一行
     */
    fscanf(msg_file, "%[^\n] ", str);
    fscanf(msg_file, "%[^\n] ", str);

    fclose(msg_file);

    char div = ',';
    str_modify(str, div, 1);
    printf("%s\n", str);

    uint8_t num_bin[20];
    str2bin_b(num_bin, str, 20);

    for (int i = 0; i < 20; i++)
    {
        printf("%02hhx", num_bin[i]); //最高位前面是0没有关系的！
    }
    printf("\n");
    printf("上面两行字符串除了第2行最高位多了2个0，其他地方都相同，说明测试成功！\n");

    return 1;
}

int main()
{
    test_str2bin_b();
    return 0;
}