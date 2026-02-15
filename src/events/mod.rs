// pub mod window;

use std::{ops::Deref, sync::Arc};

use glfw::{ClientApiHint, Glfw, WindowHint};
use window::Window;

use crate::events::window::{WindowHandle, WindowParams};

#[derive(Debug)]
pub struct EventContext {
    glfw: Glfw,

    windows: Vec<WindowHandle>,
}

impl EventContext {
    pub fn new() -> Self {
        let mut glfw = glfw::init(glfw::fail_on_errors).unwrap();

        glfw.window_hint(WindowHint::ClientApi(ClientApiHint::NoApi));

        Self {
            glfw,
            windows: vec![],
        }
    }

    pub fn get_window(&mut self, index: usize) -> Option<WindowHandle> {
        self.windows.get(index).map(Arc::clone)
    }

    pub fn create_window(&mut self, params: WindowParams) -> WindowHandle {
        let new_window = Window::new(&mut self.glfw, params);

        let arc: WindowHandle = new_window.into();

        self.windows.push(arc.clone());

        arc
    }

    // TODO: Make this return a result
    pub fn update(&mut self) {
        self.glfw.poll_events();

        for window in &self.windows {
            for (_, event) in glfw::flush_messages(window.events().deref()) {
                match event {
                    glfw::WindowEvent::Close => panic!("Window closed."),
                    glfw::WindowEvent::Pos(_, _)
                    | glfw::WindowEvent::Size(_, _)
                    | glfw::WindowEvent::Refresh
                    | glfw::WindowEvent::Focus(_)
                    | glfw::WindowEvent::Iconify(_)
                    | glfw::WindowEvent::FramebufferSize(_, _)
                    | glfw::WindowEvent::MouseButton(_, _, _)
                    | glfw::WindowEvent::CursorPos(_, _)
                    | glfw::WindowEvent::CursorEnter(_)
                    | glfw::WindowEvent::Scroll(_, _)
                    | glfw::WindowEvent::Key(_, _, _, _)
                    | glfw::WindowEvent::Char(_)
                    | glfw::WindowEvent::CharModifiers(_, _)
                    | glfw::WindowEvent::FileDrop(_)
                    | glfw::WindowEvent::Maximize(_)
                    | glfw::WindowEvent::ContentScale(_, _) => {}
                }
            }
        }
    }
}

impl Default for EventContext {
    fn default() -> Self {
        Self::new()
    }
}
