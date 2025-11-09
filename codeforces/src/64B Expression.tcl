//
// Created by Psy.C on 2025/10/29.
//
/*

1. gets stdin
从标准输入读取一行文本
返回读取到的字符串
2. expr [...]
expr是Tcl的表达式求值命令
对括号内的内容进行数学表达式计算
将读取到的字符串当作数学表达式来计算
3. puts [...]
输出计算结果到标准输出

*/
puts [expr [gets stdin]]