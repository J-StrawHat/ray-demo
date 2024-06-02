#ifndef SERVER_H
#define SERVER_H

#include <chrono>
#include <iostream>
#include <ray/api.h>
#include <thread>

const std::string COMPUTING_ACTOR_NAME = "computing_actor";
const std::string IP_ADDRESS = "192.168.1.164:6379";
const std::unordered_map<std::string, double> RESOUECES{{"CPU", 1.0}};

class MainServer {
  public:
    MainServer() {
        // if (ray::WasCurrentActorRestarted()) {
        //   HandleFailover();
        // }

        RAYLOG(INFO) << "MainServer created";
    }

    // Set value by the given key.
    void Put(const std::string &key, const std::string &val) {
        data_[key] = val;
    }

    // Get value from a key.
    std::pair<bool, std::string> Get(const std::string &key) {
        auto it = data_.find(key);
        if (it == data_.end()) {
            return {false, ""};
        }
        return {true, it->second};
    }

    // This is used for the backup server to recover data when it restarts.
    std::unordered_map<std::string, std::string> GetAllData() { return data_; }

  private:
    // A map that stores the key-value data.
    std::unordered_map<std::string, std::string> data_;
};

static MainServer *CreateMainServer() { return new MainServer(); }

RAY_REMOTE(CreateMainServer, &MainServer::GetAllData, &MainServer::Get,
           &MainServer::Put);

#endif