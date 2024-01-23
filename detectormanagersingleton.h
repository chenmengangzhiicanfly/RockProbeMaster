#ifndef DETECTORMANAGERSINGLETON_H
#define DETECTORMANAGERSINGLETON_H
#include "DetectorManager.h"


//饿汉实现
class DetectorManagerSingleton
{
public:


    static DetectorManager& getInstance();
private:
    static DetectorManager instance;
    DetectorManagerSingleton();

};

#endif // DETECTORMANAGERSINGLETON_H
