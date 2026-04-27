---
title: Static Wavelet Tree
description: 
published: true
date: 2026-04-27T11:21:44.122Z
tags: 
editor: markdown
dateCreated: 2026-04-27T11:21:44.122Z
---

# Static Wavelet Tree

**Người viết:**

- Nguyễn Tiến Mạnh - Đại học Bách khoa Hà Nội.
- Nguyễn Tấn Minh - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM.

**Reviewer:**

- Phạm Vũ Phương - THPT Chuyên Hà Tĩnh, Hà Tĩnh.
- Nguyễn Quang Minh - Michigan State University.
- Nguyễn Minh Hiển - Đại học Công nghệ, Đại học Quốc gia Hà Nội.

##  Giới thiệu

Với mảng tĩnh, các truy vấn như tìm phần tử nhỏ thứ $k$, đếm số phần tử trong một khoảng giá trị, hay tìm trung vị (median) trên đoạn thường đòi hỏi phải kết hợp nhiều cấu trúc dữ liệu khác nhau như BIT, Ordered Set hay Segment Tree.

**Wavelet Tree** là một cấu trúc dữ liệu mạnh mẽ có thể giải quyết toàn bộ những truy vấn đó trong một cấu trúc duy nhất. Nó cho phép thực hiện truy vấn đồng thời dựa trên cả vị trí và giá trị. Wavelet Tree giúp xử lý các bài toán:

- Tìm phần tử nhỏ thứ $k$ trong đoạn ($k$-th order statistic problem).
- Đếm số lần xuất hiện của một giá trị cụ thể trong đoạn (range count).
- Đếm số lượng phần tử thuộc một khoảng giá trị cho trước nằm trong đoạn (range frequency).
- ...

Độ phức tạp cho cả 3 hàm xử lý trên đều là $\mathcal{O}(\log \sigma)$ cho mỗi truy vấn (với $\sigma$ là kích thước miền giá trị của mảng sau khi nén).


##  Bài toán mở đầu

Cho mảng $A$ gồm $n$ số nguyên và $q$ truy vấn. Mỗi truy vấn yêu cầu tìm giá trị nhỏ thứ $k$ trong đoạn $[l; r]$.

* **Ràng buộc:** $n, q \leq 10^5$, $A_i \leq 10^9$.
* **Thuật toán ngây thơ:** $\mathcal{O}(q \cdot n \log n)$ sẽ không khả thi.

Wavelet Tree giúp giải quyết bài toán này với độ phức tạp $\mathcal{O}((n+q) \log \sigma)$ (với $\sigma$ là số giá trị khác nhau).

Trong bài viết này, ta quy ước mảng được đánh số từ $1$.

##  Ý tưởng

###  Cấu trúc cây

Cây Wavelet được xây dựng bằng cách chia nhị phân miền giá trị của mảng.

- **Nút gốc:** Quản lý toàn bộ các phần tử của mảng với miền giá trị $[\min; \max]$.
- **Nút con:** Giả sử nút hiện tại quản lý miền giá trị $[\text{low}; \text{high}]$, ta đặt $\text{mid} = \left\lfloor \frac{\text{low} + \text{high}}{2} \right\rfloor$.
    - Các phần tử có giá trị $\le \text{mid}$ sẽ được đưa vào nhánh trái (quản lý miền $[\text{low}; \text{mid}]$).
    - Các phần tử có giá trị $> \text{mid}$ sẽ được đưa vào nhánh phải (quản lý miền $[\text{mid}+1; \text{high}]$).

Vì miền giá trị liên tục bị chia đôi ở mỗi bước đệ quy, chiều cao tối đa của cây sẽ đạt $\mathcal{O}(\log \sigma)$.

**Lưu ý:** 
- Thứ tự xuất hiện của các phần tử trong mảng ban đầu luôn được giữ nguyên khi đẩy xuống các nút con.
- Miền giá trị ám chỉ độ lớn của lớn của các phần tử , cần phân biệt với đoạn.

### Phép duyệt

Khi duyệt cây, ta để ý rằng một đoạn các phần tử có vị trí nằm trong khoảng $[l_0; r_0]$ (các phần tử thuộc một nút của Wavelet Tree được đánh số từ $1$) tại một nút đang quản lý miền giá trị $[\text{low}; \text{high}]$ tương ứng với một đoạn các phần tử có vị trí nằm trong khoảng $[l_1; r_1]$ tại nút con trái (quản lý miền giá trị $[\text{low}; \text{mid}]$) và trong khoảng $[l_2; r_2]$ tại nút con phải (quản lý miền giá trị $[\text{mid} + 1; \text{high}]$).

Để tiện lợi cho việc xác định $l_1, r_1, l_2, r_2$ khi đã biết đoạn $[l_0; r_0]$, tại mỗi nút, thay vì lưu lại toàn bộ mảng, ta sẽ ngầm định gán cho mỗi phần tử một trạng thái nhị phân (ứng với một bit) với ý nghĩa như sau:

- Bit bật (1) ứng với các phần tử có giá trị $\le \text{mid}$, sẽ được đẩy sang nhánh trái.
- Bit tắt (0) ứng với các phần tử có giá trị $> \text{mid}$, sẽ được đẩy sang nhánh phải.

Dựa vào các bit này, tại mỗi nút , ta cần xây dựng một mảng cộng dồn $B$ để truy vấn nhanh. Khi đó, $B_i$ cho biết số lượng phần tử trong tiền tố từ $1$ đến $i$ được đẩy sang nhánh trái.

Trước tiên, giả sử ta đang ở nút cha với đoạn $[1; i]$, khi đó, sẽ có $B_i$ phần tử trong đoạn này được đẩy sang cây con trái, và $i - B_i$ phần tử còn lại được đẩy sang nhánh phải. Áp dụng công thức này cho đoạn $[1; r_0]$ rồi loại bỏ đi các phần tử trong đoạn $[1; l_0 - 1]$, ta có công thức để xác định đoạn mới như sau:

- Khi đi sang cây con trái, đoạn $[l_0; r_0]$ sẽ được thay thành đoạn $[B_{l_0-1} + 1; B_{r_0}]$.
- Khi đi sang cây con phải, đoạn $[l_0; r_0]$ sẽ được thay thành đoạn $[l_0 - B_{l_0 - 1}; r_0 - B_{r_0}]$.

Trong trường hợp mảng được đánh số từ $0$, công thức xác định đoạn mới sẽ là:

- Khi đi sang cây con trái, đoạn $[l_0; r_0]$ sẽ được thay thành đoạn $[B_{l_0-1}; B_{r_0}-1]$.
- Khi đi sang cây con phải, đoạn $[l_0; r_0]$ sẽ được thay thành đoạn $[l_0 - B_{l_0 - 1}; r_0 - B_{r_0}]$.

Lưu ý rằng khi sử dụng cách đánh số từ $0$, ta phải quy ước một phần tử ảo là $B_{-1} = 0$.

![range_split.png](/algo/data-structures/wavelet-tree/range_split.png)

Ở ví dụ trên, đoạn $[3; 7]$ ở nút cha (quản lý miền giá trị $[1; 9]$) ứng với đoạn $[2; 3]$ ở nút con trái (quản lý miền giá trị $[1; 4]$) và đoạn $[2; 4]$ ở nút con phải (quản lý miền giá trị $[5; 9]$).

Ta có dãy $B$ như sau:

| Chỉ số | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Giá trị | $2$ | $7$ | $8$ | $3$ | $9$ | $8$ | $1$ | $4$ | $7$ |
| Dãy $B$ | $1$ | $1$ | $1$ | $2$ | $2$ | $2$ | $3$ | $4$ | $4$ |

Sử dụng công thức ta vừa tìm được, đoạn $[3; 6]$ sẽ được biến đổi thành đoạn $[2; 3]$ ứng với cây con trái và $[2; 4]$ ứng với cây con phải, giống như phân tích trước đó.


<!--Giả sử ta đang ở nút cha với đoạn $[l_0; r_0]$:

- **Nhánh trái**: Số lượng số $0$ (đi sang trái) từ đầu mảng đến vị trí $r_0$ là $B_{r_0}$. Do đó, vị trí kết thúc mới tại nút con trái chính là $B_{r_0}$. Vị trí bắt đầu mới là số lượng phần tử đi sang trái trước vị trí $l_0$, tức là $B_{l_0-1} + 1$.
-  **Nhánh phải**: Tổng số phần tử từ $1$ đến $i$ là $i$. Số lượng phần tử đi sang trái là $B[i]$. Vậy số lượng phần tử đi sang phải là $i - B[i]$. Từ đó ta có công thức tương tự cho nhánh phải.

