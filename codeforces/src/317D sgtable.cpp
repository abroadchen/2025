//
// Created by Psy.C on 2026/1/6.
//

/**
* 遍历位置1到30（对应二进制位0到29）
if (s & 1<<(i-1)): 检查第i-1位是否为1（位置i-1有石子）
for (int j = i; j <= 30; j += i): 从位置i开始，每隔i个位置进行操作
if (s & 1<<(j-1)): 检查位置j-1是否有石子
t -= 1<<(j-1): 从状态t中移除位置j-1的石子（将该位置的1变为0）
vis[get(t)] = true: 标记后继状态t的SG值为可达
*寻找最小的不可达SG值（Mex - minimum excludant）
if (!vis[i]): 如果SG值i不可达
return sg[s] = static_cast<char>(i): 记忆化并返回i
return 0: 如果所有0-30都可达，返回0（实际上不会发生）
 *
*memset(sg, -1, sizeof(sg)): 将sg数组全部初始化为-1（表示未计算）
sg[0] = 0: 空状态的SG值为0
*计算状态(1<<29)-1的SG值，即前29位全为1的状态
(1<<29)-1 = 2^29-1 = 536870911
*循环输出前30个特殊状态的SG值
(1<<i)-1表示前i位全为1的状态
static_cast<int>(sg[...])将char转换为int输出
用逗号分隔输出结果
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e9+1e8;
char sg[N];
int get(const int s) {//计算状态s的SG函数值（Sprague-Grundy函数）
    if (sg[s] != -1) return sg[s];
    bool vis[31] = {};//标记可达的SG值
    for (int i = 1; i <= 30; ++i) if (s & 1<<(i-1)) {
        int t = s;
        for (int j = i; j <= 30; j += i) if (s & 1<<(j-1)) {
            t -= 1<<(j-1);
        }
        vis[get(t)] = true;
    }
    for (int i = 0; i <= 30; ++i) if (!vis[i]) {
        return sg[s] = static_cast<char>(i);
    }
    return 0;
}


int main() {
    fast;
    memset(sg, -1, sizeof(sg)); sg[0] = 0;
    get((1<<29)-1);
    for (int i = 0; i < 30; ++i) cout <<
        static_cast<int>(sg[(1<<i)-1]) << ',';
    return 0;
}