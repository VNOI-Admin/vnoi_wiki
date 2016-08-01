#Tìm kiếm nhị phân

#Giới thiệu
**Tìm kiếm nhị phân** là một trong những thuật toán cơ bản trong khoa học máy tính. Để khám phá nó, trước tiên chúng ta sẽ xây dựng tư tưởng, sau đó sử dụng để cài đặt một cách chính xác.

#Tìm một giá trị trong một dãy được sắp xếp
Ở dạng đơn giản nhất, **tìm kiếm nhị phân** được sử dụng để nhanh chóng tìm thấy một giá trị trong một dãy được sắp xếp.**Tìm kiếm nhị phân** tìm kiếm ở đoạn có chứa giá trị cần tìm. Đây được gọi là **không gian tìm kiếm** . Các **không gian tìm kiếm** là ban đầu toàn bộ dãy. Tại mỗi bước, các thuật toán so sánh giá trị trung bình trong không gian tìm kiếm với giá trị cần tìm. Dựa trên sự so sánh và vì trình tự đã được sắp xếp, nó có thể loại bỏ một nửa của không gian tìm kiếm. Bằng cách làm như vậy nhiều lần, cuối cùng sẽ được một không gian tìm kiếm bao gồm một phần tử duy nhất, **giá trị cần tìm**.

Ví dụ, xem xét dãy sau chứa các số nguyên được sắp xếp theo thứ tự tăng dần và giá trị cần tìm là 55:

$0$ , $5$ , $13$ , $19$ , $22$ , $41$ , $55$ , $68$ , $72$ , $82$ , $98$

Ta sẽ dùng chỉ số của phần tử để đại diện cho các giá trị. Ban đầu, không gian tìm kiếm là từ $1$ tới $11$. Như tư tưởng của thuật toán, ta có **giá trị trung bình**, đó là $6$ ( trung bình của $1$ và $11$ ) và nó nhỏ hơn $55$