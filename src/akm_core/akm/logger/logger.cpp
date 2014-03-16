#include "logger.hpp"

#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#ifdef _WIN32
#include <windows.h>
#endif

boost::mutex io_mutex;

akm::logger::logger::~logger()
{
	io_mutex.lock();
		std::cout << "[" << get_time() << "] [";
		set_color(tag_color);
		std::cout << tag;
		set_color(color::DEFAULT);
		std::cout << "] " << message.str() << std::endl << std::flush;
	io_mutex.unlock();
}

std::string akm::logger::logger::get_time()
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	std::ostringstream time;
	time.imbue(std::locale(time.getloc(), new boost::posix_time::time_facet("%H:%M:%S")));
	time << now;

	return time.str();
}

void akm::logger::logger::set_color(int color)
{
#ifdef _WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hstdout, color);
#endif
}