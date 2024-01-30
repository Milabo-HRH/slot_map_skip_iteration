# Slot Map with Skip Iteration
Implement a slot map with skip iteration based on the [slot_map by Sergey Makeev](https://github.com/SergeyMakeev/slot_map). 
## Requirements
* C++20
## Test
* Use `cmake -DORDERED=ON` to build the test with linked list version.
* Use `cmake -DLOW_COMPLEXITY=ON ` to build the test with low complexity version.
* Add no option after `cmake` to build the test with original slot map.
## Implementation
### Slot Map with Low Complexity Jump-Counting Pattern
This slot map implementation is inspired by Matthew Bentley's paper -- [The low complexity jump-counting pattern - an O(1) time complexity replacement for boolean skipfields](https://plflib.org/matt_bentley_-_the_low_complexity_jump-counting_pattern.pdf). In LCJC(Abbreviation of ’low complexity jump-counting’) algorithm, it's impossible to insert a slot inside a continuous sequence of erased  slots with O(1) time complexity. So we can only insert into slots which has no or only have one adjacent erased slot (We denote those slots with one adjacent erased slot as an edge slot).

To achieve that, the first implementation comes to the mind is a deque: when erase a edge slot,
push it to the front of the deque; when erase other slot, push it to the back of the deque; 
when insert a slot, pop the front of the deque. However, there are one problem with this implementation: 
version counter has a limit, when a slot's version counter reaches the limit, it will be inactivated and not be recycled. 
So the slots adjacent to it can be pop out of the deque even if they are not edge slots.

To address this problem, we used a hash table to record the slots that are edge slots and a hash table to record the slots are not edge slots. When a slot is erased/inserted, 
we do operations to keep only the edge slots are in the first hash table and we only reuse the slots in the first hash table.

```c++
    std::unordered_map<index_t, key, std::hash<index_t>, std::equal_to<index_t>, stl::Allocator<std::pair<const index_t, key>>> edgeIndicies;
    std::unordered_map<index_t, key, std::hash<index_t>, std::equal_to<index_t>, stl::Allocator<std::pair<const index_t, key>>> innerIndicies;
```
In implementation, we found this implementation is slower than the original slot map. It may be caused by the following 3 reasons:
* Although average time complexity is still O(1) for insertion and deletion but the worst case become O(M) because of the hash table -- M is the current number of erased slots. 
* The hash table is not cache friendly. And all the operations to maintain the jump-counting pattern and the hash table will cause more cache misses.
* If two edge slots of a continuous sequence of erased slots got inactivated, all the slots in the middle of them will never be reused and stay in the hash table forever which can cause memory leak and slower the hash table.

To address the second problem, we can store the jump-counting pattern for each page rather than store them in each slot's metadata to reduce the cache misses. However, I don't think there are approaches to address the first and third problem. So I think this implementation is not a good choice.

### Slot Map with High Complexity Jump-Counting Pattern
I haven't implemented this version yet. This algorithm also comes from Matthew Bentley's paper. By maintaining a jump-counting pattern for each node, we no longer need to maintain these 2 hash tables. However, insert a node into a continuous sequence of erased slots will be O(N) time complexity -- N is the number of erased slots in the sequence, which does not satisfy our requirement. Empirically, we can maintain jump-counting patterns for each page, so the time complexity will be O(M) -- M is the number of erased slots in the page. But for each iteration, we need to iterate all the pages between next slot and current slot to find the next slot. So the time complexity for iteration will be O(N/PageSize) -- N is the number of slots between next occupied slot and current slot. There must be some trade-offs between insertion and iteration.

### Slot Map with linked list
Because in slot map, the order we iterate its elements can be random. So we can use a linked list to record the order each slot is inserted. When we erase a slot, we can remove it from the linked list. When we insert a slot, we can insert it to the back of the linked list. When we iterate the slot map, we just iterate the linked list. 
We don't use a real pointer for the linked list, we use the index of the slot as the pointer and store these indexes in each slot's metadata. The time complexity for insertion and deletion is O(1). The time complexity for iteration is O(N) -- N is the number of occupied slots.

Pros:
* The worst case time complexity for insertion, deletion, and one step in iteration is O(1).
* Easy to maintain and not cause memory leak. Not cause performance degradation when the number of erased slots increases.

Cons:
* Not cache friendly. We may need to iterate back and forth in the linked list.
* Need to allocate more memory for each slot's metadata. Need a extra uint32_t for each slot to store the index of the next slot in the linked list compared with the jump-counting pattern version.
