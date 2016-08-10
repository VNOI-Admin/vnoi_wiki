# Bảng băm (Hash Tables)

Bảng băm là một cấu trúc dữ liệu đặc biệt thường được sử dụng như một từ điển. Trong đó, mỗi khóa mang theo một giá trị tương ứng. Khóa được xem như chỉ số của giá trị tương ứng. Bảng băm không như các loại từ điển cổ điển – mọi người có thể tìm được khóa thông qua giá trị của nó.

Không may, không phải tất cả các kiểu dữ liệu đều có thể sắp xếp vào một từ điển đơn giản. Đây chính là lúc mà quá trình băm (hash) ra đời. Hash là quá trình khởi tạo một giá trị khóa (thường là 32 bit hoặc 64 bit) từ một mảnh dữ liệu. Giá trị hash này sẽ giúp việc sắp xếp trở nên đơn giản hơn. Giá trị hash có thể là n bit đầu tiên của dữ liệu, n bit cuối cùng, giá trị mod hoặc là kết quả của một hàm phức tạp. Sử dụng các giá trị hash, ta có thể cài đặt các hash buckets để lưu trữ dữ liệu. Nếu các giá trị hash được phân bố đều, các buckets sẽ được điền vào một cách đồng đều. Trong một vài trường hợp, các buckets không có hoặc chỉ có một vài đối tượng trong chúng. Điều này làm cho việc tìm kiếm còn nhanh hơn nữa.

Trường hợp một hash bucket chứa nhiều hơn một giá trị ta gọi đó là va chạm. Việc xử lý  va chạm rất quan trọng đối với hiệu năng của bảng băm. Một trong những phương pháp đơn giản nhất là cài đặt các danh sách liên kết ở hash bucket. Khi đó, mỗi phần tử cùng giá trị hash có thể kết lại với nhau tại một điểm.Một số cách làm phức tạp hơn như: sử dụng liền kề, hash một lần nữa để có giá trị hash mới,… Như thường lệ, mỗi cách làm đều có những điểm tốt, xấu về mặt hiệu suất.

Một ví dụ đơn giản khác của hash table chính là hệ thống số thập phân Dewey – được sử dụng trong rất nhiều thư viện. Tất cả các sách đều được đăng ký một số tương ứng dựa vào chủ đề của nó chẳng hạn như những số gần 500 là các sách khoa học, gần 700 là sách nghệ thuật. Như một bảng hash thật sự, tốc độ của để người đọc tìm ra quyển sách sẽ dựa vào các hash bucket có thật sự được phân chia tốt. Chúng ta sẽ phải mất nhiều thời gian hơn để tìm một quyển sách về sương mù trong một thư viện sách khoa học so với một thư viện sách văn học cổ điển.

Trong phát triển ứng dụng, bảng hash thuận tiện để lưu trữ dữ liệu tham khảo, chẳng hạn như chữ viết tắt tên đầy đủ của các tổ chức. Trong giải quyết bài toán, bảng hash thật sự hữu ích để tiếp cận hướng giải quyết chia để trị cho bài toán cái túi (knapsack-type).

Giả sử, chúng ta được yêu cầu tìm một số lượng ống nhỏ nhất để xây dựng một đường ống với chiều dài cố định và chúng ta có 38 ống. Bằng cách chia thành hai tập – 19 và tính toán tất cả trường hợp ghép ống có thể ở mỗi tập, chúng ta tạo ra một bảng hash kết nối giữa độ dài mà các tổ hợp ống tạo thành với số lượng ống ít nhất cần dùng. Sau đó, với mỗi tổ hợp ống được xây dựng trong một tập, chúng ta có thể tra cứu liệu có tồn tại đường ống với độ dài phù hợp ở tập bên kia để cả hai ống tạo nên một đường ống với độ dài yêu cầu với số ống là ít nhất.

# Các tài liệu tham khảo:

- [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/data-structures/)
