
#include "cinatra.hpp"
#include "dmutil.h"

using namespace cinatra;

int main()
{
    DMSetWorkPath(DMGetRootPath() + PATH_DELIMITER_STR + ".." + PATH_DELIMITER_STR);


    {
        std::string uri =
            "http://127.0.0.1:8080/Mindjet.zip";

        auto client = cinatra::client_factory::instance().new_client();
        client->download(uri, "www2/Mindjet.zip", [](response_data data)
        {
            if (data.ec)
            {
                std::cout << data.ec.message() << "\n";
                return;
            }

            std::cout << "finished download\n";
        });
    }

    {
        std::string uri =
            "http://127.0.0.1:8080/Mind jet.zip";

        auto client = cinatra::client_factory::instance().new_client();
        client->download(uri, "www2/Mind jet.zip", [](response_data data)
        {
            if (data.ec)
            {
                std::cout << data.ec.message() << "\n";
                return;
            }

            std::cout << "finished download\n";
        });
    }

    //{
    //    auto client = cinatra::client_factory::instance().new_client();
    //    client->download(uri, [](auto ec, auto data)
    //    {
    //        if (ec)
    //        {
    //            std::cout << ec.message() << "\n";
    //            return;
    //        }

    //        if (data.empty())
    //        {
    //            std::cout << "finished all \n";
    //        }
    //        else
    //        {
    //            std::cout << data.size() << "\n";
    //        }
    //    });
    //}

    while (1)
    {
        SleepMs(1);
    }

    return 0;
}
