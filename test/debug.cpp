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

BOOST_AUTO_TEST_CASE( usage )
{
  phere::Logger logger("usage");
  logger.debug("debug message");
  logger.info("info message (%1%)", "parameter");
  logger.warning("warning message");
  logger.error("error message");
}
