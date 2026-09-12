//
// Created by Psy.C on 2026/9/12.
//
/**
每条 q[i] 表示一行表达式：
op = 0：直接给值（二进制串 s）。
op = 1/2/3：q[a] op q[b]，分别是 AND / OR / XOR。
num 运行时存储该表达式在"某一位 x 上的结果"
q[0] 是 ? 变量，其第 x 位值设为 p（0 或 1）。
按物理出现顺序（依赖的子表达式行号更小，因为读入顺序保证 a、b < i？——是的，表达式引用的变量都是先前已定义的行）模拟每一位。
对第 x 位，每个表达式的 num 是 0/1，ans 累加所有行的结果和。
返回"当 ? 第 x 位 = p 时，所有表达式结果之和"
解析每条语句：name := value 或 name := a OP b。
? 占位为第 0 个变量
m 是二进制位宽。对每一位独立决策（因为位之间互不影响）：
c1 = 该位取 0 的结果和，c2 = 取 1 的结果和。
a1（最小化结果）‍：若取 0 的结果 ≤ 取 1 的结果，则该位取 0（c1 <= c2 → '0'，否则 '1'）。
a2（最大化结果）‍：若取 0 ≥ 取 1，则取 0；否则取 1（c1 >= c2 → '0'，否则 '1'）。
== 这两个判断是每一位独立贪心：为了让整体二进制数最小/最大，高位优先、每一位选带来更小/更大结果和的值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5005;

struct node {
    string s;
    int num{}, a{}, b{}, op{};
    node() = default;
    node(string s, int num, int a, int b, int op): s(std::move(s)), num(num), a(a), b(b), op(op) {}
} q[N];

int n;
int get(int x, int p) {
    q[0].num = p;//q[0] 是 '?' 占位（mp["?"] = 0）
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (q[i].op == 0) q[i].num = q[i].s[x] - '0';//直接值取第 x 位
        else {
            int a = q[q[i].a].num, b = q[q[i].b].num;
            if (q[i].op == 1) q[i].num = a&b;
            if (q[i].op == 2) q[i].num = a|b;
            if (q[i].op == 3) q[i].num = a^b;
        }
        ans += q[i].num;//累加所有表达式在第 x 位的结果
    }
    return ans;
}

int m;
map<string, int> mp;
int main() {
    fast;
    cin >> n >> m;
    string s; mp["?"] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> s; mp[s] = i;//变量名 -> 行号
        cin >> s; cin >> s;//":="
        if (isdigit(s[0])) {//直接值
            q[i].op = 0; q[i].s = s;
        } else {//二元运算
            q[i].a = mp[s]; cin >> s;
            if (s[0] == 'A') q[i].op = 1;
            if (s[0] == 'O') q[i].op = 2;
            if (s[0] == 'X') q[i].op = 3;
            cin >> s;
            q[i].b = mp[s];
        }
    }
    string a1, a2;
    for (int i = 0; i < m; ++i) {
        int c1 = get(i, 0), c2 = get(i, 1);//'?' 第 i 位取 0 和取 1 的总结果
        if (c1 <= c2) a1 += '0'; else a1 += '1';
        if (c1 >= c2) a2 += '0'; else a2 += '1';
    }
    cout << a1 << '\n' << a2 << '\n';
    return 0;
}