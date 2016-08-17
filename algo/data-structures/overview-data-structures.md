# Cấu trúc dữ liệu

**Nguồn:** [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/data-structures/) 

**Tác giả:** [timmac](https://www.topcoder.com/members/timmac)

# Các cấu trúc dữ liệu đơn giản

Cấu trúc dữ liệu đơn giản nhất chính là các biến. Chúng nắm giữ duy nhất một giá trị, hơn nữa, phạm vi sử dụng có giới hạn. Khi nhiều giá trị cần lưu trữ, mảng được sử dụng.

Một khái niệm hơi khó hơn mặc dù không kém phần căn bản là con trỏ. Con trỏ thay vì giữ một giá trị, nó lại giữ một địa chỉ vùng nhớ. Hầu hết các lập trình viên dày dạn đều có hiểu biết rõ về con trỏ và rất cẩn thận khi sử dụng chúng. Trong khi rất nhiều lập trình viên hiện nay có thể không quan tâm đến kỹ năng này. Họ tìm đến các ngôn ngữ quản lý hiện đại. Những ngôn ngữ này sử dụng con trỏ ngầm. Dù thế nào, chúng ta cũng nên nắm được rằng con trỏ chỉ trỏ tới một điểm đâu đó trong bộ nhớ chứ không thực sự lưu trữ dữ liệu.
Một ví dụ ít trừu tượng hơn về con trỏ là so sánh với cách con người ghi nhớ hoặc không thể ghi nhớ một điều nào đó. Rất nhiều kỹ sư, lập trình viên giỏi không biết các công cụ hay công thức một cách cụ thể nhưng khi được hỏi họ vẫn có thể chỉ cho bạn chính xác các nguồn tài liệu để tham khảo.

# Mảng (Arrays)
Mảng là một cấu trúc dữ liệu cực kỳ đơn giản và có thể xem như một danh sách với chiều dài cố định. Mảng là một cấu trúc dữ liệu “đẹp” bởi tính đơn giản của nó. Mảng đặc biệt thích hợp cho các tình huống mà ta biết trước được số lượng phần tử hoặc có thể xác định được theo chương trình. Giả sử bạn cần một đoạn mã để tính giá trị trung bình của một vài con số. Mảng là sự lựa chọn tuyệt vời để giữ các giá trị một cách riêng rẽ bởi yêu cầu bài toán không đòi hỏi một thứ tự lưu trữ cụ thể và các phép tính toán cũng không đòi hỏi gì khác ngoài việc duyệt qua toàn bộ các phần tử. Một trong những sức mạnh khác của mảng chính là ta có thể truy cập các phần tử của mảng một cách ngẫu nhiên bằng chỉ số. Ví dụ như, bạn có một danh sách gồm tên của các học sinh trong lớp học. Mỗi học sinh đánh số từ 1 đến n khi đó để đọc hoặc lưu tên học sinh thứ i bạn chỉ cần gọi tới studentName[i].
Mảng có số lượng phần tử cố định, mỗi phần tử giữ của mảng một thông tin và ở một vị trí không đổi đã được định nghĩa trước đó.

# Danh sách liên kết (Linked Lists)
Danh sách liên kết là một cấu trúc dữ liệu có thể giữ một số lượng phần tử tùy ý và dễ dàng thay đổi kích thước, cũng như dễ dàng bỏ đi các phần tử bên trong nó. Danh sách liên kết, hiểu theo cách đơn giản nhất là một con trỏ trỏ tới một nút dữ liệu. Mỗi nút dữ liệu bao gồm dữ liệu cần chứa và một con trỏ trỏ tới nút tiếp theo. Tại điểm cuối cùng, con trỏ trỏ tới giá trị NULL.

Với thiết kế như ban đầu, một danh sách liên kết thích hợp để lưu trữ dữ liệu khi chưa biết trước được số lượng các phần tử hoặc các phần tử thường xuyên thay đổi. Tuy vậy, chúng ta không thể truy cập một cách ngẫu nhiên các phần tử của danh sách liên kết. Để tìm kiếm một giá trị, ta phải bắt đầu tại phần tử đầu tiên và duyệt tuần tự qua các phần tử cho tới khi bắt gặp được giá trị mà mình cần tìm kiếm. Để chèn một nút vào danh sách liên kết, bạn cũng phải thực hiện tương tực. Dễ dàng nhận thấy, thao tác tìm kiếm và chèn trong danh sách liên kết không thật sự hiệu quả.

Một danh sách liên kết đầy đủ thông thường sẽ có định nghĩa như dưới đây

```cpp
struct ListNode {
    int data; // dữ liệu được lưu ở nút của linked list
    ListNode* nextNode; // con trỏ trỏ tới phần tử tiếp theo của linked list.
};
ListNode* firstNode;
```

Bạn có thể chèn một nút mới vào bằng cách chèn chúng vào đầu danh sách.

```cpp
ListNode* newNode = new ListNode();
newNode->nextNode = firstNode;
firstNode = newNode;
```

Duyệt qua toàn bộ danh sách liên kết rất đơn giản như sau:

```cpp
ListNode* curNode = firstNode;
while (curNode != NULL) {
   cout << curNode->data << endl;
   curNode = curNode->nextNode;
}
```

Một cấu trúc liên quan khác chính là danh sách liên kết đôi. Điểm khác biệt so với danh sách liên kết thông thường đó là nút gốc lưu trữ con trỏ trỏ tới cả phần tử đầu tiên và cuối cùng. Mỗi nút có một liên kết đến nút liền trước và sau nó. Cấu trúc như vậy giúp ta có thể duyệt qua các phần tử theo cả hai hướng. Tuy vậy, danh sách liên kết kép vẫn có một số hạn chế nhất định.

# Hàng đợi (Queues)
Hàng đợi là cấu trúc dữ liệu diễn tả tốt nhất cho câu “vào trước, ra trước”. Một ví dụ thực tế của hàng đợi là đoàn người xếp hàng ở ngân hàng. Mỗi người khi xếp hàng sẽ được đẩy vào hàng đợi ở vị trí cuối cùng. Sau khi người ở đầu hàng hoàn thành thủ tục và rời đi, những người đang xếp ở sau sẽ được đẩy về đầu hàng.
Một trong những giải thuật phổ biến nhất thường sử dụng hàng đợi để giải quyết các bài tập ở topcoder chính là tìm kiếm theo chiều rộng (BFS). BFS duyệt tất cả trạng thái có thể tới được sau một bước. Sau đó là các trạng thái có thể đến được sau hai bước,…Hàng đợi hỗ trợ để thực hiện điều này bởi chúng lưu trữ một danh sách tất cả trạng thái đã được thăm.

Một bài toán phổ biến của dạng bài tập này chính là tìm đường đi qua mê cung. Tại điểm bắt đầu, duyệt qua tất cả các vị trí có thể đến được trong một bước duy nhất và thêm chúng vào hàng đợi. Sau đó lấy ra một vị trí, tìm tất cả các vị trí có thể đến được từ vị trí này và lại thêm chúng vào hàng đợi. Tiếp tục quá trình này cho tới khi một đường đi được tìm thấy hoặc hàng đợi rỗng (không có đường đi qua mê cung). Khi yêu cầu tìm một đường đi với số bước ít nhất, BFS kết hợp với hàng đợi là giải pháp cực kỳ hiệu quả.

Hầu hết các thư viện chuẩn, như JAVA và .NET framework đều cung cấp lớp hàng đợi và các thao tác đơn giản như thêm, lấy một phần tử ra khỏi hàng đợi.
Các bài tập dạng BFS xuất hiện thường xuyên trong các cuộc thi. Trong một vài trường hợp, xác định thành công hướng giải bằng BFS có thể rất đơn giản và nhanh chóng. Trong một số trường hợp khác thì không.

Duyệt một hàng đợi khá đơn giản. Ví dụ như, nếu bạn biết mình đang cố gắng đi từ điểm A đến điểm B trên một lưới ô vuông 50*50 (hướng đi, các chi tiết khác đều không liên quan) khi đó, sẽ có hơn 2500 trạng thái để thăm. Chương trình của bạn sẽ như sau:

```cpp
class StateNode {
   int xPos;
   int yPos;
   int moveCount;
}

class MyQueue {
   StateNode[] queueData = new StateNode[2500];
   int queueFront = 0;
   int queueBack = 0;

   void Enqueue(StateNode node) {
      queueData[queueBack] = node;
      queueBack++;
   }

   StateNode Dequeue() {
      StateNode returnValue = null;
      if (queueBack > queueFront) {
      returnValue = queueData[queueFront];
      QueueFront++;
   }
   return returnValue;
   }

   boolean isNotEmpty() {
      return (queueBack > queueFront);
   }
}
```

Khi đó đoạn code chính của bạn sẽ như bên dưới. (Nếu hàng đợi của chúng ta không đến được thêm một trạng thái nào nữa và chúng ta vẫn chưa đến được vị trí đích khi đó không có đường đi từ A đến B. Trong trường hợp này, chúng ta trả về giá trị -1).

```cpp
MyQueue queue = new MyQueue();
queue.Enqueue(initialState);
while (queue.isNotEmpty()) {
   StateNode curState = queue.Dequeue();
   if (curState == destState)
return curState.moveCount;
   for (int dir = 0; dir < 3; dir++) {
      if (CanMove(curState, dir))
         queue.Enqueue(MoveState(curState, dir));
   }
}
```

#Ngăn xếp (Stack)
Ngăn xếp có thể được xem như một định nghĩa đối nghịch với hàng đợi. Đối với ngăn xếp, “vào trước, ra trước”. Một ví dụ thực tế đối với ngăn xếp là chồng đĩa. Người rửa dọn sẽ luôn chọn đĩa trên cùng  – đây chính là đĩa được thêm vào sau cùng, sau đó đến đĩa tiếp theo.

Trông có vẻ như ngăn xếp hiếm khi được sử dụng một cách rõ ràng. Tuy vậy, hiểu biết về ngăn xếp và cách thức chúng được sử dụng ngầm hiện nay là vô cùng quan trọng. Những ai đã lập trình được một thời gian sẽ rất quen với việc ngăn xếp được sử dụng mỗi khi một chương trình con được gọi lên từ bên trong một chương trình. Tất cả các tham biến, biến địa phương đều được đặt trên ngăn xếp. Khi quá trình kết thúc, các biến này được giải phóng, địa chỉ được trả về và lấy ra khỏi ngăn xếp. Như vậy, chương trình có thể tiếp tục thực thi tiếp tục ở đúng nơi mà nó đang dừng để gọi chương trình con.

Một trong những hiểu biết quan trọng hơn với kỹ thuật này là một hàm gọi một hàm khác. Và hàm này lại tiếp tục gọi một hàm khác nữa. Với mỗi lần gọi hàm, mức độ lồng của các thực thi càng lúc càng tăng. Điều này làm kích thước của ngăn xếp càng ngày càng lớn. Một ví dụ quan trọng nhất chính là đệ quy. Khi một hàm đệ quy liên tục gọi chính nó, kích thước ngăn xếp tăng tương ứng với mỗi lần gọi đệ quy. Hầu như tất cả các lập trình viên dày dặn đều đã từng mắc lỗi viết hàm đệ quy mà không gọi giá trị trả về. Trong trường hợp đó, hàm đệ quy tự gọi chính mình cho đến khi ngăn xếp tràn và bị lỗi.

Ngăn xếp khi không được sử dụng một cách rõ ràng thì ứng dụng của nó vẫn cực kỳ lớn. Ngăn xếp chính là trái tim của thuật toán tìm kiếm theo chiều sâu (DFS).
Điển hình của duyệt cây của tìm kiếm theo chiều sâu (ví dụ như: tìm kiếm một nút cụ thể trong tài liệu XML). Ngăn xếp trong trường hợp này có trách nhiệm duy trì các con đường đã đi để chương trình có thể quay lại khi cần (ví dụ như: trở về từ một hàm đệ quy sau khi không tìm được nút mong muốn) và tiếp tục tìm kiếm các nút lân cận tiếp theo.

[Soma (SRM 198)](https://community.topcoder.com/stat?c=problem_statement&pm=2824&rd=5073) là một ví dụ tuyệt vời để tiếp cận hướng giải này.

#Cây (Trees)
Cây là một cấu trúc dữ liệu bao gồm một hoặc nhiều nút dữ liệu. Nút đầu tiên được gọi là gốc, mỗi nút không có nút con nào hoặc nhiều nút con. Số lượng con tối đa của một nút và độ sâu tối đa thường được giới hạn tùy theo từng cây.

Một trong những ví dụ dễ thấy nhất của cây là các tài liệu XML. Trên cùng của tài liệu XML là phần tử gốc. Mỗi tag có thể được xem như một nút con. Trong các tag này có thể có các nút con nữa,… Trong một cây, hệ thống phân cấp và thứ tự của các nút cũng được xác định – một phần quan trọng, không thể thiếu của cây. Một trong những ví dụ rõ hơn của cây là văn bản. Toàn bộ văn bản có thể được xem như một nút gốc. Mỗi văn bản như vậy có thể gồm các luận điểm. Mỗi luận điểm lại có các luận cứ,.. Các file được lưu trữ trên đĩa cũng tuân theo cấu trúc cây.

Cấu trúc tổ chức của một doanh nghiệp cũng có thể được xem như một cây. Trong một hệ thống phân cấp quản lý cổ điển, một chủ tịch có thể có một hoặc nhiều phó chủ tịch. Mỗi phó chủ tịch có thể có một hoặc nhiều quản lý. Mỗi quản lý lại có một vài nhân viên dưới quyền.

[PermissionTree (SRM 218)](https://community.topcoder.com/stat?c=problem_statement&pm=3093&rd=5864) là một bài tập hiếm thấy về cách tổ chức file.

[bloggoDocStructure (SRM 214)](https://community.topcoder.com/stat?c=problem_statement&pm=3025&rd=5860) là một ví dụ tốt về cách sử dụng cây.

#Cây nhị phân (Binary Trees)
Cây nhị phân là một cấu trúc cây đặc biệt. Đây là một trong những cách hiệu quả nhất để lưu trữ và đọc một tập các bảng ghi có thể đánh số bởi khóa.Ý tưởng đằng sau cây nhị phân là mỗi nút có tối đa hai nút con.

Trong hầu hết các trường hợp, giá trị ở nút bên trái nhỏ hơn giá trị nút cha và giá trị nút bên phải lớn hơn giá trị của nút cha. Dữ liệu được lưu trữ trong cây nhị phân luôn được đánh chỉ số bởi một giá trị khóa. Nhờ vậy khi duyệt cây nhị phân, bạn có thể dễ dàng phát hiện ra nút con nào cần đi với một giá trị khóa cho trước.

Một trong những lý do khiến cây nhị phân được yêu thích hơn mảng đó là các giá trị đã được sắp xếp. Độ phức tạp để tìm kiếm một giá trị cho trước trong cây nhị phân là log(N). Thêm một phần tử vào cây nhị phân cũng mất một độ phức tạp tương tự. Thao tác này khá đơn giản. Trong khi đó để thêm một phần tử vào mảng đòi hỏi bạn phải mất thời gian để tổ chức lại cấu trúc của mảng nhằm duy trì trật tự ban đầu.

Nếu bạn đã từng sử dụng sách hướng dẫn thực vật để tìm kiếm một chiếc lá nào đó, bạn sẽ hiểu được cách thức duyệt cây nhị phân. Khi mở trang đầu tiên, bạn sẽ được hỏi “chiếc là nhám hay mịn?”. Với mỗi câu trả lời bạn sẽ được dẫn tới một trang khác. Tại trang này, bạn sẽ tiếp tục nhận được các câu hỏi với hình thức tương tự để cuối cùng dẫn tới kết quả. Trong trường hợp duyệt cây nhị phân, câu hỏi mà bạn nhận được sẽ là “giá trị này lớn hơn hay bé hơn X?”

#Hàng đợi ưu tiên (Priority Queues)
Trong thuật toán BFS, hàng đợi hoạt động hiệu quả khi chúng có khả năng lưu lại các trạng thái đã qua. Nếu để đi từ vị trí này đến vị trí khác chỉ với một bước, ta chỉ việc sử dụng hàng đợi kết hợp với BFS là có thể tìm ra được phương án đi tối ưu nhất (nếu có tồn tại). Vậy nếu để đi từ trạng thái này đến trạng thái khác tốn hơn một bước thì sao?

Hãy xem xét ví dụ sau, khi bạn lái xe, bạn luôn mong muốn mình tới điểm đến nhanh nhất có thể. Trong các bài toán thông thường, mỗi bước đi lên, xuống, trái, phải, bạn đều mất thời gian là một bước. Đối với trường hợp này, BFS sẽ giải quyết hiệu quả. Nhưng sẽ ra sao nếu lái xe dọc theo hướng bạn đi sẽ mất 2 phút, trong khi sang trái, sang phải lại mất tới 3 phút. Với những loại bước đi như vậy, để đi đến một trạng thái mới không còn chỉ tốn một bước đi với chi phí cố định nữa, tính chất thứ tự đơn giản ban đầu của hàng đợi cũng vì vậy mà không thể đảm bảo nữa.

Đây chính là lúc hàng đợi ưu tiên xuất hiện. Một hàng đợi ưu tiên nhận vào các phần từ và sắp xếp chúng sao cho phần tử có chi phí nhỏ nhất được trả về đầu tiên.

Một ví dụ thực tế của hàng đợi ưu tiên chính là việc xếp hàng chờ đợi check in ở sân bay. Đa phần mọi người đều xếp hàng và chờ đến lượt gọi tên mình. Tuy vậy, những khách đi ở ghế hạng sang sẽ được ưu tiên gọi tên trước và hoàn thành thủ tục check in nhanh chóng hơn.

Một triển khai rất đơn giản của hàng đợi ưu tiên là mảng tìm kiếm lần lượt từng phần tử một cho đến khi tìm ra phần tử nhỏ nhất trong nó, phần tử mới được thêm vào cuối mảng. Một biểu diễn như vậy sẽ giúp thao tác chèn thêm có độ phức tạp nhỏ hơn	 nhưng thao tác lấy phần tử ra sẽ mất rất nhiều thời gian.
Một loại cây nhị phân đặc biệt được gọi là heap thường được sử dụng để cài đặt cho hàng đợi ưu tiên. Trong heap, giá trị của nút gốc luôn ít hơn hoặc nhiều hơn (tùy thuộc vào định nghĩa độ ưu tiên của bạn) so với tất cả các nút con của nó. Thêm vào đó, heap là một cây nhị phân hoàn chỉnh. Một định nghĩa đơn giản của cây hoàn chỉnh đó là các nút của cây của một nhánh sẽ không bao giờ đạt tới độ sâu n + 1 trừ khi tất cả các nhánh của cây đã đạt tới độ sâu n. Nút trái ngoài cùng sẽ luôn được thực hiện trước.

Để lấy một giá trị từ heap, nút gốc được lấy ra. Nút phải nhất với độ sâu lớn nhất trở thành nút gốc. Nếu nút gốc mới lớn hơn ít nhất một nút con của nó, khi đó, nút gốc sẽ được tráo đổi với nút con nhỏ hơn đó, để đảm bảo là nút gốc luôn nhỏ hơn các nút con của nó. Thao tác này tiếp tục thực hiện khi vẫn còn cần thiết. Thêm giá trị vào heap là một quá trình ngược lại. Giá trị mới được thêm vào ở nút lá và hoán đổi lên cho tới khi thỏa tính chất của heap.
Một trong những tính chất cực kỳ tiện lợi của cây đầy đủ là chúng có thể được lưu trữ như mảng bình thường. Phần tử 0 là gốc của cây, phần tử 2k + 1 và 2k + 2 là con của phần tử k. Nhờ vậy việc thêm một nút vào cây sẽ tương tự với việc thêm một phần tử vào mảng.

#Bảng băm (Hash Tables)
Bảng băm là một cấu trúc dữ liệu đặc biệt thường được sử dụng như một từ điển. Trong đó, mỗi khóa mang theo một giá trị tương ứng. Khóa được xem như chỉ số của giá trị tương ứng. Bảng băm không như các loại từ điển cổ điển – mọi người có thể tìm được khóa thông qua giá trị của nó.

Không may, không phải tất cả các kiểu dữ liệu đều có thể sắp xếp vào một từ điển đơn giản. Đây chính là lúc mà quá trình băm (hash) ra đời. Hash là quá trình khởi tạo một giá trị khóa (thường là 32 bit hoặc 64 bit) từ một mảnh dữ liệu. Giá trị hash này sẽ giúp việc sắp xếp trở nên đơn giản hơn. Giá trị hash có thể là n bit đầu tiên của dữ liệu, n bit cuối cùng, giá trị mod hoặc là kết quả của một hàm phức tạp. Sử dụng các giá trị hash, ta có thể cài đặt các hash buckets để lưu trữ dữ liệu. Nếu các giá trị hash được phân bố đều, các buckets sẽ được điền vào một cách đồng đều. Trong một vài trường hợp, các buckets không có hoặc chỉ có một vài đối tượng trong chúng. Điều này làm cho việc tìm kiếm còn nhanh hơn nữa.

Trường hợp một hash bucket chứa nhiều hơn một giá trị ta gọi đó là va chạm. Việc xử lý  va chạm rất quan trọng đối với hiệu năng của bảng băm. Một trong những phương pháp đơn giản nhất là cài đặt các danh sách liên kết ở hash bucket. Khi đó, mỗi phần tử cùng giá trị hash có thể kết lại với nhau tại một điểm.Một số cách làm phức tạp hơn như: sử dụng liền kề, hash một lần nữa để có giá trị hash mới,… Như thường lệ, mỗi cách làm đều có những điểm tốt, xấu về mặt hiệu suất.

Một ví dụ đơn giản khác của hash table chính là hệ thống số thập phân Dewey – được sử dụng trong rất nhiều thư viện. Tất cả các sách đều được đăng ký một số tương ứng dựa vào chủ đề của nó chẳng hạn như những số gần 500 là các sách khoa học, gần 700 là sách nghệ thuật. Như một bảng hash thật sự, tốc độ của để người đọc tìm ra quyển sách sẽ dựa vào các hash bucket có thật sự được phân chia tốt. Chúng ta sẽ phải mất nhiều thời gian hơn để tìm một quyển sách về sương mù trong một thư viện sách khoa học so với một thư viện sách văn học cổ điển.

Trong phát triển ứng dụng, bảng hash thuận tiện để lưu trữ dữ liệu tham khảo, chẳng hạn như chữ viết tắt tên đầy đủ của các tổ chức. Trong giải quyết bài toán, bảng hash thật sự hữu ích để tiếp cận hướng giải quyết chia để trị cho bài toán cái túi (knapsack-type).

Giả sử, chúng ta được yêu cầu tìm một số lượng ống nhỏ nhất để xây dựng một đường ống với chiều dài cố định và chúng ta có 38 ống. Bằng cách chia thành hai tập – 19 và tính toán tất cả trường hợp ghép ống có thể ở mỗi tập, chúng ta tạo ra một bảng hash kết nối giữa độ dài mà các tổ hợp ống tạo thành với số lượng ống ít nhất cần dùng. Sau đó, với mỗi tổ hợp ống được xây dựng trong một tập, chúng ta có thể tra cứu liệu có tồn tại đường ống với độ dài phù hợp ở tập bên kia để cả hai ống tạo nên một đường ống với độ dài yêu cầu với số ống là ít nhất.

#Kết luận

Một góc nhìn rộng hơn, cấu trúc dữ liệu chỉ là một tập hợp các công cụ khác trong bộ đồ nghề của một lập trình viên dày dặn kinh nghiệm. Các thư viện toàn diện hiện nay và frameworks có sẵn hỗ trợ nhiều ngôn ngữ đã giúp cho lập trình viên tránh đi việc phải hiểu biết đầy đủ với cấu trúc dữ liệu. Kết quả là các nhà phát triển đã có thể đưa ra các giải pháp nhanh và chất lượng hơn nhờ vào việc tận dụng những công cụ này. Thách thức đối với các nhà phát triển là lựa chọn cấu trúc dữ liệu nào để sử dụng cho phù hợp.
Tuy nhiên, việc biết một chút về cách thức vận hành của các công cụ này sẽ giúp việc lựa chọn dễ dàng hơn. Hoặc khi có nhu cầu, giải một bài toán với lời giải tốt hơn cho khách hàng hoặc để kiếm 1000 điểm trong 45 phút trong các cuộc thi SRM tiếp theo, bạn cũng sẽ cần tới chúng.
