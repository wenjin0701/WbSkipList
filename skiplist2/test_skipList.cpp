#include "skipList.h"
#include <iostream>
#include <string>
#include <cassert>

void test_skipList_basic_operations() {
    std::cout << "=== Testing SkipList Basic Operations ===" << std::endl;
    
    // Create a skip list with max level 6
    SkipList<std::string, std::string> skipList(6);
    
    // Test 1: Insert elements
    std::cout << "Test 1: Inserting elements" << std::endl;
    std::string key1 = "key1";
    std::string value1 = "value1";
    std::string key2 = "key2";
    std::string value2 = "value2";
    std::string key3 = "key3";
    std::string value3 = "value3";
    
    skipList.insert_element(key1, value1);
    skipList.insert_element(key2, value2);
    skipList.insert_element(key3, value3);
    
    // Display the skip list
    skipList.display_list();
    
    // Test 2: Search elements
    std::cout << "Test 2: Searching elements" << std::endl;
    std::string searchValue;
    assert(skipList.search_element(key1, searchValue) == true);
    assert(searchValue == value1);
    std::cout << "Found key1: " << searchValue << std::endl;
    
    assert(skipList.search_element(key2, searchValue) == true);
    assert(searchValue == value2);
    std::cout << "Found key2: " << searchValue << std::endl;
    
    assert(skipList.search_element(key3, searchValue) == true);
    assert(searchValue == value3);
    std::cout << "Found key3: " << searchValue << std::endl;
    
    // Test 3: Search non-existent element
    std::cout << "Test 3: Searching non-existent element" << std::endl;
    std::string nonExistentKey = "key4";
    assert(skipList.search_element(nonExistentKey, searchValue) == false);
    std::cout << "Correctly failed to find non-existent key: " << nonExistentKey << std::endl;
    
    // Test 4: Delete element
    std::cout << "Test 4: Deleting element" << std::endl;
    skipList.delete_element(key2);
    skipList.display_list();
    assert(skipList.search_element(key2, searchValue) == false);
    std::cout << "Correctly deleted key2" << std::endl;
    
    // Test 5: Insert set element (update existing element)
    std::cout << "Test 5: Inserting/updating element" << std::endl;
    std::string updatedValue1 = "updatedValue1";
    skipList.insert_set_element(key1, updatedValue1);
    skipList.display_list();
    assert(skipList.search_element(key1, searchValue) == true);
    assert(searchValue == updatedValue1);
    std::cout << "Found updated key1: " << searchValue << std::endl;
    
    // Test 6: Get size
    std::cout << "Test 6: Getting size" << std::endl;
    int size = skipList.size();
    std::cout << "Current size: " << size << std::endl;
    assert(size == 2); // key1 and key3
    
    std::cout << "=== All basic operation tests passed! ===" << std::endl;
}

void test_skipList_serialization() {
    std::cout << "\n=== Testing SkipList Serialization ===" << std::endl;
    
    // Create a skip list with max level 6
    SkipList<std::string, std::string> skipList1(6);
    
    // Insert some elements
    std::string key1 = "key1";
    std::string value1 = "value1";
    std::string key2 = "key2";
    std::string value2 = "value2";
    std::string key3 = "key3";
    std::string value3 = "value3";
    
    skipList1.insert_element(key1, value1);
    skipList1.insert_element(key2, value2);
    skipList1.insert_element(key3, value3);
    
    std::cout << "Original skip list:" << std::endl;
    skipList1.display_list();
    
    // Serialize the skip list
    std::string serializedData = skipList1.dump_file();
    std::cout << "Serialized data generated" << std::endl;
    
    // Create a new skip list and load the serialized data
    SkipList<std::string, std::string> skipList2(6);
    skipList2.load_file(serializedData);
    
    std::cout << "Loaded skip list:" << std::endl;
    skipList2.display_list();
    
    // Verify that the loaded skip list has the same elements
    std::string searchValue;
    assert(skipList2.search_element(key1, searchValue) == true);
    assert(searchValue == value1);
    std::cout << "Found key1 in loaded list: " << searchValue << std::endl;
    
    assert(skipList2.search_element(key2, searchValue) == true);
    assert(searchValue == value2);
    std::cout << "Found key2 in loaded list: " << searchValue << std::endl;
    
    assert(skipList2.search_element(key3, searchValue) == true);
    assert(searchValue == value3);
    std::cout << "Found key3 in loaded list: " << searchValue << std::endl;
    
    std::cout << "=== All serialization tests passed! ===" << std::endl;
}

int main() {
    test_skipList_basic_operations();
    test_skipList_serialization();
    std::cout << "\n=== All SkipList tests passed! ===" << std::endl;
    return 0;
}
