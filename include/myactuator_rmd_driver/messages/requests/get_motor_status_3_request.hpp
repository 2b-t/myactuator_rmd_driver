/**
 * \file get_motor_status_3_request.hpp
 * \mainpage
 *    Request for reading the motor status
 * \author
 *    Tobit Flatscher (github.com/2b-t)
*/

#ifndef MYACTUATOR_RMD_DRIVER__MESSAGES__REQUESTS__GET_MOTOR_STATUS_3_REQUEST
#define MYACTUATOR_RMD_DRIVER__MESSAGES__REQUESTS__GET_MOTOR_STATUS_3_REQUEST
#pragma once

#include "myactuator_rmd_driver/messages/definitions.hpp"
#include "myactuator_rmd_driver/messages/request.hpp"


namespace myactuator_rmd_driver {

  /**\class GetMotorStatus3Request
   * \brief
   *    Request for reading the motor status
  */
  class GetMotorStatus3Request: public Request<CommandType::READ_MOTOR_STATUS_3> {
    public:
      /**\fn GetMotorStatus3Request
       * \brief
       *    Class constructor
      */
      constexpr GetMotorStatus3Request();
      GetMotorStatus3Request(GetMotorStatus3Request const&) = default;
      GetMotorStatus3Request& operator = (GetMotorStatus3Request const&) = default;
      GetMotorStatus3Request(GetMotorStatus3Request&&) = default;
      GetMotorStatus3Request& operator = (GetMotorStatus3Request&&) = default;
  };

  constexpr GetMotorStatus3Request::GetMotorStatus3Request()
  : Request{} {
    return;
  }

}

#endif // MYACTUATOR_RMD_DRIVER__MESSAGES__REQUESTS__GET_MOTOR_STATUS_3_REQUEST
