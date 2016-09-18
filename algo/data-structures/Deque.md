# Deque - hàng đợi hai đầu

**Hàng đợi hai đầu** (**deque**) là cấu trúc dữ liệu chứa 0 hoặc nhiều phần tử có cùng kiểu dữ liệu và được biểu diễn bằng một hàng có phần tử _đầu_ (**front**) và phần tử _cuối_ (**last**). **Deque** hỗ trợ 4 thao tác như sau:

  - _Thêm_ một phần tử vào _cuối deque_. **(Push back)**
  - _Thêm_ một phần tử vào _đầu deque_. **(Push front)**
  - _Bỏ_ đi phần tử ở _cuối deque_, trả về giá trị của phần tử đó. **(Pop back)**
  - _Bỏ_ đi phần tử ở _đầu deque_, trả về giá trị của phần tử đó. **(Pop front)**

Về ứng dụng, ta sẽ bổ sung thêm một số thao tác sau:
  
  - _Xây dưng_ một deque rỗng. **(Construct)**
  - _Sao chép_ deque này sang một deque khác. **(Copy)**
  - _Lấy giá trị_ của phần tử cuối mà không xóa nó. **(Peek back)**
  - _Lấy giá trị_ của phần tử đầu mà không xóa nó. **(Peek front)**
  - _Xóa sạch_ một deque đang có phần tử. **(Empty)**
  - _Tìm số lượng phần tử_ trong deque. **(Find size)**
  - _Kiểm tra_ xem deque có rỗng hay không. **(Test empty)**

Hai thao tác _lấy giá trị_ thật sự không cần thiết, bởi _lấy giá trị phần tử đầu_ deque **(peek front)** tương đương với việc xóa đi phần tử đó **(pop front)** rồi lại thêm nó vào **(push front)**, và tương tự với _lấy giá trị phần tử cuối_ **(peek last)**. Cũng như  _kiểm tra rỗng_ **(Test empty)** thật ra cũng chỉ là _kiểm tra xem số lượng phần tử_ của deque có bằng 0 hay không.

[[_TOC_]]

# Thuật ngữ

Thuật ngữ **deque** là cách gọn ngắn tắt của _double-ended queue_ (hàng đợi hai đầu). Sở dĩ là vì nó có thể thêm, bớt phần tử ở cả hai đầu; còn thuật ngữ **queue** ở đây là một lớp cấu trúc dữ liệu cho phép thêm, bớt phần tử (nhưng không thể tìm kiếm). Một phần tử được xem là **đứng trước** một phần tử khác nếu nó gần với phần tử đầu (**front**) hơn là phần tử còn lại; ngược, lại, một phần tử được xem là **đứng sau** một phần tử khác nếu nó xa với phần tử đầu (**front**) hơn là phần tử còn lại. **Push** một phần tử là thêm phần tử đó vào hàng đợi, **pop** đẩy ra một phần tử. Lưu ý rằng _điểm đầu_ (**front**) và _điểm cuối_ (**last**) là tương đương nhau, khi thay đổi toàn bộ điểm cuối và đầu trong giải thuật của chúng ta thì nó vẫn hoạt động tương tự như trước đó.

# Cài đặt

## Cài đặt bằng mảng

- Khi sử dụng mảng để biển diễn **deque**, thì giá trị của **deque** sẽ được lưu giữ bằng những phần tử liên tiếp trong mảng. Tuy nhiên, đối vấn cách cài đặt này, thì nếu ta muốn đặt phần tử có _chỉ số thấp nhất_ (**front**) luôn luôn cố định ở một chỉ số (ví dụ $0$ hoặc $1$), hay nói cách khác, chỉ số thấp nhất luôn là cố định thì: Khi ta muốn **pop front** (thêm phần tử phía trước vào đầu hàng đợi), ta sẽ phải tịnh tiến toàn bộ các phần tử về bên trái sao cho phần tử có _chỉ số thấp nhất_ (**front**) sẽ lưu giá trị của phần tử _tiếp theo_ (**next**) và tương tự với các phần tử còn lại. Cũng như đối với việc **push front** (thêm phần tử vào đầu hàng đợi), toàn bộ những phần tử hiện tại trong **deque** sẽ phải tịnh tiến về bên phải để phần tử _chỉ số thấp nhất_ (**front**) sẽ lưu giá trị của phần tử vừa thêm vào, trong khi các phần tử còn lại sẽ lưu phần tử _đứng trước_. Thế nên, với cách cài đặt thế này, mỗi thao tác thực hiện sẽ tốn chi phí là **$O(n)$** - với $n$ là số lượng phần tử hiện đang có của **deque**. 

