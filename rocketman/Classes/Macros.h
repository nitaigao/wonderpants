#ifndef MACROS_H
#define MACROS_H

#define SAFE_DELETE(o) if (o) { delete (o); (o) = 0; }

#define PROPERTY_READONLY(TYPE, NAME) \
public:\
inline TYPE NAME() const { return NAME ##_; };\
private:\
TYPE NAME ##_;

#endif
