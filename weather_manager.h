#ifndef WEATHER_MANAGER_H
#define WEATHER_MANAGER_H

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeatherManager : public QObject
{
    Q_OBJECT

public:
    WeatherManager(QObject *parent = nullptr);
    void getWeather(const QString &city);

signals:
    void weatherReceived(const QString &result);
    void errorOccurred(const QString &error);

private slots:
    void handleNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager netManager;
};

#endif // WEATHER_MANAGER_H
