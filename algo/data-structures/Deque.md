# Deque - hàng đợi hai đầu

**Hàng đợi hai đầu** (**deque**) là cấu trúc dữ liệu chứa 0 hoặc nhiều phần tử có cùng kiểu dữ liệu và được biểu diễn bằng một hàng có phần tử _đầu_ (**front**) và phần tử _cuối_ (**last**). **Deque** hỗ trợ 4 thao tác như sau:

  - _Thêm_ một phần tử vào _cuối deque_. **(Push back)**
  - _Thêm_ một phần tử vào _đầu deque_. **(Push front)**
  - _Bỏ_ đi phần tử ở _cuối deque_, trả về giá trị của phần tử đó. **(Pop back)**
  - _Bỏ_ đi phần tử ở _đầu deque_, trả về giá trị của phần tử đó. **(Pop front)**

Về thực hành, ta sẽ bổ sung thêm một số thao tác sau:
  
  - _Xây dưng_ một deque rỗng. **(Construct)**
  - _Sao chép_ deque này sang một deque khác. **(Copy)**
  - _Lấy giá trị_ của phần tử cuối mà không xóa nó. **(Peek back)**
  - _Lấy giá trị_ của phần tử đầu mà không xóa nó. **(Peek front)**
  - _Xóa sạch_ một deque đang có phần tử. **(Empty)**
  - _Tìm số lượng phần tử_ trong deque. **(Find size)**
  - _Kiểm tra_ xem deque có rỗng hay không. **(Test empty)**

Hau thao tác _lấy giá trị_ thật sự cũng không cần thiết lắm, _lấy giá trị phần tử đầu_ deque **(peek front)** tương đương với việc xóa đi phần tử đó **(pop front)** rồi lại thêm nó vào **(push front)**, và tương tự với _lấy giá trị phần tử cuối_ **(peek last)**. Và _kiểm tra rỗng_ **(Test empty)** thật ra cũng chỉ là _kiểm tra xem số lượng phần tử_ của deque có bằng 0 hay không thôi.

[[_TOC_]]

# Thuật ngữ

Thuật ngữ **deque** là cách gọn ngắn tắt của _double-ended queue_ (hàng đợi hai đầu). Sở dĩ là vì nó có thể thêm, bớt phần tử ở cả hai đầu; còn thuật ngữ **queue** ở đây là một lớp cấu trúc dữ liệu cho phép thêm, bớt phần tử (nhưng không thể tìm kiếm). Một phần tử được xem là **đứng trước** một phần tử khác nếu nó gần với phần tử đầu (**front**) hơn là phần tử còn lại; ngược, lại, một phần tử được xem là **đứng sau** một phần tử khác nếu nó xa với phần tử đầu (**front**) hơn là phần tử còn lại. **Push** một phần tử là thêm phần tử đó vào hàng đợi, **pop** đẩy ra một phần tử. Lưu ý rằng _điểm đầu_ (**front**) và _điểm cuối_ (**last**) là tương đương nhau, khi thay đổi toàn bộ điểm cuối và đầu trong giải thuật của chúng ta thì nó vẫn hoạt động chính xác như trước đó.

# Cài đặt

## Cài đặt bằng mảng

## Cài đặt bằng danh sách liên kết

## Lớp deque trong STD C++