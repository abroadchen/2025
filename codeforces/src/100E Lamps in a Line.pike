//
// Created by Psy.C on 2025/11/12.
//

/*
第一次调用：读取但丢弃第一行输入
第二次调用：读取第二行，按空格分割成字符串数组a
第三次调用：读取但丢弃第三行输入
第四次调用：读取第四行，按空格分割成字符串数组b

声明一个映射（类似哈希表）c，键和值都是整数
遍历数组b中的每个字符串i：
将字符串i转换为整数作为键
对应的值递增1
这实际上是在统计每个数字在数组b中出现的次数

遍历映射c，i是键（数字），j是值（出现次数）
如果出现次数是偶数，跳过当前迭代
如果出现次数是奇数：
从索引i-1开始（因为数组索引从0开始）
以步长i遍历数组a
切换对应位置元素的状态："on"↔"off"

使用*操作符将数组a的元素用空格连接成字符串并输出

读取两组数据（跳过第一行和第三行）
第二行是初始开关状态数组（"on"或"off"）
第四行是数字序列
统计每个数字出现的次数
对于出现奇数次的数字，以该数字为间隔切换开关状态
输出最终的开关状态

*/

string read() {
    return Stdio.stdin->gets();
}

int main() {
    read();
    array(string) a = read() / " ";
    read();
    array(string) b = read() / " ";
    mapping(int:int) c = ([]);
    foreach (b, string i) ++c[(int)i];
    foreach (c; int i; int j) {
        if (j % 2 == 0) continue;
        for (int k = i - 1; k < sizeof(a); k += i) {
            a[k] = a[k] == "on" ? "off" : "on";
        }
    }
    write(a * " ");
    return 0;
}