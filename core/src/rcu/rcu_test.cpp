#include <utest/utest.hpp>

#include <rcu/rcu.hpp>

using X = std::pair<int, int>;

TEST(rcu, Ctr) { rcu::Variable<X> ptr; }

TEST(rcu, ReadInit) {
  rcu::Variable<X> ptr(1, 2);

  auto reader = ptr.Read();
  EXPECT_EQ(std::make_pair(1, 2), *reader);
}

TEST(rcu, ChangeRead) {
  RunInCoro([] {
    rcu::Variable<X> ptr(1, 2);

    {
      auto writer = ptr.StartWrite();
      writer->first = 3;
      writer.Commit();
    }

    auto reader = ptr.Read();
    EXPECT_EQ(std::make_pair(3, 2), *reader);
  });
}

TEST(rcu, ChangeCancelRead) {
  RunInCoro([] {
    rcu::Variable<X> ptr(1, 2);

    {
      auto writer = ptr.StartWrite();
      writer->first = 3;
    }

    auto reader = ptr.Read();
    EXPECT_EQ(std::make_pair(1, 2), *reader);
  });
}

TEST(rcu, AssignRead) {
  RunInCoro([] {
    rcu::Variable<X> ptr(1, 2);

    ptr.Assign({3, 4});

    auto reader = ptr.Read();
    EXPECT_EQ(std::make_pair(3, 4), *reader);
  });
}

TEST(rcu, ReadNotCommitted) {
  RunInCoro([] {
    rcu::Variable<X> ptr(1, 2);

    auto reader1 = ptr.Read();
    EXPECT_EQ(std::make_pair(1, 2), *reader1);

    {
      auto writer = ptr.StartWrite();
      writer->second = 3;
      EXPECT_EQ(std::make_pair(1, 2), *reader1);

      auto reader2 = ptr.Read();
      EXPECT_EQ(std::make_pair(1, 2), *reader2);
    }

    EXPECT_EQ(std::make_pair(1, 2), *reader1);

    auto reader3 = ptr.Read();
    EXPECT_EQ(std::make_pair(1, 2), *reader3);
  });
}

TEST(rcu, ReadCommitted) {
  RunInCoro([] {
    rcu::Variable<X> ptr(1, 2);

    auto reader1 = ptr.Read();

    auto writer = ptr.StartWrite();
    writer->second = 3;
    auto reader2 = ptr.Read();

    writer.Commit();
    EXPECT_EQ(std::make_pair(1, 2), *reader1);
    EXPECT_EQ(std::make_pair(1, 2), *reader2);

    auto reader3 = ptr.Read();
    EXPECT_EQ(std::make_pair(1, 3), *reader3);
  });
}

struct Counted {
  Counted() { counter++; }
  Counted(const Counted&) : Counted() {}
  Counted(Counted&&) = delete;

  ~Counted() { counter--; }

  int value{1};

  static size_t counter;
};

size_t Counted::counter = 0;

TEST(rcu, Lifetime) {
  RunInCoro([] {
    EXPECT_EQ(0, Counted::counter);

    rcu::Variable<Counted> ptr;
    EXPECT_EQ(1, Counted::counter);

    {
      auto reader = ptr.Read();
      EXPECT_EQ(1, Counted::counter);
    }
    EXPECT_EQ(1, Counted::counter);

    {
      auto writer = ptr.StartWrite();
      EXPECT_EQ(2, Counted::counter);
    }
    EXPECT_EQ(1, Counted::counter);

    {
      auto reader2 = ptr.Read();
      EXPECT_EQ(1, Counted::counter);
      {
        auto writer = ptr.StartWrite();
        EXPECT_EQ(2, Counted::counter);

        writer->value = 10;
        writer.Commit();
        EXPECT_EQ(2, Counted::counter);
      }
      EXPECT_EQ(2, Counted::counter);
    }

    EXPECT_EQ(2, Counted::counter);

    {
      auto writer = ptr.StartWrite();
      EXPECT_EQ(3, Counted::counter);

      writer->value = 10;
      writer.Commit();
      EXPECT_EQ(1, Counted::counter);
    }
    EXPECT_EQ(1, Counted::counter);
  });
}

TEST(rcu, NoCopy) {
  struct X {
    X(X&&) = default;
    X(const X&) = delete;
    X& operator=(const X&) = delete;

    bool operator==(const X& other) const {
      return std::tie(x, y) == std::tie(other.x, other.y);
    }

    int x{};
    bool y{};
  };

  RunInCoro([] {
    rcu::Variable<X> ptr(X{1, false});

    // Write
    ptr.Assign(X{2, true});

    // Won't compile if uncomment, no X::X(const X&)
    // auto write_ptr = ptr.StartWrite();

    auto reader = ptr.Read();
    EXPECT_EQ((X{2, true}), *reader);
  });
}
