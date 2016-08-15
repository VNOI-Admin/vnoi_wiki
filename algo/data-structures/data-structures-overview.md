# Tổng quan về Cấu Trúc Dữ Liệu

[[_TOC_]]

Mặc dù máy tính đã có thể xử lý hàng triệu phép tính mỗi giây, nhưng khi một bài toán trở phức tạp, cách tổ chức dữ liệu vẫn vô cùng quan trọng.

Để minh họa điểm này, hãy tham khảo ví dụ sau: bạn đi đến thư viện, thử tìm kiếm một quyển sách với chủ đề nào đó. Các cuốn sách được xếp theo lĩnh vực. Trong mỗi chủ đề, sách lại được xếp theo tên tác giả, nhờ vậy mà việc lấy và cất sách từ giá trở nên khá dễ dàng và đơn giản.

Bây giờ, hãy thử tưởng tượng thay vì tổ chức thành từng giá sách cụ thể, sách được chất thành từng đống ở khắp thư viện. Để tìm được quyển sách của mình, bạn sẽ phải mất hàng giờ, thậm chí rất nhiều ngày.

Tương tự, một phần mềm không thể vận hành hiệu quả khi dữ liệu không được lưu trữ một cách phù hợp với ứng dụng.

Trong bài viết này, chúng ta sẽ cùng nhau điểm qua các loại cấu trúc dữ liệu từ cơ bản đến nâng cao. Để tìm hiểu chi tiết về một cấu trúc dữ liệu, các bạn có thể đọc ở link tương ứng.

# Mảng (array), danh sách liên kết (linked list)

Mảng và danh sách liên kết là 2 cấu trúc dữ liệu nền tảng cho tất cả các loại cấu trúc dữ liệu khác. Mảng và danh sách liên kết đều được dùng khi bạn muốn lưu nhiều dữ liệu (thường có cùng kiểu dữ liệu). Bảng dưới đây so sánh các thao tác về mảng và danh sách liên kết:

<table>
<tr>
<th></th>
<th>Mảng</th>
<th>Danh sách liên kết</th>
</tr>
<tr>
<th>Bộ nhớ</th>
<td>Cố định (cần biết trước số phần tử)</td>
<td>Có thể tăng giảm tùy ý</td>
</tr>
<tr>
<th>Thêm/Xóa 1 phần tử</th>
<td>$\mathcal{O}(N)$</td>
<td>$\mathcal{O}(1)$</td>
</tr>
<tr>
<th>Truy cập phần tử</th>
<td>$\mathcal{O}(1)$</td>
<td>$\mathcal{O}(N)$</td>
</tr>
<tr>
<th>Khác</th>
<td>- Ít bộ nhớ hơn<br/>- Cache locality: các phần tử ở vị trí gần nhau trên bộ nhớ máy tính, nên khi truy cập các phần tử liên tiếp sẽ nhanh hơn</td>
<td></td>
</tr>
</table>

Bạn có thể đọc thêm về mảng và danh sách liên kết [[ở đây|algo/data-structures/array-vs-linked-lists]]

# Mảng cộng dồn (Partial Sum)

Mảng cộng dồn là một cách áp dụng khéo léo mảng. Có 2 dạng bài cơ bản có thể giải được bằng cách áp dụng Partial Sum.

## Mảng cộng dồn - Tìm tổng một đoạn liên tiếp

**Ví dụ**

- Cho một mảng $a_1,a_2,a_3,...,a_N$.
- Cần trả lời nhiều truy vấn, mỗi truy vấn cho 2 số $L$ và $R$, yêu cầu in ra tổng $a_L + a_{L+1} + ... + a_R$.

**Cách làm**

- Tạo một mảng $S$, với $S_i = a_1 + a_2 + ... + a_i$. Mảng $S$ được gọi là mảng cộng dồn
- Với mỗi truy vấn, in ra: $S_R – S_{L-1}$.

## Mảng cộng dòn - Tăng giá trị các đoạn

**Ví dụ**

- Cho mảng $a_1,a_2,...,a_N$.
- Cần thực hiện nhiều truy vấn, mỗi truy vấn cho 3 số $L$, $R$, $V$. Yêu cầu: với mỗi $i (L \le i \le R)$, cộng $V$ vào $a_i$.
- Tính mảng $a$ sau khi thực hiện tất cả các truy vấn.

**Cách làm**

- Tạo một mảng $P$: $p_1,p_2,...,p_N$
- Khởi tạo $p_i = 0$.
- Với mỗi truy vấn, tăng $p_L$ lên $V$ và trừ $p_{R+1}$ đi $V$.
- Cuối cùng, với mỗi $i$ (từ 1), $p_i += p_{i–1}$. Ta có $a_i = a_i + p_i$.

# Cây (Tree)

**Cây (tree)** là một đồ thị vô hướng liên thông không có chu trình.

Cây có nhiều tính chất đặc biệt:

- Cây là đồ thị liên thông
- Cây không có chu trình
- Số đỉnh của đồ thị lớn hơn số cạnh của đồ thị đúng 1 đơn vị

Có nhiều dạng cây như **Cây Có Gốc (Rooted Trees)**, **Cây Có Hướng (Directed Trees)**,...

Cây được sử dụng để cài đặt nhiều cấu trúc dữ liệu khác như Heap, Segment Tree (Interval Tree), Fenwick Tree (Binary Indexed Tree)...

Bạn có thể đọc thêm về cây ở [[bài viết này|translate/wcipeg/tree]].

# Disjoint Sets

**Disjoint Sets** là cấu trúc dữ liệu được sử dụng trong thuật toán **Kruskal** và thuật toán **Prim** - 2 thuật toán tìm cây khung nhỏ nhất của đồ thị. Như tên gọi của nó, Disjoint Set được dùng để quản lý các tập hợp không giao nhau.

