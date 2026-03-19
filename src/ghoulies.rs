use bnl::asset::AssetName;

mod xbe_reader;

struct XBEResource {
    name: String,
    data: Vec<u8>,
    type_hash: u32,
}

#[repr(C)]
#[derive(Debug, Clone)]
pub struct XBEScriptHeader {
    pub name: AssetName,
    pub transition_index: i32,
    pub unknown_val_1: i32,
    pub pause_flags: i32,
    pub unknown_val_2: i32,
}

#[derive(Debug)]
pub struct GameFiles {
    // The directory which the game files are located in
    path: std::path::PathBuf,
    script_headers: Vec<XBEScriptHeader>,
    xbe: xbe_reader::XBEFile,
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
        assert_eq!(size_of::<XBEScriptHeader>(), 0x90);

        let path: std::path::PathBuf = path.as_ref().into();

        if !path.exists() {
            return Err(format!("Game path {} does not exist.", path.display()).into());
        }

        let xbe_file = xbe_reader::XBEFile::new(path.join("default.xbe"))?;

        let script_headers = xbe_file
            .get::<[XBEScriptHeader; 168]>(0x42ac80u32)?
            .to_vec();

        assert!(!script_headers.is_empty());

        Ok(Self {
            path,
            script_headers,
            xbe: xbe_file,
        })
    }

    /// Get a file from the game by its full path
    pub fn get(&self, filepath: impl AsRef<std::path::Path>) -> Option<Vec<u8>> {
        std::fs::read(self.path.join(filepath.as_ref())).ok()
    }

    pub fn path(&self) -> &std::path::Path {
        &self.path
    }

    pub fn xbe(&self) -> &xbe_reader::XBEFile {
        &self.xbe
    }

    pub fn script_headers(&self) -> &[XBEScriptHeader] {
        &self.script_headers
    }
}

#[derive(Default, Debug, PartialEq, Clone, Copy)]
#[repr(C)]
#[expect(unused)]
pub enum LoadState {
    #[default]
    Null = 0,
    Normal = 1,
    State2 = 2,
    BeginLoading = 3,
    Loading = 4,
    FinishedLoading = 5,
    Paused = 6,
}

