#ifndef JKR_UTIL_EVENT_FLAGS_HPP
#define JKR_UTIL_EVENT_FLAGS_HPP

// TODO: Add type restriction for <uchar, ushort, uint, ulong>
template<typename T>
class EventFlags {
  T signalFlags = 0;
  T eventFlags = 0;

public:
  EventFlags(T flags) : signalFlags(flags), eventFlags() {}
  EventFlags() : signalFlags(), eventFlags() {}

  void setSignalFlags(T bits) { signalFlags |= bits; }
  void clearEventFlags() { eventFlags = 0; }
  void processSignalFlags() { 
    eventFlags = signalFlags;
    signalFlags = 0;
  }

  bool hasSignalFlags() const { return signalFlags; }
  bool hasEventFlags() const { return eventFlags; }
  bool getEventFlags(T bit) const { return signalFlags & (1 << bit); }
};

typedef EventFlags<unsigned char> EventFlags1b;
typedef EventFlags<unsigned short> EventFlags2b;
typedef EventFlags<unsigned int> EventFlags4b;

#endif
