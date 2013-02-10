#define BOOST_TEST_MODULE Debug
#include <boost/test/unit_test.hpp>

#include <phere/Logger.hpp>
#include <phere/LogWriters.hpp>
#include <phere/ConsoleWriter.hpp>

namespace
{
  struct LogWriterInit
  {
	phere::ConsoleWriter* logWriter;
	LogWriterInit()
	  : logWriter(NULL)
	{
	  logWriter = new phere::ConsoleWriter();
	  phere::LogWriters::add(logWriter);
	}

	~LogWriterInit()
	{
	  phere::LogWriters::remove(logWriter);
	  logWriter = NULL;
	}
  };
}

BOOST_GLOBAL_FIXTURE( LogWriterInit );

struct Custom
{
  int x;
  Custom(int x_) : x(x_) {}
};
Custom makeCustom()
{
  return Custom(12);
}

std::ostream& operator<<(std::ostream& os, Custom const& obj)
{
  os << "Custom(" << obj.x << ")";
  return os;
}

BOOST_AUTO_TEST_CASE( basic_usage )
{
  phere::Logger logger("usage");
  logger.debug("debug message");
  logger.info("info message (%1%)", "parameter");
  logger.warning("warning message");
  logger.error("error message");
}

BOOST_AUTO_TEST_CASE( custom_types )
{
  phere::Logger logger("custom types");

  Custom c(42);
  logger.debug("logging a %1%", c);
}

BOOST_AUTO_TEST_CASE( errors )
{
  phere::Logger logger("errors");
  logger.debug("not enough arguments %1%");
  logger.debug("too many arguments", 1);
}

BOOST_AUTO_TEST_CASE( rvalues )
{
  phere::Logger logger("rvalues");
  logger.debug("%1% from a function", makeCustom());
}
