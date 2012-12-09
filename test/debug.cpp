#define BOOST_TEST_MODULE Debug
#include <boost/test/unit_test.hpp>

#include <phere/Logger.hpp>
#include <phere/Console.hpp>

BOOST_AUTO_TEST_CASE( usage )
{
  phere::Debug::Logger<> logger("usage");
  logger.trace("Trace message");
  logger.trace("Trace message (%1%)", "parameter");
  logger.message("General message");
  logger.warning("Warning message");
  logger.error("Error message");
}

BOOST_AUTO_TEST_CASE( output )
{
  phere::Debug::Logger
	<phere::Debug::Console> logger("output");
  logger.trace("Trace message");
  logger.trace("Trace message (%1%)", "parameter");
  logger.message("General message");
  logger.warning("Warning message");
  logger.error("Error message");
}
