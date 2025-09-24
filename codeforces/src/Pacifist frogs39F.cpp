//
// Created by Psy.C on 2025/9/24.
//
/*
 *n(可能的总距离)，m(青蛙数量)，k(蚊子位置数量)
 *
 *fv，存储每只青蛙的跳跃距离
 *mv，存储k个蚊子的位置
 *
*minn初始化为k+1，用于记录最少能吃到的蚊子数（初始设为最大可能值+1）
frogs vector用于存储最佳青蛙的编号
 *
*外层循环遍历每只青蛙
cnt初始化为0，用于统计当前青蛙能吃到的蚊子数量
内层循环遍历每个蚊子位置
mv[j] % fv[i] == 0判断蚊子位置是否能被青蛙跳跃距离整除（即青蛙能否跳到该位置）
如果能整除，表达式为true(1)，cnt增加1
 *
*如果当前青蛙吃到的蚊子数少于已知最少值：
更新最少值minn
清空frogs向量
将当前青蛙编号(从1开始)加入frogs
如果当前青蛙吃到的蚊子数等于已知最少值：
将当前青蛙编号加入frogs
 *
 *
 *
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {

    long n, m, k; scanf("%ld %ld %ld", &n, &m, &k);
    vector<long> fv(m);
    for (long i = 0; i < m; ++i) scanf("%ld", &fv[i]);
    vector<long> mv(k);
    for (long i = 0; i < k; ++i) scanf("%ld", &mv[i]);

    long minn(k + 1);
    vector<long> frogs;

    for (long i = 0; i < m; ++i) {
        long cnt(0);
        for (long j = 0; j < k; ++j) cnt += (mv[j] % fv[i] == 0);
        if (cnt < minn) {
            minn = cnt;
            frogs.clear();
            frogs.push_back(i + 1);
        } else if (cnt == minn) {
            frogs.push_back(i + 1);
        }
    }

    printf("%ld\n", frogs.size());
    for (long i = 0; i < frogs.size(); ++i) {
        printf("%ld ", frogs[i]);
    }
    return 0;
}