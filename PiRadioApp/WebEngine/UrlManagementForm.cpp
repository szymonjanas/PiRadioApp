#include "UrlManagementForm.hpp"

UrlManagementForm::UrlManagementForm() : 
    Wt::WContainerWidget()
{
    nameLabel   = new Wt::WLabel("Name: ");
    urlLabel    = new Wt::WLabel("URL: ");
    confirm     = new Wt::WPushButton("Confirm");
    nameInput   = new Wt::WLineEdit();
    urlInput    = new Wt::WLineEdit();
    feedback    = new Wt::WText();

    confirm->clicked().connect(this, &UrlManagementForm::saveURL);

    addWidget(std::unique_ptr<Wt::WWidget>(nameLabel));
    addWidget(std::unique_ptr<Wt::WWidget>(nameInput));
    addWidget(std::unique_ptr<Wt::WWidget>(urlLabel));
    addWidget(std::unique_ptr<Wt::WWidget>(urlInput));
    addWidget(std::unique_ptr<Wt::WWidget>(confirm));
    addWidget(std::unique_ptr<Wt::WWidget>(feedback));

}

UrlManagementForm::~UrlManagementForm() {

}

void UrlManagementForm::saveURL()
{
    feedback->setText(nameInput->text() + ": " + urlInput->text());
}
