# Ngăn xếp #

**Nguồn: [Wcipeg](http://wcipeg.com/wiki/Stack)**

# Giới thiệu

**Ngăn xếp (stack)** là cấu trúc dữ liệu chứa 0 hoặc nhiều phần tử có cùng kiểu dữ liệu. Ngăn xếp hỗ trợ hai thao tác cơ bản sau:

- *Thêm* một phần tử vào *đầu stack* **(Push)**
- *Bỏ* đi phần tử ở *đầu stack*, trả về giá trị của phần tử đó.

Về ứng dụng, ta sẽ bổ sung thêm một số thao tác sau:

- *Xây dựng* một stack rỗng **(Construct)**
- *Sao chép* stack này sang stack khác **(Copy)**
- *Lấy* phần tử ở đầu stack mà không xóa nó **(Peek)**
- *Xóa sạch* một stack có phần tủ **(Empty)**
- *Trả về* số lượng phần tử trong stack **(Find size)**
- *Kiểm tra* stack rỗng hay không **(Test empty)**

Thao tác *peek* có thể xem như *pop* phần tử đầu stack và lại *push* nó vào. Cũng như thao tác *kiểm tra* chỉ đơn giản là kiểm tra xem số lượng phần tử có trong stack có bằng 0 hay không.

[[_TOC_]]

# Thuật ngữ

Thuật ngữ *ngăn xếp* **(stack)**  dựa trên cuộc sống (một chồng sách, một chồng giấy,..). Trong khoa học máy tính, đôi khi đầu và cuối không quan trọng. Thay vào đó, từng phần tử lần lượt thêm vào stack. Phần tử thêm vào mới nhất sẽ nằm ở *đầu stack*, và phần tử cũ nhất (lấy ra cuối cùng) sẽ nằm ở *cuối stack*. Một phần tử được gọi cũ hơn phần tử khác nếu nó được *pop* sớm hơn và tương tự. *Push* là thêm phần tử, và ngược lại *pop* là xóa đi phàn tử.

# Cài đặt

## Call stack
Quá trình chạy của chương trình có thể gọi là *call stack*. Mỗi phần tử trong stack này lưu trữ tổng thể trạng thái các biến hay hàm. Khi một thủ tục gọi thủ tục khác, việc này xảy ra và đưa vào stack, khi thoát ra thì phần tử đó được xóa khỏi stack. Ví dụ, nếu thủ tục `main` gọi thủ tục `fox`, mà thủ tục này gọi tiếp chính nó, trong lúc chạy, stack này sẽ chứa quá trình chạy của `main`, `fox` và `fox`. Mỗi quá trình này chứa các đối số liên qua đến hai thủ tục, cũng như các biến toàn cục liên quan. Ở đây, phần tử trong *call stack* sẽ chứa đối số của thủ tục sâu hơn. *Call stack* được thực hiện ngầm gần như trong tất cả ngôn ngữ lập trình.
  
## Stack bình thường 
Khi thủ tục đệ quy không có, một stack được trữ tách biệt nhau trong các ô nhớ từ *call stack* bằng cách cài đặt mảng hoặc danh sách liên kiết.

## Cài đặt bằng mảng

Stack cài bằng mảng chứa dữ liệu trong các phần tử liên tiếp nhau. Thông thường, phần tử cuối stack có chỉ số nhỏ nhất (chẳng hạn 0) và ngược lại với phần tử đầu stack. Dưới đây sẽ là một cách cài đặt bằng mã giả.

```
object stack
     function construct(max_size)
          let A be an array that can hold at least max_size elements
          let top = 0
     function push(x)
          A[top]=x
          top = top + 1
     function pop
          top = top - 1
          return A[top]
     function peek
          return A[top-1]
     function size
          return top
     function make_empty
          top = 0
```

Việc thêm vào các thủ tục *sao chép, kiểm tra lỗi, kiễm tra rỗng* được lược bỏ đi nhằm mục đích ngắn gọn code.

## Cài đặt bằng danh sách liên kết
Cài đặt mảng hầu như là phương pháp tối ưu. Nhưng trong một vài trường hợp, khi số lượng phần tử không xác định được, danh sách liên kết là một cách thay thế. Mã giả như sau:

```
object stack
     function construct
          let L be an empty linked list
     function push(x)
          insert x after tail of L
     function pop
          remove tail of L, returning its data element
     function peek
          return data element at tail of L
     function size
          return size of L
     function make_empty
          empty L
```

Ta có thể dễ dàng nhận ra ở đây chỉ là các thao tác trên list. (Ở đây ta giả định rằng list bao gồm cả hàm trả về kích thước, nếu không thì ta sẽ thêm hàm trả về kích thước trong stack).

## Lớp **stack** trong C++ STL
Trong STD C++, lớp `std:stack` nằm trong tiêu đề `<stack>`, là một _cấu trúc dữ liệu_ có khả năng chứa mọi kiểu dữ liệu (**cố định**), và kiểu dữ liệu này xem được xem như một thông số mẫu. Ví dụ như `stack<char>` là một hàng đợi hai đầu chứa các ký tự. Cấu trúc dữ liệu này cho phép sử dụng các hàm sau: (lưu ý rằng `T` là kiểu dữ liệu mà hàng đợi đó lưu trữ)

1.  `void push(const T& x)`: thực hiện thao tác **push**
2.  `void pop()`: thực hiện thao tác **pop**
3.  `T& top()`: trả về giá trị đầu **stack**
4.  `size_type size()`: trả về số lượng phần tử hiện tại trong **stack**
5.  `bool empty()`: trả về giá trị `true` nếu **stack** rỗng và ngược lại, `false` nếu **stack** có phần tử.

Cấu trúc dữ liệu `stack` nên dùng bất cứ khi nào mà nó có thể; bởi sử dụng nó sẽ nhanh và ít lỗi hơn so với việc bạn tự cài đặt lại. Tuy nhiên, sẽ có lúc bạn phải cần đến các thủ tục không được hỗ trợ như ghi đè lên các phần tử trong stack. Lúc này STL `stack` không dùng được.

Lưu ý rằng thao tác pop được định nghĩa trong cấu trúc dữ liệu stack chỉ xóa đi phần tử đó nhưng không trả về giá trị của nó. Để lấy được giá trị của nó rồi xóa, ta thực hiện thao tác top trước thao tác pop.