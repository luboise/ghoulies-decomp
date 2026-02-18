// #include <iostream>

// #include <SDL3/SDL_gpu.h>

use std::sync::Arc;

use winit::{
    application::ApplicationHandler,
    event::WindowEvent,
    event_loop::{ActiveEventLoop, ControlFlow, EventLoop},
    window::WindowId,
};

use crate::graphics::{Buffer as _, RenderContext, VulkanRenderer, types::Vertex3D};

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

    let mut app = App::new()?;
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

struct App {
    window: Option<Arc<winit::window::Window>>,
    render_context: Option<RenderContext>,
    game_files: ghoulies::GameFiles,
    bnl: bnl::BNLFile,

    input_helper: winit_input_helper::WinitInputHelper,

    vb: Option<Arc<graphics::VulkanBuffer<Vertex3D>>>,
    ib: Option<Arc<graphics::VulkanBuffer<graphics::Index>>>,
}

impl App {
    fn new() -> Result<Self, Box<dyn std::error::Error>> {
        let args = std::env::args().collect::<Vec<_>>();

        if args.len() != 2 {
            return Err("Expected playcam script in CLI args. eg. ghoulies_launcher ghoulies_chapter2a_scene2_1playcam".into());
        }

        let config = Config::default();
        let game_files = ghoulies::GameFiles::new(config.game_directory)?;

        let bnl_file_path = format!("bundles/aid_script/{}.bnl", args[1]);

        let bnl_file = bnl::BNLFile::from_bytes(
            &game_files
                .get(&bnl_file_path)
                .ok_or_else(|| format!("Failed to find game asset {bnl_file_path}"))?,
        )
        // TODO: Fix this error printing
        .map_err(|e| format!("{e:?}"))?;

        let xbe = game_files.get_executable();

        Ok(Self {
            window: None,
            game_files,
            render_context: None,
            bnl: bnl_file,
            input_helper: winit_input_helper::WinitInputHelper::new(),
            vb: None,
            ib: None,
        })
    }

