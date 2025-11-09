//
// Created by Psy.C on 2025/11/8.
//
/*
 *x[N]: 存储每个状态的SG值（Sprague-Grundy值）
 *r[N]: 存储每个状态的某种结果值
 *
 *计算状态n的SG值
 *如果x[n]已经计算过（不等于-1），直接返回
*创建向量v存储子状态的SG值
循环i从2开始，条件是i*(i+1)/2 ≤ n（这是前i个自然数的和）
计算a = n - i*(i+1)/2
如果a不能被i整除，跳过
重新计算a = 1 + a/i
*初始化当前状态的SG值cur为0
对j从a到a+i-1循环：
递归计算状态j的SG值
将所有子状态的SG值进行异或运算
*如果当前SG值为0且r[n]未设置，则设置r[n] = i
将当前SG值加入向量v
*对向量v进行排序
去除重复元素，保留唯一值
 *
*计算mex（minimal excludant）值：
从0开始查找第一个不在v中的非负整数
这就是状态n的SG值
*将计算出的SG值存储在x[n]中
返回r[n]的值
*时间复杂度：O(n²)
空间复杂度：O(n)
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100001;

int x[N], r[N];

int dfs(int n) {
    if (x[n] != -1) return x[n];
    vector<int> v;
    for (int i = 2; i * (i + 1) / 2 <= n; ++i) {
        int a = n - i * (i + 1) / 2;
        if (a % i != 0) continue;
        a = 1 + a / i;
        int cur(0);
        for (int j = a; j < a + i; ++j) {
            dfs(j);
            cur ^= x[j];
        }
        if (cur == 0 && r[n] == -1) r[n] = i;
        v.push_back(cur);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    int res(0);
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == res) res++;
        else break;
    }
    x[n] = res;
    return r[n];
}


int main() {
    int n; scanf("%d",&n);
    for (int i = 0; i <= n; ++i) r[i] = x[i] = -1;
    printf("%d\n",dfs(n));
    return 0;
}