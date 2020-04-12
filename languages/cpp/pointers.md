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
- Dữ liệu của các biến này **hoàn toàn độc lập** với nhau: Giá trị của biến `a` không phụ thuộc vào giá trị của biến `b` và **ngược lại**. 
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

Trong đoạn code này, biến `b` được gọi là *biến tham chiếu* kiểu `int`. Nó được khai báo bằng việc thêm một dấu `&` vào sau tên kiểu `int`. Chú ý rằng hai cách khai báo `int& a = b` và `int &a = b` đều hợp lệ và có ý nghĩa như nhau. Qua thí nghiệm này, ta thấy rằng lệnh gán biến `a` cũng làm thay đổi giá trị của `b` và lệnh gán biến `b` cũng lam thay đổi giá trị của `a`. Thực tế, hai biến `a` và `b` này chỉ là một biến, nghĩa là `a` và `b` **luôn mang cùng một giá trị**, và mọi lệnh làm thay đổi giá trị của `a` **cũng làm thay đổi giá trị của** `b` và **ngược lại**.

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
Con trỏ sử dụng ý tưởng của biến tham chiếu: Biến con trỏ được tạo ra *thường* không để có thêm không gian lưu trữ dữ liệu, mà là để tạo ra "tên khác" hoặc "nhãn mác mới" cho một biến đã có từ trước. Điều này giải thích tên gọi "con trỏ": "trỏ" trong từ "chỉ trỏ" có nghĩa là chỉ vào, hướng vào một cái gì đó. Nhưng khác với biến tham chiếu, một con trỏ ở những thời điểm khác nhau có thể *trỏ vào* (hay "là tên biến khác" hoặc "đại diện cho") các biến khác nhau. Biến con trỏ có thể không trỏ vào cái gì (gọi là con trỏ rỗng - *NULL* mà ta sẽ nghiên cứu ở phần sau) và không cần thiết phải được khởi tạo lúc khai báo.

Tóm lại, sau phần này, bạn cần nắm được sự khác biệt của con trỏ với những loại biến mà các bạn hay sử dụng: Các biến "thông thường" dùng để **lưu trữ thông tin** và **có tính độc lập**. Các biến tham chiếu và con trỏ dùng để "đặt lại tên" hoặc "tạo một tên mới" cho các biến đã có từ trước.

*Ghi chú: Ý tưởng phân tích ở phần này có thể KHÔNG phải là ý tưởng để người sáng lập ngôn ngữ lập trình C/C++ đưa con trỏ vào ngôn ngữ; nhưng theo quan điểm của tác giả, góc nhìn này giúp các bạn học lập trình ở phổ thông hiểu được khái niệm của con trỏ.*

# 2. Cách sử dụng con trỏ
## a. Các cú pháp cơ bản
Phần này chủ yếu giới thiệu cho các bạn các cú pháp cơ bản để sử dụng con trỏ một cách chính xác. Bạn có thể coi những đoạn code dưới đây như là cú pháp, chỉ học thuộc lòng mà không cần quan tâm quá nhiều về ý nghĩa.

### Khai báo con trỏ
Dù con trỏ có thể *trỏ vào* (đại diện cho/là một tên khác của) **nhiều biến khác nhau** trong những thời điểm khác nhau, các đối tượng được trỏ vào phải có **cùng một kiểu dữ liệu**. Kiểu dữ liệu chung này cần được xác định khi khai báo.

Để khai báo một con trỏ *trỏ vào* các biến có kiểu dữ liệu `int`, ta khai báo `int *p` hoặc `int* p` (hai cách này như nhau về mặt cú pháp). Tương tự, nếu bạn muốn con trỏ của bạn trỏ vào các biến có kiểu `string` hoặc `queue<char>`, ta khai báo `string *s` hoặc `queue<char> *q`.

Tổng quát, nếu `T` là một kiểu dữ liệu nào đó (có thể là kiểu *nguyên thủy* như `int`, `char`, `double` hoặc các struct, class như `vector<string>`, `queue<pair<int, int>>`) thì `T*` là một **con trỏ trỏ vào các biến thuộc kiểu T**. Do con trỏ cũng là một kiểu dữ liệu, con trỏ cũng có thể trỏ vào một con trỏ khác. Ví dụ, `int **p` là một *con trỏ trỏ vào một con trỏ trỏ vào một biến kiểu `int`* hay `char *******just_to_troll` là một con trỏ trỏ vào một con trỏ trỏ vào một con trỏ trỏ vào một con trỏ trỏ vào một con trỏ trỏ vào một con trỏ trỏ vào một con trỏ trỏ vào một biến kiểu `char`.

