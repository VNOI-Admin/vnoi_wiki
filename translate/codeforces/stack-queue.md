# Queue & Stack

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


# Ngăn xếp (Stack)
Ngăn xếp có thể được xem như một định nghĩa đối nghịch với hàng đợi. Đối với ngăn xếp, “vào trước, ra trước”. Một ví dụ thực tế đối với ngăn xếp là chồng đĩa. Người rửa dọn sẽ luôn chọn đĩa trên cùng  – đây chính là đĩa được thêm vào sau cùng, sau đó đến đĩa tiếp theo.

Trông có vẻ như ngăn xếp hiếm khi được sử dụng một cách rõ ràng. Tuy vậy, hiểu biết về ngăn xếp và cách thức chúng được sử dụng ngầm hiện nay là vô cùng quan trọng. Những ai đã lập trình được một thời gian sẽ rất quen với việc ngăn xếp được sử dụng mỗi khi một chương trình con được gọi lên từ bên trong một chương trình. Tất cả các tham biến, biến địa phương đều được đặt trên ngăn xếp. Khi quá trình kết thúc, các biến này được giải phóng, địa chỉ được trả về và lấy ra khỏi ngăn xếp. Như vậy, chương trình có thể tiếp tục thực thi tiếp tục ở đúng nơi mà nó đang dừng để gọi chương trình con.

Một trong những hiểu biết quan trọng hơn với kỹ thuật này là một hàm gọi một hàm khác. Và hàm này lại tiếp tục gọi một hàm khác nữa. Với mỗi lần gọi hàm, mức độ lồng của các thực thi càng lúc càng tăng. Điều này làm kích thước của ngăn xếp càng ngày càng lớn. Một ví dụ quan trọng nhất chính là đệ quy. Khi một hàm đệ quy liên tục gọi chính nó, kích thước ngăn xếp tăng tương ứng với mỗi lần gọi đệ quy. Hầu như tất cả các lập trình viên dày dặn đều đã từng mắc lỗi viết hàm đệ quy mà không gọi giá trị trả về. Trong trường hợp đó, hàm đệ quy tự gọi chính mình cho đến khi ngăn xếp tràn và bị lỗi.

Ngăn xếp khi không được sử dụng một cách rõ ràng thì ứng dụng của nó vẫn cực kỳ lớn. Ngăn xếp chính là trái tim của thuật toán tìm kiếm theo chiều sâu (DFS).
Điển hình của duyệt cây của tìm kiếm theo chiều sâu (ví dụ như: tìm kiếm một nút cụ thể trong tài liệu XML). Ngăn xếp trong trường hợp này có trách nhiệm duy trì các con đường đã đi để chương trình có thể quay lại khi cần (ví dụ như: trở về từ một hàm đệ quy sau khi không tìm được nút mong muốn) và tiếp tục tìm kiếm các nút lân cận tiếp theo.

[Soma (SRM 198)](https://community.topcoder.com/stat?c=problem_statement&pm=2824&rd=5073) là một ví dụ tuyệt vời để tiếp cận hướng giải này.

# Tài liệu tham khảo:

- [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/data-structures/)
