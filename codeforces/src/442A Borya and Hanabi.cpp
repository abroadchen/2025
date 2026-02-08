//
// Created by Psy.C on 2026/2/8.
//
/**
n: 输入数据的数量
a[N]: 存储每个位置的状态
x[N]: 存储颜色信息
y[N]: 存储数字信息
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 150
using namespace std;

int get_id(const char ch) {//颜色字符映射为数字
    if (ch == 'R') return 1;
    if (ch == 'G') return 2;
    if (ch == 'B') return 3;
    if (ch == 'Y') return 4;
    if (ch == 'W') return 5;
    return 0;
}

int get1(int x) {//x的二进制表示中1的个数
    int cnt = 0;
    while (x) { cnt += x&1, x >>= 1; }
    return cnt;
}

int n, a[N], x[N], y[N];
bool ok(const int st) {//st是一个10位的掩码（前5位表示颜色，后5位表示数字）
    for (int i = 0; i < n; ++i) {
        a[i] = 0;//初始化状态
        a[i] |= 1<<(x[i]-1)&st;//设置颜色位（前5位，代表RGBYW）
        a[i] |= 1<<(y[i]-1+5)&st;//设置数字位（后5位，代表1-5）
        for (int j = 0; j < i; ++j)//检查是否有重复
            //状态相同但原始数据不同，则冲突
            if (a[i] == a[j] && (x[i] != x[j] || y[i] != y[j]))
                return false;
    }
    return true;
}


int main() {
    fast;
    string str;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> str;
        x[i] = get_id(str[0]);//颜色字符
        y[i] = str[1] - '0';//数字字符转为整数
    }
    int ans = 10;//最大可能值
    for (int i = 0; i < 1<<10; ++i) {//枚举所有10位掩码（0到1023）
        const int n1 = get1(i);//当前掩码中1的个数
        if (n1 >= ans) continue;
        if (ok(i)) ans = n1;
    }
    cout << ans << '\n';
    return 0;
}