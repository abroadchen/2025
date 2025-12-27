/**
参数类型为64位有符号整数
如果b为0，返回a的绝对值
否则递归调用gcd(b, a % b)
*/
use std::io;

fn gcd(a: i64, b: i64) -> i64 { if b == 0 { a.abs() } else { gcd(b, a % b) } }

fn dis(a: i64, b: i64, c: i64, d: i64) -> (i64, i64) {//两个分数之间的距离（差的绝对值）
    let x = (a * d - b * c).abs();//分子
    let y = b * d;//分母
    let t = gcd(x, y);//使用最大公约数化简分数
    (x / t, y / t)//化简后的分子和分母组成的元组
}

fn comp(a: i64, b: i64, c: i64, d: i64) -> bool { a * d < b * c }//比较两个分数 a/b 和 c/d 的大小
fn main() {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let nums: Vec<i64> = buffer.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let a = nums[0];
    let b = nums[1];
    let c = nums[2];
    let mut x = 0i64;//明确指定为64位整数 初始化当前最优分数的分子和分母
    let mut y = 1i64;
    for i in 1..=c {
        let tx = a * i / b;//计算当前i对应的分子和分母 floor(a*i/b)，这是a/b的小数倍数的整数部分
        let ty = i;
        let l = std::cmp::max(0, tx - 10);//范围是[tx-10, tx+10]，但不小于0
        let r = tx + 10;
        for j in l..=r {//在搜索范围内遍历可能的分子值
            let d1 = dis(j, ty, a, b);//计算新分数j/ty与目标a/b的距离
            let d2 = dis(x, y, a, b);//计算当前最优分数x/y与目标a/b的距离
            if comp(d1.0, d1.1, d2.0, d2.1) {//如果新分数更接近目标（距离更小）
                x = j;//更新最优分数为新分数
                y = ty;
            }
        }
    }
    let t = gcd(x, y);
    x /= t;
    y /= t;
    println!("{}/{}", x, y);
}