#!/usr/bin/bash

# 输出200个随机消息，以及对应sha1值
rm out/temp/message.txt
for((i=1;i<=200;i++));  
do   
message=`openssl rand -hex 8`; # 8字节的随机消息(16进制形式)
str1=$message',';
str2=`echo -n $message | openssl dgst -sha1 | tr -d '(stdin)= '`;
str=$str1$str2
echo $str >> out/temp/message.txt
done  