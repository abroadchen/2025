//
// Created by Psy.C on 2025/11/13.
//
/*
*定义深度优先搜索函数，用于生成所有幸运数字
如果x超过inf则返回（剪枝）
如果x不为0，则将其加入向量a中
递归生成以x为前缀，后跟4或7的数字
 *
*定义get函数计算区间交集占总区间的比例
计算[l,r]与[a,b]的交集区间
如果交集为空，返回0
否则返回交集长度占总区间[a,b]长度的比例
 *
 *如果从当前位置开始无法组成k个连续的幸运数字，则跳过
 *x为第i个幸运数字，y为第i+k-1个幸运数字
*l1到r1表示包含x的最大非幸运数字区间
如果i为0，则l1为1，否则为前一个幸运数字+1
 *l2为第i+k-1个幸运数字
*r2表示包含y的最大非幸运数字区间的右端点
如果y是最后一个幸运数字，则r2为inf，否则为下一个幸运数字-1
*计算第一种情况的概率并累加到结果中
即：第一个区间选到[l1,r1]∩[pl,pr]的概率 × 第二个区间选到[l2,r2]∩[vl,vr]的概率
*计算第二种情况的概率并累加到结果中
即：第一个区间选到[l2,r2]∩[pl,pr]的概率 × 第二个区间选到[l1,r1]∩[vl,vr]的概率
*如果r1等于l2，说明有重复计算，需要减去重复部分
减去两个区间都选到r1=l2的概率
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int inf = 1e9;
int pl, pr, vl, vr, k;
vector<int> a;

void dfs(ll x) {
    if (x > inf) return;
    if (x != 0) a.push_back(x);
    dfs(x * 10 + 4);
    dfs(x * 10 + 7);
}

double get(int l, int r, int a, int b) {
    l = max(l, a); r = min(r, b);
    if (l > r) return 0.;
    return (double)(r - l + 1) / (double)(b - a + 1);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> pl >> pr >> vl >> vr >> k;//两个区间端点和k值
    dfs(0);
    sort(a.begin(), a.end());
    int n = a.size();
    double res = 0.;
    for (int i = 0; i < n; ++i) {
        if (i + k - 1 >= n) continue;
        int x = a[i], y = a[i + k - 1],
        l1 = i == 0 ? 1 : a[i - 1] + 1, r1 = a[i],
        l2 = a[i + k - 1],
        r2 = i + k - 1 == n - 1 ? inf : a[i + k] - 1;
        res += get(l1, r1, pl, pr) * get(l2, r2, vl, vr);
        res += get(l2, r2, pl, pr) * get(l1, r1, vl, vr);
        if (r1 == l2)
            res -= get(r1, l2, pl, pr) * get(r1, l2, vl, vr);
    }
    printf("%.10lf\n", res);
    return 0;
}