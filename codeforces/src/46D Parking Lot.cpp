//
// Created by Psy.C on 2025/10/7.
//
/*
*list：存储已分配的区间信息
n：总长度
cov[N<<2]：线段树的lazy标记数组，N<<2等价于N*4
mx[N<<2]：线段树节点对应区间的最大连续长度
mxL[N<<2]：从节点区间左端点开始的最大连续长度
mxR[N<<2]：以节点区间右端点结束的最大连续长度
m：操作次数
 *
*维护线段树节点信息
cov[o] = val：设置lazy标记
当val=1时表示空闲，val=0时表示占用
mx[o] = mxL[o] = mxR[o] = val * (R - L + 1)：更新连续长度信息
 *
*向上传递信息，更新父节点
mxL[rt]和mxR[rt]初始化为左右子树的对应值
mx[rt]取左子树、右子树和跨越中点的连续段的最大值
如果左子树的左连续段等于左子树区间长度，则加上右子树的左连续段
如果右子树的右连续段等于右子树区间长度，则加上左子树的右连续段
如果左右子树标记相同，则父节点标记相同，否则为-1
 *
*构建线段树
初始所有节点标记为-1（表示未确定状态）
叶子节点初始为空闲状态（val=1）
递归构建左右子树并向上更新
 *
*下传lazy标记
如果当前节点有标记，则将标记传给左右子树
 *
*查询第一个长度为need的连续空闲区间起始位置
先下传标记
优先在左子树查找
如果左子树最大连续段不够，但跨越中点的连续段够用，则返回跨越段的起始位置
否则在右子树查找
 *
*修改区间[ql,qr]的状态为val
如果完全包含则直接修改并返回
否则递归修改左右子树并向上更新
 *
 *
*L是可分配区域长度，b是前保护区域长度，f是后保护区域长度
操作1是分配大小为x的内存块，需要额外的b+f保护空间
操作2是释放第x个分配的内存块
使用线段树维护区间状态，支持快速查找连续空闲区间和区间修改
 *
 *
 */
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;
typedef pair<int, int> pii;//用于存储区间
const int N = 100105;

vector<pii> list;//存储已分配的区间信息
int n, cov[N<<2], mx[N<<2], mxL[N<<2], mxR[N<<2], m;

void maintain(int o, int L, int R, int val) {
    cov[o] = val;
    mx[o] = mxL[o] = mxR[o] = val * (R - L + 1);
}

void pushUp(int rt, int L, int R) {
    int mid = L + (R - L) / 2;
    mxL[rt] = mxL[rt<<1], mxR[rt] = mxR[rt<<1|1];
    mx[rt] = max(mx[rt<<1], max(mx[rt<<1|1], mxR[rt<<1]+mxL[rt<<1|1]));
    if (mxL[rt<<1] == (mid - L + 1)) mxL[rt] += mxL[rt<<1|1];
    if (mxR[rt<<1|1] == (R - (mid + 1) + 1)) mxR[rt] += mxR[rt<<1];
    if (cov[rt<<1] == cov[rt<<1|1]) cov[rt] = cov[rt<<1];
    else cov[rt] = -1;
}


void build(int o, int L, int R) {
    cov[o] = -1;
    if (L == R) {
        maintain(o, L, R, 1);
        return;
    }
    int mid = (L + R) >> 1;
    build(o<<1, L, mid);
    build(o<<1|1, mid+1, R);
    pushUp(o, L, R);
}

void pushDown(int rt, int L, int R) {
    if (cov[rt] != -1) {
        int mid = (L + R) >> 1;
        maintain(rt<<1, L, mid, cov[rt]);
        maintain(rt<<1|1, mid+1, R, cov[rt]);
        cov[rt] = -1;
    }
}

int query(int rt, int L, int R, int need) {
    if (L == R ) return L;
    int mid = (L + R) >> 1;
    pushDown(rt, L, R);
    if (mx[rt<<1] >= need) return query(rt<<1, L, mid, need);
    else if (mxR[rt<<1] + mxL[rt<<1|1] >= need) return mid - mxR[rt<<1] + 1;
    else return query(rt<<1|1, mid+1, R, need);
}

void modify(int o, int L, int R, int ql, int qr, int val) {
    if (ql <= L && R <= qr) {
        maintain(o, L, R, val);
        return;
    }
    int mid = (L + R) >> 1;
    pushDown(o, L, R);
    if (ql <= mid) modify(o<<1, L, mid, ql, qr, val);
    if (qr > mid) modify(o<<1|1, mid+1, R, ql, qr, val);
    pushUp(o, L, R);
}

int main() {

    int L, b, f, op, x, start, ql, qr;
    while (~scanf("%d%d%d", &L, &b, &f)) {
        list.clear();
        n = L + b + f;
        build(1, 0, n);
        scanf("%d", &m);
        while (m--) {
            scanf("%d%d", &op, &x);
            if (op == 1) {
                int need = x + b + f;
                start = query(1, 0, n, need);
                ql = start + b, qr = ql + x - 1;
                list.push_back({ql, qr});
                if (b <= ql && qr < b + L) {
                    printf("%d\n", start);
                    modify(1, 0, n, ql, qr, 0);
                } else puts("-1");
            } else {
                ql = list[x - 1].first, qr = list[x - 1].second;
                list.push_back({ql, qr});
                modify(1, 0, n, ql, qr, 1);
            }
        }
    }
    return 0;
}