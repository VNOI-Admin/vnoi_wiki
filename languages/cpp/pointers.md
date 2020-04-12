# Con trỏ trong C/C++

**Tác giả**: Phạm Văn Hạnh (*skyvn97, prof.PVH, I_love_tigersugar*)

Con trỏ là một trong những tính năng quan trọng của mỗi ngôn ngữ lập trình. Thực tế, để được gọi là sử dụng thành thạo một ngôn ngữ lập trình như C/C++, lập trình viên cần biết cách sử dụng con trỏ. Tuy nhiên, do ít được sử dụng trong các bài toán lập trình ở các kỳ thi học sinh giỏi, nhiều bạn học sinh chuyên tin cấp ba không nắm chắc cách dùng con trỏ, hoặc thậm chỉ bỏ qua phần kiến thức này. Vì vậy, bài viết này giúp các bạn hiểu qua cách sử dụng con trỏ và các ý nghĩa của nó.

Cần nói thêm rằng, để có cái nhìn toàn diện về con trỏ trong các ngôn ngữ lập trình, bạn cần có các kiến thức về kiến trúc máy tính, hệ điều hành, cách lưu trữ biến trong bộ nhớ máy tính. Bài viết dưới đây bỏ qua các khía cạnh này, chủ yếu nhắc đến cách sử dụng con trỏ, các lỗi hay mắc, lợi ích của con trỏ trong các bài toán lập trình thi đấu. 

Bởi thế, bạn có thể yên tâm rằng bài viết dưới đây không khiến các bạn hại não, chỉ cần uống chút **sữa tươi chân trâu đường hổ** rồi bắt đầu đọc thôi :)

[[_TOC_]]

# 1. Con trỏ là gì?
## a. Biến "thông thường"
Chúng ta đã quá quen thuộc với các biến (*variables*) trong C++. Một biến có thể mang một giá trị, ví dụ như biến dạng `bool`, `int` hay `double`. Mỗi biến thuộc các kiểu này dùng để lưu một **giá trị** nào đó. Các biến còn có thể là một đối tượng phức tạp hơn, ví dụ như các cấu trúc dữ liệu `vector<int>`, `queue<string>` hay `map<int, string>`. Các biến thuộc loại này có thể chứa một tập hợp nhiều giá trị nào đó. Dù đơn giản hay phức tạp, các biến thuộc một trong các dạng kể trên luôn giúp chúng ta lưu trữ dữ liệu. Tác giả tạm gọi những kiểu biến này là biến "thông thường".

Như vậy, các biến "thông thường" là các biến **có thể lưu trữ dữ liệu**. Chúng có hai tính chất cơ bản sau: 
- Dữ liệu của các biến này **hoàn toàn độc lập** với nhau: Giá trị của biến `a` không phụ thuộc vào giá trị của biến `b` và ngược lại. 
- Mỗi khi ta khai báo một biến "thông thường" `int x; string s; vector<double> v;...` ta có thêm một biến mới, và biến đó cho ta **thêm không gian lưu trữ dữ liệu**.

## b. Biến tham chiếu (*reference*)
Giờ chúng ta sang tới một loại biến khác, có tên chính thức là *biếu tham chiến* (*reference*). Có thể các bạn đã biết, đã sử dụng nhưng không để ý, hoặc chưa từng sử dụng biến tham chiếu. Đầu tiên, ta hãy cùng chạy thử một đoạn code đơn giản sau:

```cpp
int a = 1;
int &b = a;
b = 2;
cout << a << endl; // it prints 2, not 1 (!)
a = 3;
cout << b << endl; // it prints 3, not 2 (!)

```

Trong đoạn code này, biến `b` được gọi là *biến tham chiếu* kiểu `int`. Nó được khai báo bằng việc thêm một dấu `&` vào sau tên kiểu `int`. Chú ý rằng hai cách khai báo `int& a = b` và `int &a = b` đều hợp lệ và có ý nghĩa như nhau. Qua thí nghiệm này, ta thấy rằng lệnh gán biến `a` cũng làm thay đổi giá trị của `b` và lệnh gán biến `b` cũng lam thay đổi giá trị của `a`. Thực tế, hai biến `a` và `b` này chỉ là một biến, nghĩa là `a` và `b` **luôn mang cùng một giá trị**, và mọi lệnh làm thay đổi giá trị của `a` **cũng làm thay đổi giá trị của** `b` và ngược lại.

Ta xét thêm một ví dụ nữa - một trường hợp điển hình cho việc sử dụng biến tham chiếu trong lập trình thi đấu: Quy hoạch động đệ quy có nhớ.

```cpp
int cacheDPResults[2207][1997] = {-1};
int dp(int i, int j) {
	int &result = cacheDPResults[i][j];
	if (result >= 0) return result;

	if (i == 0) return result = 0;
	result = dp(i - 1, j);
	if (j >= weight[i]) result = max(result, dp(i - 1, j - weight[i]) + value[i];

	return result;
}

```

