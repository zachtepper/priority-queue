#include <gtest/gtest.h>
#include <string>
#include "priorityqueue.h"

TEST(priorityqueue, one) {
    // multiple instances of priorityqueue with different data typese
    priorityqueue<int> pqInt;
    priorityqueue<string> pqString;
    priorityqueue<double> pqDouble;
    // test size 
    ASSERT_EQ(pqInt.Size(), 0);
    ASSERT_EQ(pqString.Size(), 0);
    ASSERT_EQ(pqDouble.Size(), 0);
    // test enqueue
    pqInt.enqueue(3, 4);
    EXPECT_EQ(pqInt.Size(), 1);
    pqInt.enqueue(10, 2);
    ASSERT_EQ(pqInt.Size(), 2);
    pqString.enqueue("Test", 2);
    ASSERT_EQ(pqString.Size(), 1);
    pqDouble.enqueue(3.14, 7);
    ASSERT_EQ(pqDouble.Size(), 1);
    // test with duplicates 
    pqInt.enqueue(9, 4);
    EXPECT_EQ(pqInt.Size(), 3);
    pqInt.enqueue(14, 4);
    EXPECT_EQ(pqInt.Size(), 4);
    pqInt.enqueue(1, 2);
    ASSERT_EQ(pqInt.Size(), 5);
}

TEST(priorityqueue, toString) {
    string pqIntExpectedResult = "2 value: 3\n6 value: 5\n9 value: 17\n";
    string pqStringExpectedResult = "1 value: XYZ\n2 value: ABC\n3 value: 123\n";
    priorityqueue<int> pqInt;
    priorityqueue<string> pqString;
    priorityqueue<double> pqDouble;
    pqInt.enqueue(5, 6);
    pqInt.enqueue(3, 2);
    pqInt.enqueue(17, 9);
    EXPECT_EQ(pqInt.Size(), 3);
    ASSERT_EQ(pqInt.toString(), pqIntExpectedResult);
    pqString.enqueue("ABC", 2);
    pqString.enqueue("123", 3);
    pqString.enqueue("XYZ", 1);
    EXPECT_EQ(pqString.Size(), 3);
    ASSERT_EQ(pqString.toString(), pqStringExpectedResult);
    pqIntExpectedResult = "2 value: 3\n2 value: 4\n6 value: 5\n6 value: 10\n6 value: 2\n9 value: 17\n9 value: 1\n9 value: 22\n";
    // start adding duplicates 
    pqInt.enqueue(10, 6);
    pqInt.enqueue(2, 6);
    pqInt.enqueue(1, 9);
    pqInt.enqueue(22, 9);
    pqInt.enqueue(4, 2);
    EXPECT_EQ(pqInt.Size(), 8);
    ASSERT_EQ(pqInt.toString(), pqIntExpectedResult);
    // test with empty priorityqueue 
    ASSERT_EQ(pqDouble.toString(), "");
}

TEST(priorityqueue, clear) {
    priorityqueue<int> pqInt;
    string pqIntExpectedResult = "2 value: 1\n5 value: 1\n10 value: 1\n14 value: 1\n15 value: 1\n15 value: 1\n15 value: 1\n";
    EXPECT_EQ(pqInt.Size(), 0);
    EXPECT_EQ(pqInt.toString(), "");
    pqInt.enqueue(1, 10);
    pqInt.enqueue(1, 5);
    pqInt.enqueue(1, 15);
    pqInt.enqueue(1, 14);
    pqInt.enqueue(1, 2);
    pqInt.enqueue(1, 15);
    pqInt.enqueue(1, 15);
    EXPECT_EQ(pqInt.toString(), pqIntExpectedResult);
    EXPECT_EQ(pqInt.Size(), 7);
    pqInt.clear();
    ASSERT_EQ(pqInt.Size(), 0);
    ASSERT_EQ(pqInt.toString(), "");
}

