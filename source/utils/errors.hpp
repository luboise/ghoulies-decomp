#pragma once

#include <expected>
#include <optional>
#include <stdexcept>
#include <string>

namespace utils::errors
{

constexpr const char* kNoValueError = "No value in optional.";
constexpr const char* kOffsetOutOfBounds = "Offset is out of bounds.";

using VoidResult = std::expected<void, std::string>;

template<typename T, typename E>
T OrThrow(std::expected<T, E>&& exp)
{
  if (exp.has_value()) {
    return std::move(exp).value();
  }

  throw std::runtime_error(exp.error());
}

template<typename T>
T OrThrow(std::optional<T>&& opt)
{
  if (opt.has_value()) {
    return std::move(opt).value();
  }

  throw std::runtime_error(kNoValueError);
}

template<typename T, typename E>
std::expected<T, E> OrError(std::optional<T>&& opt,
                            E&& err = std::string("No value in optional."))
{
  if (opt.has_value()) {
    return std::move(opt).value();
  }

  return std::unexpected(std::forward<E>(err));
}

}  // namespace utils::errors
