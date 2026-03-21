//
// Created by Psy.C on 2026/3/21.
//
/**
c[N] 每个节点的颜色
cl:每种颜色计数,mx:最大频率,sum:最大频率颜色的权值和
时间复杂度：O(n log n)，每个节点最多被轻边访问log n次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

int c[N];
ll cl[N], mx, sum;
vector<int> v[N];///邻接表存储树结构
///统计子树信息
void dfs(int pos, int fa, int p) {
    cl[c[pos]]++;//当前节点颜色计数增加
    if (cl[c[pos]] > mx) mx = cl[c[pos]], sum = c[pos];//更新最大频率 更新对应颜色值
    else if (cl[c[pos]] == mx) sum += c[pos];//累加相同频率的颜色值
    for (auto i : v[pos]) {
        if (i == fa) continue;
        if (i != p) dfs(i, pos, p);//遍历轻儿子
    }
}
///移除子树贡献
void pre(int pos, int fa) {
    cl[c[pos]]--;//移除节点颜色计数
    for (auto i : v[pos]) {
        if (i == fa) continue;
        pre(i, pos);//递归清理
    }
}

int mxx[N];
ll ans[N];
///启发式合并
void dfs(int pos, int fa) {
    int p = 0;//重儿子
    for (auto i : v[pos]) {
        if (i == fa) continue;
        if (i != mxx[pos]) {//轻儿子处理
            dfs(i, pos);
            pre(i, pos);//移除轻儿子子树贡献
            sum = 0, mx = 0;//重置统计
        } else p = i;//记录重儿子
    }
    if (p) dfs(p, pos);//先处理重儿子（保留其贡献）
    dfs(pos, fa, p);//统计当前节点子树信息
    ans[pos] = sum;//保存答案
}

int cnt[N];
///找重儿子
void get(int pos, int fa) {
    for (auto i : v[pos]) {
        if (i == fa) continue;
        get(i, pos);
        cnt[pos] += cnt[i];//累计子树大小
        if (cnt[i] > cnt[mxx[pos]])
            mxx[pos] = i;//找最大子树作为重儿子
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i]; cnt[i] = 1;//读取颜色，初始化子树大小
    }
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        v[x].emplace_back(y); v[y].emplace_back(x);
    }
    get(1, 0); dfs(1, 0);
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}