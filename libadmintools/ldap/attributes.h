#pragma once
#include <string>

/*
   These classes contain all the attributes we
 * store in ldap. We want to make certain that
 * no mistakes will happen with accidental conversions
 * or wrong argument order in any programs we create.
 * This is why it is not allowed to use standard strings
 * or int's as arguments. Instead you have to use
 * DN, CN, FULL_NAME etc. No conversions from one to 
 * another are possible.
 */

namespace y {
  namespace ldap {
    class DN {
    public:
      explicit DN(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      DN & operator=(const DN &ref);
      bool operator==(const DN &ref) const;
      bool operator!=(const DN &ref) const;

    private:
      std::wstring val;
    };

    class UID_NUMBER {
    public:
      explicit UID_NUMBER(const int val) : val(val) {}

      // operators
      int operator()() const; // get value
      UID_NUMBER & operator=(const UID_NUMBER &ref) {
        if(this != &ref) {
          val = ref.val;
        }
        return *this;
      }
      bool operator==(const UID_NUMBER &ref) const;
      bool operator!=(const UID_NUMBER &ref) const;

    private:
      int val;
    };

    class UID {
    public:
      explicit UID(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      UID & operator=(const UID &ref);
      bool operator==(const UID &ref) const;
      bool operator!=(const UID &ref) const;

    private:
      std::wstring val;
    };

    class CN {
    public:
      explicit CN(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      CN & operator=(const CN &ref);
      bool operator==(const CN &ref) const;
      bool operator!=(const CN &ref) const;

    private:
      std::wstring val;
    };

    class SN {
    public:
      explicit SN(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      SN & operator=(const SN &ref);
      bool operator==(const SN &ref) const;
      bool operator!=(const SN &ref) const;

    private:
      std::wstring val;
    };

    class FULL_NAME {
    public:
      explicit FULL_NAME(const std::wstring & val) : val(val) {}
      explicit FULL_NAME(const CN & cn, const SN & sn);

      // operators
      const std::wstring & operator()() const; // get value
      FULL_NAME & operator=(const FULL_NAME &ref);
      bool operator==(const FULL_NAME &ref) const;
      bool operator!=(const FULL_NAME &ref) const;

    private:
      std::wstring val;
    };

    // used for class, like 1D, extern, personeel...
    class GID {
    public:
      explicit GID(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      GID & operator=(const GID &ref);
      bool operator==(const GID &ref) const;
      bool operator!=(const GID &ref) const;

    private:
      std::wstring val;
    };

    class GID_NUMBER {
    public:
      explicit GID_NUMBER(int val) : val(val) {}

      // operators
      int operator()() const; // get value
      GID_NUMBER & operator=(const GID_NUMBER &ref);
      bool operator==(const GID_NUMBER &ref) const;
      bool operator!=(const GID_NUMBER &ref) const;

    private:
      int val;
    };

    class WISA_ID {
    public:
      explicit WISA_ID(int val) : val(val) {}

      // operators
      int operator()() const; // get value
      WISA_ID & operator=(const WISA_ID &ref);
      bool operator==(const WISA_ID &ref) const;
      bool operator!=(const WISA_ID &ref) const;

    private:
      int val;
    };

    class MAIL {
    public:
      explicit MAIL(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      MAIL & operator=(const MAIL &ref);
      bool operator==(const MAIL &ref) const;
      bool operator!=(const MAIL &ref) const;

    private:
      std::wstring val;
    };

    class PASSWORD {
    public:
      explicit PASSWORD(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      PASSWORD & operator=(const PASSWORD &ref);
      bool operator==(const PASSWORD &ref) const;
      bool operator!=(const PASSWORD &ref) const;

    private:
      std::wstring val;
    };

    class DAY {
    public:
      explicit DAY(int val);

      // operators
      int operator()() const; // get value
      DAY & operator=(const DAY &ref);
      bool operator==(const DAY &ref) const;
      bool operator!=(const DAY &ref) const;

    private:
      int val;
    };

    class MONTH {
    public:
      explicit MONTH(int val);

      // operators
      int operator()() const; // get value
      MONTH & operator=(const MONTH &ref);
      bool operator==(const MONTH &ref) const;
      bool operator!=(const MONTH &ref) const;

    private:
      int val;
    };

    class YEAR {
    public:
      explicit YEAR(int val) : val(val) {}

      // operators
      int operator()() const; // get value
      YEAR & operator=(const YEAR &ref);
      bool operator==(const YEAR &ref) const;
      bool operator!=(const YEAR &ref) const;

    private:
      int val;
    };

    class DATE {
    public: 
      explicit DATE(const std::wstring & ldapDate);
      explicit DATE(const DAY & day, const MONTH & month, const YEAR & year);

      // operators
      int operator()() const; // get value
      std::wstring asString() const;
      int getDay() const;
      int getMonth() const;
      int getYear() const;
      DATE & operator=(const DATE &ref);
      bool operator==(const DATE &ref) const;
      bool operator!=(const DATE &ref) const;

    private:
      DAY day;
      MONTH month;
      YEAR year;
    };

    class HOMEDIR {
    public:
      explicit HOMEDIR(const std::wstring & val) : val(val) {}

      // operators
      const std::wstring & operator()() const; // get value
      HOMEDIR & operator=(const HOMEDIR &ref);
      bool operator==(const HOMEDIR &ref) const;
      bool operator!=(const HOMEDIR &ref) const;

    private:
      std::wstring val;
    };
  }
}