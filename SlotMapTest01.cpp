#include <gtest/gtest.h>
#if defined(LOW_COMPLEXITY)
#include <slot_map_low_complexity.h>
template <class T, size_t PAGESIZE = 4096, size_t MINFREEINDICES = 64>
using slot_map = slot_map_low_complexity<T, dod::slot_map_key64<T>, PAGESIZE, MINFREEINDICES>;
#elif defined(ORDERED)
#include <ordered_slot_map.h>
template <class T, size_t PAGESIZE = 4096, size_t MINFREEINDICES = 64>
using slot_map = dod::ordered_slot_map<T, dod::slot_map_key64<T>, PAGESIZE, MINFREEINDICES>;
#else
#include <slot_map.h>
template <class T, size_t PAGESIZE = 4096, size_t MINFREEINDICES = 64>
using slot_map64 = slot_map<T, dod::slot_map_key64<T>, PAGESIZE, MINFREEINDICES>;
#endif

/*
void _onAssertionFailed(const char* expression, const char* srcFile, unsigned int srcLine)
{
    //
    printf("ASSERT FAILED %s, %s, %d\n", expression, srcFile, srcLine);
}
*/

TEST(SlotMapTest, BasicTest64)
{
    dod::slot_map64<int> slotMap;
    EXPECT_EQ(slotMap.size(), 0u);

    auto id1 = slotMap.emplace(1);
    EXPECT_EQ(slotMap.size(), 1u);

    auto id2 = slotMap.emplace(2);
    EXPECT_EQ(slotMap.size(), 2u);

    auto id3 = slotMap.emplace(3);
    EXPECT_EQ(slotMap.size(), 3u);

    auto id4 = slotMap.emplace(4);
    EXPECT_EQ(slotMap.size(), 4u);

    auto id5 = slotMap.emplace(5);
    EXPECT_EQ(slotMap.size(), 5u);

    const int* v1 = slotMap.get(id1);
    EXPECT_NE(v1, nullptr);
    EXPECT_EQ(*v1, 1);

    const int* v2 = slotMap.get(id2);
    EXPECT_NE(v2, nullptr);
    EXPECT_EQ(*v2, 2);

    const int* v3 = slotMap.get(id3);
    EXPECT_NE(v3, nullptr);
    EXPECT_EQ(*v3, 3);

    const int* v4 = slotMap.get(id4);
    EXPECT_NE(v4, nullptr);
    EXPECT_EQ(*v4, 4);

    const int* v5 = slotMap.get(id5);
    EXPECT_NE(v5, nullptr);
    EXPECT_EQ(*v5, 5);

    slotMap.erase(id1);
    EXPECT_EQ(slotMap.size(), 4u);

    slotMap.erase(id2);
    EXPECT_EQ(slotMap.size(), 3u);

    slotMap.erase(id3);
    EXPECT_EQ(slotMap.size(), 2u);

    slotMap.erase(id4);
    EXPECT_EQ(slotMap.size(), 1u);

    slotMap.erase(id5);
    EXPECT_EQ(slotMap.size(), 0u);

    slotMap.clear();
}

TEST(SlotMapTest, BasicTest32)
{
    dod::slot_map32<int> slotMap;
    EXPECT_EQ(slotMap.size(), 0u);

    auto id1 = slotMap.emplace(1);
    EXPECT_EQ(slotMap.size(), 1u);

    auto id2 = slotMap.emplace(2);
    EXPECT_EQ(slotMap.size(), 2u);

    auto id3 = slotMap.emplace(3);
    EXPECT_EQ(slotMap.size(), 3u);

    auto id4 = slotMap.emplace(4);
    EXPECT_EQ(slotMap.size(), 4u);

    auto id5 = slotMap.emplace(5);
    EXPECT_EQ(slotMap.size(), 5u);

    const int* v1 = slotMap.get(id1);
    EXPECT_NE(v1, nullptr);
    EXPECT_EQ(*v1, 1);

    const int* v2 = slotMap.get(id2);
    EXPECT_NE(v2, nullptr);
    EXPECT_EQ(*v2, 2);

    const int* v3 = slotMap.get(id3);
    EXPECT_NE(v3, nullptr);
    EXPECT_EQ(*v3, 3);

    const int* v4 = slotMap.get(id4);
    EXPECT_NE(v4, nullptr);
    EXPECT_EQ(*v4, 4);

    const int* v5 = slotMap.get(id5);
    EXPECT_NE(v5, nullptr);
    EXPECT_EQ(*v5, 5);

    slotMap.erase(id1);
    EXPECT_EQ(slotMap.size(), 4u);

    slotMap.erase(id2);
    EXPECT_EQ(slotMap.size(), 3u);

    slotMap.erase(id3);
    EXPECT_EQ(slotMap.size(), 2u);

    slotMap.erase(id4);
    EXPECT_EQ(slotMap.size(), 1u);

    slotMap.erase(id5);
    EXPECT_EQ(slotMap.size(), 0u);

    slotMap.clear();
}

