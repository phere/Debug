#include "phere/Logger.hpp"

namespace phere
{
  Logger::Logger()
  {}

  Logger::Logger(std::string name_)
	: name(name_)
  {}

  std::string Logger::get_name() const
  {
	return name;
  }
}
