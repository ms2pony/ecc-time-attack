## 概述

本项目用于攻击`secp128r1`的 ecdsa 并还原出私钥

攻击基于隐藏数问题即 hidden number problem（HNP）, 该问题在论文 Hardness of Computing the Most Significant Bits of Secret Keys in Diffie-Hellman and Related Schemes 中首次提出，隐藏数问题可以通过构造数学模型格中的最短向量问题来解决

- ecdsa 源码参考仓库：<https://github.com/jestan/easy-ecc.git>

## 快速使用

1. 执行脚本`util/getHash.sh`得到文件`message.txt`，其中有 200 个随机消息及其 sha1 的哈希值
2. 进入目录`attack`，执行命令`make test`，在当前目录下得到攻击程序`app`，运行它即执行 `./app`

   每次执行`app`都会随机生成一对公钥和私钥，并使用`message.txt`中的哈希值进行一系列签名，
   并将相关数据存入`key.txt`,`sign.log`,`nonces.log`

3. 执行`python3 dataAnalyze.py`, 其使用`sign.log`,`nonces.log`文件的数据产生
   `out/data.log`,`out/small_cycle.txt`,`out/small_nonce.txt`文件

4. 执行`sage attack.sage`，运行完毕后会打印一个值，该值便是还原出的私钥，
   将该值与`key.txt`中的`Private Key`(也就是本次攻击的真实私钥)的值进行对比，
   如果两者相等，说明还原成功
