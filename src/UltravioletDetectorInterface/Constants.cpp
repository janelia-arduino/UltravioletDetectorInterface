// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  .version_major=2,
  .version_minor=0,
  .version_patch=1,
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

CONSTANT_STRING(hardware_error_constant_string,"hardware_error");

const int absorbance_base = 10;
const double absorbance_divisor = 100;

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
const long wavelength_min = 200;
const long wavelength_max = 800;
CONSTANT_STRING(wavelengths_parameter_name,"wavelengths");

// Functions
CONSTANT_STRING(get_detector_info_function_name,"getDetectorInfo");
CONSTANT_STRING(get_status_function_name,"getStatus");
CONSTANT_STRING(lamp_is_on_function_name,"lampIsOn");
CONSTANT_STRING(is_autozeroing_function_name,"isAutozeroing");
CONSTANT_STRING(get_wavelength_range_function_name,"getWavelengthRange");
CONSTANT_STRING(get_wavelengths_function_name,"getWavelengths");
CONSTANT_STRING(set_wavelengths_function_name,"setWavelengths");
CONSTANT_STRING(get_absorbances_function_name,"getAbsorbances");

// Callbacks
CONSTANT_STRING(turn_lamp_on_callback_name,"turnLampOn");
CONSTANT_STRING(turn_lamp_off_callback_name,"turnLampOff");
CONSTANT_STRING(autozero_callback_name,"autozero");
CONSTANT_STRING(play_short_tone_callback_name,"playShortTone");
CONSTANT_STRING(play_medium_tone_callback_name,"playMediumTone");
CONSTANT_STRING(play_long_tone_callback_name,"playLongTone");

// Errors
CONSTANT_STRING(no_error,"No error.");
CONSTANT_STRING(not_communicating_error,"The detector is not communicating. Check power and connections.");
CONSTANT_STRING(invalid_command_error,"Invalid command. It does not exist or it has an invalid pattern.");
CONSTANT_STRING(invalid_parameter_error,"Value of parameter is out of range.");
CONSTANT_STRING(invalid_mode_error,"Invalid mode for applied command.");
CONSTANT_STRING(operation_error,"Operation end with error.");
}
}
