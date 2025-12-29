#include <iostream>
#include <stack>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 1000005
using namespace std;

int main() {
    fast;
    int n, num[N], m, t; cin >> n;
    bool vis[N]={false};//标记某些位置是否为特殊位置
    for (int i = 1; i <= n; ++i) cin >> num[i];//存储数值
    cin >> m;//特殊位置个数
    while (m--) {
        cin >> t;//特殊位置的索引t
        vis[t] = true;
    }
    if (n & 1) { cout << "NO\n"; return 0; }//奇数个元素无法完全配对
    stack<int> s;
    while (!s.empty()) s.pop();//清空栈
    for (int i = n; i >= 1; --i) {
        if (s.empty()) s.push(i);//直接将当前索引i压入栈
        else {
            t = s.top();//获取栈顶元素（索引）
            if (num[t] == num[i]) {//当前元素与栈顶元素值相等
                if (!vis[i] && vis[t]) s.pop();//当前位置不是特殊位置且栈顶位置是特殊位置
                else if (!vis[i] && !vis[t]) {//都不是特殊位置
                    vis[t] = !vis[t];//将栈顶位置标记为特殊位置
                    s.pop();
                } else s.push(i);//当前是特殊位置或栈顶不是特殊位置
            } else s.push(i);//当前元素与栈顶元素不相等
        }
    }
    if (!s.empty()) cout << "NO\n";//还有未匹配的元素
    else {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';//不是第一个元素，输出空格
            if (vis[i]) cout << '-';//位置i是特殊位置
            cout << num[i];
        }
        cout << '\n';
    }
    return 0;
}