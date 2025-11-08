//
// Created by Psy.C on 2025/9/30.
//

#include <vector>
#include <ios>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<int> l(n);
    for (int i = 0; i < n; ++i) cin>>l[i];

    vector<int> p, m, z;//p(正数)、m(负数)、z(零)
    for (int i : l) {
        if (i < 0) m.push_back(i);
        else if (i > 0) p.push_back(i);
        else z.push_back(i);
    }
    sort(m.begin(), m.end());//对负数数组进行升序排序(从小到大)

    vector<int> r;
    if (m.size() % 2) {//奇数个负数：去掉绝对值最小的那个(最接近0的负数)，然后加上所有正数
        r.insert(r.end(), m.begin(), m.end() - 1);
        r.insert(r.end(), p.begin(), p.end());
    } else {//偶数个负数：保留所有负数和正数
        r.insert(r.end(), m.begin(), m.end());
        r.insert(r.end(), p.begin(), p.end());
    }

    if (!r.empty()) {
        for (int i = 0; i < r.size(); ++i) {
            cout << r[i];
            if (i < r.size() - 1) cout << " ";
        }
        cout << endl;
    } else if (!z.empty()) cout << 0 << endl;
    else {
        for (int i = 0; i < m.size(); ++i) {
            cout << m[i];
            if (i < m.size() - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}