TEST(SlotMapTest, NonTrivialCtorDtor)
{
    slot_map<std::string> slotMap;
    EXPECT_EQ(slotMap.size(), 0u);

    {
        auto id1 = slotMap.emplace("one");
        EXPECT_EQ(slotMap.size(), 1u);

        auto id2 = slotMap.emplace("two");
        EXPECT_EQ(slotMap.size(), 2u);

        auto id3 = slotMap.emplace("three");
        EXPECT_EQ(slotMap.size(), 3u);

        auto id4 = slotMap.emplace("four");
        EXPECT_EQ(slotMap.size(), 4u);

        auto id5 = slotMap.emplace("five");
        EXPECT_EQ(slotMap.size(), 5u);

        const std::string* v1 = slotMap.get(id1);
        EXPECT_NE(v1, nullptr);
        EXPECT_STREQ(v1->c_str(), "one");

        const std::string* v2 = slotMap.get(id2);
        EXPECT_NE(v2, nullptr);
        EXPECT_STREQ(v2->c_str(), "two");

        const std::string* v3 = slotMap.get(id3);
        EXPECT_NE(v3, nullptr);
        EXPECT_STREQ(v3->c_str(), "three");

        const std::string* v4 = slotMap.get(id4);
        EXPECT_NE(v4, nullptr);
        EXPECT_STREQ(v4->c_str(), "four");

        const std::string* v5 = slotMap.get(id5);
        EXPECT_NE(v5, nullptr);
        EXPECT_STREQ(v5->c_str(), "five");

        slotMap.clear();
        EXPECT_EQ(slotMap.empty(), true);

        auto id6 = slotMap.emplace("six");
        EXPECT_EQ(slotMap.size(), 1u);

        const std::string* v6 = slotMap.get(id6);
        EXPECT_NE(v6, nullptr);
        EXPECT_STREQ(v6->c_str(), "six");

        EXPECT_EQ(slotMap.has_key(id1), false);
        EXPECT_EQ(slotMap.has_key(id2), false);
        EXPECT_EQ(slotMap.has_key(id3), false);
        EXPECT_EQ(slotMap.has_key(id4), false);
        EXPECT_EQ(slotMap.has_key(id5), false);
        EXPECT_EQ(slotMap.has_key(id6), true);

        // Note: by calling `reset` we guarantee that we are not going to store/use any of previously allocated IDs
        slotMap.reset();
    }

    auto id7 = slotMap.emplace("seven");
    EXPECT_EQ(slotMap.size(), 1u);

    auto id8 = slotMap.emplace("eight");
    EXPECT_EQ(slotMap.size(), 2u);

    auto id9 = slotMap.emplace("nine");
    EXPECT_EQ(slotMap.size(), 3u);

    EXPECT_EQ(slotMap.has_key(id7), true);
    EXPECT_EQ(slotMap.has_key(id8), true);
    EXPECT_EQ(slotMap.has_key(id9), true);

    const std::string* v7 = slotMap.get(id7);
    EXPECT_NE(v7, nullptr);
    EXPECT_STREQ(v7->c_str(), "seven");

    const std::string* v8 = slotMap.get(id8);
    EXPECT_NE(v8, nullptr);
    EXPECT_STREQ(v8->c_str(), "eight");

    const std::string* v9 = slotMap.get(id9);
    EXPECT_NE(v9, nullptr);
    EXPECT_STREQ(v9->c_str(), "nine");

    std::optional<std::string> r7 = slotMap.pop(id7);
    EXPECT_EQ(slotMap.has_key(id7), false);
    EXPECT_EQ(r7.has_value(), true);
    EXPECT_STREQ(r7.value().c_str(), "seven");

    std::optional<std::string> _r7 = slotMap.pop(id7);
    EXPECT_EQ(_r7.has_value(), false);
}