Theo kinh nghiệm của mình, *con trỏ trỏ vào một con trỏ* là thứ rất ít khi sử dụng trong lập trình thi đấu. Vì vậy, để đơn giản, trong phần lớn thời lượng còn lại của bài viết, mình chỉ xét trường hợp con trỏ trỏ vào một biến "thông thường".

### Thay đổi (gán) biến được con trỏ trỏ vào
Bạn có thể cho một con trỏ trỏ vào một biến "thông thường" hoặc trỏ vào nơi mà *một con trỏ khác đang trỏ tới*. Ví dụ

```cpp
int normal;
int *first;
int *second;
first = &normal;
second = first;

```
Trong ví dụ trên, ta có `normal` là một biến "thông thường" kiểu `int`. `first` và `second` là các con trỏ mà đối tượng (biến) được trỏ tới có kiểu `int`. Dòng số 4 `first = &normal` giúp con trỏ first trỏ vào biến normal. Dòng số 5 `second = first` mang ý nghĩa rằng *con trỏ `second` trỏ vào nơi mà `first` đang trỏ vào, nghĩa là biến `normal`*. 

Chú ý rằng nếu bạn muốn trỏ vào một biến "thông thường", trước tên biến phải có dấu `&`. Còn nếu muốn một con trỏ trỏ vào đối tượng của một con trỏ khác, vế phải không cần có dấu `&`. Đồng thời, các con trỏ trỏ vào các đối tượng khác kiểu nhau không thể bị gán ghép với nhau. Do đó, các dòng code dưới đây đều gặp lỗi khi biên dịch:

```cpp
int normal;
int *pointer_1, *pointer_2;
string *pointer_string;

pointer_1 = normal; // ERROR!!! should be pointer_1 = &normal
pointer_2 = &pointer_1; // ERROR!!! should be pointer_2 = pointer_1;
pointer_2 = pointer_string // ERROR!!! type mismatches: string* vs int*

```

Tới đây các bạn sẽ thắc mắc: Dấu `&` xuất hiện trong `&normal` có mối quan hệ biện chứng nào với dấu `&` ở phần biến tham chiếu hay không. Câu trả lời là có, nhưng nó hơi phức tạp với các bạn. Nhắc lại lần nữa, mình khuyên các bạn coi các đoạn code ở phần này là những **cú pháp cố định** và **phải học thuộc lòng** thay vì cố phân tích các quy tắc.

### Truy cập vào biến được con trỏ trỏ tới
Như đã nói ở trên, ngoại trừ trường hợp con trỏ trỏ vào một con trỏ, các con trỏ được dùng để "đặt tên khác" cho một biến "thông thường" nào đó. Để truy cập vào một biến được con trỏ `p` trỏ tới, bạn dùng `*p`. Các bạn hãy coi `*p` ở đây **như một biến "thông thường"**, nghĩa là nếu các biến "thông thường" cùng kiểu có thể xuất hiện thế nào, `*p` có thể sử dụng hoàn toàn tương tự như vậy:

```cpp
int *p_int = ...; // something which does not matter
string *p_string = ...; // something which does not matter

*p_int = 5; (*p_int)++; cout << *p_int << endl;
if (!(*p_string).empty()) for (int i = 0; i < (*p_string).size(); i++) printf("%c", (*p_string)[i]);

```

Việc một con trỏ *là một tên khác* của một biến "thông thường" được thể hiện dưới đây:

```cpp
int normal_1, normal_2;
int *pointer;

normal_1 = normal_2 = 100;
pointer = &normal_1;
printf("%d\n", *pointer); // 100
*pointer = 200;
printf("%d\n", normal_1); // 200;

pointer = &normal_2;
*pointer = 300;
printf("%d %d\n", normal_1, normal_2); // 200 300

int *another_pointer = pointer;
normal_2 = 400;
printf("%d\n", *another_pointer); // 400

```

Trong ví dụ trên:
- Đầu tiên con trỏ `pointer` trỏ vào biến "thông thường" `normal_1`. Do đó, `normal_1` và `*pointer` lúc này **cùng là một biến**: Khi một lệnh làm thay đổi giá trị `normal_1`, giá trị của `*pointer` cũng thay đổi theo và ngược lại. 
- Sau lệnh gán `pointer = &normal_2`, `pointer` lúc này trỏ vào `normal_2` và **không còn trỏ vào** `normal_1` nữa. Vì vậy, lện gán `*pointer_2 = 300` **làm thay đổi** `normal_2` nhưng **không làm thay đổi** `normal_1`. 
- Cuối cùng, con trỏ `another_pointer` được cho trỏ vào *nơi `pointer` đang trỏ vào*, tức là biến "thông thường" `normal_2`. Do đó lệnh gán `normal_2` làm thay đổi `*another_pointer`.

