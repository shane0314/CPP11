/*
g++ test28-CBasicMath.cpp test28-cppunittest.cpp -o t28 -lcppunit -g -I .
*/
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "test28-CBasicMath.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestBasicMath : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestBasicMath);
    CPPUNIT_TEST(testAddition);
    CPPUNIT_TEST(testMultiply);
    CPPUNIT_TEST(testAll);
    CPPUNIT_TEST(testTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testAddition(void);
    void testMultiply(void);
	void testAll(void);
	void testTest(void);
    void testAddition(int a, int b);
    void testMultiply(int a, int b);

private:
	static int mCount;
    CBasicMath *mTestObj;
};

int TestBasicMath::mCount = 0;
//-----------------------------------------------------------------------------

void
TestBasicMath::testAddition(void)
{
	std::cout << "\nmCount = " << mCount << std::endl;
	mCount ++;
    CPPUNIT_ASSERT(5 == mTestObj->Addition(2,3));
}

void
TestBasicMath::testMultiply(void)
{
	std::cout << "\nmCount = " << mCount << std::endl;
	mCount ++;
    CPPUNIT_ASSERT(6 == mTestObj->Multiply(2,3));
}

void TestBasicMath::testAll(void)
{
	std::cout << "\nmCount = " << mCount << std::endl;
	mCount ++;
	testAddition(3,4);
	testMultiply(3,4);
}

void TestBasicMath::testTest(void)
{
	std::cout << "\nmCount = " << mCount << std::endl;
	mCount ++;
	std:string str("Hello");
	std::stringstream ss;
	ss << "Hello";
	CPPUNIT_ASSERT_EQUAL(str, ss.str() );
}

void
TestBasicMath::testAddition(int a, int b)
{
    CPPUNIT_ASSERT(a+b == mTestObj->Addition(a,b));
}

void
TestBasicMath::testMultiply(int a, int b)
{
 	CPPUNIT_ASSERT(a*b == mTestObj->Multiply(a,b));
}


void TestBasicMath::setUp(void)
{
    mTestObj = new CBasicMath();
	//mCount = 0;
	std::cout << "\n setUP() " << std::endl;
}

void TestBasicMath::tearDown(void)
{
    delete mTestObj;
	std::cout << "\n tearDown " << std::endl;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestBasicMath );

int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("cppTestBasicMathResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}
