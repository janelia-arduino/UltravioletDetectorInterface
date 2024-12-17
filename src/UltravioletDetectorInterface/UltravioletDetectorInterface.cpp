// ----------------------------------------------------------------------------
// UltravioletDetectorInterface.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "UltravioletDetectorInterface.h"


using namespace ultraviolet_detector_interface;

UltravioletDetectorInterface::UltravioletDetectorInterface()
{
}

void UltravioletDetectorInterface::setup()
{
  // Parent Setup
  SerialInterface::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup
  error_ptr_ = &constants::no_error;

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins
  modular_server::Pin & btn_a_pin = modular_server_.pin(modular_device_base::constants::btn_a_pin_name);

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

  modular_server::Property & write_line_endings_property = modular_server_.property(serial_interface::constants::write_line_endings_property_name);
  write_line_endings_property.setDefaultValue(constants::line_endings_default);
  write_line_endings_property.setSubset(constants::line_ending_ptr_subset);

  modular_server::Property & read_line_endings_property = modular_server_.property(serial_interface::constants::read_line_endings_property_name);
  read_line_endings_property.setDefaultValue(constants::line_endings_default);
  read_line_endings_property.setSubset(constants::line_ending_ptr_subset);

  modular_server::Property & timeouts_property = modular_server_.property(serial_interface::constants::timeouts_property_name);
  timeouts_property.setDefaultValue(constants::timeouts_default);

  // Parameters
  modular_server::Parameter & wavelengths_parameter = modular_server_.createParameter(constants::wavelengths_parameter_name);
  wavelengths_parameter.setRange(constants::wavelength_min,constants::wavelength_max);
  wavelengths_parameter.setArrayLengthRange(constants::CHANNEL_COUNT_MAX,constants::CHANNEL_COUNT_MAX);

  // Functions
  modular_server::Function & get_detector_info_function = modular_server_.createFunction(constants::get_detector_info_function_name);
  get_detector_info_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::getDetectorInfoHandler));
  get_detector_info_function.setResultTypeObject();

  modular_server::Function & get_status_function = modular_server_.createFunction(constants::get_status_function_name);
  get_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::getStatusHandler));
  get_status_function.setResultTypeString();

  modular_server::Function & lamp_is_on_function = modular_server_.createFunction(constants::lamp_is_on_function_name);
  lamp_is_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::lampIsOnHandler));
  lamp_is_on_function.setResultTypeBool();

  modular_server::Function & is_autozeroing_function = modular_server_.createFunction(constants::is_autozeroing_function_name);
  is_autozeroing_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::isAutozeroingHandler));
  is_autozeroing_function.setResultTypeBool();

  modular_server::Function & get_wavelength_range_function = modular_server_.createFunction(constants::get_wavelength_range_function_name);
  get_wavelength_range_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::getWavelengthRangeHandler));
  get_wavelength_range_function.setResultTypeLong();
  get_wavelength_range_function.setResultTypeArray();

  modular_server::Function & get_wavelengths_function = modular_server_.createFunction(constants::get_wavelengths_function_name);
  get_wavelengths_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::getWavelengthsHandler));
  get_wavelengths_function.setResultTypeLong();
  get_wavelengths_function.setResultTypeArray();

  modular_server::Function & set_wavelengths_function = modular_server_.createFunction(constants::set_wavelengths_function_name);
  set_wavelengths_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::setWavelengthsHandler));
  set_wavelengths_function.addParameter(wavelengths_parameter);

  modular_server::Function & get_absorbances_function = modular_server_.createFunction(constants::get_absorbances_function_name);
  get_absorbances_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&UltravioletDetectorInterface::getAbsorbancesHandler));
  get_absorbances_function.setResultTypeDouble();
  get_absorbances_function.setResultTypeArray();

  // Callbacks
  modular_server::Callback & turn_lamp_on_callback = modular_server_.createCallback(constants::turn_lamp_on_callback_name);
  turn_lamp_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&UltravioletDetectorInterface::turnLampOnHandler));

  modular_server::Callback & turn_lamp_off_callback = modular_server_.createCallback(constants::turn_lamp_off_callback_name);
  turn_lamp_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&UltravioletDetectorInterface::turnLampOffHandler));

  modular_server::Callback & autozero_callback = modular_server_.createCallback(constants::autozero_callback_name);
  autozero_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&UltravioletDetectorInterface::autozeroHandler));

  modular_server::Callback & play_short_tone_callback = modular_server_.createCallback(constants::play_short_tone_callback_name);
  play_short_tone_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&UltravioletDetectorInterface::playShortToneHandler));

  modular_server::Callback & play_medium_tone_callback = modular_server_.createCallback(constants::play_medium_tone_callback_name);
  play_medium_tone_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&UltravioletDetectorInterface::playMediumToneHandler));
  play_medium_tone_callback.attachTo(btn_a_pin,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & play_long_tone_callback = modular_server_.createCallback(constants::play_long_tone_callback_name);
  play_long_tone_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&UltravioletDetectorInterface::playLongToneHandler));

}

