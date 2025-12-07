//
// Created by Psy.C on 2025/12/7.
//
/*
*n: 数字个数
s[N]: 存储原始数字的数组
res[N]: 存储结果数字的数组
v1, v2, v3: 三个向量，分别存储余数为1、2、0的数字
sum: 所有数字的总和
 *
*将每个数字按模3的结果放入对应的向量中
同时计算所有数字的总和
*对三个向量进行降序排序
对原数组进行升序排序（从索引1到n）
 *
 *如果最小的数字不是0，则无法组成以0结尾的数，输出-1
 *如果总和能被3整除，则所有数字都可以使用，将它们全部复制到结果数组中
*如果总和模3余1：
优先从余数为1的数字中去掉一个最小值
如果没有余数为1的数字，则从余数为2的数字中去掉两个最小值
将剩余数字放入结果数组
*如果总和模3余2：
优先从余数为2的数字中去掉一个最小值
如果没有余数为2的数字，则从余数为1的数字中去掉两个最小值
将剩余数字放入结果数组
*对结果数组进行升序排序
去除前导零并输出结果（至少保留一个数字，即使是0）
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

bool cmp(const int a, const int b){ return a>b; }

int main() {
    fast;
    int n, s[N], res[N]; cin>>n;
    vector<int> v1, v2, v3; v1.clear(); v2.clear(); v3.clear();
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin>>s[i];
        if (s[i] % 3 == 0) v3.push_back(s[i]);
        if (s[i] % 3 == 1) v1.push_back(s[i]);
        if (s[i] % 3 == 2) v2.push_back(s[i]);
        sum += s[i];
    }
    sort(v3.begin(), v3.end(), cmp);
    sort(v1.begin(), v1.end(), cmp);
    sort(v2.begin(), v2.end(), cmp);
    sort(s + 1, s + n + 1);
    if (s[1] != 0) cout << -1 << '\n';
    else {
        int cnt = 0;
        if (sum % 3 == 0) {
            for (int i = n; i >= 1; --i) { cnt++; res[cnt] = s[i]; }
        } else if (sum % 3 == 1) {
            if (!v1.empty()) v1.pop_back();
            else if (v2.size() > 1) { v2.pop_back(); v2.pop_back(); }
            for (const int i : v1) { cnt++; res[cnt] = i; }
            for (const int i : v3) { cnt++; res[cnt] = i; }
            for (const int i : v2) { cnt++; res[cnt] = i; }
        } else if (sum % 3 == 2) {
            if (!v2.empty()) v2.pop_back();
            else if (v1.size() > 1) { v1.pop_back(); v1.pop_back(); }
            for (const int i : v1) { cnt++; res[cnt] = i; }
            for (const int i : v3) { cnt++; res[cnt] = i; }
            for (const int i : v2) { cnt++; res[cnt] = i; }
        }
        sort(res + 1, res + 1 + cnt);
        bool flag = false;
        for (int i = cnt; i >= 1; --i) {
            if (res[i] != 0) flag = true;
            if (flag == 1 || i == 1) cout << res[i];
        }
        cout << '\n';
    }
    return 0;
}