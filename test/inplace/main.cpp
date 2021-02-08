
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main() {
	DMSetWorkPath(DMGetRootPath() + PATH_DELIMITER_STR + ".." + PATH_DELIMITER_STR + "www");

	bool is_running = true;
	http_server_<io_service_inplace> server;
	server.listen("8080");

	server.set_http_handler<GET, POST>("/", [](request& req, response& res) {
		res.set_status_and_content(status_type::ok, "hello world");
	});

	server.set_http_handler<GET, POST>("/close", [&](request& req, response& res) {
		res.set_status_and_content(status_type::ok, "will close");

		is_running = false;
		server.stop();
	});

	while(is_running)
		server.poll_one();

	return 0;
}