    fn update_frame(&mut self) -> Result<(), Box<dyn std::error::Error>> {
        self.update_events()?;

        {
            let renderer = &mut self.render_context_mut().renderer;
            renderer.begin_frame().map_err(|e| e.to_string())?;
        }

        self.render_context_mut().use_camera(0).unwrap();

        if self.vb.is_none() {
            let mut vb = self
                .render_context()
                .renderer
                .create_buffer::<Vertex3D>(graphics::BufferType::Vertex, 3)
                .unwrap();
            vb.subbuffer
                .write_values(
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

            self.vb = Some(vb.into());
        }

        if self.ib.is_none() {
            let mut ib = self
                .render_context()
                .renderer
                .create_buffer::<graphics::Index>(graphics::BufferType::Index, 3)
                .unwrap();
            ib.subbuffer.write_values(&[0, 1, 2], 0).unwrap();

            self.ib = Some(ib.into());
        }

        let camera_descriptor_set = self
            .render_context
            .as_ref()
            .unwrap()
            .camera_descriptor_set
            .clone();

        let vb = self.vb.clone().unwrap();
        let ib = self.ib.clone().unwrap();

        // Draw everything
        self.render_context_mut()
            .renderer
            .run_commands(|ctx| {
                ctx.set_vertex_buffer(&vb)?;
                ctx.set_index_buffer(&ib)?;

                ctx.set_view_uniforms(camera_descriptor_set.clone())
                    .map_err(|e| graphics::RenderError::Draw(e.to_string()))?;

                ctx.draw(graphics::DrawCall {
                    num_indices: 3,
                    start_offset: 0,
                    primitive_type: graphics::types::PrimitiveType::LineStrip,
                })?;
                Ok(())
            })
            .map_err(|e| e.to_string())?;

        self.render_context_mut()
            .renderer
            .end_frame()
            .map_err(|e| e.to_string())?;
        // println!("Updating frame.");

        Ok(())
    }

    fn update_events(&mut self) -> Result<(), Box<dyn std::error::Error>> {
        const MAX_MOVEMENT_SPEED: f32 = 100.0;
        const MIN_MOVEMENT_SPEED: f32 = 0.2;

        const MOUSE_SENSITIVITY: f32 = 0.01;

        let delta = self
            .input_helper
            .delta_time()
            .unwrap_or(std::time::Duration::from_micros(1_000_000 / 60))
            .as_secs_f64() as f32;

        let t = delta * MIN_MOVEMENT_SPEED;

        let mut new_cam = unsafe { self.render_context().cameras.get_unchecked(0) }.clone();

        if self.input_helper.key_held(winit::keyboard::KeyCode::KeyA) {
            new_cam.transform.position += t * new_cam.transform.left();
        }
        if self.input_helper.key_held(winit::keyboard::KeyCode::KeyD) {
            new_cam.transform.position += t * new_cam.transform.right();
        }
        if self.input_helper.key_held(winit::keyboard::KeyCode::KeyW) {
            new_cam.transform.position += t * new_cam.transform.forwards();
        }
        if self.input_helper.key_held(winit::keyboard::KeyCode::KeyS) {
            new_cam.transform.position += t * new_cam.transform.backwards();
        }

        let (x, y) = self.input_helper.mouse_diff();
        new_cam.transform.rotation.x += MOUSE_SENSITIVITY * y;
        new_cam.transform.rotation.y += MOUSE_SENSITIVITY * x;

        self.render_context_mut().update_camera(0, |camera| {
            *camera = new_cam.clone();
        })?;

        // Hack to get window to stay up
        // SDL_Event e;

        // glm::vec2 player_rotation {0, 0};

        /*
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_EVENT_KEY_DOWN) {
            if (e.key.key == SDLK_F8) {
              this->toggle_menu_ = true;
            }
          }

          if (menu_active_) {
            menu_->ProcessEvent(&e);
          }

          if (e.type == SDL_EVENT_QUIT) {
            this->quit_ = true;
          }

          // Only handle these events if the menu isn't active
          if (!menu_active_) {
            // TODO: Move this into an event loop somewhere else
            if (e.type == SDL_EVENT_MOUSE_MOTION) {
              constexpr float kMouseSensitivity {0.3F};
              player_rotation = {e.motion.yrel * kMouseSensitivity,
                                 -e.motion.xrel * kMouseSensitivity};
            }
          }
        }
        */

        /*
        if (menu_active_) {
          return;
        }

        if (game_context_.player == nullptr) {
          return;
        }
        */

        /*
        auto& player_transform {game_context_.player->GetTransform()};
        player_transform.RotateX(player_rotation.x);
        player_transform.RotateY(player_rotation.y);
        if (!menu_active_) {
          if (key_states_[SDL_SCANCODE_EQUALS]) {
            movement_speed = std::min(kMaxMovementSpeed, movement_speed * 1.03F);
          }

          if (key_states_[SDL_SCANCODE_MINUS]) {
            movement_speed = std::max(kMinMovementSpeed, movement_speed / 1.03F);
          }

          if (key_states_[SDL_SCANCODE_0]) {
            this->lighting_uniforms_.ambient_brightness =
                std::min(1.0F, this->lighting_uniforms_.ambient_brightness + 0.005F);
          } else if (key_states_[SDL_SCANCODE_9]) {
            this->lighting_uniforms_.ambient_brightness =
                std::max(0.1F, this->lighting_uniforms_.ambient_brightness - 0.005F);
          }

          if (key_states_[SDL_SCANCODE_B]) {
            this->game_context_.draw_backgrounds = !key_states_[SDL_SCANCODE_LSHIFT];
          }
          if (key_states_[SDL_SCANCODE_C]) {
            this->game_context_.draw_colliders = !key_states_[SDL_SCANCODE_LSHIFT];
          }

        }
        */

        Ok(())
    }

    fn render_context(&self) -> &RenderContext {
        // TODO: Make this print an error message at the very least
        self.render_context.as_ref().unwrap()
    }

    fn render_context_mut(&mut self) -> &mut RenderContext {
        // TODO: Make this print an error message at the very least
        self.render_context.as_mut().unwrap()
    }
}

impl ApplicationHandler for App {
    fn resumed(&mut self, event_loop: &ActiveEventLoop) {
        println!("Resuming");

        let new_window = Arc::new(
            event_loop
                .create_window(winit::window::WindowAttributes::default())
                .map_err(|e| e.to_string())
                .unwrap(),
        );

        // TODO: Implement this once actual controls are implemented
        // new_window
        //     .set_cursor_grab(winit::window::CursorGrabMode::Confined)
        //     .expect("Unable to confine cursor");

        self.window = Some(new_window.clone());

        if self.render_context.is_none() {
            // TODO: Replaces these unwraps with something else
            let renderer = VulkanRenderer::new(event_loop, &new_window).unwrap();
            self.render_context = Some(RenderContext::new(renderer).unwrap());
        }
    }

    fn about_to_wait(&mut self, _event_loop: &ActiveEventLoop) {
        self.input_helper.end_step();
        self.window.as_ref().unwrap().request_redraw();
    }

    fn new_events(&mut self, _event_loop: &ActiveEventLoop, _cause: winit::event::StartCause) {
        self.input_helper.step();
    }

    fn device_event(
        &mut self,
        _event_loop: &ActiveEventLoop,
        _device_id: winit::event::DeviceId,
        event: winit::event::DeviceEvent,
    ) {
        self.input_helper.process_device_event(&event);
    }

    fn window_event(&mut self, event_loop: &ActiveEventLoop, _id: WindowId, event: WindowEvent) {
        self.input_helper.process_window_event(&event);

        match event {
            WindowEvent::CloseRequested => {
                println!("The close button was pressed; stopping");
                event_loop.exit();
            }
            WindowEvent::RedrawRequested => {
                if let Err(e) = self.update_frame() {
                    eprintln!("Error drawing frame: {e}");
                }
            }
            _ => (),
        }
    }
}
