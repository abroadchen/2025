//
// Created by Psy.C on 2026/9/27.
//
/**
str：当前读入的字符串。
n：目标所需的不同字符种类数。
st：一个 set<char>，用于去重统计字符串里出现了哪些不同字符（set 天然有序且唯一）
while(cin >> str)：持续读入字符串，读到输入流结束（EOF）才停，因此支持多组测试数据。
每轮读入字符串后，再读入整数 n，并把上轮残留的 st 清空。
如果字符串长度本身都小于 n——即使字符串里的字符全部互不相同，也凑不出 n 种，因此输出 impossible
否则：遍历字符串每个字符，插入 st。重复出现的字符在 set 里只保留一份，所以 st.size() = 字符串中不同字符的种类数。
比较目标 n 与已有种类数 st.size()：
若 n <= st.size()：现有不同字符已够 n 种，无需新增，输出 0。
否则：还差 n - st.size() 种，那就需要再补这多个不同字符（因为字符串长度 ≥ n，空间足够），输出这个差值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string str;
int n;
set<char> st;
int main() {
    fast;
    while (cin >> str) {
        cin >> n; st.clear();
        if (str.length() < n) cout << "impossible\n";
        else {
            for (int i = 0; i < str.length(); ++i)
                st.insert(str[i]);
            if (n <= st.size()) cout << "0\n";
            else cout << n-st.size() << '\n';
        }
    }
    return 0;
}