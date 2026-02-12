//
// Created by Psy.C on 2026/2/12.
//
/**
str[N]：输入字符串
len：模式长度
m：字符串长度
ch[N*20][4]：字典树的转移数组
tot：字典树节点总数
cc[4][4][20]：统计数组，记录字符转移出现次数
tag[N*20]：标记数组，标记字典树节点是否被访问过

从位置pos开始插入子串到字典树
sc = str[pos] - 'A'获取起始字符
遍历从pos开始最多len个字符
c = str[i] - 'A'获取当前字符
在字典树中创建路径
统计从字符sc到字符c长度为i-pos+1的子串数量

如果实际出现次数不等于理论值，说明存在约束
tr[i][j] = k - 1设置转移距离
 */
#include <bits/stdc++.h>
#define ll long long
#define N 100200
using namespace std;

ll ksm(ll b, ll t) {
    ll ret = 1;
    while (t) {
        if (t&1) ret *= b;
        b *= b;
        t >>= 1;
    }
    return ret;
}

struct node {
    ll mat[4][4];
    ll* operator[](const int& o) { return mat[o]; }
    node operator*(const node& o) const {
        node ret{};
        memset(ret.mat, 0x3f, sizeof(ret.mat));
        for (int k = 0; k < 4; ++k)
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    ret[i][j] = min(ret[i][j], mat[i][k]+o.mat[k][j]);
        return ret;
    }
    node operator^(const ll& o) const {
        ll t = o - 1;
        node ret = *this, b = *this;
        while (t) {
            if (t&1) ret = ret * b;
            b = b * b;
            t >>= 1;
        }
        return ret;
    }
} tr;

char str[N];
int len, m, ch[N*20][4], tot, cc[4][4][20];;
bool tag[N*20];
void insert(const int pos) {
    int p = 0;
    const int sc = str[pos] - 'A';
    for (int i = pos; i <= min(pos + len - 1, m); ++i) {
        const int c = str[i] - 'A';
        if (ch[p][c] == 0) ch[p][c] = ++tot;
        p = ch[p][c];
        if (!tag[p]) tag[p] = true, cc[sc][c][i-pos+1]++;
    }
}

ll n;
bool ok(const ll mid) {
    node ret = tr ^ mid;
    bool flag = true;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            flag &= ret[i][j] >= n;
    return flag;
}

int main() {
    scanf("%lld%s", &n, str + 1), m = strlen (str + 1), len = min(11, m + 1);
    for (int i = 1; i <= m; ++i) insert(i);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = len; k >= 2; --k)
                if (cc[i][j][k] != ksm(4, k - 2))
                    tr[i][j] = k - 1;
    ll l = 1, r = n, res = 0;
    while (l <= r) {
        if (const ll mid = (l + r) >> 1; ok(mid)) r = mid - 1, res = mid;
        else l = mid + 1;
    }
    printf("%lld\n", res);
    return 0;
}