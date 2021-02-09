
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main()
{
    std::string uri = "http://www.httpwatch.com/httpgallery/chunked/chunkedimage.aspx";

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->download(uri, "test.jpg", [](response_data data) {
            if (data.ec) {
                std::cout << data.ec.message() << "\n";
                return;
            }

            std::cout << "finished download\n";
        });
    }

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->download(uri, [](auto ec, auto data) {
            if (ec) {
                std::cout << ec.message() << "\n";
                return;
            }

            if (data.empty()) {
                std::cout << "finished all \n";
            }
            else {
                std::cout << data.size() << "\n";
            }
        });
    }

    return 0;
}
