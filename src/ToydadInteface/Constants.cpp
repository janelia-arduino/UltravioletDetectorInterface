// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace toydad_interface
{
namespace constants
{
CONSTANT_STRING(device_name,"toydad_interface");

CONSTANT_STRING(firmware_name,"ToydadInteface");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

// Interrupts

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}
