#ifndef TESTSFBOUNDINGBOX_H
#define TESTSFBOUNDINGBOX_H

#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

using namespace std;

#include "SFBoundingBox.h"

class TestSFBoundingBox : public CPPUNIT_NS::TestCase {
  CPPUNIT_TEST_SUITE( TestSFBoundingBox );
  CPPUNIT_TEST( testContained );
  CPPUNIT_TEST( testOverlap );
  CPPUNIT_TEST( testDisjoint );
  CPPUNIT_TEST( testSmallLarge );
  CPPUNIT_TEST_SUITE_END();

public: 
  TestSFBoundingBox( ) : CppUnit::TestCase( "TestSFBoundingBox" ) {}
  TestSFBoundingBox( std::string name ) : CppUnit::TestCase( name ) {}

  void testContained() {
    Vector2 c(0.0f, 0.0f);
    auto b1 = make_shared<SFBoundingBox>(SFBoundingBox(c, 5.0f, 5.0f));
    auto b2 = make_shared<SFBoundingBox>(SFBoundingBox(c, 5.0f, 5.0f));

    CPPUNIT_ASSERT( b1->CollidesWith(b2) );
    CPPUNIT_ASSERT( b2->CollidesWith(b1) );
  }

  void testOverlap() {
    auto b1 = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 0.0f), 5.0f, 5.0f));
    auto b2 = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(2.5f, 2.5f), 5.0f, 5.0f));

    CPPUNIT_ASSERT( b1->CollidesWith(b2) );
    CPPUNIT_ASSERT( b2->CollidesWith(b1) );
  }

  void testDisjoint() {
    auto b1 = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 0.0f), 5.0f, 5.0f));
    auto b2 = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(20.0f, 20.0f), 5.0f, 5.0f));

    CPPUNIT_ASSERT( !b1->CollidesWith(b2) );
    CPPUNIT_ASSERT( !b2->CollidesWith(b1) );
  }

  void testSmallLarge() {
    // Strange magic numbers come from an instance that failed
    auto b1 = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(10.0f, 119.0f), 2.0f, 2.0f));
    auto b2 = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 200.0f), 288.0f, 298.0f));

    CPPUNIT_ASSERT( b1->CollidesWith(b2) );
    CPPUNIT_ASSERT( b2->CollidesWith(b1) );
  }
};

#endif
