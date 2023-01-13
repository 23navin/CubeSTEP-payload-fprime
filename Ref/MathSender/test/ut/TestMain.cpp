// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "Tester.hpp"

TEST(Nominal, ToDo) {
    Ref::Tester tester;
    tester.toDo();
}

TEST(Nominal, AddCommand) {
    Ref::Tester tester;
    tester.testAddCommand();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
