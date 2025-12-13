enum StateId: u16{};

struct AID{
    char aid[0x80];
};


struct StatetableEntry {
    s128 start = $;
    
    StateId id;
    AID stateAID;
    AID moveAID;
    
    u8 unknown_1;
    u8 unknown_2;
    
    u32 animation_name_ptr;
    
    
    s128 end = $;
    
    // padding[0x108 - (end - start)];
};

struct StatetableResource {
    u32 numEntries;
    StatetableEntry entries[1];
};
