#include "pch.h"
#include <gtest/gtest.h>
#include "BinarySearchTree.h"
#include <vector>
#include <string>

BinarySearchTree setUP() {
    BinarySearchTree bst = BinarySearchTree();
    bst.add(10, "Value for 10");
    bst.add(52, "Value for 52");
    bst.add(5, "Value for 5");
    bst.add(8, "Value for 8");
    bst.add(1, "Value for 1");
    bst.add(40, "Value for 40");
    bst.add(30, "Value for 30");
    bst.add(45, "Value for 45");

    return bst;
}

TEST(testBSTInsertion, add_test) {

    //Instantiation of BinarySearchTree
    BinarySearchTree bsTree;

    //Tree must be empty
    ASSERT_EQ(bsTree.size(), 0);

    //Add a key-value pair
    bsTree.add(15, "Value for 15");
    //size of tree must be 1
    ASSERT_EQ(bsTree.size(), 1);

    //Add another key-value pair
    bsTree.add(10, "Value for 10");
    //now size of tree must be 2
    ASSERT_EQ(bsTree.size(), 2);


    //The added keys must exist
    ASSERT_EQ(bsTree.search(10), "Value for 10");
    ASSERT_EQ(bsTree.search(15), "Value for 15");

}

TEST(testBSTTraversal, test_inorder) {
    //instantiate bst and get values from setUP:
    BinarySearchTree bst = setUP();

    //using vector as a sort of mutable data-type similar to python lists.
    std::vector<int> actual_output = bst.inorder_walk();
    std::vector<int> expected_output = { 1, 5, 8, 10, 30, 40, 45, 52 };
    
    EXPECT_EQ(actual_output, expected_output);

    //Add one more node
    bst.add(25, "Value for 25");

    //defining new variable for new expected output as c++ won't recognize the datatype otherwise;
    std::vector<int> new_expected_output = { 1, 5, 8, 10, 25, 30, 40, 45, 52 };

    //Insertion again and inorder_walk must return a different sequence
    EXPECT_EQ(bst.inorder_walk(), new_expected_output);
}

TEST(testBSTTraversal, test_postorder) {
    //instantiate bst and get values from setUP:
    BinarySearchTree bst = setUP();

    //again using vector as a sort of mutable data-type similar to python lists.
    std::vector<int> actual_output = bst.postorder_walk();
    std::vector<int> expected_output = { 1, 8, 5, 30, 45, 40, 52, 10 };

    EXPECT_EQ(actual_output, expected_output);

    //Add one more node
    bst.add(25, "Value for 25");

    //defining new variable for new expected output as c++ won't recognize the datatype otherwise;
    std::vector<int> new_expected_output = { 1, 8, 5, 25, 30, 45, 40, 52, 10 };

    //Insertion again and inorder_walk must return a different sequence
    EXPECT_EQ(bst.postorder_walk(), new_expected_output);
}

TEST(testBSTTraversal, test_preorder) {
    //instantiate bst and get values from setUP:
    BinarySearchTree bst = setUP();

    //again using vector as a sort of mutable data-type similar to python lists.
    std::vector<int> actual_output = bst.preorder_walk();
    std::vector<int> expected_output = { 10, 5, 1, 8, 52, 40, 30, 45 };

    EXPECT_EQ(actual_output, expected_output);

    //Add one more node
    bst.add(25, "Value for 25");

    //defining new variable for new expected output as c++ won't recognize the datatype otherwise;
    std::vector<int> new_expected_output = { 10, 5, 1, 8, 52, 40, 30, 25, 45 };

    //Insertion again and inorder_walk must return a different sequence
    EXPECT_EQ(bst.preorder_walk(), new_expected_output);
}


TEST(testBSTSearch, test_search) {
    //instantiate bst and get values from setUP:
    BinarySearchTree bst = setUP();

    std::string actual_output = bst.search(40);
    std::string expected_output = "Value for 40";

    ASSERT_EQ(actual_output, expected_output);
    
    //the function returns "False" in string if the key is not found while searching
    //so if it returns "False" it would indicate bool value false too.
    bool new_actual_output;
    if (bst.search(90) == "False") {
        new_actual_output = false;
    }
    ASSERT_FALSE(new_actual_output);

    bst.add(90, "Value for 90");
    ASSERT_EQ(bst.search(90), "Value for 90");
}


TEST(testBSTRemove, test_remove) {
    //instantiate bst and get values from setUP:
    BinarySearchTree bst = setUP();

    bst.remove(40);
    ASSERT_EQ(bst.size(), 7);
    
    std::vector<int>expected_inorder_walk = { 1, 5, 8, 10, 30, 45, 52 };
    std::vector<int>expected_preorder_walk = { 10, 5, 1, 8, 52, 30, 45 };
    EXPECT_EQ(bst.inorder_walk(), expected_inorder_walk);

    EXPECT_EQ(bst.preorder_walk(), expected_preorder_walk);
    /* test for preorder walk won't pass because the implementation is done 
    in such a way that the remove function will copy the value from the least
    key bearing node in the right subtree instead of the highest key bearing
    node in the left subtree to the current node(temp/root) being deleted*/
    //INSTEAD THE EXPECTED VALUE SHOULD BE: {10, 5, 1, 8, 52, 45, 30} for this implementation

    //checking for {10, 5, 1, 8, 52, 45, 30} again:
    std::vector<int>corrected_expected_preorder_walk = { 10, 5, 1, 8, 52, 45, 30 };
    EXPECT_EQ(bst.preorder_walk(), corrected_expected_preorder_walk);

}

//There's no direct way to compare tuples in C++

void assert_tuple_equal(const std::tuple<int, std::string>& expected, const std::tuple<int, std::string>& actual)
{
    EXPECT_EQ(std::get<0>(expected), std::get<0>(actual));
    EXPECT_EQ(std::get<1>(expected), std::get<1>(actual));
}

TEST(testBSTsmallest, test_smallest) {
    //instantiate bst and get values from setUP:
    BinarySearchTree bst = setUP();

    std::tuple<int, std::string> expected = std::make_tuple(1, "Value for 1");
    std::tuple<int, std::string> actual = bst.smallest();
    assert_tuple_equal(expected, actual);

    //Add some more nodes:
    bst.add(6, "Value for 6");
    bst.add(4, "Value for 4");
    bst.add(0, "Value for 0");
    bst.add(32, "Value for 32");

    //now the smallest key has to be 0:
    std::tuple<int, std::string> new_expected = std::make_tuple(0, "Value for 0");
    std::tuple<int, std::string> new_actual = bst.smallest();
    assert_tuple_equal(new_expected, new_actual);
}

TEST(testBSTlargest, test_largest) {
    //instantiate bst and get values from setUP:
    BinarySearchTree bst = setUP();

    std::tuple<int, std::string> expected = std::make_tuple(52, "Value for 52");
    std::tuple<int, std::string> actual = bst.largest();
    assert_tuple_equal(expected, actual);

    //Add some more nodes:
    bst.add(6, "Value for 6");
    bst.add(54, "Value for 54");
    bst.add(0, "Value for 0");
    bst.add(32, "Value for 32");

    //now the smallest key has to be 0:
    std::tuple<int, std::string> new_expected = std::make_tuple(54, "Value for 54");
    std::tuple<int, std::string> new_actual = bst.largest();
    assert_tuple_equal(new_expected, new_actual);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}