#pragma once

#include <std/ptr>
#include <std/string>

struct LSBLEntry
{
  u16 keyHash;
  u32 offset;
  std::string::NullString16 string @(parent.bufStart + offset * sizeof(u16));
};

struct LSBLValues
{
  u32 sectionSize;
  u32 numValues;

  u32 bufStart = $ + (6 * numValues) + sizeof(u16) + sizeof(u32);
  LSBLEntry entries[numValues];
  u16 endSentinel;
  u32 bufLength;
};

struct LoctextHashList
{
  u32 size;
  u32 numHashes;
  u16 hashes[numHashes];
};

struct LoctextLocator
{
  u16 hash;
  u16 hashIndex;
  u32 charOffset;

  std::string::NullString key @(parent.locatorsStart + charOffset);
};

struct LoctextLocatorList
{
  u32 size;
  u32 numLocators;
  u32 locatorsStart = $ + 8 * numLocators;
  LoctextLocator locators[numLocators];
};

struct LSBLSection
{
  u32 ptr_base = $;
  char lsbl[4];
  u32 headerSize;

  u16 numSomethings;

  u16 idk2;

  u32 valuesPtr;
  if (valuesPtr != 0) {
    LSBLValues values @ptr_base + valuesPtr;
  }

  u32 keys_ptr;
  if (keys_ptr != 0) {
    LoctextLocatorList keys @ptr_base + keys_ptr;
  }

  u32 idk3;

  u32 hashListPtr;
  if (hashListPtr != 0) {
    LoctextHashList hashes @ptr_base + hashListPtr;
  }
};

struct LoctextDescriptor
{
  s128 start = $;
  u32 lsbl_ptr;
  u32 num_collisions;
  u32 collisions_start;

  if (lsbl_ptr != 0) {
    LSBLSection lsbl_section @start + lsbl_ptr;
  }
};
