//
// Created by Psy.C on 2025/11/30.
//
/*
*N = 2e5+5：哈希表大小常量
h：哈希表大小（模数）
m：探测步长参数
n：操作数量
cnt：冲突探测次数计数器
ht[N]：布尔数组，标记哈希表位置是否被占用
num：映射容器，存储ID到哈希位置的映射关系
 *
*读入原始哈希值hsh
设置初始位置t = hsh
如果位置已被占用，使用二次探测法寻找下一个位置：
探测公式：t = (hsh + i * m) % h
每次探测增加计数器cnt
递增探测次数i
找到空位置后，记录ID到位置的映射
标记该位置为已占用
 *
*通过num[id]找到该ID对应的哈希位置
将该位置标记为未占用（释放空间）
 *
*时间复杂度：单次操作最坏O(h)，平均情况下较好
空间复杂度：O(h)
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;
int h, m, n, cnt;
bool ht[N];
map<int,int> num;

int main() {
    fast;
    cin >> h >> m >> n;
    while (n--) {
        char op; int id; cin >> op >> id;
        if (op == '+') {
            int hsh; cin >> hsh;
            int t = hsh, i = 1;
            while (ht[t]) {
                t = (hsh + i * m) % h;
                cnt++;
                i++;
            }
            num[id] = t;
            ht[t] = true;
        } else ht[num[id]] = false;
    }
    cout << cnt;
    return 0;
}