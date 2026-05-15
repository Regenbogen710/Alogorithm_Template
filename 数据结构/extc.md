在 GCC 的 C++ 标准库扩展中， `ext/pb_ds`（全称 `ext/pb_ds/assoc_container.hpp` 等）提供了 **Policy‑Based Data Structures (PBDS)**，即基于策略的数据结构。通过组合少量策略参数，你可以获得功能比 STL 容器更丰富、性能特征更灵活的哈希表、平衡树、优先队列、Trie 等。

下面按常用程度介绍用法，所有示例均基于 `g++`，**无需链接额外库**，只需包含对应头文件。

---

## 1. 头文件与命名空间

```cpp
#include <ext/pb_ds/assoc_container.hpp>   // 树、哈希表、Trie 等
#include <ext/pb_ds/priority_queue.hpp>    // 优先队列
#include <ext/pb_ds/trie_policy.hpp>       // Trie

using namespace __gnu_pbds;                // 推荐局部 using，避免污染
```

为了代码清晰，下面的示例将直接使用 `__gnu_pbds::` 前缀。

---

## 2. 带有顺序统计的平衡树（红黑树 / Splay）

这是 PBDS 最实用的功能之一：一棵支持 **按排名查询（find_by_order）** 和 **查给定值的排名（order_of_key）** 的平衡二叉树。行为类似 `std::set`，但比插入到 `vector` 再排序更高效。

### 2.1 定义 ordered_set
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>   // tree_order_statistics_node_update

using namespace __gnu_pbds;

typedef tree<
    int,                               // key 类型
    null_type,                         // 映射值，null_type 表示类似 set（无映射）
    std::less<int>,                    // 比较函数
    rb_tree_tag,                       // 底层平衡树类型：rb_tree_tag / splay_tree_tag
    tree_order_statistics_node_update  // 启用顺序统计节点更新
> ordered_set;
```

若需 **多重集（multiset）**，把 `std::less<int>` 换成 `std::less_equal<int>`，但此时 `find`、`erase` 等行为会受影响，推荐自己实现一个“比较时用 `less`，存储时把 key 扩展为 `pair<int, 唯一id>`”的版本，或使用 `tree` 配合 `null_type` 和合理的 `insert` 策略。

### 2.2 常用操作
```cpp
ordered_set X;
X.insert(1);
X.insert(2);
X.insert(4);
X.insert(8);
X.insert(16);

// 按排名查找：第 k 小（下标从 0 开始）
auto it = X.find_by_order(2);   // *it == 4

// 查询给定值的排名：严格小于 key 的元素个数
size_t pos = X.order_of_key(9); // pos == 4 （小于 9 的有 1,2,4,8）

// 标准容器操作
bool exist = (X.find(2) != X.end());
X.erase(2);
```

**时间复杂度**：红黑树均为 O(log n)，splay 树均摊 O(log n)。

---

## 3. 高性能哈希表

PBDS 提供两种链地址哈希表：
- **gp_hash_table**：使用探测法（开地址法），查找更快，适合 key 尺寸小、哈希函数优秀的场景。
- **cc_hash_table**：使用分离链接法，对坏的哈希函数容忍度更高。

### 3.1 基本定义
```cpp
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// 类似 std::unordered_map 的 "gp" 版本
gp_hash_table<int, std::string> gp_map;

// 类似 std::unordered_set 的 "cc" 版本
cc_hash_table<int, null_type> cc_set;   // 注意映射类型用 null_type
```

由于标准是 C++11 后的 `unordered_map`，PBDS 的哈希表主要用于需要 **自定义哈希策略** 或追求 **极致性能** 的场合。它允许通过模板参数改变哈希方法、碰撞处理策略等。

### 3.2 带策略的自定义哈希表
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>   // std::hash

typedef gp_hash_table<
    int,                    // key
    int,                    // mapped（没有则用 null_type）
    std::hash<int>,         // 哈希函数
    std::equal_to<int>,     // 等值比较
    direct_mask_range_hashing<>,   // 哈希值 → 桶索引的策略
    linear_probe_fn<>,             // 探测函数
    hash_standard_resize_policy<>  // 重哈希策略
> my_map;
```

大多数情况下，如果你不需要特殊策略，直接用 `gp_hash_table<int, int>` 或 `cc_hash_table<int, int>` 即可，接口类似 `unordered_map`。

