use std::sync::Arc;

use bnl::asset::aidlist::AidList;
use cgmath::{InnerSpace, Rotation3};
use ghoulies::LoadState;
use winit::{
    application::ApplicationHandler,
    event::WindowEvent,
    event_loop::{ActiveEventLoop, ControlFlow, EventLoop},
    window::WindowId,
};

use crate::{
    assets::script::bnl_name_from_asset_name,
    graphics::{Draw, RenderContext, RenderPassType, WgpuRenderer},
    objects::ObjectLike,
};

use clap::Parser;

mod assets;

mod events;
mod ghoulies;
pub mod graphics;
mod input;
mod maths;
mod objects;

pub(crate) mod utility;

#[derive(clap::Parser)]
pub struct Config {
    /// The directory which the game files are located in. If unspecified,
    /// cwd/gbtg will be used. eg. ghoulies_launcher/gbtg/bundles/whatever.bnl
    pub game_directory: Option<std::path::PathBuf>,

    #[clap(short = 'i', long = "index", default_value_t = 0)]
    pub aid_index: usize,
}

impl Default for Config {
    fn default() -> Self {
        Self {
            game_directory: Some(std::env::current_dir().unwrap().join("gbtg")),
            aid_index: 0,
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
    pub object_database: objects::ObjectDatabase,

    /// The order of the game scripts
    pub scene_order: Vec<String>,

    combined_gamepad: input::Gamepad,
    gamepads: [Option<input::Gamepad>; 4],

    pub input_helper: winit_input_helper::WinitInputHelper,

    pub game_state: ghoulies::GameState,

    pub global_flags: u32,

    pub powerup: Option<std::sync::Arc<std::sync::Mutex<objects::avatar::Powerup>>>,
    pub player: Option<std::sync::Arc<std::sync::Mutex<objects::avatar::Actor>>>,
}

impl App {
    fn new() -> Result<Self, Error> {
        let Config {
            game_directory,
            aid_index,
        } = Config::parse();
        let game_files = ghoulies::GameFiles::new(
            game_directory.unwrap_or_else(|| std::env::current_dir().unwrap().join("gbtg")),
        )?;

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
                .get_file("bundles/common.bnl")
                .ok_or_else(|| "Unable to get common.bnl".to_owned())?,
        )
        .map_err(|e| e.to_string())?;
        asset_database.add_bnl("common.bnl", common_bnl)?;

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

            combined_gamepad: input::Gamepad::default(),
            gamepads,
            object_database: objects::ObjectDatabase::default(),

            powerup: None,
            player: None,
        };

        app.set_next_playcam_aid(
            &app.scene_order
                .get(aid_index)
                .ok_or_else(|| {
                    format!(
                        "unable to get aid index {aid_index} from scene order of size {}",
                        app.scene_order.len()
                    )
                })?
                .clone(),
        )?;

        // TODO: Move this into the actual function it came from (default.xbe:0x12c631)
        // This needs to not be 0 for the game loop to actually run
        app.global_flags = 0x1000;

        // FIXME: Remove this value since its used for testing only
        app.global_flags = 0x401ff;

        // TODO: Look into __controlfp(_PC_24,0x30000);

        Ok(app)
    }

    fn render_frame(&mut self) -> Result<(), Error> {
        self.update_events()?;

        {
            self.render_context_mut()
                .renderer
                .begin_frame()
                .map_err(|e| e.to_string())?;
        }

        let powerup = self.powerup.clone();
        let player = self.player.clone();

        self.render_context_mut()
            .run_commands(RenderPassType::PBR, |ctx, render_pass| {
                ctx.use_camera(render_pass, 0)?;

                if let Some(powerup) = powerup.clone() {
                    powerup.lock().unwrap().draw(render_pass)?;
                } else {
                    eprintln!("no powerup");
                }

                if let Some(player) = player.clone() {
                    player.lock().unwrap().draw(render_pass)?;
                }

                Ok(())
            })?;

        // let camera_descriptor_set = self.render_context().camera_descriptor_set.clone();
        //
        self.render_context_mut()
            .renderer
            .end_frame()
            .map_err(|e| e.to_string())?;

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

        let (mouse_x, mouse_y) = self.input_helper.mouse_diff();

        new_cam.transform.rotation =
            (crate::maths::Quat::from_angle_x(cgmath::Rad(MOUSE_SENSITIVITY * mouse_y))
                * crate::maths::Quat::from_angle_y(cgmath::Rad(MOUSE_SENSITIVITY * mouse_x))
                * new_cam.transform.rotation)
                .normalize();

        self.render_context_mut().update_camera(0, |camera| {
            *camera = new_cam.clone();
        })?;

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
                self.update_new_entities()?;

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

        Ok(())
    }

