//
// Created by Psy.C on 2025/11/12.
//


int main() {
    float k, pi = acos(-1.0);
    sscanf(Stdio.stdin->gets(), "%f", k);
    k = k * pi / 180.0;
    float x, y;
    sscanf(Stdio.stdin->gets(), "%f %f", x, y);
    float u, v;
    u = x * cos(k) - y * sin(k);
    v = x * sin(k) + y * cos(k);
    write(u + " " + v);
    return 0;
}