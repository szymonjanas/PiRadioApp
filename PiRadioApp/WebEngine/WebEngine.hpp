#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <memory>

#include "UrlManagementForm.hpp"

class WebEngine : public Wt::WApplication
{

public:
	WebEngine(const Wt::WEnvironment& enviroment);

};