    fn init_playcam_and_globals(&mut self) -> Result<(), crate::Error> {
        // TODO: Figure out what these are and write them into the game state

        // FLOAT_00509b2c = 1.0;
        // vec3_00509b20.x = 1.0;
        // vec3_00509b20.y = 1.0;
        // vec3_00509b20.z = 1.0;
        // FLOAT_00509b4c = 1.0;
        //                           /* Starts at pi/9 (20deg) */
        // UnknownAngle1 = 0.34906587;
        // DAT_005462fc = 1;
        //                           /* Starts at pi/4.5 (40deg) */
        // UnknownAngle2 = 0.69813174;
        // DAT_00509b58 = 1;
        // DAT_00509b70 = 0;
        // Game::UseMovementSmoothing = 1;
        // AllocateGlobalShorts();
        // DAT_00545d1c = 0;
        // DAT_00545cc8 = 0;
        // FUN_0013cbd0();
        // FUN_00116e00();

        // InitPlaycamStuff (default.xbe:0x124420)

        // TODO: Get playcam index in scene order

        // TODO: Get the bundle which the script came from

        // Remove the old player objparams from the last scene
        let _ = self.asset_database.remove_bnl("player_objparams");

        // TODO: Check if the script is a level script or menu
        let script_is_regular = true;

        if script_is_regular {
            // TODO:  Get the player's objparams AIDS (eg. aid_objparams_ghoulies_actor_player_boy)
            let player_objparams_aid = "ghoulies_actor_player_boy";

            let player_bnl = {
                let bytes = self
                    .game_files
                    .get_file(format!("bundles/aid_objparams/{player_objparams_aid}.bnl"));

                if let Some(bytes) = bytes {
                    bnl::BNLFile::from_bytes(&bytes)
                } else {
                    Err(bnl::BNLError::DataReadError(format!(
                        "Unable to construct bnl for objparams AID {player_objparams_aid}"
                    )))
                }
            }
            // FIXME: BNLError handling
            .map_err(|e| e.to_string())?;

            self.asset_database
                .add_bnl("player_objparams", player_bnl)?;
        }
        let _ = self.load_bnl_from_script_aid(&self.game_state.current_script_aid.clone());

        Ok(())
    }

    fn set_load_state(&mut self, load_state: LoadState) -> Result<(), crate::Error> {
        // let state = &mut self.game_state;

        if self.game_state.load_state != load_state {
            // Cleanup current load state
            match self.game_state.load_state {
                LoadState::Normal | LoadState::State2 => {

                    // g_stateStack = g_stateStack + 1;
                    // FUN_00106e90();
                }
                LoadState::Loading => {

                    // Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
                    // GlobalCounter2 = GlobalCounter2 + -1;
                }
                LoadState::FinishedLoading => {
                    // runtime::FinaliseLoad();
                }
                LoadState::Paused => {
                    // UnpauseGame();
                }
                LoadState::Null | LoadState::BeginLoading => (),
            }

            match load_state {
                LoadState::Normal | LoadState::State2 => {

                    // g_stateStack = g_stateStack + -1;
                    // if (g_stateStack < 0) {
                    //   g_stateStack = 0;
                    // }
                    // UpdateDrawingData???();
                }
                LoadState::BeginLoading => {
                    // self.game_state.preventLoading = 1;
                    // self.game_state.field10_0x120 = 0;
                    // self.game_state.loadedCutscene = 0;
                }
                LoadState::Loading => {
                    // Game::EndScene(state);
                    // Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
                    // GlobalCounter2 = GlobalCounter2 + 1;

                    // Original game just writes anyway and stubs out the new aid
                    self.game_state.current_script_aid =
                        self.game_state.new_script_aid.take().unwrap_or_default();

                    println!(
                        "New playcam script: {}",
                        &self.game_state.current_script_aid
                    );

                    self.game_state.current_playcam_script_header = Some(
                        self.game_files
                            .script_headers
                            .iter()
                            .find(|header| {
                                header
                                    .name
                                    .iter()
                                    .take_while(|c| **c != 0)
                                    .map(|c| *c as char)
                                    .collect::<String>()
                                    == self.game_state.current_script_aid
                            })
                            .cloned()
                            .unwrap_or(self.game_files.script_headers.first().cloned().unwrap()),
                    );

                    // *(undefined4 *)((int)&self.game_state.field79_0x22b + 1) = 4;
                    // UpdateVolumes();
                    self.init_playcam_and_globals()?;
                    // self.game_state.field10_0x120 = 1;
                }
                LoadState::Paused => {
                    // UI::EnterPauseUI();
                }
                LoadState::FinishedLoading => (),
                LoadState::Null => (),
            }

            ///////////////////

            println!("Setting load state to {load_state:?}");
            self.game_state.load_state = load_state;
        }

        Ok(())
    }

