#include <nova/nova.h>
#include "nova/application.h"

int main()
{
  nova::ApplicationSpecification spec;
  spec.name = "Nova Test Application";
  spec.width = 800;
  spec.height = 600;

  nova::Application app(spec);

  if (!app.init())
  {
    return -1;
  }

  app.run();

  return 0;
}
