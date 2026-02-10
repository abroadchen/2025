//
// Created by Psy.C on 2026/2/10.
//
/**
k：任务数量
n1, n2, n3：三条流水线的容量（机器数量）
t1, t2, t3：各阶段所需时间

调度策略
使用循环分配：第i个任务分配给第(i%n1)、(i%n2)、(i%n3)台机器
每个任务的完成时间是其在各阶段完成时间的最大值

res是第i个任务的最终完成时间
f1[i%n1] + t1 + t2 + t3：从机器1开始的总时间 经过所有阶段
f2[i%n2] + t2 + t3：从机器2开始的总时间 经过后两个阶段
f3[i%n3] + t3：从机器3开始的总时间 只经过最后一个阶段
更新各阶段完成时间
f1[i%n1] = res - t2 - t3：机器1完成该任务的时间
f2[i%n2] = res - t3：机器2完成该任务的时间
f3[i%n3] = res：机器3完成该任务的时间

时间复杂度：O(k)，处理k个任务
空间复杂度：O(n1+n2+n3)，存储各机器的完成时间
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int k, n1, n2, n3, t1, t2, t3;


int main() {
    fast;
    cin >> k >> n1 >> n2 >> n3 >> t1 >> t2 >> t3;
    vector<int> f1(n1, 0), f2(n2, 0), f3(n3, 0);
    int res = 0;
    for (int i = 0; i < k; ++i) {
        res = max({f1[i%n1] + t1 + t2 + t3,
                f2[i%n2] + t2 + t3, f3[i%n3] + t3});
        f1[i%n1] = res - t2 - t3;
        f2[i%n2] = res - t3;
        f3[i%n3] = res;
    }
    cout << res << '\n';
    return 0;
}