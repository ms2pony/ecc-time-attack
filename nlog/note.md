## 参考

1. <https://blog.csdn.net/weixin_39219503/article/details/103444787> (参考本攻击格的构造的相关推导公式)
2. <https://blog.soreatu.com/posts/intended-solution-to-nhp-in-gxzyctf-2020/> (本项目的攻击成功率分析)

## prerequirement

- 格的相关概念

  - 格是什么
  - 格中的最短向量(SVP)问题

- 隐藏数问题
  - 隐藏数问题如何转化为最短向量(SVP)问题
  - 格中的最短向量(SVP)问题的解决方法
    使用 LLL 算法规约格，得到经过规约后格的基的第一个向量为该基中最短的向量，且该向量也可以近似看做 SVP 的解，
    另外 BKZ 算法与 LLL 算法的作用一样，且效果更好
