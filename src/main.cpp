#include "application.hpp"
#include "types/vector2i.hpp"
#include <iostream>

int main() {
  Application app;

  app.init("My Application", 800, 600, false);

  while (app.running()) {
    app.poll();

    if (app.input().onKeyDown(KeyCode::ESCAPE)) {
      app.quit();
    }

    app.render();
  }

  app.clean();

  return 0;
}
