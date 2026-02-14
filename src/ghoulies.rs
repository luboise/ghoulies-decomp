pub mod asset;
mod xbe_reader;

pub struct GhouliesCtx {
    game_directory: std::path::PathBuf,
    asset_context: asset::GameFiles,
}
