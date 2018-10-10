#include <UltravioletDetectorInterface.h>


UltravioletDetectorInterface dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