### 3.3 常用操作（与 STL 类似）
```cpp
gp_hash_table<int, std::string> ht;
ht[1] = "one";
ht.insert({2, "two"});
auto it = ht.find(1);
if (it != ht.end()) std::cout << it->second;
ht.erase(1);
```

**注意**：PBDS 的哈希表迭代器顺序是不确定的，且某些操作（如 `erase`）在探测法表中可能会使迭代器失效，用法与 `std::unordered_map` 基本一致。

---

## 4. 可修改优先级的优先队列

PBDS 的优先队列支持 **策略定制** 以及 **迭代器可修改性**，可以像 `std::priority_queue` 一样使用，也可以修改队列中的元素并自动维护堆序。

### 4.1 基本使用
```cpp
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;

// 最小堆样例
typedef priority_queue<int, std::greater<int>, pairing_heap_tag> min_heap;
min_heap pq;
pq.push(10);
pq.push(5);
pq.push(20);
while (!pq.empty()) {
    std::cout << pq.top() << ' ';    // 5 10 20
    pq.pop();
}
```

**可选堆标签**：
- `pairing_heap_tag` — 配对堆，多数操作最优。
- `binary_heap_tag` — 二叉堆，类似 STL，但不支持 `modify` / `erase`。
- `binomial_heap_tag` — 二项堆，支持 `modify` / `erase`，合并 O(log n)。
- `thin_heap_tag` — 薄堆，类似 Fibonacci 堆。
- `rc_binomial_heap_tag` — 引用计数二项堆。

### 4.2 使用迭代器修改元素
```cpp
#include <ext/pb_ds/priority_queue.hpp>

typedef __gnu_pbds::priority_queue<int, std::less<int>, binomial_heap_tag> pq_t;
pq_t pq;
auto it = pq.push(10);
pq.push(20);

// 修改已存在元素的值，并自动重新调整堆
pq.modify(it, 30);   // it 原来指向 10，现在改成 30，堆顶变为 30
std::cout << pq.top(); // 30
```

只有 `binary_heap_tag` **不支持** `modify` 和 `erase` 通过迭代器，其他标签均支持。修改操作的时间复杂度取决于堆类型。

---

## 5. Trie（前缀树）

PBDS 提供了 `trie`，可用于字符串或二进制序列的查询。

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;

typedef trie<
    std::string,           // key 类型
    null_type,             // 没有映射值（类似于 set）
    trie_string_access_traits<>,  // 访问特性（默认字符串即可）
    pat_trie_tag,          // PATRICIA trie（推荐）
    trie_prefix_search_node_update  // 更新策略：支持前缀搜索
> string_trie;

string_trie t;
t.insert("hello");
t.insert("helium");

// 前缀范围查询：返回一对迭代器表示所有以 "hel" 开头的字符串
auto range = t.prefix_range("hel");
for (auto it = range.first; it != range.second; ++it)
    std::cout << *it << ' ';    // hello helium
```

若需要映射值，将 `null_type` 换成值类型即可；若 key 是二进制，可使用 `trie_binary_access_traits`。

---

## 6. 策略定制一览

PBDS 的核心是“策略”（Policy），你可以像搭积木一样组合它们：

- **树**：底层（`rb_tree_tag`, `splay_tree_tag`, `ov_tree_tag`）+ 更新策略（`null_node_update`, `tree_order_statistics_node_update`）。
- **哈希表**：哈希函数、冲突探测（`linear_probe_fn`, `quadratic_probe_fn`）、重哈希大小策略。
- **优先队列**：堆标签（上述六种）+ 比较器。
- **Trie**：PATRICIA / 前缀搜索等。

大多情况下，默认策略能满足 90% 的需求，特殊策略用于极端优化。

---

## 7. 与 STL 容器的对比与选择

| 需求                         | PBDS 推荐                     | 注释                                       |
| ---------------------------- | ----------------------------- | ------------------------------------------ |
| 需要排名 / 顺序统计的 set    | `tree<..., rb_tree, order_statistics>` | 比 `std::vector` 的插入删除快得多        |
| 追求极致速度的哈希表         | `gp_hash_table`               | 通常比 `std::unordered_map` 快             |
| 需要修改优先级               | `priority_queue` + 迭代器      | 除 `binary_heap` 外均支持 `modify` / `erase` |
| 前缀搜索                     | `trie`                        | 直接返回前缀范围迭代器                     |
| 普通平衡树 / 哈希            | 直接使用 `std::map` / `std::unordered_map` | 标准库可移植性更好，功能基本够用           |

---

## 8. 编译注意事项

- **GCC 专属**：这是 GNU 扩展，不适用于 MSVC 或 Clang 的 libc++（Clang 使用 GCC 的 libstdc++ 时可用）。
- **无额外链接**：只需要 `#include` 对应头文件。
- **警告抑制**：GCC 可能产生 `-Wattributes`、`-Wclass-memaccess` 等无关警告，可用 `#pragma GCC diagnostic` 屏蔽：
```cpp
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC diagnostic pop
```

