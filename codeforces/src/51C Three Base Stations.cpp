//
// Created by Psy.C on 2025/10/15.
//
/*
*n：城市数量
v：存储城市位置的整数向量
t：存储无线电塔位置的双精度浮点数向量（最多3个塔）
 *
*cnt：塔的计数器，初始为1
last：第一个城市的位置
ans：临时存储塔位置的向量
在第一个城市位置加上传输范围d处放置第一个塔
 *
*使用贪心算法放置塔：
计算当前塔能覆盖的最大距离：last + 2*d
使用upper_bound找到第一个超出当前塔覆盖范围的城市
如果没有这样的城市，说明所有城市都已被覆盖，跳出循环
否则增加塔的计数
如果需要的塔超过3个，返回false（无法用3个塔覆盖）
在找到的未覆盖城市位置加上传输范围d处放置新塔
 *
 *将计算出的塔位置复制到全局向量t中，返回true表示可以覆盖
 *
*读取城市数量
调整向量大小以适应数据
读取所有城市的位置
按位置对城市进行排序
 *
*使用二分查找寻找最优解：
设置搜索范围从0到1e10（很大的数）
执行500次迭代的二分查找
每次取中点值，检查这个传输范围是否有效
如果有效，记录答案并缩小右边界
如果无效，增大左边界
 *
*以6位小数精度输出最小传输范围
输出塔的位置，将值为0的位置替换为最后一个城市的位置
 *
 *upper_bound 返回第一个大于dis值的元素的迭代器
 *v.begin() 返回指向vector第一个元素的迭代器
*使用计算出的索引访问vector中对应位置的元素
等价于直接通过索引访问元素
v[it - v.begin()] 和 *it 在功能上是等价的
 */
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> v;
vector<double> t;

bool valid(double d) {//是否可以用传输范围为d的最多3个塔来覆盖所有城市
    int cnt(1), last = v[0];
    vector<double> ans;
    ans.push_back(last + d);
    while (true) {
        double dis = last + (2 * d);
        auto it = upper_bound(v.begin(), v.end(), dis);
        if (it == v.end()) break;
        cnt++;
        if (cnt > 3) return false;
        last = v[it - v.begin()];
        ans.push_back(last + d);
    }
    for (int i = 0; i < ans.size(); ++i) t[i] = ans[i];
    return true;
}

void solve() {
    cin >> n; v.resize(n); t.resize(3);
    for (auto& i : v) cin >> i;
    sort(v.begin(), v.end());
    double l(0), r(1e10), ans, mid;
    int x(500);
    while (x--) {
        mid = (l + r) / 2;
        if (valid(mid)) ans = mid, r = mid;
        else l = mid;
    }
    cout << fixed << setprecision(6) << ans << "\n";
    for (auto& i : t) {
        if (i == 0) i = v[n - 1];
        cout << fixed << setprecision(6) << i << " ";
    }
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}