// server/server.cpp
#include "../../include/server.h"

int main(int argc, char **argv) {
    ray::RayConfig config;
    config.ray_namespace = "mycluster";
    config.address = IP_ADDRESS;
    ray::Init(config);
    // ray::Init();

    // std::vector<std::unordered_map<std::string, double>> bundles{RESOUECES};
    // ray::PlacementGroupCreationOptions options{"kv_server_pg", bundles,
    // ray::PlacementStrategy::SPREAD}; auto placement_group =
    // ray::CreatePlacementGroup(options);
    // // Wait until the placement group is created.
    // assert(placement_group.Wait(10));

    // Create the main server actor and backup server actor.
    ray::Actor(CreateMainServer)
        .SetName(COMPUTING_ACTOR_NAME) // Set name of this actor.
        .SetResources(RESOUECES) // Set the resources that this actor needs.
        // .SetPlacementGroup(placement_group, 0) // Set the corresponding
        // placement group.
        .SetMaxRestarts(
            -1) // Tell Ray to restart this actor automatically upon failures.
        .Remote();

    // Keep the server running
    std::cout << "Server is running..." << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    ray::Shutdown();
    return 0;
}