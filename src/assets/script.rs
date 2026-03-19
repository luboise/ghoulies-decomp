pub fn bnl_name_from_asset_name(asset_name: &str) -> Result<String, crate::Error> {
    let substr_start = if asset_name.starts_with("aid_script_") {
        "aid_script_".len()
    } else {
        0
    };

    if substr_start >= asset_name.len() {
        return Err(
            format!("Invalid asset name to bnl name conversion on string {asset_name}").into(),
        );
    }

    Ok(format!("{}.bnl", &asset_name[substr_start..]))
}
