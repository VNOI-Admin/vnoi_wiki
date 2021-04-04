# **Stack (ngăn xếp)**

**Tác giả:** Nguyễn Hà Duy - THPT Chuyên Hà Nội - Amsterdam

* Table of contents
{:toc}

# Giới thiệu

Stack là một danh sách được bổ sung 2 thao tác: **thêm một phần tử vào cuối danh sách**, và **loại bỏ một phần tử ở cuối danh sách**. Ví trí cuối của Stack được gọi là đỉnh (**top**).

Có thể hình dung Stack như một chồng sách. Việc đặt một quyển sách lên trên cùng chính là thao tác thêm phần tử, và lấy ra quyển sách ở trên đầu là thao tác loại bỏ phần tử. Như vậy, quyển sách được đặt vào sau cùng sẽ luôn được lấy ra trước tiên. Vì tính chất này, Stack còn được gọi là danh sách **LIFO** (Last In - First Out, hay vào sau - ra trước).

Hình ảnh minh họa cho Stack chứa các phần tử kiểu `char`:
![](https://i.imgur.com/hMPdsl6.png)
    
Stack có khá nhiều ứng dụng trong lập trình thi đấu. Bài viết này sẽ xem xét các ứng dụng điển hình của Stack.

# Cài đặt

## Cài đặt thủ công

Ta có thể biểu diễn Stack bằng một mảng, cùng với biến `top` biểu diễn vị trí của phần tử nằm ở đỉnh Stack. Dưới đây là một cách cài đặt Stack chứa các phần tử thuộc kiểu `int`:
```cpp
const int MAXN = 1e5 + 2;

int st[MAXN];
int top = 0;

void push(int x) // thêm x vào cuối Stack
{
    ++top;
    st[top] = x;
}

void pop() // loại bỏ phần tử ở cuối Stack
{
    assert(top); // đảm bảo Stack đang chứa ít nhất 1 phần tử
    --top;
}

int peek() // trả về giá trị của phần tử ở đỉnh Stack
{
    return st[top];
}
```

Qua cách cài đặt này, có thể thấy bản chất của Stack là mảng, được bổ sung một vài thao tác đặc biệt để giải quyết các vấn đề trong khoa học máy tính. 

## Sử dụng thư viện chuẩn

Thư viện chuẩn của C++ cho phép ta sử dụng Stack qua kiểu dữ liệu `stack` trong header cùng tên. Các thao tác chính trên `stack` là:

* `push`: thêm phần tử vào cuối danh sách
* `top`: trả về giá trị phần tử ở cuối danh sách
* `pop`: loại bỏ phần tử ở cuối danh sách

Ngoài ra, `stack` cũng hỗ trợ các thao tác:
* `size`: trả về số phần tử hiện có trong stack
* `empty`: trả về trạng thái của stack (\\(true\\) nếu stack rỗng, \\(false\\) nếu stack có ít nhát 1 phần tử)

Ví dụ:
```cpp
#include <iostream>
#include <stack>

using namespace std;

int main()
{
    stack<int> st;
    st.push(5); // thêm 5 vào stack
    st.push(10); // thêm 10 vào stack
    cout << st.top() << endl; // In ra 10
    st.pop(); // loại bỏ phần tử ở cuối
    cout << st.top() << endl; // In ra 5
    return 0;
}
```
![](https://i.imgur.com/vOJp7DT.png)

Ngoài ra, ta có thể dùng `vector` để biểu diễn một Stack. Các hàm `push`, `top` và `pop` sẽ được thay bằng `push_back`, `pop_back` và `back` khi sử dụng `vector`.

## Phân tích

Do Stack có thể được cài đặt bằng `vector` nên các thao tác trên Stack cũng có cùng độ phức tạp với `vector`.

### Độ phức tạp thời gian

Các hàm `push`, `pop`, `top`, `size` và `empty` của Stack đều hoạt động trong \\(O(1)\\). Hơn nữa, như ta đã thấy ở cách cài đặt thủ công, bản chất của Stack chính là mảng, nên tất cả các thao tác trên Stack đều hoạt động trong \\(O(1)\\).

### Độ phức tạp bộ nhớ

Độ phức tạp bộ nhớ của Stack là \\(O(N)\\), với \\(N\\) là số phần tử được đưa vào Stack.

# Ứng dụng

## Sử dụng Stack để xử lý xâu

### Bài toán 1

Cho xâu \\(S\\) chỉ gồm các số nguyên dương và các dấu \\(+\\), \\(-\\), \\(\times\\), \\(\div\\), trong \\(S\\) không có dấu khoảng trống. Bạn cần tính giá trị của biểu thức được biểu diễn bởi xâu đó.

Đây là bài toán dễ hơn của [**Expression Parsing**](https://cp-algorithms.com/string/expression_parsing.html).

#### Cách giải

Vấn đề chính của bài toán là các toán tử \\(+\\), \\(-\\), \\(\times\\) và \\(\div\\) không có cùng độ ưu tiên. Cụ thể, ta cần tính kết quả của các cụm dấu \\(\times\\) và \\(\div\\) trước, do nhân và chia có độ ưu tiên cao hơn cộng và trừ.

Xét bài toán đơn giản hơn: trong xâu \\(S\\) chỉ có các dấu \\(+\\) và \\(-\\). Rõ ràng, do \\(+\\) và \\(-\\) có cùng độ ưu tiên nên ta có thể xử lý bài toán bằng cách duyệt các toán hạng và toán tử từ trái sang phải và tính trực tiếp kết quả sau mỗi phép cộng hoặc trừ. Ta có thể cài đặt như sau: duy trì một danh sách chứa số (toán hạng) và một danh sách chứa toán tử. Duyệt xâu từ trái qua phải, nếu ký tự đang xét là chữ số thì ta đẩy nó vào danh sách chứa số. Nếu đó là toán tử, ta đẩy ký tự vào danh sách chứa toán tử. Cuối cùng, ta lần lượt tính kết quả dựa vào danh sách toán hạng và toán tử đã xây dựng.

```cpp
// xử lý toán tử và cập nhật trực tiếp vào mảng val
void process_op(vector<int>& val, char op)
{
    // l, r là 2 toán hạng, op là dấu giữa chúng
    int r = val.back(); val.pop_back();
    int l = val.back(); val.pop_back();
    switch(op)
    {
    case '+':  val.push_back(l + r); break;
    case '-': val.push_back(l - r); break;
    }
}

// tính giá trị của biểu thức biểu diễn bởi s
int evaluate(string s)
{
    vector<int> val;
    vector<char> op;
    for (int i = 0; i < (int)s.size(); ++i)
    {
        if (isdigit(s[i]))
        {
            int number = 0; // giá trị của toán hạng đang xét
            while (i < (int)s.size() && isdigit(s[i]))
            {
                number = number * 10 + s[i] - '0';
                ++i;
            }
            --i; // cẩn thận với index!
        }
        else
        {
            op.push_back(s[i]);
        }
    }
    while (!op.empty())
    {
        process_op(val, op.back());
        op.pop_back();
    }
    return val.back();
}
```

Quan sát đoạn code ở cuối hàm `evaluate`:
```cpp
while (!op.empty())
{
    process_op(val, op.back());
    op.pop_back();
}
```
Do các toán tử có cùng độ ưu tiên, nên ta có thể xử lý chúng lần lượt theo danh sách đã xây dựng. Tuy nhiên, nếu danh sách \\(op\\) có các toán tử khác độ ưu tiên, nhưng chúng tạo thành dãy có **độ ưu tiên tăng dần**, thì ta vẫn có thể xử lý như trên, do các dấu có độ ưu tiên lớn hơn sẽ luôn được xử lý trước. Do các thay đổi được cập nhật trực tiếp vào mảng giá trị \\(val\\) nên ta luôn đảm bảo thu được kết quả đúng.

Trong bài toán gốc, xâu \\(S\\) còn chứa ký tự \\(\times\\) và \\(\div\\). Ta cần xử lý danh sách toán tử sao cho các phép tính có độ ưu tiên lớn hơn luôn được thực hiện trước.

Ta định nghĩa một thứ tự ưu tiên cho các dấu:
```cpp
// Trả về 2 nếu là nhân hoặc chia, 1 nếu là cộng hoặc trừ
int priority(char op)
{
    if (op == '+' || op == '-') return 1;
    else return 2;
}
```

Giống với bài toán đơn giản, ta vẫn duyệt xâu \\(S\\) từ trái sang phải. Khi gặp toán hạng, ta vẫn đẩy chúng vào danh sách. Tuy nhiên, khi gặp toán tử, ta cần xem xét thứ tự ưu tiên của toán tử ngay trước nó. Nếu toán tử trước có độ ưu tiên lớn hơn, ta cần phải xử lý nó trước, và loại bỏ toán tử đứng trước đó khỏi danh sách. Ta sẽ lặp lại việc xử lý toán tử đứng trước này cho đến khi nó có độ ưu tiên không lớn hơn toán tử đang xét. Điều này đảm bảo phép tính sẽ luôn được thực hiện theo mức độ ưu tiên.

Ý tưởng chính của lời giải là ta luôn duy trì danh sách toán tử có độ ưu tiên tăng dần. Khi đó, ta có thể xử lý lần lượt các dấu từ cuối về đầu danh sách toán tử như với bải toán chỉ có \\(+\\) và \\(-\\).

Quan sát rằng bản chất của danh sách ta sử dụng chính là Stack. Việc thêm toán tử/toán hạng vào danh sách chính là thao tác \\(push\\); cách ta xử lý toán tử gợi đến việc \\(top\\) và \\(pop\\) do trong các bước của lời giải, ta chỉ cần quan tâm tới những phần tử ở cuối danh sách. Lời giải sử dụng `vector` để biểu diễn Stack.

```cpp
void process_op(vector<int>& val, char op)
{
    int r = val.back(); val.pop_back();
    int l = val.back(); val.pop_back();
    switch(op)
    {
    case '+': val.push_back(l + r); break;
    case '-': val.push_back(l - r); break;
    case '*': val.push_back(l * r); break;
    case '/': val.push_back(l / r); break;
    }
}

int evaluate(string s)
{
    // ...
    for (int i = 0; i < (int)s.size(); ++i)
    {
        if (isdigit(s[i]))
        {
            // ...
        }
        else
        {
            char cur_op = s[i]; // toán tử hiện tại
            while (!op.empty() && priority(op.back()) > priority(cur_op))
            // xử lý các toán tử ngay trước nó có độ ưu tiên lớn hơn
            {
                process_op(val, op.back());
                op.pop_back();
            }
            op.push_back(cur_op);
        }
    }
    // do danh sách toán tử có độ ưu tiên tăng dần nên ta có thể xử lý
    // lần lượt như trong bài toán chỉ có + và -
    // chú ý là ta xử lý ngược từ đáy về đầu, nên các toán tử được xử lý
    // sẽ tạo thành một dãy giảm theo thứ tự ưu tiên
    while (!op.empty())
    {
        process_op(val, op.back());
        op.back();
    }
    return val.back();
}
```

Xét ví dụ: \\(S = 2 \times 3 - 4 \times 5\\).

Giá trị của \\(val\\) và \\(op\\) sau khi xử lý xâu \\(S\\):
![](https://i.imgur.com/r2zmJwN.png)

Quá trình xử lý danh sách toán tử \\(op\\):
![](https://i.imgur.com/UAV9GBN.png)

### Bài toán 2

Cho xâu \\(S\\) chỉ gồm ký tự \\((\\) và \\()\\). Bạn cần kiểm tra xem \\(S\\) có phải là dãy ngoặc đúng không.

Nếu \\(S\\) là dãy ngoặc đúng, với mỗi vị trí trong \\(S\\) bạn cần in ra vị trí của **dấu ngoặc tương ứng**. 

Định nghĩa:
* Xâu rỗng là dãy ngoặc đúng
* Nếu xâu \\(A\\) là dãy ngoặc đúng thì \\((A)\\) cũng là dãy ngoặc đúng. Khi đó, cặp dấu ngoặc quanh xâu \\(A\\) này là cặp **dấu ngoặc tương ứng**.
* Nếu xâu \\(A\\) và \\(B\\) đều là dãy ngoặc đúng thì xâu \\(A + B\\) cũng là dãy ngoặc đúng

Hình ảnh minh họa cho một dãy ngoặc đúng. Các cặp dấu ngoặc tương ứng được tô cùng màu:
![](https://i.imgur.com/K1Obiw8.png)

#### Nhận xét

Ta định nghĩa thêm: dãy ngoặc đúng cơ bản là dãy ngoặc đúng không thể tách được thành tổng của các dãy ngoặc đúng nhỏ hơn. Ví dụ, \\((()())\\) là dãy ngoặc đúng cơ bản, và \\((())()\\) không phải là dãy ngoặc đúng cơ bản, do nó có thể tách được thành \\((()) + ()\\).

Từ các định nghĩa, có thể rút ra các tính chất của dãy ngoặc đúng:

* **Tính chất 1**: Giữa một cặp dấu ngoặc tương ứng là một dãy ngoặc đúng
* **Tính chất 2**: Một dãy ngoặc đúng độ dài \\(2 \times n\\) có \\(n\\) cặp dấu ngoặc tương ứng, tương ứng với \\(n\\) dấu ngoặc mở và \\(n\\) dấu ngoặc đóng. Dấu ngoặc tương ứng của một dấu ngoặc mở phải nằm ở sau nó trong dãy, và dấu ngoặc tương ứng của một dấu ngoặc đóng phải nằm trước nó. Do đó, dãy ngoặc đúng không thể bắt đầu bằng dấu đóng ngoặc, hay kết thúc bằng dầu mở ngoặc.
* **Tính chất 3**: Xét một dãy ngoặc đúng \\(S\\). Nếu một tiền tố hoặc hậu tố \\(A\\) của \\(S\\) là một dãy ngoặc đúng, thì dãy \\(S \setminus A\\), hay dãy con của \\(S\\) không chứa \\(A\\), cũng là một dãy ngoặc đúng.
* **Tính chất 4**: Nếu \\(S\\) là dãy ngoặc đúng thì nó có thể được tách ra thành tổng của các dãy ngoặc đúng độc lập nhau, hay \\(S = s_1 + s_2 + ... + s_k\\), với \\(s_1, s_2, ..., s_k\\) đều là dãy ngoặc đúng *cơ bản*.
* **Tính chất 5**: Ký tự đầu và cuối của dãy ngoặc đúng cơ bản tạo thành một cặp dấu ngoặc tương ứng.

Ta có các bổ đề và hệ quả sau:

#### Bổ đề 1

Trong dãy ngoặc đúng, mỗi dấu ngoặc tương ứng với một và chỉ một dấu ngoặc khác.

#### Chứng minh

Giả sử tồn tại một dấu ngoặc có thể tương ứng với nhiều hơn một dấu ngoặc khác. Khi đó, sẽ có nhiều hơn một cách chia dãy ngoặc thành các cặp dấu ngoặc tương ứng. Do đó, tồn tại một dấu ngoặc đóng trong dãy tương ứng với nhiều hơn một dấu ngoặc khác.

Giả sử dấu ngoặc ở vị trí \\(k\\) là dấu ngoặc đóng và có thể tương ứng với các dấu ngoặc mở ở vị trí \\(i\\) và \\(j\\), với \\(i < j < k\\). Theo **tính chất 1**, ta có:

* Dãy ngoặc con từ vị trí \\(i + 1\\) đến \\(k - 1\\) của dãy gốc là dãy ngoặc đúng.
* Dãy ngoặc con từ vị trí \\(j + 1\\) đến \\(k - 1\\) của dãy gốc là dãy ngoặc đúng.

\\(......(......(...)\\)

\\(......i......j...k\\)

Theo **tính chất 3**, dãy ngoặc từ vị trí \\(i + 1\\) đến \\(j\\) cũng là dãy ngoặc đúng. Mà dãy ngoặc từ vị trí \\(i + 1\\) đến \\(j\\) lại kết thúc bằng dấu mở ngoặc, trái với **tính chất 2**. Vậy giả thiết tồn tại một dấu ngoặc tương ứng với nhiều hơn một dấu ngoặc khác là sai.

Vậy ta có điều phải chứng minh.

#### Bổ đề 2

Dãy ngoặc đúng khi và chỉ khi số dấu ngoặc mở bằng số dấu ngoặc đóng, và trong mọi tiền tố của dãy, số dấu ngoặc mở không nhỏ hơn số dấu ngoặc đóng.

#### Chứng minh

* **Chiều thuận**: dãy ngoặc đúng có số dấu ngoặc mở bằng số dấu ngoặc đóng, và trong mọi tiền tố của dãy, số dấu ngoặc mở không nhỏ hơn số dấu ngoặc đóng. Theo **tính chất 2**, dãy ngoặc mở có số dấu đóng ngoặc bằng số dấu mở ngoặc. Mặt khác, nếu tồn tại một tiền tố của dãy ngoặc đúng có số dấu mở ngoặc nhỏ hơn số dấu đóng ngoặc thì rõ ràng tồn tại ít nhất 1 dấu đóng ngoặc không tương ứng với dấu mở ngoặc nào, trái với **bổ đề 1**. Vậy ta chứng minh được chiều thuận.

* **Chiều đảo**: trong mọi tiền tố của dãy, số dấu ngoặc mở không nhỏ hơn số dấu ngoặc đóng đảm bảo rằng mỗi dấu ngoặc đóng đều có dấu ngoặc mở tương ứng với nó. Hơn nữa, số dấu ngoặc mở bằng số dấu ngoặc đóng đảm bảo không có dấu ngoặc mở bị thừa ra (hay không tương ứng với dấu ngoặc nào) trong dãy ngoặc. Do đó, dãy có số dấu ngoặc mở bằng số dấu ngoặc đóng và trong mọi tiền tố của dãy, số dấu ngoặc mở không nhỏ hơn số dấu ngoặc đóng là dãy ngoặc đúng.

#### Hệ quả 1

Dãy ngoặc không đúng sẽ có số dấu ngoặc mở lớn hơn số ngoặc đóng, hoặc có một tiền tố mà số dấu ngoặc mở nhỏ hơn số dấu ngoặc đóng. 

#### Cách giải

Cho một Stack chứa các phần tử kiểu `char`, đang ở trạng thái rỗng. Xét quá trình sau:
* Duyệt xâu \\(S\\) từ trái qua phải
* Nếu ký tự đang xét là dấu \\((\\), thêm nó vào Stack
* Nếu ký tự đang xét là dấu \\()\\), xét phần tử đang ở đỉnh Stack. Nếu đó là dấu \\((\\), ta tìm được một cặp dấu ngoặc tương ứng, và loại bỏ dấu ngoặc mở khỏi Stack. Nếu ngược lại, hoặc Stack rỗng, xâu \\(S\\) không phải dãy ngoặc đúng.
* Sau khi thực hiện quá trình, nếu Stack không rỗng thì \\(S\\) không phải dãy ngoặc đúng.

Trước hết, quá trình này sẽ luôn xác định xem xâu \\(S\\) có phải là dãy ngoặc đúng hay không. Nhắc lại, quá trình sẽ kết luận xâu \\(S\\) không phải dãy ngoặc đúng khi:
* Ký tự đang xét là dấu đóng ngoặc và Stack đang rỗng.
* Sau khi xử lý, Stack không rỗng.

Trường hợp 1 xảy ra khi xâu \\(S\\) có một tiền tố mà số dấu ngoặc đóng nhiều hơn số dấu ngoặc mở. Trường hợp 2 xảy ra khi xâu \\(S\\) có số dấu ngoặc mở nhiều hơn số dấu ngoặc đóng. Cả hai trường hợp trên đều là dấu hiệu của dãy ngoặc không đúng nêu trong **hệ quả 1**. Vậy quá trình sẽ luôn xác định \\(S\\) là dãy đúng hay không.

Từ bây giờ, ta mặc định \\(S\\) là dãy ngoặc đúng, và chứng minh rằng việc sử dụng Stack sẽ **luôn chỉ ra các cặp dấu ngoặc tương ứng**.

Quan sát quá trình trên, ta có một nhận xét quan trọng: sau khi xử lý một dãy ngoặc đúng trên Stack \\(st\\) thì Stack sẽ giữ nguyên trạng thái. Điều này là đúng do mỗi dấu mở ngoặc được \\(push\\) vào Stack và \\(pop\\) khỏi Stack đúng một lần.

Theo **tính chất 4**, \\(S\\) có thể được tách thành tổng của các dãy ngoặc đúng cơ bản \\(s_1 + s_2 + ... + s_k\\). Theo **tính chất 5**, \\(s_i = ( \ + s' + \ )\\), với \\(s'\\) là dãy ngoặc đúng, có thể là xâu rỗng. Vì sau khi xử lý các dãy \\(s_1, s_2, ...\\) thì Stack sẽ trở về trạng thái rỗng, nên ta chỉ cần xem xét quá trình với dãy ngoặc đúng cơ bản \\(s_i\\):

* Đẩy dấu ngoặc mở vào Stack
* Xử lý dãy ngoặc đúng \\(s'\\) để tìm các cặp dấu ngoặc tương ứng trong đó. Sau bước này, ta tìm được tất cả cặp dấu tương ứng trong \\(s'\\).
* Xét dấu ngoặc đóng ở cuối \\(s_i\\). Do sau khi xử lý dãy ngoặc đúng, Stack chỉ còn một phần tử là dấu ngoặc mở được thêm vào từ đầu, ta tìm được một cặp dấu ngoặc tương ứng, và xóa dấu ngoặc mở khỏi Stack
* Stack trở về trạng thái rỗng

Như vậy, quá trình sẽ xác định tất cả các cặp dấu ngoặc tương ứng.

#### Cài đặt

Ta có thể cài đặt bài toán đúng như mô tả của quá trình nêu trên:

```cpp
stack<int> st;
vector<pair<int, int>> matches; // lưu các cặp dấu ngoặc tương ứng

bool solve(string s)
{
    int n = (int)s.size();
    for (int i = 0; i < n; ++i)
    {
        if (s[i] == '(') // chỉ đẩy dấu ngoặc mở vào Stack
            st.push(i);
        else
        {
            if (st.empty()) return false; // dãy không phải là dãy ngoặc đúng
            matches.push_back({st.top(), i}); // tìm thấy một cặp tương ứng
            st.pop();
        }
    }
    if (!st.empty()) return false; // nếu Stack không rỗng thì dãy không đúng
    return true;
}
```

### Mở rộng
Bài toán 2 có thể được mở rộng thêm: dãy có thể có cả ngoặc vuông và ngoặc nhọn. Rõ ràng, ta có thể xử lý các loại ngoặc như cách ta làm với bài toán 2. Lưu ý duy nhất là ta cần phải kiểm soát thêm cả kiểu loại của dấu.

Minh họa cho quá trình với \\(S = \\) "\\(([\{\}])()\\)":
![](https://i.imgur.com/EFJVEf9.png)

## Sử dụng Stack để khử đệ quy

Vì tính chất **LIFO** của Stack, nó có thể được sử dụng để khử các hàm đệ quy. Trên thực tế, khi ta dùng hàm đệ quy, hệ thống sẽ tự động tạo một cấu trúc **LIFO** như Stack để chứa và thực hiện các lời gọi hàm.

Xét thuật toán DFS với cách cài đặt sử dụng đệ quy:

```cpp
void dfs(int start)
{
    visited[start] = true; // đánh dầu đỉnh đã thăm
    for (int u : adj[start]) // với các đỉnh thuộc danh sách kề của đỉnh đang xét
    {
        if (visited[u])
            continue;
        dfs(u); // đệ quy: thăm u
    }
}
```

Ta có thể cài đặt DFS sử dụng Stack:

```cpp
void dfs(int start)
{
    stack<int> st;
    st.push(start); // ta bắt đầu từ đỉnh "start"
    
    while (!st.empty())
    {
        int v = st.top(); // thăm đỉnh v ở đỉnh Stack
        st.pop(); // loại bỏ đỉnh v khỏi Stack do đã thăm
        visited[v] = true; // đánh dấu v đã thăm
        
        for (int u : adj[v]) // xét các đỉnh của đồ thị chung cạnh với v
        {
            if (visited[u]) // nếu đã thăm thì thôi
                continue;
            st.push(u); // đẩy đỉnh u vào Stack thay vì gọi đệ quy đến u
        }
    }
}
```

Trong cách cài đặt DFS đệ quy, một nhánh đệ quy luôn phải được xử lý trọn vẹn trước khi ta gọi đệ quy đến nhánh khác. Nói cách khác, khi ta thăm một đỉnh \\(v\\) thì ta phải thăm toàn bộ những đỉnh kề với nó, và cứ tiếp tục như vậy đến khi không còn đỉnh nào thăm được nữa. Stack hoạt động trên nguyên lý tương tự: những đỉnh được đẩy vào Stack sau đều được xử lý trọn vẹn trước những đỉnh được đẩy vào sớm hơn. Do đó, lời giải trên là đúng đắn.

Việc dùng Stack để khử đệ quy có thể áp dụng với mọi hàm có tính chất đệ quy. Trên lý thuyết, độ phức tạp thời gian và bộ nhớ của 2 cách cài đặt dùng Stack và dùng đệ quy là như nhau, nhưng trên thực tế, cách cài đặt dùng Stack thường hiệu quả hơn về mặt bộ nhớ, do việc gọi đệ quy chịu ảnh hưởng bởi [Function Overhead](https://en.wikipedia.org/wiki/Overhead_(computing)). Đổi lại, cách cài đặt dùng Stack thường khiến code trở nên phức tạp và thiếu trực quan hơn.

Trong lập trình thi đấu, ta có thể sử dụng đệ quy thông thường trong hầu hết các trường hợp. Ta chỉ cần dùng Stack khi hàm đệ quy quá sâu và có nguy cơ bị [tràn bộ nhớ](https://vi.wikipedia.org/wiki/L%E1%BB%97i_tr%C3%A0n_b%E1%BB%99_nh%E1%BB%9B_%C4%91%E1%BB%87m). Theo kinh nghiệm của người viết, ta cần khử đệ quy khi hàm có thể đạt độ sâu khoảng \\(10^7\\).

## Stack đơn điệu

Stack đơn điệu là ngăn xếp mà các phần tử của nó xét từ đáy của Stack đến đỉnh Stack tạo thành một dãy số đơn điệu.

Hình ảnh minh họa cho một Stack đơn điệu giảm:

![](https://i.imgur.com/bzwD9F1.png)

### Bài toán

Cho mảng \\(A\\) có \\(n\\) phần tử \\(a_1, a_2, \dots, a_n\\), \\(n \leq 10^6\\). Với mỗi \\(i\\) từ \\(1\\) đến \\(n\\) ta cần tìm \\(j\\) sao cho \\(a_j > a_i\\), và \\(\lvert i - j \rvert\\) nhỏ nhất. Nếu không tồn tại \\(j\\), in ra \\(-1\\).

#### Nhận xét

Ta sẽ bài toán đơn giản hơn: với mỗi \\(i\\) ta chỉ cần tìm \\(j\\) thỏa mãn điều kiện gốc, *mà \\(j < i\\)*. Rõ ràng, nếu ta giải được bài toán này thì bài toán gốc cũng có thể dễ dàng giải được, vì nếu \\(j > i\\) thì ta có thể duyệt ngược lại mảng \\(A\\), đưa bài toán về dạng đơn giản như đã nói.

Do \\(n \leq 10^6\\) nên cách giải hồn nhiên: với mỗi \\(i\\) ta lại xét \\(j\\) từ \\(1\\) đến \\(n\\) là chưa đủ để giải quyết bài toán, do độ phức tạp thời gian lên tới \\(O(n^2)\\).

#### Mô hình lại bài toán

Xét mô hình sau:
* Phần tử thứ \\(i\\) của mảng \\(A\\) tượng trưng cho một người có chiều cao \\(a_i\\).
* Lần lượt người từ \\(1\\) đến \\(n\\) xếp thành một hàng. Người thứ \\(i\\) sẽ *nhìn được* người thứ \\(j\\) nếu \\(j\\) đứng trước \\(i\\) trong hàng.
* Hàng luôn nhìn từ cuối về đầu.

Theo mô hình này, giá trị \\(j\\) gần \\(i\\) nhất \\((j < i)\\) mà \\(a_i < a_j\\) chính là chỉ số của người gần nhất cao hơn người \\(i\\) mà anh ta có thể nhìn được.

Hình ảnh minh họa, số ở hàng trên là chiều cao mỗi người, ở hàng dưới là chỉ số người gần nhất ở bên trái cao hơn họ:

![](https://i.imgur.com/KZWZoll.png)

Ta có thể cải tiến mô hình bằng việc chỉnh sửa cách thức xếp hàng.
Khi người thứ \\(i\\) xếp hàng, họ sẽ thực hiện các thao tác sau:
1. Xếp vào cuối hàng
2. Nếu họ đứng đầu hàng thì ghi lại số \\(-1\\). Mặt khác, nếu người đứng trước họ có chiều cao thấp hơn hoặc bằng với \\(a_i\\), đuổi người đó ra khỏi hàng. Lặp lại quá trình đuổi người đứng trước thấp hơn cho tới khi người \\(i\\) đứng đầu hàng, hoặc người đứng trước có chiều cao lớn hơn. Ghi lại chỉ số của người đứng trước, hoặc \\(-1\\) nếu họ đứng đầu hàng.

Ta sẽ chứng minh số mà mỗi người ghi lại chính là chỉ số của người gần nhất đứng trước mà cao hơn họ.

Lúc đầu, cho một người có chỉ số \\(-1\\), chiều cao \\(+\infty\\). Việc đứng đầu hàng có thể coi như đứng ngay sau người chỉ số \\(-1\\) này. Xét một người \\(i\\) bất kỳ ghi lại số \\(j\\), \\(j < i\\). Trước hết, \\(a_j\\) chắc chắn phải lớn hơn \\(a_i\\). Giả sử ngược lại, \\(j\\) không phải là người gần \\(i\\) nhất mà cao hơn người \\(i\\), mà \\(k\\) mới là người như vậy. Ta có \\(j < k < i\\) và \\(a_k > a_i\\). Tại thời điểm người \\(i\\) xếp vào hàng thì người \\(k\\) này *không còn trong hàng nữa* (nếu còn thì họ sẽ ghi lại người \\(k\\) chứ không phải \\(j\\)). Do đó, người \\(k\\) đã bị đuổi khỏi hàng bởi một người nào đó đứng sau \\(k\\) và trước \\(i\\). Gọi chỉ số của người đó là \\(l\\). Để đuổi người \\(k\\) thì \\(a_l \geq a_k\\). Từ đó ta có \\(k < l < i, \ \ a_l \geq a_k > a_i\\), trái với giả thiết \\(k\\) là người gần \\(i\\) nhất mà cao hơn \\(i\\).

Như vậy, số mà mỗi người nhớ lại chính là **chỉ số của người gần nhất cao hơn họ** (\\(-1\\) nếu không tồn tại người như vậy). Đây chính là giá trị \\(j\\) cần tìm với mỗi \\(i\\).

Giả sử mảng \\(A = [1, 2, 7, 4, 3, 6]\\). Các bước diễn ra như sau:

![](https://i.imgur.com/39cNzvd.png)

Dễ thấy chiều cao của người trong hàng luôn tạo thành một dãy đơn điệu.

#### Cài đặt

Ta có thể biểu diễn mô hình nêu trên dưới dạng một Stack đơn điệu như sau:
* Người xếp vào hàng là phép \\(push\\)
* Đuổi người đứng trước là phép \\(pop\\)

Từ các bước nêu trong mô hình, có thể cài đặt lời giải như sau:
```cpp
stack<int> st;

for (int i = 1; i <= n; ++i)
{
    while (!st.empty() && a[st.top()] <= a[i])
        st.pop(); 
    int ans = -1;
    if (!st.empty())
        ans = st.top();
    cout << ans << ' ';
    st.push(i);
}
```

#### Đánh giá độ phức tạp

Độ phức tạp bộ nhớ của lời giải là \\(O(n)\\) do sử dụng Stack và một mảng chứa \\(n\\) phần tử.

Thoạt nhìn, độ phức tạp tính toán của lời giải có vẻ là \\(O(n^2)\\) do có vòng lặp \\(while\\) lồng trong vòng \\(for\\). Tuy nhiên, để ý rằng mỗi phần tử \\(a_i\\) đều được \\(push()\\) vào Stack đúng một lần, và bị \\(pop()\\) khỏi Stack tối đa 1 lần, nên độ phức tạp tính toán vẫn là \\(O(n)\\)

### Mở rộng

Bài toán gốc nêu trên có nhiều ứng dụng và mở rộng. Sau đây là một vài ví dụ.

#### Hình chữ nhật lớn nhất

[Link SPOJ](https://www.spoj.com/PTIT/problems/SSAM219G/).

Vẽ \\(n\\) cột hình chữ nhật sát nhau. Cột thứ \\(i\\) có chiều rộng \\(1\\) và chiều cao \\(h_i\\). Tìm hình chữ nhật có diện tích lớn nhất tạo bởi các cột.

Ví dụ:
\\(h = \{2, 4, 4, 3, 2\}\\)

Hình chữ nhật lớn nhất có diện tích \\(10\\)

![](https://i.imgur.com/wm76udO.png)

##### Cách giải

Để ý rằng hình chữ nhật lớn nhất luôn có chiều cao bằng với chiều cao của một cột đã có.

Với mỗi cột \\(i\\), ký hiệu \\(L_i\\), \\(R_i\\) là cột gần nhất ở bên trái/phải \\(i\\) có chiều cao **nhỏ hơn \\(i\\)**. Việc tìm cột gần nhất ở bên trái/phải cột \\(i\\) mà thấp hơn \\(h_i\\) chính là bài toán gốc nêu ở mục trước. Ta chỉ cần sửa đổi thay vì tìm cột cao hơn thì phải tìm cột thấp hơn.

Khi đã xác định các mảng \\(L\\) và \\(R\\), ta có thể xét từng cột \\(i\\) từ \\(1\\) đến \\(n\\). Giả sử hình chữ nhật có chiều cao bằng với cột đang xét. Khi đó, chiều dài lớn nhất của hình chữ nhật là từ cột gần nhất bên trái thấp hơn cột \\(i\\) đến cột gần nhất bên phải thấp hơn cột \\(i\\). Diện tích của hình chữ nhật lớn nhất qua cột \\(i\\) là: \\((R_i - L_i - 1) * h_i\\).

Vậy diện tích hình chữ nhật lớn nhất chính là giá trị \\((R_i - L_i - 1) * h_i\\) lớn nhất với mọi \\(i\\) từ \\(1\\) đến \\(n\\).

Độ phức tạp thời gian và bộ nhớ của lời giải là \\(O(n)\\).

#### Hình chữ nhật lớn nhất trong lưới ô vuông

[Link SPOJ](https://vn.spoj.com/problems/QBRECT/)

Đây là một mở rộng của bài toán trước. Cho lưới ô vuông \\(n \times m\\), các ô có giá trị \\(0\\) hoặc \\(1\\). Ta cần tìm hình chữ nhật có diện tích lớn nhất có tất cả ô vuông có cùng giá trị.

##### Cách giải

Ta có thể chia bài toán thành 2 trường hợp riêng biệt: tìm hình chữ nhật chỉ gồm các ô giá trị \\(0\\) và chỉ gồm các ô giá trị \\(1\\). Nếu giải được một trường hợp, ta cũng có thể dễ dàng giải trường hợp còn lại. Từ giờ, ta sẽ giải bài toán tìm hình chữ nhật lớn nhất *chỉ chứa giá trị \\(1\\)*.

Ta xét lưới ô vuông con của lưới gốc, kích thước \\(k \times m\\). Nói cách khác, lưới ô vuông con này chính là \\(k\\) hàng đầu tiên của lưới gốc. Với mỗi \\(k\\) từ \\(1\\) đến \\(n\\), ta xét chiều cao của các cột chứa toàn số \\(1\\) dựng trên từng vị trí trong hàng. Sau đó, ta có thể áp dụng bài toán tìm hình chữ nhật lớn nhất tạo bởi các cột để giải quyết vấn đề.

```cpp
for (int i = 1; i <= m; ++i) h[i] = 0;
for (int k = 1; k <= n; ++k)
{
    for (int j = 1; j <= m; ++j)
    {
        if (grid[k][j] == 1) ++h[j];
        else h[j] = 0;
    }
    // giải bài toán tìm hình chữ nhật lớn nhất trong các cột...
}
```

Độ phức tạp thời gian và bộ nhớ của lời giải là \\(O(n \times m)\\).

# Bài tập áp dụng
* [JNEXT](https://www.spoj.com/problems/JNEXT/)
* [STPAR](https://www.spoj.com/problems/STPAR/)
* [280B - Codeforces](https://codeforces.com/problemset/problem/280/B)
* [1132G - Codeforces](https://codeforces.com/problemset/problem/1132/G)
* Tham khảo thêm tại: [VNOI Problem List](https://vnoi.info/problems/list/)