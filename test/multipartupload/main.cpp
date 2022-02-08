
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main()
{
    DMSetWorkPath();

    std::string strFile = DMGetRootPath() + PATH_DELIMITER_STR + "multipartupload.exe";

    std::string uri = "http://127.0.0.1:8080/upload_multipart";
    auto client = cinatra::client_factory::instance().new_client();
    client->sync_upload(uri, strFile, [](response_data data) {
        if (data.ec) {
            std::cout << data.ec.message() << "\n";
            return;
        }

        std::cout << data.resp_body << "\n"; //finished upload
    });
    return 0;
}
