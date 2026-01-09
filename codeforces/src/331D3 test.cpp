//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#include <algorithm>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr  int MAX = 2e5 + 5;
constexpr  int MAXX = 51;
constexpr  ll INF = 1e15 + 5;
typedef multimap <ll, ll> MP;
typedef MP::iterator IT;

struct N
{
  ll sx{}, sy{}, tx{}, ty{}, dx = 0, dy = 0;
} a[MAX];

bool cmpx0(const ll x, const ll y) { return min(a[x].sx, a[x].tx) == min(a[y].sx, a[y].tx) ? x > y : min(a[x].sx, a[x].tx) > min(a[y].sx, a[y].tx); }
bool cmpx1(const ll x, const ll y) { return max(a[x].sx, a[x].tx) == max(a[y].sx, a[y].tx) ? x > y : max(a[x].sx, a[x].tx) < max(a[y].sx, a[y].tx); }
bool cmpy0(const ll x, const ll y) { return min(a[x].sy, a[x].ty) == min(a[y].sy, a[y].ty) ? x > y : min(a[x].sy, a[x].ty) > min(a[y].sy, a[y].ty); }
bool cmpy1(const ll x, const ll y) { return max(a[x].sy, a[x].ty) == max(a[y].sy, a[y].ty) ? x > y : max(a[x].sy, a[x].ty) < max(a[y].sy, a[y].ty); }

ll n, b, q;
char op;
ll tim[MAX], h[MAX];
ll f[MAX][MAXX], g[MAX][MAXX];

void solve(const ll dx, const ll dy, bool (*cmp)(ll, ll)) {
  for (int i = 1; i <= n + q; ++i) { h[i] = i; }
  sort(h + 1, h + n + q + 1, cmp);
  MP mp; mp.clear();
  for (int i = 1; i <= n + q; ++i) {
    if (h[i] <= n) {
      ll t1, t2;
      if (dx != 0) { t1 = a[h[i]].sy, t2 = a[h[i]].ty; } else { t1 = a[h[i]].sx, t2 = a[h[i]].tx; }
      if (t1 > t2) { swap(t1, t2); }
      const auto i1 = mp.lower_bound(t1), i2 = mp.upper_bound(t2);
      for (IT j = i1; j != i2; mp.erase(j++)) {
        const ll p = j -> second;
        f[p][0] = h[i]; g[p][0] = abs(a[p].tx - a[h[i]].tx) + abs(a[p].ty - a[h[i]].ty);
      }
    }
    if (a[h[i]].dx == dx and a[h[i]].dy == dy) {
      mp.insert({dx != 0 ? a[h[i]].ty : a[h[i]].tx, h[i]});
    }
  }
}

int main() {
  cin >> n >> b;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].sx >> a[i].sy >> a[i].tx >> a[i].ty;
    a[i].dx = a[i].tx - a[i].sx == 0 ? 0 : a[i].tx - a[i].sx > 0 ? 1 : -1;
    a[i].dy = a[i].ty - a[i].sy == 0 ? 0 : a[i].ty - a[i].sy > 0 ? 1 : -1;
  }
  cin >> q;
  for (int i = n + 1; i <= n + q; ++i) {
    cin >> a[i].sx >> a[i].sy >> op >> tim[i]; a[i].tx = a[i].sx; a[i].ty = a[i].sy;
    if (op == 'L') { --a[i].dx; } if (op == 'R') { ++a[i].dx; } if (op == 'U') { ++a[i].dy; } if (op == 'D') { --a[i].dy; }
  }
  solve(-1, 0, cmpx0); solve(1, 0, cmpx1); solve(0, -1, cmpy0); solve(0, 1, cmpy1);
  for (int i = 1; i <= MAXX - 1; ++i) {
    for (int j = 1; j <= n + q; ++j) {
      f[j][i] = f[f[j][i - 1]][i - 1];
      g[j][i] = min(INF, g[j][i - 1] + g[f[j][i - 1]][i - 1]);
    }
  }
  for (int i = n + 1; i <= n + q; ++i) {
    int p = i;
    for (int j = MAXX - 1; j >= 0; --j) {
      if (!f[p][j]) { continue; }
      if (g[p][j] <= tim[i]) { tim[i] -= g[p][j]; p = f[p][j]; }
    }
    if (f[p][0] and tim[i] >= a[p].dx * (a[f[p][0]].tx - a[p].tx) + a[p].dy * (a[f[p][0]].ty - a[p].ty)) {
      tim[i] -= g[p][0]; p = f[p][0];
    }
    cout << min(max(a[p].tx + a[p].dx * tim[i], 0ll), b) << ' '
      << min(max(a[p].ty + a[p].dy * tim[i], 0ll), b) << '\n';
  }
  return 0;
}