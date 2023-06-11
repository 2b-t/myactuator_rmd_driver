/**
 * \file get_motor_status_3_response.hpp
 * \mainpage
 *    Response to request for getting motor status
 * \author
 *    Tobit Flatscher (github.com/2b-t)
*/

#ifndef MYACTUATOR_RMD_DRIVER__MESSAGES__RESPONSES__GET_MOTOR_STATUS_3_RESPONSE
#define MYACTUATOR_RMD_DRIVER__MESSAGES__RESPONSES__GET_MOTOR_STATUS_3_RESPONSE
#pragma once

#include <array>
#include <cstdint>

#include "myactuator_rmd_driver/messages/definitions.hpp"
#include "myactuator_rmd_driver/messages/response.hpp"
#include "myactuator_rmd_driver/exceptions.hpp"
#include "myactuator_rmd_driver/motor_status_3.hpp"


namespace myactuator_rmd_driver {

  /**\class GetMotorStatus3Response
   * \brief
   *    Response to request for getting motor status
  */
  class GetMotorStatus3Response: public Response {
    public:
      /**\fn GetMotorStatus3Response
       * \brief
       *    Class constructor
       * 
       * \param[in] data
       *    The data to be transmitted to the driver
      */
      constexpr GetMotorStatus3Response(std::array<std::uint8_t,8> const& data);
      GetMotorStatus3Response() = delete;
      GetMotorStatus3Response(GetMotorStatus3Response const&) = default;
      GetMotorStatus3Response& operator = (GetMotorStatus3Response const&) = default;
      GetMotorStatus3Response(GetMotorStatus3Response&&) = default;
      GetMotorStatus3Response& operator = (GetMotorStatus3Response&&) = default;

      /**\fn getStatus
       * \brief
       *    Get the motor status
       * 
       * \return
       *    Motor status of the actuator
      */
      [[nodiscard]]
      MotorStatus3 getStatus() const noexcept;
  };

  constexpr GetMotorStatus3Response::GetMotorStatus3Response(std::array<std::uint8_t,8> const& data)
  : Response{data} {
    if (data[0] != CommandType::READ_MOTOR_STATUS_3) {
      throw ProtocolException("Unexpected response to get motor status 3 request!");
    }
    return;
  }

}

#endif // MYACTUATOR_RMD_DRIVER__MESSAGES__RESPONSES__GET_MOTOR_STATUS_3_RESPONSE
