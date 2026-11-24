#ifndef UTILS_H
#define UTILS_H

class utils {
  public:
    /*
      waits x milliseconds... Basically the same as a delay(int) that doesn't stop the whole program.
      Returns false until the timer is done.

      Params:
          ms = milliseconds the timer should wait until doing the next thing
          last = last time to check the ms against. Used as a separate variable so multiple wait calls can coexist.
    */ 
    static bool wait(unsigned long ms, unsigned long &last) {
        unsigned long now = millis();
        if(now - last < ms) return false;
        last = now;

        return true;
    }
};

#endif