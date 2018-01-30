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

CONSTANT_STRING(firmware_name,"ToydadInterface");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

const char * line_beginning = "#";

CONSTANT_STRING(detector_name_constant_string,"detector_name");
CONSTANT_STRING(hardware_version_constant_string,"hardware_version");
CONSTANT_STRING(model_constant_string,"model");
CONSTANT_STRING(firmware_version_constant_string,"firmware_version");
CONSTANT_STRING(serial_number_constant_string,"serial_number");

// Interrupts

// Units

// Properties
modular_server::SubsetMemberType baud_subset[BAUD_SUBSET_LENGTH] =
{
  {.l=57600},
  {.l=115200},
};
const long & baud_default = baud_subset[0].l;

modular_server::SubsetMemberType format_ptr_subset[FORMAT_SUBSET_LENGTH] =
{
  {.cs_ptr=&serial_interface::constants::format_8n1},
};
const ConstantString * const format_ptr_default = &serial_interface::constants::format_8n1;

modular_server::SubsetMemberType line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH] =
{
  {.cs_ptr=&serial_interface::constants::line_ending_lf},
};
const ConstantString * const line_ending_ptr_default = &serial_interface::constants::line_ending_lf;

// Parameters

// Functions
CONSTANT_STRING(get_detector_info_function_name,"getDetectorInfo");

// Callbacks

// Errors
}
}
