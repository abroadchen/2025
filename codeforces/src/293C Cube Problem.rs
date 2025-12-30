///
/// 如果x * y * z ≠ n（不满足乘积条件）
// 或者t ≤ z（三角形不等式条件）
// 或者(x + y + z)为奇数
// 满足任一条件则跳过当前循环
///
///当x = y = z时（三个数相等），方案数加1
// 当x = y ≠ z 或 x ≠ y = z时（两个数相等），方案数加3
// 当x ≠ y ≠ z ≠ x时（三个数都不相等），方案数加6
///
use std::io;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: i64 = input.trim().parse().unwrap();
    if n % 3 != 0 { println!("0"); return }
    let n = n / 3;
    let mut ans = 0i64;
    for x in 1.. {//从1开始遍历x的所有可能值
        if x * x * x > n { break }
        if n % x == 0 {//只有当x能整除n时才进入内层处理
            let dif = x as f64 * x as f64 * x as f64 * x as f64 + 4. * n as f64 * x as f64;
            let ys = ((-x as f64 * x as f64 + dif.sqrt()) / 2. / x as f64).ceil() as i64;
            let ys = ys.max(x);//确保ys至少等于x（保证x ≤ y）
            for y in ys.. {
                if x * y * y > n { break }//x * y² > n
                let z = n / x / y;//x * y * z = n
                let t = (x + y + z) >> 1;
                if x * y * z != n || t <= z || ((x + y + z) & 1) != 0 { continue }
                if x == y && y == z { ans += 1 }
                else if x == y || y == z { ans += 3 }
                else { ans += 6 }
            }
        }
    }
    println!("{}", ans);
}