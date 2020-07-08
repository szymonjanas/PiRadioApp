#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <memory>

#include "PlayingManagementForm.hpp"
#include "UrlManagementForm.hpp"
#include "StationsManagementForm.hpp"

class WebEngine : public Wt::WApplication
{

public:
	WebEngine(const Wt::WEnvironment& enviroment);

};

