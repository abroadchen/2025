
use futures::StreamExt;
use tokio::runtime::Runtime;
use std::io::Result;
use futures::{future, pin_mut, select, FutureExt, Stream};
use futures::stream::FusedStream;

/**
@author: June
@since: 2025/7/26
@desc:
*/

async fn func1() -> Result<()> {
    tokio::time::advance(tokio::time::Duration::from_secs(1)).await;
    Ok(())
}

async fn func2() -> Result<()> {
    Ok(())
}

async fn async_fn() {
    // let f1 = func1();
    // let f2 = func2();
    let f1 = func1().fuse();
    let f2 = func2().fuse();
    // futures::join!(f1, f2);
    // if let Err(_) = futures::try_join!(f1, f2) {
    //     println!("Error");
    // }
    pin_mut!(f1, f2);
    select! {
        _ = f1 => {},
        _ = f2 => {},
    }
}


async fn count() {
    let mut a_fut = future::ready(4);
    let mut b_fut = future::ready(6);
    let mut total = 0;

    loop {
        select! {
            a = a_fut => total += a,
            b = b_fut => total += b,
            complete => break,
            default => unreachable!(),
        }
    }
    assert_eq!(total, 10);
}



async fn add_two_streams (
    mut s1: impl Stream<Item=u8> + FusedStream + Unpin,
    mut s2: impl Stream<Item=u8> + FusedStream + Unpin,
    ) -> u8 {
    let mut total = 0;

    loop {
        let item = select! {
            x = s1.next() => x,
            x = s2.next() => x,
            complete => break,
        };
        if let Some(next_num) = item {
            total += next_num;
        }
    }
    total
}








fn main() {
    let runtime = Runtime::new().unwrap();
    runtime.block_on(async_fn());
}