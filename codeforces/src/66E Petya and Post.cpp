//
// Created by Psy.C on 2025/10/30.
//
/*
 *x为0（存储数值），f为1（符号标志），c为当前读取的字符
 *跳过非数字字符，直到遇到数字、负号或文件结束符
 *读取数字字符，转换为数值：每次乘以10并加上当前数字
 *
 *如果是负数，先输出负号，然后取绝对值
 *
 *l为0（数字位数），d为存储各位数字的数组
 *将数字的各位从低位到高位存储在数组d中
 *如果是0，则直接存储0
 *从高位到低位输出数字（ASCII码中'0'是48）
 *
 *遍历数组，计算a[i]-b[i]的前缀和，并记录最小值
 *再次遍历，如果当前最小前缀和>=0，则标记该位置有效，然后更新最小值
 *
 *定义build函数，用于反转数组
 *反转pos和a数组
 *反转b数组（注意范围是n-1）
 *
 *
*现在：mn += b[i] - a[i] （相当于 mn -= (a[i] - b[i])）
实际意义：

这是在模拟"移除第i个元素对前缀和的影响"
相当于将窗口向前滑动，去掉第i个元素的贡献
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
const int N = 100005;
int n, i, pos[N];
ll a[N], b[N];
bool vis[N];
vector<int> ans;

template<typename T>
bool read(T& n) {
    T x(0), f(1); char c = getchar();
    while ((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if (c == EOF) return false;
    if (c == '-') c = getchar(), f = -1;
    while (c >= '0' && c <= '9') x *= 10, x += c - '0', c = getchar();
    n = x * f;
    return true;
}

void write(int n) {
    if (n < 0) putchar('-'), n = -n;
    int l(0), d[20];
    while (n) d[l++] = n % 10, n /= 10;
    if (!l) d[l++] = 0;
    while (l--) putchar(d[l]+48);
}

void solve() {
    ll mn(1e18), cur(0);
    for (i = 1; i <= n; ++i) cur += a[i] - b[i], mn = min(mn, cur);
    for (i = 1; i <= n; ++i) vis[pos[i]] |= (mn >= 0), mn += b[i] - a[i];
}

void build() {
    for (i = 1; i + i <= n; ++i) swap(pos[i], pos[n - i + 1]), swap(a[i], a[n - i + 1]);
    for (i = 1; i + i <= n - 1; ++i) swap(b[i], b[n - i]);
}

int main() {
    while (read(n)) {
        for (i = 1; i <= n; ++i) read(a[i]);
        for (i = 1; i <= n; ++i) read(b[i]), pos[i] = i;
        solve();
        build();
        solve();
        ans.clear();
        for (i = 1; i <= n; ++i) if (vis[i]) ans.push_back(i);//将所有有效位置添加到答案向量中
        write(ans.size()); putchar('\n');//输出答案数量并换行
        for (i = 0; i < ans.size(); ++i) write(ans[i]), putchar(' ');//输出所有有效位置，每个后面跟一个空格
        putchar('\n');
    }
    return 0;
}