TEST(SlotMapTest, TagTest64)
{
    dod::slot_map64<int> slotMap;
    EXPECT_EQ(slotMap.size(), 0u);

    auto id1 = slotMap.emplace(1);
    EXPECT_EQ(slotMap.size(), 1u);

    auto id2 = slotMap.emplace(2);
    EXPECT_EQ(slotMap.size(), 2u);

    EXPECT_TRUE(slotMap.has_key(id1));
    EXPECT_TRUE(slotMap.has_key(id2));

    id1.set_tag(4095);
    id2.set_tag(13);

    EXPECT_TRUE(slotMap.has_key(id1));
    EXPECT_TRUE(slotMap.has_key(id2));

    auto ud1 = id1.get_tag();
    EXPECT_EQ(ud1, 4095u);
    auto ud2 = id2.get_tag();
    EXPECT_EQ(ud2, 13u);
}

TEST(SlotMapTest, TagTest32)
{
    dod::slot_map32<int> slotMap;
    EXPECT_EQ(slotMap.size(), 0u);

    auto id1 = slotMap.emplace(1);
    EXPECT_EQ(slotMap.size(), 1u);

    auto id2 = slotMap.emplace(2);
    EXPECT_EQ(slotMap.size(), 2u);

    EXPECT_TRUE(slotMap.has_key(id1));
    EXPECT_TRUE(slotMap.has_key(id2));

    id1.set_tag(1);
    id2.set_tag(3);

    EXPECT_TRUE(slotMap.has_key(id1));
    EXPECT_TRUE(slotMap.has_key(id2));

    auto ud1 = id1.get_tag();
    EXPECT_EQ(ud1, 1u);
    auto ud2 = id2.get_tag();
    EXPECT_EQ(ud2, 3u);
}

TEST(SlotMapTest, KeyImplicitConversionToNumber64)
{
    auto key = dod::slot_map_key64<int>::invalid();
    uint64_t test = key;
    EXPECT_EQ(test, 0ull);
}

TEST(SlotMapTest, KeyImplicitConversionToNumber32)
{
    auto key = dod::slot_map_key32<int>::invalid();
    uint32_t test = key;
    EXPECT_EQ(test, 0ull);
}

void testFunction(slot_map<std::string>::key k, const slot_map<std::string>& slotMap)
{
    const std::string* v = slotMap.get(k);
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v->c_str(), "test");
}

TEST(SlotMapTest, ConstantGetter)
{
    slot_map<std::string> slotMap;
    EXPECT_EQ(slotMap.size(), 0u);
    auto id = slotMap.emplace("test");
    testFunction(id, slotMap);
}

TEST(SlotMapTest, IteratorsComparison)
{
    slot_map<std::string> slotMap;
    EXPECT_FALSE(slotMap.begin() != slotMap.end());
    EXPECT_TRUE(slotMap.begin() == slotMap.end());

    EXPECT_FALSE(slotMap.items().begin() != slotMap.items().end());
    EXPECT_TRUE(slotMap.items().begin() == slotMap.items().end());
}

TEST(SlotMapTest, Iterator)
{
    slot_map<int> slotMap;
    ASSERT_EQ(0u, slotMap.size());

    auto id1 = slotMap.emplace(12);
    auto id2 = slotMap.emplace(13);

    ASSERT_TRUE(slotMap.has_key(id1));
    ASSERT_TRUE(slotMap.has_key(id2));

    slotMap.erase(id2);
    ASSERT_FALSE(slotMap.has_key(id2));

    for (const auto& [key, val] : slotMap.items()) {
        EXPECT_TRUE(slotMap.has_key(key));
        EXPECT_EQ(key, id1);
    }
    for (const auto& val : slotMap) {
        EXPECT_EQ(val, 12);
    }
}