**Chú ý**: Các lệnh gán các biến "thông thường" `normal_1` và `normal_2` ở trên kia làm thay đổi `*pointer`, **nhưng không thay đổi** `pointer`. Các bạn cần **phân biệt rất cẩn thận** hai lệnh `*another_pointer = *pointer` và `another_pointer = pointer`. Lệnh thứ nhất chỉ là phép gán giá trị giữa hai biến "thông thường", trong khi lệnh thứ hai làm thay đổi đối tượng mà `another_pointer` đại diện cho.

### Con trỏ *NULL* - con trỏ không trỏ vào một đối tượng nào.
Một con trỏ có thể không trỏ vào một đối tượng nào, khi đó con trỏ mang một giá trị mặc định *NULL*. Khi bạn cố gắng truy cập vào đối tượng của một con trỏ mang gía trị *NULL*, chương trình bạn **bị crash ngay lập tức** (bị *crash* chứ không bị *crush*) và bạn sẽ gặp phải lỗi *run-time error* (hoặc *non-zero exit code*, *segmentation fault*):

```cpp
int* p = NULL;
cout << *p << endl; // ERROR!!!

```

Do đó, kinh nghiệm ở đây là luôn kiểm tra một con trỏ có phải *NULL* hay không trước khi truy cập vào. Khi biết chương trình của bạn chạy sinh lỗi (khi chạy thử test đề hoặc nộp lên hệ thống bị run-time error), bạn nên rà soát lại toàn bộ code, và xem các con trỏ đã được kiểm tra *NULL* trước khi truy cập hay chưa:

```cpp
int* p ...;
printf("%d\n", *p); // DANGEROUS!!! p might be NULL
printf("%d\n", p != NULL ? *p : 0); // SAFE :)

```

### Lệnh *new* tạo biến "thông thường":
Dù một con trỏ thường được dùng để trỏ vào ("tạo tên biến khác") cho một biến đã có trước đó, có những trường hợp chúng ta muốn con trỏ trỏ vào một biến hoàn toàn mới. Khi đó lệnh `new` (từ khóa của C/C++) giúp chúng tạo ra một biến mới:

```cpp
int normal_1 = 100, normal_2 = 200, normal_3 = 300;
int *pointer = new int;
*pointer = 400;
printf("%d %d %d %d\n", normal_1, normal_2, normal_3, *pointer); // 100 200 300

```

Ở đây, rõ ràng biến `*pointer` là một biến "thông thường" kiểu `int`. Nhưng biến này không trùng với bất kỳ biến "thông thường" kiểu `int` nào đã khai báo trước đó. Do đó lệnh `*pointer = 400` không ảnh hưởng tới `normal_1`, `normal_2` hay `normal_3`.

Nếu các bạn đã quen với *constructor* của struct/class hay các thư viện STL (một cách truyền tham só để khởi tạo các đối tượng), bạn có thể truyền các tham số một cách hoàn toàn tương tự để khởi tạo các đối tượng của lệnh `new`. Dưới đây, ta có một biến thông thường `vec` là một `vector<int>` có 10 số 1, và một con trỏ `vec_pointer` trỏ vào một `vector<int>` có 10 số 1. Tuy nhiên, hai vector này **không liên quan đến nhau**.

```cpp
vector<int> vec(10, 1);
vector<int> *vec_pointer = new vector<int>(10, 1);
cerr << (*vec_pointer).size() << " " << (*vec_pointer)[0] << endl; // 10 1

```

### Truy cập các trường của một con trỏ trỏ vào đối tượng.
Nếu một con trỏ trỏ vào một đối tượng (struct/class) hoặc các biến có kiểu là các kiểu dữ liệu trong STL, ta có thể dùng mũi tên `->` để truy cập vào các trường và hàm của chúng. Về mặt ý nghĩa, `(*p).x` và `p->x` **hoàn toàn giống nhau**, nhưng cách viết sau ngắn gọn và dễ nhìn hơn.

```cpp
vector<int> *p = new vector<int>(); // an empty vector
p->push_back(2);
cerr << p->size() << " " << p->front() << "\n"; // 1 2

```