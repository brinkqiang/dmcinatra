
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

void print(const response_data& result)
{
    print(result.ec, result.status, result.resp_body, result.resp_headers.second);
}

int main()
{
    DMSetWorkPath();

    std::string uri = "http://www.baidu.com";
    std::string uri1 = "http://cn.bing.com";
    std::string uri2 = "https://www.baidu.com";
    std::string uri3 = "https://cn.bing.com";
    std::string uri4 = "http://129.211.105.209:15509/chatservice?";
    std::string uri5 = "http://129.211.105.208:15509/chatservice?";
    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri, [](response_data data)
        {
            print(data);
        });
    }

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri1, [](response_data data)
        {
            print(data);
        });
    }

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_post(uri, "hello", [](response_data data)
        {
            print(data);
        });
    }

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri4, [](response_data data)
        {
            if (data.status == 404)
            {
                print(data);
            }
            else
            {
                print(data);
            }
        });
    }
    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri5, [](response_data data)
        {
            if (data.status == 404)
            {
                print(data);
            }
            else
            {
                print(data);
            }
        });
    }

#ifdef CINATRA_ENABLE_SSL
    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri2, [](response_data data)
        {
            print(data);
        });
    }

    {
        auto client = cinatra::client_factory::instance().new_client();
        client->async_get(uri3, [](response_data data)
        {
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