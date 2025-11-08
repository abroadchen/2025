//
// Created by Psy.C on 2025/9/10.
//

#include <ios>
#include <iostream>
#include <utility>
using namespace std;

const int maxn = 1e5+7;
pair<int, int> p1[maxn], p2[maxn];
int sum1[maxn], sum2[maxn];
int n1, n2;

bool cmp(pair<int, int> p1, pair<int, int> p2) {
    return p1.first > p2.first;
}


int main()
{
    int n, v;
    scanf("%d%d", &n, &v);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x == 1) p1[++n1]=make_pair(y, i);
        else p2[++n2]=make_pair(y, i);
    }
    sort(p1+1, p1+1+n1, cmp);
    sort(p2+1, p2+1+n2, cmp);
    for (int i = 1; i <= n1; i++)
        sum1[i] = sum1[i-1] + p1[i].first;
    for (int i = 1; i <= n2; i++)
        sum2[i] = sum2[i-1] + p2[i].first;

    int Ans = 0, x = 0, y = 0;
    for (int i = 0; i <= n1; i++) {
        if (i > v) break;
        int l = 0, r = n2, ans = 0;
        while (l <= r) {
            int mid = (l + r)/2;
            if (2 * mid <= v - i) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        int tmp = sum1[i] + sum2[ans];
        if (tmp > Ans) {
            Ans = tmp;
            x = i, y = ans;
        }
    }
    printf("%d\n", Ans);
    for (int i = 1; i <= x; i++) printf("%d ", p1[i].second);
    for (int i = 1; i <= y; i++) printf("%d ", p2[i].second);


    return 0;
}