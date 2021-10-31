
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

    auto client = cinatra::client_factory::instance().new_client();
    std::string uri = "http://www.baidu.com";
    std::string uri1 = "http://cn.bing.com";
    std::string uri2 = "https://www.baidu.com";
    std::string uri3 = "https://cn.bing.com";
    std::string uri4 = "http://129.211.105.209:15509/chatservice?";

    {
        response_data result = client->get(uri);
        print(result);
    }
    {
        response_data result = client->get(uri1);
        print(result);
    }

    print(client->post(uri, "hello"));
    print(client->post(uri1, "hello"));

#ifdef CINATRA_ENABLE_SSL

    {
        response_data result = client->get(uri2);
        print(result);
    }

    {
        response_data result = client->get(uri3);
        print(result);
    }
    print(result5);
#endif

    {
        response_data result = client->get(uri4);
        print(result);
    }

    return 0;
}