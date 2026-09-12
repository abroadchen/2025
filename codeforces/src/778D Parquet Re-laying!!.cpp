//
// Created by Psy.C on 2026/9/12.
//
/**
每个格子存一个方向字符：

'U'：朝上、'D'：朝下、'L'：朝左、'R'：朝右
每个 2×2 块的合法状态只有两种（形如"两个水平多米诺"或"两个垂直多米诺"）：

check() 判断：
  状态A（垂直合法）:
    U U
    D D
  状态B（水平合法）:
    L L
    R R
递归沿"锯齿"（zigzag）路径向下/向右找，确保路径上的每个 2×2 块都能被转成合法。
每次走到一个块都 rot 一次并记录操作。
（注意 adj 里即使是已合法的块也 rot 一次——这是一种"统一翻转"技巧，配合后续贪心能保证可行。）
把矩阵转置并旋转方向，从而把"m 为奇数"的问题转换为"列数为偶数"的问题（因为算法要求列数 m 为偶数，即按 2 列分块）
若 m 为奇数，先转置（保证列数 m 为偶数可按 2 列分块）。
扫描每两个相邻列 (j, j+1)：若该位置不是 'L'（即需要调整），用 adj 沿锯齿把 s1 和 s2 分别变成"全 L"基准。
把 s1 的操作序列 a 和 s2 的反向序列 b（reverse 后）拼接：a（把 s1 变成基准）+ 反向 b（把基准变回 s2）。
输出总操作数和每个操作（2×2 左上角坐标，转置过则换回
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 60;

//把 2×2 块在"垂直合法态"和"水平合法态"之间切换
void rot(char s[][N], int x, int y) {
    if (s[x][y] == 'U') {
        s[x][y] = s[x+1][y] = 'L';
        s[x][y+1] = s[x+1][y+1] = 'R';
    } else {
        s[x][y] = s[x][y+1] = 'U';
        s[x+1][y] = s[x+1][y+1] = 'D';
    }
}

bool check(char s[][N], int x, int y) {
    if (s[x][y] == s[x][y+1] && s[x][y] == 'U' &&
        s[x+1][y] == s[x+1][y+1] && s[x+1][y] == 'D')
        return true;
    if (s[x][y] == s[x+1][y] && s[x][y] == 'L' &&
        s[x][y+1] == s[x+1][y+1] && s[x][y+1] == 'R')
        return true;
    return false;
}

int n, m;
bool adj(char s[][N], int x, int y, int flag, vector<ii>& a) {
    if (x+1 >= n || y+1 >= m) return false;
    if (check(s, x, y)) {
        rot(s, x, y); a.emplace_back(x, y);
        return true;
    }
    if (!adj(s, x+1-flag, y+flag, flag^1, a))
        return false;
    rot(s, x, y); a.emplace_back(x, y);
    return true;
}

void op(char& c) {
    switch (c) {
        case 'L': c = 'U'; break;
        case 'U': c = 'L'; break;
        case 'R': c = 'D'; break;
        case 'D': c = 'R'; break;
    }
}

int mx;
void change(char s[][N]) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) op(s[i][j]);
    for (int i = 0; i < mx; ++i)
        for (int j = 0; j < i; ++j)
            swap(s[i][j], s[j][i]);
}

char s1[N][N], s2[N][N];
vector<ii> a, b;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s1[i];
    for (int i = 0; i < n; ++i) cin >> s2[i];
    mx = n > m ? n : m;
    bool flag = false;
    if (m&1) {
        change(s1); change(s2); swap(n, m);
        flag = true;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; j += 2) {
            if (s1[i][j] != 'L') {
                if (!adj(s1, i, j, 1, a)) {
                    cout << "-1\n";
                    return 0;
                }
            }
            if (s2[i][j] != 'L') {
                if (!adj(s2, i, j, 1, b)) {
                    cout << "-1\n";
                    return 0;
                }
            }
        }
    ranges::reverse(b);
    a.insert(a.end(), b.begin(), b.end());
    cout << a.size() << '\n';
    for (auto t : a) {
        if (flag) swap(t.first, t.second);
        cout << t.first+1 << ' ' << t.second+1 << '\n';
    }
    return 0;
}