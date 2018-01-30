// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef TOYDAD_INTERFACE_CONSTANTS_H
#define TOYDAD_INTERFACE_CONSTANTS_H
#include <ConstantVariable.h>
#include <SerialInterface.h>


namespace toydad_interface
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

enum{REQUEST_SIZE_MAX=20};
enum{RESPONSE_SIZE_MAX=3000};
enum{KEY_SIZE=3};
enum{KEY_BUFFER_SIZE=4};

extern const char * line_beginning;

extern ConstantString detector_name_constant_string;
extern ConstantString hardware_version_constant_string;
extern ConstantString model_constant_string;
extern ConstantString firmware_version_constant_string;
extern ConstantString serial_number_constant_string;

// Interrupts

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

// Functions
extern ConstantString get_detector_info_function_name;

// Callbacks

// Errors
extern ConstantString not_communicating_error;
}
}
#include "5x3.h"
#include "3x2.h"
#endif
