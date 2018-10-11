// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef ULTRAVIOLET_DETECTOR_INTERFACE_CONSTANTS_H
#define ULTRAVIOLET_DETECTOR_INTERFACE_CONSTANTS_H
#include <ConstantVariable.h>
#include <SerialInterface.h>


namespace ultraviolet_detector_interface
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=14};
enum{CALLBACK_COUNT_MAX=1};

enum{CHANNEL_COUNT_MAX=4};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

enum{REQUEST_SIZE_MAX=20};
enum{RESPONSE_SIZE_MAX=3000};
enum{KEY_SIZE=3};
enum{KEY_BUFFER_SIZE=4};
enum{STATUS_SIZE=2};
enum{STATUS_BUFFER_SIZE=3};
enum{STATUS_OFFSET=0};
enum{HARDWARE_ERROR_SIZE=8};
enum{HARDWARE_ERROR_BUFFER_SIZE=9};
enum{HARDWARE_ERROR_OFFSET=2};
enum{WAVELENGTH_SIZE=3};
enum{WAVELENGTH_BUFFER_SIZE=4};
enum{WAVELENGTH_OFFSET=1};
enum{RANGE_SIZE=2};
enum{ABSORBANCE_SIZE=7};
enum{ABSORBANCE_BUFFER_SIZE=8};
enum{ABSORBANCE_OFFSET=1};
enum{ABSORBANCE_TAIL_SIZE=2};

extern const char * line_beginning;

extern ConstantString detector_name_constant_string;
extern ConstantString hardware_version_constant_string;
extern ConstantString model_constant_string;
extern ConstantString firmware_version_constant_string;
extern ConstantString serial_number_constant_string;

extern ConstantString status_constant_string;
extern ConstantString status_standby_constant_string;
extern ConstantString status_lamp_ignition_constant_string;
extern ConstantString status_measurement_constant_string;
extern ConstantString status_autozero_constant_string;
extern ConstantString status_scan_abs_constant_string;
extern ConstantString status_scan_its_constant_string;
extern ConstantString status_user_calib_constant_string;
extern ConstantString status_self_test_constant_string;
extern ConstantString status_scan_abs_subs_constant_string;

extern ConstantString hardware_error_constant_string;

extern const int absorbance_base;
extern const double absorbance_divisor;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
enum{BAUD_SUBSET_LENGTH=2};
extern modular_server::SubsetMemberType baud_subset[BAUD_SUBSET_LENGTH];
extern const long & baud_default;

enum{FORMAT_SUBSET_LENGTH=1};
extern modular_server::SubsetMemberType format_ptr_subset[FORMAT_SUBSET_LENGTH];
extern const ConstantString * const format_ptr_default;

enum{LINE_ENDING_SUBSET_LENGTH=1};
extern modular_server::SubsetMemberType line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH];
extern const ConstantString * const line_ending_ptr_default;

extern const long timeout_default;

// Parameters
extern const long wavelength_min;
extern const long wavelength_max;
extern ConstantString wavelengths_parameter_name;

// Functions
extern ConstantString get_detector_info_function_name;
extern ConstantString get_status_function_name;
extern ConstantString lamp_is_on_function_name;
extern ConstantString turn_lamp_on_function_name;
extern ConstantString turn_lamp_off_function_name;
extern ConstantString autozero_function_name;
extern ConstantString is_autozeroing_function_name;
extern ConstantString play_short_tone_function_name;
extern ConstantString play_medium_tone_function_name;
extern ConstantString play_long_tone_function_name;
extern ConstantString get_wavelength_range_function_name;
extern ConstantString get_wavelengths_function_name;
extern ConstantString set_wavelengths_function_name;
extern ConstantString get_absorbances_function_name;

// Callbacks

// Errors
extern ConstantString no_error;
extern ConstantString not_communicating_error;
extern ConstantString invalid_command_error;
extern ConstantString invalid_parameter_error;
extern ConstantString invalid_mode_error;
extern ConstantString operation_error;
}
}
#include "5x3.h"
#include "3x2.h"
#endif
