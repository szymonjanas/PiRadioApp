#pragma once 

#include <memory>

#include "ipc/IPCRoutes.hpp"
#include "ipc/IPCMessage.hpp"
#include "dbStationJson.hpp"
#include "RadioStation.hpp"
#include "AudioManager.hpp"

namespace radio {
    class Routes : public ipc::IPCRoutes {

        db::StationsJson *database;
        radio::Audio *audio;
        
        public:
        typedef void (Routes::* MemberRoutesMethod)(ipc::message::IPCRecived& , ipc::message::IPCReply&);

        Routes(db::StationsJson *database, radio::Audio *audio) :
            database(database), audio(audio)
        {
            this->add("database/put",    & Routes::database_put);
            this->add("database/delete", & Routes::database_delete);

            this->add("audio/switch/prev", & Routes::audio_switch_prev);
            this->add("audio/switch/next", & Routes::audio_switch_next);
            this->add("audio/set/state",   & Routes::audio_set_state);
            this->add("audio/set/station", & Routes::audio_set_station);
            this->add("audio/get/state",   & Routes::audio_get_state);
            this->add("audio/get/current", & Routes::audio_get_current);
        }
        
        void add(std::string route, MemberRoutesMethod function) override {
            ipc::IPCRoutes::add(route, (MemberMethod)(function));
        }

        void database_put(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        void database_delete(ipc::message::IPCRecived& , ipc::message::IPCReply&);

        void audio_switch_prev(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        void audio_switch_next(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        void audio_set_state(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        void audio_set_station(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        void audio_get_state(ipc::message::IPCRecived& , ipc::message::IPCReply&);
        void audio_get_current(ipc::message::IPCRecived& , ipc::message::IPCReply&);
    }
}
