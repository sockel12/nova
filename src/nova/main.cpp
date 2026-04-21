#include <nova/application.h>

#include <nova/core/logger.h>

int main()
{
  nova::ApplicationSpecification spec = create_application_specification();

  auto app = std::make_shared<nova::Application>(spec);

  if (!app->init())
  {
    nova::core::logger()->error("Failed to initialize application");
    return -1;
  }

  app->run();
}