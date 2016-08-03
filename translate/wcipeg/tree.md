# Cây (Tree)

Nguồn: [wcipeg](http://wcipeg.com/wiki/Tree)

[[_TOC_]]

## Định nghĩa

**Cây** (**tree**) là một đồ thị vô hướng liên thông không có chu trình. Tập hợp các cây không có đỉnh chung gọi là một **rừng** (**forest**).

## Tính chất

Với một đồ thị bất kì, nếu 2 trong 3 mệnh đề sau là đúng, thì mệnh đề còn lại là đúng:

- Đồ thị liên thông
- Đồ thị không có chu trình
- Số đỉnh của đồ thị lớn hơn số cạnh của đồ thị đúng 1 đơn vị

Điều đó có nghĩa là, chỉ cần thỏa 2 trong 3 điều kiện đó thì đồ thị chắc chắn sẽ là một cây, và cây đó sẽ thỏa cả 3 điều kiện trên (trừ cây rỗng - cây không có đỉnh nào).

Ngoài ra, nếu mỗi cặp đỉnh của đồ thị đều có chính xác 1 đường đi thì đồ thị là cây và ngược lại.

Mọi cây đều là đồ thị phẳng ([planar graph](https://vi.wikipedia.org/wiki/%C4%90%E1%BB%93_th%E1%BB%8B_ph%E1%BA%B3ng)), nhưng không phải mọi đồ thị phẳng đều là cây.

## Các ví dụ:

**Cây có gốc** (**rooted tree**) là cây có một đỉnh cụ thể gọi là **gốc** (**root**) của cây. Một số cây không có gốc (**unrooted tree**), có thể là do cây không cần đỉnh nào đặc biệt để làm gốc.

- Trong một cây trong tự nhiên, có một số điểm mà ở đó thân và cành cây phân nhánh. Ta coi những điểm đó, cùng với mặt đất và các điểm kết thúc của những cành cây nhỏ nhất là các **đỉnh** đồ thị, trong đó đỉnh ở mặt đất là **gốc** cây, còn thân cây và cành cây là các **cạnh**. Ý nghĩa của việc này là để thân và các cành đều được coi là xuất phát từ gốc. Một số định nghĩa xuất phát từ ví dụ này:
    - Những đỉnh là điểm kết thúc của các cành cây nhỏ nhất, mà luôn có bậc là 1, được gọi là **lá** (**leaf**).
    - Khoảng cách từ gốc đến các đỉnh khác đôi khi được gọi là **chiều cao** (**height**) của đỉnh (trong khoa học máy tính chúng ta thường vẽ cây ngược lại nên khoảng cách này thường được gọi là **độ sâu** (**depth**) của đỉnh).
    - Chiều cao lớn nhất trong tất cả các đỉnh của cây được gọi là chiều cao của cây (**tree's height**).

- **Gia phả** (**family tree**): bao gồm tất cả hậu duệ của một người (cụ tổ). Xem mỗi người trong cây gia đình là một đỉnh, và giữa 2 đỉnh có cạnh nối nếu 1 trong 2 người là **con** (**child**) của người còn lại. Đỉnh ứng với cụ tổ là đỉnh gốc. Những đỉnh ứng với những người con của cụ tổ, được gọi là những đỉnh con của đỉnh gốc. Một số định nghĩa bắt nguồn từ ví dụ này:
    - Nếu 2 đỉnh kề nhau thì đỉnh ở xa gốc hơn được coi là con của đỉnh ở gần gốc hơn, và đỉnh gần gốc hơn là **cha** (**parent**) của đỉnh xa gốc hơn. Mỗi đỉnh có đúng 1 cha, trừ gốc.
    - Đỉnh $u$, cùng các con của nó, các con của các con của nó,... được gọi là các **hậu duệ** (**descendant**) của nó. (tùy định nghĩa, u có thể không được coi là hậu duệ của chính nó).
    - Đỉnh $u$, cùng cha của nó, cha của cha của nó,... gọi là các **tổ tiên** (**ancestor**) của nó. (tùy định nghĩa, u có thể không được coi là tổ tiên của chính nó).
    - Gốc là tổ tiên của tất cả các đỉnh.

- Cho một số thành phố không được nối với nhau, chúng ta muốn xây dựng một số con đường giữa các thành phố sao cho có đúng 1 đường đi giữa mỗi cặp thành phố. Ta sẽ xây dựng những con đường sao cho các thành phố là các đỉnh còn các con đường là các cạnh của cây. Đây là một ví dụ về cây không có gốc, bởi vì chẳng có lí do đặc biệt nào để để đánh dấu một thành phố là gốc cả.

- Đặt song song 2 tấm gỗ gần nhau và đóng đinh vào 2 tấm gỗ đó, nhúng chúng vào nước có xà phòng và glyxerin rồi lấy ra, các tấm phim xà phòng (soap film) sẽ nối các đinh với nhau mà không hình thành chu trình ([ví dụ](https://www.youtube.com/watch?v=PI6rAOWu-Og)). Đây gọi là **cây Steiner** ([**Steiner tree**](https://en.wikipedia.org/wiki/Steiner_tree_problem)), một ví dụ nữa cho cây không có gốc vì chẳng có lí gì lại đi đặt một đỉnh bất kì làm gốc.

_Một vài chú ý:_

- Ta hoàn toàn có thể coi một cây có gốc là không gốc (bằng cách không quan tâm đỉnh nào là gốc) và ngược lại, coi một cây không gốc là 1 cây có gốc (bằng cách chọn một đỉnh bất kỳ làm gốc).

- Trong một cây có gốc, gốc không được coi là lá kể cả khi nó có bậc là 1 (trừ khi cây chỉ có 1 đỉnh). Mặt khác, trong một cây không gốc, mọi đỉnh có bậc 1 được coi là lá.

- Mọi đồ thị con liên thông của một cây cũng là một cây và được gọi là **cây con** (**subtree**).

- Nếu cây có gốc, một đỉnh $u$ và tất cả các hâu duệ của nó được gọi là **cây con gốc $u$**. (Cây con có gốc ở đỉnh gốc chính là cây ban đầu).

## Cây nhị phân (binary tree) và cây k-phân (k-ary tree)

- **Cây nhị phân** (**binary tree**) là cây có gốc mà mỗi đỉnh có *tối đa* 2 con, gọi là **con trái** (**left**) và **phải** (**right**). Cây con có gốc là đỉnh con trái của một đỉnh gọi là **cây con trái** (**left subtree**). **Cây con phải** (**right subtree**) cũng định nghĩa tương tự. Cây nhị phân được sử dụng rất nhiều ví dụ như trong *cây nhị phân tìm kiếm* (*binary search tree*), [[Heap nhị phân|translate/wcipeg/Binary-Heap]],...

- Một cây nhị phân được coi là có vô hạn số **tầng** (**level**), nhưng chỉ có một số tầng thường được sử dụng. Mỗi tầng của cây bao gồm tất cả các đỉnh có cùng độ sâu. Tầng $0$ của cây chỉ bao gồm $1$ đỉnh là gốc; tầng thứ nhất chứa những đỉnh con của gốc, như vậy tầng $1$ chứa tối đa $2$ đỉnh; tầng thứ $2$ chứa tất cả đỉnh cháu của gốc (con của con của gốc), như vậy tầng này chứa tối đa $4$ đỉnh;... tổng quát: tầng thứ $h$ của cây nhị phân có thể chứa tới $2^{h}$ đỉnh. Nếu một cây nhị phân có chiều cao $h$ thì số đỉnh tối đa nó có thể chứa là $1 + 2 + 4 + ... + 2^{h} = 2^{h+1} - 1$. Mặt khác, cây nhị phân có $N$ đỉnh sẽ có chiều cao ít nhất là $\left \lceil log_2 (N + 1) \right \rceil - 1$.

- Một cây nhị phân được gọi là **hoàn chỉnh** (**complete**) nếu tất cả các đỉnh từ tầng $0$ đến tầng $h - 1$ đều được sử dụng, và tất cả các đỉnh trên tầng $h$ đều dồn về bên trái nhiều nhất có thể. Một cây nhị phân hoàn chỉnh sẽ luôn có chiều cao *thấp nhất* có thể có.

- Một cây nhị phân gọi là **cân bằng** (**balance**) nếu chênh lệnh chiều cao của 2 đỉnh lá bất kì đều không quá 1, nếu tất cả đỉnh lá đều có cùng chiều cao thì nó được coi là **hoàn toàn cân bằng** (**perfectly balanced**). Các cây cân bằng thường được sử dụng rất hiệu quả trong việc tìm kiếm dữ liệu.

- Tổng quát, một **cây k-phân** (**k-ary tree**) là một cây có gốc mà mỗi đỉnh có tối đa k con, các thuật ngữ khác định nghĩa tương tự như cây nhị phân.

## Duyệt cây (tree traversal) 

**Duyệt cây** là việc thăm tất cả đỉnh của cây. Liệt kê các đỉnh được thăm theo thứ tự, ta thu được một thứ tự duyệt cây. Nếu một cây có $N$ đỉnh thì sẽ có $N!$ thứ tự duyệt cây. Có 2 cách duyệt quan trọng là duyệt theo **thứ tự trước** (**preoder**) và duyệt theo **thứ tự sau** (**postorder**). 

### Duyệt theo thứ tự trước (preorder)

Trong cách duyệt theo thứ tự trước, chúng ta sẽ thực hiện một phép tìm kiếm theo chiều sâu (**DFS**) bắt đầu từ đỉnh gốc, mỗi đỉnh sẽ được đánh dấu đã đi qua ngay khi nó được đưa vào stack lần đầu.

```
DFS(u):
  preorder <- u
  for v in children(u):
    DFS(v)
```

### Duyệt theo thứ tự sau (postorder)

Phép duyệt theo thứ tự sau cũng tương tự, nhưng khác ở chỗ là một đỉnh được coi là đã thăm ngay khi *tất cả* các con của nó đã được thăm (các đỉnh lá được đánh dấu đã thăm khi chúng vừa được đưa vào stack vì chúng không có con). 

```
DFS(u):
  for v in children(u):
    DFS(v)
  postorder <- u
```

Ta có thể định nghĩa thứ tự cho các con của 1 đỉnh: "con thứ nhất", "con thứ hai",... Khi đó, phép duyệt theo thứ tự trước hay sau đều chỉ sinh ra một thứ tự duy nhất.

### Duyệt theo thứ tự giữa (inorder)

Ngoài duyệt theo thứ tự trước và sau, cây **nhị phân** còn có cách duyệt theo **thứ tự giữa** (**inorder traversal**). Một đỉnh được coi là đã thăm sau khi tất cả đỉnh thuộc cây con trái của nó được thăm và trước khi bất kì đỉnh nào thuộc cây con phải của nó được thăm. Trình tự duyệt theo thứ tự giữa là duy nhất đối với mỗi cây nhị phân, và duyệt cây nhị phân tìm kiếm theo thứ tự giữa luôn trả về một danh sách đã sắp xếp.

```
DFS(u)
  DFS(u.left_child)
  in_order <- u
  DFS(u.right_child)
```

## Các cấu trúc dữ liệu

Các cấu trúc dữ liệu sau đều dựa trên cây có gốc, và thường là cây nhị phân:

- **Cây nhị phân tìm kiếm** ([**binary search tree**](https://vi.wikipedia.org/wiki/C%C3%A2y_t%C3%ACm_ki%E1%BA%BFm_nh%E1%BB%8B_ph%C3%A2n)): nhãn của một đỉnh luôn không nhỏ hơn nhãn của đỉnh con trái của nó (nếu có) và không lớn hơn nhãn của đỉnh con phải của nó (nếu có). [Cây 2-3-4](https://vi.wikipedia.org/wiki/C%C3%A2y_2-3-4) hay [B-tree](https://vi.wikipedia.org/wiki/B-c%C3%A2y) cũng giống vậy, nhưng mỗi đỉnh có thể có hơn 2 con.

- **Heap** ([**binary heap**](https://vi.wikipedia.org/wiki/%C4%90%E1%BB%91ng_nh%E1%BB%8B_ph%C3%A2n)): một cây nhị phân hoàn chỉnh mà nhãn của mỗi đỉnh luôn không nhỏ hơn nhãn của các con của nó (nếu có) (heap max, tương tự với heap min)
    - [**Binomial Heap**](https://en.wikipedia.org/wiki/Binomial_heap): chức năng cũng như Heap nhị phân nhưng có thêm phương thức kết hợp 2 heap.
    - [**Fibonaci Heap**](https://en.wikipedia.org/wiki/Fibonacci_heap): cũng như Binomial Heap nhưng thường nhanh hơn cả Binomial Heap.

- **Cây phân đoạn** (**segment tree**, **range tree** hay [**interval tree**](https://en.wikipedia.org/wiki/Interval_tree)): một cây nhị phân quản lý một dãy, với mỗi lá biểu diễn một phần tử của dãy, và giá trị của mỗi đỉnh khác lá là một hàm kết hợp giá trị 2 con của nó.

- [**Binary indexed tree**](https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/)) hay **Fenwick tree**: cho phép tính toán và truy vấn trên các **tiền tố** (**prefix**) của một dãy số.

- [**Parse tree**](https://en.wikipedia.org/wiki/Parse_tree): cây biểu diễn việc phân tích cú pháp của một chuỗi. Khi viết liên tiếp các ký tự trên các lá của cây từ trái sang phải thì ta được chuỗi ban đầu. Mỗi cây con quản lý một đoạn con của chuỗi, và các đỉnh không phải là lá mang thông tin về quan hệ cú pháp giữa các đoạn con mà các con của nó quản lí.

- [**Abstract syntax tree**](https://en.wikipedia.org/wiki/Abstract_syntax_tree): cũng giống như cây phân tích cú pháp nhưng nó mang thông tin trừu tượng hơn so với cây phân tích cú pháp. Lá của nó mang những *khái niệm* (*concept*) cơ bản và các đỉnh lưu giữ quan hệ logic hơn là quan hệ cú pháp của cây phân tích cú pháp (mối quan hệ *có nghĩa*).

- **Cây kd** (**k-dimensional tree** hay [**kd-tree**](https://en.wikipedia.org/wiki/K-d_tree)): lưu trữ và quản lý các điểm thuộc không gian k-chiều.

- **Cây trie** hay **cây tiền tố** ([**prefix tree**](http://vnoi.info/library/121/4973/)): mỗi đỉnh lưu giữ một ký tự và mỗi đường đi từ gốc đến một đỉnh thể hiện một tiền tố của chuỗi.

- [**Suffix tree**](https://en.wikipedia.org/wiki/Suffix_tree): cũng giống như trie, nhưng mỗi đường đi sẽ thể hiện một hậu tố.

## Các bài toán về cây

- **Cây khung nhỏ nhất** (**minium spanning tree**): cây $T$ gọi là **cây khung** (**span**) của đồ thị $G$ khi $T$ là đồ thị con của $G$ và chứa tất cả đỉnh của $G$. Trọng số của cây là tổng trọng số của tất cả các cạnh trên cây. Cần tìm cây khung có trọng số nhỏ nhất.
    - **Cây khung nhỏ nhất** (**minimum diameter spanning tree**): tìm cây khung sao cho khoảng cách lớn nhất giữa 2 đỉnh bất kì là nhỏ nhất.
    - Cây khung cũng tình cờ được sinh ra trong các phép duyệt đồ thị như DFS hay BFS, tạo nên cây DFS và cây BFS. Dijkstra cho ta một **cây đường đi ngắn nhất** (**shortest paths tree**)

- **Tổ tiên chung gần nhất** ([**Lowest Common Ancestor - LCA**](https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/)): cho một cặp đỉnh trên cây, yêu cầu tìm tổ tiên chung thấp nhất của 2 đỉnh này, tức đỉnh thấp nhất là tổ tiên của cả 2 đỉnh này.

- Chúng ta có thể dễ dàng tìm khoảng cách giữa các cặp đỉnh trong cây dù có trọng số hay không trọng số bởi vì chỉ có một đường đi duy nhất, ta có thể thực hiện bằng phép duyệt DFS hay BFS
    - Để tìm **đường kính** (**diameter**) của một cây, ta chọn một đỉnh bắt đầu bất kì $u$, tìm đỉnh $v$ xa $u$ nhất sử dụng DFS hay BFS, rồi tìm đỉnh $w$ xa $v$ nhất. Khoảng cách giữa $v$ và $w$ là kích thước của cây.
    - Trong bài toán **dynamic distance query**, chúng ta muốn tìm khoảng cách giữa các cặp đỉnh trong cây, đồng thời ta cũng cần có thể thay đổi trọng số của các cạnh. Bài toán này có thể được giải bằng cấu trúc [**heavy-light decomposition**](http://vnoi.info/forum/5/5012/).

- Bài toán **cặp ghép cực đại** ([**maximum matching**](https://en.wikipedia.org/wiki/Matching_(graph_theory))), **tập phủ đỉnh cực đại** ([**minimum vertex cover**](https://en.wikipedia.org/wiki/Vertex_cover)), **tập phủ cạnh cực đại** ([**minimum edge cover**](https://en.wikipedia.org/wiki/Edge_cover)) và **tập độc lập cực đại** ([**maximum independent set**](https://en.wikipedia.org/wiki/Independent_set_(graph_theory))) đều nhận những lời giải quy hoạch động (dynamic programming) đơn giản khi mà đồ thị là một cây.