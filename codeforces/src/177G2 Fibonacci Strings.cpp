//
// Created by Psy.C on 2025/11/30.
//
/*
*k：要查找的目标字符串索引。
m：查询字符串的数量。
str：自定义结构体，保存查询字符串、编号和匹配次数。
s[]：最多可容纳 N 个查询项的数组
 *
*S1, S2：KMP 算法所需的字符数组缓冲区。
fail[]：KMP 中的失配表（即 next 数组）
 *
*利用矩阵快速幂计算后续字符串中某子串的出现次数。
构造初始状态向量 st 和两个转移矩阵 tn1, tn2；
应用矩阵快速幂计算最终状态；
得到答案 s[i].ans = st.v[0][0]
 *
*d1 = c - a - b 的含义：
当我们从 s1 和 s2 构造出 s3 时（s3 = s1 + s2）
新增的匹配次数就是 c - a - b
这是因为原有的匹配来自 s1 和 s2，额外增加的部分就是交叉匹配
d2 = d - b - c 的含义：
当我们从 s2 和 s3 构造出 s4 时（s4 = s2 + s3）
新增的匹配次数就是 d - b - c
 *
*tn1 (对应d1):      tn2 (对应d2):
[ 0  1  0 ]        [ 0  1  0 ]
[ 1  1  0 ]        [ 1  1  0 ]
[ 0 d1  1 ]        [ 0 d2  1 ]
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

typedef long long ll;
constexpr int N = 1e6+5, mod = 1e9+7;

struct Mat {
    static constexpr int N = 3; int v[N][N]{};
    Mat() = default;
    explicit Mat(const int x) {
        memset(v, 0, sizeof(v));
        if (x == 1) rep(i,N) v[i][i] = 1;//单位矩阵
    }
    void set(const int p) {
        v[0][0] = 0, v[0][1] = 1, v[0][2] = 0;
        v[1][0] = 1, v[1][1] = 1, v[1][2] = 0;
        v[2][0] = 0, v[2][1] = p, v[2][2] = 1;
    }
    void print() const {
        for (int i = 0; i < N; ++i, puts(""))
            for (int j = 0; j < N; ++j)
                printf("%3d ", v[i][j]);
        puts("");
    }
    Mat operator*(const Mat x) const {
        Mat res(0);
        rep(i,N) rep(j,N) rep(k,N) {
            res.v[i][j] = static_cast<int>((1ll*v[i][k]*x.v[k][j]+res.v[i][j])%mod);
        }
        return res;
    }
    Mat operator^(ll y) const {//计算当前矩阵的 y 次幂
        Mat x = *this, ans(1);
        while (y) {
            if (y & 1ll) ans = ans * x;
            x = x * x, y >>= 1;
        }
        return ans;
    }
};

ll k; int m;//k（目标序列编号）和 m（查询数量）
struct str { string s; int id{}, ans{}; } s[N];//存储每个查询字符串及其编号和答案
string s1 = "a", s2 = "b", s3 = "ba", s4 = "bab";
bool cmp(const str& a, const str& b) {//先按长度排序，再按字典序排序。
    if (sz(a.s) == sz(b.s)) return a.s < b.s;
    return sz(a.s) < sz(b.s);
}

char S1[N], S2[N]; int fail[N];
int kmp(const string& s1, const string& s2) {//统计模式串在主串中的出现次数
    const int n = sz(s1), m = sz(s2);
    for (int i = 1; i <= n; ++i) S1[i] = s1[i-1];
    for (int i = 1; i <= m; ++i) S2[i] = s2[i-1];
    fail[0] = fail[1] = 0;
    for (int i = 2; i <= m; ++i) {
        int k = fail[i-1];
        while (k && S2[i] != S2[k+1]) k = fail[k];
        if (S2[i] == S2[k+1]) k++;
        fail[i] = k;
    }
    int ans = 0, k = 0;
    for (int i = 1; i <= n; ++i) {
        while (k && S1[i] != S2[k+1]) k = fail[k];
        if (S1[i] == S2[k+1]) k++;
        if (k == m) { ans++; k = fail[k]; }
    }
    return ans;
}

bool cmp2(const str& a, const str& b) { return a.id < b.id; }

int main() {
    fast;
    cin >> k >> m;
    for (int i = 1; i <= m; ++i) { cin >> s[i].s; s[i].id = i; }
    sort(s+1, s+m+1, cmp);
    int cnt = 1;//如果当前生成的字符串长度不足当前查询串，则继续迭代构造新的字符串序列
    for (int i = 1; i <= m; ++i) {
        while (cnt < k && sz(s1) < sz(s[i].s)) {
            s1 = s4 + s3;
            //将所有变量向前移动一位
            swap(s1, s2); swap(s2, s3); swap(s3, s4);
            cnt++;
        }
        //如果已经到达第 k 个字符串，直接用 KMP 统计匹配次数
        if (cnt == k) { s[i].ans = kmp(s1, s[i].s); continue; }
        const int a = kmp(s1, s[i].s), b = kmp(s2, s[i].s), c = kmp(s3, s[i].s), d = kmp(s4, s[i].s);
        const int d1 = c - a - b, d2 = d - b - c;
        Mat st(0), tn1(0), tn2(0);
        st.v[0][0] = a, st.v[0][1] = b, st.v[0][2] = 1;
        tn1.set(d1), tn2.set(d2);
        st = st * ((tn1*tn2)^((k-cnt)/2));
        if ((k-cnt)&1) st = st * tn1;
        s[i].ans = st.v[0][0];
    }
    sort(s+1, s+m+1, cmp2);
    for (int i = 1; i <= m; ++i) cout << s[i].ans << '\n';
    return 0;
}