
#include <atomic>
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main() {
    DMSetWorkPath();

    http_server server(std::thread::hardware_concurrency());
    server.listen("0.0.0.0", "8080");

    //http upload(multipart)
    server.set_http_handler<GET, POST>("/upload_multipart", [](request& req, response& res) {
        assert(req.get_content_type() == content_type::multipart);

        auto& files = req.get_upload_files();
        for (auto& file : files) {
            std::cout << file.get_file_path() << " " << file.get_raw_file_name() << " " << file.get_file_size() << std::endl;
        }

        res.set_status_and_content(status_type::ok, "multipart finished");
    });

    server.run();
    return 0;
}
