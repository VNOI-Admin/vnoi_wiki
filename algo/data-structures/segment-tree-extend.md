# Tất tần tật về Cây Phân Đoạn (Segment Tree)

[[_TOC_]]

**LƯU Ý**:

- Segment Tree trong 1 số tài liệu Tiếng Việt còn được dịch là Interval Tree. Ở bài viết này, mình sẽ dùng tên Segment Tree (ST) - tên gọi phổ biến hơn của CTDL này.
- Tất cả hàm trong bài đều đánh số từ 1. Các nút của cây phân đoạn sẽ quản lý đoạn $[l,r]$

# 0. Giới thiệu

Segment Tree là một cấu trúc dữ liệu được sử dụng rất nhiều trong các kỳ thi, đặc biệt là trong những bài toán xử lý trên dãy số.

Segment Tree là một [cây](translate/wcipeg/tree). Cụ thể hơn, nó là một cây nhị phân đầy đủ (mỗi nút là lá hoặc có đúng 2 nút con), với mỗi nút quản lý một đoạn trên dãy số. Với một dãy số gồm $N$ phần tử, nút gốc sẽ lưu thông tin về đoạn $[1, N]$, nút con trái của nó sẽ lưu thông tin về đoạn $[1, ⌊N/2⌋]$ và nút con phải sẽ lưu thông tin về đoạn $[⌊N/2⌋+1, N]$. Tổng quát hơn: nếu nút $A$ lưu thông tin đoạn $[i, j]$, thì 2 con của nó: $A1$ và $A2$ sẽ lưu thông tin của các đoạn $[i, ⌊(i+j)/2⌋]$ và đoạn $[⌊(i+j)/2⌋ + 1, j]$.

## Ví dụ

Xét một dãy gồm 7 phần tử, Segment Tree sẽ quản lý các đoạn như sau:

[[/uploads/segment_tree_structure_example.png]]

## Cài đặt

Để cài đặt, ta có thể dùng một mảng 1 chiều, phần tử thứ nhất của mảng thể hiện nút gốc. Phần tử thứ $id$ sẽ có 2 con là $2 \* id$ (con trái) và $2 \* id+1$ (con phải). Với cách cài đặt này, người ta đã chứng minh được bộ nhớ cần dùng cho ST không quá $4 \* N$ phần tử.

## Áp dụng