std::atomic<int> ctorCount = 0;
std::atomic<int> dtorCount = 0;

struct Counter
{
    Counter() { ctorCount++; }
    ~Counter() { dtorCount++; }

    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;
    Counter(Counter&&) = delete;
    Counter& operator=(Counter&&) = delete;
};

TEST(SlotMapTest, CheckCtorsDtors)
{

    ctorCount = 0;
    dtorCount = 0;

    {
        EXPECT_EQ(ctorCount, 0);
        EXPECT_EQ(dtorCount, 0);
        slot_map<Counter> slotMap;

        slotMap.emplace();
        auto id2 = slotMap.emplace();
        auto id3 = slotMap.emplace();
        EXPECT_EQ(ctorCount, 3);
        EXPECT_EQ(dtorCount, 0);

        slotMap.erase(id2);
        slotMap.erase(id3);
        EXPECT_EQ(ctorCount, 3);
        EXPECT_EQ(dtorCount, 2);

        slotMap.clear();
        EXPECT_EQ(ctorCount, 3);
        EXPECT_EQ(dtorCount, 3);

        slotMap.emplace();
        slotMap.emplace();
        slotMap.emplace();
        EXPECT_EQ(ctorCount, 6);
        EXPECT_EQ(dtorCount, 3);
    }

    EXPECT_EQ(ctorCount, 6);
    EXPECT_EQ(dtorCount, 6);
}

std::atomic<int> ctorCount2 = 0;
std::atomic<int> moveCount2 = 0;
std::atomic<int> dtorCount2 = 0;

struct Counter2
{
    Counter2() { ctorCount2++; }
    ~Counter2() { dtorCount2++; }

    Counter2(const Counter2&) = delete;
    Counter2& operator=(const Counter2&) = delete;
    Counter2(const Counter2&&) { moveCount2++; }
    Counter2& operator=(Counter2&&)
    {
        moveCount2++;
        return *this;
    }
};

TEST(SlotMapTest, CheckMoves)
{
    ctorCount2 = 0;
    dtorCount2 = 0;
    moveCount2 = 0;

    {
        EXPECT_EQ(ctorCount2, 0);
        EXPECT_EQ(dtorCount2, 0);
        EXPECT_EQ(moveCount2, 0);
        slot_map<Counter2> slotMap;

        slotMap.emplace();
        auto id2 = slotMap.emplace();
        auto id3 = slotMap.emplace();
        EXPECT_EQ(ctorCount2, 3);
        EXPECT_EQ(dtorCount2, 0);
        EXPECT_EQ(moveCount2, 0);

        slotMap.erase(id2);
        EXPECT_EQ(ctorCount2, 3);
        EXPECT_EQ(dtorCount2, 1);
        EXPECT_EQ(moveCount2, 0);

        {
            std::optional<Counter2> v = slotMap.pop(id3);
            EXPECT_EQ(ctorCount2, 3);
            EXPECT_EQ(dtorCount2, 3);
            EXPECT_EQ(moveCount2, 2);
            EXPECT_TRUE(v.has_value());
        }
        EXPECT_EQ(ctorCount2, 3);
        EXPECT_EQ(dtorCount2, 4);
        EXPECT_EQ(moveCount2, 2);

        {
            std::optional<Counter2> v = slotMap.pop(id3);
            EXPECT_EQ(ctorCount2, 3);
            EXPECT_EQ(dtorCount2, 4);
            EXPECT_EQ(moveCount2, 2);
            EXPECT_FALSE(v.has_value());
        }
        EXPECT_EQ(ctorCount2, 3);
        EXPECT_EQ(dtorCount2, 4);
        EXPECT_EQ(moveCount2, 2);

        slotMap.clear();
        EXPECT_EQ(ctorCount2, 3);
        EXPECT_EQ(dtorCount2, 5);
        EXPECT_EQ(moveCount2, 2);

        slotMap.emplace();
        slotMap.emplace();
        slotMap.emplace();
        EXPECT_EQ(ctorCount2, 6);
        EXPECT_EQ(dtorCount2, 5);
        EXPECT_EQ(moveCount2, 2);
    }

    EXPECT_EQ(ctorCount2, 6);
    EXPECT_EQ(dtorCount2, 8);
    EXPECT_EQ(moveCount2, 2);
}

