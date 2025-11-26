//
// Created by Psy.C on 2025/11/26.
//
/*
 *定义结构体node，包含价值v和编号num
 *创建N个vector<node>类型的数组，用于按颜色分组存储节点
*定义cube结构体：颜色c、大小s、编号num
重载<运算符：先按颜色升序，颜色相同时按大小降序
 *
*a[N]: 存储离散化后的颜色值
mi[N]: 记录每种长度下最大价值的颜色索引
si[N]: 记录每种长度下次大价值的颜色索引
mv[N]: 记录每种长度下的最大价值（初始化为0）
sv[N]: 记录每种长度下次大价值（初始化为0）
sum[N]: 记录每种颜色的累计价值（初始化为0
 *
 *读取立方体数量n
 *清空所有vector，确保初始状态为空
*读取每个立方体的颜色和大小
设置编号为i+1（从1开始）
 *
*颜色离散化：提取所有不同的颜色值
k记录不同颜色的数量
*遍历每个立方体
通过二分查找获取颜色在离散化数组中的索引
创建节点并添加到对应颜色的vector中
累计该颜色的总价值
 *
*获取当前颜色vector的大小作为长度
更新该长度下的最大值和次大值：
如果当前总价值大于最大值，则更新最大值和次大值
否则如果大于次大值，则更新次大值
 *
 *初始化结果变量：两个颜色索引、两个长度、最大答案
 *枚举所有可能的长度组合
*情况1：两个相同长度的序列，颜色不同
如果该长度下存在最大值和次大值，且颜色不同
则检查是否能更新最大答案
*情况2：长度为len和len+1的两个序列，颜色不同
检查能否更新最大答案
 *情况3：长度为len的次优序列和长度为len+1的最优序列，颜色不同
 *情况4：长度为len的最优序列和长度为len+1的次优序列，颜色不同
 *
 *输出最大价值和以及两个序列的总长度
*输出具体的立方体编号序列
先输出第二个序列的第一个元素
然后交替输出两个序列的后续元素
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr int N = 1e5+5;
struct node { int v, num; };
vector<node> v[N];
struct cube {
    int c, s, num;
    bool operator<(const cube& o) const {
        if (c == o.c) return s > o.s;
        return c < o.c;
    }
} c[N];

int a[N], mi[N], si[N];
ll mv[N]={}, sv[N]={}, sum[N]={};

int tws(const int x, const int k) {
    int l(0), r(k - 1);
    while (l <= r) {
        const int mid = (l + r) >> 1;
        if (a[mid] == x) return mid;
        if (a[mid] > x) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int main() {
    fast;
    int n; cin>>n;
    for (int i = 0; i <= n; ++i) v[i].clear();
    for (int i = 0; i < n; ++i) {
        cin>>c[i].c>>c[i].s; c[i].num = i + 1;
    }
    sort(c, c+n);
    int k = 0; a[k++] = c[0].c;
    for (int i = 1; i < n; ++i) if (c[i].c != c[i - 1].c) {
        a[k++] = c[i].c;
    }
    for (int i = 0; i < n; ++i) {
        const int idx = tws(c[i].c, k);
        node x{}; x.num = c[i].num; x.v = c[i].s;
        v[idx].push_back(x); sum[idx] += c[i].s;
        const int len = static_cast<int>(v[idx].size());
        if (mv[len] < sum[idx]) {
            sv[len] = mv[len]; si[len] = mi[len];
            mv[len] = sum[idx]; mi[len] = idx;
        } else if (sv[len] < sum[idx]) {
            sv[len] = sum[idx]; si[len] = idx;
        }
    }
    int c1 = 0, c2 = 0, l1 = 0, l2 = 0; ll ans = 0;
    for (int len = 1; len <= n; ++len) {
        if (mv[len] && sv[len]) if (mi[len] != si[len]) {
            if (ans < mv[len] + sv[len]) {
                ans = mv[len] + sv[len];
                c1 = mi[len]; c2 = si[len];
                l1 = len; l2 = len;
            }
        }
        if (mv[len] && mv[len + 1]) if (mi[len] != mi[len + 1]) {
            if (ans < mv[len] + mv[len + 1]) {
                ans = mv[len] + mv[len + 1];
                c1 = mi[len]; c2 = mi[len + 1];
                l1 = len; l2 = len + 1;
            }
        }
        if (sv[len] && mv[len + 1]) if (si[len] != mi[len + 1]) {
            if (ans < sv[len] + mv[len + 1]) {
                ans = sv[len] + mv[len + 1];
                c1 = si[len]; c2 = mi[len + 1];
                l1 = len; l2 = len + 1;
            }
        }
        if (mv[len] && sv[len + 1]) if (mi[len] != si[len + 1]) {
            if (ans < mv[len] + sv[len + 1]) {
                ans = mv[len] + sv[len + 1];
                c1 = mi[len]; c2 = si[len + 1];
                l1 = len; l2 = len + 1;
            }
        }
    }
    cout << ans << '\n' << l1 + l2 << '\n';
    cout << v[c2][0].num;
    for (int i = 0; i < l1; ++i) {
        cout << " " << v[c1][i].num;//输出第一个序列的第i个元素
        if (i + 1 < l2) cout << " " << v[c2][i + 1].num;//输出第二个序列的第(i+1)个元素
    }
    cout << '\n';
    return 0;
}