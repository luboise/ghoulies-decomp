use std::sync::Arc;

use bnl::asset::{AssetLike, aidlist::AidList, model::nd::NdNode};
use winit::{
    application::ApplicationHandler,
    event::WindowEvent,
    event_loop::{ActiveEventLoop, ControlFlow, EventLoop},
    window::WindowId,
};

use crate::graphics::{Buffer as _, RenderContext, VulkanRenderer, types::Vertex3D};

mod assets;

// mod events;
mod ghoulies;
pub mod graphics;
mod input;
mod maths;
mod objects;

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

// TODO: Make this into custom error type later or use anyhow or something
type Error = Box<dyn std::error::Error>;

fn main() -> Result<(), Error> {
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

#[expect(unused, reason = "These will definitely be used later")]
struct App {
    window: Option<Arc<winit::window::Window>>,
    render_context: Option<RenderContext>,

    pub game_files: ghoulies::GameFiles,
    pub asset_database: assets::AssetDatabase,

    /// The order of the game scripts
    pub scene_order: Vec<String>,

    combined_gamepad: input::Gamepad,
    gamepads: [Option<input::Gamepad>; 4],

    pub input_helper: winit_input_helper::WinitInputHelper,

    pub game_state: ghoulies::GameState,

    pub global_flags: u32,

    vb: Option<Arc<graphics::VulkanBuffer<Vertex3D>>>,
    ib: Option<Arc<graphics::VulkanBuffer<graphics::Index>>>,
    draw_calls: Vec<graphics::DrawCall>,
}

impl App {
    fn new() -> Result<Self, Error> {
        let args = std::env::args().collect::<Vec<_>>();

        if args.len() != 2 {
            return Err("Expected playcam script in CLI args. eg. ghoulies_launcher ghoulies_chapter2a_scene2_1playcam".into());
        }

        let config = Config::default();
        let game_files = ghoulies::GameFiles::new(config.game_directory)?;

        // TODO: Load locale

        // TODO: Initialise renderer

        // TODO: Disable controller rumbles

        // TODO: Set game refresh rate (50hz pal, 60hz ntsc)

        // TODO: Initialise gamepads from real gamepads
        let gamepads = Default::default();

        // TODO: Resource buffers  (default.xbe:0x00035a90)
        // let resource_buffer = ResourceBuffer::new(32);
        // let small_asset_buffer_1 = ResourceBuffer::new(2);
        // let small_asset_buffer_2 = ResourceBuffer::new(2);

        // TODO: Register attackdata, hitreaction, objparams, scripttable from xbe
        // let xbe = game_files.get_executable();

        // TODO: Load common.bnl into persistent memory
        let mut asset_database = assets::AssetDatabase::default();

        let common_bnl = bnl::BNLFile::from_bytes(
            &game_files
                .get("bundles/common.bnl")
                .ok_or_else(|| "Unable to get common.bnl".to_owned())?,
        )
        .map_err(|e| e.to_string())?;
        asset_database.add_bnl("common.bnl", common_bnl)?;

        let user_bnl_name = format!("{}.bnl", args[1]);

        let user_bnl = bnl::BNLFile::from_bytes(
            &game_files
                .get(format!("bundles/aid_script/{user_bnl_name}"))
                .ok_or_else(|| format!("Unable to get {user_bnl_name}"))?,
        )
        .map_err(|e| e.to_string())?;

        asset_database.add_bnl(&user_bnl_name, user_bnl)?;

        // TODO: Initialise audio system

        // TODO: Load "aid_misc_ghoulies_audio_generalsettings" (originally from common.bnl)

        // TODO: Initialise the 4 render cameras in the render context (default.xbe:0x000f5900)

        // TODO: Initialise the logical cameras/camera slots

        let scene_order = asset_database
            .get_asset::<AidList>("aid_aidlist_ghoulies_sceneorder_game")
            .ok_or("Failed to get scene order")?
            .asset()
            .asset_ids()
            .clone();

        // TODO: Initialise default save data (default.xbe@0x33400)

        // TODO: Load "aid_misc_ghoulies_statsheet_actors" (originally from common.bnl?)

        // TODO: Clear next playcam, cutscene delta and (default.xbe:0x35a80)

        let game_state = ghoulies::GameState::default();

        let mut app = Self {
            window: None,
            game_files,
            render_context: None,
            asset_database,
            scene_order,
            input_helper: winit_input_helper::WinitInputHelper::new(),
            game_state,
            global_flags: 0,
            vb: None,
            ib: None,
            draw_calls: Vec::default(),
            combined_gamepad: input::Gamepad::default(),
            gamepads,
        };

        app.set_next_playcam_aid(&app.scene_order.first().expect("Empty scene order").clone())?;

        // TODO: Move this into the actual function it came from (default.xbe:0x12c631)
        // This needs to not be 0 for the game loop to actually run
        app.global_flags = 0x1000;

        // FIXME: Remove this value since its used for testing only
        app.global_flags = 0x401ff;

        // TODO: Look into __controlfp(_PC_24,0x30000);

        Ok(app)
    }

    fn update_frame(&mut self) -> Result<(), Error> {
        self.update_events()?;

        {
            let renderer = &mut self.render_context_mut().renderer;
            renderer.begin_frame().map_err(|e| e.to_string())?;
        }

        self.render_context_mut().use_camera(0).unwrap();

        if self.vb.is_none() || self.ib.is_none() {
            let model = self
                .asset_database
                .get_asset::<bnl::asset::model::Model>("aid_model_ghoulies_powerups_cans_cookcan")
                .ok_or_else(|| {
                    "Unable to get asset \"aid_model_ghoulies_powerups_cans_cookcan\"".to_string()
                })?;

            let mesh = model
                .asset()
                .get_descriptor()
                .mesh_descriptors()
                .first()
                .cloned()
                .unwrap();

            let model_vertex_buffer = mesh
                .primitives()
                .iter()
                .find_map(|nd| {
                    nd.children().find_map(|child| match child {
                        bnl::asset::model::nd::Nd::VertexBuffer(nd_vertex_buffer) => {
                            Some(nd_vertex_buffer)
                        }
                        _ => None,
                    })
                })
                .expect("Failed to find can model");

            let model_push_buffer = mesh
                .primitives()
                .iter()
                .find_map(|nd| {
                    nd.children().find_map(|child| {
                        child.heirarchy().find_map(|inner_child| match inner_child {
                            bnl::asset::model::nd::Nd::PushBuffer(nd_push_buffer) => {
                                Some(nd_push_buffer)
                            }
                            _ => None,
                        })
                    })
                })
                .expect("Failed to get push buffer.");

            let indices = model_push_buffer
                .indices()
                .into_iter()
                .map(|index| index.into())
                .collect::<Vec<u32>>();

            self.draw_calls = model_push_buffer
                .draw_calls()
                .iter()
                .map(|draw| graphics::DrawCall {
                    num_indices: draw.num_vertices as usize,
                    start_offset: (draw.data_ptr - model_push_buffer.push_buffer_base) as usize,
                    primitive_type: draw.prim_type.clone().into(),
                })
                .collect();

            let mut ib = self
                .render_context()
                .renderer
                .create_buffer::<graphics::Index>(graphics::BufferType::Index, indices.len())
                .unwrap();
            ib.subbuffer.write_values(&indices, 0).unwrap();

            self.ib = Some(ib.into());

            let resource = model
                .asset()
                .get_resource_chunks()
                .unwrap()
                .iter()
                .flatten()
                .map(|v| v.to_owned())
                .collect::<Vec<_>>();

            let vertices = model_vertex_buffer
                .get_positions(&resource)
                .unwrap()
                .into_iter()
                .map(|position| Vertex3D {
                    position,
                    ..Default::default()
                })
                .collect::<Vec<_>>();

            let mut vb = self
                .render_context()
                .renderer
                .create_buffer::<Vertex3D>(graphics::BufferType::Vertex, vertices.len())
                .unwrap();
            vb.subbuffer
                .write_values(&vertices, 0)
                .map_err(|e| e.to_string())?;

            self.vb = Some(vb.into());
        }

        let camera_descriptor_set = self
            .render_context
            .as_ref()
            .unwrap()
            .camera_descriptor_set
            .clone();

        let vb = self.vb.clone().unwrap();
        let ib = self.ib.clone().unwrap();

        let draw_calls = self.draw_calls.clone();

        // Draw everything
        self.render_context_mut()
            .renderer
            .run_commands(|ctx| {
                ctx.set_vertex_buffer(&vb)?;
                ctx.set_index_buffer(&ib)?;

                ctx.set_view_uniforms(camera_descriptor_set.clone())
                    .map_err(|e| graphics::RenderError::Draw(e.to_string()))?;

                for draw_call in &draw_calls {
                    ctx.draw(draw_call)?;
                }
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

    fn update_events(&mut self) -> Result<(), Error> {
        #[expect(dead_code)]
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

    /// default.xbe:0x11eb30
    fn set_next_playcam_aid(&mut self, new_playcam_aid: &str) -> Result<(), Error> {
        self.game_state.new_script_aid = Some(new_playcam_aid.to_owned());
        Ok(())
    }

    /// default.xbe:0x33b50
    fn update(&mut self) -> Result<(), Error> {
        self.update_events()?;

        if self.global_flags & 0xff != 0 {
            // Likely to be "If we need to update physics or anything on a fixed tick"
            if self.global_flags & 0x40000 != 0 {
                // default.xbe:0x11e4c0
                self.update_game_state()?;

                // runtime::UpdateStateLinkedLists(&CurrentChapterState);
                /* Draw the UI and handle blocks related to the UI */
                // HandleUIUpdate();
                // PeriodicUpdateWithPi?();
                /* No tangible difference?
                 */
                // FUN_00048f90();
            }
            // FUN_00033480();
            // FUN_00032ab0();
            // Graphics::Update();
            // return;
        }

        self.update_frame()?;

        Ok(())
    }

    #[expect(unused)]
    fn set_load_state(&mut self, load_state: ghoulies::LoadState) -> Result<(), crate::Error> {
        println!("TODO: Set the state");
        Ok(())
    }

    fn update_game_state(&mut self) -> Result<(), Error> {
        if !self.game_state.currently_loading && self.game_state.new_script_aid.is_some() {
            self.set_load_state(ghoulies::LoadState::BeginLoading)?;

            // if self.giant_loctext_struct != 1 && self.giant_loctext_struct != 2 {
            // EventLoop::CreateTransitionCameraAndText();
            // }
        }

        self.game_state.prev_load_state = self.game_state.load_state;

        if let Some(new_load_state) = self.game_state.new_load_state {
            if new_load_state != self.game_state.load_state && !self.game_state.currently_loading
            // TODO: Implement global pause bool
            // && g_paused? == 0
            {
                self.set_load_state(new_load_state)?;
            }
        }

        // FUN_00109470(*(InputHandlerType4 **)((int)&state.loctext? + 1));
        // UpdatePauseScreen();
        // switch(state.globalState) {
        // case State2?:
        //    CurrentChapterState.newState = 0;
        //    Events::UpdateEntities(state);
        //    UpdateStorybook();
        //    return;
        // case BEGUN_LOADING_TRANSITION:
        //                             /* Unable to run any cutscenes when skipped,
        //                                - Music doesn't stop playing
        //                                - Cutscene is permanently loading
        //                                - Game fails to begin cutscene
        //                                - Game fails to exit from cutscene
        //
        //                                NO impact when disabled mid cutscene */
        //    if (state.loadedCutscene != 0) {
        //       EventLoop::SetGameplayState(state,LOADING);
        //    }
        //    state.loadedCutscene = 1;
        //    UpdateStorybook();
        //    return;
        // case LOADING:
        //    Audio::Loading = 1;
        //    iVar1 = Events::loadNewBNL(unaff_EDI);
        //    if ((iVar1 == 0) &&
        //         (CacheContext.utilityDriveError = 0, g_GiantLoctextStruct.g_someGlobalVar == 2)) {
        //       FUN_0012c770();
        //       state.preventStateChanges = 0;
        //       EventLoop::RunPostLoadSetupScripts(state);
        //       CurrentChapterState.newState = FINISHED_LOADING_TRANSITION;
        //       UpdateStorybook();
        //       return;
        //    }
        //    break;
        // case FINISHED_LOADING_TRANSITION:
        //    if (g_GiantLoctextStruct.g_someGlobalVar == 0) {
        //       CurrentChapterState.newState = state.newChapterState;
        //       UpdateStorybook();
        //       return;
        //    }
        //    if (CurrentChapterState.currentChapter == 0) break;
        // case NORMAL:
        //    Events::UpdateEntities(state);
        // }
        // UpdateStorybook();

        Ok(())
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
                if let Err(e) = self.update() {
                    eprintln!("Error drawing frame: {e}");
                }
            }
            _ => (),
        }
    }
}
