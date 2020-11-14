#include "RadioRoutes.hpp"

namespace radio
{

    void Routes::database_get_all(ipc::message::IPCRecived &recived, ipc::message::IPCReply &reply)
    {
        try
        {
            if (!database->isLoad())
                database->load();
            reply.setCode(200);
            reply.setMessage("Stations");
            reply.setValue(database->toJson());
            Log::debug("Returned all stations!");
        }
        catch (std::string str)
        {
            delete database;
            std::string dbDir = "radio-database.json";
            database = new db::StationsJson(dbDir);
            database->save();
            reply.setCode(206);
            reply.setMessage("Cannot load database: " + str + ". Created new database: " + dbDir);
            Log::warn("Cannot load database: " + str + ". CREATED NEW DATABASE: " + dbDir);
        }
    }
 
    void Routes::database_put(ipc::message::IPCRecived &recived, ipc::message::IPCReply &reply)
    {
        radio::Station station (recived.getValue());
        std::unique_ptr<radio::Station> StationPtr = std::make_unique<radio::Station>(recived.getValue());
        try
        {
            database->put(station.getName(), std::move(StationPtr));
            reply.setCode(200);
            reply.setMessage("Station added to database: " + station.getName());
            Log::debug("Station added to database: " + station.getName());
        }
        catch (...)
        {
            reply.setCode(304);
            reply.setMessage("Cannot add/change station: " + station.getName());
            Log::debug("Cannot add/change station: " + station.getName());
        }
    }

    void Routes::database_delete(ipc::message::IPCRecived &recived, ipc::message::IPCReply &reply)
    {
        radio::Station station (recived.getValue());
        std::string id = station.getName();
        if (database->getByID(id) != nullptr)
        {
            if (audio->getStation() != nullptr and audio->getStation()->getName() == id){
                audio->setState(audio::STATE::STOP);
                audio->setStation(nullptr);
            }
            database->remove(id);
            reply.setCode(200);
            reply.setMessage("Station deleted: " + station.getName());
            Log::debug("Station deleted: " + station.getName());
        }
        else
        {
            reply.setCode(400);
            reply.setMessage("Station does not exist: " + station.getName());
            Log::debug("Station does not exist: " + station.getName());
        }
    }

    void Routes::audio_switch_prev(ipc::message::IPCRecived &recive, ipc::message::IPCReply &reply)
    {
        if (database->getDatabase()->size() > 0){
            if (audio->getStation() != nullptr)
                audio->getStation()->setPlaying(false);
            audio->setStation(
                database->getPrev(audio->getStation())
                );
            reply.setCode(200);
            reply.setMessage("Station switch: previous");
            Log::debug("Station switch: previous");
        }
        else
        {
            reply.setCode(400);
            reply.setMessage("Not found station to switch!");
            Log::debug("Not found station to switch!");
        }
    }

    void Routes::audio_switch_next(ipc::message::IPCRecived &recive, ipc::message::IPCReply &reply)
    {
        if (database->getDatabase()->size() > 0)
        {
            if (audio->getStation() != nullptr)
                audio->getStation()->setPlaying(false);
            audio->setStation(
                database->getNext(audio->getStation()));
            reply.setCode(200);
            reply.setMessage("Station switch: next");
            Log::debug("Station switch: next");
        }
        else
        {
            reply.setCode(400);
            reply.setMessage("Not found station to switch!");
            Log::debug("Not found station to switch!");
        }
    }

    void Routes::audio_set_state(ipc::message::IPCRecived &recive, ipc::message::IPCReply &reply)
    {
        std::string state;
        try {
            state = recive.getValue()["state"].get<std::string>();
        } catch (nlohmann::json::exception &err){
            reply.setCode(400);
            reply.setMessage("State not found! Wrong value given!");
            Log::debug("State not found! Wrong value given!");
            return;
        }
        if (audio->canSetState(state))
        {
            audio->setState(state);
            reply.setCode(200);
            reply.setMessage("Audio state is: " + radio::Audio::stateToString(audio->getState()));
            Log::debug("Audio state is:" + radio::Audio::stateToString(audio->getState()));
        }
        else
        {
            reply.setCode(400);
            reply.setMessage("Cannot set given state: " + state);
            Log::debug("Cannot set given state: " + state);
        }
    }
    void Routes::audio_set_station(ipc::message::IPCRecived &recived, ipc::message::IPCReply &reply)
    {
        radio::Station station (recived.getValue());
        if (station.getName().size() > 0 && database->getByID(station.getName()) != nullptr)
        {
            if (audio->getStation() != nullptr)
                audio->getStation()->setPlaying(false);
            audio->setStation(database->getByID(station.getName()));
            reply.setCode(200);
            reply.setMessage("Station setted: " + audio->getStation()->getName());
            Log::debug("Station setted: " + audio->getStation()->getName());
        }
        else
        {
            reply.setCode(400);
            reply.setMessage("Station does not exist: " + station.getName());
            Log::debug("Station does not exist: " + station.getName());
        }
    }

    void Routes::audio_get_state(ipc::message::IPCRecived &recived, ipc::message::IPCReply &reply)
    {
        nlohmann::json jdata;
        jdata["state"] = audio->stateToString(audio->getState());
        reply.setCode(200);
        reply.setMessage("Station state");
        reply.setValue(jdata);
    }

    void Routes::audio_get_current(ipc::message::IPCRecived &recived, ipc::message::IPCReply &reply)
    {
        radio::Station *station = audio->getStation();
        if (station != nullptr)
        {
            reply.setCode(200);
            reply.setMessage("Current station");
            reply.setValue(station->toJson());
        }
        else
        {
            reply.setCode(400);
            reply.setMessage("No station loaded!");
            Log::debug("No station loaded!");
        }
    }

    void Routes::audio_volume_set(ipc::message::IPCRecived &recive, ipc::message::IPCReply &reply)
    {
        int volume = recive.getValue()["volume"].get<int>();
        Log::debug("volume set: " + std::to_string(volume));
        audio->setVolume(volume);
        reply.setCode(200);
        reply.setMessage("OK");
        nlohmann::json data;
        data["volume"] = audio->getVolume();
        reply.setValue(data);
    }

    void Routes::audio_volume_get(ipc::message::IPCRecived &recive, ipc::message::IPCReply &reply)
    {
        int volume = audio->getVolume();
        Log::debug("volume get: " + volume);
        reply.setCode(200);
        reply.setMessage("OK");
        nlohmann::json data;
        data["volume"] = volume;
        reply.setValue(data);
    }

} // namespace radio
