//
// Created by Psy.C on 2025/12/17.
//
/*
 *
*a[i][j]表示从(1,1)到(i,j)矩形区域内'a'字符的个数
使用二维前缀和公式：当前值 = 上 + 左 - 左上 + 当前点贡献
如果s[i][j]是'a'则贡献1，否则贡献0
 *
*定义计数数组cnt[200]（用于统计字符）
双重循环枚举两行i和j（i<j），作为上下边界
 *
*每次外层循环重新初始化cnt数组
初始化右指针r为1
枚举左列l从1到m-1
如果第i行和第j行在位置l的字符不同，跳过
 *
*将位置l的字符计数减1
使用while循环扩展右边界r
条件：当前矩形区域内的'a'字符数不超过lim
二维前缀和查询公式计算矩形[i,l]到[j,r]内'a'的个数
如果i行和j行在位置r字符相同，则对应字符计数加1
 *
 *如果cnt[s[i][l]]大于0，将其加到答案中
 *
 *O(n² × m)：外层两重循环O(n²)，内层滑动窗口O(m)
 *O(n × m)：存储字符串矩阵和前缀和数组
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 450
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, m, lim; cin >> n >> m >> lim;
    char s[N][N];
    for (int i = 1; i <= n; ++i) {
        char t[N]; cin >> t;
        strcpy(s[i] + 1, t);
    }
    int a[N][N];
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + (s[i][j] == 'a' ? 1 : 0);
    }
    ll ans = 0; int cnt[200];
    for (int i = 1; i < n; ++i) for (int j = i + 1; j <= n; ++j) {
        memset(cnt, 0, sizeof(cnt));
        int r = 1;
        for (int l = 1; l < m; ++l) {
            if (s[i][l] != s[j][l]) continue;
            cnt[s[i][l]]--;
            while (r <= m && a[j][r] - a[i-1][r] - a[j][l-1] + a[i-1][l-1] <= lim) {
                if (s[i][r] == s[j][r]) cnt[s[j][r]]++;
                r++;
            }
            if (cnt[s[i][l]] > 0) ans += cnt[s[i][l]];
        }
    }
    cout << ans << '\n';
    return 0;
}