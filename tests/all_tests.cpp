#include <QtTest>
#include "test_test.h"

int main(int argc, char *argv[])
{
    int result = 0;

    TestTest testTest;
    result |= QTest::qExec(&testTest, argc, argv);

    return result;
}
