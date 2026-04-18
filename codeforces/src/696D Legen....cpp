//
// Created by Psy.C on 2026/4/17.
//
/**
str 存储输入字符串
rt 为AC自动机根节点
ch[node][c] 表示节点node通过字符c转移到的节点
val[node] 存储到达节点node时获得的价值
a[i] 存储第i个模式串的价值

原始的 L 需要计算 L-1 次转移（因为从长度1扩展到长度L需要L-1次转移）
所以先执行 L--，将L变为 L-1
然后在矩阵快速幂中使用这个新的L值 base^(L-1)

时间复杂度：O(tl³ log L)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 205;

int tl;///AC自动机中节点总数
struct node {
    ll M[N][N]{};
    node() { memset(M, -1, sizeof(M)); }//不可达状态
    node operator*(const node& o) const {
        node ret;
        for (int i = 0; i <= tl; ++i)
            for (int j = 0; j <= tl; ++j)
                for (int k = 0; k <= tl; ++k)
                    if (M[i][k] >= 0 && o.M[k][j] >= 0)//最值矩阵乘法
                        ret.M[i][j] = max(ret.M[i][j], M[i][k] + o.M[k][j]);
        return ret;
    }
};

char str[N];
int rt, ch[N][26], val[N], a[N];
void insert(int id) {
    int len = strlen(str), tmp = rt;
    for (int i = 0; i < len; ++i) {
        int c = str[i] - 'a';
        if (!ch[tmp][c]) ch[tmp][c] = ++tl;
        tmp = ch[tmp][c];
    }
    val[tmp] += a[id];
}

queue<int> q;
int fail[N];
void get() {
    for (int i = 0; i < 26; ++i) {
        if (ch[rt][i])
            q.push(ch[rt][i]), fail[ch[rt][i]] = rt;
        else ch[rt][i] = rt;
    }
    while (!q.empty()) {
        int top = q.front(); q.pop();
        for (int i = 0; i < 26; ++i) {
            if (!ch[top][i])
                ch[top][i] = ch[fail[top]][i];
            else {
                int u = ch[top][i];
                fail[u] = ch[fail[top]][i];
                val[u] += val[fail[u]];//将失败路径上的所有价值累加
                q.push(u);
            }
        }
    }
}

int n;
ll L;
int main() {
    fast;
    cin >> n >> L;//模式串数量和目标长度
    for (int i = 1; i <= n; ++i) cin >> a[i];//每个模式串的价值
    for (int i = 1; i <= n; ++i)
        cin >> str, insert(i);//插入所有模式串
    get();//构建AC自动机
    node ret, base;
    for (int i = 0; i <= tl; ++i)
        for (int c = 0; c < 26; ++c) {
            int j = ch[i][c];
            ret.M[i][j] = val[j];//状态i通过字符c转移到j时获得的价值
        }
    base = ret; L--;
    for (; L; L>>=1) {//长度为L的字符串的最大价值
        if (L&1) ret = ret*base;
        base = base*base;
    }
    ll ans = 0;
    for (int i = 0; i <= tl; ++i)
        ans = max(ans, ret.M[0][i]);//从空状态开始，经过恰好 L 个字符，到达状态 i 时能获得的最大价值
    cout << ans << '\n';
    return 0;
}