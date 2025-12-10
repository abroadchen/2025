//
// Created by Psy.C on 2025/12/10.
//
/*
*pos[M]：存储'1'的位置数组
cnt：'1'的个数计数器
num[N]：存储每行'1'的位置信息的数组
 *
*在num[id]行的'1'位置数组中查找不超过key的最大位置
使用标准二分查找模板
返回找到的位置索引，如果没找到返回-1
 *
*读取第i行字符串到mp[i]
初始化tag为false，cnt为0
遍历该行每个字符，如果为'1'：
设置tag为true（表示该行有'1'）
将位置j存储到num[i].pos数组中
cnt计数器递增
如果该行没有'1'（tag仍为false），设置flag为true
 *如果有任何一行全为'0'，输出-1并结束程序 因为题目要求每行至少有一个'1'
 *
*遍历每一列j作为候选位置：
初始化cnt为0，用于累计该列的总代价
遍历每一行i：
如果该行在列j处已经是'1'，则无需移动，跳过
*使用二分查找找到不超过位置j的最接近的'1'的位置
初始化r为0，用于计算移动距离
 *
*如果找到的位置是该行最后一个'1'：
计算两种移动方案的最小值：
向左移动到该'1'的距离：j - num[i].pos[cur]
向右绕一圈再向左移动的距离：(m-1) - j + (num[i].pos[0] + 1) //该行第一个'1'的位置索引
 *
*如果找到的位置不是最后一个'1'：
计算两种移动方案的最小值：
向左移动到该'1'的距离：j - num[i].pos[cur]
向右移动到下一个'1'的距离：num[i].pos[cur+1] - j
 *
*如果没有找到有效的'1'（cur == -1）：
计算两种移动方案的最小值：
向右绕一圈再向左移动的距离：num[i].pos[0] - j
向左绕一圈再向右移动的距离：(m-1) - num[i].pos[num[i].cnt-1] + (j+1) //num[i].pos[num[i].cnt-1]：该行最后一个'1'的位置索引
 *
 *将计算得到的移动距离r累加到总代价cnt中 更新全局最小代价ans
*预处理：O(n×m)
查询：O(n×m×log(m))
总体：O(n×m×log(m))
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

constexpr int N = 105, M = 10005, inf = 0x3f3f3f3f;
struct node { int pos[M], cnt; } num[N];

int find(const int key, const int id, int l, int r) {
    while (l <= r) {
        const int mid = l + ((r - l) >> 1);
        if (num[id].pos[mid] <= key) l = mid + 1;
        else r = mid - 1;
    }
    if (r >= 0) return r;
    return -1;
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    bool flag = false;//是否有全0行
    char mp[N][M];
    rep(i,n) {
        cin >> mp[i];
        bool tag = false; num[i].cnt = 0;
        rep(j,m) if (mp[i][j] == '1') {
            tag = true;
            num[i].pos[num[i].cnt++] = j;
        }
        if (!tag) flag = true;
    }
    if (flag) { cout << "-1\n"; return 0; }
    int ans = inf;
    rep(j,m) {
        int cnt = 0;
        rep(i,n) {
            if (mp[i][j] == '1') continue;
            const int cur = find(j,i,0,num[i].cnt-1);
            int r = 0;
            if (cur == num[i].cnt - 1 && cur != -1)
                r = min(j - num[i].pos[cur],
                    (m-1) - j + (num[i].pos[0] + 1));
            else if (cur != -1 && cur + 1 < num[i].cnt)
                r = min(j - num[i].pos[cur],
                    num[i].pos[cur+1] - j);
            else
                r = min(num[i].pos[0] - j,
                    (m-1) - num[i].pos[num[i].cnt-1] + (j+1));
            cnt += r;
        }
        ans = min(ans, cnt);
    }
    cout << ans << '\n';
    return 0;
}