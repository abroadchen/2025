//
// Created by Psy.C on 2025/9/12.
//


#include <cmath>
#include <cstdio>
#define siz 100010
#define maxn(a,b) (((a) > (b)) ? (a) : (b))
#define minn(a,b) (((a) < (b)) ? (a) : (b))
using namespace std;

int l,r, n, mid, k, nans, cnt;
int maxT[siz][20], minT[siz][20], a[siz], ansl[siz][2];

inline int gmax(int l, int r) {
    int j = log2(r-l+1);
    return maxn(maxT[l][j], maxT[r - (1 << j) + 1][j]);
}
inline int gmin(int l, int r) {
    int j = log2(r-l+1);
    return minn(minT[l][j], minT[r - (1 << j) + 1][j]);
}

int binary_(int i) {
    l = i, r = n;
    int ans = i;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (gmax(i, mid) - gmin(i, mid) <= k) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}



int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), maxT[i][0] = minT[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; (i + (1 << j) - 1) <= n; ++i) {
            maxT[i][j] = maxn(maxT[i][j - 1], maxT[i + (1 << (j - 1))][j - 1]);
            minT[i][j] = minn(minT[i][j - 1], minT[i + (1 << (j - 1))][j - 1]);
        }
    for (int i = 1; i <= n; ++i) {
        int pos = binary_(i);
        if (pos - i + 1 > nans) nans = pos - i + 1, ansl[cnt=1][0]=i,ansl[cnt][1]=pos;
        else if (pos - i + 1 == nans) ansl[++cnt][0] = i, ansl[cnt][1]=pos;
    }
    printf("%d %d\n", nans, cnt);
    for (int i = 1; i <= cnt; ++i) printf("%d %d\n", ansl[i][0], ansl[i][1]);
    return 0;
}