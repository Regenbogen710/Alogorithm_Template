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