#pragma once

#include <Wt/WWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include <memory>

#include "AudioEngineManager.hpp"

class UrlManagementForm : public Wt::WContainerWidget
{
    Wt::WLabel *label;
    Wt::WPushButton *playBtn;
    Wt::WPushButton *pauseBtn;
    Wt::WPushButton *stopBtn;

    std::string url;

public:
	UrlManagementForm();
    ~UrlManagementForm();

    void play();
    void pause();
    void stop();

};
