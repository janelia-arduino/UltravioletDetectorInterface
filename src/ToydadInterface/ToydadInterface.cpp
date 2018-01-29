// ----------------------------------------------------------------------------
// ToydadInterface.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "../ToydadInterface.h"


using namespace toydad_interface;

ToydadInterface::ToydadInterface()
{
}

void ToydadInterface::setup()
{
  // Parent Setup
  SerialInterface::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & bauds_property = modular_server_.property(serial_interface::constants::bauds_property_name);
  bauds_property.setDefaultValue(constants::bauds_default);
  bauds_property.setSubset(constants::baud_subset);

  modular_server::Property & formats_property = modular_server_.property(serial_interface::constants::formats_property_name);
  formats_property.setDefaultValue(constants::formats_default);
  formats_property.setSubset(constants::format_ptr_subset);

  modular_server::Property & line_endings_property = modular_server_.property(serial_interface::constants::line_endings_property_name);
  line_endings_property.setDefaultValue(constants::line_endings_default);
  line_endings_property.setSubset(constants::line_ending_ptr_subset);

  // Parameters

  // Functions
  modular_server::Function & get_detector_info_function = modular_server_.createFunction(constants::get_detector_info_function_name);
  get_detector_info_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ToydadInterface::getDetectorInfoHandler));
  get_detector_info_function.setResultTypeObject();

  // Callbacks
}

bool ToydadInterface::getDetectorName(char detector_name[])
{
  const char key[constants::KEY_SIZE + 1] = "Dtr";
  sendCommandGetResponse(key);
}

bool ToydadInterface::sendCommandGetResponse(const char key[])
{
  const char data[constants::REQUEST_SIZE_MAX] = "";
  strcat(data,constants::line_beginning);
  strcat(data,key);
  writeRead(data,response_,constants::RESPONSE_SIZE_MAX);
}

size_t ToydadInterface::getResponseLength()
{
  return strlen(response_);
}

bool ToydadInterface::getResponseKey(char key[])
{
  if (getResponseLength() >= constants::KEY_SIZE)
  {
    key = response_;
  }
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void ToydadInterface::getDetectorInfoHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write("detector_name",response_);

  modular_server_.response().endObject();
}