Vậy nên khi di chuyển xuống nút con , ta sẽ có các đoạn mới là:
- **Xuống con trái**: $B_{l-1} + 1$ và $B_r$.
- **Xuống con phải**:  $l -  B_{l-1}$ và $\ r - B_{r}$.-->

Điểm mấu chốt khiến Wavelet Tree hoạt động hiệu quả chính là việc duy trì thứ tự tương đối của các phần tử. Khi một đoạn $[l; r]$ tại nút cha được đẩy xuống các nút con, chúng ta không cần lưu trữ toàn bộ mảng tại mỗi nút mà chỉ cần dãy $B$.

### Minh họa

 Ta xét ví dụ với mảng $A = [5, 2, 7, 1, 6, 3, 8, 4, 2, 5]$ gồm $10$ phần tử và miền giá trị ban đầu là $[1; 8]$. Tại nút gốc, ta có $\text{mid} = 4$, các giá trị tại nút này sẽ được xử lý như bảng sau:

 
| Chỉ số $i$ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| :--- | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| **Giá trị $A[i]$** | 5 | 2 | 7 | 1 | 6 | 3 | 8 | 4 | 2 | 5 |
| **So sánh với $\text{mid}$** | $>4$ | $\le4$ | $>4$ | $\le4$ | $>4$ | $\le4$ | $>4$ | $\le4$ | $\le4$ | $>4$ |
| **Bit vector** | `0` | `1` | `0` | `1` | `0` | `1` | `0` | `1` | `1` | `0` |
| **Dãy $B$** | $0$ | $1$ | $1$ | $2$ | $2$ | $3$ | $3$ | $4$ | $5$ | $5$ |

Dãy số được tách thành hai phần, giữ nguyên thứ tự tương đối:

 - Nút con trái (quản lý miền giá trị $[1; 4]$) nhận các phần tử mang bit 1 $\rightarrow [2, 1, 3, 4, 2]$.
 - Nút con phải (quản lý miền giá trị $[5; 8]$) nhận các số bit 0 $\rightarrow [5, 7, 6, 8, 5]$.
 
Quá trình này lặp lại đệ quy. Mô hình cây sẽ có dạng như sau:

![upload_734b36e81682244536d3fb85e7bd5dce.png](/algo/data-structures/wavelet-tree/upload_734b36e81682244536d3fb85e7bd5dce.png)


### Cài đặt

Trước tiên, ta cài đặt một `struct Node` để biểu diễn một nút thuộc Wavelet Tree:

```cpp=
struct Node {
    Node *lpt, *rpt;
    vector<int> B;

    // constructor tạo cây rỗng
    Node() : lpt(nullptr), rpt(nullptr) {}
    
    // constructor xây dựng cây từ mảng được cho bởi hai con trỏ from và to
    // ứng với đoạn [from; to) với miền giá trị [x; y].
    Node (int* from, int* to, int low, int high) {
        if (low == high || from >= to) return;
        int mid = (low + high) / 2;
        function<bool(int)> f = [mid] (int x) {
            return x <= mid;
        };

        // xây dựng mảng prefix sum B
        B.reserve(to - from + 1);
        B.push_back(0);
        for (auto it = from; it != to; it++)
            B.push_back(B.back() + f(*it));
        
        // phân chia mảng thành 2 phần theo điều kiện x <= mid
        auto pivot = stable_partition(from, to, f);

        // tiếp tục xây dựng cây con
        if (from < pivot) lpt = new Node(from, pivot, low, mid);
        if (pivot < to) rpt = new Node(pivot, to, mid + 1, high);
    }
};
```

Trong phần cài đặt trên, ta sử dụng hàm `stable_partition` để hỗ trợ tách mảng gốc thành 2 phần theo điều kiện $x \leq \text{mid}$. Hàm này nhận vào hai con trỏ `from`, `to` và một điều kiện boolean, nó sẽ đưa tất cả phần tử thỏa điều kiện lên đầu và các phần tử còn lại ra sau mảng mà vẫn duy trì thứ tự tưởng đối của các phần tử. Sau đó, hàm trả về điểm cắt là con trỏ chỉ vào phần tử đầu tiên của nửa sau (phần tử đầu tiên không thỏa điều kiện).

Lưu ý rằng với việc sử dụng hàm `stable_partition`, mảng được truyền vào constructor của cấu trúc dữ liệu cũng sẽ được sắp xếp sau khi khởi tạo cây.

Khi đã có `Node`, ta tạo `struct WaveletTree` để có thể dễ dàng sử dụng Wavelet Tree:

```cpp=
template <int MIN, int MAX>
struct WaveletTree {
    Node* root;

    WaveletTree() : root(nullptr) {}
    WaveletTree (int* from, int* to) : root(new Node(from, to, MIN, MAX)) {}
};
```

Giả sử ta cần khởi tạo Wavelet Tree có miền giá trị là $[0; 10^9]$ trên mảng $a$ gồm $n$ phần tử được đánh số từ $1$, ta sử dụng cú pháp sau:

```cpp=
WaveletTree<0, 1'000'000'000> tree(a + 1, a + N + 1);
```

Sau khi khởi tạo, mảng $a$ cũng sẽ được sắp xếp tăng dần. Nếu muốn giữ lại trạng thái của mảng $a$, ta cần điều chỉnh constructor của `WaveletTree`, bằng cách sao chép mảng $a$ trước khi gọi constructor của `Node`.

Từ quá trình xây dựng trên, ta có thể rút ra các tính chất quan trọng của Wavelet Tree:

- Ở mỗi bước, miền giá trị được chia đôi. Do đó, chiều cao (độ sâu tối đa) của cây là $\mathcal{O}(\log \sigma)$.
- Wavelet Tree thực chất là một cây nhị phân xây dựng trên miền giá trị $\sigma$. Số lượng nút trên cây được giới hạn bởi $\mathcal{O}(\min(n \log \sigma, \sigma))$.

### Nén Bitvector

Để hỗ trợ thao tác truy vấn $\mathcal{O}(1)$ khi đi xuống các nhánh, tại mỗi nút trên Wavelet Tree, ta buộc phải duy trì một mảng cộng dồn $B$ để lưu số lượng phần tử rẽ trái (đi vào nhánh con trái). Với cách cài đặt thông thường, sử dụng kiểu `int` cho mỗi phần tử, tổng bộ nhớ cho toàn bộ cây sẽ là $\mathcal{O}(N \log \sigma)$.

Để tối ưu bộ nhớ, ta để ý rằng bản chất của việc rẽ nhánh chỉ là hai trạng thái nhị phân: $1$ (rẽ trái) và $0$ (rẽ phải). Do đó, việc dùng hẳn một biến `int` $32$ bit để lưu một trạng thái là vô cùng lãng phí.

Kỹ thuật Nén Bitvector giúp ta giảm lượng bộ nhớ xuống tới $64$ lần bằng cách gộp các bit lại:
- Tạo một mảng $b$  để lưu nhóm $64$ trạng thái nhị phân liên tiếp thành một khối.
- Tạo một mảng prefix sum $c$  lưu tổng số lượng bit $1$ tính đến trước khối thứ $i$. Kích thước mảng $c$ nhờ vậy bằng $\lceil N / 64 \rceil$.

Hai mảng này sinh ra để bù trừ khiếm khuyết cho nhau khi xây dựng hàm truy vấn ``rank1(i)``.

```cpp=
int n = to - from;
int num_blocks = (n / 64) + 1;

// Khởi tạo mảng nén
b.assign(num_blocks, 0);
c.assign(num_blocks + 1, 0);

// Xây dựng các khối 64-bit và đếm số lượng bit 1 cho từng khối
for (int i = 0; i < n; i++) {
    if (f(from[i])) {
        // Bật bit thứ (i % 64) trong khối thứ (i / 64)
        b[i / 64] |= (1ULL << (i % 64));
        // Tạm thời đếm số bit 1 nội bộ trong khối này
        c[i / 64 + 1]++; 
    }
}

// Biến mảng c thành mảng cộng dồn thưa (lưu các cột mốc)
for (int i = 1; i <= num_blocks; i++) {
    c[i] += c[i - 1];
}
```


