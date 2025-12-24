---
title: Li-chao Tree
description: 
published: true
date: 2024-10-27T10:34:29.779Z
tags: 
editor: markdown
dateCreated: 2024-10-27T10:34:29.779Z
---

# Li-chao Tree (Cây phân đoạn trên tập đường thẳng)

**Tác giả:**
- Nguyễn Tấn Minh - THPT Chuyên Lê Hồng Phong, TPHCM.

**Reviewer:**
- Đoàn Gia Huy - HUS High School for Gifted Students
- Nguyễn Quang Minh - HUS High School for Gifted Students 


## Giới thiệu

**Li-chao tree** (cây phân đoạn trên tập đường thẳng) là một biến thể của **Segment tree**[^[1]^](/algo/data-structures/segment-tree-extend) (cây phân đoạn) cho phép quản lý một tập đường thẳng với $2$ thao tác sau:
1. Thêm một hàm $f(x) = ax + b$ vào tập đường thẳng.
2. Cho một số nguyên $t$ (với $1 \leq t \leq M$), gọi $S$ là tập đường thẳng hiện tại, tính $\min_{f \in S} f(t)$ hoặc $\max_{f \in S} f(t)$.

Cả hai thao tác trên đều có thể được xử lý trong $O(\log M)$.

Tổng quát hơn, Li-chao tree có thể xử lý những loại hàm có tính chất sau:

:::info
Gọi $f(x)$ và $g(x)$ là hai hàm bất kì thuộc loại này sao cho $f(x)$ và $g(x)$ xác định trên khoảng $D$ đang xét. Hai hàm này cần thỏa một trong hai tính chất:
- Nếu $f(x_1) < g(x_1)$ thì $f(x_2) < g(x_2)$ với $x_1 < x_2$ và $x_1, x_2 \in D$.
- Nếu $f(x_1) > g(x_1)$ thì $f(x_2) > g(x_2)$ với $x_1 < x_2$ và $x_1, x_2 \in D$.

Hoặc ta cũng có thể biến đổi điều kiện này thành $f(x)$ cắt $g(x)$ tại **tối đa** $1$ điểm.
:::

Trong bài viết này, ta chỉ quan tâm đến phương trình đường thẳng, loại phương trình thỏa tính chất nêu trên:

![function property no bg](/algo/data-structures/lichao/lichao1.png)

Ngoài ra, ta giả sử thao tác loại $2$ sẽ thực hiện tìm $\min$, thao tác tìm $\max$ được thực hiện tương tự.

## Ý tưởng

### Đường thẳng và tính chất của phương trình đường thẳng

Trong toán học, ta đã biết một đường thẳng có thể biểu diễn dưới dạng một phương trình tuyến tính bậc $1$ có dạng $ax + b$. Trong đó:

- **Hệ số góc hay độ dốc (slope) $a$** thể hiện mức độ tăng/giảm nhanh/chậm của hàm. Ví dụ, hàm $3x + 2$ tăng nhanh hơn hàm $2x + 10$ do có hệ số dốc lớn hơn. Tương tự, hàm $-10x + 1$ giảm nhanh hơn hàm $-8x - 9$ do có hệ số góc bé hơn.
- **Hệ số tự do (y-intercept) $b$** cho biết phương trình cắt trục $Oy$ tại điểm $(0, b)$.

![linear equation no bg](/algo/data-structures/lichao/lichao2.png)


### Tính chất của tập đường thẳng

