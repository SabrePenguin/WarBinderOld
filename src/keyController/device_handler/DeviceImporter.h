#ifndef DEVICE_IMPORTER_H
#define DEVICE_IMPORTER_H
#include <vector>
class Device ;

int startup() ;

std::vector<Device> find_devices() ;

void shutdown() ;

#endif // !DEVICE_IMPORTER_H