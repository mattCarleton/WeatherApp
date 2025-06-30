#ifndef TEST_WEATHER_MANAGER_H
#define TEST_WEATHER_MANAGER_H

#include <QObject>

class WeatherManagerTest : public QObject {
    Q_OBJECT
private:
    QByteArray originalApiKey;
private slots:
    void initApiKey(void);
    void testEmptyCity(void);
    void testNoApiKey(void);
    void testInvalidApiKey(void);
    void testInvalidCity(void);
};

#endif // TEST_WEATHER_MANAGER_H
