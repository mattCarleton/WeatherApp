#include <QCoreApplication>
#include <QtTest>
#include "test_weather_manager.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int result = 0;

    WeatherManagerTest weatherManagerTest;
    result |= QTest::qExec(&weatherManagerTest, argc, argv);

    return result;
}
