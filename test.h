#ifndef TEST_H
#define TEST_H

#include <QThread>
#include "VideoDetector.h"
#include "DetectorManager.h"

class Test : public QThread,public DetectorManager
{
public:
    explicit Test(QObject *parent = nullptr);
};

#endif // TEST_H
