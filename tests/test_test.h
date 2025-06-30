#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <QObject>

class TestTest : public QObject {
    Q_OBJECT
private slots:
    void sanityTest(void);
};

#endif // TEST_TEST_H