TEST(priorityqueue, equalsOperator) {
    priorityqueue<int> pqInt;
    priorityqueue<int> pqInt2;
    string pqInt2String = "1 value: 6\n5 value: 8\n9 value: 4\n9 value: 10\n";
    EXPECT_EQ(pqInt.Size(), 0);
    EXPECT_EQ(pqInt2.Size(), 0);
    pqInt2.enqueue(8, 5);
    pqInt2.enqueue(4, 9);
    pqInt2.enqueue(6, 1);
    pqInt2.enqueue(10, 9);
    EXPECT_EQ(pqInt2.Size(), 4);
    EXPECT_EQ(pqInt2.toString(), pqInt2String);
    pqInt = pqInt2;
    ASSERT_EQ(pqInt.Size(), pqInt2.Size());
    ASSERT_EQ(pqInt.toString(), pqInt2String);
    pqInt2 = pqInt2;
    ASSERT_EQ(pqInt2.Size(), 4);
    ASSERT_EQ(pqInt2.toString(), pqInt2String);
    pqInt2.clear();
    pqInt = pqInt2;
    EXPECT_EQ(pqInt2.Size(), 0);
    EXPECT_EQ(pqInt2.toString(), "");
    ASSERT_EQ(pqInt.Size(), 0);
    ASSERT_EQ(pqInt.toString(), "");
}

TEST(priorityqueue, beginAndNext) {
    int value; 
    int priority;
    
    priorityqueue<int> pqInt;
    priorityqueue<int> pqInt2;
    pqInt.enqueue(1, 6);
    pqInt.enqueue(1, 4);
    pqInt.enqueue(1, 8);
    pqInt.enqueue(1, 10);
    pqInt.enqueue(1, 3);
    pqInt.enqueue(1, 5);
    pqInt.enqueue(1, 5);
    pqInt.enqueue(1, 1);
    EXPECT_EQ(pqInt.Size(), 8);
    
    pqInt.begin();
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 1);
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 3);
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 4);
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 5);
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 5);
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 6);
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 8);
    pqInt.next(value, priority);
    ASSERT_EQ(priority, 10);
    
    value = 0;
    priority = 0;
    
    pqInt2.enqueue(1, 1000);
    pqInt2.enqueue(1, 500);
    pqInt2.enqueue(1, 1500);
    pqInt2.enqueue(1, 250);
    pqInt2.enqueue(1, 750);
    pqInt2.enqueue(1, 1250);
    pqInt2.enqueue(1, 1750);
    pqInt2.enqueue(1, 1000);
    pqInt2.enqueue(1, 500);
    pqInt2.enqueue(1, 1500);
    pqInt2.enqueue(1, 250);
    pqInt2.enqueue(1, 750);
    pqInt2.enqueue(1, 1250);
    pqInt2.enqueue(1, 1750);
    EXPECT_EQ(pqInt2.Size(), 14);
    
    pqInt2.begin();
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 250);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 250);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 500);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 500);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 750);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 750);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1000);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1000);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1250);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1250);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1500);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1500);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1750);
    pqInt2.next(value, priority);
    ASSERT_EQ(priority, 1750);
}

TEST(priorityqueue, dequeue) {
    priorityqueue<int> pqInt;
    
    pqInt.enqueue(1, 1000);
    pqInt.enqueue(2, 500);
    pqInt.enqueue(3, 1500);
    pqInt.enqueue(4, 250);
    pqInt.enqueue(5, 750);
    pqInt.enqueue(6, 1250);
    pqInt.enqueue(7, 1750);
    pqInt.enqueue(8, 1000);
    pqInt.enqueue(9, 500);
    pqInt.enqueue(10, 1500);
    pqInt.enqueue(11, 250);
    pqInt.enqueue(12, 750);
    pqInt.enqueue(13, 1250);
    pqInt.enqueue(14, 1750);
    EXPECT_EQ(pqInt.Size(), 14);
    ASSERT_EQ(pqInt.dequeue(), 4);
    ASSERT_EQ(pqInt.dequeue(), 11);
    ASSERT_EQ(pqInt.dequeue(), 2);
    ASSERT_EQ(pqInt.dequeue(), 9);
    ASSERT_EQ(pqInt.dequeue(), 5);
    ASSERT_EQ(pqInt.dequeue(), 12);
    ASSERT_EQ(pqInt.dequeue(), 1);
    ASSERT_EQ(pqInt.dequeue(), 8);
    ASSERT_EQ(pqInt.dequeue(), 6);
    ASSERT_EQ(pqInt.dequeue(), 13);
    ASSERT_EQ(pqInt.dequeue(), 3);
    ASSERT_EQ(pqInt.dequeue(), 10);
    ASSERT_EQ(pqInt.dequeue(), 7);
    ASSERT_EQ(pqInt.dequeue(), 14);
}

