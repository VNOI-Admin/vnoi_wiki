# Fenwick Tree

**Fenwick** hay ở Việt Nam được gọi là **Cây Chỉ Số Nhị Phân** (**Binary Indexed Tree**) là một CTDL với $n$ node và mỗi node thứ $i$ chứa thông tin về các phần tử trong đoạn $\(i - \(i \& -i\), i\]$

**Ví dụ:** Có một mảng $a_1,a_2,...,a_N$ và được khởi tạo bằng 0. Chúng ta nhận được các truy vấn, 1 là tăng phần tử $a_P$ lên $val$, 2 là in ra $a_1+a_2+...+a_P$.

Giờ chúng ta chỉ cần quan tâm cách giải bài toán này với Fenwick (nhưng sau đó bạn có thể tìm tòi và áp dụng nó cho nhiều bài tập khác).

[[/uploads/fenwick1.gif|fenwick1]]

**Độ phức tạp** khi xử lý các truy vấn là $O(log(n))$.

_Code (1-based):_

```cpp
int fen[MAX_N];
void update(int p, int val){
    for(int i = p; i <= n; i += i & -i)
        fen[i] += val;
}
int sum(int p) {
    int ans = 0;
    for(int i = p; i; i -= i & -i)
        ans += fen[i];
    return ans;
}
```

Mảng bắt buộc phải là 1-based, không thể chạy với 0-based.

# Bài tập

- [Pashmak and Parmida’s problem](http://codeforces.com/contest/459/problem/D)
- [BST](http://hsin.hr/coci/archive/2008_2009/contest3_tasks.pdf)

# Tài liệu tham khảo

- [Codeforces](http://codeforces.com/blog/entry/15729)
