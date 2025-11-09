//
// Created by Psy.C on 2025/9/22.
//


#include <iosfwd>
#include <fstream>
using namespace std;

bool fstwin(long n, long m, long k) {
    long min = (m < n) ? m : n;
    if (min % (k + 1) == 0) {
        return true;
    } else if (k == 1 || (min / (k + 1)) % 2 == 0) {
        return (m % 2) != (n % 2);// 返回m和n奇偶性不同
    } else {
        return (m % 2) == (n % 2);
    }
}

int main() {

    ifstream instream;
    instream.open("input.txt");
    FILE* f = fopen("output.txt", "w");

    long t, k; instream >> t >> k;
    while (t--) {
        long n, m; instream >> n >> m;
        fputs(fstwin(n, m, k) ? "+\n" : "-\n", f);
    }
    instream.close();
    fclose(f);
    return 0;
}