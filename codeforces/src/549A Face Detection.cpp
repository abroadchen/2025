//
// Created by Psy.C on 2026/3/9.
//
/**
for(int i=0;i<n;i++)
{
    getchar();
    for(int j=0;j<m;j++)
    {
        scanf("%c",&mp[i][j]);
    }
}

遍历矩阵的每个位置
如果当前位置是'f', 'a', 'c', 'e'之一
将当前字符标记为出现过
将左邻居a[i][j-1]标记为出现过
将下邻居a[i+1][j]标记为出现过
将左下邻居a[i+1][j-1]标记为出现过
检查是否四个目标字符'f', 'a', 'c', 'e'都出现了

1. 键值范围较小且连续
2. 需要频繁随机访问
3. 对性能要求极高
1. 键值范围很大或不连续
2. 键值类型复杂
3. 数据稀疏
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1001;
int n, m;
char a[N][N];
map<char, int> mp;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < m - 1; ++j) {
            if (a[i][j] == 'f' || a[i][j] == 'a' ||
                a[i][j] == 'c' || a[i][j] == 'e') {
                mp[a[i][j]] = 1;
                mp[a[i][j-1]] = 1;
                mp[a[i+1][j]] = 1;
                mp[a[i+1][j-1]] = 1;
                if (mp['f'] == 1 && mp['a'] == 1 &&
                    mp['c'] == 1 && mp['e'] == 1) cnt++;
                mp.clear();
            }
        }
    cout << cnt << '\n';
    return 0;
}