//
// Created by Psy.C on 2026/8/26.
//
/**
由座位编号k求桌子编号pos：

k为偶数时，pos=k/2

k为奇数时，pos=(k+1)/2

若k为偶数，则k/2=(k+1)/2

综上，pos=(k+1)/2

4、由桌子编号求行列数（感觉翻译有点奇怪，以下行为横排(desk)，列为纵排(line)）

对于一般的桌子，r=pos/n+1，d=pos%n

但是这两个式子对于pos==n的情况并不适用，此时r=pos/n，d=n，按照上式算会到下一列的第0行

于是因为懒得写特判干脆将错就错，pos-1，解决了列的问题，而行都少了1，加回去即可

最后得到pos=(k+1)/2-1，r=pos/n+1，d=pos%n+1

5、至于位置的左右，显然k&1（k%2==1）为左，反之为右
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, k, p; cin >> n >> m >> k;
    p = (k + 1) / 2 - 1;
    cout << p/m + 1 << ' ' << p%m + 1 << ' ';
    if (k & 1) cout << "L"; else cout << "R";
    return 0;
}