/**
@author: June
@since: 2025/7/26
@desc:
*/

async fn async_put_data_to_buf(mut buf: &[u8]) {}

async fn async_main() {
    let f = async {
        let mut x = [0; 128];
        let async_put = async_put_data_to_buf(&mut x);
        async_put.await;
    };
}

struct AsyncFuture<'what_lifetime> {
    x: [u8; 128],
    async_put: PutIntoBuf<'what_lifetime>,
}

struct PutIntoBuf<'a> {
    buf: &'a mut[u8],
}

