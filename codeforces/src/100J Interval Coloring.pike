//
// Created by Psy.C on 2025/11/12.
//
/*
pl存储左括号字符'('或'['
l[i]存储左端点数值
r[i]存储右端点数值
pr存储右括号字符')'或']'

左端点加0.5（表示不包含该点）
右端点减0.5（表示不包含该点）

r[i] >= l[i+1]：第i个区间与第i+1个区间相交
r[i+1] >= l[i+2]：第i+1个区间与第i+2个区间相交
如果同时满足，说明存在三个两两相交的区间，答案设为2
*/

#define rep(i,n) for(int i=0; i<(n); i++)

int main() {
    int n = (int)Stdio.stdin->gets();
    array l = allocate(n), r = allocate(n);
    rep(i,n) {
        int pl, pr;
        sscanf(Stdio.stdin->gets(), "%c%f,%f%c", pl, l[i], r[i], pr);
        if (pl == '(') l[i] += 0.5;
        if (pr == ')') r[i] -= 0.5;
    }
    sort(l, r);//同时对左右端点数组进行排序

    int ans = 1;
    rep(i,n-2) if (r[i] >= l[i + 1] && r[i + 1] >= l[i + 2]) ans = 2;
    write(ans + "\n");
    return 0;
}