---

## 9. 总结

`extc pbds` 在算法竞赛和部分对性能、功能有特殊要求的工程中非常有用。它通过策略设计提供了：

- **顺序统计树**（插入时自动维护排名）；
- **更灵活的哈希表**（自定义探测、重哈希策略）；
- **支持修改操作的优先队列**；
- **便于前缀搜索的 Trie**。

只需包含对应头文件，便可在 GCC 环境中直接使用，比手写平衡树功能更强大、可靠性更高。对于大多数日常需求，推荐用 `tree` 解决排名问题，用 `gp_hash_table` 加速查找，用 `pairing_heap` 或 `binomial_heap` 管理动态变化的优先级。






`ext/pb_ds` 中的容器严格遵循标准 C++ 容器和关联容器的接口要求，所以你通常能找到 `size()`、`empty()`、`clear()`、`find()`、`count()`、`lower_bound()`、`upper_bound()`、`equal_range()`、`swap()` 以及所有迭代器函数。下面列出的都是这些常规函数 **之外** 的、PBDS 特有的或需要特别留意的操作。

---

## 1. 树（`tree`）特有的函数

**顺序统计策略 `tree_order_statistics_node_update` 开启后**：

| 函数 | 说明 |
|------|------|
| `iterator find_by_order(size_type order)` | 返回排名为 `order`（第 k 小的元素，索引从 0 开始）的迭代器 |
| `size_type order_of_key(const_key_reference r_key)` | 返回严格小于 `r_key` 的元素个数，即 `r_key` 的排名 |
| `node_begin()` / `node_end()` | 遍历容器元节点（一般不需要） |
| `join(tree &other)` | 将另一棵树的 **全部元素** 合并到当前树，前提是所有元素必须严格在另一棵树与当前树之间（即 `other` 中的最大元素 ≤ 当前树的最小元素，或反之，取决于比较器） |
| `split(const_key_reference r_key, tree &other)` | 将大于等于 `r_key` 的元素移动到 `other` 中，自己保留小于 `r_key` 的元素。要求 `other` 为空。注意关联容器一般不提供 O(log n) 的分裂，这是 PBDS 的特有功能。 |

**示例**：
```cpp
ordered_set X, Y;
X.insert(1); X.insert(3); X.insert(5);
Y.insert(2); Y.insert(4);

// 合并，调用前必须保证所有元素处于正确的序关系
X.join(Y);   // now X = {1,2,3,4,5}, Y 为空

X.split(4, Y); // X = {1,2,3}, Y = {4,5}
```

> ⚠️ `join` 和 `split` 需要确保树满足谓词顺序，否则行为未定义。红黑树支持这两个操作，splay 树不支持。

---

## 2. 哈希表（`gp_hash_table` / `cc_hash_table`）特有的函数

除了标准的 `operator[]`、`insert`、`erase`、`find`、`count` 之外，PBDS 哈希表暴露了底层的桶接口，用于调优和调试：

| 函数 | 说明 |
|------|------|
| `size_type get_actual_size() const` | 返回分配的总桶数（或实际表格大小） |
| `size_type get_num_used_entries() const` | 返回已使用的桶数（非空桶） |
| `void resize(size_type n)` | 重新哈希到至少 `n` 个桶 |
| `void erase(iterator it)` | 删除迭代器所指元素，与标准相同，但需要注意探测法表中的迭代器失效规则 |
| `void clear()` | 清空表 |

探测法（`gp`）还提供：

| 函数 | 说明 |
|------|------|
| `void erase_if(Predicate pred)` | 移除所有满足谓词的元素（C++20 风格，但很早就有）？实际 PBDS 的 `gp_hash_table` 有一个内部 `erase_if`，但建议直接遍历并删除。这里以具体实现为准。 |

对于分离链接法（`cc`），还有：

| 函数 | 说明 |
|------|------|
| `bucket_size_type get_bucket_size(size_type n) const` | 获取第 `n` 个桶中元素个数 |
| `size_type get_bucket(const_key_reference r_key) const` | 获取键所落的桶索引 |

