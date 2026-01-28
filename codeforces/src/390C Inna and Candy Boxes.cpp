//
// Created by Psy.C on 2026/1/28.
//
/**
* 对每个余数 i (0 到 k-1)，构建前缀和数组
s[i][j] 表示在起始位置模 k 余 i 的情况下，到位置 j 为止满足条件的子串数量
 *
 *因为 k % k = 0，所以 +k 不会影响模 k 的结果
*(y - x) % k：区间 [x, y) 的长度模 k
(y - x + 1) % k：区间 [x, y] 的长度模 k
 *
 *从 O(n) 降低到 O(1) 每次查询（预处理后）
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int k;
char str[N];
bool ok(const int x, const int y) {//区间 [x, y) 中以 y-1 位置结尾的子串是否满足条件
    //区间长度 (y-x) 模 k 等于 0，且末尾字符为 '0'
    if ((y - x + k + 1) % k == 0 && str[y-1] == '0') return true;
    if ((y - x + k + 1) % k != 0 && str[y-1] == '1') return true;
    return false;
}

int get(const int x) {//单个位置 x-1 是否满足特定条件
    if (k == 1) {
        if (str[x - 1] == '0') return 1;
    } else {
        if (str[x - 1] == '1') return 1;
    }
    return 0;
}

int main() {
    fast;
    int s[15][N]={}, n, w;
    cin >> n >> k >> w >> str;
    const int len = static_cast<int>(strlen(str));
    for (int i = 0; i < k; ++i) for (int j = i + 1; j <= len; ++j) {
        s[i][j] = s[i][j-1];//继承前面的累计值
        if (ok(i, j)) s[i][j]++;//如果当前位置满足条件，计数+1
    }
    for (int i = 0, x, y; i < w; ++i) {
        cin >> x >> y;
        const int t = x % k;
        cout << s[t][y] - s[t][x] + get(x) << '\n';
    }
    return 0;
}