**Bài toán**

Cho đồ thị có $N$ đỉnh. Ta cần thực hiện 2 loại truy vấn:

- Nối 2 đỉnh $i$ và $j$
- Kiểm tra 2 đỉnh $i$ và $j$ có thuộc cùng thành phần liên thông hay không.

Disjoint set cho phép ta thực hiện 2 thao tác trên với độ phức tạp $\mathcal{O}(\log{N})$.

Bạn có thể đọc thêm về Disjoint Set ở [[bài viết này|algo/data-structures/disjoint-set]].

# Priority Queue - Heap

Heap là một cấu trúc dữ liệu cho phép thực hiện các thao tác:

- Thêm một phần tử, với độ phức tạp $\mathcal{O}(\log{N})$.
- Xóa một phần tử, với độ phức tạp $\mathcal{O}(\log{N})$.
- Tìm $max$ của các phần tử, với độ phức tạp $\mathcal{O}(1)$.

Bạn có thể đọc thêm về Heap [[ở đây|translate/wcipeg/Binary-Heap]]


**Fibonacci Heap** là một dạng heap có **độ phức tạp** bé hơn. Trong **C++**, CTDL **priority_queue** được cài đặt bằng Fibonacci Heap.

# Cây Tìm Kiếm Nhị Phân

**Cây Tìm Kiếm Nhị Phân** (**BST Binary Search Tree**) là một cây nhị phân có tính chất: Với mỗi giá trị trên node đang xét, giá trị của mọi node trên cây con trái luôn nhỏ hơn node đang xét và giá trị của mọi node trên cây con phải luôn lớn hơn node đang xét.

[[/uploads/bst1.png|bst1]]

**Cây Đỏ Đen** (Red-Black Tree) là một dạng **cây tìm kiếm nhị phân** (**BST**) mà sau mỗi truy vấn được thực hiện, cây tự cân bằng theo đúng tính chất của nó với độ phức tạp $O(log(N))$. CTDL **set** trong **C++** được cài đặt bằng cây đỏ đen.

[[/uploads/redblack1.png|redblack1]]

# Sparse Table

Sparse Table là cấu trúc dữ liệu được sử dụng trong [[bài toán LCA & RMQ|translate/topcoder/Range-Minimum-Query-and-Lowest-Common-Ancestor]].

Với cả 2 bài toán, Sparse Table cho phép:

- Khởi tạo với độ phức tạp: $\mathcal{O}(N\* \log{N})$.
- Trả lời truy vấn với độ phức tạp $\mathcal{O}(1)$.

# Segment Tree

Segment Tree, còn được gọi là Interval Tree trong nhiều tài liệu tiếng Việt, là cấu trúc dữ liệu cho phép thực hiện các truy vấn trên một dãy số. Segment Tree rất linh động và có thể áp dụng với nhiều loại truy vấn khác nhau, nên nó xuất hiện rất nhiều trong các kỳ thi.

Với dãy số độ dài $N$, Segment Tree cho phép thực hiện các thao tác với độ phức tạp $\mathcal{O}(\log{N})$.

Bạn có thể đọc thêm về Segment Tree [[ở đây|algo/data-structures/segment-tree-extend]].

# Fenwick

Cũng giống như Segment Tree, Fenwick tree (còn được gọi là Binary Indexed Tree) là cấu trúc dữ liệu cho phép thực hiện các truy vấn trên một dãy số:

- Ưu điểm:
    - Hằng số tự nhiên thấp hơn Segment Tree, nên chạy nhanh hơn.
    - Dùng ít bộ nhớ hơn.
    - Dễ cài đặt hơn Segment Tree
- Nhược điểm:
    - Không tổng quát bằng Segment Tree. Tất cả những bài giải được bằng Fenwick tree đều có thể giải được bằng Segment Tree. Nhưng chiều ngược lại không đúng.

Bạn có thể đọc thêm về Fenwick Tree [[ở đây|algo/data-structures/fenwick]].

# Cây Tiền Tố (Trie)

**Trie** là một cấu trúc dữ liệu dùng để quản lý một tập hợp các xâu. Trie cho phép:

- Thêm một xâu vào tập hợp, với độ phức tạp $\mathcal{O}(L)$ với $L$ là độ dài xâu cần thêm.
- Xóa một xâu khỏi tập hợp, với độ phức tạp $\mathcal{O}(L)$.
- Kiểm tra một xâu có tồn tại trong tập hợp hay không, với độ phức tạp $\mathcal{O}(L)$.

Ngoài ra trên thực tế, trie cũng rất tiết kiệm bộ nhớ khi áp dụng để lưu các từ có nghĩa, vì vậy nó là một CTDL có ứng dụng rất lớn.

Bạn có thể đọc thêm [[bài viết về trie|algo/data-structures/trie]].

# Mảng Hậu Tố (Suffix Array)

Suffix Array là một CTDL giúp sắp xếp các hậu tố của một xâu theo thứ tự từ điển. CTDL này thường được sử dụng trong các bài toán xử lý xâu.

Bạn có thể đọc thêm về Suffix Array [[ở đây|algo/data-structures/suffix-array]].

# Persistent Data Structures

Persistent Data Structures là những cấu trúc dữ liệu được dùng khi chúng ta cần có **toàn bộ lịch sử** của các thay đổi trên 1 cấu trúc dữ liệu.

Bạn có thể  đọc thêm ở: [[Persistent Data Structures|algo/data-structures/persistent-data-structures]]

# Các tài liệu tham khảo:

- [Codeforces](http://codeforces.com/blog/entry/15729)
- [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/data-structures/)
