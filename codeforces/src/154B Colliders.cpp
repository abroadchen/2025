//
// Created by Psy.C on 2025/11/24.
//
/*
*get函数功能：获取数字x的所有质因数
输入：整数x和质数标记数组f
输出：x的所有质因数组成的向量
算法：试除法分解质因数
特殊情况：如果没找到因数（x本身就是质数），则返回x本身
 *
 *n（数字范围）和m（操作次数）
*埃拉托斯特尼筛法生成质数表：
初始化f数组，所有数标记为质数
0和1标记为非质数
从2开始筛选，将每个质数的倍数标记为合数
 *
*a[n+1]：记录每个质因数被哪个设备占用（0表示未占用）
s：记录当前开启的设备集合
 *
*处理m个操作：
读取操作符c（'+'或'-'）和设备编号x
获取x的所有质因数
*开启设备操作：
如果设备已开启，输出提示
*检查冲突：
遍历x的所有质因数
如果某个质因数已被其他设备占用，记录冲突设备编号
 *如果存在冲突，输出冲突信息
*如果没有冲突：
输出成功信息
将设备加入开启集合
标记所有质因数被该设备占用
*关闭设备操作：
如果设备开启，成功关闭并释放质因数
如果设备已关闭，输出提示
 *
*预处理（筛法）：O(n log log n)
单次操作：O(√x + ω(x))，其中ω(x)是x的质因数个数
 */
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

vector<int> get(const int x, vector<bool> f) {
    vector<int> res;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i != 0) continue;
        if (f[i]) res.push_back(i);
        if (f[x/i]) res.push_back(x/i);
    }
    if (res.empty()) res.push_back(x);
    return res;
}

int main() {
    ostream::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<bool> f(n + 1, true); f[0] = false; f[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (!f[i]) continue;
        for (int j = 2 * i; j <= n; j += i) f[j] = false;
    }
    vector<int> a(n + 1, 0);
    set<int> s;
    while (m--) {
        char c; int x; cin >> c >> x;
        vector<int> v = get(x, f);
        if (c == '+') {
            if (s.count(x) > 0) cout << "Already on" << '\n';
            else {
                int cf = 0;
                for (const int i : v) {
                    if (a[i] > 0) { cf = a[i]; break; }
                }
                if (cf) cout << "Conflict with " << cf << '\n';
                else {
                    cout << "Success" << '\n';
                    s.insert(x);
                    for (const int i : v) a[i] = x;
                }
            }
        } else if (c == '-') {
            if (s.count(x) > 0) {
                cout << "Success" << '\n';
                s.erase(x);
                for (const int i : v) a[i] = 0;
            } else cout << "Already off" << '\n';
        }
    }
    return 0;
}