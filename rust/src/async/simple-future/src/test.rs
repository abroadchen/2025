use std::pin::Pin;
use std::task::{Context, Poll};


/**
@author: June
@since: 2025/7/26
@desc:
*/

async fn async_f1() {}
async fn async_f2() {}

async fn async_main() {
  let f1 = async_f1();
  let f2 = async_f2();
  let f = async move {
    f1.await;
    f2.await;
  };
  f.await;
}

// struct AsyncFuture {
//   fut_1: FutFunction1,
//   fut_2: FutFunction2,
//   state: State,
// }

enum State {
  AwaitFut1,
  AwaitFut2,
  Done,
}

// impl Future for AsyncFuture {
//   type Output = ();
//   fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<()> {
//     loop {
//       match self.state {
//         State::AwaitFut1 => match self.fut_1.poll(..) {
//           Poll::Ready(()) => self.state = State::AwaitFut2,
//           Poll::Pending => return Poll::Pending,
//         }
//         State::AwaitFut2 => match self.fut_2.poll(..) {
//           Poll::Ready(()) => self.state = State::Done,
//           Poll::Pending => return Poll::Pending,
//         }
//         State::Done => return Poll::Ready(()),
//       }
//     }
//   }
// }