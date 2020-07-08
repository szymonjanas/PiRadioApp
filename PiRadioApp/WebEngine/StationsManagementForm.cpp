#include "StationsManagementForm.hpp"

StationsManagementForm::StationsManagementForm() :
    Wt::WContainerWidget()
{
    //nameLabel = new Wt::WLabel();
    //urlLabel = new Wt::WLabel();
    //playBtn = new Wt::WPushButton("Play");


    //playBtn->setCheckable(true);
    //playBtn->clicked().connect(this, &PlayingManagementForm::play);

    auto database = DatabaseEngine::getDatabase();

    addNew<Wt::WBreak>();
    addNew<Wt::WText>(Wt::WString("Stations: "));
    addNew<Wt::WBreak>();
    for (auto iter = (*database).begin(); iter != (*database).end(); ++iter) {
        addNew<Wt::WText>(Wt::WString(iter->first));
        addNew<Wt::WText>(Wt::WString(iter->second));
        addNew<Wt::WBreak>();
    }


}
