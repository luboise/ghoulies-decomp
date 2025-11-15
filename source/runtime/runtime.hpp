#pragma once

#include <algorithm>
#include <cstdint>

namespace runtime
{

extern float dx_timer;

/// The time between the current frame and the last frame
extern float delta_time;

/// The current speed of the game, typically 1.0x for normal gameplay.
extern float time_scale;

extern std::uint32_t ticks_to_run;
extern float total_ticks_updated;

/// Decrements a given timer by delta and time-scale. Returns true if the timer
/// just ended, false otherwise
inline bool DecrementTimerByDelta(float& timer)
{
  if (0.0F < timer) {
    timer = std::max(0.0F, timer - (runtime::delta_time * runtime::time_scale));
    return timer == 0.0F;
  }

  return false;
}

}  // namespace runtime
