//
// Created by Psy.C on 2026/1/31.
//
/**
* 定义二维数组a和inv，每个都包含N个vector<int>
a[i][j]存储某种计算结果
inv[i][j]存储a[i][j]的模逆元
 *
 *a[i]和inv[i]的第一个元素设置为1
 *t，等于前一项乘以i再取模
 *j>=2，将额外项加到t上
 *将计算结果t添加到a[i]的末尾
 *计算t的模逆元
 *将模逆元t添加到inv[i]的末尾
 *
 *ans（当前答案）和cir数组（记录各种长度的循环数量）
 *栈顶指针top，长度数组len，辅助循环计数数组cir1，最终结果res
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define mod 1000000007
using namespace std;

inline int ksm(int a, int b) {
    int r = 1;
    while (b) {
        if (b&1) r = static_cast<int>(1ll*r*a%mod);
        a = static_cast<int>(1ll*a*a%mod);
        b >>= 1;
    }
    return r;
}

int n;
vector<int> a[N], inv[N];
inline void init() {
    for (int i = 1; i <= n; ++i) {
        a[i].push_back(1); inv[i].push_back(1);
        for (int j = 1; i*j <= n; ++j) {
            int t = static_cast<int>(1ll * a[i][j-1] * i % mod);
            if (j >= 2) t = (t +
                static_cast<int>(1ll * a[i][j-2] * (j-1) % mod * i % mod)) % mod;
            a[i].push_back(t);
            t = ksm(t, mod - 2);
            inv[i].push_back(t);
        }
    }
}

int ans, cir[N];
inline void get() {
    ans = 1;
    for (int i = 1; i <= n; ++i)
        ans = static_cast<int>(1ll*ans*a[i][cir[i]] % mod);
}

int top, len[N], cir1[N], res;
inline void calc(int d) {//d是当前方案的贡献
    int t = ans;
    for (int i = 1; i <= top; ++i) {
        int l = len[i];//获取第i个元素的长度
        t = static_cast<int>(1ll * t * inv[l][cir[l]] % mod);//除以原来的贡献（乘以其模逆元）
        cir[l]++, cir1[min(l, 3)]++;//长度为l的循环数量加1，同时更新cir1数组（长度不超过3）
        t = static_cast<int>(1ll * t * a[l][cir[l]] % mod);//乘以新的贡献
    }
    //如果存在长度至少为3的循环，将贡献乘以t
    if (cir1[3]) d = static_cast<int>(1ll * d * t % mod);
    res = (res + d) % mod;//将当前方案的贡献加入最终结果
    for (int i = 1; i <= top; ++i) {//恢复原来的状态
        int l = len[i];
        cir[l]--, cir1[min(l, 3)]--;//撤销之前对循环计数的更新
    }
}

int k, chain[N], num[N];//chain数组（链长），num数组（每个组的成员数）
inline void dfs(const int now, const int d) {//now是当前位置，d是当前贡献
    if (now == k) { calc(d); return; }//已经处理完k个元素
    len[++top] = chain[now];//将当前链长加入栈中，栈顶指针增加
    num[top] = 1;//新组的成员数为1
    dfs(now + 1, d);//递归处理下一个元素，贡献不变
    num[top--] = 0;//回溯：将栈顶元素的成员数设为0，栈顶指针减少
    for (int i = 1; i <= top; ++i) {//遍历栈中的所有现有组
        len[i] += chain[now];//将当前链长加到第i组
        num[i]++;//第i组成员数加1
        dfs(now + 1, static_cast<int>(1ll*d*(num[i]-1)%mod));//递归处理下一个元素，贡献变为d*(num[i]-1)
        num[i]--;//回溯：成员数减1
        len[i] -= chain[now];//回溯：长度减去刚才加的值
    }
}

int bz[N], vis[N], p[N];//bz标记数组，vis访问标记，p排列数组
inline void solve() {
    init();
    int tot = 0;
    for (int i = 1; i <= n; ++i) if (!bz[i]) {//遍历所有未被指向的节点
        int x = i, y = 0;//从节点i开始追踪路径直到遇到0，计算路径长度
        while (x) { vis[x] = 1; x = p[x]; ++y; }
        chain[tot] = y; tot++;//将路径长度保存到chain数组
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) {//遍历所有未访问的节点（即循环中的节点）
        int x = i, y = 1;//找到包含节点i的循环，计算循环长度
        while (x) {
            vis[x] = 1;
            if (p[x] == i) break;
            x = p[x];
            y++;
        }
        ++cir[y];//更新对应长度循环的计数
        ++cir1[min(y, 3)];
    }
    get();//计算初始答案
    dfs(0, 1);
}


int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        bz[p[i]] = 1;//标记被指向的节点
    }
    solve();
    cout << res << '\n';
    return 0;
}