#include <cstdint>

class Nd
{
};

enum ModelSubresourceType : uint32_t
{
  kModel = 0,
  kUnknown0x2 = 2,
  kUnknown0x3 = 3,
  kMatrix = 5,
  kColliders = 6,
  kTexture = 7,
  kVertexBuffer = 18
};

class ModelSubresource
{
};

struct ModelFooterEntry
{
  ModelSubresourceType subresource_type;
  ModelSubresource* subresource;
};

struct ModelDescriptor
{
  struct ModelFooterEntry* footer_entries;
  int num_footer_entries;
  uint32_t field2_0x8;
  uint32_t field3_0xc;
  struct ModelRuntimeContext* runtime_ctx;
  uint32_t field5_0x14;
};
