//
// Created by Psy.C on 2025/11/12.
//

/*
辅助函数f用于格式化多项式的项：
c：系数
k：变量X的指数
如果k == 0：返回常数项加换行
否则：
如果系数为1，不显示系数；否则显示"系数*X"
如果指数>1，显示"X^指数"；否则显示"X"

创建大小为n+1的整数数组a，用于存储多项式系数
初始化a[0] = 1（常数项为1）
读取n个数值t
对于每个t，更新系数数组a
这实际上是在计算形如(X+t1)(X+t2)...(X+tn)的展开式
内层循环实现了多项式乘法的系数更新

首先输出最高次项（系数为1）
然后依次输出其他非零项：
根据系数正负决定符号"+"或"-"
使用辅助函数f格式化每项

(X²+5X+6)(X+4) = X³+9X²+26X+24
a = [1, 9, 26, 24]

*/

string f(int c, int k) {
    if (k == 0) return c + "\n";
    return (c == 1 ? "" : c + "*") +
        (k > 1 ? "X^" + k : "X");
}

int read() {
    return (int)Stdio.stdin->gets();
}

int main() {
    int n = read(), i, t, j;
    array(int) a = allocate(n + 1);
    a[0] = 1;
    for (i = 0; i < n; ++i) {
        t = read();
        for (j = i; j >= 0; --j) a[j + 1] += a[j] * t;
    }
    write(f(1, n));
    for (i = 1; i <= n; ++i) if (a[i]) {
        write((a[i] > 0 ? "+" : "-") +
            f(abs(a[i]), n - i));
    }
    return 0;
}