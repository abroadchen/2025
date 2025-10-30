//
// Created by Psy.C on 2025/10/29.
//
/*

[gets stdin]：从标准输入读取一行文本
[split [gets stdin]]：将输入按空格分割成列表
lsort -decreasing -integer -indices [...]：对列表进行降序整数排序，返回排序后的索引列表
-decreasing：降序排列
-integer：按整数值比较
-indices：返回原始元素的索引而不是元素本身

初始化列表t为{0 0 0}，用于存储每个位置的排名

遍历排序后的索引列表s中的每个元素v
incr i：将变量i递增1（初始为0，第一次变为1）
lset t $v [incr i]：将列表t中索引为v的元素设置为当前的i值

输出结果列表t

*/
set s [lsort -decreasing -integer -indices [split [gets stdin]]]
set t {0 0 0}
foreach v $s {lset t $v [incr i]}
puts $t