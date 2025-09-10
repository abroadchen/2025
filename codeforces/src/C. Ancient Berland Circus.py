"""
@author June
@time 2025/9/9
@description:
"""
import math
import sys


def read_points():
    data = list(map(float, sys.stdin.read().strip().split()))
    if len(data) != 6:
        raise SystemExit(0)
    x1, y1, x2, y2, x3, y3 = data
    return (x1, y1), (x2, y2), (x3, y3)


def dist(p, q):
    return math.hypot(p[0] - q[0], p[1] - q[1])


def area2(a, b, c):
    return abs((b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]))


def clamp_unit(t):
    return -1.0 if t < -1.0 else (1.0 if t > 1.0 else t)


def gcd_angle(x, y, eps=1e-10):
    while y > eps:
        x, y = y, math.fmod(x, y)
        if y < 0:
            y += x
    return x


def main():
    A, B, C = read_points()
    S2 = area2(A, B, C)
    if S2 < 1e-12:
        print("0.000000")
        return

    a = dist(B, C)
    b = dist(A, C)
    c = dist(A, B)

    S = S2 / 2.0
    R = (a * b * c) / (4.0 * S)

    cosA = (b * b + c * c - a * a) / (2.0 * b * c)
    A_angle = math.acos(clamp_unit(cosA))
    ta = 2.0 * A_angle

    cosB = (a * a + c * c - b * b) / (2.0 * a * c)
    B_angle = math.acos(clamp_unit(cosB))
    tb = 2.0 * B_angle

    cosC = (a * a + b * b - c * c) / (2.0 * a * b)
    C_angle = math.acos(clamp_unit(cosC))
    tc = 2.0 * C_angle
    two_pi = 2.0 * math.pi
    ta %= two_pi
    tb %= two_pi
    tc %= two_pi

    total = ta + tb + tc
    if abs(total - two_pi) > 1e-10:
        raise ValueError("Invalid angles")
    theta0 = gcd_angle(gcd_angle(ta, tb), tc)

    n = round(two_pi / theta0)
    if n < 3:
        n = 3
    elif n > 100:
        n = 100
    theta0 = two_pi / n
    area = 0.5 * n * R * R * math.sin(theta0)
    print(f"{area:.10f}")


if __name__ == '__main__':
    main()
