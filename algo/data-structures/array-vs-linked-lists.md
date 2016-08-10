# Mảng và danh sách liên kết

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

# Tài liệu tham khảo

- [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/data-structures/)
