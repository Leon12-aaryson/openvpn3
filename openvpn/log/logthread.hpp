#ifndef OPENVPN_LOG_LOGTHREAD_H
#define OPENVPN_LOG_LOGTHREAD_H

#include <string>
#include <sstream>

#include <openvpn/common/types.hpp>
#include <openvpn/common/thread.hpp>

// Define these parameters before including this header:

// OPENVPN_LOG_CLASS -- client class that exposes a log() method
// OPENVPN_LOG_INFO  -- converts a log string to the form that should be passed to log()

# define OPENVPN_LOG(args) \
  do { \
    if (openvpn::Log::global_log != NULL) { \
      std::ostringstream _ovpn_log; \
      _ovpn_log << args << std::endl; \
      ((OPENVPN_LOG_CLASS*)openvpn::Log::global_log)->log(OPENVPN_LOG_INFO(_ovpn_log.str())); \
    } \
  } while (0)

// like OPENVPN_LOG but no trailing newline
#define OPENVPN_LOG_NTNL(args) \
  do { \
    if (openvpn::Log::global_log != NULL) { \
      std::ostringstream _ovpn_log; \
      _ovpn_log << args; \
      ((OPENVPN_LOG_CLASS*)openvpn::Log::global_log)->log(OPENVPN_LOG_INFO(_ovpn_log.str())); \
    } \
  } while (0)

namespace openvpn {
  namespace Log {

    boost::asio::detail::tss_ptr<OPENVPN_LOG_CLASS> global_log; // GLOBAL

    struct Context
    {
      Context(OPENVPN_LOG_CLASS *cli)
      {
	global_log = cli;
      }

      ~Context()
      {
	global_log = NULL;
      }
    };

  }
}

#endif
