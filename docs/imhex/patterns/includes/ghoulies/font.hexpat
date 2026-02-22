#pragma once

#include "ghoulies/types"
#include "ghoulies/nd/all"

struct FontEntry{
	u32 textureHeaderPtr;
	if (textureHeaderPtr != 0) {
		TEXTURE_HEADER tex @ parent.start + textureHeaderPtr;
	}

	u32 resourceSize;

	u32 c;
	u32 d;
	u32 e;
	u32 f;
};

struct FontDescriptor {
	s128 start = $;

	u32 startGlyph;
	u32 endGlyph;
	u32 texturesPerGlyph;
	u32 xOffset;
	u32 lineHeight;
	u32 entriesStart;

	if (entriesStart != 0) {
		FontEntry entries[endGlyph - startGlyph + 1] @ start + entriesStart;
	}
};


struct FontFile {
	AssetChunkInfo chunkInfo;
	FontDescriptor descriptor @ chunkInfo.descriptor_ptr;
};

