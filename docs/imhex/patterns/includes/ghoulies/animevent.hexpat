#pragma once

struct AnimEventEntry {
    s128 start = $;
    u32 size;
    
    float duration;
    
    u32 probablyHash;
    
    u32 eventType;
    
    s128 end = $;
    if ((end - start) < size) {
        u8 data[size-(end - start)];    
    }
};

