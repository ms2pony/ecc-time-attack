## 签名过程

生成要签名消息的哈希(sha256)：
使用命令`echo -n "password" | openssl dgst -sha256`，得到哈希值为：
`5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8`

使用`ecc_make_key`生成公钥和私钥，如下：
