
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main()
{
    DMSetWorkPath(DMGetRootPath());

    std::string uri = "http://cn.bing.com/";
    auto client = cinatra::client_factory::instance().new_client();
    client->upload(uri, "boost_1_72_0.7z", [](response_data data) {
        if (data.ec) {
            std::cout << data.ec.message() << "\n";
            return;
        }

        std::cout << data.resp_body << "\n"; //finished upload
    });

    return 0;
}
