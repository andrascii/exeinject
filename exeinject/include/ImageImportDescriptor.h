#pragma once

namespace exe_inject {

struct ImageImportDescriptor {
  union {
    // 0 for terminating null import descriptor
    uint32_t characteristics;

    // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
    uint32_t original_first_thunk;
  };

  // 0 if not bound,
  // -1 if bound, and real date\time stamp
  // in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
  // O.W. date/time stamp of DLL bound to (Old BIND)
  uint32_t time_date_stamp;

  // -1 if no forwarders
  uint32_t forwarder_chain;
  uint32_t name;

  // RVA to IAT (if bound this IAT has actual addresses)
  uint32_t first_thunk;
};

}
