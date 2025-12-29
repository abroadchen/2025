///
/// 如果度数为2：继续（对bus/ring拓扑正常）
// 如果度数为1：计数器c减1（bus拓扑应有2个度数为1的节点）
// 如果m == n-1且度数为n-1：星型拓扑（一个中心节点连接所有其他节点）
// 其他情况：未知拓扑
///如果c == 0：说明有2个度数为1的节点，是bus topology
// 否则：所有节点度数都为2，是ring topology
///
///
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0];//图的节点数
    let m = parts[1];//图的边数
    let mut deg = vec![0; n + 1];
    for _ in 0..m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<usize> = input.trim().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        let x = parts[0];//边的两个端点
        let y = parts[1];
        deg[x] += 1; deg[y] += 1;//无向图
    }
    let mut c = 2;
    let st = n - 1;//星型拓扑中中心节点的度数
    for i in 1..=n {
        if deg[i] == 2 {} else if deg[i] == 1 { c -= 1; } else if m == n - 1 &&
            deg[i] == st {
            println!("star topology"); return;
        } else {
            println!("unknown topology"); return;
        }
    }
    if c == 0 { println!("bus topology"); } else { println!("ring topology"); }
}