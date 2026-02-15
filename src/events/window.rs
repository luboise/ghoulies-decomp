use std::sync::{Arc, Mutex};

use glfw::{Glfw, GlfwReceiver, WindowEvent};

#[derive(Debug, Clone)]
pub struct WindowParams {
    pub width: u32,
    pub height: u32,
    pub handles_input: bool,
}

impl Default for WindowParams {
    fn default() -> Self {
        Self {
            width: 1280,
            height: 720,
            handles_input: true,
        }
    }
}

pub type WindowHandle = Arc<Window>;

#[derive(Debug)]
pub struct Window {
    handle: Mutex<glfw::PWindow>,
    events: Mutex<GlfwReceiver<(f64, WindowEvent)>>,
}

impl Window {
    pub(crate) fn new(glfw: &mut Glfw, params: WindowParams) -> Self {
        let (mut window_handle, events) = glfw
            .create_window(
                params.width,
                params.height,
                "Unnamed window",
                glfw::WindowMode::Windowed,
            )
            .expect("Failed to create GLFW window.");

        window_handle.set_key_polling(false);

        Self {
            handle: window_handle.into(),
            events: events.into(),
        }
    }

    /* For OpenGL Windows Only
    pub fn focus(&mut self) {
        self.handle.make_current();
    }
    */

    pub(crate) fn events(&self) -> std::sync::MutexGuard<'_, GlfwReceiver<(f64, WindowEvent)>> {
        self.events.lock().unwrap()
    }

    pub(crate) fn events_mut(&mut self) -> &mut GlfwReceiver<(f64, WindowEvent)> {
        self.events.get_mut().unwrap()
    }

    pub(crate) fn handle(&self) -> std::sync::MutexGuard<'_, glfw::PWindow> {
        self.handle.lock().unwrap()
    }

    pub(crate) fn handle_mut(&mut self) -> &mut glfw::PWindow {
        self.handle.get_mut().unwrap()
    }

    pub fn framebuffer_size(&self) -> [u32; 2] {
        let fb_size = self.handle().get_framebuffer_size();

        [fb_size.0 as u32, fb_size.1 as u32]
    }
}
