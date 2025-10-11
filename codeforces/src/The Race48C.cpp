//
// Created by Psy.C on 2025/10/11.
//
/*
*maxl存储下界的最大值，初始为0
minu存储上界的最小值，初始为无穷大
 *
*对每个已知条件计算约束范围：
l = (n+1) * s[i] / i：根据前i个元素中有s[i]个1计算的下界
h = (n+1) * (s[i] + 1.0) / i：根据前i个元素中最多有s[i]+1个1计算的上界
更新全局最大下界maxl和最小上界minu

 *
*计算有效的整数解范围：
minn = floor(maxl + eps)：下界向上取整
maxx = ceil(minu - eps) - 1.0：上界向下取整后再减1
eps用于处理浮点数精度问题
将结果转换为long long类型存储在mi和ma中
 *
 */
#include <ios>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

typedef long long ll;
typedef long double lb;

const lb inf = numeric_limits<lb>::max();
const lb eps = 1e-12L;

lb maxl = 0.0L, minu = inf;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    if (!(cin>>n)) return 0;
    vector<lb> s(n + 1);//索引从1开始使用
    for (int i = 1; i <= n; ++i) {//循环读取n个整数，并转换为long double类型存储在s数组中
        ll x; cin>>x;
        s[i] = (lb)x;
    }

    for (int i = 1; i <= n; ++i) {
        lb l = ((lb)(n + 1)) * s[i] / (lb)i;
        lb h = ((lb)(n + 1)) * (s[i] + 1.0L) / (lb)i;
        if (l > maxl) maxl = l;
        if (h < minu) minu = h;
    }

    lb minn = floorl(maxl + eps), maxx = ceill(minu - eps) - 1.0L;
    ll mi = (ll)minn, ma = (ll)maxx;
    if (mi == ma) cout << "unique\n" << mi << "\n";
    else cout << "not unique\n";
    return 0;
}