TEST(SlotMapTest, SwapTest)
{
    slot_map<std::string> slotMapA;
    slot_map<std::string> slotMapB;

    EXPECT_EQ(slotMapA.size(), 0u);
    EXPECT_EQ(slotMapB.size(), 0u);

    auto id1 = slotMapA.emplace("one");
    auto id2 = slotMapA.emplace("two");
    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 0u);

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));
    const std::string* v1 = slotMapA.get(id1);
    ASSERT_NE(v1, nullptr);
    EXPECT_STREQ(v1->c_str(), "one");
    const std::string* v2 = slotMapA.get(id2);
    ASSERT_NE(v2, nullptr);
    EXPECT_STREQ(v2->c_str(), "two");

    slotMapA.swap(slotMapB);
    EXPECT_EQ(slotMapA.size(), 0u);
    EXPECT_EQ(slotMapB.size(), 2u);

    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));
    v1 = slotMapB.get(id1);
    ASSERT_NE(v1, nullptr);
    EXPECT_STREQ(v1->c_str(), "one");
    v2 = slotMapB.get(id2);
    ASSERT_NE(v2, nullptr);
    EXPECT_STREQ(v2->c_str(), "two");
}

TEST(SlotMapTest, CopyAssignment)
{
    slot_map<std::string> slotMapA;
    slot_map<std::string> slotMapB;
    EXPECT_EQ(slotMapA.size(), 0u);
    EXPECT_EQ(slotMapB.size(), 0u);

    auto id1 = slotMapA.emplace("one");
    auto id2 = slotMapA.emplace("two");

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));

    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 0u);

    slotMapB = slotMapA;
    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 2u);

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    {
        std::string* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_STREQ(av1->c_str(), "one");
        std::string* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_STREQ(av2->c_str(), "two");

        const std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        const std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");

        *av1 = "1";
        *av2 = "2";
    }

    {
        const std::string* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_STREQ(av1->c_str(), "1");
        const std::string* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_STREQ(av2->c_str(), "2");

        const std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        const std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");
    }

    slotMapA.erase(id1);
    slotMapA.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    slotMapB.erase(id1);
    slotMapB.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));
}

TEST(SlotMapTest, CopyAssignmentPod)
{
    slot_map<int> slotMapA;
    slot_map<int> slotMapB;
    EXPECT_EQ(slotMapA.size(), 0u);
    EXPECT_EQ(slotMapB.size(), 0u);

    auto id1 = slotMapA.emplace(1);
    auto id2 = slotMapA.emplace(2);

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));

    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 0u);

    slotMapB = slotMapA;
    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 2u);

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    {
        int* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_EQ(*av1, 1);
        int* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_EQ(*av2, 2);

        const int* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_EQ(*bv1, 1);
        const int* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_EQ(*bv2, 2);

        *av1 = 3;
        *av2 = 4;
    }

    {
        const int* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_EQ(*av1, 3);
        const int* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_EQ(*av2, 4);

        const int* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_EQ(*bv1, 1);
        const int* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_EQ(*bv2, 2);
    }

    slotMapA.erase(id1);
    slotMapA.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    slotMapB.erase(id1);
    slotMapB.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));
}

TEST(SlotMapTest, CopyCtor)
{
    slot_map<std::string> slotMapA;
    EXPECT_EQ(slotMapA.size(), 0u);

    auto id1 = slotMapA.emplace("one");
    auto id2 = slotMapA.emplace("two");

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));

    EXPECT_EQ(slotMapA.size(), 2u);

    slot_map<std::string> slotMapB(slotMapA);
    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 2u);

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    {
        std::string* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_STREQ(av1->c_str(), "one");
        std::string* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_STREQ(av2->c_str(), "two");

        const std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        const std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");

        *av1 = "1";
        *av2 = "2";
    }

    {
        const std::string* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_STREQ(av1->c_str(), "1");
        const std::string* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_STREQ(av2->c_str(), "2");

        const std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        const std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");
    }

    slotMapA.erase(id1);
    slotMapA.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    slotMapB.erase(id1);
    slotMapB.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));
}

