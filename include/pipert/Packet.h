#ifndef _PACKET_H_
#define _PACKET_H_

#include <utility>
#include "pipert/PacketBase.h"
#include "pipert/MeasurementProfile.h"

namespace pipert {

template <class T>
class Packet : public PacketBase {
 public:
  template <class... Args>
  Packet(Timer::Time timestamp, Args&&... args);
  ~Packet() {}

  const T& data() const;
  T& data();

  MeasurementProfile measurementProfile();

 private:
  T data_;  // the data stored in the package
  MeasurementProfile<T> measurementProfile;
};

template <class T> template <class... Args>
Packet<T>::Packet(Timer::Time timestamp, Args&&... args)
  : PacketBase(timestamp), data_(std::forward<Args>(args)...) {}

template <class T>
const T& Packet<T>::data() const {
  return data_;
}

template <class T>
T& Packet<T>::data() {
  return data_;
}

template <class T>
MeasurementProfile<T>::measurementProfile() {
  return measurementProfile;
}

}  // namespace pipert

#endif  //_PACKET_H_