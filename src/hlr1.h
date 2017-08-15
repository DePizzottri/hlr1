// generated by D:\lib\sqlpp11\scripts\ddl2cpp -fail-on-parse postgres.sql hlr1 hlr1
#ifndef HLR_HLR_H
#define HLR_HLR_H

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

namespace hlr1
{
  namespace Users_
  {
    struct Id
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "id";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T id;
            T& operator()() { return id; }
            const T& operator()() const { return id; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
    struct Email
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "email";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T email;
            T& operator()() { return email; }
            const T& operator()() const { return email; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct FirstName
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "first_name";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T firstName;
            T& operator()() { return firstName; }
            const T& operator()() const { return firstName; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct LastName
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "last_name";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T lastName;
            T& operator()() { return lastName; }
            const T& operator()() const { return lastName; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct Gender
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "gender";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T gender;
            T& operator()() { return gender; }
            const T& operator()() const { return gender; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::char_, sqlpp::tag::require_insert>;
    };
    struct BirthDate
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "birth_date";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T birthDate;
            T& operator()() { return birthDate; }
            const T& operator()() const { return birthDate; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
  }

  struct Users: sqlpp::table_t<Users,
               Users_::Id,
               Users_::Email,
               Users_::FirstName,
               Users_::LastName,
               Users_::Gender,
               Users_::BirthDate>
  {
    struct _alias_t
    {
      static constexpr const char _literal[] =  "users";
      using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
      template<typename T>
      struct _member_t
      {
        T users;
        T& operator()() { return users; }
        const T& operator()() const { return users; }
      };
    };
  };
  namespace Location_
  {
    struct Id
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "id";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T id;
            T& operator()() { return id; }
            const T& operator()() const { return id; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
    struct Place
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "place";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T place;
            T& operator()() { return place; }
            const T& operator()() const { return place; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::require_insert>;
    };
    struct Country
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "country";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T country;
            T& operator()() { return country; }
            const T& operator()() const { return country; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct City
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "city";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T city;
            T& operator()() { return city; }
            const T& operator()() const { return city; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct Distance
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "distance";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T distance;
            T& operator()() { return distance; }
            const T& operator()() const { return distance; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
  }

  struct Location: sqlpp::table_t<Location,
               Location_::Id,
               Location_::Place,
               Location_::Country,
               Location_::City,
               Location_::Distance>
  {
    struct _alias_t
    {
      static constexpr const char _literal[] =  "location";
      using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
      template<typename T>
      struct _member_t
      {
        T location;
        T& operator()() { return location; }
        const T& operator()() const { return location; }
      };
    };
  };
  namespace Visit_
  {
    struct Id
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "id";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T id;
            T& operator()() { return id; }
            const T& operator()() const { return id; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
    struct Location
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "location";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T location;
            T& operator()() { return location; }
            const T& operator()() const { return location; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
    struct Usr
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "usr";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T usr;
            T& operator()() { return usr; }
            const T& operator()() const { return usr; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
    struct VisitedAt
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "visited_at";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T visitedAt;
            T& operator()() { return visitedAt; }
            const T& operator()() const { return visitedAt; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::require_insert>;
    };
    struct Mark
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "mark";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T mark;
            T& operator()() { return mark; }
            const T& operator()() const { return mark; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::require_insert>;
    };
  }

  struct Visit: sqlpp::table_t<Visit,
               Visit_::Id,
               Visit_::Location,
               Visit_::Usr,
               Visit_::VisitedAt,
               Visit_::Mark>
  {
    struct _alias_t
    {
      static constexpr const char _literal[] =  "visit";
      using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
      template<typename T>
      struct _member_t
      {
        T visit;
        T& operator()() { return visit; }
        const T& operator()() const { return visit; }
      };
    };
  };
} // namespace hlr1
#endif