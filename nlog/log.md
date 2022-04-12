## 实验结论

- 2022-4-12 17:02:51
  对于`secp128r1`曲线，采集 20000 签名样本不足以还原私钥，采集 50000 签名样本成功还原私钥

## ecdsa 代码中需要注意的点

参考[](../util/readme.md)

- `ecc_bytes2native`与`ecc_native2bytes`函数

  - 弄清楚 native 和 bytes 存储大数的形式

    native 是小端模式，limb 的单位为 uint64_t，即 8 字节
    bytes 是大端模式，limb 的单位为 uint8_t，即 1 字节

  - bytes 转 native 即`ecc_bytes2native`执行时，bytes 大小超过是如何处理的：

    sha1 生成的 bytes 类型的数据截断为 16 字节，将低位截断 4 个字节，
    不管 bytes 原来是多少位(sha1 生成的哈希值不一定是 20 字节，也有可能是 18 字节，但就算是 18 字节，低位还是要截断 4 字节)

## 签名过程

1. 生成要签名消息的哈希(sha256)：
   使用命令`echo -n "password" | openssl dgst -sha256`，得到哈希值为：
   `5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8`

2. 使用`ecc_make_key`生成公钥和私钥

## 存储大数的数组转成大数字符串的实现

在实现函数`array2Num`时，有如下问题：

```c
a[2]={0x1,0x23}
printf(key_file, "%x", a[1]);
printf(key_file, "%x", a[0]);
```

a 数组代表的数应该是`0x2301`，但上面的代码输出的大数却是`0x231`，所以这种转换大数字符串的方法不可取
