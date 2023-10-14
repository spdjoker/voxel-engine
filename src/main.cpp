#include "Application.hpp"
#include <iostream>

int main() {
  Application app;

  app.init("My Application", 800, 600, false);
  
  while (app.running()) {
    app.poll();
    app.update();
    app.render();
  }

  app.clean();

  return 0;
}
