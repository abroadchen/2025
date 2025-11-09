//
// Created by Psy.C on 2025/9/11.
//


#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 50005;
char s[MAXN];
int n, a[MAXN], b[MAXN];

struct Node {
    int no, a, b;
    bool operator<(const Node &rhs) const {
        return b - a < rhs.b - rhs.a;
    }
};

priority_queue<Node> pq;


int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int cnt = 0;
    LL sum = 0;

    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') cnt++;
        if (s[i] == '?') {
            scanf("%d%d", &a[i], &b[i]);
            if (i == 1) {
                sum += a[i];
                s[i] = '(';
                cnt++;
                continue;
            }
            sum += b[i];
            s[i] = ')';
            pq.push(Node{i, a[i], b[i]});
        }
        if (s[i] == ')') {
            if (cnt == 0) {
                if (pq.empty()) {
                    puts("-1");
                    return 0;
                }
                Node t = pq.top();
                pq.pop();
                if (t.no == n) {
                    t = pq.top();
                    pq.pop();
                }
                sum -= t.b;
                sum += t.a;
                s[t.no] = '(';
                if (t.no == i) cnt++;
                else cnt += 2;
            }
            if (s[i] == ')') cnt--;
        }
    }
    if (cnt != 0) {
        puts("-1");
        return 0;
    }

    printf("%lld\n%s", sum, s + 1);


    return 0;
}