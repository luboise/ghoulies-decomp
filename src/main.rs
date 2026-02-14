// #include <iostream>

// #include <SDL3/SDL_gpu.h>

mod ghoulies;
pub(crate) mod graphics;

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
    let args = std::env::args().collect::<Vec<_>>();

    if args.len() != 2 {
        return Err("Expected playcam script in CLI args. eg. ghoulies_launcher ghoulies_chapter2a_scene2_1playcam".into());
    }

    let config = Config::default();
    let asset_context = ghoulies::asset::GameFiles::new(config.game_directory)?;

    let xbe = asset_context.get_executable();

    let mut graphics_ctx = graphics::GraphicsCtx::new()?;

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
