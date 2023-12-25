# Tìm kiếm nhị phân

#Giới thiệu
**Tìm kiếm nhị phân** là một trong những thuật toán cơ bản trong khoa học máy tính. Để khám phá nó, trước tiên chúng ta sẽ xây dựng tư tưởng, sau đó sử dụng để cài đặt một cách chính xác.

#Tìm một giá trị trong một dãy được sắp xếp
Ở dạng đơn giản nhất, **tìm kiếm nhị phân** được sử dụng để nhanh chóng tìm thấy một giá trị trong một dãy được sắp xếp.**Tìm kiếm nhị phân** tìm kiếm ở đoạn có chứa giá trị cần tìm. Đây được gọi là **không gian tìm kiếm** . Các **không gian tìm kiếm** là ban đầu toàn bộ dãy. Tại mỗi bước, các thuật toán so sánh giá trị trung bình trong không gian tìm kiếm với giá trị cần tìm. Dựa trên sự so sánh và vì trình tự đã được sắp xếp, nó có thể loại bỏ một nửa của không gian tìm kiếm. Bằng cách làm như vậy nhiều lần, cuối cùng sẽ được một không gian tìm kiếm bao gồm một phần tử duy nhất, **giá trị cần tìm**.

Ví dụ, xem xét dãy sau chứa các số nguyên được sắp xếp theo thứ tự tăng dần và giá trị cần tìm là 55:

$0$ , $5$ , $13$ , $19$ , $22$ , $41$ , $55$ , $68$ , $72$ , $82$ , $98$

Ta sẽ dùng chỉ số của phần tử để đại diện cho các giá trị. Ban đầu, không gian tìm kiếm là từ $1$ tới $11$. Như tư tưởng của thuật toán, ta có **giá trị trung bình**, đó là $6$ ( trung bình của $1$ và $11$ ) và nó nhỏ hơn $55$. Từ đây chúng ta kết luận phần tử tại chỉ số 6 không phải là **giá trị cần tìm**, nhưng cũng không có phần tử nào có chỉ số từ $1$ tới $5$ có thể mang **giá trị cần tìm** , bởi vì giá trị tất cả các phần tử ở các chỉ số này nhỏ hơn 41. Từ đây ta có không gian tìm kiếm từ $7$ tới $11$:

$55$, $68$, $72$, $81$, $98$

Tương tự, ta còn:

$55$, $68$

Tùy theo cách ta chọn **giá trị trung bình**, làm tròn hay không, ta sẽ có $55$ trong bước tiếp theo hoặc là $68$. Dù cách nào đi nữa, ta cũng sẽ tìm được $55$ ở phần tử thứ $7$.

Nếu **giá trị cần tìm** không có trong dãy, in ra $-1$ hoặc trả về là không tìm được.

Code C++:

```cpp

binary_search(A, target):
   lo = 1, hi = size(A)
   while lo <= hi:
      mid = lo + (hi-lo)/2
      if A[mid] == target:
         return mid
      else if A[mid] < target:
         lo = mid+1
      else:
         hi = mid-1

   // target was not found

```

#Độ phức tạp

Với mỗi so sánh, **tìm kiếm nhị phân** sử dụng hai nửa **không gian tìm kiếm**, nên ta có thể khẳng định rằng **tìm kiếm nhị phân**  không bao giờ sử dụng nhiều hơn $O(logN)$ để tìm **giá trị cần tìm**.

Lưu ý rằng **tìm kiếm nhị phân** sẽ truy cập vào một phần tử ngẫu nhiên trong dãy, cho nên với những bài toán đặc trưng, nên sử dụng **tìm kiếm tuần tự** thay vì **tìm kiếm nhị phân**.

#Tìm kiếm nhị phân trong thư viện

Thư viện **STL C++** thực hiện các tìm kiếm trong các hàm **LOWER_BOUND**, **UPPER_BOUND**, **binary_search** và **equal_range** tùy vào những gì bạn cần mà lựa chọn hàm phù hợp.

**Java** thì có sẵn **Arrays.binary_search** và **.NET Framework** có **Array.BinarySearch**.

Chỉ nên dùng **tìm kiếm nhị phân** có sẵn trong thư viện khi bạn đã nắm chắt tư tưởng của thuật toán.
