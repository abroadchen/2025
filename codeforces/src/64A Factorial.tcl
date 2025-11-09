//
// Created by Psy.C on 2025/10/29.
//
/*
从标准输入读取一个数字，存储到变量n中
这是要计算阶乘的数
初始化变量f为1
f用来存储阶乘的结果，初始值为1（因为0! = 1，1! = 1）
开始for循环：
set i 1：初始化循环变量i为1
$i <= $n：循环条件，当i小于等于n时继续循环
incr i：每次循环结束后i自增1

在每次循环中计算阶乘：
expr {$f * $i}：计算f乘以i
set f [...]：将结果重新赋值给f
这样f就累积了1×2×3×...×i的值

*/
set n [gets stdin]
set f 1
for {set i 1} {$i <= $n} {incr i} {
    set f [expr {$f * $i}]
}
puts $f