    fn update_game_state(&mut self) -> Result<(), Error> {
        if !self.game_state.prevent_loading && self.game_state.new_script_aid.is_some() {
            self.set_load_state(LoadState::BeginLoading)?;

            // if self.giant_loctext_struct != 1 && self.giant_loctext_struct != 2 {
            // EventLoop::CreateTransitionCameraAndText();
            // }
        }

        self.game_state.prev_load_state = self.game_state.load_state;

        if let Some(new_load_state) = self.game_state.new_load_state {
            if new_load_state != self.game_state.load_state && !self.game_state.prevent_loading
            // TODO: Implement global pause bool
            // && g_paused? == 0
            {
                self.set_load_state(new_load_state)?;
            }
        }

        // Handle input
        // FUN_00109470(*(InputHandlerType4 **)((int)&state.loctext? + 1));

        // UpdatePauseScreen();

        match self.game_state.load_state {
            LoadState::State2 => {
                // CurrentChapterState.newState = 0;
                // Events::UpdateEntities(state);
                // UpdateStorybook();
                return Ok(());
            }
            LoadState::BeginLoading => {
                if self.game_state.transition_finished {
                    self.set_load_state(LoadState::Loading)?;
                }
                self.game_state.transition_finished = true;
                // UpdateStorybook();
                return Ok(());
            }
            LoadState::Loading => {
                // Audio::Loading = 1;
                let script_aid = bnl_name_from_asset_name(&self.game_state.current_script_aid)?;

                let bnl_path = format!("bundles/aid_script/{script_aid}");

                let bnl_bytes = self
                    .game_files
                    .get_file(&bnl_path)
                    .ok_or_else(|| format!("Failed to get bnl bytes for path {bnl_path}"))?;

                let new_script_bnl =
                    bnl::BNLFile::from_bytes(&bnl_bytes).map_err(|e| e.to_string())?;

                self.asset_database.add_bnl(&script_aid, new_script_bnl)?;

                // if ((iVar1 == 0)
                //     && (
                //         CacheContext.utilityDriveError = 0,
                //         g_GiantLoctextStruct.g_someGlobalVar == 2,
                //     ))

                {
                    // FUN_0012c770();
                    // state.preventStateChanges = 0;
                    // EventLoop::RunPostLoadSetupScripts(state);
                    self.game_state.new_load_state = Some(LoadState::FinishedLoading);
                    // UpdateStorybook();
                    // return;
                }
                // UpdateStorybook();
                return Ok(());
            }
            LoadState::FinishedLoading => {
                // if (g_GiantLoctextStruct.g_someGlobalVar == 0) {
                // self.game_state.new_load_state = self.game_state.new_chapter_state;
                // UpdateStorybook();
                //     return Ok(());
                // }

                // TODO: Replace this with the actual logic here
                self.game_state.new_load_state = Some(LoadState::Normal);
                return Ok(());

                // equivalent of break in original code
                if self.game_state.current_chapter == 0 {
                    // UpdateStorybook();
                    return Ok(());
                }

                // Events::UpdateEntities(self.game_state);
                // Events::UpdateStorybook(self.game_state);
                return Ok(());
            }
            LoadState::Normal => {
                if self.powerup.is_none() {
                    let params = self
                        .game_files
                        .powerup_objparams
                        .get("aid_objparams_ghoulies_powerup_knockdownmania")
                        .cloned()
                        .expect("unable to find base PowerupParams");

                    match objects::avatar::Powerup::ctor(self, &params) {
                        Ok(v) => self.powerup = Some(std::sync::Arc::new(v.into())),
                        Err(e) => {
                            eprintln!("{e}");
                            panic!();
                        }
                    }
                }

                if self.player.is_none() {
                    let params = self
                        .game_files
                        .actor_objparams
                        .get("aid_objparams_ghoulies_actor_player_boy")
                        .cloned()
                        .expect("unable to find player objparams");

                    match objects::avatar::Actor::ctor(self, &params) {
                        Ok(v) => self.player = Some(std::sync::Arc::new(v.into())),
                        Err(e) => {
                            eprintln!("{e}");
                            panic!();
                        }
                    }
                }

                {
                    //  if (state->someLoadedVar != 0) {
                    //   uVar3 = state->someLoadedVar - 1;
                    //   state->someLoadedVar = uVar3;
                    //   if (uVar3 == 2) {
                    //     Audio::Loading = 0;
                    //   }
                    //                   /* If done loading, unmute the game */
                    //   UpdateGameVolumes();
                    // }

                    // if ((0.0 < runtime::dx_timer) &&
                    //    (runtime::dx_timer = runtime::dx_timer - runtime::DeltaTime * runtime::TimeScale,
                    //    runtime::dx_timer <= 0.0)) {
                    //   runtime::dx_timer = 0.0;
                    // }
                    // TODO: Use real delta time
                    let delta = std::time::Duration::from_secs_f32(1.0 / 60.0);
                    // g_ticksToRun = (int)delta;
                    // g_totalTicksUpdated = delta - (float)g_ticksToRun;

                    // UpdateCutsceneProgress();
                    // UpdateCutsceneAndDraws();

                    // UpdateDialogEvents();
                    // /* If in dialogs */
                    // if (Game::UpdateActionType == 3) {
                    //   FUN_0013ffd0();
                    // }

                    // CheckLevelExitTriggers();
                    // RunChallengeSetupTriggers();
                    // RunEndOfScaryShockEvents();
                    // CheckLevelExitTriggers();
                    // puVar2 = Game::SceneControls.next;
                    // if (Game::InGhoulyIntro == 1) {
                    //   EventLoop::ExecuteGhoulieIntro();
                    //   puVar2 = Game::SceneControls.next;
                    // }
                    //                   /* Update scene controls */
                    // while (puVar2 != NULL) {
                    //   puVar1 = *(sceneControlObj@0x8 *)(puVar2 + 4);
                    //                   /* Skipping this breaks
                    //                      - music in level
                    //                      - menu completely
                    //                      - menu input if menu already loaded
                    //                      - but not dialog? */
                    //   (**(code **)&(*(sceneControlObj **)(puVar2 + -8))->field_0x10)(puVar2 + -8);
                    //   puVar2 = puVar1;
                    // }
                    //                   /* 0x511b18 = scene tree?
                    //                      - set to 0 when entering level */
                    // avatar::updateRecursive((avatar@0x918)Game::SceneInfo.sceneTree.head);
                    //                   /* Draw Background */
                    // Background::updateViews();
                    // UpdatePerSecondTimers();
                    // UpdateGhoulyBoxes();
                    // Scripting::RunScriptConditionsCallback2();
                    // ExecuteGhoulieIntroLoctext();
                    // UpdateActionsAndDialog();
                    // delta = 0.0;
                    // if ((runtime::dx_timer <= 0.0) &&
                    //    (delta = runtime::DeltaTime * runtime::TimeScale, 0.016666668 < delta)) {
                    //   delta = 0.016666668;
                    // }
                    // UpdateTextureMaybeSomethings(delta * 7.2);
                    // Graphics::CleanupResources?();
                    // if ((DAT_00510580 != 0) && (DAT_00510650 == 0)) {
                    //   DAT_00510648 = DAT_00510648 + 0.002;
                    //   DAT_0051064c = DAT_0051064c + 0.002;
                    //   Graphics::InitialiseScreenSpaceQuads();
                    // }
                    // UpdateDeltaAngles();
                    // FUN_001185e0();
                    // FUN_000fdda0();
                    // Graphics::UpdateFog?();
                    //                   /* Run input handlers */
                    // if ((((((int)Input::InputHandlers->tail - (int)Input::InputHandlers->head) /
                    //        (int)(uint)Input::InputHandlers->valueSize != 0) &&
                    //      (piVar2 = *(Buffer<> **)
                    //                 (Input::InputHandlers->head->handlerName +
                    //                 (Input::NumInputHandlers - 1) * (uint)Input::InputHandlers->valueSize + -4),
                    //      piVar2 != NULL)) &&
                    //     (matches = Input::ContextHasButton(START,(InputHandlerType3 *)piVar2), matches != 0)) &&
                    //    (Game::NotAllowedToPause == 0)) {
                    //   Game::GameState.new_load_state =
                    //        (-(uint)(g_paused? != 0) & 0b11111111111111111111111111111011) + Paused;
                    // }
                }
            }
            LoadState::Null | LoadState::Paused => (),
        }
        // UpdateStorybook();

        Ok(())
    }

