#pragma once

#include <array>

namespace ghoulies
{

using AssetAID = std::array<char, 0x80>;

constexpr bool IsValidAssetAID(const AssetAID& aid)
{
  return aid[0] == 'a' && aid[1] == 'i' && aid[2] == 'd' && aid[3] == '_';
}

using AudioID = std::array<char, 0x80>;

template<typename T>
class Singleton
{
public:
  static T& Instance()
  {
    static T s {};
    return s;
  };

  Singleton() = default;

  Singleton(Singleton&&) = delete;
  ~Singleton() = default;

  Singleton& operator=(Singleton&&) = delete;
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton) = delete;
};

/** A linked list node embedded within another data structure.
 * eg. Background having an embedded linked list node to other backgrounds. **/
template<typename T>
struct Registry
{
  Registry<T>* next;
  Registry<T>* prev;

  void Register(Registry<T>* new_item)
  {
    auto tail {this};

    while (tail->next != nullptr) {
      tail = tail->next;
    }

    this->next = new_item;
    new_item->prev = tail;
  }
};

template<typename... Ts>
struct Overload : Ts...
{
  using Ts::operator()...;
};

template<typename T>
struct EmbeddedNode
{
  T prev;
  T next;
};

}  // namespace ghoulies
