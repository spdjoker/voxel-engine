#ifndef JKR_UTIL_EVENT_FLAGS_HPP
#define JKR_UTIL_EVENT_FLAGS_HPP

// TODO: Add type restriction for <uchar, ushort, uint, ulong>
template<typename T>
class flags {
  T signalFlags = 0;
  T eventFlags = 0;

public:
  flags(T flags) : signalFlags(flags), eventFlags() {}
  flags() : signalFlags(), eventFlags() {}

  void setSignalFlags(T bits) { signalFlags |= bits; }
  void toggleSignalFlags(T bits) { signalFlags ^= bits; }
  void clearEventFlags() { eventFlags = 0; }
  void processSignalFlags() { 
    eventFlags = signalFlags;
    signalFlags = 0;
  }

  bool hasSignalFlags() const { return signalFlags; }
  bool hasAllSignalFlags(T bits) const { return (signalFlags & bits) == bits; }
  bool hasAnySignalFlags(T bits) const { return signalFlags & bits; }
  bool hasEventFlags() const { return eventFlags; }
  bool getEventFlags(T bit) const { return eventFlags & (1 << bit); }
};

#endif
