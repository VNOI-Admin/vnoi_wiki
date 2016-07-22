[Bài viết chưa hoàn thiện]

# Cây (Tree)
----

## Định nghĩa

**Cây** (**tree**) là một đồ thị vô hướng liên thông không có chu trình. Tập hợp các cây không giao nhau gọi là một **rừng** (**forest**).

## Tính chất

* Với một đồ thị bất kì, nếu 2 trong 3 mệnh đề sau là đúng, thì mệnh đề còn lại là đúng:

	*  Đồ thị liên thông
	* Đồ thị không có chu trình
	* Số đỉnh của đồ thị lớn hơn số cạnh của đồ thị đúng 1 đơn vị

* Điều đó có nghĩa là, chỉ cần thỏa 2 trong 3 điều kiện đó thì đồ thị chắc chắn sẽ là một cây, và cây đó sẽ thỏa cả 3 điều kiện trên (trừ cây rỗng - cây không có đỉnh nào, mặc dù vậy nhưng đôi khi cũng được coi là một cây).

* Ngoài ra, nếu mỗi cặp đỉnh của đồ thị đều có chính xác 1 đường đi thì đồ thị là cây và ngược lại.

* Mọi cây đều là đồ thị phẳng ([planar graph](https://vi.wikipedia.org/wiki/%C4%90%E1%BB%93_th%E1%BB%8B_ph%E1%BA%B3ng)), nhưng không phải mọi đồ thị phẳng đều là cây.

## Các ví dụ

* **Cây có gốc** (**rooted tree**) là cây có một đỉnh cụ thể gọi là **gốc** (root****) của cây. Một số cây không có gốc (**unroot**), có thể là do cây  không cần đỉnh nào đặc biệt để làm gốc.

	* Trong một cây hữu cơ, có một số điểm mà ở đó thân và cành cây phân nhánh. Ta coi những điểm đó, cùng với mặt đất và các điểm kết thúc của những cành cây nhỏ nhất là các **đỉnh** đồ thị, trong đó đỉnh ở mặt đất là **gốc** cây, còn thân cây và cành cây là các **cạnh** . Ý nghĩa của việc này là để thân và các cành đều được coi là xuất phát từ gốc (như cách cây mọc trong thực tế). Những đỉnh là điểm kết thúc của các cành cây nhỏ nhất, mà luôn có bậc là 1, được gọi là **lá** (**leaf**), tương tự như trong thực tế. Khoảng cách từ gốc đến các nút khác đôi khi được gọi là chiều cao (height) của nút, nhưng trong khoa học máy tính chúng ta thường vẽ cây ngược lại nên khoảng cách này thường được gọi là **độ sâu** (**depth**) của nút.  Chiều cao (độ sâu) lớn nhất trong tất cả các đỉnh của cây được gọi là chiều cao của cây (**tree's height**).

	* **Cây gia đình** (**family tree**): bao gồm tất cả hâu duệ của một cá nhân. Cây này được gọi là cây do cũng có sự tương đồng với một cây hữu cơ, và không ngạc nhiên rằng nó có thể được dùng để biểu thị sự tương đồng với cây trong lý thuyết đồ thị. Xem mỗi người trong cây gia đình là một đỉnh, và giữa 2 đỉnh có cạnh nối nếu 1 trong 2 người là **con** (**child**) của người còn lại. Gắn nhãn cá nhân đã nói ở trên là đỉnh gốc. Như vậy tất cả những người có đỉnh kề với đỉnh gốc là con của cá nhân ở trên, và cũng tương tự, những đỉnh đó gọi là con của đỉnh gốc. Tổng quát, trong một cây có gốc, nếu 2 nút kề nhau thì nút ở xa gốc hơn được coi là con của nút ở gần gốc hơn, và nút gần gốc hơn là **cha** (hoặc mẹ) (**parent**) của nút xa gốc hơn (mỗi nút sẽ có đúng 1 nút cha, trừ nút gốc). Ngoài ra, một nút u, cùng các con của nó, các con của các con của nó,... được gọi là các hậu duệ (descendant) của nó (đôi khi chúng ta không coi một nút là hậu duệ của chính nó). Cũng giống vậy, nút u, cùng cha của nó, cha của cha của nó,... gọi là các tổ tiên (ancestor) của nó (đôi khi một nút không được coi là tổ tiên của chính nó). Nút gốc là tổ tiên của tất cả các nút.

	* Cây sự sống (tree of life), mỗi đỉnh biểu diễn một giống loài và mỗi cạnh biểu diễn sự tiến hóa từ một loài sang loài khác. Gốc của cây này là một tổ tiên chung của sự sống trên Trái đất, còn những lá cây là những loài còn sót lại hoặc những loài đã tuyệt chủng mà không chuyển hóa thành loài khác.

	* Hệ thống quản lý nhân sự có thể biểu diễn bằng một cây có gốc, với mỗi nhân viên là một đỉnh, con của mỗi đỉnh là những nhân viên cấp dưới mà người đó quản lý, và giám đốc (CEO hoặc tương tự) là gốc của cây.

	* Cho một số thành phố không được nối với nhau, chúng ta muốn xây dựng một số con đường giữa các thành phố sao cho có đúng 1 đường đi giữa mỗi cặp thành phố; nếu có ít hơn 1 đường thì đảm bảo sẽ có một số thành phố không đến được nhau, còn nếu có nhiều hơn 1 đường thì sẽ dư thừa. Từ đó chúng ta sẽ xây dựng những con đường sao cho các thành phố là các đỉnh và các con đường là các cạnh của cây. Đây là một ví dụ về câ không có gốc bởi vì chẳng có lí do đặc biệt nào để để đánh dấu một thành phố là gốc.

	* Đặt song song 2 tấm gỗ gần nhau và đóng đinh vào 2 tấm gỗ đó, rồi nhúng vào nước có xà phòng và glyxerin rồi lấy ra, xà phòng sẽ nối các đinh với nhau mà không hình thành chu trình ([ví dụ](https://www.youtube.com/watch?v=PI6rAOWu-Og)). Đây gọi là cây Steiner (Steiner tree), một ví dụ nữa cho cây không có gốc vì chẳng có lí gì lại đi đặt một đỉnh bất kì làm gốc.

* Cây có hay không có gốc chỉ là do con người phân biệt, chúng ta có thể coi một cây có gốc là cây không gốc bằng cách không quan tâm nút nào là gốc nữa, và đôi khi, trong thuật toán chúng ta có thể biến một cây không có gốc thành một cây có gốc bằng cách chọn một đỉnh nào đó làm gốc.

* Trong một cây có gốc, nút gốc không được coi là lá kể cả khi nó có bậc là 1 (trừ khi nó không có con, tức là nó là đỉnh duy nhất trong cây). Mặt khác, trong một cây không gốc, mọi đỉnh có bậc 1 được coi là lá.

* Mọi đồ thị con liên thông của một cây cũng là một cây và được gọi là cây con (subtree), nhưng trong cây có gốc thuật ngữ này thường dùng để chỉ một nút u và tất cả các hâu duệ của nó, gọi là cây con gốc u (cây con có gốc ở gốc chính là cây ban đầu). Chúng ta sẽ sử dụng định nghĩa này trong bài viết. Cũng như những ví dụ ở trên, cây con có thể biểu diễn cho mọi thứ mọc từ một nhánh cây cụ thể trong cây hữu cơ, tất cả hâu duệ của một cá nhân cụ thể trong cây gia đình, hay tất cả nhân viên dưới quyền một nhân viên cụ thể trong công ty,...

## Duyệt cây (tree traversal) 

Duyệt cây là việc thăm tất cả đỉnh của cây. Việc duyệt cây sẽ sản sinh ra một thứ tự duyệt cho các đỉnh của cây. Nếu một cây có N đỉnh thì sẽ có N! cách đánh thứ tự, nhưng có 2 cách duyệt quan trọng là duyệt theo thứ tự trước (preoder) và duyệt theo thứ tự sau (postorder). 

Trong cách duyệt theo thứ tự trước, chúng ta sẽ thực hiện một phép tìm kiếm theo chiều sâu (dfs) bắt đầu từ đỉnh gốc, mỗi nút sẽ được đánh dấu đã đi qua ngay khi nó được đưa vào stack lần đầu.

Phép duyệt theo thứ tự sau cũng tương tự, nhưng khác ở chỗ là một nút được coi là đã thăm ngay khi tất cả các nút con của nó đã được thăm (các nút lá được đánh dấu đã thăm khi chúng vừa được đưa vào stack vì chúng không có con). 

Trong một số cây, một thứ tự duyệt đã được định sẵn cho con của mọi đỉnh, có nghĩa là, một nút có nhiều con sẽ có "con thứ nhất", "con thứ hai",... Khi đó, phép duyệt theo thứ tự trước hay sau đều duyệt con của mỗi nút theo một trình tự duy nhất đối.

## Cây nhị phân (binary tree) và cây k-phân (k-ary tree)

Cây nhị phân là cây có gốc mà mỗi nút có tối đa 2 nút con, gọi là nút con trái (left) và phải (right). Cây con có gốc là nút con trái của một nút gọi là cây con trái (left subtree), cây con phải (right subtree) cũng định nghĩa tương tự. Cây nhị phân đặc biệt thú vị bởi khả năng tổ chức và quản lý dữ liệu của nó, như trong cây nhị phân tìm kiếm (binary search tree), heap nhị phân (binary heap).

Một cây nhị phân được coi là có vô hạn số tầng, nhưng chỉ có một số tầng thường được sử dụng. Mỗi tầng của cây bao gồm tất cả các nút có cùng độ sâu. Tầng 0 của cây chỉ bao gồm 1 nút là gốc; tầng thứ nhất chứa những đỉnh con của gốc, như vậy tầng 1 chứa tối đa 2 nút; tầng thứ 2 chứa tất cả nút cháu của nút gốc (con của con của gốc), như vậy tầng này chứa tối đa 4 nút;... tổng quát: tầng thứ h của cây nhị phân có thể chứa tới $2^{h}$ đỉnh. Nếu một cây nhị phân có chiều cao h thì số đỉnh tối đa nó có thể chứa là $1 + 2 + 4 + ... + 2^{h} = 2^{h+1} - 1$. Ngược lại, cây nhị phân có N đỉnh sẽ có chiều cao ít nhất là $\left \lceil log_2 N \right \rceil - 1$