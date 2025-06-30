#include "test_weather_manager.h"
#include <QSignalSpy>
#include <QTest>
#include "../weather_manager.h"

void WeatherManagerTest::initApiKey()
{
    originalApiKey = qgetenv("OPENWEATHER_API_KEY");
    QVERIFY(!originalApiKey.isEmpty());
}

void WeatherManagerTest::testEmptyCity()
{
    // Ensure we have API key
    qputenv("OPENWEATHER_API_KEY", originalApiKey);

    WeatherManager wm;
    QSignalSpy errorSpy(&wm, &WeatherManager::errorOccurred);

    wm.getWeather(QString());

    QTRY_VERIFY_WITH_TIMEOUT(!errorSpy.isEmpty(), 3000); // wait 3000ms for signal
    QCOMPARE(errorSpy.count(), 1);

    QString error = errorSpy.takeFirst().at(0).toString();
    QVERIFY(error.contains("city name is empty", Qt::CaseInsensitive));
}

void WeatherManagerTest::testNoApiKey()
{
    // set an invalid API key
    qputenv("OPENWEATHER_API_KEY", "invalid_key");

    WeatherManager wm;
    QSignalSpy errorSpy(&wm, &WeatherManager::errorOccurred);

    wm.getWeather("Auckland");

    QTRY_VERIFY_WITH_TIMEOUT(!errorSpy.isEmpty(), 3000); // wait 3000ms for signal
    QCOMPARE(errorSpy.count(), 1);

    QString error = errorSpy.takeFirst().at(0).toString();
    QVERIFY(error.contains("Host requires authentication") ||
            error.contains("Unauthorized", Qt::CaseInsensitive));

}

void WeatherManagerTest::testInvalidApiKey()
{
    // Clear API key
    qputenv("OPENWEATHER_API_KEY", QByteArray());

    WeatherManager wm;
    QSignalSpy errorSpy(&wm, &WeatherManager::errorOccurred);

    wm.getWeather("Auckland");

    QTRY_VERIFY_WITH_TIMEOUT(!errorSpy.isEmpty(), 3000); // wait 3000ms for signal
    QCOMPARE(errorSpy.count(), 1);

    QString error = errorSpy.takeFirst().at(0).toString();
    QVERIFY(error.contains("API key not found", Qt::CaseInsensitive));
}

void WeatherManagerTest::testInvalidCity()
{
     // Ensure we have API key
    qputenv("OPENWEATHER_API_KEY", originalApiKey);

    WeatherManager wm;
    QSignalSpy errorSpy(&wm, &WeatherManager::errorOccurred);
    QSignalSpy weatherSpy(&wm, &WeatherManager::weatherReceived);

    wm.getWeather("Auck-land");

    QTRY_VERIFY_WITH_TIMEOUT(!errorSpy.isEmpty(), 3000); // wait 3000ms for signal

    // make sure an error result was returned
    QCOMPARE(errorSpy.count(), 1);
    QString error = errorSpy.takeFirst().at(0).toString();
    qDebug() << "Error message:" << error;
    QVERIFY(error.contains("server replied: Not Found", Qt::CaseInsensitive));

    // make sure no weather results were returned
    QCOMPARE(weatherSpy.count(), 0);
}
