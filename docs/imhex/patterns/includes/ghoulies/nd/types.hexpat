#pragma once

struct NdPtr<T>
{
  s128 model_root = parent.model_root;

  u32 ptr;

  if (ptr != 0) {
    T val @model_root + ptr;
  }
};
