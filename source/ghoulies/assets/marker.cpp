#include <cstring>
#include <iostream>

#include "marker.hpp"

namespace ghoulies
{

Marker::Marker(const Asset& asset)
{
  std::vector<MarkerEntry> marker_entries;

  MarkerHeader header {};

  if (asset.descriptor.size() < sizeof(MarkerHeader)) {
    throw std::runtime_error(std::format(
        "Unable to create marker from descriptor with size less than {} bytes.",
        sizeof(MarkerHeader)));
  }

  std::size_t curr {0};

  std::memcpy(
      static_cast<void*>(&header), &asset.descriptor[0], sizeof(MarkerHeader));

  do {
    Bytes data;

    if (header.size > sizeof(MarkerHeader)) {
      if (header.marker_type == MarkerType::Weapon) {
        if (header.size != sizeof(WeaponMarker)) {
          throw std::runtime_error(std::
                                       format("Mismatch between declared "
                                              "header " "size " "{} and " "actu"
                                                                          "al" " " "si" "ze" " " "of a " "weapon " "marker {}.",
                                              header.size,
                                              sizeof(WeaponMarker)));
        }

        WeaponMarker weapon_marker {};

        std::memcpy(static_cast<void*>(&weapon_marker),
                    &asset.descriptor[curr],
                    sizeof(WeaponMarker));

        marker_entries.emplace_back(weapon_marker);
      }

      std::size_t data_size {header.size - sizeof(MarkerHeader)};
      data.resize(data_size);

      if (curr + sizeof(MarkerHeader) > asset.descriptor.size()) {
        throw std::runtime_error(
            std::format(
                "Marker read from bytes {} to {} " "is " "invalid for " "descri" "pto" "r" " " "of " "size" " {}" ".",
                curr + sizeof(MarkerHeader),
                curr + header.size,
                asset.descriptor.size()));
      }

      std::memcpy(data.data(),
                  &asset.descriptor[curr + sizeof(MarkerHeader)],
                  data_size);

    } else {
      marker_entries.emplace_back(
          RawMarkerEntry {.header = header, .data = data});
    }

    curr += header.size;

    if (curr >= asset.descriptor.size()) {
      break;
    }

    std::memcpy(static_cast<void*>(&header),
                &asset.descriptor[curr],
                sizeof(MarkerHeader));

  } while (curr < asset.descriptor.size());

  this->entries_ = std::move(marker_entries);
}

}  // namespace ghoulies
