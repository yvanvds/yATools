#pragma once
#include <string>

namespace ldp {
  class DN {
  public:
    explicit DN(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    DN & operator=(const DN &ref);
    bool operator==(const DN &ref);
    bool operator!=(const DN &ref);

  private:
    std::string val;
  };
 
  class UID_NUMBER {
  public:
    explicit UID_NUMBER(const int val) : val(val) {}
 
    // operators
    int operator()(); // get value
    UID_NUMBER & operator=(const UID_NUMBER &ref) {
      if(this != &ref) {
        val = ref.val;
      }
      return *this;
    }
    bool operator==(const UID_NUMBER &ref);
    bool operator!=(const UID_NUMBER &ref);

  private:
    int val;
  };

  class UID {
  public:
    explicit UID(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    UID & operator=(const UID &ref);
    bool operator==(const UID &ref);
    bool operator!=(const UID &ref);

  private:
    std::string val;
  };

  class CN {
  public:
    explicit CN(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    CN & operator=(const CN &ref);
    bool operator==(const CN &ref);
    bool operator!=(const CN &ref);

  private:
    std::string val;
  };

  class SN {
  public:
    explicit SN(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    SN & operator=(const SN &ref);
    bool operator==(const SN &ref);
    bool operator!=(const SN &ref);

  private:
    std::string val;
  };

  class FULL_NAME {
  public:
    explicit FULL_NAME(const std::string & val) : val(val) {}
    explicit FULL_NAME(const CN & cn, const SN & sn);
 
    // operators
    const std::string & operator()(); // get value
    FULL_NAME & operator=(const FULL_NAME &ref);
    bool operator==(const FULL_NAME &ref);
    bool operator!=(const FULL_NAME &ref);

  private:
    std::string val;
  };

  // used for class, like 1D, extern, personeel...
  class GID {
  public:
    explicit GID(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    GID & operator=(const GID &ref);
    bool operator==(const GID &ref);
    bool operator!=(const GID &ref);

  private:
    std::string val;
  };

  class GID_NUMBER {
  public:
    explicit GID_NUMBER(int val) : val(val) {}
 
    // operators
    int operator()(); // get value
    GID_NUMBER & operator=(const GID_NUMBER &ref);
    bool operator==(const GID_NUMBER &ref);
    bool operator!=(const GID_NUMBER &ref);

  private:
    int val;
  };

  class WISA_ID {
  public:
    explicit WISA_ID(int val) : val(val) {}
 
    // operators
    int operator()(); // get value
    WISA_ID & operator=(const WISA_ID &ref);
    bool operator==(const WISA_ID &ref);
    bool operator!=(const WISA_ID &ref);

  private:
    int val;
  };

  class MAIL {
  public:
    explicit MAIL(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    MAIL & operator=(const MAIL &ref);
    bool operator==(const MAIL &ref);
    bool operator!=(const MAIL &ref);

  private:
    std::string val;
  };

  class PASSWORD {
  public:
    explicit PASSWORD(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    PASSWORD & operator=(const PASSWORD &ref);
    bool operator==(const PASSWORD &ref);
    bool operator!=(const PASSWORD &ref);

  private:
    std::string val;
  };

  class DAY {
  public:
    explicit DAY(int val) : val(val) {}
 
    // operators
    int operator()(); // get value
    DAY & operator=(const DAY &ref);
    bool operator==(const DAY &ref);
    bool operator!=(const DAY &ref);

  private:
    int val;
  };

  class MONTH {
  public:
    explicit MONTH(int val) : val(val) {}
 
    // operators
    int operator()(); // get value
    MONTH & operator=(const MONTH &ref);
    bool operator==(const MONTH &ref);
    bool operator!=(const MONTH &ref);

  private:
    int val;
  };

  class YEAR {
  public:
    explicit YEAR(int val) : val(val) {}
 
    // operators
    int operator()(); // get value
    YEAR & operator=(const YEAR &ref);
    bool operator==(const YEAR &ref);
    bool operator!=(const YEAR &ref);

  private:
    int val;
  };

  class DATE {
  public: 
    explicit DATE(const DAY & day, const MONTH & month, const YEAR & year);

    // operators
    int operator()(); // get value
    DATE & operator=(const DATE &ref);
    bool operator==(const DATE &ref);
    bool operator!=(const DATE &ref);

  private:
    DAY day;
    MONTH month;
    YEAR year;
  };
  
  class HOMEDIR {
  public:
    explicit HOMEDIR(const std::string & val) : val(val) {}
 
    // operators
    const std::string & operator()(); // get value
    HOMEDIR & operator=(const HOMEDIR &ref);
    bool operator==(const HOMEDIR &ref);
    bool operator!=(const HOMEDIR &ref);

  private:
    std::string val;
  };
};