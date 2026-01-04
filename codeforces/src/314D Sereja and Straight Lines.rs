///只使用了切片引用（&[Node]），不需要拥有结构体的所有权
use std::io::{self, BufRead};

const N: usize = 500_005;
const INF: i64 = 2e10 as i64;
#[derive(Clone, Copy)]
struct Node { x: i64, y: i64 }
fn cmp(x: &Node, y: &Node) -> std::cmp::Ordering { x.x.cmp(&y.x) }
//给定长度x是否能覆盖所有点
fn solve(x: i64, t: &[Node], n: i64, mxl: &[i64], mnl: &[i64], mxr: &[i64], mnr: &[i64]) -> i32 {
    let mut h = 1i64;//右边界指针
    for i in 1..=n {//枚举左边界
        while h <= n {
            if t[h as usize].x - t[i as usize].x > x { break; }//当前区间长度超过x
            h += 1;
        }
        //竖着的区间，计算区间外的纵坐标最大最小值
        let mxv = mxl[(i - 1) as usize].max(mxr[h as usize]);//左侧和右侧的最大值中的较大者
        let mnv = mnl[(i - 1) as usize].min(mnr[h as usize]);//左侧和右侧的最小值中的较小者
        if mxv - mnv <= x { return 1; }//纵坐标范围不超过x 可以覆盖
    }
    0//无法覆盖
}
fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();//输入行的迭代器
    let n: i64 = lines.next().unwrap().unwrap().parse().unwrap();
    let mut t = vec![Node { x: 0, y: 0 }; N];//变换后的坐标
    for i in 1..=n {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i64> = line.split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let x = parts[0];
        let y = parts[1];
        t[i as usize].x = x - y;//旋转变换：x' = x - y
        t[i as usize].y = x + y;//旋转变换：y' = x + y
    }
    t[1..=(n as usize)].sort_by(cmp);
    //左侧最大最小值数组
    let mut mxl = vec![0i64; N];//从左到i的y坐标的最大值
    let mut mnl = vec![0i64; N];//从左到i的y坐标的最小值
    mxl[0] = -INF; mnl[0] = INF;//边界值
    for i in 1..=n {//前缀最大最小值
        mxl[i as usize] = mxl[(i - 1) as usize].max(t[i as usize].y);
        mnl[i as usize] = mnl[(i - 1) as usize].min(t[i as usize].y);
    }
    //右侧最大最小值数组
    let mut mxr = vec![0i64; N];//从i到末尾的y坐标的最大值
    let mut mnr = vec![0i64; N];//从i到末尾的y坐标的最小值
    mxr[(n + 1) as usize] = -INF; mnr[(n + 1) as usize] = INF;
    for i in (1..=n).rev() {//后缀最大最小值
        mxr[i as usize] = mxr[(i + 1) as usize].max(t[i as usize].y);
        mnr[i as usize] = mnr[(i + 1) as usize].min(t[i as usize].y);
    }
    //最小的正方形边长
    let mut l = 0i64;
    let mut r = 1e10 as i64;
    while l < r {
        let mid = (l + r) >> 1;//当前边长无法覆盖 调高左边界| 可以覆盖 调低右边界
        if solve(mid, &t, n, &mxl, &mnl, &mxr, &mnr) == 0 { l = mid + 1; } else { r = mid; }
    }
    println!("{}", r as f64 / 2.);//边长除以2，因为之前进行了坐标变换
}