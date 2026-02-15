mod xbe_reader;

struct XBEResource {
    name: String,
    data: Vec<u8>,
    type_hash: u32,
}

pub struct GameFiles {
    // The directory which the game files are located in
    path: std::path::PathBuf,
    /*
    std::vector<XBEResource> anim_tables;
    std::vector<XBEResource> attack_data;
    std::vector<XBEResource> hit_reactions;
    std::vector<XBEResource> main_objparams;
    std::vector<XBEResource> script_tables;
    std::vector<XBEResource> move_state_objparams;
    std::vector<XBEResource> state_tables;

    static std::expected<GhouliesExecutableData, std::string> FromXBEStream(
        utils::file::XBEStream& stream, const XBEConfig& config);

    [[nodiscard]] const XBEResource* GetResource(
        std::string_view objparams_aid) const;

    std::expected<GhouliesExecutableData, std::string> GetExecutable();
      */
}

impl GameFiles {
    pub fn new(path: impl AsRef<std::path::Path>) -> Result<Self, Box<dyn std::error::Error>> {
        if !path.as_ref().exists() {
            return Err(format!("Game path {} does not exist.", path.as_ref().display()).into());
        }

        Ok(Self {
            path: path.as_ref().into(),
        })
    }

    /// Get a file from the game by its full path
    pub fn get(&self, filepath: impl AsRef<std::path::Path>) -> Option<Vec<u8>> {
        std::fs::read(self.path.join(filepath.as_ref())).ok()
    }

    pub fn get_executable(&self) -> Vec<u8> {
        // TODO: Error handling here
        std::fs::read(self.path.join("default.xbe")).unwrap()
    }

    pub fn path(&self) -> &std::path::Path {
        &self.path
    }
}
