//
// Created by Psy.C on 2025/11/3.
//
/*

检查字符串s的第一个字符是否是ASCII码45（即减号"-"）
如果是负数，则输出一个减号"-"

对字符串s执行strip("-0")操作，移除开头的"-"和"0"字符
将结果字符串反转
输出反转后的字符串


*/
s := File standardInput readLine
if(s at(0) == 45, "-" print)
s strip("-0") reverse print
