
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main()
{
    DMSetWorkPath();

    std::string uri = "http://127.0.0.1:8080";
    auto client = cinatra::client_factory::instance().new_client();
    client->upload(uri, "multipartupload.exe", [](response_data data) {
        if (data.ec) {
            std::cout << data.ec.message() << "\n";
            return;
        }

        std::cout << data.resp_body << "\n"; //finished upload
    });
    while (1)SleepMs(1);
    return 0;
}
