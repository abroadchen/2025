use std::io;

fn floyd(dis: &mut Vec<Vec<i32>>, n: usize) {
    for k in 1..=n {//中间节点（松弛节点）
        for i in 1..=n {//起始节点
            for j in 1..=n {//终点节点
                //如果通过中间节点 k 可以缩短 i 到 j 的距离
                if dis[i][j] > dis[i][k] + dis[k][j] && j != k && i != k {//中间节点不是起点或终点
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let d = parts[1];
    let mut a = vec![0i32; 105];//存储点权值
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let ap: Vec<i32> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    for i in 2..n { a[i] = ap[i - 2]; }//a[2], a[3], ..., a[n-1]
    let mut x = vec![0i32; 105];// x 坐标数组
    let mut y = vec![0i32; 105];
    for i in 1..=n {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
        x[i] = parts[0];
        y[i] = parts[1];
    }
    let mut dis = vec![vec![0i32; 105]; 105];
    for i in 1..=n {
        dis[i][i] = 0;//对角线元素为 0
        for j in i + 1..=n {//(曼哈顿距离) * d - a[j]：边权计算
            dis[i][j] = (i32::abs(x[j] - x[i]) + i32::abs(y[j] - y[i])) * d - a[j];
            dis[j][i] = (i32::abs(x[j] - x[i]) + i32::abs(y[j] - y[i])) * d - a[i];
        }
    }
    floyd(&mut dis, n);
    println!("{}", dis[1][n]);//节点 1 到节点 n 的最短距离
}