#[derive(Debug)]
pub struct GameState {
    pub current_script_aid: String,
    pub new_script_aid: Option<String>,
    // TODO: Replace with enum later
    pub new_script_state: i32,
    pub load_state: LoadState,
    pub new_load_state: Option<LoadState>,
    pub prev_load_state: LoadState,
    pub prevent_loading: bool,
    pub transition_finished: bool,
    // actor: std::cell::RefCell<crate::objects::actor::Actor>>,
    /*
    0x10c	0x4	int	prevState		int
    0x110	0x4	int	preventStateChanges		int
    0x114	0x4	int	loadedCutscene		int
    0x118	0x4	actor *	actor		actor *
    0x11c	0x4	int			int
    0x120	0x4	int			int
    */
    pub current_chapter: u32,
    /*
    0x128	0x4	int	currentScene		int
    0x12c	0x4	int			int
    0x130	0x4	int			int
    0x134	0x4	int			int
    0x138	0x4	int			int
    0x13c	0x4	int			int
    0x140	0x4	int			int
    0x144	0x4	int			int
    0x148	0x4	int			int
    0x14c	0x4	int			int
    0x150	0x4	int			int
    0x154	0x4	int			int
    0x158	0x4	int	somethingState		int
    0x15c	0x4	undefined *32			addr
    0x160	0x4	int			int
    0x164	0x4	int			int
    0x168	0x4	int			int
    0x16c	0x4	int			int
    0x170	0x4	int			int
    0x174	0x4	int			int
    0x178	0x4	int			int
    0x17c	0x4	int			int
    0x180	0x4	int			int
    0x184	0x4	int			int
    0x188	0x4	int			int
    0x18c	0x4	int			int
    0x190	0x4	int			int
    0x194	0x4	int			int
    0x198	0x4	int			int
    0x19c	0x4	int			int
    0x1a0	0x4	int			int
    0x1a4	0x4	int			int
    0x1a8	0x4	int			int
    0x1ac	0x4	int			int
    0x1b0	0x4	int			int
    0x1b4	0x4	int			int
    0x1b8	0x4	int			int
    0x1bc	0x4	int			int
    0x1c0	0x4	int			int
    0x1c4	0x4	int			int
    0x1c8	0x4	int			int
    0x1cc	0x4	int			int
    0x1d0	0x4	int			int
    0x1d4	0x4	int			int
    0x1d8	0x4	int			int
    0x1dc	0x4	int			int
    0x1e0	0x4	int			int
    0x1e4	0x4	int			int
    0x1e8	0x4	int			int
    0x1ec	0x4	int			int
    0x1f0	0x4	int			int
    0x1f4	0x4	int			int
    0x1f8	0x4	int			int
    0x1fc	0x4	int			int
    0x200	0x4	int			int
    0x204	0x4	int			int
    0x208	0x4	int			int
    0x20c	0x1	undefined			??
    0x20d	0x1	undefined			??
    0x20e	0x1	undefined			??
    0x20f	0x4	int			int
    0x213	0x4	int			int
    0x217	0x4	int			int
    0x21b	0x4	int			int
    0x21f	0x4	int			int
    0x223	0x4	int			int
    0x227	0x4	int			int
    0x22b	0x4	InputHandlerType4 *			InputHandlerType4 *
    0x22f	0x4	InputHandlerType4 *	loctext?		InputHandlerType4 *
    0x233	0x1	undefined			??
    0x234	0x4	MarkerInstance *	markerInstance		MarkerInstance *
    0x238	0x1	undefined			??
    0x239	0x1	undefined			??
    0x23a	0x1	undefined			??
    0x23b	0x4	AssetGroup *	assetGroup		AssetGroup *
    0x23f	0x4	TwoPositions *	heapMem1		TwoPositions *
    0x243	0x4	int			int
    0x247	0x4	D3DResource *			D3DResource *
    0x24b	0x4	D3DResource *	d3dr1		D3DResource *
    0x24f	0x4	D3DResource *	d3dr2		D3DResource *
    0x253	0x4	D3DResource *	d3dr3		D3DResource *
    0x257	0x4	D3DResource *	d3dr4		D3DResource *
    0x25b	0x4	typedef BOOL int	renderingEnabled		BOOL
    0x25f	0x4	int			int
    0x263	0x4	int			int
    0x267	0x4	int			int
    0x26b	0x4	int			int
    0x26f	0x4	int			int
    0x273	0x4	int			int
    0x277	0x4	int			int
    0x27b	0x4	int			int
    0x27f	0x4	int			int
    0x283	0x4	int			int
    0x287	0x4	int			int
    0x28b	0x4	int			int
    0x28f	0x4	int			int
    0x293	0x1	char			char
    0x294	0x4	int			int
    0x298	0x4	int			int
    0x29c	0x4	int			int
    0x2a0	0x4	int			int
    0x2a4	0x4	int			int
    0x2a8	0x4	int			int
    0x2ac	0x4	int			int
    0x2b0	0x4	int			int
    0x2b4	0x4	int			int
    0x2b8	0x4	int			int
    0x2bc	0x4	int			int
    0x2c0	0x4	int			int
    0x2c4	0x4	int			int
    0x2c8	0x4	int			int
    0x2cc	0x4	int			int
    0x2d0	0x4	int			int
    0x2d4	0x4	int			int
    0x2d8	0x4	int			int
    0x2dc	0x4	int			int
    0x2e0	0x4	int			int
    0x2e4	0x4	int			int
    0x2e8	0x4	int			int
    0x2ec	0x4	int			int
    0x2f0	0x4	int			int
    0x2f4	0x4	int			int
    0x2f8	0x4	int			int
    0x2fc	0x4	int			int
    0x300	0x4	int			int
    0x304	0x1	undefined			??
    0x305	0x1	undefined			??
        */
    pub current_playcam_script_header: Option<XBEScriptHeader>,
}

impl Default for GameState {
    fn default() -> Self {
        Self {
            current_script_aid: String::default(),
            new_script_aid: None,
            new_script_state: Default::default(),
            load_state: LoadState::Null,
            new_load_state: None,
            prev_load_state: LoadState::default(),
            prevent_loading: false,
            transition_finished: false,
            // TODO: Figure out default current chapter
            current_chapter: 0,
            current_playcam_script_header: None,
        }
    }
}
