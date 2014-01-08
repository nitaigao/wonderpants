#ifndef rocketman_LookAtData_h
#define rocketman_LookAtData_h

struct LookAtData {
    
  LookAtData(int to_, int from_, int offset_)
  : to(to_), from(from_), offset(offset_) {

  }
  
  int from;
  int to;
  int offset;
  
};

#endif
