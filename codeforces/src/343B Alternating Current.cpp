//
// Created by Psy.C on 2026/1/13.
//

#include <iostream>
#include <stack>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    char s[N]; cin >> s;
    const int n = static_cast<int>(strlen(s));
    stack<char> st;
    for (int i = 0; i < n; ++i) {
        if (st.empty()) {
            st.push(s[i]);//直接压入当前字符
            continue;
        }
        //栈顶字符与当前字符相同
        if (st.top() == s[i]) st.pop(); else {//弹出栈顶（相当于消除了两个相同字符
            st.push(s[i]);
        }
    }
    if (st.empty()) cout << "YES\n"; else cout << "NO\n";
    return 0;
}