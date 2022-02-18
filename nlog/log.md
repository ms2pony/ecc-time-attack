## 签名过程

生成要签名消息的哈希(sha256)：
使用命令`echo -n "password" | openssl dgst -sha256`，得到哈希值为：
`5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8`

使用`ecc_make_key`生成公钥和私钥，如下：

## 存储大数的数组转成大数字符串的实现

如下问题：

```c
a[2]={0x1,0x23}
printf(key_file, "%x", a[1]);
printf(key_file, "%x", a[0]);
```

a 数组代表的数应该是`0x2301`，但上面的代码输出的大数却是`0x231`，所以这种转换大数字符串的方法不可取
