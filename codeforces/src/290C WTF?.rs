use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: f64 = input.trim().parse().unwrap();
    let mut sum = 0.;//累计当前处理过的所有数字的总和
    let mut cnt = 0.;//当前处理过的数字个数
    let mut ret = 0.;//产生最大平均值的总和
    let mut tot = 1.;//产生最大平均值时的数字个数
    for _ in 1..=(n as i32) {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let x: f64 = input.trim().parse().unwrap();
        sum += x;//将当前数字
        cnt += 1.;//记录处理的数字个数
        if sum * tot > ret * cnt {//比较当前平均值与历史最佳平均值
            ret = sum;
            tot = cnt;
        }
    }
    println!("{:.6}", ret / tot);
}