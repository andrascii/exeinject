#pragma once

namespace exe_inject {

constexpr auto kImageDirectoryEntryExport = 0; // Export Directory
constexpr auto kImageDirectoryEntryImport = 1; // Import Directory
constexpr auto kImageDirectoryEntryResource = 2; // Resource Directory
constexpr auto kImageDirectoryEntryException = 3; // Exception Directory
constexpr auto kImageDirectoryEntrySecurity = 4; // Security Directory
constexpr auto kImageDirectoryEntryBaseReloc = 5; // Base Relocation Table
constexpr auto kImageDirectoryEntryDebug = 6; // Debug Directory
constexpr auto kImageDirectoryEntryCopyright = 7; // (X86 usage)
constexpr auto kImageDirectoryEntryArchitecture = 7; // Architecture Specific Data
constexpr auto kImageDirectoryEntryGlobalPtr = 8; // RVA of GP
constexpr auto kImageDirectoryEntryTls = 9; // TLS Directory
constexpr auto kImageDirectoryEntryLoadConfig = 10; // Load Configuration Directory
constexpr auto kImageDirectoryEntryBoundImport = 11; // Bound Import Directory in headers
constexpr auto kImageDirectoryEntryIat = 12; // Import Address Table
constexpr auto kImageDirectoryEntryDelayImport = 13; // Delay Load Import Descriptors
constexpr auto kImageDirectoryEntryComDescriptor = 14; // COM Runtime descriptor

constexpr auto kImageNumberOfDirectoryEntries = 16;

struct ImageDataDirectory {
  uint32_t virtual_address;
  uint32_t size;
};

}
