#define BOOST_TEST_MODULE Debug
#include <boost/test/unit_test.hpp>

#include <phere/Logger.hpp>
#include <phere/ConsoleWriter.hpp>

BOOST_AUTO_TEST_CASE( usage )
{
  phere::Logger logger("usage");
  logger.debug("debug message");
  logger.info("info message (%1%)", "parameter");
  logger.warning("warning message");
  logger.error("error message");
}
