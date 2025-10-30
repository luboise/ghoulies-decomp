#include <expected>
#include <utility>

#include "nd.hpp"

template<typename T>
void update_pointer(T*& ptr, void* base)
{
  ptr = (T*)((int64_t)ptr + (int64_t)base);
}

namespace ghoulies
{
std::expected<ghoulies::ModelDescriptor, std::string>
ModelDescriptor::FromBytes(std::span<uint8_t> bytes)
{
  void* descriptor_base {bytes.data()};

  auto* descriptor {reinterpret_cast<ModelDescriptor*>(bytes.data())};

  update_pointer(descriptor->footer_entries, descriptor_base);

  return ModelDescriptor {descriptor, bytes};
}

}  // namespace ghoulies
