#pragma once

#include <Wt/WWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>

#include <memory>

#include "AudioEngineManager.hpp"

class PlayingManagementForm : public Wt::WContainerWidget
{
    Wt::WLabel* label;
    Wt::WPushButton* playBtn;
    Wt::WPushButton* pauseBtn;
    Wt::WPushButton* stopBtn;

    std::string url;

public:

    PlayingManagementForm();
    ~PlayingManagementForm();

    void play();
    void pause();
    void stop();
};
