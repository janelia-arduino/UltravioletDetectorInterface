// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace ultraviolet_detector_interface
{
namespace constants
{
CONSTANT_STRING(device_name,"ultraviolet_detector_interface");

CONSTANT_STRING(firmware_name,"UltravioletDetectorInterface");
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

CONSTANT_STRING(status_constant_string,"status");
CONSTANT_STRING(status_standby_constant_string,"STANDBY");
CONSTANT_STRING(status_lamp_ignition_constant_string,"LAMP_IGNITION");
CONSTANT_STRING(status_measurement_constant_string,"MEASUREMENT");
CONSTANT_STRING(status_autozero_constant_string,"AUTOZERO");
CONSTANT_STRING(status_scan_abs_constant_string,"SCAN_ABS");
CONSTANT_STRING(status_scan_its_constant_string,"SCAN_ITS");
CONSTANT_STRING(status_user_calib_constant_string,"USER_CALIB");
CONSTANT_STRING(status_self_test_constant_string,"SELF_TEST");
CONSTANT_STRING(status_scan_abs_subs_constant_string,"SCAN_ABS_SUBS");

// Pins

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

const long timeout_default = 100;

// Parameters

// Functions
CONSTANT_STRING(get_detector_info_function_name,"getDetectorInfo");
CONSTANT_STRING(get_status_function_name,"getStatus");
CONSTANT_STRING(lamp_is_on_function_name,"lampIsOn");
CONSTANT_STRING(turn_lamp_on_function_name,"turnLampOn");
CONSTANT_STRING(turn_lamp_off_function_name,"turnLampOff");
CONSTANT_STRING(play_short_tone_function_name,"playShortTone");
CONSTANT_STRING(play_medium_tone_function_name,"playMediumTone");
CONSTANT_STRING(play_long_tone_function_name,"playLongTone");

// Callbacks

// Errors
CONSTANT_STRING(not_communicating_error,"The detector is not communicating. Check power and connections.");
}
}
