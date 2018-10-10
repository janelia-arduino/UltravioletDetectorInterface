// ----------------------------------------------------------------------------
// UltravioletDetectorInterface.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef ULTRAVIOLET_DETECTOR_INTERFACE_H
#define ULTRAVIOLET_DETECTOR_INTERFACE_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <SerialInterface.h>

#include "UltravioletDetectorInterface/Constants.h"


class UltravioletDetectorInterface : public SerialInterface
{
public:
  UltravioletDetectorInterface();
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

  typedef Array<size_t,ultraviolet_detector_interface::constants::CHANNEL_COUNT_MAX> WavelengthArray;

private:
  modular_server::Property properties_[ultraviolet_detector_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[ultraviolet_detector_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[ultraviolet_detector_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[ultraviolet_detector_interface::constants::CALLBACK_COUNT_MAX];

  char request_[ultraviolet_detector_interface::constants::REQUEST_SIZE_MAX];
  char request_key_[ultraviolet_detector_interface::constants::KEY_BUFFER_SIZE];
  char response_[ultraviolet_detector_interface::constants::RESPONSE_SIZE_MAX];
  char response_key_[ultraviolet_detector_interface::constants::KEY_BUFFER_SIZE];
  char * const response_data_ = response_ + ultraviolet_detector_interface::constants::KEY_SIZE;

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