大多数情况下这些函数不需要直接使用，但在写自定义策略或性能测试时有用。

---

## 3. 优先队列（`priority_queue`）特有的函数

除了 `push`、`pop`、`top`、`size`、`empty` 外，PBDS 的堆支持迭代器语义和高级操作：

| 函数 | 说明 |
|------|------|
| `iterator push(const_reference r_val)` | 插入元素并返回指向该元素的迭代器，后续可用于 `modify` 或 `erase` |
| `void modify(iterator it, const_reference r_new_val)` | 修改迭代器所指元素的值，并自动重新维护堆序 |
| `void erase(iterator it)` | 删除迭代器所指元素，并调整堆 |
| `void join(priority_queue &other)` | 合并另一个优先队列到当前队列，`other` 被清空，合并后仍然保持堆性质 |
| `void split(Pred prd, priority_queue &other)` | 将所有满足谓词 `prd` 的元素移动到 `other` 中。谓词应接受 `const_reference`，返回 `bool` |
| `const_iterator begin() const` | 返回一个只读迭代器，可用于遍历所有元素（顺序不受堆序保证） |

> ⚠️ 只有 `binary_heap_tag` 不支持 `modify`、`erase` 和迭代器语义（它类似 STL 的优先队列），其他标签（`pairing_heap_tag`、`binomial_heap_tag`、`thin_heap_tag`、`rc_binomial_heap_tag`）均支持。

**示例**：
```cpp
typedef __gnu_pbds::priority_queue<int, std::less<int>, binomial_heap_tag> pq_t;
pq_t pq1, pq2;
auto it = pq1.push(10);
pq1.push(20);
pq2.push(5);

pq1.modify(it, 30);    // it 原指向 10，现在变成 30，堆顶变为 30
pq1.join(pq2);         // pq1 包含 {5,20,30}，pq2 为空

pq1.split([](int x) { return x < 15; }, pq2);  // pq1 剩余 >=15 的，pq2 得到 <15 的
```

---

## 4. Trie（`trie`）特有的函数

除了 `insert`、`find`、`erase` 等关联操作，`trie` 提供强大的前缀查询：

| 函数 | 说明 |
|------|------|
| `std::pair<iterator, iterator> prefix_range(const_key_reference r_key)` | 返回一对迭代器，表示所有以 `r_key` 为前缀的元素范围。第一个迭代器指向第一个匹配的元素，第二个迭代器指向最后一个匹配元素的下一个位置 |
| `void insert(iterator hint, const_reference r_val)` | 带提示的插入，但不太常用 |
| `node_begin()` / `node_end()` | 遍历 trie 的内部节点 |

对于自定义 `trie_prefix_search_node_update` 的 trie，还有：

| 函数 | 说明 |
|------|------|
| `void erase_if(Predicate pred)` | （可能支持）条件删除，通常手动循环 `erase` 更可控 |

**二进制键 trie**（用 `trie_binary_access_traits`）用法同理，`prefix_range` 可以查找所有以某个二进制前缀开头的数据。

---

## 5. 其他策略暴露的小工具函数

- **树和 trie**：`get_node_allocator()` 获取节点分配器，用于高级内存管理。
- **树**：`void erase(const_iterator it)` / `iterator erase(iterator it)` 标准但容易忘。
- **所有容器**：PBDS 的迭代器通常提供 `operator->` 和 `operator*` 与标准完全一致。

---

## 总结：你可能忽视但很实用的函数

| 容器 | 函数 | 用途 |
|------|------|------|
| 树 | `join` | O(n) 合并两棵树 |
| 树 | `split` | O(n) 按键分裂 |
| 堆 | `modify` / `erase` | 动态更新优先级，无需重复 push/pop |
| 堆 | `join` / `split` | 合并两个队列，或按条件拆分 |
| Trie | `prefix_range` | 一次拿到所有特定前缀的元素 |
| 哈希表 | `resize` / `get_actual_size` | 调整桶数，避免重哈希开销 |

这些函数是 PBDS 相对标准库最明显的“增值”部分。如果你在使用中需要某个功能但不确定是否有对应函数，最可靠的方法是查阅 GCC 源码目录下的 `ext/pb_ds` 或直接阅读头文件——它们的接口通常提供与 STL 一致的命名风格。

如果你有具体的使用场景想进一步优化，可以告诉我，我可以给出更针对性的建议。