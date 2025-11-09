//
// Created by Psy.C on 2025/10/29.
//
/*
定义一个名为isPrime的过程（函数），接受参数x
如果x小于2，返回0（false），因为质数必须大于等于2
从2开始循环到√x：
set i 2：初始化循环变量i为2
$i * $i <= $x：循环条件，i的平方小于等于x
incr i：每次循环i增加1
($x % $i) == 0：检查x是否能被i整除
如果能整除，说明x不是质数，返回0
如果没有找到因子，说明x是质数，返回1（true）

定义一个名为solve的过程
从标准输入读取一个数字，存储到变量n

a：小于等于n的最大质数（初始为0）
b：大于等于n的最小质数（初始为n+100）

循环搜索质数：
起始值：max(2, n-100)，确保至少从2开始
结束值：n+100
这个范围是为了在n附近寻找质数

如果i是质数
如果质数i小于等于n，且比当前记录的a更大，则更新a
如果质数i大于等于n，且比当前记录的b更小，则更新b

*/
proc isPrime {x} {
    if {$x < 2} {
        return 0
    }
    for {set i 2} {$i * $i <= $x} {incr i} {
        if {($x % $i) == 0} {
            return 0
        }
    }
    return 1
}

proc solve {} {
    gets stdin n
    set a 0
    set b [expr {$n + 100}]

    for {set i [expr {max(2,$n - 100)}]} {$i <= $n + 100} {incr i} {
        if {[isPrime $i]} {
            if {$i <= $n} {
                if {$i > $a} {set a $i}
            }
            if {$i >= $n} {
                if {$i < $b} {set b $i}
            }
        }
    }
    puts "$a $b"
}
solve