## 概述

隐藏数问题在密码学破解中的应用，隐藏数问题可以通过构造数学模型格中的最短向量问题来解决

还原 LCG 中的 seed，LCG 是线性同余发生器（Linear congruential generator），常用作伪随机数发生器

参考：<https://www.anquanke.com/post/id/204846> k NPUCTF2020-babyLCG

## 使用

### 要点

1. `lcg.py`中的 class`LCG`中的`next`函数对应 LCG 生成随机数的公式：
   $s_{i+1}=a * s_{i}+b(\bmod m)$，然后该文件中其他代码作用不大

2. `attack.sage`中的 a,b,m 为已知条件，它们来自于`lcg.py`中，
   然后通过这些已知条件构造合适的格来还原出 seed

### 操作步骤

执行`sage attack.sage`，打印出一个数，这个数是还原出的 seed，如果该数与`lcg.py`中的`seed`相等，
则表明还原成功
