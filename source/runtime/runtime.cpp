#include "runtime/runtime.hpp"

float runtime::delta_time = {0.0F};
float runtime::dx_timer = {0.0F};
float runtime::time_scale = {1.0F};

std::uint32_t runtime::ticks_to_run {0};
float runtime::total_ticks_updated = {0.0F};
