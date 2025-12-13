#pragma once

#include <std/ptr>
#include <std/string>

struct LoctextKey
{
  u16 keyHash;
  u32 offset;
  std::string::NullString16 string @(parent.wCharsStart + offset * sizeof(u16));
};

struct LoctextMapHeader
{
  u32 mapStart;
  u32 numLoctexts;

  u32 wCharsStart = $ + (6 * numLoctexts) + sizeof(u16) + sizeof(u32);
  LoctextKey keys[numLoctexts];
  u16 endSentinel;
  u32 numChars;
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
  u32 values_ptr;

  u16 numSomethings;
  u16 idk2;
  u32 idk1;

  u32 keys_ptr;
  u32 idk3;
  u32 hashListPtr;

  LoctextMapHeader values @ptr_base + values_ptr;
  LoctextLocatorList keys @ptr_base + keys_ptr;
  LoctextHashList hashes @ptr_base + hashListPtr;
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
