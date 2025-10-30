//
// Created by Psy.C on 2025/10/30.
//

#include <cstdio>
using namespace std;

long a, b, c, d, e, f;

int main() {
    scanf("%ld %ld %ld %ld %ld %ld", &a, &b, &c, &d, &e, &f);
    puts((!a && b && d) || (!c && d) ||
        (b * d * f > a * c * e) ? "Ron" : "Hermione");
    return 0;
}