    fn update_new_entities(&mut self) -> Result<(), Error> {
        self.process_new_scene_controls()?;

        /*
                          /* Add new avatars and scene controls to global lists */
        avatar::processNew();
                          /* Tell the new ones that the scene has begun */
        sceneControlObj::BeginScene();
        avatar::BeginScene();
                          /* Update them once (this would be at the end of the event loop) */
        sceneControlObj::updateAndDepleteList();
        avatar::updateAndDepleteList();
                          /* If normal or state 2

                             If we're in a normal state, update fx and timers */
        if ((0 < (int)param_1->load_state) && ((int)param_1->load_state < 3)) {
          UpdatePowerups();
          UpdateFX();
          UpdateGlobalTimers();
        }
        UpdateAvatarAudio();
        sceneControlObj::destroyStaleControls();
        avatar::destroyStaleAvatars();
        EntitiesNeedUpdating = 0;
        avatar::updateShadows();
        */

        Ok(())
    }

    fn process_new_scene_controls(&mut self) -> Result<(), Error> {
        while let Some(new_scene_control) = self.object_database.new_scene_controls.pop_front() {
            self.object_database
                .scene_controls
                .push_back(new_scene_control);
        }

        self.object_database
            .scene_controls
            .extend(std::mem::take(&mut self.object_database.new_scene_controls));

        Ok(())
    }

