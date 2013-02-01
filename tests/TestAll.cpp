#include <cppunit/ui/text/TestRunner.h>

#include "TestSFBoundingBox.h"

int main( int argc, char **argv) {
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( TestSFBoundingBox::suite() );
  runner.run();
  return 0;
}
