
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

void print(const response_data& result) {
    print(result.ec, result.status, result.resp_body, result.resp_headers.second);
}

int main()
{
    DMSetWorkPath(DMGetRootPath());

    std::string uri = "http://www.baidu.com";
    std::string uri1 = "http://cn.bing.com";
    std::string uri2 = "https://www.baidu.com";
    std::string uri3 = "https://cn.bing.com";

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri, [](response_data data) {
            print(data);
        });
    }
    
    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri1, [](response_data data) {
            print(data);
        });
    }

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_post(uri, "hello", [](response_data data) {
            print(data);
        });
    }

#ifdef CINATRA_ENABLE_SSL
    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri2, [](response_data data) {
            print(data);
        });
    }

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri3, [](response_data data) {
            print(data);
        });
    }
#endif
    while(1)
    {
        SleepMs(1);
    }
    return 0;
}