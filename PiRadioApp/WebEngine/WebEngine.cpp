#include "WebEngine.hpp"


WebEngine::WebEngine(const Wt::WEnvironment& enviroment) :
	Wt::WApplication(enviroment)
{
	setTitle("PiRadio");
	auto ptr = Wt::cpp14::make_unique<PlayingManagementForm>();
	root()->addWidget(std::move(ptr));

	auto url = Wt::cpp14::make_unique<UrlManagementForm>();
	root()->addWidget(std::move(url));

	auto stations = Wt::cpp14::make_unique<StationsManagementForm>();
	root()->addWidget(std::move(stations));

	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();

	container->addNew<Wt::WText>("A first widget");

	root()->addWidget(std::move(container));

	root()->addNew<Wt::WText>("Hello World Again!");
	root()->addNew<Wt::WBreak>();
	root()->addNew<Wt::WText>("It's great to be alive!");

}
