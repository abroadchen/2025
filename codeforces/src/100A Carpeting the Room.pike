//
// Created by Psy.C on 2025/11/12.
//

/*
从标准输入读取一行字符串到str
使用sscanf解析字符串，提取三个整数分别赋值给n, k, n1

如果n不能被n1整除（有余数），则s加1
这实际上是计算n除以n1的向上取整结果

*/
int main() {
    int n, k, n1, s;
    string str = Stdio.stdin->gets();
    sscanf(str, "%d%d%d", n, k, n1);
    s = n / n1;
    if (n % n1) s++;
    s *= s;
    if (s <= k) write("YES");
    else write("NO");
    return 0;
}