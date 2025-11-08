//
// Created by Psy.C on 2025/9/11.
//


#include <ios>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    rotate(h.begin(), max_element(h.begin(), h.end()), h.end());
    h.push_back(h[0]);

    vector<int> left(n + 1);
    vector<int> right(n + 1);
    vector<int> same(n + 1, 0);
    stack<int> st;
    st.push(0);
    left[0] = -1;

    for (int i = 1; i < n; i++) {
        while (!st.empty() && h[st.top()] <= h[i]) {
            if (h[st.top()] == h[i]) same[i] = same[st.top()] + 1;
            st.pop();
        }
        if (st.empty()) left[i] = -1;
        else left[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();
    st.push(n);
    right[n] = n;
    for (int i = n - 1; i >= 1; i--) {
        while (!st.empty() && h[st.top()] <= h[i]) st.pop();
        if (st.empty()) right[i] = n + 1;
        else right[i] = st.top();
        st.push(i);
    }

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        if (left[i] != -1) ans++;
        if (right[i] != n + 1) ans++;
        if (left[i] == 0 && right[i] == n) ans--;
        ans += same[i];
    }
    cout << ans << endl;

    return 0;
}