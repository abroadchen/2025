use std::marker::PhantomData;

/**
 @author: June
 @since: 2025/7/25
 @desc:
*/
struct Unique<T> {
    ptr: *const T,
    _marker: PhantomData<T>,
}
unsafe impl<T: Send> Send for Unique<T> {}
unsafe impl<T: Send> Sync for Unique<T> {}

impl<T> Unique<T> {
    const unsafe fn new_unchecked(ptr: *mut T) -> Self {
        unsafe { Unique { ptr, _marker: PhantomData } }
    }
    fn new (ptr: *mut T) -> Option<Self> {
        if !ptr.is_null() {
            Some(unsafe { Unique { ptr, _marker: PhantomData } })
        } else {
            None
        }
    }
    fn as_ptr (&self) -> *mut T {
        self.ptr as *mut T
    }
}


struct MyVec<T> {
    // ptr: *mut T,
    ptr: Unique<T>,
    cap: usize,
    len: usize,
}