Để dễ hình dung, ta lấy 1 ví dụ cụ thể, từ bài [VOJ - QMAX](http://vn.spoj.com/problems/QMAX)

- Cho dãy $N$ phần tử $(N \le 10^5)$. Ban đầu mỗi phần tử có giả trị 0.
- Có $Q$ truy vấn $(Q \le 10^5)$. Mỗi truy vấn có 1 trong 2 loại:
    1. Gán giá trị $v$ cho phần tử ở vị trí $i$.
    2. Tìm giá trị lớn nhất cho đoạn $[i, j]$.

Cách đơn giản nhất là dùng 1 mảng $A$ duy trì giá trị các phần tử. Với thao tác 1 thì ta gán $A[i] = v$. Với thao tác 2 thì ta dùng 1 vòng lặp từ $i$ đến $j$ để tìm giá trị lớn nhất. Rõ ràng cách này có độ phức tạp là $O(N*Q)$ và không thể chạy trong thời gian cho phép.

Cách dùng Segment Tree như sau:

- Với truy vấn loại 1, ta sẽ cập nhật thông tin của các nút trên cây ST mà đoạn nó quản lý chứa phần tử $i$.
- Với truy vấn loại 2, ta sẽ tìm tất cả các nút trên cây ST mà đoạn nó quản lý nằm trong $[i, j]$, rồi lấy max của các nút này.

Cài đặt như sau:

```cpp
// Truy vấn: A(i) = v
// Hàm cập nhật trên cây ST, cập nhật cây con gốc id quản lý đọan [l, r]
void update(int id, int l, int r, int i, int v) {
    if (i < l || r < i) {
        // i nằm ngoài đoạn [l, r], ta bỏ qua nút i
        return ;
    }
    // i nằm trong đoạn [l, r], ta cần cập nhật nút id
    ST[id] = max(ST[id], v);

    // Gọi đệ quy để xử lý các nút con của nút id
    int mid = (l + r) / 2;
    update(id*2, l, mid, i, v);
    update(id*2 + 1, mid+1, r, i, v);
}

// Truy vấn: tìm max đoạn [u, v]
// Hàm tìm max các phần tử trên cây ST nằm trong cây con gốc id - quản lý đoạn [l, r]
int get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
        // Đoạn [u, v] không giao với đoạn [l, r], ta bỏ qua đoạn này
        return -INFINITY;
    }
    if (u <= l && r <= v) {
        // Đoạn [l, r] nằm hoàn toàn trong đoạn [u, v] mà ta đang truy vấn, ta trả lại
        // thông tin lưu ở nút id
        return ST[id];
    }
    int mid = (l + r) / 2;
    // Gọi đệ quy với các con của nút id
    return max(get(id*2, l, mid, u, v), get(id*2 + 1, mid+1, r, u, v));
}
```

## Phân tích thời gian chạy

Mỗi thao tác truy vấn trên cây ST có độ phức tạp $O(\log{N})$. Để chứng minh điều này, ta xét 2 loại thao tác trên cây ST:

1. Truy vấn 1 phần tử trên ST (giống thao tác `update` ở trên)
2. Truy vấn nhiều phần tử trên ST (giống thao tác `get` ở trên)

Đầu tiên ta có thể chứng minh được:

- Độ cao của cây ST không quá $O(\log{N})$.
- Tại mỗi độ sâu của cây, không có phần tử nào nằm trong 2 nút khác nhau của cây.

### Thao tác loại 1

Với thao tác này, ở mỗi độ sâu của cây, ta chỉ gọi đệ quy các con của không quá 1 nút. Phân tích đoạn code trên, ta xét các trường hợp:

- Phần tử cần xét không nằm trong đoạn $[l, r]$ do nút $id$ quản lý. Trường hợp này ta dừng lại, không xét tiếp.
- Phần tử cần xét nằm trong đoạn $[l, r]$ do nút $id$ quản lý. Ta xét các con của nút `id`. Tuy nhiên chỉ có 1 con của nút `id` chứa phần tử cần xét và ta sẽ phải xét tiếp các con của nút này. Với con còn lại, ta sẽ dừng ngay mà không xét các con của nó nữa.

Do đó độ phức tạp của thao tác này không quá $O(\log{N})$.


### Thao tác loại 2

Với thao này, ta cũng chứng minh tương tự, nhưng ở mỗi dộ sâu của cây, ta chỉ gọi hàm đệ quy với các con của không quá 2 nút.

Ta chứng minh bằng phản chứng, giả sử ta gọi đệ quy với 3 nút khác nhau của cây ST (đánh dấu màu đỏ):

[[/uploads/segment_tree_proof_time_complexity.png]]

Trong trường hợp này, rõ ràng toàn bộ đoạn của nút ở giữa quản lý nằm trong đoạn đang truy vấn. Do đó ta không cần phải gọi đệ quy các con của nút ở giữa. Từ đó suy ra vô lý, nghĩa là ở mỗi độ sâu ta chỉ gọi đệ quy với không quá 2 nút.

## Phân tích bộ nhớ

Ta xét 2 trường hợp:

- $N = 2^k$: Cây ST đầy đủ, ở độ sâu cuối cùng có đúng $2^k$ lá, và các độ sâu thấp hơn không có nút lá nào (và các nút này đều có đúng 2 con). Như vậy:
    - Tầng $k$: có $2^k$ nút
    - Tầng $k-1$: có $2^{k-1}$ nút
    - ...
    Tổng số nút không quá $2^{k+1}$.
- Với $N > 2^k$ và $N < 2^{k+1}$. Số nút của cây ST không quá số nút của cây ST với $N = 2^{k+1}$.

Do đó, số nút của cây cho dãy $N$ phần tử, với $N \le 2^k$ là không quá $2^{k+1}$, giá trị này xấp xỉ $4 \* N$. Bằng thực nghiệm, ta thấy dùng $4 \* N$ là đủ.

# 1. Segment Tree cổ điển

Tại sao lại gọi là cổ điển? Đây là dạng ST đơn giản nhất, chúng ta chỉ giải quyết truy vấn update một phần tử và truy vấn đoạn, mỗi nút lưu một loại dữ liệu cơ bản như biến số hay biến luận lý (boolean).

## Ví dụ 1

**Bài toán**: [380C-Codeforces](http://codeforces.com/contest/380/problem/C)

### Tóm tắt đề

Cho một dãy ngoặc độ dài $N$ $(N\le10^6)$, cho $M$ truy vấn có dạng $l_i, r_i (1\le l_i\le r_i \le N)$. Yêu cầu của bài toán là với mỗi truy vấn tìm một chuỗi con (không cần liên tiếp) của chuỗi từ $l_i$ đến $r_i$ dài nhất mà tạo thành dãy ngoặc đúng.

### Lời giải

Với mỗi nút(ví dụ như nút $id$, quản lý đoạn $[l, r]$) chúng ta lưu ba biến nguyên:

- `optimal`: Là kết quả tối ưu trong đoạn $[l, r]$.
- `open`: Số lượng dấu `(` sau khi đã xóa hết các phần tử thuộc dãy ngoặc đúng độ dài `optimal` trong đoạn.
- `close`: Số lượng dấu `)` sau khi đã xóa hết các phần tử thuộc dãy ngoặc đúng độ dài `optimal` trong đoạn.

Ta tạo 1 kiểu dữ liệu cho 1 nút của cây ST như sau:

```cpp
struct Node {
    int optimal;
    int open;
    int close;

    Node(int opt, int o, int c) { // Khởi tạo struct Node
        optimal = opt;
        open = o;
        close = c;
    }
};
```

Và ta khai báo cây ST như sau:

```cpp
Node st[MAXN * 4];
```

### Định lý

Để tính thông tin ở nút $id$ quản lý đoạn $[l, r]$, dựa trên 2 nút con $2\*id$ và $2\*id+1$, ta định nghĩa 1 thao tác kết hợp 2 nút của cây ST:

```cpp
Node operator + (const Node& left, const Node& right) {
    Node res;
    // min(số dấu "(" thừa ra ở cây con trái, và số dấu ")" thừa ra ở cây con phải)
    int tmp = min(left.open, right.close);

    // Để xây dựng kết quả tối ưu ở nút id, ta nối dãy ngoặc tối ưu ở 2 con, rồi thêm
    // min(số "(" thừa ra ở con trái, số ")" thừa ra ở con phải).
    res.optimal = left.optimal + right.optimal + tmp;

    res.open = left.open + right.open - tmp;
    res.close = left.close + right.close - tmp;

    return res;
}
```

Ban đầu ta có thể khởi tạo cây như sau:

```cpp
void build(int id, int l, int r) {
    if (l == r) {
        // Đoạn [l, r] chỉ có 1 phần tử.
        if (s[l] == '(') st[id] = Node(0, 1, 0);
        else st[id] = Node(0, 0, 1);
        return ;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid+1, r);

    st[id] = st[id * 2] + st[id * 2 + 1];
}
```

Để trả lời truy vấn, ta cũng làm tương tự như trong bài toán cơ bản:

``` cpp
Node query(int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
        // Trường hợp không giao nhau
        return Node(0, 0, 0);
    }
    if (u <= l && r <= v) {
        // Trường hợp [l, r] nằm hoàn toàn trong [u, v]
        return st[id];
    }

    int mid = (l + r) / 2;
    return query(id * 2, l, mid, u, v) + query(id * 2 + 1, mid+1, r, u, v);
}
```

## Ví dụ 2

**Bài toán**: [SPOJ-KQUERY](http://www.spoj.com/problems/KQUERY/)

**Tóm đề**:

- Cho một dãy số $a_i(1\le a_i \le 10^9)$ có $N(1\le N \le 30,000)$ phần tử
- Cho $Q(1\le Q \le 200,000)$ truy vấn có dạng 3 số nguyên là $l_i, r_i, k_i$ $(1\le l_i\le r_i\le N, 1\le k \le 10^9)$. Yêu cầu của bài toán là đếm số lượng số $a_j (l_i\le j \le r_i)$ mà $a_j\ge k$.

Giả sử chúng ta có một mảng $b$ với $b_i=1$ nếu $a_i>k$ và bằng $0$ nếu ngược lại. Thì chúng ta có thể dễ dàng trả lời truy vấn $(i, j, k)$ bằng cách lấy tổng từ $i$ đến $j$.

Cách làm của bài này là xử lý các truy vấn theo một thứ tự khác, để ta có thể dễ dàng tính được mảng $b$. Kĩ năng này được gọi là **xử lý offline** (tương tự nếu ta trả lời các truy vấn theo đúng thứ tự trong input, thì được gọi là **xử lý online**):

- Sắp xếp các truy vấn theo thứ tự tăng dần của $k$.
- Lúc đầu mảng $b$ gồm toàn bộ các số 1.
- Với mỗi truy vấn, ta xem trong mảng $a$ có những phần tử nào lớn hơn giá trị $k$ của truy vấn trước, và nhỏ hơn giá trị $k$ của truy vấn hiện tại, rồi đánh dấu các vị trí đó trên mảng $b$ thành 0. Để làm được việc này một cách hiệu quả, ta cũng cần sắp xếp lại mảng $a$ theo thứ tự tăng dần.

Ta tạo kiểu dữ liệu cho truy vấn:

```cpp
struct Query {
    int k;
    int l, r;
};

// so sánh 2 truy vấn để dùng vào việc sort.
bool operator < (const Query& a, const Query &b) {
    return a.k < b.k;
}
```

Phần xử lý chính sẽ như sau:

```cpp
vector< Query > queries; // các truy vấn
// Đọc vào các truy vấn
readInput();

// Sắp xếp các truy vấn
sort(queries.begin(), queries.end());

// Khởi tạo mảng id sao cho:
// a[id[1]], a[id[2]], a[id[3]] là mảng a đã sắp xếp tăng dần.

// Khởi tạo Segment Tree

for(Query q : queries) {
    while (a[id[i]] <= q.k) {
        b[id[i]] = 0;
        // Cập nhật cây Segment Tree.
        ++i;
    }
}
```

Vậy ta có thể viết hàm xây dựng cây như sau:

```cpp
void build(int id, int l, int r) {
    if (l == r) {
        // Nút id chỉ gồm 1 phần tử
        st[id] = 1;
        return ;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2, mid+1, r);

    st[id] = st[id*2] + st[id*2+1];
}
```

Một hàm cập nhật khi ta muốn gán lại một vị trí bằng 0:

```cpp
void update(int id, int l, int r, int u) {
    if (u < l || r < u) {
        // u nằm ngoài đoạn [l, r]
        return ;
    }
    if (l == r) {
        st[id] = 0;
        return ;
    }
    int mid = (l + r) / 2;
    update(id*2, l, mid, u);
    update(id*2 + 1, mid+1, r, u);

    st[id] = st[id*2] + st[id*2+1];
}
```

Và cuối cùng là thực hiện truy vấn lấy tổng một đoạn:

```cpp
int get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
        // Đoạn [l, r] nằm ngoài đoạn [u, v]
        return 0;
    }
    if (u <= l && r <= v) {
        // Đoạn [l, r] nằm hoàn toàn trong đoạn [u, v]
        return st[id];
    }
    int mid = (l + r) / 2;
    return get(id*2, l, mid, u, v)
        + get(id*2+1, mid+1, r, u, v);
}
```


# 2. Lazy Propagation

Đây là kĩ thuật được sử dụng trong ST để giảm độ phức tạp của ST với các truy vấn cập nhật đoạn.

## Bài Toán

[VOJ - QMAX2](http://vn.spoj.com/problems/QMAX2)

## Tóm tắt đề

Cho dãy số $A$ với $N$ phần tử $(N \le 50,000)$. Bạn cần thực hiện 2 loại truy vấn:

1. Cộng tất cả các số trong đoạn $[l, r]$ lên giá trị $val$.
2. In ra giá trị lớn nhất của các số trong đoạn $[l, r]$.

## Phân tích

Thao tác 2 là thao tác cơ bản trên Segment Tree, đã được ta phân tích ở bài QMAX ở trên.

Với thao tác 1, truy vấn đoạn $[u, v]$. Giả sử ta gọi $F(id)$ là giá trị lớn nhất trong đoạn mà nút $id$ quản lý. Trong lúc cập nhật, muốn hàm này thực hiện với độ phức tạp không quá $O(\log{N})$, thì khi đến 1 nút $id$ quản lý đoạn $[l, r]$ với đoạn $[l, r]$ nằm hoàn toàn trong đoạn $[u, v]$, thì ta không được đi vào các nút con của nó nữa (nếu không độ phức tạp sẽ là $O(N)$ do ta đi vào tất cả các nút nằm trong đoạn $[u, v]$). Để giải quyết, ta dùng kĩ thuật Lazy Propagation như sau:

- Lưu $T(id)$ với ý nghĩa, tất cả các phần tử trong đoạn $[l, r]$ mà nút $id$ quản lý đều được cộng thêm $T(id)$.
- Trước khi ta cập nhật hoặc lấy 1 giá trị của 1 nút $id'$ nào đó, ta phải đảm bảo ta đã "đẩy" giá trị của mảng $T$ ở tất cả các nút tổ tiên của $id'$ xuống $id'$. Để làm được điều này, ở các hàm `get` và `update`, trước khi gọi đệ quy xuống các con $2 \* id$ và $2 \* id+1$, ta phải gán:
    - `T[id*2] += T[id]`
    - `T[id*2+1] += T[id]`
    - `T[id] = 0` chú ý ta cần phải thực hiện thao tác này, nếu không mỗi phần tử của dãy sẽ bị cộng nhiều lần, do ta đẩy xuống nhiều lần.

**Chú ý**: Bài QMAX2 này có cách cài đặt khác không sử dụng Lazy Propagation, tuy nhiên sẽ không được trình bày ở đây.

## Cài đặt

Ta có kiểu dữ liệu cho 1 nút của ST như sau:

```cpp
struct Node {
    int lazy; // giá trị T trong phân tích trên
    int val; // giá trị lớn nhất.
} nodes[MAXN * 4];
```

Hàm "đẩy" giá trị $T$ xuống các con:

```cpp
void down(int id) {
    int t = nodes[id].lazy;
    nodes[id*2].lazy += t;
    nodes[id*2].val += t;

    nodes[id*2+1].lazy += t;
    nodes[id*2+1].val += t;

    nodes[id].lazy = 0;
}

```

Hàm cập nhật:

```cpp
void update(int id, int l, int r, int u, int v, int val) {
    if (v < l || r < u) {
        return ;
    }
    if (u <= l && r <= v) {
        // Khi cài đặt, ta LUÔN ĐẢM BẢO giá trị của nút được cập nhật ĐỒNG THỜI với
        // giá trị lazy propagation. Như vậy sẽ tránh sai sót.
        nodes[id].val += val;
        nodes[id].lazy += val;
        return ;
    }
    int mid = (l + r) / 2;

    down(id); // đẩy giá trị lazy propagation xuống các con

    update(id*2, l, mid, u, v, val);
    update(id*2+1, mid+1, r, u, v, val);

    nodes[id].val = max(nodes[id*2].val, nodes[id*2+1].val);
}
```

Hàm lấy giá trị lớn nhất:

```cpp
int get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
        return -INFINITY;
    }
    if (u <= l && r <= v) {
        return nodes[id].val;
    }
    int mid = (l + r) / 2;
    down(id); // đẩy giá trị lazy propagation xuống các con

    return max(get(id*2, l, mid, u, v),
        get(id*2+1, mid+1, r, u, v));
    // Trong các bài toán tổng quát, giá trị ở nút id có thể bị thay đổi (do ta đẩy lazy propagation
    // xuống các con). Khi đó, ta cần cập nhật lại thông tin của nút id dựa trên thông tin của các con.
}
```

Đến đây các bạn đã nắm được kiến thức cơ bản về Segment Tree. Những phần tiếp theo nói về các kiến thức nâng cao - các mở rộng của ST. Bạn nên làm nhiều bài luyện tập (tham khảo ở cuối bài) trước khi nghiên cứu tiếp.

# 3. Ứng dụng với cấu trúc mảng động

Trong loại bài toán này với mỗi nút của cây ta lưu lại một `vector` và một số biến khác.

## Ví dụ

[KQUERY2](http://vn.spoj.com/problems/KQUERY2).

## Tóm tắt đề

- Cho dãy $A$ với $N$ phần tử. Cần trả lời $Q$ truy vấn.
- Có 2 loại truy vấn:
    - Cập nhật: Gán $A_i = v$
    - Truy vấn: đếm số phần tử lớn hơn $k$ trong đoạn $[l, r]$.
- Giới hạn:
    - $N \le 30,000$
    - $A_i, v \le 10,000$
    - $Q \le 200,000$

Bài này tương đối giống với bài KQUERY đã phân tích ở trên, tuy nhiên vì có thao tác cập nhật, nên ta buộc phải xử lý online.

## Phân tích

- Có $\log{N}$ nút mà ta cần xét khi trả lời truy vấn của đoạn $[u, v]$.
- Nếu trên mỗi nút chúng ta có thể lưu lại danh sách các phần tử đó theo thứ tự tăng dần, ta có thể tìm ra kết quả ở mỗi nút bằng tìm kiếm nhị phân.

Vì thế với mỗi nút ta lưu lại một `vector` chứa các phần tử từ $l$ đến $r$ theo thứ tự tăng dần. Điều này có thể được thực hiện với bộ phức tạp bộ nhớ là $\mathcal{O}(N\log{N})$ do mỗi phần tử có thể ở tối đa $\mathcal{O}(\log{N})$ nút (độ sâu của cây không quá $\mathcal{O}(\log{N})$). Ở mỗi nút cha có ta có thể gộp hai nút con vào nút cha bằng phương pháp giống như **Merge Sort** (lưu lại hai biến chạy và so sánh lần lượt từng phần tử ở hai mảng) để có thể xây dựng cây trong $\mathcal{O}(N\log{N})$.

Hàm xây cây có thể được như sau:

```cpp
void build(int id, int l, int r) {
    if (l == r) {
        // Đoạn gồm 1 phần tử. Ta dễ dàng khởi tạo nút trên ST.
        st[id].push_back(a[l]);
        return ;
    }
    int mid = (l + r) / 2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);

    merge(st[id*2].begin(), st[id*2].end(), st[id*2+1].begin(), st[id*2+1].end(), st[id].begin());
}
```

Và hàm truy vấn có thể cài đặt như sau:

```cpp
int get(int id, int l, int r, int u, int v, int k) { // Trả lời truy vấn (x, y, k)
    if (v < l || r < u) {
        return 0;
    }
    if (u <= l && r <= v) {
        // Đếm số phần tử > K bằng chặt nhị phân
        return st[id].size() - (upper_bound(st[id].begin(), st[id].end(), k) - st[id].begin());
    }
    int mid = (l + r) / 2;
    return get(id*2, l, mid, u, v, k) + get(id*2+1, mid+1, r, u, v, k);
}
```

Một ví dụ khác là bài [Component Tree](http://codeforces.com/gym/100513/problem/C)


# 4. Ứng dụng với cấu trúc set

Ở cấu trúc này mỗi nút chúng ta lưu một `set`,`multiset`, `hashmap`, hoặc `unodered map` và một số biến khác.

Đây là một bài toán ví dụ:
Cho $n$ vector $a_1, a_2, a_3,...,a_n$ rỗng ban đầu. Chúng ta có thể thực hiện $m$ truy vấn trên những vector này:

1. Truy vấn $A$ $p$ $k$ là thêm số $k$ vào cuối vector $a_p$.
2. Truy vấn $C$ $l$ $r$ $k$ là xuất ra $\sum_{i=l}^rcount(a_i,k)$, với $count(a_i,k)$ là số lần xuất hiện của số $k$ trong vector $a_i$.

Bài toán này chúng ta lưu lại mỗi nút của cây là một `multiset` $s$, với mỗi nút lưu số $k$ đúng $\sum_{i=l}^rcount(a_i,k)$ lần với độ phức tạp bộ nhớ chỉ $\mathcal{O}(q\log{n})$.

Với mỗi truy vấn  $C$ $x$ $y$ $k$ chúng ta sẽ in ra tổng của tất cả dùng cây phân đoạn và truy vấn trên set trong mỗi đoạn thuộc đoạn $x$ đến $y$ như truy trên truy vấn cây phân đoạn bình thường.

Chúng ta sẽ không có hàm xây cây do các vector ban đầu đang là rỗng, nhưng chúng ta sẽ có thêm hàm cộng phần tử vào như sau:

```cpp
void add(int id, int l, int r, int p, int k) {  // Thực hiện truy vấn A p k
    s[id].insert(k);
    if (l == r) return ;

    int mid = (l + r) / 2;
    if (p <= mid) add(id*2, l, mid, p, k);
    else add(id*2 + 1, mid+1, r, p, k);
}
```

Và một hàm cho truy vấn 2:

```cpp
int ask(int id, int l, int r, int x, int y, int k) { // Trả lời C x y k
    if (y < l || r < x) return 0;
    if (x <= l && r <= y) {
        return s[id].count(k);
    }
    int mid = (l + r) / 2;
    return ask(id*2, l, mid, x, y, k) + ask(id*2+1, mid+1, r, x, y, k);
}
```

# 5. Ứng dụng với các cấu trúc dữ liệu khác

Cây phân đoạn còn có thể có thể sử dụng một cách linh hoạt với các cấu trúc dữ liệu khác như ở trên. Sử dụng một cây phân đoạn khác trên từng nút có thể giúp chúng ta truy vấn dễ dàng hơn trên mảng hai chiều. Trên đây cũng có thể là các loại cây như **Cây tiền tố(Trie)** hoặc cũng có thể là cấu trúc **Disjoint Set**. Sau đây mình xin giới thiệu một loại cây khác cũng sử dụng nhiều trong cây phân đoạn đó chính là **Cây Fenwick (Binary Indexed Tree)**:

Như trên mỗi nút của cây sẽ là một cây **Fenwick** và có thể một số biến khác. Dưới đây là một bài toán ví dụ:

Cho $n$ vectors $a_1,a_2,a_3,...,a_n$ rỗng ban đầu. Chúng ta cần thực hiện hai loại truy vấn:

1. Truy vấn $A$ $p$ $k$ là thêm số $k$ vào đằng sau vector $a_p$.
2. Truy vấn $C$ $l$ $r$ $k$ là xuất ra $\sum_{i=l}^rcount(a_i,j)$ với $j\le k$ với $count(a_i,j)$ là số lần xuất hiện $k$ trong $a_i$.

Với bài toán này, ta cũng lưu lại ở một nút là một `vector` $v$ chứa số $k$ khi và chỉ khi $\sum_{i=l}^rcount(a_i,j)\ne 0$ (độ phức tạp bộ nhớ sẽ là $\mathcal{O}(q\log{n})$ ) (các số theo theo thứ tự tăng dần)

Đầu tiên, đọc và lưu các truy vấn lại với mỗi truy vấn loại 1 ta sẽ thêm $v$ vào tất cả vector có chứa phần tử $p$. Sau đó ta tiến hành sắp xếp các truy vấn theo phương pháp **Merge Sort** đã nói ở trên và dùng hàm `unique` để loại các phần tử trùng.

Sau đó chúng ta sẽ xây dụng ở mỗi nút một cây Fenwick có độ lớn bằng độ dài vector. Sau đây là hàm thêm giá trị:

```cpp
void insert(int id, int l, int r, int p, int k) { // Thực hiện A p k
    if (l == r) {
        v[id].push_back(k);
        return ;
    }
    int mid = (l+r) / 2;
    if (p < mid)
        insert(id*2, l, mid, p, k);
    else
        insert(id*2+1, mid+1, r, p, k);
}
```

Hàm sắp xếp sau khi đã đọc hết các truy vấn:

```cpp
void sort_(int id, int l, int r) {
    if (l == r) return ;
    int mid = (l + r) / 2;
    sort_(id*2, l, mid);
    sort_(id*2+1, mid+1, r);

    merge(v[2 * id].begin(), v[2 * id].end(), v[2 * id + 1].begin(), v[2 * id +1].end(), v[id].begin());
}
```

Với mỗi truy vấn loại 1 ta làm như sau với mỗi nút x:

```cpp
for(int i = a + 1; i < fen[x].size(); i += i & -i)
    fen[x][i] ++;
```

Với tất cả $v[x][a]=k$:

```cpp
void update(int id, int l, int r, int p, int k) {
    int a = lower_bound(v[id].begin(), v[id].end(), k) - v[id].begin();
    for(int i = a + 1; i < fen[id].size(); i += i & -i)
        fen[id][i]++;

    if (l == r) return ;

    int mid = (l + r) / 2;
    if (p < mid)
        update(id*2, l, mid, p, k);
    else
        update(id*2+1, mid+1, r, p, k);
}
```

Còn lại việc tính toán truy vấn loại 2 trở nên dễ dàng hơn:

```cpp
int ask(int id, int l, int r, int x, int y, int k) { // Trả lời C x y-1 k
    if (y < l || r < x) return 0;
    if (x <= l && r <= y) {
        int a = lower_bound(v[id].begin(), v[id].end(), k) - v[id].begin();
        int ans = 0;
        for(int i = a + 1; i > 0; i -= i & -i)
            ans += fen[id][i];
        return ans;
    }
    int mid = (l + r) / 2;
    return ask(id*2, l, mid, x, y, k)
        + ask(id*2+1, mid+1, r, x, y, k);
}
```

# 6. Ứng dụng trong cây có gốc

Ta có thể thấy cây phân đoạn là một ứng dụng trong mảng, vì lí do đó nếu chúng ta có thể đổi cây thành các mảng, ta có thể dễ dàng xử lý các truy vấn trên cây. Đây là tư tưởng của [Heavy Light Decomposition](algo/data-structures/heavy-light-decomposition).

**Bài tập ví dụ**: [396C - On Changing Tree](http://codeforces.com/contest/396/problem/C)

Gọi $h_v$ là độ cao tương ứng của nút $v$.

Ta có với mỗi nút $u$ trong cây con gốc $v$ sau truy vấn một giá trị của nó sẽ tăng một lượng là $x+(h_u-h_v)\*-k=x+k\* h_v-k\* h$. Kết quả của truy vấn 2 sẽ là $\sum_{i\in s}(k_i\*h_{v_i}+x_i)-h_u\*\sum_{i\in s}k_i$. Vì vậy ta chỉ cần tính hai giá trị là $\sum_{i\in s}(k_i\* h_{v_i}+x_i)$ và $\sum_{i\in s}k_i$. Vậy với mỗi nút ta có thể lưu lại hai giá trị là $hkx=\sum x +h*k$ và $sk=\sum k$ (không cần lazy propagation do chúng ta chỉ update nút đầu tiên thỏa việc nằm trong đoạn.

Với truy vấn cập nhật:

```cpp
void update(int id, int l, int r, int x, int k, int v) {
    if (s[v] >= r || l >= f[v]) return ;
    if (s[v] <= l && r <= f[v]) {
        hkx[id] = (hkx[id] + x) % mod;
  			int a = (1LL * h[v] * k) % mod;
  			hkx[id] = (hkx[id] + a) % mod;
  			sk[id] = (sk[id] + k) % mod;
  			return ;
    }
    int mid = (l+r) / 2;
    update(id*2, l, mid, x, k, v);
    update(id*2+1, mid+1, r, x, k, v);
}
```

Và truy vấn:

```cpp
int ask(int id, int l, int r, int v) {
    int a = (1LL * h[v] * sk[id]) % mod;
    int ans = (hkx[id] + mod - a) % mod;
    if (l == r) return ans;
    int mid = (l+r) / 2;
    if(s[v] < mid)
        return (ans + ask(2 * id, l, mid, v)) % mod;
    return (ans + ask(2*id + 1, mid, r, v)) % mod;
}
```

# 7. Persistent Segment Trees

**Persistent Data Structures** là những cấu trúc dữ liệu được dùng khi chúng ta cần có **toàn bộ lịch sử** của các thay đổi trên 1 cấu trúc dữ liệu (CTDL).

Các bạn có thể đọc thêm ở: [Persistent Data Structures](algo/data-structures/persistent-data-structures)


# Bài tập áp dụng:

- [VOJ - NKLINEUP](http://vn.spoj.com/problems/NKLINEUP)
- [VOJ - GSS](http://vn.spoj.com/problems/GSS)
- [VOJ - LITES](http://vn.spoj.com/problems/LITES)
- [VOJ - DQUERY](http://vn.spoj.com/problems/DQUERY)
- [VOJ - KQUERY](http://vn.spoj.com/problems/KQUERY)
- [FREQUENT](http://www.spoj.com/problems/FREQUENT/)
- [VOJ - KQUERY2](http://vn.spoj.com/problems/KQUERY2)
- [GSS2](http://www.spoj.com/problems/GSS2/)
- [GSS3](http://www.spoj.com/problems/GSS3/)
- [MULTQ3](http://www.spoj.com/problems/MULTQ3)
- [POSTERS](http://www.spoj.com/problems/POSTERS)
- [PATULJCI](http://www.spoj.com/problems/PATULJCI)
- [New Year Domino](http://codeforces.com/problemset/problem/500/E)
- [Copying Data](http://codeforces.com/problemset/problem/292/E)
- [DZY Loves Fibonacci Numbers](http://codeforces.com/problemset/problem/446/)
- [FRBSUM](http://www.codechef.com/JAN14/problems/FRBSUM)


# Các nguồn tham khảo:

- [Codeforces](http://codeforces.com/blog/entry/15890)
- [Một số vấn đề đáng chú ý trong môn Tin học](algo/basic/Tai-Lieu-Thuat-Toan)
