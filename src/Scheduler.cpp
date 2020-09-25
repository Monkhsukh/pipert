#include "pipert/Scheduler.h"

#include <cassert>
#include <thread>
#include "ChannelImpl.h"
#include "SchedulerImpl.h"
#include "pipert/PacketStub.h"

namespace pipert {

Scheduler::Scheduler(int workers)
    : impl_(new SchedulerImpl(workers == 0 ? std::thread::hardware_concurrency()
                                           : workers)) {}

Scheduler::~Scheduler() {
  assert(impl_);
  delete impl_;
  impl_ = nullptr;
}

void Scheduler::Start() {
  assert(impl_);
  impl_->Start();
}

void Scheduler::Stop() {
  assert(impl_);
  impl_->Stop();
}

ChannelImpl* Scheduler::CreateChannelImpl(
    const char* name, int capacity, int packet_size, void* single_thread_object,
    ChannelBase::InternalCallback callback) {
  assert(impl_);
  ChannelImpl* ch_impl = new ChannelImpl(name, capacity, packet_size,
                                         single_thread_object, callback, impl_);
  return ch_impl;
}

}  // namespace pipert