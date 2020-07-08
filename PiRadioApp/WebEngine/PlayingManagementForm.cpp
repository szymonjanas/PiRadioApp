#include "PlayingManagementForm.hpp"

PlayingManagementForm::PlayingManagementForm() :
    Wt::WContainerWidget()
{
    url = "https://stream.open.fm/127?type=.mp3";
    label = new Wt::WLabel(url);
    playBtn = new Wt::WPushButton("Play");
    pauseBtn = new Wt::WPushButton("Pause");
    stopBtn = new Wt::WPushButton("Stop");

    playBtn->setCheckable(true);
    playBtn->clicked().connect(this, &PlayingManagementForm::play);

    pauseBtn->setCheckable(true);
    pauseBtn->clicked().connect(this, &PlayingManagementForm::pause);

    stopBtn->setCheckable(true);
    stopBtn->clicked().connect(this, &PlayingManagementForm::stop);

    addWidget(std::unique_ptr<Wt::WWidget>(label));
    addWidget(std::unique_ptr<Wt::WWidget>(playBtn));
    addWidget(std::unique_ptr<Wt::WWidget>(pauseBtn));
    addWidget(std::unique_ptr<Wt::WWidget>(stopBtn));

}

PlayingManagementForm::~PlayingManagementForm() {
    delete label;
    delete playBtn;
    delete pauseBtn;
    delete stopBtn;
}

void PlayingManagementForm::play()
{
    AudioEngineManager::play(url);
}

void PlayingManagementForm::pause()
{
    AudioEngineManager::pause();
}

void PlayingManagementForm::stop()
{
    PlayingManagementForm::stop();
}
