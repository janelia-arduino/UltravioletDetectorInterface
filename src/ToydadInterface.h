// ----------------------------------------------------------------------------
// ToydadInterface.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef TOYDAD_INTERFACE_H
#define TOYDAD_INTERFACE_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <SerialInterface.h>

#include "ToydadInterface/Constants.h"


class ToydadInterface : public SerialInterface
{
public:
  ToydadInterface();
  virtual void setup();

  bool communicating();

  bool getDetectorName(char * & detector_name);
  bool getHardwareVersion(char * & hardware_version);
  bool getModel(char * & model);
  bool getFirmwareVersion(char * & firmware_version);
  bool getSerialNumber(char * & serial_number);

  enum Status
  {
    STANDBY = 0,
    LAMP_IGNITION = 1,
    MEASUREMENT = 2,
    AUTOZERO = 3,
    SCAN_ABS = 4,
    SCAN_ITS = 5,
    USER_CALIB = 6,
    SELF_TEST = 7,
    SCAN_ABS_SUBS = 9,
  };
  bool getStatus(Status & status);

  bool lampIsOn();
  bool turnLampOn();
  bool turnLampOff();

  bool playShortTone();
  bool playMediumTone();
  bool playLongTone();

  typedef Array<size_t,toydad_interface::constants::CHANNEL_COUNT_MAX> WavelengthArray;

private:
  modular_server::Property properties_[toydad_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[toydad_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[toydad_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[toydad_interface::constants::CALLBACK_COUNT_MAX];

  char request_[toydad_interface::constants::REQUEST_SIZE_MAX];
  char request_key_[toydad_interface::constants::KEY_BUFFER_SIZE];
  char response_[toydad_interface::constants::RESPONSE_SIZE_MAX];
  char response_key_[toydad_interface::constants::KEY_BUFFER_SIZE];
  char * const response_data_ = response_ + toydad_interface::constants::KEY_SIZE;

  bool sendCommandGetResponse(const char command[]);
  size_t getResponseLength();
  void initializeRequestAndResponse();

  // Handlers
  void getDetectorInfoHandler();
  void getStatusHandler();
  void lampIsOnHandler();
  void turnLampOnHandler();
  void turnLampOffHandler();
  void playShortToneHandler();
  void playMediumToneHandler();
  void playLongToneHandler();

};

#endif
