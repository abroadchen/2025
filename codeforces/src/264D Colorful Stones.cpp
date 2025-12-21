//
// Created by Psy.C on 2025/12/21.
//
/*
 *使用 scanf 从标准输入读取两个字符串，分别存储在 a[1] 开始的位置和 b[1] 开始的位置（跳过索引0）
*n 是字符串 a 的长度（从 a+1 开始计算）
m 是字符串 b 的长度（从 b+1 开始计算）
*将 a 中每个字符的ASCII值对3取模
将 b 中每个字符的ASCII值对3取模
这样可以将字符映射到 0, 1, 2 三个值
 *
*第一维和第二维表示相邻字符对的值（0-2）
第三维表示位置，存储到该位置为止特定模式出现的次数
*使用宏 rep 遍历所有可能的字符对组合 (x,y)，范围都是 0-2
对于每个位置 i（从2开始）：
继承前一个位置的计数值
如果 b[i-1]==x 且 b[i]==y，则计数加1
这样 s[x][y][i] 表示在字符串 b 的前 i 个字符中，模式 (x,y) 出现的次数
 *
 *
*a 是我们正在匹配的模式字符串
b 是我们正在搜索的目标字符串
l 和 r 是定义 b 字符串中窗口的左右指针
i 是模式字符串 a 中的当前位置
 *i-1 代表已经处理过的字符
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000003
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;


int main() {
    fast;
    char a[N], b[N]; scanf("%s%s", a + 1, b + 1);
    int n = static_cast<int>(strlen(a + 1)),
    m = static_cast<int>(strlen(b + 1));
    for (int i = 1; i <= n; ++i) a[i] %= 3;
    for (int i = 1; i <= m; ++i) b[i] %= 3;
    int s[3][3][N];
    rep(x,3) rep(y,3) for (int i = 2; i <= m; ++i) {
        s[x][y][i] = s[x][y][i-1];
        if (b[i-1] == x && b[i] == y) ++s[x][y][i];
    }
    int l = 1, r = 1;
    while (r < m && b[r] != a[1]) ++r;//移动 r 直到找到与 a[1] 匹配的字符
    ll ans = r - l + 1;
    for (int i = 2; i <= n; ++i) {
        if (l <= m && a[i-1] == b[l]) ++l;
        if (l > m) break;
        if (r < m) {
            ++r;
            while (r < m && b[r] != a[i]) ++r;//继续移动 r 直到找到与 a[i] 匹配的字符
        }
        if (l > r) continue;
        const int x = static_cast<unsigned char>(a[i - 1]),
        y = static_cast<unsigned char>(a[i]);
        ans += r - l + 1;
        if (x != y) ans -= s[y][x][r] - s[y][x][l-1];//区间 [l,r] 内模式 (y,x) 出现的次数
    }
    cout << ans << '\n';
    return 0;
}