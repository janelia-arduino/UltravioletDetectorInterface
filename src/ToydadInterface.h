// ----------------------------------------------------------------------------
// ToydadInterface.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef TOYDAD_INTERFACE_H
#define TOYDAD_INTERFACE_H
#include <Flash.h>
#include <EEPROM.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <JsonSanitizer.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <MemoryFree.h>
#include <ConstantVariable.h>
#include <SavedVariable.h>
#include <Functor.h>
#include <IndexedContainer.h>
#include <FunctorCallbacks.h>
#include <Watchdog.h>

#include <ModularClient.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <SerialInterface.h>

#include "ToydadInterface/Constants.h"


class ToydadInterface : public SerialInterface
{
public:
  ToydadInterface();
  virtual void setup();

  bool getDetectorName(char * & detector_name);
  bool getHardwareVersion(char * & hardware_version);
  bool getModel(char * & model);
  bool getFirmwareVersion(char * & firmware_version);
  bool getSerialNumber(char * & serial_number);

private:
  modular_server::Property properties_[toydad_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[toydad_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[toydad_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[toydad_interface::constants::CALLBACK_COUNT_MAX];

  char response_[toydad_interface::constants::RESPONSE_SIZE_MAX];
  char response_key_[toydad_interface::constants::KEY_BUFFER_SIZE];
  char * const response_data_ = response_ + toydad_interface::constants::KEY_SIZE;

  bool sendCommandGetResponse(const char key[]);
  size_t getResponseLength();
  void initializeResponse();

  // Handlers
  void getDetectorInfoHandler();

};

#endif
