
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
    std::string uri = "https://api.weixin.qq.com/sns/jscode2session";
    {
        response_data result = client->get(uri);
        print(result);
    }

    return 0;
}
