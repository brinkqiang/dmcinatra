#include <iostream>
#include <thread>
#include "dmcinatra.hpp"
#include "dmutil.h"

using namespace cinatra;
//日志切面
struct log_t
{
    bool before(request& req, response& res) {
        std::cout << "before log" << std::endl;
        return true;
    }

    bool after(request& req, response& res) {
        std::cout << "after log" << std::endl;
        return true;
    }
};

struct check {
    bool before(request& req, response& res) {
        std::cout << "before check" << std::endl;

        return true;
    }

    bool after(request& req, response& res) {
        std::cout << "after check" << std::endl;

        return true;
    }
};

struct person
{
    void foo(request& req, response& res)
    {
        std::cout << i << std::endl;
        res.render_string("ok");
    }

    void foo1(request& req, response& res)
    {
        std::cout << i << std::endl;
        res.render_string("ok");
    }

    int i = 0;
};

int main() {

    DMSetWorkPath(DMGetRootPath() + PATH_DELIMITER_STR + ".." + PATH_DELIMITER_STR);

    http_server server(std::thread::hardware_concurrency());
#ifdef CINATRA_ENABLE_SSL
    server.init_ssl_context(true, [](auto, auto) { return "123456"; }, "server.crt", "server.key", "dh1024.pem");
    bool r = server.listen("0.0.0.0", "https");
#else
    bool r = server.listen("0.0.0.0", "8080");
#endif
    if (!r) {
        return -1;
    }

    //server.set_base_path("base_path","/feather");
    server.enable_http_cache(false);//set global cache
    server.set_res_cache_max_age(86400);
    server.set_cache_max_age(5);
    server.set_http_handler<GET, POST>("/", [](request& req, response& res) {
        res.set_status_and_content(status_type::ok, "hello world");
    }, enable_cache{ false });

    person p{ 2 };
    server.set_http_handler<GET, POST>("/a", &person::foo, enable_cache{ false }, log_t{});
    server.set_http_handler<GET, POST>("/b", &person::foo1, log_t{}, enable_cache{ false });

    server.set_http_handler<GET, POST>("/string", [](request& req, response& res) {
        res.render_string(std::to_string(std::time(nullptr)));
    }, enable_cache{ true });

    server.set_http_handler<GET, POST>("/404", [](request& req, response& res) {
        res.set_status(status_type::not_found);
    }, enable_cache{ false });

    server.set_http_handler<GET, POST>("/404_custom", [](request& req, response& res) {
        res.set_status(status_type::not_found);
    }, enable_cache{ false });

    server.set_http_handler<GET, POST>("/login", [](request& req, response& res) {
        auto session = res.start_session();
        session->set_data("userid", std::string("1"));
        session->set_max_age(-1);
        res.set_status_and_content(status_type::ok, "login");
    }, enable_cache{ false });

    server.set_http_handler<GET, POST>("/islogin", [](request& req, response& res) {
        auto ptr = req.get_session();
        auto session = ptr.lock();
        if (session == nullptr || session->get_data<std::string>("userid") != "1") {
            res.set_status_and_content(status_type::ok, "没有登录");
            return;
        }
        res.set_status_and_content(status_type::ok, "已经登录");
    }, enable_cache{ false });

    server.set_http_handler<GET, POST>("/test.html", [](request& req, response& res) {
        nlohmann::json json;
        json["number"] = 1024;
        json["test_text"] = "hello,world";
        json["header_text"] = "hello cinatra";
        res.set_status(status_type::ok);
        res.set_status_and_content(status_type::ok, render::render_file("./www/test.html", json), cinatra::req_content_type::html);
    });

    server.set_http_handler<GET, POST>("/index.html", [](request& req, response& res) {
        res.add_header("Content-Type", "text/html; charset=utf-8");
        res.set_status_and_content(status_type::ok, render::render_file("./www/index.html"), cinatra::req_content_type::html);
    });

    server.set_http_handler<GET, POST, OPTIONS>("/json", [](request& req, response& res) {
        nlohmann::json json;
        res.add_header("Access-Control-Allow-Origin", "*");
        if (req.get_method() == "OPTIONS"){
            res.add_header("Access-Control-Allow-Headers", "Authorization");
            res.render_string("");
        }
        else{
            json["abc"] = "abc";
            json["success"] = true;
            json["number"] = 100.005;
            json["name"] = "中文";
            json["time_stamp"] = std::time(nullptr);
            res.render_string(json.dump());
        }
    });

    server.set_http_handler<GET, POST>("/redirect", [](request& req, response& res){
        res.redirect("http://www.baidu.com"); // res.redirect("/json");
    });

    server.set_http_handler<GET, POST>("/pathinfo/*", [](request& req, response& res) {
        auto s = req.get_query_value(0);
        res.render_string(std::string(s.data(), s.length()));
    });

    server.set_http_handler<GET, POST>("/restype", [](request& req, response& res) {
        //http://127.0.0.1:8080/restype?type=html&itemInfo=%5B%7B%22itemNum%22%3A%221%22%2C%22itemCode%22%3A%22638%22%7D%5D
        //curl --location --request GET 'http://127.0.0.1:8080/restype?type=html&itemInfo=%5B%7B%22itemNum%22%3A%221%22%2C%22itemCode%22%3A%22638%22%7D%5D' --header 'Content-Type: application/json' --data-raw '{"query":"","variables":{}}'
        auto itemInfo = req.get_query_value("itemInfo");
        auto json = nlohmann::json::parse(itemInfo);
        if (json.is_array())
        {
            for (auto node : json)
            {
                std::string itemNum = node["itemNum"];
                std::string itemCode = node["itemCode"];
            }
        }

        auto type = req.get_query_value("type");
        auto res_type = cinatra::req_content_type::string;
        if (type == "html")
        {
            res_type = cinatra::req_content_type::html;
            res.set_status_and_content(status_type::ok, "<a href='http://www.baidu.com'>hello world 百度</a>", res_type, content_encoding::none);
        }
        else if (type == "json") {
            res_type = cinatra::req_content_type::json;
            nlohmann::json json;
            json["a"] = "hello world 百度";
            json["href"] = "http://www.baidu.com";
            res.set_status_and_content(status_type::ok, json.dump(), res_type, content_encoding::none);
        }
        else if (type == "string") {
            //do not anything;
            res_type = cinatra::req_content_type::string;
            res.set_status_and_content(status_type::ok, "<a href='http://www.baidu.com'>hello world 百度</a>", res_type, content_encoding::none);
        }
    });

    server.set_http_handler<GET, POST>("/getzh", [](request& req, response& res) {
        auto zh = req.get_query_value("zh");
        res.render_string(std::string(zh.data(), zh.size()));
    });

    server.set_http_handler<GET, POST>("/gzip", [](request& req, response& res) {
        auto body = req.body();
        std::cout << body.data() << std::endl;
        res.set_status_and_content(status_type::ok, "hello world", req_content_type::none, content_encoding::gzip);
    });


    server.set_http_handler<GET, POST>("/test", [](request& req, response& res) {
        auto name = req.get_header_value("name");
        if (name.empty()) {
            res.render_string("no name");
            return;
        }

        auto id = req.get_query_value("id");
        if (id.empty()) {
            res.set_status(status_type::not_found);
            return;
        }
        res.render_string("hello world");
    });

    //aspect
    server.set_http_handler<GET, POST>("/aspect", [](request& req, response& res) {
        res.render_string("你好啊!");
    }, check{}, log_t{});

    //web socket
    server.set_http_handler<GET, POST>("/ws", [](request& req, response& res) {
        assert(req.get_content_type() == content_type::websocket);

        req.on(ws_open, [](request& req){
            std::cout << "websocket start" << std::endl;
        });

        req.on(ws_message, [](request& req) {
            auto part_data = req.get_part_data();
            //echo
            std::string str = std::string(part_data.data(), part_data.length());
            req.get_conn<cinatra::NonSSL>()->send_ws_string(std::move(str));
            std::cout << part_data.data() << std::endl;
        });

        req.on(ws_close, [](request& req) {
            std::cout << "websocket close" << std::endl;
        });

        req.on(ws_error, [](request& req) {
            std::cout << "websocket error" << std::endl;
        });
    });

    //http upload(multipart)
    server.set_http_handler<GET, POST>("/upload_multipart", [](request& req, response& res) {
        assert(req.get_content_type() == content_type::multipart);
        auto text = req.get_query_value("text");
        std::cout << text << std::endl;
        auto& files = req.get_upload_files();
        for (auto& file : files) {
            std::cout << file.get_file_path() << " " << file.get_file_size() << std::endl;
        }
        res.render_string("multipart finished");
    }, check{});

    //http upload(octet-stream)
    server.set_http_handler<GET, POST>("/upload_octet_stream", [](request& req, response& res) {
        assert(req.get_content_type() == content_type::octet_stream);
        auto& files = req.get_upload_files();
        for (auto& file : files) {
            std::cout << file.get_file_path() << " " << file.get_file_size() << std::endl;
        }
        res.render_string("octet-stream finished");
    });

    //chunked download
    //http://127.0.0.1:8080/assets/show.jpg
    //cinatra will send you the file, if the file is big file(more than 5M) the file will be downloaded by chunked
    server.run();
    return 0;
}
