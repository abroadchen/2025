use std::io::{self, BufRead};
const N: usize = 100005;
#[derive(Clone)]
struct Edge { nxt: usize, to: usize }
struct Graph {
    n: usize,
    q: usize,
    head: [usize; N],
    edges: Vec<Edge>,
    tot: usize,
    cnt: usize,
    ans1: i32,
    de: [i32; N],
    id: [usize; N],
    sum: Vec<Vec<i32>>
}
impl Graph {
    fn new() -> Self {
        Graph {
            n: 0,
            q: 0,
            head: [0; N],
            edges: vec![Edge { nxt: 0, to: 0 }; N<<1],
            tot: 0,
            cnt: 0,
            ans1: 0,
            de: [0; N],
            id: [0; N],
            sum: vec![]
        }
    }
    fn add(&mut self, u: usize, v: usize) {
        self.tot += 1;
        self.edges[self.tot] = Edge {
            nxt: self.head[u],
            to: v
        };
        self.head[u] = self.tot;
    }

    fn dfs(&mut self, u: usize, fa: usize, idd: usize) {
        if idd >= self.sum.len() {
            self.sum.resize(idd + 1, Vec::new());
        }
        self.sum[idd].push(0);
        self.de[u] = self.de[fa] + 1;
        self.id[u] = idd;
        let mut i = self.head[u];
        while i != 0 {
            let v = self.edges[i].to;
            if v != fa { self.dfs(v, u, idd); }
            i = self.edges[i].nxt;
        }
    }
    fn query(&self, mut x: i32, id: usize) -> i32 {
        let mut t = 0;
        while x > 0 {
            t += self.sum[id][x as usize];
            x -= x & (-x);
        }
        t
    }
    fn update(&mut self, mut x: i32, k: i32, id: usize) {
        while (x as usize) < self.sum[id].len() {
            self.sum[id][x as usize] += k;
            x += x & (-x);
        }
    }

    fn change(&mut self, l: i32, r: i32, k: i32, id: usize) {
        self.update(l, k, id);
        if r + 1 < self.sum[id].len() as i32 {
            self.update(r + 1, -k, id);
        }
    }

    fn solve(&mut self) {
        let stdin = io::stdin();
        let lines: Vec<String> = stdin.lock().lines().map(|l| l.unwrap()).collect();
        let mut idx = 0;
        let first_line: Vec<usize> = lines[idx]
            .split_whitespace()
            .map(|l| l.parse().unwrap())
            .collect();
        idx += 1;
        self.n = first_line[0];
        self.q = first_line[1];
        for _ in 0..self.n - 1 {
            let edge_line: Vec<usize> = lines[idx]
                .split_whitespace()
                .map(|l| l.parse().unwrap())
                .collect();
            idx += 1;
            let u = edge_line[0];
            let v = edge_line[1];
            self.add(u, v);
            self.add(v, u);
        }
        let mut i = self.head[1];
        while i != 0 {
            self.cnt += 1;
            self.dfs(self.edges[i].to, 1, self.cnt);
            i = self.edges[i].nxt;
        }
        self.sum.resize(self.cnt + 1, Vec::new());
        self.sum[0].resize(self.n + 2, 0);
        for i in 0..=self.cnt {
            if i >= self.sum.len() { self.sum.push(Vec::new()); }
            self.sum[i].resize(1, 0);
        }
        for _ in 0..self.q {
            let query_line: Vec<i32> = lines[idx]
                .split_whitespace()
                .map(|l| l.parse().unwrap())
                .collect();
            idx += 1;
            let op = query_line[0];
            let v = query_line[1] as usize;
            if op == 1 {
                if v == 1 { println!("{}", self.ans1); }
                else {
                    let res = self.query(self.de[v], 0) + self.query(self.de[v], self.id[v]);
                    println!("{}", res);
                }
            } else {
                let x = query_line[2];
                let d = query_line[3];
                if v == 1 {
                    let right = std::cmp::min(d, self.n as i32);
                    self.change(1, right, x, 0);
                    self.ans1 += x;
                    continue;
                }
                let t = std::cmp::min(self.n as i32, d - self.de[v]);
                let l = std::cmp::max(t + 1, std::cmp::max(0, self.de[v] - d));
                let r = std::cmp::min(self.sum[self.id[v]].len() as i32 - 1, self.de[v] + d);
                if l <= r { self.change(l, r, x, self.id[v]); }
                if t > 0 { self.change(1, t, x, 0); }
                if t >= 0 { self.ans1 += x; }
            }
        }
    }
}

fn main() {
    let mut ans = Graph::new();
    ans.solve();
}