Hàm ``rank1(i)`` trả về số lượng bit $1$ (phần tử rẽ trái) trong tiền tố từ vị trí $0$ đến $i-1$. 

Khi cần tính tổng số phần tử rẽ trái trong tiền tố độ dài $i$, thuật toán chia công việc làm hai thành phần dựa trên tọa độ khối:

- Ở phần chẵn , ta tính tổng số bit $1$ của tất cả các khối nguyên vẹn đứng trước bằng cách truy xuất trực tiếp từ cột mốc $c[\lfloor i / 64 \rfloor]$.
- Ở phần lẻ , ta tính số lượng bit $1$ dư ra nằm bên trong khối hiện tại bằng cách trích xuất khối $b[\lfloor i / 64 \rfloor]$. Áp dụng phép toán bitmask ``(1ULL << (i % 64)) - 1`` để giữ lại đúng phần tiền tố cần xét, sau đó đếm nhanh số lượng bit $1$ bằng ``__builtin_popcountll``.

```cpp=
// Hàm truy cập O(1): Trả về số lượng phần tử rẽ trái trong tiền tố độ dài i
int rank1(int i) {
    if (i == 0) return 0;
    int block_idx = i / 64;
    int rem = i % 64;

    // 1. Lấy phần chẵn (tổng từ các khối hoàn chỉnh đứng trước)
    int res = c[block_idx];

    // 2. Lấy phần lẻ (các bit dư trong khối hiện tại)
    if (rem > 0) {
        unsigned long long mask = (1ULL << rem) - 1;
        res += __builtin_popcountll(b[block_idx] & mask);
    }

    return res;
}
```

## Các truy vấn 

### Đếm số phần tử có giá trị bằng $K$ trong đoạn

Ý tưởng chính của truy vấn đếm số phần tử có giá trị bằng $K$ trong đoạn đó là ta tìm đường đi từ nút gốc của Wavelet Tree xuống nút lá quản lý miền giá trị $[K; K]$ và duy trì đoạn tìm kiếm $[l; r]$ tương ứng. Cuối cùng, ta chỉ cần trả về $r - l + 1$, tức số phần tử trong đoạn $[l; r]$ ứng với nút lá tìm được.

Cụ thể hơn, ta bắt đầu quá trình tìm kiếm bằng chia để trị từ nút gốc. Giả sử ta đã thu hẹp phạm vi tìm kiếm xuống một nút có miền giá trị $[\text{low}; \text{high}]$ và đoạn được truy vấn (theo chỉ số của nút này) là $[l; r]$.

Tại một nút bất kỳ, nếu đoạn $[l; r]$ rỗng hoặc giá trị $K$ không nằm trong miền mà nút này quản lý, kết quả hiển nhiên bằng $0$. Nếu nút hiện tại là nút lá đang quản lý miền giá trị $[K; K]$, như đã phân tích, ta trả về $r - l + 1$.

Trong trường hợp nút đang tìm kiếm chưa phải là lá, ta so sánh $k$ với giá trị trung điểm $\text{mid} = \frac{\text{low} + \text{high}}{2}$.

- Nếu $K \le \text{mid}$, tức $K$ nằm ở cây con trái, ta chiếu đoạn $[l; r]$ xuống cây con trái ứng với đoạn $[B_{l-1} + 1; B_r]$.
- Ngược lại, nếu $K > \text{mid}$, tức $K$ nằm ở cây con phải, ta chiếu đoạn $[l; r]$ xuống cây phải ứng với đoạn $[l - B_{l-1}; r - B_r]$.

Nhờ mảng prefix $B$, việc ánh xạ này luôn chính xác, nó đảm bảo các phần tử thuộc đoạn $[l; r]$ được chuyển về đúng vị trí trong cây con chứa giá trị $K$. Nói cách khác, tính đúng đắn của thuật toán đến từ việc: mỗi bước ta đều đi đúng nhánh duy nhất có thể chứa giá trị $K$, và mảng $B$ đảm bảo sự tương ứng một-một giữa đoạn ở nút cha và đoạn ở nút con. 

Có thể thấy, ở mỗi tầng của Wavelet tree, các thao tác xử lý đều có độ phức tạp hằng số. Do đó, độ phức tạp của mỗi truy vấn $\texttt{count}(l, r, K)$ là $\mathcal{O}(\log \sigma)$.

:::spoiler Code tham khảo
```cpp=
int countEqualK (int l, int r, int K, int low, int high) {
    if (l > r || K < low || K > high) return 0;
    if (low == high) return r - l + 1;
    int mid = (low + high) / 2;
    if (K <= mid) return (lpt ? lpt->countEqualK(B[l - 1] + 1, B[r], K, low, mid) : 0);
    return (rpt ? rpt->countEqualK(l - B[l - 1], r - B[r], K, mid + 1, high) : 0);
}
```
:::

### Tìm phần tử nhỏ thứ $k$ trong đoạn

Tương tự truy vấn ở trên, ta cũng bắt đầu quá trình tìm kiếm bằng chia để trị từ nút gốc. Giả sử ta đã thu hẹp phạm vi tìm kiếm xuống một nút có miền giá trị $[\text{low}; \text{high}]$ và đoạn được truy vấn (theo chỉ số của nút này) là $[l; r]$.

Gọi $\texttt{cnt\_left}$ là số lượng phần tử thuộc nhánh trái nằm trong đoạn $[l; r]$. Từ dãy $B$, ta có thể xác định $\texttt{cnt\_left}$ như sau:

$$
\texttt{cnt\_left} = B_r - B_{l-1}
$$


Nếu $k \le \texttt{cnt\_left}$ thì phần tử cần tìm chắc chắn nằm trong tập trái (vì toàn bộ các phần tử trong tập này đều không lớn hơn $\text{mid}$). Khi đó, truy vấn được chuyển tiếp xuống cây con trái với đoạn chỉ số mới $[B_{l-1} + 1; B_r]$, giữ nguyên giá trị $k$.

Ngược lại, nếu $k > \texttt{cnt\_left}$, tức là phần tử cần tìm không nằm trong tập trái mà nằm trong tập phải. Lúc này, do đã có $\texttt{cnt\_left}$ phần tử nhỏ hơn đã đi sang cây con trái nên phần tử cần tìm sẽ là phần tử nhỏ thứ $k - \texttt{cnt\_left}$ ở cây con phải. Nói cách khác, truy vấn được chuyển tiếp xuống cây con phải với đoạn đoạn mới $[l - B_{l-1}; r - B_r]$, đồng thời cập nhật lại  $k \leftarrow k - \texttt{cnt\_left}$.

Quá trình này tiếp tục cho đến khi ta đi tới một nút lá, tại đó miền giá trị chỉ còn một phần tử duy nhất, và giá trị này chính là phần tử nhỏ thứ $k$ cần tìm.

Độ phức tạp của mỗi truy vấn $\texttt{kth}(l, r, k)$ là $\mathcal{O}(\log \sigma)$. Việc phân tích độ phức tạp được thực hiện tương tự truy vấn ở trên.

:::spoiler Code tham khảo
```cpp=
int kthSmallest (int l, int r, int k, int low, int high) {
    if (l > r) return 0;
    if (low == high) return low;
    int cntLeft = B[r] - B[l - 1], mid = (low + high) / 2;
    if (k <= cntLeft)
        return lpt->kthSmallest(B[l - 1] + 1, B[r], k, low, mid);
    return rpt->kthSmallest(l - B[l - 1], r - B[r], k - cntLeft, mid + 1, high);
}
```

