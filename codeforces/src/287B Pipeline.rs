/**
|x|：闭包参数
x.parse()：将字符串解析为指定类型

计算从1到k的和再减去k-1（即1+2+...+(k-1)+1）
这是所有可能值的最小和

如果f(mid, k, n)返回true，说明mid满足条件，将左边界移到mid
否则，说明mid不满足条件，将右边界移到mid
*/
use std::io;

fn ok(mid: i64, k: i64, n: i64) -> bool {
    let mut s: i64;
    if mid == k { s = mid; }
    else { s = (k + 1) * k / 2 - mid * (mid - 1) / 2 - (k - mid); }
    s >= n
}
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i64> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0];
    let k = parts[1];
    let sum = k * (k + 1) / 2 - k + 1;
    let mut ans = k - 1;
    let mut l = 1;
    let mut r = k + 1;
    let mut mid = (l + r) >> 1;
    if sum < n { println!("-1"); }
    else if n == 1 { print!("0"); }
    else {
        while r - l > 1 {
            mid = (l + r) >> 1;
            if ok(mid, k, n) { l = mid; } else { r = mid; }
        }
        ans = k + 1 - l;
        println!("{}", ans);
    }
}