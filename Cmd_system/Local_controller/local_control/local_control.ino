#include "Controller\Controller.h"

Controller m_Controller;

void setup()
{
  m_Controller.Initiate();
}

void loop()
{
  // put your main code here, to run repeatedly:
  m_Controller.Execute();
}
