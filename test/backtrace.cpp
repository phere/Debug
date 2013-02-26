#define BOOST_TEST_MODULE Backtrace
#include <boost/test/unit_test.hpp>

#include <phere/Backtrace.hpp>

#include <iostream>

BOOST_AUTO_TEST_CASE( trivial )
{
  std::cerr << "Trivial test case:\n" << phere::backtrace() << std::endl;
}
