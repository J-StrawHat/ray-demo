// client/client.cpp
#include "../../include/client.h"

int main(int argc, char **argv) {
    ray::RayConfig config;
    config.ray_namespace = "mycluster";
    config.address = IP_ADDRESS;
    ray::Init(config);

    Client client;
    bool r = client.Put("hello", "ray");
    assert(r);
    // Silence warning.
    (void)r;

    auto get_result = [&client](const std::string &key) {
        bool ok;
        std::string result;
        std::tie(ok, result) = client.Get("hello");
        assert(ok);
        std::cout << "Client got result: " << result << std::endl;
    };

    get_result("hello");

    client.Put("hello", "world");

    get_result("hello");

    client.Shutdown();
    ray::Shutdown();
    return 0;
}