//
// Created by Psy.C on 2025/10/22.
//
/*
*m: 步骤或操作的数量
k: 查询或测试用例的数量
 *
*使用get<索引>(tuple)提取三元组中的元素
检查查询值x是否在区间[a,b]内
如果满足条件，则将c + (x - a)加到sum中
这里的计算公式表示：基础值c加上x相对于区间起点a的偏移量
 *
 */
#include <vector>
#include <ios>
#include <iostream>
using namespace std;

typedef long long ll;
int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<tuple<int, int, int>> steps;
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        steps.emplace_back(a, b, c);
    }
    ll total(0);
    for (int i = 0; i < k; ++i) {
        int x; cin >> x;
        ll sum(0);
        for (auto& s : steps) {
            int a = get<0>(s), b = get<1>(s), c = get<2>(s);
            if (x >= a && x <= b) sum += c + (x - a);
        }
        total += sum;
    }
    cout << total << endl;

    return 0;
}