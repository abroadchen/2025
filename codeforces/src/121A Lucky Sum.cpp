//
// Created by Psy.C on 2025/11/17.
//
/*
 *
 *l(区间左端点)、r(区间右端点)、sum(结果和，初始化为0)
 *向量ans，用于保存所有幸运数字
*定义深度优先搜索函数，用于生成所有由4和7组成的幸运数字
如果当前数字超过限制值inf，则返回
将当前数字x加入ans向量中
递归生成以x为前缀，后面分别添加7和4的数字
 *
*遍历所有幸运数字
如果当前幸运数字大于等于区间左端点l：
如果幸运数字大于右端点r，则将当前幸运数字乘以区间剩余长度加到sum中，跳转到标签p
否则将当前幸运数字乘以(当前幸运数字-l+1)加到sum中
更新左端点l为当前幸运数字+1
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll inf = 5e9;
ll l, r, sum(0);
vector<ll> ans;

void dfs(ll x) {
    if (x > inf) return;
    ans.push_back(x);
    dfs(x*10+7);
    dfs(x*10+4);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    dfs(0);
    sort(ans.begin(), ans.end());
    cin >> l >> r;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] >= l) {
            if (ans[i] > r) { sum += ans[i] * (r - l + 1); goto p; }
            sum += ans[i] * (ans[i] - l + 1);
            l = ans[i] + 1;
        }
    }
    p:;
    cout << sum;
    return 0;
}