Chắc các bạn lờ mờ đoán ra đoạn code trên mô phỏng công thức quy hoạch động của bài toán cái túi (*knapsack*). Tất nhiên không ai cài bài toán cái túi bằng đệ quy có nhớ cả :)

Giờ ta để ý dòng code thứ 3 trong đoạn ví dụ trên: `int &result = cacheDPResults[i][j]`. Dù dòng code này dùng để khai báo biến `result`, nhưng do có ký tự `&` ở trước, kết quả của biến `result` này được "đồng bộ" với biến `cacheDPResult[i][j]`. Biến `result` và `cacheDPResult[i][j]` **luôn mang cùng giá trị**, và khi giá trị một biến thay đổi, **biến kia cũng thay đổi theo**.

Như vậy, biến `result` này (và biến `b` ở ví dụ trước) có hai điểm khác với các biến "thông thường" được đề cập ở phần 1a:
- Giá trị của biến `result` **không độc lập** với giá trị của biến `cacheDPResult[i][j]`: Hai giá trị này luôn bằng nhau.
- Khi khai báo biến `result`, ta **không có thêm không gian lưu trữ dữ liệu**.

Do đó, nếu giữ định nghĩa về biến "thông thường" như ở phần 1a, ta không coi `result` là biến, mà nó chỉ như một tên gọi khác của biến `cacheDPResults[i][j]`. Thực tế, cách đặt biến `result` chỉ giúp cho đoạn code của bạn trong sáng hơn. Nếu bạn thay lệnh khai báo `int &result = cacheDPResults[i][j]` bằng lệnh `#define result cacheDPResults[i][j]`, hiệu ứng của đoạn code không đổi. Thậm chí, bạn có thể không sử dụng biến result và tạo ra đoạn code tuy không được trong sáng, nhưng có kết quả hoàn toàn giống đoạn code phía trên:

```cpp
int cacheDPResults[2207][1997] = {-1};
int dp(int i, int j) {
	if (cacheDPResults[i][j] >= 0) return cacheDPResults[i][j];
	if (i == 0) return 0;
	cacheDPResults[i][j] = dp(i - 1, j);
	if (j >= weight[i]) cacheDPResults[i][j] = max(cacheDPResults[i][j], dp(i - 1, j - weight[i]) + value[i];
	return cacheDPResults[i][j];
}

```

Biếu tham chiến này cho ta ý tưởng về một dạng biến đặc biệt trong ngôn ngữ lập trình, ở đó dù biến được tạo ra nhưng bản chất chỉ là "đặt một tên khác" cho một biến đã có sẵn từ trước. Tuy nhiên, biến tham chiếu này có hai nhược điểm: Biến tham chiếu **luôn tham chiếu vào một biến cố định** và đối tượng được tham chiếu **phải được xác định ngay lúc khai báo**. Có nghĩa là, nếu bạn có hai biến "thông thường" `int a, b` và một biến tham chiếu `int &c = a`, bạn không thể nào làm cho `b` và `c` đồng bộ nhau được. Đồng thời, nếu bạn chỉ khai bảo `int &c` mà không có vế phải, trình biên dịch sẽ báo lỗi.

Những thông tin trên cho chúng ta ý tưởng về **con trỏ**.

## c. Con trỏ (*pointer*)
Con trỏ sử dụng ý tưởng của biến tham chiếu: Biến con trỏ được tạo ra *thường* không để có thêm không gian lưu trữ dữ liệu, mà là để tạo ra "tên khác" hoặc "nhãn mác mới" cho một biến đã có từ trước. Điều này giải thích tên gọi "con trỏ": "trỏ" trong từ "chỉ trỏ" có nghĩa là chỉ vào, hướng vào một cái gì đó. Nhưng khác với biến tham chiếu, một con trỏ ở những thời điểm khác nhau có thể "đại diện" hay "trỏ vào" các biến khác nhau. Biến con trỏ có thể không trỏ vào cái gì (gọi là con trỏ rỗng - *NULL* mà ta sẽ nghiên cứu ở phần sau) và không cần thiết phải được khởi tạo lúc khai báo.

Tóm lại, sau phần này, bạn cần nắm được sự khác biệt của con trỏ với những loại biến mà các bạn hay sử dụng: Các biến "thông thường" dùng để **lưu trữ thông tin** và **có tính độc lập**. Các biến tham chiếu và con trỏ dùng để "đặt lại tên" hoặc "tạo một tên mới" cho các biến đã có từ trước.

*Ghi chú: Ý tưởng phân tích ở phần này có thể KHÔNG phải là ý tưởng để người sáng lập ngôn ngữ lập trình C/C++ đưa con trỏ vào ngôn ngữ; nhưng theo quan điểm của tác giả, góc nhìn này giúp các bạn học lập trình ở phổ thông hiểu được khái niệm của con trỏ.*

# 2. Cách sử dụng con trỏ


