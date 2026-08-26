//
// Created by Psy.C on 2026/8/26.
//
/**
- constexpr int N = 150 ：字符ASCII码范围上限（ASCII码最大为127，150足够覆盖所有可打印字符）。
- constexpr int M = 1500 ：映射对数量上限（字符串长度最大为1500，对应最多1500个映射对）。
- string a, b ：存储输入的两个等长字符串，需逐字符构建映射。
- int v[N] ： 双向映射表 ，核心逻辑：
- 下标为原字符的ASCII码，值为映射目标字符的ASCII码。
- 初始值为 0 （ASCII码0是不可打印字符，用 0 表示「未映射」）。
- 通过双向赋值（ v[a] = b, v[b] = a ）保证双射。
- int w[M] ：存储需要输出的映射对的「原字符」（仅存储非恒等映射的原字符，即 a[i]≠b[i] 的情况）。
- int cnt ：统计非恒等映射对的数量，作为输出的第一行

当前字符对均未映射
- 条件判断 ： v[a[i]] == 0 && v[b[i]] == 0
  - 检查当前位置的两个字符 a[i] 和 b[i] 是否都未建立映射（值为0）。
- 建立双向映射 ： v[a[i]] = b[i]; v[b[i]] = a[i];
  - 同时赋值原→像、像→原，保证双射（避免 a→c 和 b→c 的冲突）。
- 记录非恒等映射 ： if (a[i] != b[i]) w[++cnt] = a[i];
  - 若 a[i] 和 b[i] 不同，将原字符存入 w 数组（恒等映射 a→a 无需输出）。
  - ++cnt ：先递增计数，再存入 w[cnt] 。
- continue; ：跳过后续检查，处理下一个字符对
当前字符对已有映射，检查是否冲突
- 冲突条件 ： v[a[i]] != b[i] || v[b[i]] != a[i]
  - v[a[i]] != b[i] ：原字符 a[i] 的映射目标不是 b[i] （破坏单射）。
  - v[b[i]] != a[i] ：像字符 b[i] 的原像不是 a[i] （破坏满射）。
- 冲突处理 ：输出 -1 并立即结束程序，说明无法构成合法双射

- 输出映射对数量 ： cout << cnt << '\n';
- 第一行输出非恒等映射对的数量 cnt 。
- 遍历输出每个映射对 ：
- x = w[i]; ：取第 i 个映射对的原字符（从 w 数组中读取）。
- y = v[x]; ：通过映射表获取原字符 x 的像字符 y 。
- cout << x << ' ' << y << '\n'; ：输出原字符和像字符，用空格分隔，每个映射对占一行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 150, M = 1500;
string a, b;
int v[N], w[M], cnt;
int main() {
    fast;
    cin >> a >> b;
    for (int i = 0; i < a.size(); ++i) {
        if (v[a[i]] == 0 && v[b[i]] == 0) {
            v[a[i]] = b[i]; v[b[i]] = a[i];
            if (a[i] != b[i]) w[++cnt] = a[i];
            continue;
        }
        if (v[a[i]] != b[i] || v[b[i]] != a[i]) {
            cout << "-1";
            return 0;
        }
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i) {
        char x, y;
        x = w[i]; y = v[x];
        cout << x << ' ' << y << '\n';
    }
    return 0;
}