TEST(priorityqueue, peek) {
    priorityqueue<int> pqInt;
    
    pqInt.enqueue(1, 1000);
    pqInt.enqueue(2, 500);
    pqInt.enqueue(3, 1500);
    pqInt.enqueue(4, 250);
    pqInt.enqueue(5, 750);
    pqInt.enqueue(6, 1250);
    pqInt.enqueue(7, 1750);
    pqInt.enqueue(8, 1000);
    EXPECT_EQ(pqInt.Size(), 8);
    ASSERT_EQ(pqInt.peek(), 4);
    pqInt.dequeue();
    ASSERT_EQ(pqInt.peek(), 2);
    pqInt.dequeue();
    ASSERT_EQ(pqInt.peek(), 5);
    pqInt.dequeue();
    ASSERT_EQ(pqInt.peek(), 1);
    pqInt.dequeue();
    ASSERT_EQ(pqInt.peek(), 8);
    pqInt.dequeue();
    ASSERT_EQ(pqInt.peek(), 6);
    pqInt.dequeue();
    ASSERT_EQ(pqInt.peek(), 3);
    pqInt.dequeue();
    ASSERT_EQ(pqInt.peek(), 7);
    pqInt.dequeue();
    
}

TEST(priorityqueue, equalityOperator) {
    priorityqueue<int> pqInt;
    priorityqueue<int> pqInt2;
    priorityqueue<int> pqInt3;
    priorityqueue<int> pqInt4;
    priorityqueue<int> pqInt5;
    
    pqInt.enqueue(1, 1000);
    pqInt.enqueue(2, 500);
    pqInt.enqueue(3, 1500);
    pqInt.enqueue(4, 250);
    pqInt.enqueue(5, 750);
    pqInt.enqueue(6, 1250);
    pqInt.enqueue(7, 1750);
    pqInt.enqueue(8, 1000);
    
    pqInt3.enqueue(1, 1000);
    pqInt3.enqueue(2, 500);
    pqInt3.enqueue(3, 1500);
    pqInt3.enqueue(4, 250);
    pqInt3.enqueue(5, 750);
    pqInt3.enqueue(6, 1250);
    pqInt3.enqueue(7, 1750);
    pqInt3.enqueue(8, 1000);
    
    pqInt4.enqueue(1, 1000);
    pqInt4.enqueue(2, 500);
    pqInt4.enqueue(3, 1500);
    pqInt4.enqueue(4, 250);
    pqInt4.enqueue(5, 750);
    pqInt4.enqueue(6, 1250);
    pqInt4.enqueue(8, 1000);
    
    pqInt5.enqueue(1, 1000);
    pqInt5.enqueue(3, 1500);
    pqInt5.enqueue(4, 250);
    pqInt5.enqueue(5, 750);
    pqInt5.enqueue(6, 1250);
    pqInt5.enqueue(7, 1750);
    pqInt5.enqueue(8, 1000);
    
    pqInt2 = pqInt;
    ASSERT_EQ(pqInt == pqInt2, true);
    ASSERT_EQ(pqInt == pqInt3, true);
    ASSERT_EQ(pqInt2 == pqInt3, true);
    ASSERT_EQ(pqInt == pqInt4, false);
    ASSERT_EQ(pqInt == pqInt5, false);
}