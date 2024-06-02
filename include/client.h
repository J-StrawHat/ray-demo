#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"

class Client {
  public:
    Client() {
        main_actor_ = ray::GetActor<MainServer>(COMPUTING_ACTOR_NAME);
        // In case the main server hasn't started yet, retry getting
        // the actor handle.
        if (!main_actor_) {
            RetryGetActor();
        }
    }

    bool Put(const std::string &key, const std::string &val) {
        // During the restart of the main server actor, the task may fail.
        // So we use retry here.
        AlwaysRetry([this, &key, &val] {
            (*main_actor_).Task(&MainServer::Put).Remote(key, val).Get();
            return true;
        });

        return true;
    }

    std::pair<bool, std::string> Get(const std::string &key) {
        // During the restart of the main server actor, the task may fail.
        // So we use retry here.
        return AlwaysRetry([this, &key] {
            return *(*main_actor_).Task(&MainServer::Get).Remote(key).Get();
        });
    }

    void Shutdown() { main_actor_->Kill(false); }

  private:
    void RetryGetActor() {
        AlwaysRetry([this] {
            main_actor_ = ray::GetActor<MainServer>(COMPUTING_ACTOR_NAME);
            return std::make_pair(bool(main_actor_), "");
        });
    }

    template <typename F> std::result_of_t<F()> AlwaysRetry(const F &f) {
        using R = std::result_of_t<F()>;
        R r{};
        while (true) {
            try {
                r = f();
                if (IsValid(r)) {
                    break;
                }
            } catch (const std::exception &) {
            }

            std::cout << "Retry in 2 seconds\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        return r;
    }

    bool IsValid(bool r) { return r; }

    bool IsValid(const std::pair<bool, std::string> r) { return r.first; }

    boost::optional<ray::ActorHandle<MainServer>> main_actor_;
};

#endif