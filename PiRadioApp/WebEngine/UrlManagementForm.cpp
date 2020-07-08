#include "UrlManagementForm.hpp"

UrlManagementForm::UrlManagementForm() : 
    Wt::WContainerWidget()
{
    url = "https://stream.open.fm/127?type=.mp3";
    label   = new Wt::WLabel(url);
    playBtn = new Wt::WPushButton("Play");
    pauseBtn = new Wt::WPushButton("Pause");
    stopBtn = new Wt::WPushButton("Stop");

    playBtn->setCheckable(true);
    playBtn->clicked().connect(this, &UrlManagementForm::play);

    pauseBtn->setCheckable(true);
    pauseBtn->clicked().connect(this, &UrlManagementForm::pause);

    stopBtn->setCheckable(true);
    stopBtn->clicked().connect(this, &UrlManagementForm::stop);

    addWidget(std::unique_ptr<Wt::WWidget>(label));
    addWidget(std::unique_ptr<Wt::WWidget>(playBtn));
    addWidget(std::unique_ptr<Wt::WWidget>(pauseBtn));
    addWidget(std::unique_ptr<Wt::WWidget>(stopBtn));

}

UrlManagementForm::~UrlManagementForm() {

}

void UrlManagementForm::play()
{
    AudioEngineManager::play(url);
}

void UrlManagementForm::pause()
{
    AudioEngineManager::pause();
}

void UrlManagementForm::stop()
{
    AudioEngineManager::stop();
}