bool UltravioletDetectorInterface::communicating()
{
  char * detector_name = NULL;
  return getDetectorName(detector_name);
}

bool UltravioletDetectorInterface::getDetectorName(char * & detector_name)
{
  detector_name = response_data_;
  const char command[] = "DTr";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::getHardwareVersion(char * & hardware_version)
{
  hardware_version = response_data_;
  const char command[] = "HWr";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::getModel(char * & model)
{
  model = response_data_;
  const char command[] = "MDr";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::getFirmwareVersion(char * & firmware_version)
{
  firmware_version = response_data_;
  const char command[] = "SWr";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::getSerialNumber(char * & serial_number)
{
  serial_number = response_data_;
  const char command[] = "SNr";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::getStatus(Status & status,
  char * const & hardware_error)
{
  const char command[] = "STr";
  bool success = sendCommandGetResponse(command);
  if (!success)
  {
    return success;
  }
  char status_str[constants::STATUS_BUFFER_SIZE];
  memset(status_str,0,constants::STATUS_BUFFER_SIZE);
  strncpy(status_str,(response_data_ + constants::STATUS_OFFSET),constants::STATUS_SIZE);
  status = static_cast<Status>(atoi(status_str));
  memset(hardware_error,0,constants::HARDWARE_ERROR_BUFFER_SIZE);
  strncpy(hardware_error,(response_data_ + constants::HARDWARE_ERROR_OFFSET),constants::HARDWARE_ERROR_SIZE);
  return success;
}

const ConstantString & UltravioletDetectorInterface::getCommunicationError()
{
  if (error_ptr_ == NULL)
  {
    return constants::no_error;
  }
  return *error_ptr_;
}

bool UltravioletDetectorInterface::lampIsOn(bool & lamp_is_on)
{
  lamp_is_on = false;
  const char command[] = "LPr";
  bool success = sendCommandGetResponse(command);
  if (!success)
  {
    return success;
  }
  lamp_is_on = (strcmp("T",response_data_) == 0);
  return success;
}

bool UltravioletDetectorInterface::turnLampOn()
{
  const char command[] = "LPwT";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::turnLampOff()
{
  const char command[] = "LPwF";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::autozero()
{
  const char command[] = "ZRw";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::isAutozeroing(bool & is_autozeroing)
{
  is_autozeroing = false;
  const char command[] = "ZRr";
  bool success = sendCommandGetResponse(command);
  if (!success)
  {
    return success;
  }
  is_autozeroing = (strcmp("T",response_data_) == 0);
  return success;
}

bool UltravioletDetectorInterface::playShortTone()
{
  const char command[] = "SGw1";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::playMediumTone()
{
  const char command[] = "SGw2";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::playLongTone()
{
  const char command[] = "SGw3";
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::getWavelengthRange(WavelengthArray & range)
{
  const char command[] = "WRr";
  bool success = sendCommandGetResponse(command);
  if (!success)
  {
    return success;
  }
  char wavelength_str[constants::WAVELENGTH_BUFFER_SIZE];
  size_t wavelength;
  size_t offset;
  range.clear();
  for (size_t range_index=0; range_index<constants::RANGE_SIZE; ++range_index)
  {
    memset(wavelength_str,0,constants::WAVELENGTH_BUFFER_SIZE);
    offset = range_index * (constants::WAVELENGTH_SIZE + constants::WAVELENGTH_OFFSET) + constants::WAVELENGTH_OFFSET;
    strncpy(wavelength_str,(response_data_ + offset),constants::WAVELENGTH_SIZE);
    wavelength = atoi(wavelength_str);
    range.push_back(wavelength);
  }
  return success;
}

bool UltravioletDetectorInterface::getWavelengths(WavelengthArray & wavelengths)
{
  const char command[] = "WLr";
  bool success = sendCommandGetResponse(command);
  if (!success)
  {
    return success;
  }
  char wavelength_str[constants::WAVELENGTH_BUFFER_SIZE];
  size_t wavelength;
  size_t offset;
  wavelengths.clear();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT_MAX; ++channel)
  {
    memset(wavelength_str,0,constants::WAVELENGTH_BUFFER_SIZE);
    offset = channel * (constants::WAVELENGTH_SIZE + constants::WAVELENGTH_OFFSET) + constants::WAVELENGTH_OFFSET;
    strncpy(wavelength_str,(response_data_ + offset),constants::WAVELENGTH_SIZE);
    wavelength = atoi(wavelength_str);
    wavelengths.push_back(wavelength);
  }
  return success;
}

bool UltravioletDetectorInterface::setWavelengths(const WavelengthArray & wavelengths)
{
  char command[] = "WLwAnnnBnnnCnnnDnnn";
  char wavelength_str[constants::WAVELENGTH_BUFFER_SIZE];
  size_t offset;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT_MAX; ++channel)
  {
    sprintf(wavelength_str,"%03d",wavelengths[channel]);
    offset = constants::KEY_SIZE + channel * (constants::WAVELENGTH_SIZE + constants::WAVELENGTH_OFFSET) + constants::WAVELENGTH_OFFSET;
    strncpy((command + offset),wavelength_str,constants::WAVELENGTH_SIZE);
  }
  bool success = sendCommandGetResponse(command);
  return success;
}

bool UltravioletDetectorInterface::getAbsorbances(AbsorbanceArray & absorbances)
{
  const char command[] = "ABr";
  bool success = sendCommandGetResponse(command);
  if (!success)
  {
    return success;
  }
  // bool success = true;
  // const char test[] = "A+040050:0B-000028:0C+088000:0D+120400:0";
  char absorbance_str[constants::ABSORBANCE_BUFFER_SIZE];
  double absorbance;
  size_t offset;
  char * end;
  absorbances.clear();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT_MAX; ++channel)
  {
    memset(absorbance_str,0,constants::ABSORBANCE_BUFFER_SIZE);
    offset = channel * (constants::ABSORBANCE_SIZE + constants::ABSORBANCE_OFFSET + constants::ABSORBANCE_TAIL_SIZE) + constants::ABSORBANCE_OFFSET;
    strncpy(absorbance_str,(response_data_ + offset),constants::ABSORBANCE_SIZE);
    // strncpy(absorbance_str,(test + offset),constants::ABSORBANCE_SIZE);
    absorbance = strtol(absorbance_str,&end,constants::absorbance_base);
    absorbance = absorbance / constants::absorbance_divisor;
    absorbances.push_back(absorbance);
  }
  return success;
}

bool UltravioletDetectorInterface::sendCommandGetResponse(const char command[])
{
  initializeRequestAndResponse();
  strcat(request_,constants::line_beginning);
  strcat(request_,command);
  writeRead(request_,response_,constants::RESPONSE_SIZE_MAX);
  strncpy(request_key_,command,constants::KEY_SIZE);
  strncpy(response_key_,response_,constants::KEY_SIZE);
  // Serial << "command = " << command << "\n";
  // Serial << "request_ = " << request_ << "\n";
  // Serial << "request_key_ = " << request_key_ << "\n";
  // Serial << "response_ = " << response_ << "\n";
  // Serial << "response_key_ = " << response_key_ << "\n";
  // Serial << "response_data_ = " << response_data_ << "\n";
  bool success = false;
  error_ptr_ = &constants::no_error;
  if (strcmp("???",response_key_) == 0)
  {
    error_ptr_ = &constants::invalid_command_error;
  }
  else if (strcmp(request_key_,response_key_) != 0)
  {
    error_ptr_ = &constants::not_communicating_error;
  }
  else if (strcmp("ERR2",response_data_) == 0)
  {
    error_ptr_ = &constants::invalid_parameter_error;
  }
  else if (strcmp("ERR4",response_data_) == 0)
  {
    error_ptr_ = &constants::invalid_mode_error;
  }
  else if (strcmp("ERR5",response_data_) == 0)
  {
    error_ptr_ = &constants::operation_error;
  }
  else
  {
    success = true;
  }
  return success;
}

size_t UltravioletDetectorInterface::getResponseLength()
{
  return strlen(response_);
}

void UltravioletDetectorInterface::initializeRequestAndResponse()
{
  request_[0] = '\0';
  request_key_[0] = '\0';
  response_[0] = '\0';
  response_key_[0] = '\0';
  response_data_[0] = '\0';
}

void UltravioletDetectorInterface::getDetectorInfoHandler()
{
  if (!communicating())
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }
  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  char * response_data = NULL;

  getDetectorName(response_data);
  modular_server_.response().write(constants::detector_name_constant_string,response_data);

  getHardwareVersion(response_data);
  modular_server_.response().write(constants::hardware_version_constant_string,response_data);

  getModel(response_data);
  modular_server_.response().write(constants::model_constant_string,response_data);

  getFirmwareVersion(response_data);
  modular_server_.response().write(constants::firmware_version_constant_string,response_data);

  getSerialNumber(response_data);
  modular_server_.response().write(constants::serial_number_constant_string,response_data);

  modular_server_.response().endObject();
}

void UltravioletDetectorInterface::getStatusHandler()
{
  Status status;
  char hardware_error[constants::HARDWARE_ERROR_BUFFER_SIZE];
  bool success = getStatus(status,hardware_error);
  if (!success)
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }

  ConstantString * status_ptr = NULL;
  switch (status)
  {
    case STANDBY:
    {
      status_ptr = &constants::status_standby_constant_string;
      break;
    }
    case LAMP_IGNITION:
    {
      status_ptr = &constants::status_lamp_ignition_constant_string;
      break;
    }
    case MEASUREMENT:
    {
      status_ptr = &constants::status_measurement_constant_string;
      break;
    }
    case AUTOZERO:
    {
      status_ptr = &constants::status_autozero_constant_string;
      break;
    }
    case SCAN_ABS:
    {
      status_ptr = &constants::status_scan_abs_constant_string;
      break;
    }
    case SCAN_ITS:
    {
      status_ptr = &constants::status_scan_its_constant_string;
      break;
    }
    case USER_CALIB:
    {
      status_ptr = &constants::status_user_calib_constant_string;
      break;
    }
    case SELF_TEST:
    {
      status_ptr = &constants::status_self_test_constant_string;
      break;
    }
    case SCAN_ABS_SUBS:
    {
      status_ptr = &constants::status_scan_abs_subs_constant_string;
      break;
    }
  }
  if (strcmp("00000000",hardware_error) == 0)
  {
    modular_server_.response().returnResult(status_ptr);
  }
  else
  {
    modular_server_.response().returnResult(hardware_error);
  }
}

void UltravioletDetectorInterface::lampIsOnHandler()
{
  bool lamp_is_on;
  bool success = lampIsOn(lamp_is_on);
  if (!success)
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }
  modular_server_.response().returnResult(lamp_is_on);
}

void UltravioletDetectorInterface::turnLampOnHandler(modular_server::Pin * pin_ptr)
{
  turnLampOn();
}

void UltravioletDetectorInterface::turnLampOffHandler(modular_server::Pin * pin_ptr)
{
  turnLampOff();
}

void UltravioletDetectorInterface::autozeroHandler(modular_server::Pin * pin_ptr)
{
  autozero();
}

void UltravioletDetectorInterface::isAutozeroingHandler()
{
  bool is_autozeroing;
  bool success = isAutozeroing(is_autozeroing);
  if (!success)
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }
  modular_server_.response().returnResult(is_autozeroing);
}

void UltravioletDetectorInterface::playShortToneHandler(modular_server::Pin * pin_ptr)
{
  playShortTone();
}

void UltravioletDetectorInterface::playMediumToneHandler(modular_server::Pin * pin_ptr)
{
  playMediumTone();
}

void UltravioletDetectorInterface::playLongToneHandler(modular_server::Pin * pin_ptr)
{
  playLongTone();
}

void UltravioletDetectorInterface::getWavelengthRangeHandler()
{
  WavelengthArray range;
  bool success = getWavelengthRange(range);
  if (!success)
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }
  modular_server_.response().returnResult(range);
}

void UltravioletDetectorInterface::getWavelengthsHandler()
{
  WavelengthArray wavelengths;
  bool success = getWavelengths(wavelengths);
  if (!success)
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }
  modular_server_.response().returnResult(wavelengths);
}

void UltravioletDetectorInterface::setWavelengthsHandler()
{
  ArduinoJson::JsonArray wavelengths_ja;
  modular_server_.parameter(constants::wavelengths_parameter_name).getValue(wavelengths_ja);

  WavelengthArray wavelengths;
  for (long wavelength : wavelengths_ja)
  {
    wavelengths.push_back(wavelength);
  }
  bool success = setWavelengths(wavelengths);
  if (!success)
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }
}

void UltravioletDetectorInterface::getAbsorbancesHandler()
{
  AbsorbanceArray absorbances;
  bool success = getAbsorbances(absorbances);
  if (!success)
  {
    modular_server_.response().returnError(getCommunicationError());
    return;
  }
  modular_server_.response().returnResult(absorbances);
}
