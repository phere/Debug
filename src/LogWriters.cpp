#include "phere/LogWriters.hpp"

#include "phere/LogWriter.hpp"

#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

#include <list>

namespace
{
  typedef std::list<phere::LogWriter*> WritersList;
  boost::shared_mutex writersMutex;
  WritersList writers;

  void remove_internal(phere::LogWriter* writer,
					   boost::unique_lock<boost::shared_mutex>& writersLock)
  {
	writers.remove(writer);
  }
}

namespace phere
{
  void LogWriters::write_all(Message const& message)
  {
	boost::shared_lock<boost::shared_mutex> writersLock(writersMutex);
	for (WritersList::const_iterator it(writers.begin());
		 it != writers.end(); ++it)
	  {
		(*it)->write(message);
	  }
  }

  void LogWriters::add(LogWriter* writer)
  {
	boost::unique_lock<boost::shared_mutex> writersLock(writersMutex);
	remove_internal(writer, writersLock);
	writers.push_back(writer);
  }

  void LogWriters::remove(LogWriter* writer)
  {
	boost::unique_lock<boost::shared_mutex> writersLock(writersMutex);
	remove_internal(writer, writersLock);
  }
}
