#include "weather_manager.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // Main window
    QWidget *window = new QWidget;
    window->setWindowTitle("Weather App");

    // Input field
    QLineEdit *cityInput = new QLineEdit;
    cityInput->setPlaceholderText("Enter city");

    // Get Weather button
    QPushButton *getWeatherButton = new QPushButton("Get Weather");

    // Output label
    QLabel *resultLabel = new QLabel("Result will appear here");
    resultLabel->setWordWrap(true);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(cityInput);
    layout->addWidget(getWeatherButton);
    layout->addWidget(resultLabel);
    window->setLayout(layout);

    WeatherManager *weatherManager = new WeatherManager;

    QObject::connect(getWeatherButton, &QPushButton::clicked, window, [=, &weatherManager]() {
        QString city = cityInput->text().trimmed();
        if (city.isEmpty()) {
            resultLabel->setText("Please enter a city name.");
        } else {
            weatherManager->getWeather(city);
        }
    });

    QObject::connect(weatherManager, &WeatherManager::weatherReceived, resultLabel, &QLabel::setText);
    QObject::connect(weatherManager, &WeatherManager::errorOccurred, resultLabel, &QLabel::setText);

    // Show the window
    window->resize(300, 150);
    window->show();

    return a.exec();
}
