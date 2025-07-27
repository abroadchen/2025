use core::blockchain;
use std::thread;
use std::time::Duration;

fn main() {
    let mut bc = blockchain::BlockChain::new_blockchain();

    println!("start mining ...");
    thread::sleep(Duration::from_secs(1));
    bc.add_block(String::from("a -> b: 5 btc"));
    println!("block added");

    println!("");
    println!("start mining ...");
    thread::sleep(Duration::from_secs(1));
    bc.add_block(String::from("c -> d: 1 btc"));
    println!("block added");




    for b in bc.blocks {
        println!("++++++++++++++++++++++++++++++++++++++++++++");
        println!("{:#?}", b);
        println!("");
    }
    println!("Hello, world!");
}
