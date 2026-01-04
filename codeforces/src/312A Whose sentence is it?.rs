//
// Created by Psy.C on 2026/1/4.
//
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    for _ in 0..n {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let line = if input.ends_with("\r\n") {
            &input[..(input.len() - 2)]
        } else if input.ends_with('\n') {
            &input[..(input.len() - 1)]
        } else { &input };
        let m = line.len();
        if m < 5 { println!("OMG>.< I don't know!"); } else {
            let b = line.as_bytes();
            let r = b[0] == b'm' &&
                b[1] == b'i' &&
                b[2] == b'a' &&
                b[3] == b'o' &&
                b[4] == b'.';
            let f = b[m-5] == b'l' &&
                b[m-4] == b'a' &&
                b[m-3] == b'l' &&
                b[m-2] == b'a' &&
                b[m-1] == b'.';
            match (r, f) {
                (true, false) => println!("Rainbow's"),
                (false, true) => println!("Freda's"),
                _ => println!("OMG>.< I don't know!")
            }
        }
    }
}