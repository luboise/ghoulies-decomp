pub mod texture;

#[derive(Default)]
pub struct AssetDatabase {
    loaded_bnl_files: std::collections::HashMap<String, bnl::BNLFile>,
}

impl AssetDatabase {
    pub fn add_bnl(&mut self, name: &str, bnl: bnl::BNLFile) -> Result<(), crate::Error> {
        if self.loaded_bnl_files.contains_key(name) {
            return Err(format!("BNL with name {name} has already been loaded.").into());
        }

        self.loaded_bnl_files.insert(name.into(), bnl);
        Ok(())
    }

    pub fn remove_bnl(&mut self, name: &str) -> Result<(), crate::Error> {
        self.loaded_bnl_files
            .remove(name)
            .map(|_| ())
            .ok_or_else(|| {
                format!("BNL with name {name} can't be removed as it hasn't been loaded.").into()
            })
    }

    pub fn get_asset<A: bnl::asset::AssetLike>(&self, name: &str) -> Option<bnl::asset::Asset<A>> {
        self.loaded_bnl_files
            .values()
            .find_map(|bnl| bnl.get_asset::<A>(name).ok())
    }

    #[expect(unused)]
    pub fn loaded_bnl_files(&self) -> &std::collections::HashMap<String, bnl::BNLFile> {
        &self.loaded_bnl_files
    }
}
