#include <gmock/gmock.h>
#include <test.hpp>

TEST(testHelloWorld, workingFine) {
    EXPECT_FALSE(testHelloWorld());
}

int main(int argc, char** argv) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

bool testHelloWorld() {
    return true;
}