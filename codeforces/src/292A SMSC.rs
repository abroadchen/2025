use std::io;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: i32 = input.trim().parse().unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let mut tim = parts[0];
    let mut cnt = parts[1];
    let mut mx = cnt;//最大剩余数量
    let mut cur = cnt;//当前剩余数量
    for _ in 1..n {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let t = parts[0];//当前时间点
        let c = parts[1];//当前新增的数量
        if cur - (t - tim) >= 0 {//减去时间间隔后剩余的数量
            cur -= (t - tim);//减去已处理的数量
            cur += c;//加上新来的数量
        } else { cur = c; }//之前的所有数据都已处理完，当前剩余数量等于新来的数量
        if cur > mx { mx = cur; }//当前剩余数量大于历史最大值，更新最大值
        tim = t;//更新当前时间点，用于下一次循环的时间间隔计算
    }
    println!("{} {}", tim + cur, mx);//最终完成所有任务的时间（最后的时间点 + 剩余待处理数量）
}