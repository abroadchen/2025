//
// Created by Psy.C on 2025/9/20.
//
/*
 *每个pair的第一个元素表示位置，第二个元素表示速度相关参数
 *
*对events向量按照pair的第一个元素（位置）进行排序
如果第一个元素相同，则按第二个元素排序
 *
 *
*检查相邻的两个事件是否完全相同（位置和参数都相同）
如果找到相同的事件，将mutual设为1（true）并跳出循环
 *
 *
 *
 *
 *
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

    long n(0); scanf("%ld", &n);
    vector<pair<long, long>> events;

    for (long i = 0; i < n; ++i) {
        long pos(0), spit(0); scanf("%ld %ld", &pos, &spit);
        if (spit < 0) { spit *= -1; pos -= spit; }
        events.push_back(pair<long, long>(pos, spit));
    }
    sort(events.begin(), events.end());

    bool mutual(0);
    for (long i = 0; i < n - 1; ++i) {
        if (events[i].first == events[i + 1].first && events[i].second == events[i + 1].second) {
            mutual = 1;
            break;
        }
    }

    if (mutual) puts("YES");
    else puts("NO");

    return 0;
}