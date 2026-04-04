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

    // TODO: Make this ensure there is no sense reference
    pub fn set_next(&mut self, new_next: Option<Ptr<T>>) {
        self.next = new_next
    }

    pub fn set_prev(&mut self, new_prev: Option<Ptr<T>>) {
        self.next = new_prev
    }

    pub fn next(&self) -> Option<&Ptr<T>> {
        self.prev.as_ref()
    }

    pub fn next_mut(&self) -> Option<std::sync::MutexGuard<'_, T>> {
        self.prev.as_ref().and_then(|v| v.lock().ok())
    }
}
