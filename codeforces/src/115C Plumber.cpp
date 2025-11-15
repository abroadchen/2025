//
// Created by Psy.C on 2025/11/15.
//
/*
*s：二维字符指针，用于存储输入的网格
x[2][4]：预定义的模式数组，用于棋盘着色验证
第一行：{1, 1, 0, 0} - 可能表示某种颜色模式
第二行：{1, 0, 0, 1} - 可能表示另一种颜色模式
 *
*实现快速幂取模算法：计算 a^p mod mod
ret：结果累乘器，初始为1
当指数p不为0时循环：
如果p的最低位为1，将当前a乘入结果
将a平方（a = a² mod mod）
将p右移一位（p = p/2）
返回最终结果
 *
*pre(-1)：记录前一个有效字符的位置，初始为-1
t(1)：标记当前行是否全为空，初始为true
*遍历当前行的每一列：
如果字符大于等于'0'（即不是空格）：
将字符转换为数值（'1'->0, '2'->1, '3'->2, '4'->3）
如果之前有有效字符（pre != -1）：
检查当前位置与前一位置的距离奇偶性是否符合模式
(j - pre) & 1：两点间距离的奇偶性
x[0][s[i][j]] ^ x[0][s[i][pre]]：对应模式值的异或
如果不符合，将flag置为false
更新pre为当前位置j
标记当前行不全为空(t = 0)
 *如果当前行全为空，计数器cnt加1
 *
*遍历每一列（在flag仍为true的情况下）：
pre(-1)：记录前一个有效字符的行位置
t(1)：标记当前列是否全为空
遍历当前列的每一行：
如果字符值小于等于3（即有效字符）：
进行类似的奇偶性检查，但使用x[1]的模式
更新pre和t
如果当前列全为空，计数器cnt加1
 *
 *两个标记点之间的距离奇偶性必须与其字符类型规定的模式一致
 */
#include <cstdio>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

typedef long long ll;
const int inf = 1e6+3;

char **s;
int x[2][4] = {
    {1, 1, 0, 0},
    {1, 0, 0, 1}
};

int powmod(ll a, int p, int mod) {
    ll ret(1);
    while (p) {
        if (p & 1) ret = ret * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return ret;
}

int main() {
    int n, m, cnt;
    while (scanf("%d%d", &n, &m) == 2) {
        cnt = 0; bool flag = 1;
        s = new char*[n];//动态分配n个字符指针数组
        rep(i,n) {
            int pre(-1); bool t(1);
            s[i] = new char[m + 1];//为第i行分配m+1个字符的空间
            scanf("%s", s[i]);//读入第i行字符串
            rep(j,m) if (s[i][j] >= '0') {
                s[i][j] -= '1';
                if (pre != -1) flag &=
                    ((j - pre) & 1) == (x[0][s[i][j]] ^
                        x[0][s[i][pre]]);
                pre = j;
                t = 0;
            }
            if (t) ++cnt;
        }
        for (int i = 0; i < m && flag; ++i) {
            int pre(-1); bool t(1);
            rep(j,n) if (s[j][i] <= 3) {
                if (pre != -1) flag &=
                    ((j - pre) & 1) == (x[1][s[j][i]] ^
                        x[1][s[pre][i]]);
                pre = j;
                t = 0;
            }
            if (t) ++cnt;
        }
        printf("%d\n", flag ? powmod(2, cnt, inf) : 0);
        rep(i,n) delete s[i];
        delete[] s;
    }
    return 0;
}