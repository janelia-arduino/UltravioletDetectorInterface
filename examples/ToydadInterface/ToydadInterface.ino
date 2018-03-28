#include <ToydadInterface.h>


ToydadInterface dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
