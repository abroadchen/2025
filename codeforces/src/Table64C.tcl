//
// Created by Psy.C on 2025/10/29.
//
/*
从标准输入读取一行文本，存储到变量line中
将读取的行按空格分割成列表，存储到变量input中

从分割后的列表中提取三个参数：
n：行数（数组的行维度）
m：列数（数组的列维度）
k：给定的位置索引（一维索引）

计算列号：
($k - 1)：将1基索引转换为0基索引
/ $n：整除n得到列号
这里假设是按列优先存储（column-major order）

计算行号：
($k - 1)：将1基索引转换为0基索引
% $n：取模n得到行号

将行列坐标转换回一维索引（按行优先存储）：
$row * $m：行号乘以列数得到该行之前的元素个数
+ $col：加上列偏移
+ 1：转换为1基索引

输出计算得到的新的索引号

*/
gets stdin line
set input [split $line]
set n [lindex $input 0]
set m [lindex $input 1]
set k [lindex $input 2]

set col [expr {($k - 1) / $n}]
set row [expr {($k - 1) % $n}]

set number [expr {$row * $m + $col + 1}]
puts $number
