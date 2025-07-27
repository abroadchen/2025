/**
@author: June
@since: 2025/7/28
@desc:
*/

pub struct TrackingAllocator;

#[cfg(feature = "allocator-api2")]
unsafe impl Allocator for TrackingAllocator {
    fn allocate(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        unsafe {
            let ptr = System.alloc(layout);
            if ptr.is_null() {
                Err(AllocError)
            } else {
                let slice_ptr: *mut [u8] = slice::from_raw_parts_mut(ptr, layout.size());
                let non_null_slice: NonNull<[u8]> = NonNull::new_unchecked(slice_ptr);
                record_alloc(layout); // 记录内存分配的大小的函数

                Ok(non_null_slice)
            }
        }
    }

    unsafe fn deallocate(&self, ptr: NonNull<u8>, layout: Layout) {
        record_dealloc(layout); // 记录内存释放的大小的函数
        let raw_ptr: *mut u8 = ptr.as_ptr();
        System.dealloc(raw_ptr, layout);
    }
}

fn main() {
    let alloc = TrackingAllocator;
    let mut m = hashbrown::HashMap::new_in(&alloc);
    ...

}