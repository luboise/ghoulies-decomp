// #include <iostream>

// #include <SDL3/SDL_gpu.h>

use std::sync::Arc;

use winit::{
    application::ApplicationHandler,
    dpi::PhysicalSize,
    event::WindowEvent,
    event_loop::{ActiveEventLoop, ControlFlow, EventLoop},
    window::{Window, WindowId},
};

use crate::graphics::{Buffer, CommandSubmit, VulkanRenderer, types::Vertex3D};

mod assets {
    mod texture;
}
// mod events;
mod ghoulies;
pub mod graphics;
mod maths;

pub struct Config {
    /// The directory which the game files are located in. If unspecified,
    /// cwd/gbtg will be used. eg. ghoulies_launcher/gbtg/bundles/whatever.bnl
    pub game_directory: std::path::PathBuf,
}

impl Default for Config {
    fn default() -> Self {
        Self {
            game_directory: std::env::current_dir().unwrap().join("gbtg"),
        }
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let event_loop = EventLoop::new().unwrap();

    // ControlFlow::Poll continuously runs the event loop, even if the OS hasn't
    // dispatched any events. This is ideal for games and similar applications.
    event_loop.set_control_flow(ControlFlow::Poll);

    let renderer = graphics::VulkanRenderer::new(&event_loop).map_err(|e| e.to_string())?;

    let mut app = App::new(renderer)?;
    event_loop.run_app(&mut app)?;

    // Initialise the application
    // let ghoulies = ghoulies::GhouliesCtx::new(params)?;

    /*
    ghoulies.set_playcam_script(args[1]);

    // Set the play script
    if (auto result {ghoulies.SetPlaycamScript(argv[1])}; !result.has_value()) {
      std::cerr << "Failed to execute level from BNL file " << argv[1]
                << ". Error: " << result.error() << "\n";
      return 1;
    }

    std::cout << "Ghoulies launcher launched." << '\n';

    while (!ghoulies.ShouldQuit()) {
      ghoulies.BeginFrame();
      ghoulies.UpdateEvents();

      ghoulies.UpdateScene();

      // Draw everything
      auto draw_ctx {ghoulies.NewDrawContext()};
      ghoulies.GameLoop(draw_ctx);
      ghoulies.EndDrawContext(std::move(draw_ctx));
      ghoulies.EndFrame();
    }

    if (auto result {ghoulies::GhouliesCtx::Destroy()}; !result.has_value()) {
      std::cout << "Failed to destroy GhouliesLib. Error: " << result.error();
    }

    std::cout << "Exiting ghoulies launcher." << '\n';
    */

    Ok(())
}

struct App<R: graphics::Render> {
    window: Option<Arc<winit::window::Window>>,
    renderer: R,
    game_files: ghoulies::GameFiles,
}

impl<R> App<R>
where
    R: graphics::Render,
{
    fn new(renderer: R) -> Result<Self, Box<dyn std::error::Error>> {
        let args = std::env::args().collect::<Vec<_>>();

        if args.len() != 2 {
            return Err("Expected playcam script in CLI args. eg. ghoulies_launcher ghoulies_chapter2a_scene2_1playcam".into());
        }

        let config = Config::default();
        let game_files = ghoulies::GameFiles::new(config.game_directory)?;

        let xbe = game_files.get_executable();

        Ok(Self {
            window: None,
            renderer,
            game_files,
        })
    }

    fn update_frame(&mut self) -> Result<(), Box<dyn std::error::Error>> {
        self.renderer.begin_frame().map_err(|e| e.to_string())?;

        let mut vb = self.renderer.create_vertex_buffer::<Vertex3D>(3).unwrap();
        let mut ib = self.renderer.create_index_buffer(4).unwrap();
        ib.write_values(&[0, 1, 2], 0).unwrap();

        vb.write_values(
            &[
                Vertex3D {
                    position: [0.0, 0.0, 0.0],
                    colour: [1.0, 1.0, 1.0],
                    ..Default::default()
                },
                Vertex3D {
                    position: [1.0, 0.0, 0.0],
                    colour: [1.0, 1.0, 1.0],
                    ..Default::default()
                },
                Vertex3D {
                    position: [0.0, 0.5, 0.0],
                    colour: [1.0, 1.0, 1.0],
                    ..Default::default()
                },
            ],
            0,
        )
        .map_err(|e| e.to_string())?;

        self.renderer
            .run_commands(|ctx| {
                ctx.set_vertex_buffer(&vb)?;
                ctx.set_index_buffer(&ib)?;
                ctx.draw(graphics::DrawCall {
                    num_indices: 4,
                    start_offset: 0,
                    primitive_type: graphics::types::PrimitiveType::LineStrip,
                })?;
                Ok(())
            })
            .map_err(|e| e.to_string())?;

        self.renderer.end_frame().map_err(|e| e.to_string())?;
        // println!("Updating frame.");

        Ok(())
    }
}

impl<R> ApplicationHandler for App<R>
where
    R: graphics::Render,
{
    fn resumed(&mut self, event_loop: &ActiveEventLoop) {
        println!("Resuming");

        let new_window = Arc::new(
            event_loop
                .create_window(winit::window::WindowAttributes::default())
                .map_err(|e| e.to_string())
                .unwrap(),
        );

        self.window = Some(new_window.clone());

        self.renderer.set_window(new_window).unwrap();
    }

    fn about_to_wait(&mut self, event_loop: &ActiveEventLoop) {
        self.window.as_ref().unwrap().request_redraw();
    }

    fn window_event(&mut self, event_loop: &ActiveEventLoop, id: WindowId, event: WindowEvent) {
        match event {
            WindowEvent::CloseRequested => {
                println!("The close button was pressed; stopping");
                event_loop.exit();
            }
            WindowEvent::RedrawRequested => {
                self.update_frame();
            }
            _ => (),
        }
    }
}
