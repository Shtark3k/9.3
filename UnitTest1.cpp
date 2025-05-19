#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "../Project3/lab.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PriceManagerTests
{
    TEST_CLASS(UnitTest_PriceManager)
    {
    public:

        TEST_METHOD(TestSortByShop)
        {
            Price arr[3] = {
                {"P1","ShopC",10.0},
                {"P2","ShopA",20.0},
                {"P3","ShopB",30.0}
            };
            sortByShop(arr, 3);
            Assert::AreEqual(std::string("ShopA"), arr[0].shopName);
            Assert::AreEqual(std::string("ShopB"), arr[1].shopName);
            Assert::AreEqual(std::string("ShopC"), arr[2].shopName);
        }

        TEST_METHOD(TestFindByProductName_Found)
        {
            Price arr[2] = {
                {"Alpha","X",5.0},
                {"Beta","Y",6.0}
            };
            int idx = findByProductName(arr, 2, "Beta");
            Assert::AreEqual(1, idx);
        }

        TEST_METHOD(TestFindByProductName_NotFound)
        {
            Price arr[2] = {
                {"Alpha","X",5.0},
                {"Beta","Y",6.0}
            };
            int idx = findByProductName(arr, 2, "Gamma");
            Assert::AreEqual(-1, idx);
        }
    };
}