TEST(SlotMapTest, CopyAssignmentWithInactivePages)
{
    dod::slot_map64<std::string, 32, 0> slotMapA;
    dod::slot_map64<std::string, 32, 0> slotMapB;

    // allocate and remove some IDs (to waste a few allocation pages)
    for (size_t i = 0; i < static_cast<size_t>(decltype(slotMapA)::kPageSize) * 2; i++)
    {
        for (size_t j = 0; j < static_cast<size_t>(decltype(slotMapA)::key::kMaxVersion) + 10; j++)
        {
            auto id = slotMapA.emplace();
            slotMapA.erase(id);
        }
    }
    slotMapA.clear();

    EXPECT_EQ(slotMapA.size(), 0u);
    EXPECT_EQ(slotMapB.size(), 0u);

    auto id1 = slotMapA.emplace("one");
    auto id2 = slotMapA.emplace("two");

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));

    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 0u);

    slotMapB = slotMapA;
    EXPECT_EQ(slotMapA.size(), 2u);
    EXPECT_EQ(slotMapB.size(), 2u);

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    {
        std::string* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_STREQ(av1->c_str(), "one");
        std::string* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_STREQ(av2->c_str(), "two");

        std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");

        *av1 = "1";
        *av2 = "2";
    }

    {
        std::string* av1 = slotMapA.get(id1);
        ASSERT_NE(av1, nullptr);
        EXPECT_STREQ(av1->c_str(), "1");
        std::string* av2 = slotMapA.get(id2);
        ASSERT_NE(av2, nullptr);
        EXPECT_STREQ(av2->c_str(), "2");

        std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");
    }

    slotMapA.erase(id1);
    slotMapA.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    slotMapB.erase(id1);
    slotMapB.erase(id2);
    EXPECT_FALSE(slotMapA.has_key(id1));
    EXPECT_FALSE(slotMapA.has_key(id2));
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_FALSE(slotMapB.has_key(id2));
}

TEST(SlotMapTest, MoveAssignment)
{
    auto id1 = dod::slot_map_key64<std::string>::invalid();
    auto id2 = dod::slot_map_key64<std::string>::invalid();

    slot_map<std::string> slotMapB;
    {
        slot_map<std::string> slotMapA;
        EXPECT_EQ(slotMapA.size(), 0u);
        EXPECT_EQ(slotMapB.size(), 0u);

        id1 = slotMapA.emplace("one");
        id2 = slotMapA.emplace("two");

        EXPECT_TRUE(slotMapA.has_key(id1));
        EXPECT_TRUE(slotMapA.has_key(id2));
        EXPECT_FALSE(slotMapB.has_key(id1));
        EXPECT_FALSE(slotMapB.has_key(id2));

        EXPECT_EQ(slotMapA.size(), 2u);
        EXPECT_EQ(slotMapB.size(), 0u);

        slotMapB = std::move(slotMapA);
        EXPECT_EQ(slotMapB.size(), 2u);
    }

    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    {
        std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");
    }

    slotMapB.erase(id1);
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    slotMapB.reset();
}

TEST(SlotMapTest, MoveCtor)
{
    slot_map<std::string> slotMapA;
    EXPECT_EQ(slotMapA.size(), 0u);

    auto id1 = slotMapA.emplace("one");
    auto id2 = slotMapA.emplace("two");

    EXPECT_TRUE(slotMapA.has_key(id1));
    EXPECT_TRUE(slotMapA.has_key(id2));

    EXPECT_EQ(slotMapA.size(), 2u);

    slot_map<std::string> slotMapB(std::move(slotMapA));
    EXPECT_EQ(slotMapB.size(), 2u);

    EXPECT_TRUE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    {
        std::string* bv1 = slotMapB.get(id1);
        ASSERT_NE(bv1, nullptr);
        EXPECT_STREQ(bv1->c_str(), "one");
        std::string* bv2 = slotMapB.get(id2);
        ASSERT_NE(bv2, nullptr);
        EXPECT_STREQ(bv2->c_str(), "two");
    }

    slotMapB.erase(id1);
    EXPECT_FALSE(slotMapB.has_key(id1));
    EXPECT_TRUE(slotMapB.has_key(id2));

    slotMapB.reset();
}
