#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main() {
    DMSetWorkPath();

	http_server server(std::thread::hardware_concurrency());
	server.listen("0.0.0.0", "8080");
	server.set_http_handler<GET, POST>("/", [](request& req, response& res) {
		res.set_status_and_content(status_type::ok, "hello world");
	});

	server.run();
	return 0;
}