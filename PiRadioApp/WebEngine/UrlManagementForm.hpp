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
    Wt::WLabel *nameLabel, *urlLabel;
    Wt::WLineEdit *nameInput, *urlInput;
    Wt::WPushButton *confirm;
    Wt::WText *feedback;
    
    std::string newURL;

public:
	UrlManagementForm();
    ~UrlManagementForm();

    void saveURL();

};