Bạn đọc có thể tham khảo mã nguồn đầy đủ của mình trên Library Checker [tại đây](https://judge.yosupo.jp/submission/365490).
:::

Để tự kiểm tra mã nguồn, bạn đọc có thể tham khảo bài Range Kth Smallest ở nền tảng Library Checker (đường dẫn ở phần phụ lục).

### Đếm số phần tử có giá trị không quá $K$ trong đoạn

Ta cũng thực hiện chia để trị như các truy vấn trước, giả sử nút hiện tại có miền giá trị $[\text{low}; \text{high}]$ và đoạn được truy vấn (theo chỉ số của nút này) là $[l; r]$.

Ta xét các trường hợp biên như sau:
- Nếu đoạn $[l; r]$ rỗng hoặc $K < \text{low}$, tức toàn bộ miền giá trị tại nút đều lớn hơn $k$, kết quả hiển nhiên bằng $0$.
- Nếu $\text{high} \le K$, nghĩa là mọi giá trị trong nút này đều nhỏ hơn hoặc bằng $K$, khi đó toàn bộ $r - l + 1$ phần tử trong đoạn đều thỏa mãn, và ta có thể trả về trực tiếp mà không cần đi sâu hơn.

Trong các trường hợp còn lại, tức khoảng $[1; K]$ chỉ bao phủ một phần của khoảng $[\text{low}; \text{high}]$, ta đặt $\text{mid} = \left\lfloor \frac{\text{low} + \text{high}}{2} \right \rfloor$ và so sánh $K$ với $\text{mid}$ để quyết định hướng đi.

- Nếu $K \le \text{mid}$: Các phần tử thoả mãn điều kiện $\leq K$ chỉ có thể nằm ở nhánh trái. Do đó, ta chỉ cần tiếp tục tìm kiếm trên đoạn $[B_{l-1} + 1; B_r]$ của cây con trái.
- Nếu $K > \text{mid}$: Toàn bộ các phần tử rẽ sang nhánh trái đều có giá trị $\le \text{mid} < K$, nên chắc chắn chúng thỏa mãn điều kiện bài toán. Số lượng phần tử này chính là $\texttt{cnt_left} = B_r - B_{l-1}$. Sau đó, ta chỉ cần gọi đệ quy xuống nhánh phải với đoạn ánh xạ $[l - B_{l-1}; r - B_r]$ để tìm nốt các phần tử thỏa mãn còn lại.

Với việc tính toán lượng phần tử thỏa mãn ở nhánh trái được thực hiện trong $\mathcal{O}(1)$, bằng cách luôn chỉ đi xuống nhiều nhất một cây con tại mỗi bước, thuật toán được đảm bảo chạy trong thời gian $\mathcal{O}(\log \sigma)$ \.

:::spoiler Code tham khảo
```cpp=
int countLEQ (int l, int r, int K, int low, int high) {
    if (l > r || K < low) return 0;
    if (high <= K) return r - l + 1;
    int cntLeft = B[r] - B[l - 1], mid = (low + high) / 2;
    if (K <= mid) return (lpt ? lpt->countLEQ(B[l - 1] + 1, B[r], K, low, mid) : 0);
    return cntLeft + (rpt ? rpt->countLEQ(l - B[l - 1], r - B[r], K, mid + 1, high) : 0);
}
```
:::

Bạn đọc cũng có thể tham khảo bản cài đặt đầy đủ gồm các hàm đã được đề cập [tại đây](https://www.ideone.com/cWDg2F).

## Offline Wavelet Tree

Có thể thấy, một trong những điểm yếu lớn nhất của Wavelet Tree là độ phức tạp bộ nhớ $\mathcal{O}(n \log \sigma)$. Tuy nhiên, nếu thông tin các truy vấn cần thực hiện trên Wavelet Tree đều được biết trước, ta có thể thực hiện chia để trị song song toàn bộ truy vấn và chỉ sử dụng độ phức tạp tuyến tính. Kỹ thuật này có tên gọi là **Offline Wavelet Tree** và sẽ được trình bày sau đây.

Trước tiên, ta xét một bài toán tương tự với bài toán ở phần trên:

> Cho mảng $A$ gồm $n$ phần tử và $Q$ truy vấn offline:
> 
> - Cho ba số nguyên $l, r, k$, hãy xác định phần tử nhỏ thứ $k$ trong đoạn $a_l, a_{l+1}, a_{l+2}, \dots, a_r$.

Ngoài ra, để thuận tiện cho việc cài đặt, ta giả sử miền giá trị tìm kiếm ban đầu có dạng $\left[0; 2^B\right)$ để Wavelet Tree có dạng cây nhị phân hoàn chỉnh gồm $B$ tầng. Trong phần này, ta sử dụng Wavelet Tree đánh số từ $0$.

### Ý tưởng

Để giải quyết bài toán trên, thay vì tuần tự xử lý từng truy vấn rồi với mỗi truy vấn ta duyệt qua các tầng của Wavelet Tree, ta sẽ xử lý cả $Q$ truy vấn ở tầng đầu tiên của cây, rồi sau đó chuyển sang tầng thứ hai, tiếp tục xử lý cả $Q$ truy vấn,... Quá trình được lặp lại đến khi ta di chuyển đến tầng cuối cùng của Wavelet Tree, khi đó, ta có được đáp án cho cả $Q$ truy vấn.

Với cách tiếp cận này, ta chỉ cần duy trì thông tin của đúng một tầng của Wavelet Tree tại mọi thứ điểm của thuật toán.

Một cách cài đặt đơn giản cho hướng tiếp cận này là ta ghép toàn bộ thông tin của các nút thuộc cùng một tầng của Wavelet Tree theo thứ tự từ trái sang phải vào cùng một mảng có độ dài $n$, khi đó, ta lưu kèm một mảng đánh dấu vị trí phân cắt vùng bộ nhớ của các nút khác nhau.

Ví dụ, với mảng $[4, 1, 6, 0, 5, 7, 2, 3, 1, 4]$, quá trình thực hiện Offline Wavelet Tree diễn ra như sau:

![offline_wavelet_tree_split_1.png](/algo/data-structures/wavelet-tree/offline_wavelet_tree_split_1.png)

:::spoiler Code tham khảo
```cpp=
vector<int> offlineWaveletTree (vector<int> A, vector<tuple<int,int,int,int>> queries) {
    // tiền xử lý các truy vấn
    for (auto &[l, r, k, id] : queries) k--; // chuyển thành dạng đánh số từ 0
    sort(all(queries));

    // khai báo các mảng phụ
    int N = A.size(), Q = queries.size();
    vector<int> B(N);
    vector<bool> cutpoint(N + 1);
    cutpoint[0] = cutpoint[N] = true;

    for (int b = 29; b >= 0; b--) {
        function<bool(int)> f = [b] (int x) {
            // việc so sánh với mid trong Wavelet Tree tương đương
            // với việc xét bit thứ b của giá trị cần so sánh
            return (x >> b & 1) ^ 1;
        };
        
        int lastStart = 0, queryIterator = 0;
        for (int i = 1; i <= N; i++) {
            if (!cutpoint[i]) continue;
            
            // xử lý đoạn [lastStart; i) ứng với một nút của Wavelet Tree
            for (int j = lastStart; j < i; j++) B[j] = f(A[j]);
            partial_sum(B.begin() + lastStart, B.begin() + i, B.begin() + lastStart);
            int pivot = stable_partition(A.begin() + lastStart, A.begin() + i, f) - A.begin();

            // xử lý các truy vấn trong phạm vi quản lý của nút hiện tại
            int cntLeft = B[i - 1], lastQuery = queryIterator;
            while (queryIterator < Q && get<0>(queries[queryIterator]) < i) {
                int l, r, k, id, offset; tie(l, r, k, id) = queries[queryIterator];
                int toLeft = B[r] - (l > lastStart ? B[l - 1] : 0);
                if (k < toLeft) // đi sang cây con trái
                    l = (l > lastStart ? B[l - 1] : 0), r = B[r] - 1, offset = lastStart;
                else // đi sang cây con phải
                    l -= (l > lastStart ? B[l - 1] : 0), r -= B[r], k -= toLeft, offset = cntLeft;
                l += offset, r += offset;
                queries[queryIterator++] = make_tuple(l, r, k, id);
            }
            
            // xử lý các truy vấn trong đoạn [lastQuery; queryIterator) và sắp xếp lại thứ tự
            if (lastQuery < queryIterator) {
                function<bool(tuple<int,int,int,int>)> pred = [pivot] (tuple<int,int,int,int> e) {
                    return get<0>(e) < pivot;
                };
                stable_partition(queries.begin() + lastQuery, queries.begin() + queryIterator, pred);
            }
            
            // tách nút hiện tại thành 2 nút con bằng cách đánh dấu thêm điểm cách
            cutpoint[pivot] = true, lastStart = i;
        }
    }

    // sau khi thực hiện Offline Wavelet Tree, các giá trị của mảng A cũng chính là các
    // giá trị của các nút lá, do đó, ta chỉ cần truy cập vào đúng phần tử để lấy đáp án
    vector<int> ans(Q);
    for (auto [l, r, k, id] : queries) ans[id] = A[l];
    return ans;
}
```
:::

### Tối ưu hằng số

Tuy nhiên, cách xử lý như trên khá bất lợi cho việc cài đặt, cộng với việc phải duy trì thứ tự các truy vấn cho đúng với thứ tự các nút từ trái sang phải trên cùng một tầng của Wavelet Tree là chưa hiệu quả.

Để ý rằng các truy vấn trong quá trình biến đổi sẽ được duy trì nằm gọn trong một đoạn ứng với một nút của Wavelet Tree. Khi đó, vị trí tương đối của các nút trong cùng một tầng của Wavelet Tree không còn quan trọng nữa, miễn là ta có thể "mang theo" truy vấn ứng với mỗi nút khi xáo trộn thứ tự của chúng.

Để dễ hình dung hơn, xét mảng $B$ ứng với một tầng của Wavelet Tree có hai nút quản lý miền giá trị $[0; 2^d)$ và $[2^d; 2^{d+1})$. Thông thường, ta sẽ tách hai nút này thành 4 nút và giữ lại giá trị tương đối của nó (tức là thứ tự trái-trái, trái-phải, phải-trái, phải-phải). Tuy nhiên, nếu ta chuyển toàn bộ phần tử có bit thứ $d - 1$ tắt sang trái và phần còn lại sang phải (tức là thứ tự trái-trái, phải-trái, trái-phải, phải-phải), các truy vấn vẫn được ánh xạ đúng:

![offline_wavelet_tree_transformation.png](/algo/data-structures/wavelet-tree/offline_wavelet_tree_transformation.png)

Ví dụ, đoạn màu hồng $[0; 3]$ nếu đi sang cây con trái sẽ được ánh xạ xuống đoạn $[0; 1]$, ngược lại, nếu đi sang cây con phải sẽ được đánh xạ xuống đoạn $[7; 8]$ (ứng với khoảng $[0; 1]$ của nút). Điều tương tự cũng xảy ra với đoạn màu tím.

Có thể thấy, cách làm này không làm ảnh hưởng tính chính xác của việc biến đổi các truy vấn, hơn nữa, còn làm cho quá trình biến đổi được diễn ra vô cùng thuận tiện. Bởi vì, lúc này ta đang thực hiện phân tách trên cả mảng $B$, không phải riêng từng đoạn (ứng với từng nút) như cách làm ở trên. Hơn nữa, ta cũng không cần phải duy trì các truy vấn theo một thứ tự đặc biệt nào nữa.

Do đó, ta có thể xây dựng mảng tổng cộng dồn trên cả mảng $B$. Công thức ánh xạ một đoạn $[l_0; r_0]$ sẽ là:

- Nếu sang cây con trái: $l_0 \leftarrow B_{l_0 - 1}$ và $r_0 \leftarrow B_{r_0} - 1$.
- Nếu sang cây con phải: $l_0 \leftarrow \texttt{cntLeft} + l_0 - B_{l_0 - 1}$ và $r_0 \leftarrow \texttt{cntLeft} + r_0 - B_{r_0}$.

:::spoiler Code tham khảo
```cpp=
vector<int> offlineWaveletTree (vector<int> A, vector<tuple<int,int,int>> queries) {
    // tiền xử lý các truy vấn
    for (auto &[l, r, k] : queries) k--;

    // khai báo mảng phụ
    int N = A.size(), Q = queries.size();
    vector<int> B(N);
    
    for (int b = 29; b >= 0; b--) {
        // thực hiện phân tách cả tầng chia để trị thứ b
        for (int i = 0; i < N; i++) B[i] = bool((A[i] >> b & 1) ^ 1);
        partial_sum(B.begin(), B.end(), B.begin());
        stable_partition(A.begin(), A.end(), [b] (int x) { return (x >> b) & 1 ^ 1; });

        // xử lý các truy vấn trên tầng chia để trị thứ b
        int cntLeft = B.back();
        for (auto &[l, r, k] : queries) {
            int toLeft = B[r] - (l ? B[l - 1] : 0);
            if (k < toLeft) l = (l ? B[l - 1] : 0), r = B[r] - 1; // đi sang cây con trái
            else l += cntLeft - (l ? B[l - 1] : 0), r += cntLeft - B[r], k -= toLeft; // đi sang cây con phải
        }
    }

    // lấy đáp án tương tự như trên
    vector<int> ans(Q);
    for (int i = 0; i < Q; i++) ans[i] = A[get<0>(queries[i])];
    return ans;
}
```
:::

Lưu ý, với cách làm này, mảng $A$ sẽ không được sắp xếp theo thứ tự tăng dần.

### So sánh

Ta có thể thực hiện một phép so sánh nhỏ giữa 3 lời giải cho bài tập [Range Kth Smallest](https://judge.yosupo.jp/problem/range_kth_smallest) như sau:

| Tiêu chí | [Online Wavelet Tree](https://judge.yosupo.jp/submission/365489) | [Offline Wavelet Tree](https://judge.yosupo.jp/submission/367876) | [Offline Wavelet Tree (tối ưu hằng số)](https://judge.yosupo.jp/submission/367867) |
| :-: | :-: | :-: | :-: |
| Thời gian | $692 \text{ ms}$ | $350 \text{ ms}$ | $111 \text{ ms}$ |
| Bộ nhớ | $31.86 \text{ MB}$ | $1.54 \text{ MB}$ | $1.04 \text{ MB}$ |

## Ví dụ

### [Dãy nghịch thế (NKINV)](https://oj.vnoi.info/problem/nkinv)

#### Đề bài

Cho dãy số $A$. Đếm số lượng cặp nghịch thế $(i, j)$ sao cho $i < j$ và $A[i] > A[j]$.

#### Lời giải

Ta sử dụng Wavelet Tree bằng cách duyệt từng phần tử. Khi xét đến phần tử $A[j]$ (với $j$ chạy từ $1 \to n$), ta cần đếm xem có bao nhiêu chỉ số $i < j$ mà $A[i] > A[j]$. Điều này tương đương với việc truy vấn trên đoạn tiền tố $[1; j-1]$ xem có bao nhiêu số lớn hơn $A[j]$. Công thức tổng quát:

$$\text{Inversions} = \sum_{j=1}^{N} \Big( (j - 1) - \texttt{LTE}(1, j-1, A[j]) \Big)$$

:::spoiler Code tham khảo

```cpp=
#include "bits/stdc++.h"

using namespace std;

struct Wavelet_Tree
{
    int low, high;
    Wavelet_Tree *L = NULL, *R = NULL;
    vector <int> B;

    Wavelet_Tree() {}
    Wavelet_Tree(int *From, int *To, int x, int y)
    {
        low = x, high = y;
        if (low == high || From >= To) return;
        int mid = (low + high) / 2;
        auto F = [mid](int x)
        {
            return x <= mid;
        };
        B.reserve(To - From + 1);
        B.push_back(0);
        for (auto it = From; it != To; ++it)
            B.push_back(B.back() + F(*it));
        auto pivot = stable_partition(From, To, F);
        L = new Wavelet_Tree(From, pivot, low, mid);
        R = new Wavelet_Tree(pivot, To, mid + 1, high);
    }

    // Phần tử nhỏ thứ k trong [l; r]
    int FindKth(int l, int r, int K)
    {
        if (l > r) return 0;
        if (low == high) return low;
        int cnt_left = B[r] - B[l - 1];
        if (K <= cnt_left) return L->FindKth(B[l - 1] + 1, B[r], K);
        return R->FindKth(l - B[l - 1], r - B[r], K - cnt_left);
    }

    // số lượng phần tử trong [l; r] = K
    int Count(int l, int r, int K)
    {
        if (l > r || K < low || K > high) return 0;
        if (low == high) return r - l + 1;
        int mid = (low + high) / 2;
        if (K <= mid) return L->Count(B[l - 1] + 1, B[r], K);
        return R->Count(l - B[l - 1], r - B[r], K);
    }

    // số lượng phần tử trong [l; r] <= K
    int Count_LTE(int l, int r, int K)
    {
        if (l > r || K < low) return 0;
        if (high <= K) return r - l + 1;
        return L->Count_LTE(B[l - 1] + 1, B[r], K) + R->Count_LTE(l - B[l - 1], r - B[r], K);
    }

}wvl;


const int N = 6e4 + 4;
int n, a[N], MAX, q, B[N];

signed main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], B[i] = a[i];
    MAX = *max_element(a + 1, a + 1 + n);

    wvl = Wavelet_Tree(a + 1, a + n + 1, 1, MAX);


    long long ans = 0;
    for (int i = 1; i < n; ++i) if (1 <= B[i] - 1)
        ans += wvl.Count_LTE(i + 1, n, B[i] - 1);

    cout << ans << '\n';

    return 0;
}

```

:::

### [Bedao Testing Contest 01 - KTHSUM](https://oj.vnoi.info/problem/bedao_t1_kthsum)

#### Đề bài

Cho một mảng $A$ gồm $n$ số nguyên. Như bạn đã biết, trên mảng này có tổng cộng đoạn $\frac{N(N + 1)}{2}$. con liên tiếp. Bạn được yêu cầu in ra đoạn con liên tiếp có tổng lớn thứ $K$, tức đoạn con liên tiếp có tổng lớn thứ 1 là đoạn con liên tiếp có tổng lớn nhất mảng.

#### Lời giải
 
Ta có thể giải bằng phương pháp chặt nhị phân trên kết quả. Giả sử ta cần kiểm tra xem có tồn tại ít nhất $K$ đoạn con có tổng lớn hơn hoặc bằng giá trị $\texttt{mid}$ hay không. 

Gọi $\texttt{sum}$ là mảng cộng dồn của dãy $A$, tổng của một đoạn con $A_i, A_{i+1}, \dots, A_j$ được tính bằng:
 
$$
\texttt{sum}[j] - \texttt{sum}[i - 1]
$$

Khi đó, điều kiện kiểm tra trở thành:

$$
\texttt{sum}[j] - \texttt{sum}[i - 1] \ge \texttt{mid} \iff \texttt{sum}[i - 1] \le \texttt{sum}[j] - \texttt{mid}
$$

Ta duyệt $j$ từ $1$ đến $n$, tại mỗi bước sử dụng Wavelet Tree (đã được dựng trên tập giá trị của mảng $S$) để đếm số lượng chỉ số $p < j$ thỏa mãn $\texttt{sum}[p] \le \texttt{sum}[j] - \texttt{mid}$. Nếu tổng số lượng đếm được lớn hơn hoặc bằng $K$, kết quả cần tìm sẽ lớn hơn hoặc bằng $\texttt{mid}$.

::: spoiler Code tham khảo

```cpp=
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5 + 2;
int n, MAX, MIN, ID[N];
long long K, sum[N], MAX2, MIN2;
vector <long long> C;

struct Wavelet_Tree
{
    int low, high;
    vector <int> B;
    Wavelet_Tree *L, *R;
    Wavelet_Tree() {}
    Wavelet_Tree(int *From, int *To, int x, int y)
    {
        low = x, high = y;
        if (low == high || From >= To) return;
        int mid = low + high >> 1;
        auto F = [mid](int x)
        {
            return x <= mid;
        };
        B.reserve(To - From + 1);
        B.push_back(0);
        for (auto it = From; it != To; ++it)
            B.push_back(B.back() + F(*it));
        auto pivot = stable_partition(From, To, F);
        L = new Wavelet_Tree(From, pivot, low, mid);
        R = new Wavelet_Tree(pivot, To, mid + 1, high);
    }

    int Count_LTE(int l, int r, int K)
    {
        if (l > r || K < low) return 0;
        if (high <= K) return r - l + 1;
        return L->Count_LTE(B[l - 1] + 1, B[r], K) + R->Count_LTE(l - B[l - 1], r - B[r], K);
    }

}wvl;

bool Check(long long mid)
{
    long long cnt = 0;
    for (int j = 1; j <= n; ++j)
    {

        cnt += wvl.Count_LTE(1, j, upper_bound(C.begin() , C.end(), sum[j] - mid) - C.begin());
    }

    return cnt >= K;
}

long long sum2[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> K; sum[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int a;
        cin >> a;
        MAX = max(MAX, a);
        MIN  = min(MIN, a);
        sum[i] = sum[i - 1] + a;
    }

    long long l = (long long) MIN * n, r = (long long) MAX * n, ans = r;

    C.push_back(0);
    for (int i = 1; i <= n; ++i) C.push_back(sum[i]);

    sort(C.begin() , C.end());
    C.erase(unique(C.begin() , C.end()), C.end());

    for (int i = 1; i <= n + 1; ++i)
        ID[i] = lower_bound(C.begin() , C.end(), sum[i - 1]) - C.begin() + 1;

    wvl = Wavelet_Tree(ID + 1, ID + n + 2, 1, C.size());

    while (l <= r)
    {
        long long mid = l + (r - l) / 2;
        if (Check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << ans;

    return 0;
}
```

:::
### [ICPC 2022 miền Trung bài D - Median](https://oj.vnoi.info/problem/icpc22_mt_d#comments)

#### Đề bài

Cho một dãy $n$ số và $q$ truy vấn, mỗi truy vấn tìm phần tử trung vị của đoạn con $[l; r]$.

Giới hạn: $1 \le n, q, a_i \le 10^5$.

#### Lời giải

Với bài toán này chúng ta có thể áp dụng trực tiếp cài đặt ở trên, không cần nén số. Đáp án của mỗi truy vấn là `kth(L, R, (R - L + 1) / 2)`.

::: spoiler Code tham khảo

```cpp=
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5 + 2;
int n, q, a[N], MAX;

struct Wavelet_Tree {
    int low, high;
    Wavelet_Tree *l, *r;
    vector<int> B;

    Wavelet_Tree() {}
    Wavelet_Tree(int *from, int *to, int x, int y) {
        low = x, high = y;
        if (low == high || from >= to) return;

        int mid = (low + high) / 2;
        auto f = [mid](int x) { return x <= mid; };

        B.reserve(to - from + 1);
        B.push_back(0);
        for (auto it = from; it != to; ++it)
            B.push_back(B.back() + f(*it));

        auto pivot = stable_partition(from, to, f);

        l = new Wavelet_Tree(from, pivot, low, mid);
        r = new Wavelet_Tree(pivot, to, mid + 1, high);
    }
    int kth(int l, int r, int k)
    {
        if (l > r) return 0;
        if (low == high) return low;
        int cnt_left = B[r] - B[l - 1];
        if (k <= cnt_left) return this->l->kth(B[l - 1] + 1, B[r], k);
        return this->r->kth(l - B[l - 1], r - B[r], k - cnt_left);
    }

}wvl;

int B[N];


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    MAX = *max_element(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) B[i] = a[i];
        wvl = Wavelet_Tree(B + 1, B + 1 + n, 1, MAX);
        while (q--)
        {
            int L, R;
            cin >> L >> R;
            cout << wvl.kth(L, R, (R - L + 2) / 2) << '\n';
        }

    return 0;
}

```

:::

### [COCI 2021 Round 6 bài 5 - Index](https://oj.vnoi.info/problem/coci2021_r6_index)

#### Đề bài

Cho dãy $A$ có $n$ số nguyên và $q$ truy vấn. Mỗi truy vấn là một đoạn $[l; r]$. Tìm số $h$ lớn nhất sao cho trong đoạn $A_l, A_{l+1}, \dots, A_r$ có ít nhất $h$ phần tử có giá trị $\ge h$.

Giới hạn: $1 \le n, q, a_i \le 2 \times 10^5$.

#### Lời giải

Ta có số phần tử $\ge h$ trong đoạn $A_l, A_{l+1}, \dots, A_r$ là `(r - l + 1) - Count_LTE(l, r, 0, h - 1)`. Khi ta tăng dần $h$ thì biểu thức trên giảm dần, do đó ta có thể áp dụng chặt nhị phân để tìm $h$ lớn nhất thoả mãn điều kiện `(r - l + 1) - Count_LTE(l, r, 0, h - 1) >= h`.

Độ phức tạp của thuật toán là $\mathcal{O}(n \log^2 n)$.

::: spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

struct Wavelet_Tree
{
    int low, high;
    Wavelet_Tree *L = NULL, *R = NULL;
    vector <int> B;

    Wavelet_Tree() {}
    Wavelet_Tree(int *From, int *To, int x, int y)
    {
        low = x, high = y;
        if (low == high || From >= To) return;
        int mid = (low + high) / 2;
        auto F = [mid](int x)
        {
            return x <= mid;
        };
        B.reserve(To - From + 1);
        B.push_back(0);
        for (auto it = From; it != To; ++it)
            B.push_back(B.back() + F(*it));
        auto pivot = stable_partition(From, To, F);
        L = new Wavelet_Tree(From, pivot, low, mid);
        R = new Wavelet_Tree(pivot, To, mid + 1, high);
    }

    // Phần tử nhỏ thứ k trong [l; r]
    int FindKth(int l, int r, int K)
    {
        if (l > r) return 0;
        if (low == high) return low;
        int cnt_left = B[r] - B[l - 1];
        if (K <= cnt_left) return L->FindKth(B[l - 1] + 1, B[r], K);
        return R->FindKth(l - B[l - 1], r - B[r], K - cnt_left);
    }

    // số lượng phần tử trong [l; r] = K
    int Count(int l, int r, int K)
    {
        if (l > r || K < low || K > high) return 0;
        if (low == high) return r - l + 1;
        int mid = (low + high) / 2;
        if (K <= mid) return L->Count(B[l - 1] + 1, B[r], K);
        return R->Count(l - B[l - 1], r - B[r], K);
    }

    // số lượng phần tử trong [l; r] <= K
    int Count_LTE(int l, int r, int K)
    {
        if (l > r || K < low) return 0;
        if (high <= K) return r - l + 1;
        return L->Count_LTE(B[l - 1] + 1, B[r], K) + R->Count_LTE(l - B[l - 1], r - B[r], K);
    }

} wvl;
const int N = 2e5 + 4;
int n, a[N], MAX, q;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    MAX = *max_element(a + 1, a + 1 + n);
    wvl = Wavelet_Tree(a + 1, a + n + 1, 1, MAX);

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        int low = 0, high = len, ans = 0;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            int cnt = len - wvl.Count_LTE(l , r , mid - 1);
            if (cnt >= mid)
            {
                ans = mid;
                low = mid + 1;
            }
            else
                high = mid - 1;
        }
        cout << ans << "\n";
    }
}

```
:::

### [SPOJ - ILKQ1](https://www.spoj.com/problems/ILKQUERY/en/)

#### Đề bài

Cho dãy $A$ gồm $n$ số nguyên trong khoảng $[-10^9; 10^9]$, đánh thứ tự từ $0$ và $q$ truy vấn. Mỗi truy vấn có dạng:

- `i t k`: gọi $d$ là phần tử nhỏ thứ $k$ cho đến chỉ số $i$. Trả về chỉ số của lần xuất hiện thứ $t$ của $d$ trong dãy. Nếu không tồn tại lần xuất hiện này thì in ra `-1`.

Giới hạn: $1 \le n \le 10^5, 1 \le q \le 10^5$.

#### Lời giải

Trước tiên ta nén số, sau đó với mỗi phần tử phân biệt ta lưu lại tất cả những lần xuất hiện của nó. Với hàm `FindKth` ta có thể tìm được nhanh phần tử nhỏ thứ $k$, sau đó in ra lần xuất hiện thứ $t$ đã được lưu trước đó .

::: spoiler Code tham khảo

```cpp=
#include <bits/stdc++.h>
using namespace std;

struct Wavelet_Tree
{
    int low, high;
    Wavelet_Tree *L = NULL, *R = NULL;
    vector <int> B;

    Wavelet_Tree() {}
    Wavelet_Tree(int *From, int *To, int x, int y)
    {
        low = x, high = y;
        if (low == high || From >= To) return;
        int mid = (low + high) / 2;
        auto F = [mid](int x)
        {
            return x <= mid;
        };
        B.reserve(To - From + 1);
        B.push_back(0);
        for (auto it = From; it != To; ++it)
            B.push_back(B.back() + F(*it));
        auto pivot = stable_partition(From, To, F);
        L = new Wavelet_Tree(From, pivot, low, mid);
        R = new Wavelet_Tree(pivot, To, mid + 1, high);
    }

    // Phần tử nhỏ thứ k trong [l; r]
    int FindKth(int l, int r, int K)
    {
        if (l > r) return 0;
        if (low == high) return low;
        int cnt_left = B[r] - B[l - 1];
        if (K <= cnt_left) return L->FindKth(B[l - 1] + 1, B[r], K);
        return R->FindKth(l - B[l - 1], r - B[r], K - cnt_left);
    }

    // số lượng phần tử trong [l; r] = K
    int Count(int l, int r, int K)
    {
        if (l > r || K < low || K > high) return 0;
        if (low == high) return r - l + 1;
        int mid = (low + high) / 2;
        if (K <= mid) return L->Count(B[l - 1] + 1, B[r], K);
        return R->Count(l - B[l - 1], r - B[r], K);
    }

    // số lượng phần tử trong [l; r] <= K
    int Count_LTE(int l, int r, int K)
    {
        if (l > r || K < low) return 0;
        if (high <= K) return r - l + 1;
        return L->Count_LTE(B[l - 1] + 1, B[r], K) + R->Count_LTE(l - B[l - 1], r - B[r], K);
    }

} wvl;

const int N = 1e5 + 2;
int n, q, a[N], ID[N];
vector <int> C;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n; ++i) C.push_back(a[i]);

    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());

    for (int i = 0; i < n; ++i)
        ID[i] = lower_bound(C.begin(), C.end(), a[i]) - C.begin();

    vector<vector<int>> pos(C.size());
    for (int i = 0; i < n; ++i) pos[ID[i]].push_back(i);

    wvl = Wavelet_Tree(ID, ID + n, 0, C.size() - 1);

    while (q--)
    {
        int k, i, l;
        cin >> k >> i >> l;
        int d = wvl.FindKth(1, i + 1, k);
        if (d < 0 || d >= C.size())
        {
            cout << -1 << '\n';
            continue;
        }
        if (pos[d].size() < l) cout << -1 << '\n';
        else cout << pos[d][l - 1] << '\n';
    }
    return 0;
}
```
:::


### [SPOJ - ILKQ2](http://www.spoj.com/problems/ILKQUERY2)

#### Đề bài

Cho dãy $A$ gồm $n \le 10^5$ số nguyên trong khoảng $[-10^9; 10^9]$ và $q$ truy vấn. Mỗi truy vấn có dạng:

- `0 l r k`: đếm số phần tử được bật trong đoạn $[l; r]$ có giá trị bằng $k$.
- `1 i`: chuyển trạng thái phần tử thứ $i$, nếu trước là bật thì giờ là tắt và ngược lại. Ban đầu tất cả các phần tử đều bật.

#### Lời giải

Chúng ta sẽ bắt đầu cần tích hợp nút của cây Wavelet Tree với một cấu trúc dữ liệu khác. Ở đây chúng ta sẽ dùng BIT để quản lý các vị trí bật/tắt và tính tổng dồn/cập nhật nhanh trong $\mathcal{O}(\log n)$. Kỹ thuật này còn được gọi là **Dynamic Wavelet Tree**.

::: spoiler Code tham khảo

```cpp=
#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> tr;
    BIT (int sz = 0) : tr(sz + 1) {}

    int p (int k) const { return k & -k; }

    void add (int i, int v) {
        for (; i < tr.size(); i += p(i)) tr[i] += v;
    }

    int sum (int i) const {
        int ans = 0;
        for (; i > 0; i -= p(i)) ans += tr[i];
        return ans;
    }

    int range (int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

struct WaveletTree {
    int lo, hi, mid, len;
    WaveletTree *L = nullptr, *R = nullptr;
    vector<int> leftCnt;
    BIT active;

    // xây dựng Wavelet Tree
    WaveletTree (vector<pair<int, int>>::iterator b,
                 vector<pair<int, int>>::iterator e, int mn, int mx) :
                 lo(mn), hi(mx), L(nullptr), R(nullptr), len(0) {

        if (b >= e) {
            mid = lo;
            return;
        }
        mid = lo + ((hi - lo) >> 1);
        len = int(e - b);
        leftCnt.reserve(len + 1);
        leftCnt.push_back(0);
        for (auto it = b; it != e; ++it)
            leftCnt.push_back(leftCnt.back() + (it->first <= mid));
        auto mpos = stable_partition(b, e,
            [&](const pair<int, int> &p) { return p.first <= mid; }
        );
        active = BIT(len);
        for (int i = 1; i <= len; ++i) active.add(i, 1);
        if (lo == hi) return;
        L = new WaveletTree(b, mpos, lo, mid);
        R = new WaveletTree(mpos, e, mid + 1, hi);
    }

    // thay đổi (lật bit) trạng thái của phần tử thứ pos (0: tăng 1, 1: giảm 1)
    void toggle(int pos, const int &val, const int &state) {
        active.add(pos, state == 0 ? +1 : -1);
        if (lo == hi) return;
        if (val <= mid) {
            int childPos = leftCnt[pos];
            L->toggle(childPos, val, state);
        }
        else {
            int childPos = pos - leftCnt[pos];
            R->toggle(childPos, val, state);
        }
    }

    // đếm số phần tử được bật có giá trị bằng x trong đoạn [l; r]
    int query (int l, int r, int x) const {
        if (l > r || x < lo || x > hi) return 0;
        if (lo == hi) return active.range(l, r);
        if (x <= mid) {
            int nl = leftCnt[l - 1] + 1, nr = leftCnt[r];
            return L ? L->query(nl, nr, x) : 0;
        }
        else {
            int nl = (l - 1) - leftCnt[l - 1] + 1, nr = r - leftCnt[r];
            return R ? R->query(nl, nr, x) : 0;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    if (!(cin >> N >> Q)) return 0;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<pair<int, int>> vp(N); // mảng lưu các cặp (giá trị, vị trí ban đầu)
    int mn = INT_MAX, mx = INT_MIN;
    for (int i = 0; i < N; ++i) {
        vp[i] = {A[i], i};
        mn = min(mn, A[i]);
        mx = max(mx, A[i]);
    }

    // xây dựng Wavelet Tree
    WaveletTree wt(vp.begin(), vp.end(), mn, mx);

    // trạng thái bật tắt của các phần tử
    vector<int> state(N, 1);

    while (Q--) {
        int t; cin >> t;
        if (t == 0) {
            int l, r, k; cin >> l >> r >> k;
            int ans = 0;
            if (l <= r) ans = wt.query(l + 1, r + 1, k);
            cout << ans << '\n';
        }
        else {
            int i; cin >> i;
            int pos = i + 1;
            int val = A[i];
            int st = state[i] ? 1 : 0; 
            wt.toggle(pos, val, st);
            state[i] ^= 1;
        }
    }
    return 0;
}
```
:::

### [SPOJ - ILKQ3](http://www.spoj.com/problems/ILKQUERYIII/)

#### Đề bài

Cho dãy $a$ gồm $n$ số nguyên trong khoảng $[-10^9; 10^9]$, đánh thứ tự từ $0$ và $q$ truy vấn. Mỗi truy vấn có dạng:

- `0 i t k`: gọi $d$ là phần tử nhỏ thứ $k$ cho đến chỉ số $i$. Trả về chỉ số của lần xuất hiện thứ $t$ của $d$ trong dãy. Nếu không tồn tại lần xuất hiện này thì in ra `-1`.
- `1 i`: swap 2 phần tử liền kề ở vị trí $i$ và $i + 1$.

Giới hạn: $1 \le n \le 10^6, 1 \le q \le 10^5$.

#### Lời giải

Bài toán này là mở rộng của ILKQ1, với input nhiều hơn hẳn ($n = 10^6$) và thêm truy vấn update.

Giả sử ta swap 2 phần tử khác nhau ở vị trí $i$ và $i + 1$. Khi duyệt cây từ gốc xuống, ta sẽ đến đúng một nút $v$ mà tại đó 2 phần tử này sẽ được đưa về **2 nhánh khác nhau**. Khi đó trong bitvector $B_v$ của nút $v$ sẽ có $B_v[i] \ne B_v[i + 1]$. 

Việc swap này sẽ chỉ ảnh hưởng tới mảng tổng dồn của bitvector tại đúng vị trí $i$ của nút $v$. Nếu $B_v[i] = 0, B_v[i + 1] = 1$, khi này việc swap sẽ khiến mảng tổng dồn ở $i$ tăng thêm 1 đơn vị, ngược lại thì sẽ là giảm 1 đơn vị, còn các phần tử còn lại không thay đổi.

Do đó ta có thể cài đặt hàm swap rất dễ dàng với độ phức tạp như các thao tác cơ bản là $\mathcal{O}(\log \sigma)$:

```cpp
void swap_adj(int i) {
    if (lo == hi) return;
    int a = leftCnt[i] - leftCnt[i - 1], b = leftCnt[i + 1] - leftCnt[i];
    if (a != b) pref[i] += (a == 0 ? 1 : -1);
    else {
        if (a == 1) L->swap_adj(pref[i]);
        else R->swap_adj(i - pref[i]);
    }
}
```

Độ phức tạp cho mỗi truy vấn là $\mathcal{O}(\log \sigma)$ và độ phức tạp cuối cùng là  $\mathcal{O}((N+Q) \log \sigma)$.

::: spoiler Code tham khảo

```cpp=
#include <bits/stdc++.h>
using namespace std;

struct WaveletTree {
  int lo, hi, mid;
  WaveletTree *L = 0, *R = 0;
  vector<int> pref;

  template <class It>
  WaveletTree(It b, It e, int lo, int hi) : lo(lo), hi(hi) {
    if (b >= e) return;
    mid = (lo + hi) >> 1;
    pref.reserve((int)(e - b) + 1);
    pref.push_back(0);
    for (auto it = b; it != e; ++it) pref.push_back(pref.back() + (*it <= mid));
    if (lo == hi) return;
    auto pivot = stable_partition(b, e, [&](int x) { return x <= mid; });
    L = new WaveletTree(b, pivot, lo, mid);
    R = new WaveletTree(pivot, e, mid + 1, hi);
  }

  int quantile(int r, int k) {
    if (lo == hi) return lo;
    int inLeft = pref[r];
    if (k <= inLeft) return L->quantile(inLeft, k);
    return R->quantile(r - inLeft, k - inLeft);
  }

  int rank(int r, int x) {
    if (r == 0) return 0;
    if (lo == hi) return r;
    if (x <= mid) return L->rank(pref[r], x);
    return R->rank(r - pref[r], x);
  }

  int select(int x, int j) {
    if (lo == hi) return j;
    if (x <= mid) {
      int pos = L->select(x, j);
      return (int)(lower_bound(pref.begin(), pref.end(), pos) - pref.begin());
    } else {
      int pos = R->select(x, j);
      int l = 0, r = (int)pref.size() - 1;
      while (l < r) {
        int m = (l + r) >> 1;
        if (m - pref[m] >= pos)
          r = m;
        else
          l = m + 1;
      }
      return l;
    }
  }

  void swap_adj(int i) {
    if (lo == hi) return;
    int a = pref[i] - pref[i - 1], b = pref[i + 1] - pref[i];
    if (a != b) {
      pref[i] += (a == 0 ? 1 : -1);
    } else {
      if (a == 1)
        L->swap_adj(pref[i]);
      else
        R->swap_adj(i - pref[i]);
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  // compress
  vector<int> vals = A;
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  for (auto &x : A)
    x = int(lower_bound(vals.begin(), vals.end(), x) - vals.begin());

  WaveletTree wt(A.begin(), A.end(), 0, (int)vals.size() - 1);

  while (Q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int i;
      cin >> i;
      if (i + 1 < N) {
        wt.swap_adj(i + 1);
        swap(A[i], A[i + 1]);
      }
    } else {
      int i, l, k;
      cin >> i >> l >> k;
      int d = wt.quantile(i + 1, k);
      int occ = wt.rank(N, d);
      if (l > occ)
        cout << -1 << "\n";
      else
        cout << wt.select(d, l) - 1 << "\n";
    }
  }
}
```
:::

## Phụ lục

### Tài liệu tham khảo

- [USACO Guide - Wavelet Tree](https://usaco.guide/adv/wavelet)

### Bài tập ứng dụng

- [Library Checker - Range Kth Smallest](https://judge.yosupo.jp/problem/range_kth_smallest)
- [ABC339G - Smaller Sum](https://atcoder.jp/contests/abc339/tasks/abc339_g)
- [GlobeX Cup '19 S4 - Ninjaclasher's Wrath 2
](https://dmoj.ca/problem/globexcup19s4)
- [CF840D - Destiny](https://codeforces.com/contest/840/problem/D)
- [CF543E - Listening to Music](https://codeforces.com/contest/543/problem/E)
- [ICPC Regional Danang 2019 - Easy Query](https://oj.vnoi.info/problem/icpc19_regional_e) 
- [D-query](https://oj.vnoi.info/problem/dquery)
- [Phần tử trung vị](https://oj.vnoi.info/problem/median)
- [Dãy số](https://oj.vnoi.info/problem/c11seq)
- [[PreVOI 25 - Contest 3] - Bài 4: Hoán vị](https://oj.clue.edu.vn/problem/prevoi25_c3_per)

