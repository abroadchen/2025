//
// Created by Psy.C on 2025/11/30.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 201
#define ii pair<int, int>
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

ii clus[N];
int freq[N], cnt[N];
vector<ii> v;

int main() {
    fast;
    int n, m, num, x; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> num;
        while (num--) {
            cin >> x; --x;
            clus[x] = {i, freq[i]++};
        }
    }
    int free, cur = 0;
    for (int i = 0; i < n; ++i) if (clus[i].first == -1) {
        free = i;
        break;
    }
    for (int i = 0; i < n; ++i) {
        if (clus[i].first == cur && clus[i].second == cnt[cur]) {
            if (++cnt[cur] == freq[cur]) ++cur;
            continue;
        }
        for (int j = i + 1; j <= n - 1; ++j) {
            if (clus[j].first == cur && clus[j].second == cnt[cur]) {
                if (clus[i].first > -1) v.emplace_back(i, free);
                clus[free] = clus[i];
                v.emplace_back(j,i);
                clus[i] = clus[j];
                clus[j].first = -1;
                if (++cnt[cur] == freq[cur]) ++cur;
                free = j;
                break;
            }
        }
    }
    cout << sz(v) << '\n';
    for (int i = 0; i < sz(v); ++i)
        cout << v[i].first + 1 << ' ' << v[i].second + 1 << '\n';
    return 0;
}