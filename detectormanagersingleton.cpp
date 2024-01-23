#include "detectormanagersingleton.h"
DetectorManager DetectorManagerSingleton::instance;

DetectorManagerSingleton::DetectorManagerSingleton()
{

}

DetectorManager &DetectorManagerSingleton::getInstance()
{
    return instance;
}
