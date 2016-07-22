[Dịch từ [Tree - PEGWiki](http://wcipeg.com/wiki/Tree)]

# Cây (Tree)
----

## Định nghĩa

**Cây** (**tree**) là một đồ thị vô hướng liên thông không có chu trình. Tập hợp các cây không giao nhau gọi là một **rừng** (**forest**).

## Tính chất

* Với một đồ thị bất kì, nếu 2 trong 3 mệnh đề sau là đúng, thì mệnh đề còn lại là đúng:

	* Đồ thị liên thông
	* Đồ thị không có chu trình
	* Số đỉnh của đồ thị lớn hơn số cạnh của đồ thị đúng 1 đơn vị

* Điều đó có nghĩa là, chỉ cần thỏa 2 trong 3 điều kiện đó thì đồ thị chắc chắn sẽ là một cây, và cây đó sẽ thỏa cả 3 điều kiện trên (trừ cây rỗng - cây không có đỉnh nào, mặc dù vậy nhưng đôi khi cũng được coi là một cây).

* Ngoài ra, nếu mỗi cặp đỉnh của đồ thị đều có chính xác 1 đường đi thì đồ thị là cây và ngược lại.

* Mọi cây đều là đồ thị phẳng ([planar graph](https://vi.wikipedia.org/wiki/%C4%90%E1%BB%93_th%E1%BB%8B_ph%E1%BA%B3ng)), nhưng không phải mọi đồ thị phẳng đều là cây.

## Các ví dụ

* **Cây có gốc** (**rooted tree**) là cây có một đỉnh cụ thể gọi là **gốc** (**root**) của cây. Một số cây không có gốc (**unroot**), có thể là do cây  không cần đỉnh nào đặc biệt để làm gốc.

	* Trong một cây hữu cơ, có một số điểm mà ở đó thân và cành cây phân nhánh. Ta coi những điểm đó, cùng với mặt đất và các điểm kết thúc của những cành cây nhỏ nhất là các **đỉnh** đồ thị, trong đó đỉnh ở mặt đất là **gốc** cây, còn thân cây và cành cây là các **cạnh** . Ý nghĩa của việc này là để thân và các cành đều được coi là xuất phát từ gốc (như cách cây mọc trong thực tế). Những đỉnh là điểm kết thúc của các cành cây nhỏ nhất, mà luôn có bậc là 1, được gọi là **lá** (**leaf**), tương tự như trong thực tế. Khoảng cách từ gốc đến các nút khác đôi khi được gọi là **chiều cao** (**height**) của nút, nhưng trong khoa học máy tính chúng ta thường vẽ cây ngược lại nên khoảng cách này thường được gọi là **độ sâu** (**depth**) của nút.  Chiều cao (độ sâu) lớn nhất trong tất cả các đỉnh của cây được gọi là chiều cao của cây (**tree's height**).

	* **Cây gia đình** (**family tree**): bao gồm tất cả hâu duệ của một cá nhân. Cây này được gọi là cây do cũng có sự tương đồng với một cây hữu cơ, và không ngạc nhiên rằng nó có thể được dùng để biểu thị sự tương đồng với cây trong lý thuyết đồ thị. Xem mỗi người trong cây gia đình là một đỉnh, và giữa 2 đỉnh có cạnh nối nếu 1 trong 2 người là **con** (**child**) của người còn lại. Gắn nhãn cá nhân đã nói ở trên là đỉnh gốc. Như vậy tất cả những người có đỉnh kề với đỉnh gốc là con của cá nhân ở trên, và cũng tương tự, những đỉnh đó gọi là con của đỉnh gốc. Tổng quát, trong một cây có gốc, nếu 2 nút kề nhau thì nút ở xa gốc hơn được coi là con của nút ở gần gốc hơn, và nút gần gốc hơn là **cha** (hoặc mẹ) (**parent**) của nút xa gốc hơn (mỗi nút sẽ có đúng 1 nút cha, trừ nút gốc). Ngoài ra, một nút $u$, cùng các con của nó, các con của các con của nó,... được gọi là các **hậu duệ** (**descendant**) của nó (đôi khi chúng ta không coi một nút là hậu duệ của chính nó). Cũng giống vậy, nút $u$, cùng cha của nó, cha của cha của nó,... gọi là các **tổ tiên** (**ancestor**) của nó (đôi khi một nút không được coi là tổ tiên của chính nó). Nút gốc là tổ tiên của tất cả các nút.

	* **Cây sự sống** (**tree of life**): mỗi đỉnh biểu diễn một giống loài và mỗi cạnh biểu diễn sự tiến hóa từ một loài sang loài khác. Gốc của cây này là tổ tiên chung của sự sống trên Trái đất, còn những lá cây là những loài còn sót lại hoặc những loài đã tuyệt chủng mà không tiến hóa thành loài khác.

	* Hệ thống quản lý nhân sự có thể biểu diễn bằng một cây có gốc, với mỗi nhân viên là một đỉnh, con của mỗi đỉnh là những nhân viên cấp dưới mà người đó trực tiếp quản lý, và giám đốc (CEO hoặc tương tự) là gốc của cây.

	* Cho một số thành phố không được nối với nhau, chúng ta muốn xây dựng một số con đường giữa các thành phố sao cho có đúng 1 đường đi giữa mỗi cặp thành phố; nếu có ít hơn 1 đường thì đảm bảo sẽ có một số thành phố không đến được nhau, còn nếu có nhiều hơn 1 đường thì sẽ là dư thừa. Từ đó mà ta sẽ xây dựng những con đường sao cho các thành phố là các đỉnh còn các con đường là các cạnh của cây. Đây là một ví dụ về cây không có gốc, bởi vì chẳng có lí do đặc biệt nào để để đánh dấu một thành phố là gốc cả.

	* Đặt song song 2 tấm gỗ gần nhau và đóng đinh vào 2 tấm gỗ đó, nhúng chúng vào nước có xà phòng và glyxerin rồi lấy ra, các tấm phim xà phòng (soap film) sẽ nối các đinh với nhau mà không hình thành chu trình ([ví dụ](https://www.youtube.com/watch?v=PI6rAOWu-Og)). Đây gọi là **cây Steiner** ([**Steiner tree**](https://en.wikipedia.org/wiki/Steiner_tree_problem)), một ví dụ nữa cho cây không có gốc vì chẳng có lí gì lại đi đặt một đỉnh bất kì làm gốc.

* Cây có hay không có gốc chỉ là do con người phân biệt, chúng ta có thể coi một cây có gốc là cây không gốc bằng cách không quan tâm nút nào là gốc nữa, và đôi khi trong thuật toán chúng ta có thể biến một cây không có gốc thành một cây có gốc bằng cách chọn một đỉnh nào đó làm gốc.

* Trong một cây có gốc, nút gốc không được coi là lá kể cả khi nó có bậc là 1 (trừ khi nó không có con, tức là cây chỉ có 1 đỉnh). Mặt khác, trong một cây không gốc, mọi đỉnh có bậc 1 được coi là lá.

* Mọi đồ thị con liên thông của một cây cũng là một cây và được gọi là **cây con** (**subtree**), nhưng trong cây có gốc thuật ngữ này thường dùng để chỉ một nút $u$ và tất cả các hâu duệ của nó, gọi là **cây con gốc $u$**. (Cây con có gốc ở gốc chính là cây ban đầu). Chúng ta sẽ sử dụng định nghĩa này trong bài viết. Cũng như những ví dụ ở trên, cây con có thể biểu diễn cho mọi thứ mọc ra từ một nhánh cây cụ thể trong cây hữu cơ, tất cả hậu duệ của một cá nhân cụ thể trong cây gia đình, hay tất cả nhân viên dưới quyền một nhân viên cụ thể trong công ty,...

## Duyệt cây (tree traversal) 

* **Duyệt cây** là việc thăm tất cả đỉnh của cây. Việc duyệt cây sẽ sản sinh ra một thứ tự duyệt cho các đỉnh của cây. Nếu một cây có $N$ đỉnh thì sẽ có $N!$ cách đánh thứ tự, nhưng có 2 cách duyệt quan trọng là duyệt theo **thứ tự trước** (**preoder**) và duyệt theo **thứ tự sau** (**postorder**). 

	* Trong cách duyệt theo thứ tự trước, chúng ta sẽ thực hiện một phép tìm kiếm theo chiều sâu (**DFS**) bắt đầu từ đỉnh gốc, mỗi nút sẽ được đánh dấu đã đi qua ngay khi nó được đưa vào stack lần đầu.

	* Phép duyệt theo thứ tự sau cũng tương tự, nhưng khác ở chỗ là một nút được coi là đã thăm ngay khi *tất cả* các nút con của nó đã được thăm (các nút lá được đánh dấu đã thăm khi chúng vừa được đưa vào stack vì chúng không có nút con). 

* Trong một số cây, một thứ tự duyệt đã được định sẵn cho con của các đỉnh, có nghĩa là, một nút có nhiều con sẽ có "con thứ nhất", "con thứ hai",... Khi đó, phép duyệt theo thứ tự trước hay sau đều duyệt con của mỗi nút theo một trình tự duy nhất.

## Cây nhị phân (binary tree) và cây k-phân (k-ary tree)

* **Cây nhị phân** (**binary tree**) là cây có gốc mà mỗi nút có *tối đa* 2 nút con, gọi là **nút con trái** (**left**) và **phải** (**right**). Cây con có gốc là nút con trái của một nút gọi là **cây con trái** (**left subtree**), **cây con phải** (**right subtree**) cũng định nghĩa tương tự. Cây nhị phân đặc biệt thú vị bởi khả năng tổ chức và quản lý dữ liệu của nó, ví dụ như trong *cây nhị phân tìm kiếm* (*binary search tree*), *heap nhị phân* (*binary heap*),...

* Một cây nhị phân được coi là có vô hạn số **tầng** (**level**), nhưng chỉ có một số tầng thường được sử dụng. Mỗi tầng của cây bao gồm tất cả các nút có cùng độ sâu. Tầng $0$ của cây chỉ bao gồm $1$ nút là gốc; tầng thứ nhất chứa những đỉnh con của gốc, như vậy tầng $1$ chứa tối đa $2$ nút; tầng thứ $2$ chứa tất cả nút cháu của nút gốc (con của con của gốc), như vậy tầng này chứa tối đa $4$ nút;... tổng quát: tầng thứ $h$ của cây nhị phân có thể chứa tới $2^{h}$ đỉnh. Nếu một cây nhị phân có chiều cao h thì số đỉnh tối đa nó có thể chứa là $1 + 2 + 4 + ... + 2^{h} = 2^{h+1} - 1$. Mặt khác, cây nhị phân có $N$ đỉnh sẽ có chiều cao ít nhất là $\left \lceil log_2 (N + 1) \right \rceil - 1$.

* Một cây nhị phân được gọi là **hoàn chỉnh** (**complete**) nếu tất cả các nút từ tầng $0$ đến tầng $h - 1$ đều được sử dụng, và tất cả các nút trên tầng $h$ đều dồn về bên trái nhiều nhất có thể. Một cây nhị phân hoàn chỉnh sẽ luôn có chiều cao *thấp nhất* có thể có. Một cây nhị phân gọi là **cân bằng** (**balance**) nếu chênh lệnh chiều cao của 2 nút lá bất kì đều không quá 1, nếu tất cả nút lá đều có cùng chiều cao thì nó được coi là **hoàn toàn cân bằng** (**perfectly balanced**). Các cây cân bằng thường được sử dụng rất hiệu quả trong việc tìm kiếm dữ liệu.

* Tổng quát, một **cây k-phân** (**k-ary tree**) là một cây có gốc mà mỗi nút có tối đa k nút con, các thuật ngữ khác định nghĩa tương tự như cây nhị phân.

### Duyệt theo thứ tự giữa (inorder traversal)

Ngoài duyệt theo thứ tự trước và sau, cây nhị phân còn có cách duyệt theo **thứ tự giữa** (**inorder traversal**). Một nút được coi là đã thăm sau khi tất cả nút thuộc cây con trái của nó được thăm và trước khi bất kì đỉnh nào thuộc cây con phải của nó được thăm. Trình tự duyệt theo thứ tự giữa là duy nhất đối với mỗi cây nhị phân, và duyệt cây nhị phân tìm kiếm theo thứ tự giữa luôn trả về một danh sách đã sắp xếp.

## Các cấu trúc dữ liệu
Các cấu trúc dữ liệu sau đều dựa trên cây có gốc, và thường là cây nhị phân:

* **Cây nhị phân tìm kiếm** ([**binary search tree**](https://vi.wikipedia.org/wiki/C%C3%A2y_t%C3%ACm_ki%E1%BA%BFm_nh%E1%BB%8B_ph%C3%A2n)): nhãn của một nút luôn không nhỏ hơn nhãn của nút con trái của nó (nếu có) và không lớn hơn nhãn của nút con phải của nó (nếu có). Cây 2-3, [2-3-4](https://vi.wikipedia.org/wiki/C%C3%A2y_2-3-4) hay [B-cây](https://vi.wikipedia.org/wiki/B-c%C3%A2y) cũng giống vậy, nhưng mỗi nút có thể có hơn 2 nút con.

* **Heap nhị phân** ([**binary heap**](https://vi.wikipedia.org/wiki/%C4%90%E1%BB%91ng_nh%E1%BB%8B_ph%C3%A2n)): một cây nhị phân hoàn chỉnh mà nhãn của mỗi nút luôn không nhỏ hơn nhãn của các nút con của nó (nếu có) (heap max, tương tự với heap min)
	* **Heap nhị thức** ([**binomial heap**](https://en.wikipedia.org/wiki/Binomial_heap)): chức năng cũng như heap nhị phân nhưng có thêm phương thức hợp 2 heap
	* [**Heap Fibonaci**](https://en.wikipedia.org/wiki/Fibonacci_heap): cũng như heap nhị thức nhưng thường nhanh hơn cả heap nhị thức

* **Cây phân đoạn** (**segment tree**, **range tree** hay [**interval tree**](https://en.wikipedia.org/wiki/Interval_tree)): một cây nhị phân quản lý một dãy, với mỗi lá biểu diễn một phần tử của dãy, và giá trị của mỗi nút khác lá là một hàm kết hợp giá trị 2 nút con của nó.

* **Cây chỉ số nhị phân** (**binary indexed tree** - [**BIT**](https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/)) hay **cây Fenwick**: cho phép tính toán và truy vấn trên các **tiền tố** (**prefix**) của dãy.

* **Cây phân tích cú pháp** ([**parse tree**](https://en.wikipedia.org/wiki/Parse_tree)): cây biểu diễn việc phân tích cú pháp của một chuỗi. Khi viết liên tiếp các ký tự trên các lá của cây từ trái sang phải thì ta được chuỗi ban đầu. Mỗi cây con quản lý một đoạn con của chuỗi, và các nút không phải là lá mang thông tin về quan hệ cú pháp giữa các đoạn con mà các nút con của nó quản lí.

* **Cây cú pháp trừu tượng** (**abstract syntax tree** - [**AST**](https://en.wikipedia.org/wiki/Abstract_syntax_tree)): cũng giống như cây phân tích cú pháp nhưng nó mang thông tin trừu tượng hơn so với cây phân tích cú pháp. Lá của nó mang những *khái niệm* (*concept*) cơ bản và các nút lưu giữ quan hệ logic hơn là quan hệ cú pháp của cây phân tích cú pháp (mối quan hệ *có nghĩa*).

* **Cây k-chiều** (**k-dimensional tree** hay [**kd-tree**](https://en.wikipedia.org/wiki/K-d_tree)): lưu trữ và quản lý các điểm thuộc không gian k-chiều.

* **Cây trie** hay **cây tiền tố** ([**prefix tree**](http://vnoi.info/library/121/4973/)): mỗi nút lưu giữ một ký tự và mỗi đường đi từ gốc đến một nút thể hiện một tiền tố của chuỗi.

* **Câu hậu tố** ([**suffix tree**](https://en.wikipedia.org/wiki/Suffix_tree)): cũng giống như trie, nhưng mỗi đường đi sẽ thể hiện một hậu tố.

## Các bài toán về cây

* **Cây khung nhỏ nhất** (**minium spanning tree**): cây $T$ gọi là **cây khung** (**span**) của đồ thị $G$ khi $T$ là đồ thị con của $G$ và chứa tất cả đỉnh của $G$. Trọng số của cây là tổng trọng số của tất cả các cạnh trên cây. Cần tìm cây khung có trọng số nhỏ nhất.
	
	* **Cây khung có kích thước nhỏ nhất** (**minimum diameter spanning tree**): tìm cây khung sao cho khoảng cách lớn nhất giữa 2 đỉnh bất kì là nhỏ nhất.
	
	* Cây khung cũng tình cờ được sinh ra trong các phép duyệt đồ thị như DFS hay BFS, tạo nên cây DFS và cây BFS. Thực hiện Dijkstra với tìm kiếm ưu tiên cho ta một **cây đường đi ngắn nhất** (**shortest paths tree**)

* **Tổ tiên chung thấp nhất** **(lowest common ancestor** - [**LCA**](https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/)): cho một cặp nút trên cây, yêu cầu tìm tổ tiên chung thấp nhất của 2 nút này, tức nút thấp nhất là tổ tiên của cả 2 nút này.

* Chúng ta có thể dễ dàng tìm khoảng cách giữa các cặp đỉnh trong cây dù có trọng số hay không trọng số bởi vì chỉ có một đường đi duy nhất, ta có thể thực hiện bằng phép duyệt DFS hay BFS
	
	* Để tìm **kích thước** (**diameter**) của một cây, ta chọn một đỉnh bắt đầu bất kì $u$, tìm đỉnh $v$ xa $u$ nhất sử dụng DFS hay BFS, rồi tìm đỉnh $w$ xa $v$ nhất. Khoảng cách giữa $v$ và $w$ là kích thước của cây.

	* Trong bài toán **truy vấn khoảng cách động** (**dynamic distance query**), chúng ta muốn tìm khoảng cách giữa các cặp nút trong cây, đồng thời ta cũng cần có thể thay đổi trọng số của các cạnh. Bài toán này có thể được giải bằng cấu trúc [**heavy-light decomposition**](http://vnoi.info/forum/5/5012/).

* Bài toán **cặp ghép cực đại** ([**maximum matching**](https://en.wikipedia.org/wiki/Matching_(graph_theory))), **tập phủ đỉnh cực đại** ([**minimum vertex cover**](https://en.wikipedia.org/wiki/Vertex_cover)), **tập phủ cạnh cực đại** ([**minimum edge cover**](https://en.wikipedia.org/wiki/Edge_cover)) và **tập độc lập cực đại** ([**maximum independent set**](https://en.wikipedia.org/wiki/Independent_set_(graph_theory))) đều nhận những lời giải quy hoạch động (dynamic programming) đơn giản khi mà đồ thị là một cây.