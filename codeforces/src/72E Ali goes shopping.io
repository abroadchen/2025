//
// Created by Psy.C on 2025/11/3.
//
/*
从标准输入读取一行文本并转换为字符串，赋值给变量a
初始化best变量为整个字符串a，作为当前找到的最佳子串
初始化bestcount变量为0，记录最佳子串的出现次数

外层循环：从索引0到字符串a长度减1，遍历子串的起始位置i
内层循环：从起始位置i+1到字符串a末尾，遍历子串的结束位置j
提取从位置i到位置j的子串，赋值给变量sl
计算子串sl在原字符串a中出现的次数，赋值给变量occ

判断当前子串是否应该成为新的最佳子串，条件如下：
如果出现次数大于当前最佳子串的出现次数，或者
如果出现次数等于当前最佳子串的出现次数，但是：
当前子串长度大于最佳子串长度，或者
当前子串长度等于最佳子串长度，但是当前子串字典序大于最佳子串

如果满足上述条件，更新最佳子串和最佳出现次数
*/
a := File standardInput readLine asString
best := a
bestcount := 0

for(i, 0, a size - 1,
  for(j, i + 1, a size,
    sl := a slice(i, j)
    occ := a occurancesOfSeq(sl)
    if(occ > bestcount or
      (occ == bestcount and
      (sl size > best size or
      (sl size == best size and
      sl > best))),
      best = sl
      bestcount = occ
    )
  )
)
best print

