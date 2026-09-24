//
// Created by Psy.C on 2026/9/23.
//
/**
读入操作数 n（注意：实际操作数写成 2n 次循环，说明总操作次数是 2n）。

变量：

cnt：重排次数（答案）。
tp：下一个要弹出的目标准确值，从 1 开始递增（即期望弹出 1,2,3,...）。
每次读一个操作字符串 s：

"add x"：把 x 压入栈 —— 只是入栈，不影响计数。
"remove"（否则分支）‍：
tp++：期望弹出的目标值 +1（这次要弹出 tp）。
若栈为空：无事发生（目标元素可能已经在之前被处理，或从别处补）。
若栈顶恰好等于 tp：直接弹出，正确，无需重排。
否则（栈顶不是 tp）：说明栈内顺序错了，重排——把整个栈清空（while(!st.empty()) st.pop()），cnt++（重排计一次）。
最终输出重排次数 cnt。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

stack<int> st;
string s;
int main() {
    fast;
    int n; cin >> n;
    int cnt = 0, tp = 0;
    for (int i = 1, x; i <= 2*n; ++i) {
        cin >> s;
        if (s == "add") {
            cin >> x; st.push(x);
        } else {
            tp++;
            if (st.empty()) continue;
            if (st.top() == tp) { st.pop(); continue; }
            while (!st.empty()) st.pop();
            cnt++;
        }
    }
    cout << cnt << '\n';
    return 0;
}