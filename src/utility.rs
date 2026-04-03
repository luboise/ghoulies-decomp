pub type Ptr<T: Sized> = std::sync::Arc<std::sync::Mutex<T>>;

#[derive(Debug, Default)]
pub struct EmbeddedNode<T: Sized> {
    pub prev: Option<Ptr<T>>,
    pub next: Option<Ptr<T>>,
}

impl<T: Sized> EmbeddedNode<T> {
    pub fn new(prev: Option<Ptr<T>>, next: Option<Ptr<T>>) -> Self {
        Self { prev, next }
    }

    pub fn next(&self) -> Option<std::sync::MutexGuard<'_, T>> {
        // self.prev.as_ref().map(|v| v.lock().as_deref())
        self.prev.as_ref().and_then(|v| v.lock().ok())
    }

    pub fn next_mut(&self) -> Option<std::sync::MutexGuard<'_, T>> {
        self.prev.as_ref().and_then(|v| v.lock().ok())
    }
}