Nếu vẽ một tập đường thẳng bất kì ra, ta thấy những đoạn đóng góp vào đáp án, tạm gọi là "min-line", sẽ tạo thành nửa trên của một bao lồi[^[2]^](https://en.wikipedia.org/wiki/Convex_hull) (upper hull) như sau:

![min line no bg](/algo/data-structures/lichao/lichao3.png)

Mỗi đường thẳng đóng góp vào min-line duy nhất **một đoạn liên tiếp** và từ trái qua phải, thứ tự xuất hiện của các đường thẳng là thứ tự **giảm dần theo hệ số góc** của chúng. Một số đường thẳng có thể không đóng góp gì vào min-line.

:::spoiler Đối với max-line thì sao?
Max-line sẽ tạo thành nửa dưới của một bao lồi (lower hull), với các đường thẳng đóng góp vào max-line từ trái qua phải là thứ tự tăng dần theo hệ số góc.
:::

### Xây dựng mảng $best$

Giả sử ta có mảng $best$ gồm $M$ phần tử với $best[i]$ là đường thẳng đóng góp vào min-line tại $x = i$. Với nhận xét được nêu trên, khi thêm một đường thẳng vào tập, có thể thấy một số giá trị $best[i]$ liên tiếp sẽ được gán cho đường thẳng mới.

Ví dụ, sau đây là ảnh minh họa cho mảng $best$ quản lý một upper hull tại các vị trí $x = 1, 2, 3, \cdots, 8$.

![best array no bg](/algo/data-structures/lichao/lichao4.png)

:::spoiler Lưu ý
Chúng ta phải lưu cả phương trình đường thẳng thay vì chỉ đơn giản là giá trị của hàm tại điểm đó. Nếu $best[i]$ chỉ lưu giá trị của hàm tại điểm $i$, thao tác cập nhật sẽ không còn đơn giản là gán một đoạn cho cùng một phương trình đường thẳng, mà là gán giá trị theo bậc thang.
:::

Đến đây, ta có thể liên tưởng đến Segment tree để xử lý **cập nhật đoạn (range update)** và **truy cập điểm (point access)**, sử dụng lazy propagation. Tuy nhiên, đối với Li-chao tree, ta sẽ phải làm khác đi một chút so với Segment tree truyền thống.

### Ôn lại Segment tree

Trước khi đi đến ý tưởng của Li-chao, ta sẽ tìm hiểu cách sử dụng Segment tree để xử lý bài toán sau. Cho mảng $a$ gồm $n$ phần tử và $q$ truy vấn thuộc một trong hai loại:

1. Cho ba số nguyên $L, R, x$, gán $a[i] = \min(a[i], x)$ đối với mọi $i$ thỏa $L \leq i \leq R$.
2. Cho số nguyên $p$, tính $a[p]$.

Đối với dạng bài toán này, chúng ta có thể xây dựng Segment tree chỉ có mảng `lazy` và không cần bước push-down như sau:

- Đối với truy vấn loại $1$, tách đoạn $[L; R]$ thành $O(\log n)$ đoạn (theo ý tưởng Segment tree truyền thống) và cập nhật những nút tương ứng.
- Đối với truy vấn loại $2$, lấy $\min$ của các nút quản lý vị trí $p$, tức là đường đi từ gốc xuống nút lá tương ứng.

:::spoiler Code tham khảo
```cpp=
void update (int a, int b, int x, int k, int l, int r) {
    /*
        a..b: khoảng cần cập nhật
        x: giá trị cập nhật
        k: nút hiện tại
        l..r: khoảng mà nút quản lý
    */
    if (b < l || r < a) return;
    if (a <= l && r <= b) {
        lazy[k] = min(lazy[k], x);
        return;
    }
    int mid = (l + r) >> 1;
    update(a, b, x, 2 * k, l, mid);
    update(a, b, x, 2 * k + 1, mid + 1, r);
}

int query (int p, int k, int l, int r) {
    /*
        p: vị trí được truy vấn
        k: nút hiện tại
        l..r: khoảng mà nút quản lý
    */
    int ans = lazy[k], mid = (l + r) >> 1;
    if (l == r) return ans;
    if (p <= mid)
        return min(ans, query(p, 2 * k, l, mid));
    else return min(ans, query(p, 2 * k + 1, mid + 1, r));
}
```
:::

Bây giờ, ta sẽ tìm cách biển đổi cách xử lý trên để áp dụng cho tập đường thẳng.

## Thuật toán

### Thao tác loại $1$: Thêm đường thẳng

Đầu tiên, đưa đường thẳng mới vào nút gốc của Li-chao tree. Tại mỗi nút $k$, gọi:

- $f(x)$ là hàm được đưa vào.
- $tr_k(x)$ là hàm mà nút $k$ đang chứa.
- $[l; r]$ là đoạn mà nút $k$ quản lý, $mid = \lfloor \frac{l + r}{2} \rfloor$.
- $[a; b]$ là đoạn mà hàm $f$ sẽ đóng góp vào min-line (ta chưa biết đoạn này là gì).

Ta thực hiện chia để trị[^[3]^](/algo/basic/divide-and-conquer) với $2$ trường hợp chính như sau:

#### Trường hợp 1

$$
f(mid) > tr_k(mid)
$$

Khi đó, đoạn $[a; b]$ chỉ nằm ở **một trong hai** khoảng $[l; mid]$ hoặc $(mid; r]$. Đồng nghĩa với việc hàm $tr_k$ không thay đổi và hàm $f$ sẽ được đưa xuống cây con. Để chọn cây con cho hàm $f$, ta cần so sánh hệ số góc của $f$ so với $tr_k$, cụ thể:

- Nếu hệ số góc của $f$ lớn hơn $tr_k$, hàm $f$ sẽ được đưa xuống cây con bên trái và chia để trị tiếp cho đoạn tương ứng là $[l; mid]$.
- Nếu hệ số góc của $f$ bé hơn $tr_k$, hàm $f$ sẽ được đưa xuống cây con bên phải và chia để trị tiếp cho đoạn tương ứng là $(mid; r]$.
- Nếu hệ số góc của $f$ và $tr_k$ bằng nhau, khi đó đường thẳng $f$ nằm song song và ở phía trên $tr_k$ nên chắc chắn sẽ không đóng góp gì vào min-line. Ta có thể không làm gì cả hoặc gộp trường hợp này vào một trong hai trường hợp nêu trên.

![slope comparison 1 no bg](/algo/data-structures/lichao/lichao5.png)


#### Trường hợp 2

$$
f(mid) < tr_k(mid)
$$

Khi đó, đoạn $[a; b]$ nằm ở **cả hai** khoảng $[l; mid]$ và $(mid; r]$. Đồng nghĩa với việc hàm $tr_k$ sẽ bị thay thế bởi hàm $f$. Ta gán $tr_k$ bằng $f$, thao tác này tương đương với gán $best[i] = f$ cho đoạn $[l; r]$

:::spoiler Lưu ý
Tuy phép gán cho cả đoạn $[l; r]$ có thể sẽ thừa so với đoạn $[a; b]$ nhưng ta đang thao tác với hàm $\min$/$\max$ nên điều này không làm ảnh hưởng kết quả.
:::

Đường thẳng $tr_k$ ban đầu vẫn còn có thể đóng góp vào min-line ở một trong hai khoảng $[l; mid]$ hoặc $(mid; r]$. Do đó, ta đưa đường thẳng này xuống một trong hai cây con. Việc chọn cây con tương tự trường hợp 1 nhưng bây giờ hàm $f$ và $tr_k$ đổi vai trò cho nhau.

![slope comparison 2 no bg](/algo/data-structures/lichao/lichao6.png)

#### Xử lý tổng quát

Trên thực tế, ta có thể giảm số trường hợp cần xử lý bằng một trong hai cách:

- Quy ước $f(mid) > tr_k(mid)$.
- Quy ước hệ số góc của $f$ lớn hơn hoặc bằng $tr_k$.

Nếu điều kiện quy ước không được thỏa, ta chỉ việc tráo đổi hai đường thẳng $f, tr_k$ cho nhau. Trong bài viết này, mình sẽ sử dụng cách làm đầu tiên.

Ngoài ra, để tránh phải xử lý nửa khoảng khi chia để trị, nếu ta chỉ quan tâm các vị trí $x$ là số nguyên, ta sẽ chia khoảng $[l; r]$ thành $[l; mid]$ và $[mid + 1; r]$ thay vì $[l; mid]$ và $(mid; r]$ như trên, với $mid = \lfloor \frac{l + r}{2} \rfloor$.

Tương tự, nếu ta quan tâm cả những vị trí $x$ là số thực, ta có thể chia đoạn $[l; r]$ thành $[l; mid]$ và $[mid + \epsilon; r]$ với $mid = \frac{l + r}{2}$ và $\epsilon$ là hằng số nhỏ khoảng $10$ đến $100$ lần sai số tổi thiểu (thường là $10^{-6}$ hoặc $10^{-9}$).

:::info
Như vậy, ta có thể hiểu rằng $tr_k(x)$ là đường thẳng tối ưu cho vị trí $mid$, nếu chưa tính các đường thẳng được lưu tại các nút tổ tiên của $k$.
:::

#### Trường hợp cơ sở (base case)

Quá trình chia để trị sẽ kết thúc khi ta đi xuống đến nút lá, khi đó, ta chỉ việc so sánh hai hàm $f$ và $tr_k$ xem hàm nào tốt hơn cho vị trí tương ứng rồi gán $tr_k$ cho hàm tối ưu.

### Thao tác loại $2$: Tìm hàm tối ưu cho điểm $t$

Tương tự với Segment tree, để lấy dữ liệu cho vị trí $t$, ta kết hợp dữ liệu ở các nút quản lý $t$. Nói cách khác, ta sẽ thực hiện di chuyển từ gốc của Li-chao tree xuống nút lá tương ứng với vị trí $t$ và lấy đường thẳng tối ưu nhất trên đường đi.

## Cài đặt

### Li-chao tree cho tập đường thẳng

Để thuận tiện cho việc cài đặt, ta cần tạo ra một `struct` biểu diễn đường thẳng.

```cpp=
struct line {
    ll a, b;

    line() : a(0), b(0) {}
    line (ll a, ll b) : a(a), b(b) {}

    ll calc (ll x) { return a * x + b; }

    ll slope() { return a; }
};
```

Ban đầu, tất cả các nút của Li-chao tree chứa đường thẳng $0x + \infty$ (tức là đường thẳng song song với trục $Ox$ nằm rất cao). Ở đây mình chọn vô cực là `LLONG_MAX`.

```cpp=
struct liChao {
    vector<line> tr;

    liChao() {}
    liChao (int sz) : tr(4 * sz, line(0, LLONG_MAX)) {}

    void update (line f, int k, int l, int r) {
        /*
            f: đường thẳng cần cập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        if (l == r) {
            tr[k] = (f.calc(l) < tr[k].calc(l) ? f : tr[k]);
            return;
        }
        int mid = (l + r) >> 1;
        
        // để giảm số trường hợp cần xử lý, giả sử tr[k] tốt hơn f cho vị trí mid
        if (f.calc(mid) < tr[k].calc(mid)) swap(tr[k], f);
        
        // trường hợp 1.1, đường thẳng f được đưa xuống cây con trái
        if (f.slope() > tr[k].slope())
            update(f, 2 * k, l, mid); 
        
        // trường hợp 1.2, đường thẳng f được đưa xuống cây con phải
        if (f.slope() < tr[k].slope())
            update(f, 2 * k + 1, mid + 1, r);
    }

    ll query (int pos, int k, int l, int r) {
        /*
            pos: vị trí được truy vấn
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        ll cur = tr[k].calc(pos);
        int mid = (l + r) >> 1;
        
        // thực hiện di chuyển từ nút gốc xuống nút lá tương ứng, tương tự như Segment tree
        if (l == r) return cur;
        if (pos <= mid)
            return min(cur, query(pos, 2 * k, l, mid));
        else return min(cur, query(pos, 2 * k + 1, mid + 1, r));
    }
};
```

:::success
Đánh giá độ phức tạp:
- Thời gian: $O(\log M)$ cho mỗi thao tác.
- Bộ nhớ: $O(M)$ cho cả Li-chao tree.
:::

### Li-chao tree tổng quát

Khi cài đặt Li-chao tree cho các hàm không phải phương trình đường thẳng, ta không thể chọn cây con để đưa hàm $f$ xuống bằng cách so sánh hệ số góc nữa. Lúc này, ta sử dụng điều kiện tổng quát:

- Nếu $f(l) < tr_k(l)$ thì hàm $f$ sẽ được đưa xuống cây con trái.
- Nếu $f(r) < tr_k(r)$ thì hàm $f$ sẽ được đưa xuống cây con phải.

```cpp!
void update (line f, int k, int l, int r) {
    if (l == r) {
        tr[k] = (f.calc(l) < tr[k].calc(l) ? f : tr[k]);
        return;
    }
    int mid = (l + r) >> 1;
    if (f.calc(mid) < tr[k].calc(mid)) swap(tr[k], f);
    if (f.calc(l) < tr[k].calc(l))
        update(f, 2 * k, l, mid);
    if (f.calc(r) < tr[k].calc(r))
        update(f, 2 * k + 1, mid + 1, r);
}
```

Các hàm còn lại vẫn sẽ được cài đặt như cũ. Lưu ý rằng, khi cài đặt như thế này, chúng ta cần để ý để hằng số cho việc tính toán các hàm, vì chúng được gọi khá nhiều.

## Mở rộng: Các tối ưu và biến thể Li-chao tree

### Tối ưu bộ nhớ

Đối với Li-chao tree kinh điển, ta có thể tối ưu bộ nhớ một chút bằng cách định nghĩa lại cách chia để trị. Cụ thể, với một nút quản lý đoạn $[l; r]$:

- Nút con bên trái quản lý đoạn $[l; mid - 1]$.
- Nút con bên phải quản lý đoạn $[mid + 1; r]$.

Với cách làm này, không khó để chứng minh rằng ta chỉ cần đúng $M$ nút cho Li-chao tree và việc đánh số cũng trở nên dễ dàng hơn khi ta có thể dùng $mid$ là chỉ số cho các nút.

:::spoiler Code tham khảo
```cpp=
struct liChao {
    vector<line> tr;

    liChao() {}
    liChao (int sz) : tr(sz + 1, line(0, LLONG_MAX)) {}

    void update (line f, int l, int r) {
        /*
            f: đường thẳng cần cập nhật
            mid: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        if (l > r) return;
        int mid = (l + r) >> 1;
        if (l == r) {
            tr[mid] = (f.calc(l) < tr[mid].calc(l) ? f : tr[mid]);
            return;
        }
        
        // việc cập nhật được thực hiện tương tự Li-chao tree cơ bản
        if (f.calc(mid) < tr[mid].calc(mid)) swap(tr[mid], f);
        if (f.slope() > tr[mid].slope())
            update(f, l, mid - 1); // trường hợp 1.1
        if (f.slope() < tr[mid].slope())
            update(f, mid + 1, r); // trường hợp 1.2
    }

    ll query (int p, int l, int r) {
        /*
            p: vị trí được truy vấn
            mid: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        int mid = (l + r) >> 1;
        ll cur = tr[mid].calc(p);
        if (p == mid) return cur;
        if (p < mid) return min(query(p, l, mid - 1), cur);
        if (p > mid) return min(query(p, mid + 1, r), cur);
    }
};
```

Lưu ý, với cách cài đặt này, một base case mới sẽ phát sinh đó là hàm `update` sẽ được gọi với $l > r$. Ví dụ, khi được gọi với đoạn $[1; 2]$, hàm sẽ chia thành đoạn $[1; 0]$ và $[2; 2]$.

:::

Hiệu quả của tối ưu có thể được thể hiện qua bài Building Bridges (CEOI 2017)[^[4]^](https://oj.uz/problem/view/CEOI17_building) như sau:

|  Solution   | Thời gian chạy |  Bộ nhớ  |
|:-----------:|:--------------:|:--------:|
| Chưa tối ưu |  70 mili giây  | 66540 kB |
|  Đã tối ưu  |  56 mili giây  | 19564 kB |

Các bạn có thể tham khảo code của mình [tại đây](https://oj.uz/submission/1024168).

### Li-chao tree cho tập đoạn thẳng

Ta có thể biến đổi Li-chao tree để xử lý tập đoạn thẳng với $2$ thao tác như sau:

1. Cho bốn số nguyên $L, R, a, b$, thêm đoạn thẳng $f(x) = ax + b$ với $x \in [L; R]$ vào tập đoạn thẳng.
2. Cho một số nguyên $t$ (với $1 \leq t \leq M$), gọi $S$ là tập đường thẳng hiện tại, tính $\min_{f \in S} f(t)$.

Bài toán này khác bài toán gốc ở chỗ, thay vì phải xử lý đường thẳng, ta phải xử lý đoạn thẳng, tức là:

$$
f(x) =
\begin{cases}
\infty & x \notin [L; R] \\
ax + b & x \in [L; R]
\end{cases}
$$

Tập đoạn thẳng bấy giờ không còn là nửa trên của bao lồi nữa. Tuy nhiên, với truy vấn loại $1$, ta có thể chia đoạn $[L; R]$ thành $O(\log M)$ đoạn (theo ý tưởng của Segment tree) rồi thực hiện thao tác cập nhật của Li-chao tree bắt đầu từ các nút tương ứng. Tổng độ phức tạp thời gian là $O(\log^2 M)$.

:::spoiler Lưu ý
Đối với biến thể Li-chao tree này, ta không thể sử dụng tối ưu bộ nhớ.
:::

Truy vấn loại $2$ được xử lý bình thường trong $O(\log M)$.

:::spoiler Code tham khảo
```cpp=
struct liChao {
    vector<line> tr;

    liChao() {}
    liChao (int sz) : tr(4 * sz, line(0, LLONG_MAX)) {}

    void addLine (line f, int k, int l, int r) {
        /*
            f: đường thẳng cần cập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        if (l == r) {
            tr[k] = (f.calc(l) < tr[k].calc(l) ? f : tr[k]);
            return;
        }
        int mid = (l + r) >> 1;
        if (f.calc(mid) < tr[k].calc(mid)) swap(tr[k], f);
        if (f.slope() > tr[k].slope())
            addLine(f, 2 * k, l, mid); // trường hợp 1.1
        if (f.slope() < tr[k].slope())
            addLine(f, 2 * k + 1, mid + 1, r); // trường hợp 1.2
    }

    void update (int a, int b, line f, int k, int l, int r) {
        /*
            a..b: khoảng cần cập nhật
            f: đường thẳng cần nhập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        if (b < l || r < a) return;
        
        // thực hiện thao tác cập nhật của Li-chao tree cơ bản
        // khi khoảng mà nút quản lý nằm gọn trong khoảng cần cập nhật
        if (a <= l && r <= b) return addLine(f, k, l, r), void();
        
        // chia để trị tương tự Segment tree
        int mid = (l + r) >> 1;
        update(a, b, f, 2 * k, l, mid);
        update(a, b, f, 2 * k + 1, mid + 1, r);
    }

    ll query (int pos, int k, int l, int r) {
        /*
            pos: vị trí được truy vấn
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        ll cur = tr[k].calc(pos);
        int mid = (l + r) >> 1;
        if (l == r) return cur;
        if (pos <= mid)
            return min(cur, query(pos, 2 * k, l, mid));
        else return min(cur, query(pos, 2 * k + 1, mid + 1, r));
    }
};
```
:::

### Li-chao tree trên mảng thưa (Sparse Li-chao tree)

Tương tự Sparse Segment tree[^[5]^](https://cp-algorithms.com/data_structures/segment_tree.html#dynamic-segment-tree), chúng ta cũng có thể sử dụng Li-chao tree trên mảng thưa sử dụng con trỏ. Cụ thể, khi $M$ quá lớn (ví dụ: $-10^9 \leq M \leq 10^9$), việc sử dụng bộ nhớ $O(M)$ là không thể. Khi đó, ta chỉ tạo các nút cho Li-chao mỗi khi cần cập nhật một nút chưa được tạo.

Có thể thấy, mỗi thao tác cập nhật sẽ thêm vào $O(\log M)$ nút mới. Do đó, độ phức tạp bộ nhớ của Sparse Li-chao tree sau $Q$ thao tác cập nhật là $O(Q \log M)$.

Thao tác truy vấn $\min$/$\max$ thực hiện như bình thường, cần lưu ý tránh truy cập vào con trỏ `nullptr`.

:::spoiler Code tham khảo
```cpp=
const int M = 1e9;

struct node {
    line tr;
    node *lpt, *rpt;

    node() : tr(0, LLONG_MAX), lpt(nullptr), rpt(nullptr) {}

    int divi (int a, int b) { // phép chia làm tròn xuống
        return a / b - ((a ^ b) < 0 && a % b);
    }

    void update (line f, int l = -M, int r = M) {
        /*
            f: đường thẳng cần cập nhật
            l..r: khoảng mà nút quản lý
        */
        if (l == r) {
            tr = (f.calc(l) < tr.calc(l) ? f : tr);
            return;
        }
        int mid = divi(l + r, 2);
        if (f.calc(mid) < tr.calc(mid)) swap(tr, f);
        if (f.slope() > tr.slope()) {
            if (lpt == nullptr) lpt = new node(); // khởi tạo bộ nhớ cho cây con trái
            lpt->update(f, l, mid); // trường hợp 1.1
        }
        if (f.slope() < tr.slope()) {
            if (rpt == nullptr) rpt = new node(); // khởi tạo bộ nhớ cho cây con phải
            rpt->update(f, mid + 1, r); // trường hợp 1.2
        }
    }

    ll query (int pos, int l = -M, int r = M) {
        /*
            pos: vị trí được truy vấn
            l..r: khoảng mà nút quản lý
        */
        ll cur = tr.calc(pos);
        int mid = divi(l + r, 2);
        if (l == r) return cur;
        
        // lưu ý: chỉ được di chuyển xuống cây con khi nó được khởi tạo bộ nhớ sẵn
        if (pos <= mid)
            return min(cur, lpt == nullptr ? LLONG_MAX : lpt->query(pos, l, mid));
        else
            return min(cur, rpt == nullptr ? LLONG_MAX : rpt->query(pos, mid + 1, r));
    }
};
```

Lưu ý, khi tính $mid$ cho số âm, ta cần viết lại hàm chia làm tròn xuống.
:::

### Tìm hàm tối ưu thứ $k$ trên Li-chao tree

Ở những phần trên, chúng ta đã tìm hiểu cách tìm đường thẳng tối ưu nhất cho một vị trí bất kỳ. Với Li-chao tree, ta còn có thể tìm đường thẳng tối ưu thứ $k$. Cụ thể hơn, ta có thể biến đổi Li-chao tree để hỗ trợ hai loại thao tác sau:

1. Thêm một hàm $f(x) = ax + b$ vào tập đường thẳng.
2. Cho một số nguyên $t$ (với $1 \leq t \leq M$) và $k$ (với $k$ không quá kích thước tập đường thẳng). Gọi $S$ là tập đường thẳng hiện tại, tìm phần tử thứ $k$ trong dãy $C = [f(t) | f \in S]$ sau khi đã sắp xếp tăng dần.

#### Ý tưởng

Thoạt đầu, ta sẽ nghĩ đến cách lưu $k$ đường thẳng tối ưu nhất ở mỗi nút. Khi số đường thẳng được lưu tại một nút vượt quá $k$, ta sẽ lấy đường thẳng tệ nhất đưa xuống một trong hai cây con.

Tuy nhiên, sẽ có một số trường hợp đường thẳng tệ nhất này còn phải đưa xuống cả hai cây con, ví dụ, với trường hợp sau:

![k-th optimal line no bg](/algo/data-structures/lichao/lichao8.png)
Như vậy, phải lưu bao nhiêu đường thẳng mới đủ?

Ta biết rằng, khi một đường thẳng $f(x)$ nằm dưới $g(x)$ tại $x = mid$, nó sẽ nằm dưới $g(x)$ trong khoảng $(-\infty; mid]$ hoặc $[mid; \infty)$.

Xét nút đang bị thừa một đường thẳng, gọi $a$ là số đường thẳng nằm dưới đường thẳng tệ nhất trong khoảng $(-\infty; mid]$, $b$ là số đường thẳng nằm dưới đường thẳng tệ nhất trong khoảng $[mid; \infty)$. Dễ thấy, để đường thẳng tệ nhất này không được đưa xuống cây con trái thì $a \geq k$. Tương tự, để đường thẳng tệ nhất không được đưa xuống cây con phải thì $b \geq k$.

Ta muốn đường thẳng tệ nhất này chỉ được đưa xuống **tối đa một nút con** giống như cơ chế hoạt động của Li-chao tree truyền thống. Do đó, một trong hai giá trị $a$ hoặc $b$ phải $\geq k$, tức bài toán của chúng ta bây giờ là cực tiểu hóa $a + b$ sao cho $\max(a, b) \geq k$.

Không khó để chứng minh câu trả lời là $2k - 1$.

#### Thuật toán

Như vậy, với mỗi nút của Li-chao tree, ta sẽ lưu một danh sách giữ lại $2k - 1$ đường thẳng tốt nhất (có giá trị $f(mid)$ bé nhất) được đưa vào. Khi đưa một đường thẳng vào nút, nếu số lượng nút trong danh sách lên đến $2k$, ta chọn đường thẳng tệ nhất (có giá trị $f(mid)$ lớn nhất) rồi đưa xuống một trong hai cây con:

- Trong $2k - 1$ đường thẳng còn lại, nếu số đường thẳng có hệ số góc lớn hơn đường thẳng tệ nhất là nhỏ hơn $k$, ta đưa đường thẳng tệ nhất xuống cây con trái.
- Trong $2k - 1$ đường thẳng còn lại, nếu số đường thẳng có hệ số góc bé hơn đường thẳng tệ nhất là nhỏ hơn $k$, ta đưa đường thẳng tệ nhất xuống cây con phải.

Để lấy đường thẳng tối ưu thứ $k$ tại vị trí $t$, ta đi từ gốc xuống nút lá tương ứng của vị trí $t$ và duy trì một danh sách chứa $k$ đường thẳng tốt nhất.

Như vậy, độ phức tạp thời gian cho mỗi thao tác cập nhật và truy vấn là $O(k \log M)$. Độ phức tạp bộ nhớ là $O(Mk + |S|)$ với $|S|$ là số đường thẳng được đưa vào.

#### Cài đặt

Để thuận tiện cho việc cài đặt, mình sử dụng hàm `nth_element` giúp sắp xếp lại mảng sao cho phần tử ở vị trí thứ $n$ sẽ nằm đúng vị trí của nó nếu mảng được sắp xếp, những phần tử còn lại được xếp ngẫu nhiên. Hàm này tốn độ phức tạp gần tuyến tính.

Lưu ý, với cách cài đặt này, danh sách các đường thẳng trong một nút sẽ không được sắp xếp theo thứ tự tối ưu.

:::spoiler Code tham khảo
```cpp=
struct liChao {
    vector<vector<line>> tr;
    int mkth;

    liChao (int sz, int k) : tr(4 * sz), mkth(k) {}

    void update (line cur, int k, int l, int r) {
        /*
            cur: đường thẳng cần cập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        tr[k].push_back(cur);
        if (tr[k].size() <= 2 * mkth - 1) return;

        // chèn đường thẳng mới vào và đưa đường thẳng tệ nhất ra ngoài
        int mid = (l + r) >> 1;
        nth_element(tr[k].begin(), tr[k].end() - 1, tr[k].end(),
                    [&] (line a, line b) {return a.calc(mid) < b.calc(mid);}); // đưa đường thẳng tệ nhất ra cuối vector
        line worst = tr[k].back();
        tr[k].pop_back();

        if (l == r) return;

        // đếm số đường thẳng được lưu ở nút hiện tại mà tốt hơn đường thẳng tệ nhất
        // trong khoảng [l; mid], bằng cách so sánh hệ số góc của chúng
        int dominateLeft = 0;
        for (line it : tr[k])
            dominateLeft += it.slope() > worst.slope();

        // đường thẳng tệ nhất được đưa xuống cây con có
        // số đường thẳng tốt hơn nó ít hơn "mkth"
        if (dominateLeft < mkth) update(worst, 2 * k, l, mid);
        else update(worst, 2 * k + 1, mid + 1, r);
    }

    void push (vector<ll> &cand, ll val, int kth) {
        // thêm một giá trị vào vector và giữ lại k giá trị tốt nhất
        cand.push_back(val);
        if (cand.size() > kth) {
            nth_element(cand.begin(), cand.end() - 1, cand.end());
            cand.pop_back();
        }
    }

    void walk (vector<ll> &cand, int pos, int kth, int k, int l, int r) {
        /*
            cand: vector để duy trì k giá trị tốt nhất
            pos: vị trí được truy vấn
            kth: thứ hạng của đường thẳng cần tìm
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        for (line cur : tr[k]) push(cand, cur.calc(pos), kth);
        if (l == r) return;

        int mid = (l + r) >> 1;
        if (pos <= mid)
            walk(cand, pos, kth, 2 * k, l, mid);
        else walk(cand, pos, kth, 2 * k + 1, mid + 1, r);
    }

    ll query (int pos, int kth, int k, int l, int r) {
        /*
            pos: vị trí được truy vấn
            kth: thứ hạng của đường thẳng cần tìm
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        vector<ll> cand;
        walk(cand, pos, kth, k, l, r);
        nth_element(cand.begin(), cand.end() - 1, cand.end());
        return cand.back();
    }
};
```
:::

### Lazy propagation trên Li-chao tree (Extended Li-chao tree)

Tương tự với Segment tree, chúng ta hoàn toàn có thể áp dụng Lazy propagation với Li-chao tree, tạo ra những cấu trúc dữ liệu mạnh có thể hỗ trợ những thao tác mà chỉ có Extended Li-chao tree mới làm được.

#### Bài toán 1

Cho một mảng $A$ kích thước $N$ và $Q$ truy vấn online thuộc một trong ba dạng:

1. **Chèn đoạn thẳng**: Cho bốn số nguyên $l, r, a, b$, gán $A[i] = \min(A[i], a \cdot i + b)$ với mọi $i \in [l; r]$.
2. **Tăng đoạn theo dạng bậc thang**: Cho bốn số nguyên $l, r, a, b$, tăng $A[i]$ lên $a \cdot i + b$ đơn vị, với mọi $i \in [l; r]$.
3. **Truy vấn điểm**: Cho số nguyên $i$, trả về $A[i]$.

Giới hạn:

- $1 \leq N, Q \leq 10^5$.
- $1 \leq A[i], a, b \leq 10^8$.

Với thao tác loại $1$ và $3$, chúng ta có thể cài đặt tương tự Li-chao tree quản lý đoạn thẳng như trên. Bây giờ, chúng ta sẽ tìm cách xử lý thao tác loại $2$ với Li-chao tree.

#### Tính chất của phép tăng đoạn theo dạng bậc thang

Ta đã biết, một thao tác tăng theo dạng bậc thang có thể biểu diễn dưới dạng một phương trình đường thẳng, tạm gọi là *hàm cập nhật*. Hơn nữa, tổng của hai phương trình đường thẳng, cũng là một phương trình đường thẳng. Cụ thể, với hàm $f(x) = a_1x + b_1$ và $g(x) = a_2x + b_2$, tổng của chúng là hàm $h(x) = (a_1 + a_2)x + (b_1 + b_2)$.

![line add no bg](/algo/data-structures/lichao/lichao9.png)

Như vậy, ta có thể tưởng tượng một thao tác tăng đoạn $[l; r]$ theo dạng bậc thang lên một đoạn thẳng chính là "bẻ gãy" đoạn thẳng này tại điểm $l, r$ rồi thay đoạn ở giữa thành tổng của nó và hàm cập nhật.

![line add 2 no bg](/algo/data-structures/lichao/lichao10.png)

#### Ý tưởng

Với Li-chao tree truyền thống, khi chèn một đường thẳng, ta có thể gán nó cho một đoạn rộng hơn đoạn mà đường này thật sự đóng góp và min-line. Điều này không phải là vấn đề với hàm $\min, \max$.

Tuy nhiên, khi làm việc với phép cộng, ta chỉ được phép gây ảnh hưởng lên đúng đoạn $[l; r]$ mà nó được phép gây ảnh hưởng. Để giải quyết vấn đề này, ta sử dụng lazy propagation trên Li-chao tree.

Tương tự lazy propagation trên Segment tree, với mỗi nút, ta lưu lại hàm cập nhật $\text{lazy}_k(x)$, đại diện cho cả đoạn $[l; r]$ mà nút $k$ quản lý đang được cộng thêm hàm $\text{lazy}_k(x)$. Mỗi thao tác loại $2$ tương đương với việc cộng thêm hàm cập nhật cho $O(\log N)$ nút. Các giá trị $\text{lazy}_k(x)$ chỉ được đưa xuống cây con khi ta cần xử lý đến.

Cần lưu ý, khi đi từ gốc xuống để tìm các nút cần cập nhật $\text{lazy}_k(x)$ đối với truy vấn loại $2$, ta cần đẩy tất cả các đường thẳng còn đang chứa ở các nút xuống bằng một thao tác chèn đoạn thẳng (trong code tham khảo gọi là thao tác `pushLine`). Điều này sẽ đảm bảo tất cả các đường thẳng nằm trong đoạn cần được tăng sẽ được tăng.

Bên cạnh đó, cần đảm bảo rằng khi thực hiện thao tác loại $1$ trên nút nào thì nút đó không chịu ảnh hưởng của bất kỳ giá trị lazy nào.

:::spoiler Code tham khảo
```cpp=
struct line {
    ll a, b;

    line() : a(0), b(0) {}
    line (ll a, ll b) : a(a), b(b) {}

    ll calc (ll x) { return (b == LLONG_MAX ? LLONG_MAX : a * x + b); }
    ll slope() { return a; }

    ll add (ll a, ll b) { // phép cộng chống tràn số
        return (max(a, b) == LLONG_MAX ? LLONG_MAX : a + b);
    }

    void operator += (line o) {
        a = add(a, o.a), b = add(b, o.b);
    }
};

struct liChao {
    vector<line> tr, lazy;

    liChao() {}
    liChao (int sz) : tr(4 * sz, line(0, LLONG_MAX)), lazy(4 * sz) {}

    void apply (int k, line f) {
        tr[k] += f, lazy[k] += f;
    }

    void pushDown (int k) {
        // đẩy "hàm cập nhật" theo cập nhật tăng đoạn xuống các cây con
        // để tránh ảnh hưởng của cập nhật chèn đường thẳng
        if (!lazy[k].a && !lazy[k].b) return;
        apply(2 * k, lazy[k]), apply(2 * k + 1, lazy[k]);
        lazy[k] = line(0, 0);
    }

    void insertLine (line f, int k, int l, int r) {
        /*
            f: đường thẳng cần cập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        
        // thực hiện cập nhật đường thẳng như Li-chao tree cơ bản, thêm
        // thao tác "pushDown" để không cập nhật đè lên các cập nhật tăng đoạn
        if (l == r) {
            tr[k] = (f.calc(l) < tr[k].calc(l) ? f : tr[k]);
            return;
        }
        pushDown(k);
        int mid = (l + r) >> 1;
        if (f.calc(mid) < tr[k].calc(mid)) swap(tr[k], f);
        if (f.slope() > tr[k].slope())
            insertLine(f, 2 * k, l, mid);
        else if (f.slope() < tr[k].slope())
            insertLine(f, 2 * k + 1, mid + 1, r);
    }

    void pushLine (int k, int l, int r) {
        // đẩy hàm của Li-chao tree xuống các cây con để tránh
        // ảnh hưởng của cập nhật tăng đoạn
        int mid = (l + r) >> 1;
        if (tr[k].b != LLONG_MAX) {
            insertLine(tr[k], 2 * k, l, mid);
            insertLine(tr[k], 2 * k + 1, mid + 1, r);
            tr[k] = line(0, LLONG_MAX);
        }
    }

    void updateInsert (int a, int b, line f, int k, int l, int r) {
        /*
            a..b: khoảng cần cập nhật
            f: đường thẳng cần cập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        
        // thực hiện cập nhật đoạn thẳng như Li-chao tree cơ bản, thêm
        // thao tác "pushDown" để không cập nhật đè lên các cập nhật tăng đoạn
        if (b < l || r < a) return;
        if (a <= l && r <= b)
            return insertLine(f, k, l, r), void();
        pushDown(k);
        int mid = (l + r) >> 1;
        updateInsert(a, b, f, 2 * k, l, mid);
        updateInsert(a, b, f, 2 * k + 1, mid + 1, r);
    }

    void updateIncrease (int a, int b, line f, int k, int l, int r) {
        /*
            a..b: khoảng cần cập nhật
            f: đường thẳng cần cập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        
        // thực hiện cập nhật đoạn tương tự Segment tree, thêm thao tác
        // "pushDown" và "pushLine" để không cập nhật đè lên các cập nhật trước đó
        if (b < l || r < a) return;
        if (a <= l && r <= b)
            return apply(k, f), void();
        pushDown(k), pushLine(k, l, r);
        int mid = (l + r) >> 1;
        updateIncrease(a, b, f, 2 * k, l, mid);
        updateIncrease(a, b, f, 2 * k + 1, mid + 1, r);
    }

    ll query (int pos, int k, int l, int r) {
        /*
            pos: vị trí được truy vấn
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        ll cur = tr[k].calc(pos);
        int mid = (l + r) >> 1;
        if (l == r) return cur;
        pushDown(k);
        if (pos <= mid)
            return min(cur, query(pos, 2 * k, l, mid));
        else return min(cur, query(pos, 2 * k + 1, mid + 1, r));
    }
};
```
:::

Như vậy, ta có thể xử lý các thao tác trong độ phức tạp lần lượt là $O(\log^2 N)$, $O(\log^2 N)$ và $O(\log N)$.

#### Bài toán 2

Cho một mảng $A$ kích thước $N$ và $Q$ truy vấn online thuộc một trong ba dạng:

1. **Chèn đoạn thẳng**: Cho bốn số nguyên $l, r, a, b$, gán $A[i] = \min(A[i], a \cdot i + b)$ với mọi $i \in [l; r]$.
2. **Tăng đoạn**: Cho ba số nguyên $l, r, c$, tăng $A[i]$ lên $c$ đơn vị, với mọi $i \in [l; r]$.
3. **Truy vấn đoạn**: Cho hai số nguyên $l, r$, tính $\min_{i = l}^{r} A[i]$.

#### Ý tưởng

Kết hợp với ý tưởng lazy propagation như trên, bây giờ với mỗi nút, ta lưu thêm một giá trị $\text{low}_k = \min_{i = l}^{r} A[i]$ với $[l; r]$ là đoạn mà nút $k$ quản lý.

Lưu ý, với cách làm này, ta không thể thực hiện thao tác tăng đoạn thao dạng bậc thang, vì việc tăng như thế sẽ làm thay đổi mối quan hệ lớn bé giữa các giá trị trong đoạn được tăng. Tuy nhiên, khi đoạn được tăng cho cùng một giá trị, ta chỉ việc tăng $\text{low}_k$ và hệ số tự do của các đoạn thẳng nằm trong đoạn được cập nhật cho cùng một giá trị.

## Ứng dụng: Quy hoạch động

*Đối với mỗi bài toán trong phần ứng dụng, mình khuyên các bạn đọc giả nên tự suy nghĩ lời giải cho bài toán trước khi đọc tiếp*

Bên cạnh các bài toán thuần cấu trúc dữ liệu, Li-chao tree còn có một ứng dụng rất quan trọng đó là cải tiến một số thuật toán Quy hoạch động.

Thông thường, Li-chao tree có thể cải tiến các bài toán QHĐ có công thức truy hồi có dạng:

$$
dp_i = \min_{j = 1}^{i - 1} a_j \cdot b_i + c_j
$$

Trong đó, $a_i, b_i, c_i$ là các giá trị được xác định từ $dp_i$ và các hệ số liên quan.

Để dễ hình dung hơn, chúng ta sẽ tìm hiểu các ví dụ Quy hoạch động kết hợp Li-chao tree sau.

### CEOI 2017: Building Bridges

[Link đề bài](https://oj.uz/problem/view/CEOI17_building)

Cho $n$ cột đá có độ cao $h_1, h_2, \cdots, h_n$ và chi phí tháo dỡ là $w_1, w_2, \cdots, w_n$. Chọn ra một số cột đá để xây dựng cầu với chi phí là tổng bình phương của chênh lệch độ cao hai cột đá liên tiếp được chọn, cộng cho tổng chi phí tháo dỡ các cột đá không được chọn.

![bridge visualization no bg](/algo/data-structures/lichao/lichao11.png)

Nói cách khác, gọi $S$ là dãy các vị trí được chọn, ta có công thức tính chi phí là:

$$
\sum_{i=2}^{|S|} (h_{S_i} - h_{S_{i-1}})^2 + \sum_{j \notin S} w_j
$$

Tìm cách chọn để cực tiểu hóa chi phí xây dựng cầu, đảm bảo cột đầu tiên và cuối cùng luôn được chọn.

Giới hạn:

- $2 \leq n \leq 10^5$.
- $0 \leq h_i, |w_i| \leq 10^6$.

#### Quy hoạch động $O(n^2)$

Với kiến thức Quy hoạch động cơ bản, ta có thể xây dựng thuật toán $O(n^2)$ với $dp_i$ là chi phí xây dựng cầu nhỏ nhất, trong các phương án bắt đầu từ cột đầu tiên, và kết thúc ở cột thứ $i$. Để tính $dp_i$, ta thử tất cả các vị trí $j$ là cột đá được chọn nằm ngay trước $i$, sau đó cộng thêm $(h_i - h_j)^2$ và chi phí để tháo dỡ các cột đá từ vị trí $j + 1$ đến $i - 1$. Công thức truy hồi như sau:

$$
dp_i = \min_{j=1}^{i-1} (dp_j + (h_i - h_j)^2 + \sum_{k = j + 1}^{i-1} w_k)
$$

Thuật toán Quy hoạch động như trên sẽ có độ phức tạp là $O(n^2)$ -- chưa đủ để giải quyết bài toán.

#### Áp dụng Li-chao tree

Với công thức truy hồi $dp_j + (h_i - h_j)^2 + \sum_{k = j + 1}^{i-1} w_k$, ta có thể biến đổi thành:

$$
dp_j + h_i^2 - 2h_ih_j + h_j^2 + pre_{i-1} - pre_j
$$

với $pre_i = \sum_{j = 1}^{i} w_j$.

Ta có thể nhóm biểu thức trên thành $3$ nhóm:

$$
\underbrace{-2h_j \cdot h_i}_\text{P1} + \underbrace{dp_j + h_j^2 - pre_j}_\text{P2} + \underbrace{h_i^2 + pre_{i-1}}_\text{P3}
$$

Nhóm thứ ba chỉ phụ thuộc vào $i$ nên nhiệm vụ còn lại là tìm $j$ để cực tiểu hóa $2$ nhóm đầu tiên. Có thể thấy, $2$ nhóm này có dạng phương trình đường thẳng $ax + b$ với $a = -2h_j$ và $b = dp_j + h_j^2 - pre_j$.

Đến đây, ta định nghĩa phương trình đường thẳng $f_j(x) = -2h_j \cdot x + dp_j + h_j^2 - pre_j$. Như vậy, công thức truy hồi được biến đổi thành:

$$
dp_i = \min_{j=1}^{i-1} f_j(h_i) + (h_i^2 + pre_{i-1})
$$

Ta đã đưa công thức truy hồi thành dạng bài quen thuộc của Li-chao tree: Để tính $dp_i$, ta tìm đường thẳng có giá trị bé nhất tại điểm $h_i$ cộng thêm $h_i^2 + pre_{i-1}$. Sau đó, thêm đường thẳng $f_i(x)$ vào tập đường thẳng.

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tt;
 
#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())
 
struct line {
    ll a, b;
 
    line() : a(0), b(0) {}
    line (ll a, ll b) : a(a), b(b) {}
 
    ll calc (ll x) { return a * x + b; }
 
    ll slope() { return a; }
};
 
struct liChao {
    vector<line> tr;
 
    liChao() {}
    liChao (int sz) : tr(sz + 1, line(0, LLONG_MAX)) {}
 
    void update (line f, int l, int r) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        if (l == r) {
            tr[mid] = (f.calc(l) < tr[mid].calc(l) ? f : tr[mid]);
            return;
        }
        if (f.calc(mid) < tr[mid].calc(mid)) swap(tr[mid], f);
        if (f.slope() > tr[mid].slope())
            update(f, l, mid - 1);
        if (f.slope() < tr[mid].slope())
            update(f, mid + 1, r);
    }
 
    ll query (int p, int l, int r) {
        int mid = (l + r) >> 1;
        ll cur = tr[mid].calc(p);
        if (p == mid) return cur;
        if (p < mid) return min(query(p, l, mid - 1), cur);
        if (p > mid) return min(query(p, mid + 1, r), cur);
    }
};
 
const int M = 1e6 + 1;
ll dp[M], h[M], w[M];
 
ll coef1 (int k) {
    return -2 * h[k];
}
 
ll coef2 (int k) {
    return dp[k] + h[k] * h[k] - w[k];
}
 
ll coef3 (int k) {
    return h[k] * h[k] + w[k - 1];
}
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i] += w[i - 1];
    }
 
    liChao tree(M);
    tree.update(line(coef1(1), coef2(1)), 0, M);
 
    for (int i = 2; i <= n; i++) {
        dp[i] = tree.query(h[i], 0, M) + coef3(i);
        tree.update(line(coef1(i), coef2(i)), 0, M);
    }
    cout << dp[n];
 
    return 0;
}
```
:::

Như vậy, ta đã giải bài toán trong $O(n \log h_{\max})$ và bộ nhớ $O(n + h_{\max})$.

### Codeforces Round 344: Product Sum

[Link đề bài](https://codeforces.com/problemset/problem/631/E)

Cho mảng $a$ gồm $n$ phần tử được đánh số từ $1$. Thực hiện đúng một thao tác lấy một phần tử rồi đặt vào một vị trí bất kỳ (có thể là vị trí ban đầu). Đánh số lại các phần tử. Tìm cách thực hiện thao tác để cực đại hóa giá trị:

$$
c = \sum_{i=1}^{n} a_i \cdot i
$$

Giới hạn:

- $1 \leq n \leq 2 \cdot 10^5$.
- $0 \leq |a_i| \leq 10^9$.

#### Ý tưởng

Gọi vị trí của phần tử được chọn là $j$ và vị trí mới mà nó được đặt vào là $i$. Có hai trường hợp mà ta cần quan tâm như sau:

- **Trường hợp 1:** $j < i$. Tức là phần tử được chọn sẽ được di chuyển sang phải. Khi đó, chỉ số của các phần tử trong đoạn $[j + 1; i]$ sẽ được giảm $1$ đơn vị và chỉ số của $a[j]$ biến thành $i$.

![product sum case 1 no bg](/algo/data-structures/lichao/lichao12.png)


- **Trường hợp 2:** $j > i$. Tức là phần tử được chọn sẽ được di chuyển sang trái. Khi đó, chỉ số của các phần tử trong đoạn $[i; j - 1]$ sẽ được tăng $1$ đơn vị và chỉ số của $a[j]$ biến thành $i$.

![product sum case 2 no bg](/algo/data-structures/lichao/lichao13.png)

- **Trường hợp 3:** $i = j$. Tức mảng được giữ nguyên.

Để thuật tiện cho việc tính toán, gọi:

- $pre[i] = \sum_{k=1}^{i} a[k] \cdot k$.
- $\text{shift}_L[i] = \sum_{k=1}^{i} a[k] \cdot (k-1)$.
- $\text{shift}_R[i] = \sum_{k=1}^{i} a[k] \cdot (k+1)$.

Như vậy, ở trường hợp 1, công thức tính giá trị mới của mảng là:

$$
\underbrace{pre[j - 1]}_\text{unchanged prefix} + \underbrace{pre[n] - pre[i]}_\text{unchanged suffix} + \underbrace{\text{shift}_L[i] - \text{shift}_L[j]}_\text{shifted elements} + a[j] \cdot i
$$

Ta nhóm biểu thức này lại thành $3$ nhóm:

$$
\underbrace{a[j] \cdot i}_\text{P1} + \underbrace{pre[j - 1] - \text{shift}_L[j]}_\text{P2} + \underbrace{pre[n] - pre[i] + \text{shift}_L[i]}_\text{P3}
$$

Tương tự, với trường hợp 2, ta có công thức tính giá trị mới của mảng:

$$
\underbrace{pre[i - 1]}_\text{unchanged prefix} + \underbrace{pre[n] - pre[j]}_\text{unchanged suffix} + \underbrace{\text{shift}_R[j - 1] - \text{shift}_R[i - 1]}_\text{shifted elements} + a[j] \cdot i
$$

Ta lại nhóm biểu thức này thành $3$ nhóm:

$$
\underbrace{a[j] \cdot i}_\text{P1} + \underbrace{\text{shift}_R[j - 1] - pre[j]}_\text{P2} + \underbrace{pre[n] + pre[i - 1] - \text{shift}_R[i - 1]}_\text{P3}
$$

Khi cố định $i$, ta có thể tìm một vị trí $j$ có thể cực đại hóa phần $1$ và $2$ của cả hai biểu thức trên bằng Li-chao tree cơ bản, sau đó cộng riêng phần thứ $3$ vào.

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tt;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

struct line {
    ll a, b;

    line() : a(0), b(LLONG_MIN) {}
    line (ll a, ll b) : a(a), b(b) {}

    ll calc (ll x) { return b == LLONG_MIN ? LLONG_MIN : a * x + b; }
    ll slope() { return a; }
};

struct liChao {
    vector<line> tr;
    liChao (int sz) : tr(sz + 1) {}

    void update (line cur, int l, int r) {
        if (l > r) return;
        if (l == r)
            return tr[l] = (cur.calc(l) > tr[l].calc(l) ? cur : tr[l]), void();

        int mid = (l + r) >> 1;
        if (cur.calc(mid) > tr[mid].calc(mid)) swap(cur, tr[mid]);
        if (cur.slope() < tr[mid].slope()) update(cur, l, mid - 1);
        if (cur.slope() > tr[mid].slope()) update(cur, mid + 1, r);
    }

    ll query (int pos, int l, int r) {
        if (l > r) return LLONG_MIN;
        int mid = (l + r) >> 1;
        ll cur = tr[mid].calc(pos);

        if (l == r) return cur;
        if (l <= pos && pos < mid)
            return max(query(pos, l, mid - 1), cur);
        return max(query(pos, mid + 1, r), cur);
    }

    // reset các giá trị của Li-chao tree
    void refresh() { fill(all(tr), line(0, LLONG_MIN)); }
};

const int mn = 2e5 + 5;
ll a[mn], pre[mn], shiftRight[mn], shiftLeft[mn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i] * i;
        shiftRight[i] = shiftRight[i - 1] + a[i] * (i + 1);
        shiftLeft[i] = shiftLeft[i - 1] + a[i] * (i - 1);
    }

    liChao tree(n); ll ans = pre[n];
    for (int i = 1; i <= n; i++) { // xử lý các trường hợp j < i
        ll best = tree.query(i, 1, n);
        if (best != LLONG_MIN)
            ans = max(ans, best + pre[n] - pre[i] + shiftLeft[i]);
        tree.update(line(a[i], pre[i - 1] - shiftLeft[i]), 1, n);
    }

    tree.refresh();
    for (int i = n; i >= 1; i--) { // xử lý các trường hợp j > i
        ll best = tree.query(i, 1, n);
        if (best != LLONG_MIN)
            ans = max(ans, best + pre[n] + pre[i - 1] - shiftRight[i - 1]);
        tree.update(line(a[i], shiftRight[i - 1] - pre[i]), 1, n);
    }
    cout << ans;

    return 0;
}
```
:::

### Educational Codeforces Round 82: Sum of Prefix Sums

[Link đề bài](https://codeforces.com/contest/1303/problem/G)

Định nghĩa *tổng của tổng tiền tố* của một dãy $s_1, s_2, s_3, \cdots, s_k$, gọi là $g(s)$, được xác định qua công thức

$$
g(s) = (s_1) + (s_1 + s_2) + (s_1 + s_2 + s_3) + \cdots + (s_1 + s_2 + s_3 \cdots + s_k)
$$

Cho cây $n$ đỉnh, có trọng số đỉnh $a_1, a_2, \cdots, a_n$. Định nghĩa $f(u, v)$ là tổng của tổng tiền tố của dãy thu được khi viết trọng số của các đỉnh trên đường đi đơn từ $u$ đến $v$ theo thứ tự. Hãy tìm $\displaystyle\max_{1 \leq u, v \leq n} f(u, v)$.

Giới hạn:

- $1 \leq n \leq 15 \cdot 10^4$.
- $1 \leq a_i \leq 10^6$.

#### Biến đổi công thức tổng của tổng tiền tố

Theo định nghĩa *tổng của tổng tiền tố*, ta đang có một công thức $O(n^2)$. Dễ thấy, công thức đó có thể được biến đổi thành công thức $O(n)$ sau:

$$
g(s) = \sum_{i=1}^{k} s_i \cdot (k - i + 1)
$$

Ngoài ra, nếu đã tính được $g(s_1, s_2, \cdots, s_n)$ và $g(t_1, t_2, \cdots, t_m)$, ta có thể tính $g(s_1, s_2, \cdots, s_n, t_1, t_2, \cdots, t_m)$:

$$
g(s + t) = g(s) + g(t) + (\sum_{i=1}^{n} s_i) \cdot m
$$

Để dễ hiểu hơn, ta có thể xem hình ảnh sau:

![sum of prefix sums no bg](/algo/data-structures/lichao/lichao14.png)

Với ý tưởng này, để tính $f(u, v)$, ta có thể tách đường đi này thành hai phần $u \rightarrow lca$ và $lca' \rightarrow v$ với $lca'$ là nút con của $lca$ nếu đi theo hướng xuống nút $v$. Việc tính riêng $f(u, lca), f(lca', v)$ rồi gộp lại thành $f(u, v)$ dựa trên công thức trên sẽ thuận tiện hơn nhiều so với việc tính trực tiếp $f(u, v)$.

![split path no bg](/algo/data-structures/lichao/lichao15.png)

#### Tìm đường đi tối ưu qua nút gốc

Trước khi đi đến bài toán gốc, ta cần giải một bài toán con đó là tìm $\max f(u, v)$ đối với các đường đi đơn $u \rightarrow v$ đi qua nút gốc $r$. Dễ thấy, do trọng số đỉnh là các số dương nên $u$ và $v$ phải là nút lá hoặc gốc của cây. Để thuận tiện hơn cho việc tính toán, gọi:

- $pre[u]$ là tổng trọng số các đỉnh trên đường đi từ gốc xuống nút $u$.
- $depth[u]$ là độ sâu của nút $u$ (hay số cạnh nằm trên đường đi đơn từ gốc xuống $u$).
- $g_{up}[u]$ là tổng của tổng tiền tố của các nút trên đường đi đơn từ $u$ lên nút gốc.
- $g_{down}[u]$ là tổng của tổng tiền tố của các nút trên đường đi đơn từ gốc xuống nút $u$.

Cả bốn mảng này có thể được tính bằng một lần chạy DFS đơn giản.

Xét một nút lá $u$ nằm trong cây con của $r'$ là nút con của $r$, và một nút $v$ nằm ngoài cây con của $r'$. Ta có thể tính $g(u, v)$ theo công thức:

$$
g_{up}[u] + g_{down}[v] - a[r] \cdot (depth[v] + 1) + pre[u] \cdot depth[v]
$$

Đến đây, ta có thể thấy, nếu cố định một nút $v$, ta cần tìm một phương trình đường thẳng $f_u(x) = pre[u] \cdot x + g_{up}[u]$ cực đại hóa giá trị tại $x = depth[v]$, rồi cộng thêm $g_{down}[v] - a[r] \cdot (depth[v] + 1)$. Để đảm bảo ta chỉ xét đến các nút con $u$ nằm ngoài cây con $r'$, ta cần duyệt các cây con của $r$ theo thứ tự, cập nhật các đoạn thẳng xen kẽ với truy vấn. Sau đó, ta lại duyệt các cây con của $r$ theo thứ tự ngược lại rồi thực hiện tương tự.

Ngoài ra, ta còn phải xét đường đi từ một nút lá lên nút gốc và từ nút gốc xuống một nút lá. Dễ thấy kết quả sẽ là $\max(g_{up}[u], g_{down}[u] + a[r] \cdot (depth[u] + 1))$.

#### Tìm đường tối ưu cho mọi cặp đỉnh

Đến đây, ta có thể kết hợp thuật toán phân tách trọng tâm (centroid decomposition)[^[6]^](/algo/graph-theory/centroid-decomposition) để tìm đường tối ưu cho mọi cặp đỉnh.

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tt;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

struct line {
    ll a, b;

    line() : a(0), b(LLONG_MIN) {}
    line (ll a, ll b) : a(a), b(b) {}

    ll calc (ll x) { return (b == LLONG_MIN ? b : a * x + b); }

    ll slope() { return a; }
};

const int M = 2e5;

struct liChao {
    unordered_map<int,line> tr; // sử dụng tối ưu bộ nhớ kết hợp Li-chao tree trên mảng thưa
    liChao() {}

    void update (line cur, int l = 1, int r = M) {
        if (l > r) return;
        if (l == r)
            return tr[l] = (cur.calc(l) > tr[l].calc(l) ? cur : tr[l]), void();

        int mid = (l + r) >> 1;
        if (cur.calc(mid) > tr[mid].calc(mid)) swap(cur, tr[mid]);
        if (cur.slope() < tr[mid].slope()) update(cur, l, mid - 1);
        if (cur.slope() > tr[mid].slope()) update(cur, mid + 1, r);
    }

    ll query (int pos, int l = 1, int r = M) {
        if (l > r) return LLONG_MIN;
        int mid = (l + r) >> 1;
        ll cur = tr[mid].calc(pos);

        if (l == r) return cur;
        if (l <= pos && pos < mid)
            return max(query(pos, l, mid - 1), cur);
        else return max(query(pos, mid + 1, r), cur);
    }
};

const int mn = 2e5 + 5;
ll a[mn], pre[mn], gUp[mn], gDown[mn], ans;
int sz[mn], depth[mn];
vector<int> adj[mn];
bool del[mn];

int szDfs (int u, int p) { // hàm tính kích thước từng cây con
    sz[u] = 1;
    for (int v : adj[u])
        if (v != p && !del[v]) sz[u] += szDfs(v, u);
    return sz[u];
}

int centroid (int u, int p, int sztr) { // hàm tìm kiếm trọng tâm
    for (int v : adj[u])
        if (v != p && !del[v] && sz[v] > sztr / 2)
            return centroid(v, u, sztr);
    return u;
}

void dfs (int u, int p, int d, bool start, vector<int> &leaves) { // hàm tính lại các giá trị "depth", "pre",
                                                                  // "gUp", "gDown" trong cây con sau khi đặt gốc mới
    depth[u] = d, pre[u] = pre[p] + a[u];
    gUp[u] = a[u] * (depth[u] + 1) + gUp[p];
    gDown[u] = gDown[p] + pre[u];

    int child = 0;
    for (int v : adj[u])
        if (v != p && !del[v]) child++, dfs(v, u, d + 1, 0, leaves);
    if (!child) leaves.push_back(u);
}

void solve (int root) { // hàm chia để trị trên cây
    /// phần template của thuật toán phân rã trọng tâm
    root = centroid(root, root, szDfs(root, root));
    pre[root] = gUp[root] = gDown[root] = a[root];

    vector<vector<int>> leaves(adj[root].size());
    for (int i = 0; i < adj[root].size(); i++) {
        int v = adj[root][i];
        if (del[v]) continue;

        dfs(v, root, 1, 1, leaves[i]);
    }

    // tìm f(u, v) lớn nhất với lca(u, v) = root
    function<void(void)> calc = [&] () {
        liChao tree;
        for (int i = 0; i < adj[root].size(); i++) {
            if (del[adj[root][i]]) continue;
            for (int leaf : leaves[i]) {
                ans = max({ans, gUp[leaf], gDown[leaf]}); // trường hợp lá đến gốc và từ gốc đến lá
                ll best = tree.query(depth[leaf]);
                if (best != LLONG_MIN)
                    ans = max(ans, best + gDown[leaf] - a[root] * (depth[leaf] + 1)); // trường hợp lá đến lá khác
            }
            for (int leaf : leaves[i])
                tree.update(line(pre[leaf], gUp[leaf]));
        }
        return;
    };

    calc();
    reverse(all(adj[root]));
    reverse(all(leaves));
    calc();

    // phần template của thuật toán phân rã trọng tâm
    del[root] = 1;
    for (int v : adj[root])
        if (!del[v]) solve(v);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> a[i];
    solve(1);

    cout << ans;

    return 0;
}
```
:::

Thuật toán có độ phức tạp thời gian là $O(n \log^2 n)$ và bộ nhớ $O(n \log n)$. Tuy nhiên, hằng số của thuật toán phân rã trọng tâm là khá lớn nên cần cài đặt khéo léo một chút để tối ưu hằng số.

### COMPFEST 15: Keen Tree Calculation

[Link đề bài](https://codeforces.com/contest/1866/problem/K)

Cho cây $N$ đỉnh, có trọng số cạnh và $Q$ truy vấn. Ở mỗi truy vấn, cho hai số nguyên $U, K$, cho biết nếu trọng số của các cạnh kề với đỉnh $U$ được nhân lên $K$ lần thì đường kính của cây có độ dài là bao nhiêu. Sau mỗi truy vấn, trọng số của cây không bị thay đổi.

Giới hạn:
- $2 \leq N, Q \leq 10^5$.
- $1 \leq W, K \leq 10^9$.

#### Ý tưởng

Dễ thấy, do hệ số $K \geq 1$ nên đường kính của cây chỉ có thể tăng. Từ đây, ta có ý tưởng là tính đường kính của cây ban đầu, sau đó, với mỗi truy vấn, tìm đường đi dài nhất đi qua nút $U$.

Để đơn giản hóa vấn đề, ta giả sử tất cả các truy vấn có $U$ bằng nhau. Ta đặt nút này (gọi là $r$) làm gốc. Bây giờ, ta chỉ quan tâm bài toán nhân hệ số cho nút gốc.

#### Giải bài toán cho nút gốc

Với mỗi nút con $v$ của $r$, gọi $dp[v]$ là độ dài đường đi dài nhất từ $v$ xuống một nút lá bất kỳ của cây con gốc $v$. Để tìm độ dài đường đi dài nhất đi qua $r$, ta chọn ra tối đa $2$ nút con có $w_{r, v} \cdot K + dp[v]$ lớn nhất, đáp án là tổng của hai giá trị này.

![keen tree no bg](/algo/data-structures/lichao/lichao17.png)

Để thực hiện nhiều truy vấn như vậy, ta để ý biểu thức trên có dạng phương trình đường thẳng. Do đó, ta có thể xây dựng Li-chao tree quản lý tập đường thẳng $\{w_{r, v} \cdot x + dp[v]\}$. Với mỗi truy vấn, ta tìm hai phương trình có giá trị lớn nhất tại $x = K$. Thao tác này có thể thực hiện với biến thể Li-chao tree tìm hàm tối ưu thứ $k$ được giới thiệu ở phần trước.

#### Giải bài toán cho cả cây

Để giải cho các nút không phải là gốc, ta có thể sử dụng kỹ thuật chuyển gốc cho Quy hoạch động trên cây[^[7]^](/algo/dp/treedp#b%C3%A0i-to%C3%A1n-2-k%E1%BB%B9-thu%E1%BA%ADt-chuy%E1%BB%83n-g%E1%BB%91c). Một cách làm khác là với mọi nút, ta tính:

- $dp_{down}[u]$ là độ dài đường đi dài nhất từ $u$ xuống một lá bất kỳ trong cây con của $u$.
- $dp_{up}[u]$ là độ dài đường đi dài nhất từ $u$ ra khỏi cây con của $u$ đến một lá bất kỳ ngoài cây con của $u$.

Sau đó, ta xử lý offline các truy vấn với ý tưởng tương tự.

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tt;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

struct line {
    ll a, b;

    line() : a(0), b(0) {}
    line (ll a, ll b) : a(a), b(b) {}

    ll calc (ll x) { return a * x + b; }

    ll slope() { return a; }
};

struct node {
    vector<line> tr;
    int mkth;
    node *lpt, *rpt;

    node (int mkth) : mkth(mkth), lpt(nullptr), rpt(nullptr) {}

    void update (line cur, int l, int r) {
        tr.push_back(cur);
        if (tr.size() <= mkth * 2 - 1) return;

        int mid = (l + r) >> 1;
        nth_element(tr.begin(), tr.end() - 1, tr.end(),
                    [&] (line a, line b) { return a.calc(mid) > b.calc(mid); });
        line worst = tr.back();
        tr.pop_back();

        if (l == r) return;

        int dominantLeft = 0;
        for (line it : tr)
            dominantLeft += (it.slope() < worst.slope());

        if (dominantLeft < mkth) {
            if (lpt == nullptr) lpt = new node(mkth);
            lpt->update(worst, l, mid);
        }
        else {
            if (rpt == nullptr) rpt = new node(mkth);
            rpt->update(worst, mid + 1, r);
        }
    }

    void push (vector<ll> &cand, ll cur, int kth) {
        cand.push_back(cur);
        if (cand.size() > kth) {
            nth_element(cand.begin(), cand.end() - 1, cand.end(), greater<ll>());
            cand.pop_back();
        }
    }

    void walk (vector<ll> &cand, int pos, int kth, int l, int r) {
        for (line cur : tr) push(cand, cur.calc(pos), kth);
        if (l == r) return;

        int mid = (l + r) >> 1;
        if (l <= pos && pos <= mid) {
            if (lpt != nullptr) lpt->walk(cand, pos, kth, l, mid);
        }
        else {
            if (rpt != nullptr) rpt->walk(cand, pos, kth, mid + 1, r);
        }
    }

    ll query (int pos, int kth, int l, int r) {
        vector<ll> cand;
        walk(cand, pos, kth, l, r);
        nth_element(cand.begin(), cand.end() - 1, cand.end(), greater<ll>());
        return cand.back();
    }
};

struct presfx {
    vector<ll> pre, sfx;
    int n;

    presfx (vector<ll> a) : pre(a.size()), sfx(a.size()), n(a.size()) {
        if (!n) return;
        pre[0] = a[0], sfx[n - 1] = a[n - 1];
        for (int i = 1; i < n; i++)
            pre[i] = max(pre[i - 1], a[i]);
        for (int i = n - 2; i >= 0; i--)
            sfx[i] = max(sfx[i + 1], a[i]);
    }

    ll getPre (int p) { return (0 <= p && p < n ? pre[p] : 0); }

    ll getSfx (int p) { return (0 <= p && p < n ? sfx[p] : 0); }

    // lấy giá trị lớn nhất ngoại trừ vị trí "exc", bằng cách duy trì
    // giá trị tốt nhất cho các tiền tố và hậu tố
    ll query (int exc) { return max(getPre(exc - 1), getSfx(exc + 1)); }
};

const int mn = 2e5 + 5;
const int M = 1e9;

ll dpDown[mn], dpUp[mn], bestPath[mn];
vector<pii> adj[mn], qry[mn];

void dfsDown (int u, int p) {
    vector<ll> a(adj[u].size());
    for (int i = 0; i < adj[u].size(); i++) {
        int v; ll w; tie(v, w) = adj[u][i];
        if (v == p) continue;

        dfsDown(v, u);
        dpDown[u] = max(dpDown[u], w + dpDown[v]);
        a[i] = w + dpDown[v];
    }
    presfx helper(a);

    // ghép cạnh (u, v) với một đường đi từ u xuống nút lá khác hướng u -> v
    for (int i = 0; i < adj[u].size(); i++) {
        int v; ll w; tie(v, w) = adj[u][i];
        if (v != p) dpUp[v] = max(dpUp[v], w + helper.query(i));
    }
}

void dfsUp (int u, int p, ll toParent) {
    node tree(2);
    for (auto [v, w] : adj[u])
        if (v != p) tree.update(line(w, dpDown[v]), 1, M);

    if (u != p) { // u không phải nút gốc
        dpUp[u] = max(dpUp[u], toParent + dpUp[p]);
        tree.update(line(toParent, dpUp[u] - toParent), 1, M);
    }

    // trả lời các truy vấn gắn với nút u
    for (auto [multiplier, id] : qry[u]) {
        if (adj[u].size() == 1) bestPath[id] = tree.query(multiplier, 1, 1, M);
        else bestPath[id] = tree.query(multiplier, 1, 1, M) + tree.query(multiplier, 2, 1, M);
    }

    for (auto [v, w] : adj[u])
        if (v != p) dfsUp(v, u, w);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int u, k; cin >> u >> k;
        qry[u].emplace_back(k, i);
    }

    dfsDown(1, 1);
    dfsUp(1, 1, 0);

    ll diameter = 0;
    for (int i = 1; i <= n; i++)
        diameter = max(diameter, dpDown[i] + dpUp[i]);

    for (int i = 0; i < q; i++)
        cout << max(diameter, bestPath[i]) << "\n";

    return 0;
}
```
:::

Thuật toán có độ phức tạp thời gian và bộ nhớ là $O(n \log K)$.

## Ứng dụng: Các bài tập thuần cấu trúc dữ liệu

### Codeforces Round 545: Train Car Selection

[Link đề bài](https://codeforces.com/contest/1137/problem/E)

Cho một mảng $A$ gồm $n$ phần tử được đánh số từ $1$. Ban đầu, các phần tử của $A$ có giá trị là $0$. Thực hiện $q$ thao tác trên mảng thuộc $1$ trong $3$ loại như sau:

1. Cho số nguyên $k$, thêm $k$ phần tử có giá trị $0$ vào đầu mảng $A$. Sau thao tác này, các phần tử sẽ được đánh số lại.
2. Cho số nguyên $k$, thêm $k$ phần tử có giá trị $0$ vào cuối mảng $A$.
3. Cho hai số nguyên $b, s$, thực hiện tăng $A[i]$ lên $b + (i - 1) \cdot s$ đơn vị với mọi phần tử trong mảng $A$.

Sau mỗi thao tác, trong các phần tử có giá trị nhỏ nhất, tìm phần tử có chỉ số nhỏ nhất.

Giới hạn:

- $1 \leq n \leq 10^9$.
- $1 \leq m \leq 3 \cdot 10^5$.
- $1 \leq k, b, s \leq 10^9$.
- Đảm bảo các giá trị của mảng $A$ không vượt quá $10^{18}$.

#### Xử lý chỉ số

Để tránh phải xử lý chỉ số, lưu hai biến $head$ và $tail$ ban đầu có giá trị là $1$ và $n$. Với thao tác loại 1, các phần tử được thêm vào sẽ có chỉ số từ $head - k$ đến $head - 1$ và biến $head$ sẽ được giảm $k$ đơn vị. Tương tự với thao tác loại 2, các phần tử được thêm vào có chỉ số từ $tail + 1$ đến $tail + k$ và biến $tail$ sẽ được tăng $k$ đơn vị.

Như vậy, thao tác loại 3 sẽ được biến đổi thành tăng $A[i]$ lên $b + (i - head) \cdot s$ đơn vị với $i \in [head; tail]$.

#### Ý tưởng

Thoạt đầu, bài toán có vẻ yêu cầu sử dụng một cấu trúc dữ liệu hỗ trợ tăng đoạn theo dạng bậc thang. Tuy nhiên, ta có thể biến đổi một chút để biến thành một bài toán đơn giản hơn nhiều.

Một nhận xét quan trọng đó là, với mỗi nhóm các phần tử được thêm vào trong cùng một thao tác, chỉ có phần tử đầu tiên có thể đóng góp vào đáp án. Lý do là vì ở thao tác loại 3, hệ số $s$ luôn dương nên các phần tử có chỉ số càng lớn sẽ càng tăng mạnh. Như vậy, ta chỉ cần quan tâm $O(q)$ vị trí khác nhau.

Xét các phần tử có sẵn trong mảng từ ban đầu, giả sử ta đã thực hiện được $j$ thao tác loại 3. Gọi $head_k$ là giá trị $head$ tại thời điểm thực hiện thao tác loại 3 thứ $k$. Giá trị của $A[i]$ là:

$$
[b_1 + (i - head_1) \cdot s_1] + [b_2 + (i - head_2) \cdot s_2] + \cdots + [b_j + (i - head_j) \cdot s_j]
$$

Biến đổi công thức lại thành:

$$
\underbrace{i \cdot \sum_{k=1}^{j} s_k}_\text{P1} + \underbrace{\sum_{k=1}^{j} (b_k - head_k \cdot s_k)}_\text{P2}
$$

Để áp dụng công thức này cho các phần tử được thêm vào mảng sau, ta cần tìm cách "triệt tiêu" ảnh hưởng của các thao tác loại 3 được thực hiện trước đó. Cụ thể, với phần tử $i$ được thêm vào tại thời điểm đã thực hiện được $j'$ thao tác loại 3, ta có công thức xác định $A[i]$ như sau:

$$
\underbrace{i \cdot (\sum_{k=1}^{j} s_k - \sum_{k=1}^{j'} s_k)}_\text{P1} + \underbrace{\sum_{k=1}^{j} (b_k - head_k \cdot s_k) - \sum_{k=1}^{j'} (b_k - head_k \cdot s_k)}_\text{P2}
$$

Biến đổi công thức lại và nhóm thành $3$ phần:

$$
\underbrace{(i \cdot \sum_{k=1}^{j} s_k)}_{\text{depend on both } i \text{ and } j} - \underbrace{[i \cdot \sum_{k=1}^{j'} s_k + \sum_{k=1}^{j'} (b_k - head_k \cdot s_k)]}_{\text{depend on } i \text{ only}} + \underbrace{[ \sum_{k=1}^{j} (b_k - head_k \cdot s_k)]}_{\text{depend on } j \text{ only}}
$$

:::spoiler Lưu ý
Biến $j'$ phụ thuộc vào $i$ nên ta chỉ xét tính phụ thuộc của biến $i$ và $j$.
:::

Đến đây, ta thấy hai phần đầu tiên tạo thành một phương trình đường thẳng. Như vậy, sau thao tác loại 3 thứ $j$, giá trị nhỏ nhất sẽ là giá trị của phương trình đường thẳng được cực tiểu hóa tại điểm $\sum_{k=1}^{j} s_k$. Từ đây, có thể sử dụng Sparse Li-chao tree để thực hiện các truy vấn.

#### Thuật toán

Đặt $P = \sum s_k$ và $T = \sum (b_k - head_k \cdot s_k)$, tính các thao tác đến thời điểm hiện tại, và $S$ là tập đoạn thẳng được quản lý bởi Sparse Li-chao tree. Ta xử lý các thao tác như sau:

- Thao tác loại 1: Giảm $head$ xuống $k$ đơn vị và thêm phương trình $f(x) = head \cdot x - head \cdot P - T$ vào tập đường thẳng.
- Thao tác loại 2: Thêm phương trình $f(x) = (tail + 1) \cdot x - (tail + 1) \cdot P - T$ vào tập đường thẳng rồi tăng $tail$ lên $k$ đơn vị.
- Thao tác loại 3: Tăng $P$ lên $s$ đơn vị và tăng $T$ lên $b - head \cdot s$ đơn vị.

Sau mỗi thao tác, tìm $\min_{f \in S} f(P) + T$. Để tìm chỉ số tương ứng, ta lưu mỗi hàm dưới dạng cặp giá trị $(f_i(x), i)$, ưu tiên cực tiểu hóa giá trị của hàm, sau đó mới cực tiểu hóa giá trị của $i$.

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tt;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

const int M = 5e14;

struct line {
    ll a, b;

    line() : a(0), b(0) {}
    line (ll a, ll b) : a(a), b(b) {}

    pl calc (ll x) { return make_pair(a * x + b, a); }

    ll slope() { return a; }
};

struct node {
    line tr;
    node *lpt, *rpt;

    node() : tr(0, LLONG_MAX), lpt(nullptr), rpt(nullptr) {}

    ll divi (ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    void update (line cur, ll l = -M, ll r = M) {
        if (l == r) {
            if (cur.calc(l) < tr.calc(l)) tr = cur;
            return;
        }
        ll mid = divi(l + r, 2);
        if (cur.calc(mid) < tr.calc(mid)) swap(cur, tr);
        if (cur.slope() > tr.slope()) {
            if (lpt == nullptr) lpt = new node();
            lpt->update(cur, l, mid);
        }
        else if (cur.slope() < tr.slope()) {
            if (rpt == nullptr) rpt = new node();
            rpt->update(cur, mid + 1, r);
        }
    }

    pl query (ll x, ll l = -M, ll r = M) {
        pl cur = tr.calc(x);
        ll mid = divi(l + r, 2);
        if (l == r) return cur;
        if (x <= mid) {
            if (lpt == nullptr) return cur;
            return min(cur, lpt->query(x, l, mid));
        }
        else {
            if (rpt == nullptr) return cur;
            return min(cur, rpt->query(x, mid + 1, r));
        }
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q; cin >> n >> q;
    ll head = 1, tail = n, P = 0, T = 0;

    node tree; tree.update(line(head, 0));
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int k; cin >> k;
            head -= k;
            tree.update(line(head, - head * P - T));
        }
        else if (type == 2) {
            int k; cin >> k;
            tree.update(line(tail + 1, - (tail + 1) * P - T));
            tail += k;
        }
        else {
            int b, s; cin >> b >> s;
            P += s, T += b - head * s;
        }

        ll best; int pos; tie(best, pos) = tree.query(P);
        cout << pos - head + 1 << " " << best + T << "\n";
    }

    return 0;
}
```
:::

Thuật toán có độ phức tạp thời gian và bộ nhớ là $O(q \log (\sum s))$.

### IOI 2005: Mountain

[Link đề bài](https://dmoj.ca/problem/ioi05p3)

Cho mảng $d$ gồm $n$ phần tử, ban đầu toàn bộ phần tử có giá trị bằng $0$. Thực hiện $q$ thao tác:

1. Cho ba số nguyên $a, b, D$, gán $d[i] = D$ với mọi $i \in [a; b]$.
2. Cho số nguyên $h$. Gọi mảng $p$ là mảng tổng tiền tố của $d$, tìm vị trí $k$ lớn nhất sao cho $\max(p_1, p_2, \cdots, p_k) \leq h$.

Giới hạn:
- $1 \leq n \leq 10^9$.
- $1 \leq q \leq 10^5$.
- $1 \leq a \leq b \leq n$.
- $-10^9 \leq D \leq 10^9$.
- $0 \leq h \leq 10^9$.

#### Ý tưởng

Thay vì thao tác trên mảng $d$, ta sẽ thao tác trên mảng $p$, tức mảng tổng tiền tố của $d$. Lúc này, thao tác loại 1 sẽ được biến đổi thành một thao tác gán phương trình đường thẳng và tăng/giảm một đoạn cho cùng một giá trị:

![ioi mountain no bg](/algo/data-structures/lichao/lichao18.png)

Như vậy, ta cần một cấu trúc dữ liệu hỗ trợ các thao tác sau:

- **Gán phương trình đường thẳng**: Cho bốn số nguyên $L, R, a, b$, gán $p[i] = a \cdot i + b$ với mọi $i \in [L; R]$.
- **Tăng đoạn**: Cho ba số nguyên $L, R, b$, tăng $p[i]$ lên $b$ đơn vị với mọi $i \in [L; R]$.
- **Truy vấn $\max$**: Cho hai số nguyên $L, R$, tính $\max(p[L], p[L + 1], \cdots, p[R])$.

Cả ba thao tác đều có thể được xử lý bằng Sparse Li-chao tree với Lazy propagation (Extended Li-chao tree cài đặt bằng con trỏ).

Với thao tác loại 3, ta có thể chặt nhị phân trên thao tác tìm truy vấn $\max$. Tuy nhiên, nếu giới hạn đủ chặt chẽ thì độ phức tạp $O(\log^2 n)$ sẽ là không đủ. Do đó, ta cần áp dụng một thuật toán tương tự Walk on Segment tree[^[8]^](https://leduythuccs.github.io/2020-07-10-Binary-Search-on-Segment-Tree/) cho thao tác này.

:::spoiler Code tham khảo
```cpp=
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tt;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

struct line {
    int a, b;

    line() : a(0), b(0) {}
    line (int a, int b) : a(a), b(b) {}

    int calc (int x) { return a * x + b; }

    bool operator != (const line &o) const {
        return a != o.a || b != o.b;
    }

    bool operator == (const line &o) const {
        return a == o.a && b == o.b;
    }
};

const line init(INT_MIN, INT_MIN);

struct node {
    int tr, lazy;
    line asgn;
    node *lpt, *rpt;

    node() : tr(0), lazy(0), asgn(init), lpt(nullptr), rpt(nullptr) {}

    int get (int l, int r) {
        if (asgn == init) return lazy + tr;
        return lazy + max(asgn.calc(l), asgn.calc(r));
    }

    void pushDown (int l, int r, int mid) {
        if (lpt == nullptr) lpt = new node();
        if (rpt == nullptr) rpt = new node();

        bool change = 0;
        if (asgn != init)
            lpt->asgn = rpt->asgn = asgn, lpt->lazy = rpt->lazy = 0, asgn = init, change = 1;
        if (lazy)
            lpt->lazy += lazy, rpt->lazy += lazy, lazy = 0, change = 1;
        if (change)
            tr = max(lpt->get(l, mid), rpt->get(mid + 1, r));
    }

    void assignLine (int a, int b, line cur, int l, int r) {
        /*
            a..b: khoảng cần cập nhật
            cur: đường thẳng cần cập nhật
            l..r: khoảng mà nút quản lý
        */
        if (b < l || r < a) return;
        if (a <= l && r <= b) {
            asgn = cur, lazy = 0;
            return;
        }
        int mid = (l + r) >> 1; pushDown(l, r, mid);
        lpt->assignLine(a, b, cur, l, mid);
        rpt->assignLine(a, b, cur, mid + 1, r);
        tr = max(lpt->get(l, mid), rpt->get(mid + 1, r));
    }

    void addConstant (int a, int b, int delta, int l, int r) {
        /*
            a..b: khoảng cần cập nhật
            delta: giá trị cần nhập nhật
            l..r: khoảng mà nút quản lý
        */
        if (b < l || r < a) return;
        if (a <= l && r <= b) {
            lazy += delta;
            return;
        }
        int mid = (l + r) >> 1; pushDown(l, r, mid);
        lpt->addConstant(a, b, delta, l, mid);
        rpt->addConstant(a, b, delta, mid + 1, r);
        tr = max(lpt->get(l, mid), rpt->get(mid + 1, r));
    }

    int walk (int targ, int l, int r) {
        /*
            targ: tìm vị trí nhỏ nhất > targ
            l..r: khoảng mà nút quản lý
        */
        if (l == r) return l;
        int mid = (l + r) >> 1; pushDown(l, r, mid);
        if (lpt->get(l, mid) > targ) return lpt->walk(targ, l, mid);
        return rpt->walk(targ, mid + 1, r);
    }

    int query (int pos, int l, int r) {
        /*
            pos: vị trí được truy vấn
            l..r: khoảng mà nút quản lý
        */
        if (l == r) return get(l, r);
        if (asgn != init) return asgn.calc(pos) + lazy;
        int mid = (l + r) >> 1;
        if (l <= pos && pos <= mid)
            return lazy + (lpt == nullptr ? 0 : lpt->query(pos, l, mid));
        if (mid < pos && pos <= r)
            return lazy + (rpt == nullptr ? 0 : rpt->query(pos, mid + 1, r));
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    node tree;

    char type;
    while (cin >> type) {
        if (type == 'E') return 0;
        if (type == 'I') {
            int a, b, D; cin >> a >> b >> D;
            int curL = (a > 1 ? tree.query(a - 1, 1, n) : 0), curR = tree.query(b, 1, n);
            tree.assignLine(a, b, line(D, curL - D * (a - 1)), 1, n);
            if (b < n)
                tree.addConstant(b + 1, n, tree.query(b, 1, n) - curR, 1, n);
        }
        else {
            int h; cin >> h;
            cout << (tree.get(1, n) <= h ? n : tree.walk(h, 1, n) - 1) << "\n";
        }
    }

    return 0;
}
```
:::

Thuật toán có độ phức tạp thời gian và bộ nhớ là $O(q \log n)$.

## Phụ lục

### Bài tập ứng dụng

#### Li-chao tree và các biến thể cơ bản

-  [Library Checker: Segment Add Get Min](https://judge.yosupo.jp/problem/segment_add_get_min)
-  [CEOI 2017: Building Bridges](https://oj.uz/problem/view/CEOI17_building)
- [Codeforces Round 526: The Fair Nut and Rectangles](https://codeforces.com/problemset/problem/1083/E)
- [Codeforces Round 189: Kalila and Dimna in the Logging Industry](https://codeforces.com/problemset/problem/319/C)
- [CSES: Houses and Schools](https://cses.fi/problemset/task/2087)
- [Codeforces Round 334: Product Sum](https://codeforces.com/problemset/problem/631/E)
- [CEOI 2009: Harbingers](https://oj.uz/problem/view/CEOI09_harbingers)
- [Codeforces Round 545: Train Car Selection](https://codeforces.com/contest/1137/problem/E)
- [Codeforces Round 463: Escape Through Leaf](https://codeforces.com/problemset/problem/932/F)
- [Codeforces Beta Round 75: Igloo Skyscraper](https://codeforces.com/problemset/problem/91/E)
- [Educational Codeforces Round 11: Bear and Bowling 4](https://codeforces.com/problemset/problem/660/F)
- [AtCoder: Contest with Drinks Hard](https://atcoder.jp/contests/arc066/tasks/arc066_d)
- [Educational Codeforces Round 82: Sum of Prefix Sums](https://codeforces.com/problemset/problem/1303/G)
- [APIO 2010: Commando](https://dmoj.ca/problem/apio10p1)
- [Codeforces Beta Round 64: Professor's task](https://codeforces.com/contest/70/problem/D)

#### Li-chao tree tìm hàm tối ưu thứ $k$

- [COMPFEST 15: Keen Tree Calculation](https://codeforces.com/contest/1866/problem/K0)

#### Extended Li-chao tree

- [IOI 2005: Mountain](https://dmoj.ca/problem/ioi05p3)
- [Atcoder Beginner Contest 177: I hate Shortest Path Problem](https://atcoder.jp/contests/abc177/tasks/abc177_f0)
- [NOI 2020: Progression](https://oj.uz/problem/view/NOI20_progression)
- [IOI 2018: Meetings](https://oj.uz/problem/view/IOI18_meetings)
- [Library Checker: Range Linear Add Range Min](https://judge.yosupo.jp/problem/range_linear_add_range_min)

### Nguồn tham khảo & mở rộng

- [A Simple Blog by robert1003](https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html)
- [Codeforces blog by ngk_manh](https://codeforces.com/blog/entry/95494)
- [Codeforces blog by rang_pang](https://codeforces.com/blog/entry/86731)
- [CP-Algorithm](https://cp-algorithms.com/geometry/convex_hull_trick.html)
- [USACO Guide](https://usaco.guide/adv/line-container)
- [Codeforces blog by errorgorn](https://codeforces.com/blog/entry/98663)