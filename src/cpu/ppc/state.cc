/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <xenia/common.h>
#include <xenia/core.h>
#include <xenia/cpu/ppc/state.h>


namespace {

uint64_t ParseInt64(const char* value) {
  return xestrtoulla(value, NULL, 0);
}

}

void xe_ppc_state::SetRegFromString(const char* name, const char* value) {
  int n;
  if (sscanf(name, "r%d", &n) == 1) {
    this->r[n] = ParseInt64(value);
  } else {
    printf("Unrecognized register name: %s\n", name);
  }
}

bool xe_ppc_state::CompareRegWithString(
    const char* name, const char* value,
    char* out_value, size_t out_value_size) {
  int n;
  if (sscanf(name, "r%d", &n) == 1) {
    uint64_t expected = ParseInt64(value);
    if (this->r[n] != expected) {
      xesnprintfa(out_value, out_value_size, "%016llX", this->r[n]);
      return false;
    }
    return true;
  } else {
    printf("Unrecognized register name: %s\n", name);
    return false;
  }
}