    fn process_new_avatars(&mut self) -> Result<(), Error> {
        while let Some(new_avatar) = self.object_database.new_avatars.pop_front() {
            self.object_database.avatars.push_back(new_avatar);
        }

        self.object_database
            .avatars
            .extend(std::mem::take(&mut self.object_database.new_avatars));

        Ok(())
    }

    // Default.xbe: 0x00341e0
    #[must_use]
    fn load_bnl_from_script_aid(&mut self, aid: &str) -> bool {
        // TODO: Remove loaded bnl files before loading the new one like the original game does

        self.game_files
            .get_file(format!("bundles/aid_script/{aid}"))
            .and_then(|file| bnl::BNLFile::from_bytes(&file).ok())
            .and_then(|bnl| self.asset_database.add_bnl(aid, bnl).ok())
            .is_some()
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
            let renderer =
                smol::block_on(WgpuRenderer::new(&new_window)).expect("failed to create renderer");
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
                    eprintln!("failed to update game: {e}");
                    return;
                }

                if let Err(e) = self.render_frame() {
                    eprintln!("failed to render frame: {e}");
                }
            }
            WindowEvent::Resized(winit::dpi::PhysicalSize { width, height }) => {
                self.render_context_mut()
                    .renderer
                    .resize(width, height)
                    // TODO: Remove this expect and do something better here
                    .expect("failed to resize window");
            }
            _ => (),
        }
    }
}
