//
// Created by Psy.C on 2025/11/8.
//
/*
 *数组长度n，查询数量q，当前答案sum
 *原数组a，答案数组ans，频率数组freq
 *
*定义查询节点结构体Node：
int l, r, idx;: 左端点l，右端点r，查询索引idx
重载<运算符，实现莫队算法的排序规则：
按照左端点所在的块排序
同一块内，奇数块按右端点降序，偶数块按右端点升序
 *
*从总和中减去旧贡献
增加该元素的频率
计算添加后该元素对答案的新贡献
将新贡献加到总和中
 *
 *将查询(l,r,idx)添加到查询列表中
 *通过add/remove操作扩展/收缩当前区间到目标区间[x.l, x.r]
 *时间复杂度为O((n+q)×√n)，比朴素做法更高效
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;

class Solution {
public:
    static int sqrtn;//存储块大小（√n）
    ll n, q, sum;
    vector<ll> a, ans, freq;
    struct Node {
        int l, r, idx;
        bool operator<(const Node& x) const {
            if (l / sqrtn != x.l / sqrtn) return l / sqrtn < x.l / sqrtn;
            return ((l / sqrtn) & 1) ? r > x.r : r < x.r;
        }
    };
    vector<Node> qu;
    void add(int x) {
        ll pre = freq[a[x]] * freq[a[x]] * a[x];
        sum -= pre;
        ++freq[a[x]];
        ll cur = freq[a[x]] * freq[a[x]] * a[x];
        sum += cur;
    }
    void remove(int x) {
        ll pre = freq[a[x]] * freq[a[x]] * a[x];
        sum -= pre;
        --freq[a[x]];
        ll cur = freq[a[x]] * freq[a[x]] * a[x];
        sum += cur;
    }
    Solution(const vector<ll>& x, int cnt) {
        a = x; n = a.size(); q = cnt;
        sqrtn = sqrt(n) + 1;
        freq.assign(1e6+5, 0);
        ans.assign(q, 0);
    }
    void addq(int l, int r, int idx) { qu.push_back({l, r, idx}); }
    vector<ll> proc() {
        sort(qu.begin(), qu.end());
        int curl(0), curr(-1); sum = 0;
        for (auto& x : qu) {
            while (curl > x.l) add(--curl);
            while (curr < x.r) add(++curr);
            while (curl < x.l) remove(curl++);
            while (curr > x.r) remove(curr--);
            ans[x.idx] = sum;
        }
        return ans;
    }
};
int Solution::sqrtn;//静态成员变量的定义

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q; cin >> n >> q;
    vector<ll> v(n), t(n);
    for (auto& it : v) cin >> it;
    Solution x(v, q);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        x.addq(l - 1, r - 1, i);//转换为0索引
    }
    vector<ll> ans = x.proc();
    for (auto& it : ans) cout << it << "\n";
    return 0;
}