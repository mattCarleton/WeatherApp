#include "weather_manager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QJsonArray>

WeatherManager::WeatherManager(QObject *parent) : QObject(parent) {
    connect(&netManager, &QNetworkAccessManager::finished,
            this, &WeatherManager::handleNetworkReply);
}

void WeatherManager::getWeather(const QString &city)
{
    // Get API key
    QString apiKey = QString::fromUtf8(qgetenv("OPENWEATHER_API_KEY"));
    if (apiKey.isEmpty()) {
        emit errorOccurred("API key not found. Please use: \"export OPENWEATHER_API_KEY=your_api_key\"");
        return;
    }

    if (city.trimmed().isEmpty()) {
        emit errorOccurred("City name is empty");
        return;
    }

    QUrl url("https://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;
    query.addQueryItem("q", city);
    query.addQueryItem("appid", apiKey);
    query.addQueryItem("units", "metric");
    url.setQuery(query);

    QNetworkRequest request(url);
    netManager.get(request);
}

void WeatherManager::handleNetworkReply(QNetworkReply *reply){
    // If there was an error in the reply
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred("Network error: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        emit errorOccurred("Invalid JSON response");
        return;
    }

    QJsonObject obj = doc.object();

    // If there are no keywords 'weather' or 'main' something went wrong
    if (!obj.contains("weather") || !obj.contains("main")) {
        emit errorOccurred("Weather data invalid");
        return;
    }

    QString desc = obj["weather"].toArray().first().toObject()["description"].toString();
    double temp = obj["main"].toObject()["temp"].toDouble();

    QString output = QString("Weather: %1\nTemperature: %2°C").arg(desc, QString::number(temp));
    emit weatherReceived(output);
}
