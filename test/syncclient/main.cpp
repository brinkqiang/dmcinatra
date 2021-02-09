
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

void print(const response_data& result) {
    print(result.ec, result.status, result.resp_body, result.resp_headers.second);
}

int main()
{
    DMSetWorkPath(DMGetRootPath());

    auto client = cinatra::client_factory::instance().new_client();
    std::string uri = "http://www.baidu.com";
    std::string uri1 = "http://cn.bing.com";
    std::string uri2 = "https://www.baidu.com";
    std::string uri3 = "https://cn.bing.com";
    
    response_data result = client->get(uri);
    print(result);

    response_data result1 = client->get(uri1);
    print(result1);

    print(client->post(uri, "hello"));
    print(client->post(uri1, "hello"));

#ifdef CINATRA_ENABLE_SSL
    response_data result2 = client->get(uri2);
    print(result2);

    response_data result3 = client->get(uri3);
    print(result3);

    response_data result4 = client->get(uri3);
    print(result4);

    response_data result5 = client->get(uri2);
    print(result5);
#endif

    return 0;
}