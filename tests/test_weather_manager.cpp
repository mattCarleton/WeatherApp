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
    QVERIFY(error.contains("server replied: Not Found", Qt::CaseInsensitive));

    // make sure no weather results were returned
    QCOMPARE(weatherSpy.count(), 0);
}

void WeatherManagerTest::testSuccess()
{
    // Ensure we have API key
    qputenv("OPENWEATHER_API_KEY", originalApiKey);

    WeatherManager wm;
    QSignalSpy weatherSpy(&wm, &WeatherManager::weatherReceived);
    QSignalSpy errorSpy(&wm, &WeatherManager::errorOccurred);

    wm.getWeather("Auckland");

    // Wait 5 seconds for either an error or a reply
    QTRY_VERIFY_WITH_TIMEOUT(weatherSpy.count() > 0 || errorSpy.count() > 0, 5000);

    // Ensure 0 errors and 1 response
    QVERIFY(errorSpy.isEmpty());  // No error should happen
    QCOMPARE(weatherSpy.count(), 1);

    QString weatherResult = weatherSpy.takeFirst().at(0).toString();

    QVERIFY(!weatherResult.isEmpty());
    QVERIFY(weatherResult.contains("Weather", Qt::CaseInsensitive));
    QVERIFY(weatherResult.contains("Temperature", Qt::CaseInsensitive));
}