- Tuy nhiên, để có thể thực hiện một số thuật toán quan trọng như [BFS](http://wcipeg.com/wiki/Breadth-first_search) trong _thời gian tuyến tính_, các thao tác **push, pop** phải được thực hiện với chi phí là **$O(1)$**. Đối với vấn đề này, thay vì phải thay thế phần tử bị **pop**, ta chỉ đơn thuần _thay đổi chỉ số_ của **front**, và khi **push** vào một phần tử, ta chỉ cần gán phần tử vào _chỉ số liền kề_ với phần tử đứng đầu và _thay đổi chỉ số_ của phần tử đầu. Tức là, ta chỉ cần quan tâm đến hai chỉ số của mảng, _đầu_ (**front**) và _cuối_ (**back**). Khi ta thêm một phần tử vào đầu (**push front**), ta chỉ cần giảm _chỉ số đầu_ (**front index**) rồi gán phần tử ấy vào chỉ số mới. Ngược lại khi ta thêm một phần tử vào cuối (**push back**), ta chỉ cần tăng _chỉ số đầu_ (**back index**) rồi gán phần tử ấy vào. Còn khi ta ta xóa một phần tử ở đầu (**pop front**), ta chỉ việc _tăng chỉ số đầu_, còn xóa phần tử ở cuối (**pop back**) thì ta sẽ _giảm chỉ số cuối_.

- Hãy thử nghĩ xem, trong trường hợp ta thêm một phần tử vào đầu (**push front**), rồi lại xóa đi phần tử cuối (**pop back**), rồi thêm lại phần tử đầu (**push front**), ... Tiếp tục như vậy, **deque** mà ta xây dựng vẫn luôn luôn chỉ có tối đa một phần tử, thế nhưng hai _chỉ số đầu_ và _chỉ số cuối_ lại tăng lên liên tục dẫn tới việc bị tràn giới hạn mảng. Để khắc phục vấn đề này, ta sẽ cho phép các chỉ số được _xoay vòng_ (**hàng đợi hai đầu xoay vòng**). Thế nên, khi tăng **chỉ số cực hạn** lên, ta sẽ nhận được **chỉ số cực tiểu** và ngược lại, khi giảm **chỉ số cực tiểu** ta sẽ nhận được **chỉ số cực đại**. Việc này được thực hiện bằng cách sử dụng toán tử _mod_ (**modulo** - %). Dưới đây sẽ là một cách cài đặt mẫu bằng mã giả:

``` 
cấu trúc deque
     thủ tục construct(max_size)
          gán A là một mảng có tối đa max_size+1 phần tử
          gán N = max_size+1
          gán first = 0
          gán last = 0
     thủ tục push_front(x)
          first = (first - 1) mod N
          A[first] = x
     thủ tục push_back(x)
          A[last] = x
          last = (last + 1) mod N
     hàm pop_front
          return_val = A[first]
          first = (first + 1) mod N
          trả về return_val
     hàm pop_back
          last = (last - 1) mod N
          trả về A[last]
     hàm peek_front
          trả về A[first]
     hàm peek_back
          trả về A[(last-1) mod N]
     hàm size
          trả về (last-first) mod N
     thủ tục make_empty
          last = first
```

- Lưu ý rằng, nếu **deque** đã đầy rồi nhưng ta vẫn **push** thêm các phần tử vào thì kích thước của **deque** lúc này sẽ là $0$, và một số phần tử cũ sẽ bị ghi đè lên bằng các phần tử mới. Ngoài ra, khi kích thước của deque là $0$ nhưng ta lại muốn xóa đi phần tử thì lúc này, kích thước của **deque** sẽ là cực đại. Việc thêm vào các đoạn mã _kiểm tra lỗi_, _kiểm tra rỗng_ và _copy_ **deque** được lược bỏ đi nhằm mục đích ngắn gọn code.

## Cài đặt bằng danh sách liên kết

- Cài đặt bằng mảng xoay vòng hầu như đã là phương pháp tối ưu, tuy nhiên trong một vài trường hợp, khi mà số lượng phần tử cần không thể xác định được, lúc này ta sẽ sử dụng _danh sách liên kết_ (**linked list**) để biểu diễn **deque**. Chi tiết cho cách cài đặt này được mô tả bằng đoạn mã giả như sau:

```
cấu trúc deque
     thủ tục construct
          gán L là một danh sách rỗng
     thủ tục push_front(x)
          chèn x vào đầu của L
     thủ tục push_back(x)
          chèn x vào cuối L
     hàm pop_front
          xóa phần tử đầu của L, trả về giá trị của phần tử đó
     hàm pop_back
          xóa phần tử cuối của L, trả về giá trị của phần tử đó 
     hàm peek_front
          trả về giá trị của phần tử đầu L
     hàm peek_back
          trả về giá trị của phần tử cuối L
     hàm size
          trả về kích thước của L
     thủ tục make_empty
          làm rỗng L
```

- Ta có thể dễ dàng nhận ra, **deque** đơn thuần chỉ là chứa các thao tác của **list** sẵn có. (Ở đây ta giả định rằng **list** bao gồm cả hàm trả về kích thước, nếu không thì ta sẽ thêm hàm trả về kích thước trong **deque**).


## Lớp **deque** trong STD C++
- Trong STD C++, lớp `deque` nằm trong tiêu đề `<deque>`, là một _cấu trúc dữ liệu_ có khả năng chứa mọi kiểu dữ liệu (**cố định**), và kiểu dữ liệu này xem được xem như một thông số mẫu. Do đó, ví dụ như `deque<char>` là một hàng đợi hai đầu chứa các ký tự. Cấu trúc dữ liệu này cho phép sử dụng các hàm sau: (lưu ý rằng `T` là kiểu dữ liệu mà hàng đợi đó lưu trữ)

1.  `void push_front(const T& x)`: thêm x vào đầu **deque**.
2.  `void push_back(const T& x)`: thêm x vào cuối **deque**.
3.  `void pop_front()`: xóa phần tử đầu khỏi **deque**.
4.  `void pop_back()`: xóa phần tử cuối khỏi **deque**.
5.  `T& front()`: trả về giá trị đầu **deque**.
6.  `T& back()`: trả về giá trị cuối **deque**.
7.  `size_type size()`: trả về số lượng phần tử hiện tại trong **deque**.
8.  `bool empty()`: trả về giá trị `true` nếu **deque** rỗng và ngược lại, `false` nếu **deque** có phần tử.
9.  `void clear()`: xóa toàn bộ phần tử trong **deque**.

- Ngoài ra, không giống như cấu trúc dữ liệu STD `queue` và `stack`, cấu trúc dữ liệu `deque` lưu địa chỉ của các phần tử một cách ngẫu nhiên: do đó, D[0] sẽ đại diện cho phần tử đứng đầu D, và tương tự như thế với các phần tử tiếp theo.

- Cấu trúc dữ liệu `deque` nên dùng bất cứ khi nào mà nó có thể chứ đủ các phần tử cần thiết; bởi sử dụng nó sẽ nhanh và ít lỗi hơn so với việc bạn tự cài đặt lại. Trong khi đó, hầu như bạn không bao giờ phải đối mặt với một vấn đề gì mà STD `deque` vẫn không chạy đủ nhanh.

- Lưu ý rằng thao tác `pop` được định nghĩa trong cấu trúc dữ liệu `deque` chỉ xóa đi phần tử đó nhưng không trả về giá trị của nó. Để lấy được giá trị của nó rồi xóa, ta sẽ thực hiện cả hai thao tác gọi `front` hoặc `back` và sau đó thì `pop_front` hoặc `pop_back`.

- Các cấu trúc dữ liệu STD `queue` và `stack`, trừ khi bị ghi đè lên các đối số, thì chỉ là một phần của cấu trúc dữ liệu `deque` thôi. Bởi vì các tính chất của `stack` và `queue` chỉ là một phần của `deque`, nên ta có thể dễ dàng tạo ra nó bằng cách giới hạn những thao tác `deque`.
