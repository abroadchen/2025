use futures::future::BoxFuture;
use futures::FutureExt;

/**
@author: June
@since: 2025/7/26
@desc:
*/

async fn first() {}
async fn second() {}

async fn foo() {
    first().await;
    second().await;
}

// enum FooState {
//     First(first),
//     Second(second),
// }
//
// struct Foo<'a> {
//     f1: FooState::First,
//     f2: FooState::Second,
//     state: FooState,
// }


// async fn re() {
//     re().await;
//     re().await;
// }

fn re() -> BoxFuture<'static, ()> {
    // Box::pin(async move {
    //     re().await;
    //     re().await;
    // })
    async move {
        re().await;
        re().await;
    }.boxed()
}


// enum Ree {
//     First(Re),
//     Second(Re)
// }

// struct Re {
//     f1: Ree::First,
//     f2: Ree::Second,
// }



fn main() {
    futures::executor::block_on(foo())

}