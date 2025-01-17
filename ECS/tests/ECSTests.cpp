#include <criterion/criterion.h>
#include "../src/Application/Application.hpp"

TestSuite(ApplicationTests);

Test(ApplicationTests, WindowCreation)
{
    App::Application::AppSettings settings;
    settings.windowSize = {1920, 1080};
    settings.bytePerPixel = 32;
    settings.windowTitle = "Test Window";
    settings.frameRateLimit = 60;

    App::Application app(settings);
    
    cr_assert(app.getWindow().isOpen(), "Window should be open after creation");
    cr_assert_eq(app.getWindow().getSize().x, 1920, "Window width should be 1920");
    cr_assert_eq(app.getWindow().getSize().y, 1080, "Window height should be 1080");
}

Test(ApplicationTests, WindowClosing)
{
    App::Application::AppSettings settings;
    App::Application app(settings);
    
    cr_assert(app.getWindow().isOpen(), "Window should be open initially");
    app.getWindow().close();
    cr_assert(!app.getWindow().isOpen(), "Window should be closed after calling close");
}
