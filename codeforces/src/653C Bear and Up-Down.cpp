//
// Created by Psy.C on 2026/4/7.
//
///时间复杂度：O(n × 问题位置数)，其中问题位置数≤4
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1.5e5+5;

int n, a[N];
bool ok(int id) {
    if (id < 1 || id >= n) return true;
    if (id&1) return a[id] < a[id+1];
    return a[id] > a[id+1];
}

vector<int> v;//有问题的位置
bool check() {
    return ranges::all_of(v, ok);
}

bool flag[N];//哪些位置存在问题
unordered_set<string> st;
int main() {
    fast;
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i)
        if (!ok(i)) {
            flag[i] = flag[i+1] = true;//标记当前和下一个位置有问题
            cnt++;
        }
    if (cnt > 4) { cout << 0; return 0; }//问题位置超过4个
    for (int i = 1; i <= n; ++i)
        if (flag[i]) v.push_back(i);//将所有标记的问题位置加入v
    for (int j = 1; j <= n; ++j)//遍历所有可能的第二个交换位置
        for (int i : v) {//遍历所有问题位置作为第一个交换位置
            if (i == j) continue;//不能自己和自己交换
            swap(a[i], a[j]);
            if (check() && ok(j) && ok(j-1) && ok(i) && ok(i-1)) {
                st.insert(to_string(i) + ' ' + to_string(j));
                st.insert(to_string(j) + ' ' + to_string(i));
            }
            swap(a[i], a[j]);
        }
    cout << st.size()/2;
    return 0;
}