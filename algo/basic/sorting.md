# Thuật toán sắp xếp #

**Tác giả: [timmac](https://www.topcoder.com/member-profile/timmac)**

## Giới thiệu ##
Trong ngành máy tính, một vài ứng dụng thực tế cần đến tính đúng thứ tự. Ngay cả trước khi con người bắt đầu dùng đến máy tính, chúng ta đã dùng đến sắp xếp. Với những bức ảnh mà người cao thì đứng sau đến cả người bán hàng có tiền thưởng Giáng Sinh cao nhất, nhu cầu sắp xếp từ nhỏ đến lớn hoặc từ đầu tiên đến cuối cùng không thể bị coi thường.

Khi ta gọi các truy vấn trong database, và dùng cấu trúc ORDER BY, chúng ta đang sắp xếp. Khi ta tìm kiếm một số điện thoại trong cuốn liên lạc, chúng ta đang tìm trên một danh sách sắp xếp sẵn. (Thử tưởng tượng nếu chúng không được sắp xếp!) Nếu bạn cần tìm kiếm nhị phân một giá trị trên một mảng, điều đầu tiên là phải sắp xếp lại mảng đó đã. Khi một đề bài đòi hỏi bạn phải xuất ra kết quả thỏa mãn đầu tiên, ... ừ thì bạn hiểu ý tưởng rồi đó.

### Ý tưởng đầu tiên ###
Tưởng tượng có một nhóm người, trong đó mỗi người được phát một bộ bài đã được xáo, và được yêu cầu sắp xếp lại các lá đó theo trình tự tăng dần. Một vài người bắt đầu phân ra thành các nhóm, người thì trải tất cả lá ra, người thì tráo đổi các lá trên tay họ. Đối với một vài người, vấn đề chỉ còn là thời gian, nhưng đối với người khác đó sẽ là những phút dai dẳng hoặc lâu hơn. Sau đây là các điều cơ bản, các điểm mạnh và yếu của các thuật toán sắp xếp thông dụng.

Khi so sánh giữa các thuật toán này với nhau, có nhiều vấn đề phải quan tâm. Đầu tiên là thời gian chạy. Đối với các dữ liệu nhiều khủng khiếp, các thuật toán không hiệu quả sẽ chạy chậm kinh dị cho các ứng dụng thực tế.

Vấn đề cần quan tâm thứ 2 là không gian bộ nhớ. Các thuật toán nhanh đòi hỏi đệ quy sẽ tạo ra các bản copy của dữ liệu đang xử lí. Trong một vài trường hợp khi giới hạn bộ nhớ xảy ra (embedded system) một vài thuật toán sẽ là phi thực tế. Ở các trường hợp khác, có thể cải tiến thuật toán để không tạo ra các bản copy. Tuy nhiên, cải tiến này cũng ảnh hưởng đến tốc độ xử lí.

Vấn đề thứ 3 là độ ổn định. Độ ổn định được định nghĩa đơn giản là điều gì sẽ xảy ra với các giá trị giống nhau. Đối với thuật toán sắp xếp ổn định, các phần tử bằng với khóa được chọn sẽ giữ nguyên sau khi sắp xếp như ban đầu. Đối với thuật toán sắp xếp không ổn định, không ai đảm bảo rằng điều đó sẽ giữ nguyên cả.

### Sắp xếp nổi bọt ###
Một trong những thuật toán ban đầu được dạy cho học sinh. Thuật toán chạy thường không đủ nhanh nhưng với dữ liẹu nhỏ, nó phục vụ được việc trình bày ý tưởng cơ bản của sắp xếp.

**Code:** 
```
for (int i = 0; i < data.Length; i++)
   for (int j = 0; j < data.Length - 1; j++)
      if (data[j] > data[j + 1])
      {
         tmp = data[j];
         data[j] = data[j + 1];
         data[j + 1] = tmp;
      }
```

Ý tưởng: đi qua từng phần tử từ đầu tới cuối, và tráo đổi nếu phần tử đầu lớn hơn phần tử liền kề sau nó. Vì thế, phần tử nhỏ nhất sẽ "nổi" lên trên bề mặt. Độ phức tạp thuật toán là $O(n^{2})$, tức rất chậm so với các dữ liệu lớn. Điểm lợi duy nhất của thuật toán này, là nó dễ hiểu và dễ nhớ. Ngoài ra, không có thêm bộ nhớ nào cần dùng.

### Sắp xếp chèn ###

Thuật toán này cơ bản là cố gắng tìm cách sắp xếp các phần tử giống nhau đúng một lần. Với mỗi thao tác, ta lấy phần tử kế bên cho vào hàng đợi, rồi chuyển nó qua kế tiếp phần tử có giá trị bằng nó đã đúng vị trí.

**Code:**
```
for (int i = 0; i <= data.Length; i++) {
   int j = i;
   while (j > 0 && data[i] < data[j - 1])
      j--;
   int tmp = data[i];
   for (int k = i; k > j; k--)
      data[k] = data[k - 1];
   data[j] = tmp;
}
```

Dữ liệu sẽ thay đổi như sau:
```
{18,  6,  9,  1,  4, 15, 12,  5,  6,  7, 11}
{ 6, 18,  9,  1,  4, 15, 12,  5,  6,  7, 11}
{ 6,  9, 18,  1,  4, 15, 12,  5,  6,  7, 11}
{ 1,  6,  9, 18,  4, 15, 12,  5,  6,  7, 11}
{ 1,  4,  6,  9, 18, 15, 12,  5,  6,  7, 11}
{ 1,  4,  6,  9, 15, 18, 12,  5,  6,  7, 11}
{ 1,  4,  6,  9, 12, 15, 18,  5,  6,  7, 11}
{ 1,  4,  5,  6,  9, 12, 15, 18,  6,  7, 11}
{ 1,  4,  5,  6,  6,  9, 12, 15, 18,  7, 11}
{ 1,  4,  5,  6,  6,  7,  9, 12, 15, 18, 11}
{ 1,  4,  5,  6,  6,  7,  9, 11, 12, 15, 18}
```

Một trong những lợi ích chính của thuật toán này là việc sắp xếp sẽ nhanh hơn với các danh sách mà các phẩn tử gần như đúng thứ tự. Ví dụ, khi một người cần sắp xếp các highscores trong game, sắp xếp chèn là một lựa chọn rất tốt.

### Sắp xếp trộn ###

Sắp xếp trộn hoạt động như đệ quy. Đầu tiên chia nửa dữ liệu, và sắp xếp từng cái riêng biệt nhau. Sau đó phần tử đầu tiên một trong hai phần đó sẽ được so sánh. Các phần tử tiếp theo thực hiện tương tự cho tới khi được một danh sách hoàn chỉnh.

**Code:**
```
int[] mergeSort (int[] data) {
   if (data.Length == 1)
      return data;
   int middle = data.Length / 2;
   int[] left = mergeSort(subArray(data, 0, middle - 1));
   int[] right = mergeSort(subArray(data, middle, data.Length - 1));
   int[] result = new int[data.Length];
   int dPtr = 0;
   int lPtr = 0;
   int rPtr = 0;
   while (dPtr < data.Length) {
      if (lPtr == left.Length) {
         result[dPtr] = right[rPtr];
         rPtr++;         
      } else if (rPtr == right.Length) {
         result[dPtr] = left[lPtr];
         lPtr++;
      } else if (left[lPtr] < right[rPtr]) {
         result[dPtr] = left[lPtr];
         lPtr++;
      } else {
         result[dPtr] = right[rPtr];
         rPtr++;         
      }
      dPtr++;
   }
   return result;
}
```

Mỗi lần gọi đệ quy mất $O(n)$, và tổng cộng cần $O(log{n})$ như vậy, do đó độ phức tạp thuật toán là $O(n*log{n})$. Thuật toán này có thể được cải thiện để sắp xếp một danh sách gần như đúng thứ tự. Sau khi đã sắp xếp từng nửa danh sách, nếu phần tử cao nhất của phần này nhỏ hơn phần tử nhỏ nhất của phần kia, thủ tục trộn không cần thiết nữa. (Ví dụ là phần Java API là phần cải tiến thuật toán này). Dữ liệu, qua từng lời đệ quy, sẽ như thế này:
```
{18, 6, 9, 1, 4, 15, 12, 5, 6, 7, 11}
{18, 6, 9, 1, 4} {15, 12, 5, 6, 7, 11}
{18, 6} {9, 1, 4} {15, 12, 5} {6, 7, 11}
{18} {6} {9} {1, 4} {15} {12, 5} {6} {7, 11}
{18} {6} {9} {1} {4} {15} {12} {5} {6} {7} {11}
{18} {6} {9} {1, 4} {15} {5, 12} {6} {7, 11}
{6, 18} {1, 4, 9} {5, 12, 15} {6, 7, 11}
{1, 4, 6, 9, 18} {5, 6, 7, 11, 12, 15}
{1, 4, 5, 6, 6, 7, 9, 11, 12, 15, 18}
```

Ngoài việc hiệu quả, sắp xếp trộn còn có thể giúp giải các bài toán khác, chẳng hạn như xác định "danh sách đã sắp xếp".

### Sắp xếp vun đống ###

Trong sắp xếp vun đống, ta tạo một cấu trúc heap từ dữ liệu. Cấu trúc heap là cấu trúc lưu dữ liệu sao cho phần tử nhỏ nhất (hoặc lớn nhất) luôn ở nút gốc. (Heap còn được gọi là hàng đợi ưu tiên, xem qua [Data Structures](http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=dataStructures)). Để thực hiện, dữ liệu được đưa vào heap và nút gốc được thay thế liên tục. Từ khi nút gốc là phần tử nhỏ nhất, kết quả là một danh sách đã sắp xếp. Nếu bạn đã có code Heap haowjc bạn dùng Java PriorityQueue (điểm mới trong bản 1.5), code thuật toán này khá ngắn.

**Code:**
```
Heap h = new Heap();
for (int i = 0; i < data.Length; i++)
   h.Add(data[i]);
int[] result = new int[data.Length];
for (int i = 0; i < data.Length; i++)
   data[i] = h.RemoveLowest();
```

Độ phức tạp thuật toán này là giới hạn trên của $O(n*log{n})$. Ngoài ra, thuật toán này yêu cầu thêm bộ nhớ là kích cỡ của dữ liệu. Sắp xếp vun đống có điểm yếu là không ổn định, và khó hiểu hơn các thuật toán sắp xếp cơ bản.

### Sắp xếp nhanh ###

Như tên gọi, đây là một thuật toán rất hiệu quả. Cấu trúc đằng sau nó là cách mà con người thường hay sắp xếp. Đầu tiên chia thành hai nhóm, nhóm các phần tử "lớn" và nhóm các phần tử "nhỏ". Sau đó, gọi đệ quy hai nhóm.

**Code:**
```
Array quickSort(Array data) {
   if (Array.Length <= 1)
      return;
   middle = Array[Array.Length / 2];
   Array left = new Array();
   Array right = new Array();
   for (int i = 0; i < Array.Length; i++)
      if (i != Array.Length / 2) {
         if (Array[i] <= middle)
            left.Add(Array[i]);
         else
            right.Add(Array[i]);
      }
   return concatenate(quickSort(left), middle, quickSort(right));
}
```

Thách thức trong sắp xếp nhanh là xác định phần tử khóa làm mốc chia thành hai nhóm. Độ phức tạp thuật toán này phụ thuộc vào chọn phần tử đó chính xác như thế nào. Trong trường hợp tốt nhất, độ phức tạp là $O(n*log{n})$, và xấu nhất đối với hai tập có cùng một phần tử là $O(n^{2})$. Dữ liệu sẽ thay đổi như sau:
```
{18, 6, 9, 1, 4, 15, 12, 5, 6, 7, 11}
{6, 9, 1, 4, 12, 5, 6, 7, 11} {15} {18}
{6, 9, 1, 4, 5, 6, 7, 11} {12} {15} {18}
{1, 4} {5} {6, 9, 6, 7, 11} {12} {15} {18}
{1} {4} {5} {6} {6} {9, 7, 11} {12} {15} {18}
{1} {4} {5} {6} {6} {7} {9, 11} {12} {15} {18}
{1} {4} {5} {6} {6} {7} {9} {11} {12} {15} {18}
```

Nếu biết rõ các phần tử cần sắp xếp thuộc phần nào nhất định, bạn có thể cải thiện thuật toán bằng cách chọn phần tử khóa chia dữ liệu thành hai tập chính xác nhất có thể. Cải tiến chung là chọn phần tử khóa chú ý đến giới hạn các phần tử hoặc random.

### Sắp xếp cơ số ###

Thuật toán này được thiết kế sao cho vẫn sắp xếp nhưng không so sánh trực tiếp các phần tử. Đầu tiên, thuật toán sẽ lấy các chữ số cuối (hoặc nhiều chữ số, các bit), và đưa các phần tử vào các nhóm. Nếu ta lấy 4 bit một lúc, ta cần 16 nhóm. Sau đó ta đưa các nhóm lại với nhau, và được danh sách sắp xếp theo chữ số cuối của các phần tử. Quá trình này lặp đi lặp lại với chữ số át cuối cho tới khi tất cả vị trí chữ số đã sắp xếp.

Lấy ví dụ, hãy xem qua một dãy các số sắp xếp bằng cách lấy 1 bit. Lưu ý rằng, chúng ta tốn 4 bước để có được kết quả, và mỗi bước ta dùng đúng 2 nhóm:
```
{6, 9, 1, 4, 15, 12, 5, 6, 7, 11}
{6, 4, 12, 6} {9, 1, 15, 5, 7, 11}
{4, 12, 9, 1, 5} {6, 6, 15, 7, 11}
{9, 1, 11} {4, 12, 5, 6, 6, 15, 7}
{1, 4, 5, 6, 6, 7} {9, 11, 12, 15}
```

Lấy 2 bit, chúng ta cần 2 bước và 4 nhóm:
```
{6, 9, 1, 4, 15, 12, 5, 6, 7, 11}
{4, 12} {9, 1, 5} {6, 6} {15, 7, 11}
{1} {4, 5, 6, 6, 7} {9, 11} {12, 15}
```

Lấy 4 bit và chỉ cần 1 bước, cùng 16 nhóm:
```
{6, 9, 1, 4, 15, 12, 5, 6, 7, 11}
{1} {} {} {4} {5} {6, 6} {7} {} {9} {} {11} {12} {} {} {15}
```

Chú ý rằng, với ví dụ cuối, ta có nhiều nhóm rỗng. Điều này giải thích rằng, ta có bao nhiêu bit ta có thể chọn hơn trước khi dùng đến giới hạn bộ nhớ. Thời gian thực hiện giống như số các xô càng lớn đưa thành một danh sách có thể đôi lúc phải xem xét.

Bởi vì hiệu quả sắp xếp cơ số khác với sắp xếp so sánh bình thường, nó có thể có hiệu quả cao hơn nữa. Độ phức tạp là $O(n*{k})$ với k là kích cỡ của khóa. (số nguyên 32 bit, nếu lấy 4 bit, k=8). Điểm yếu cơ bản là một vài dữ liệu rất dài (như chuỗi), hoặc khó dùng thuật toán này (chẳng hạn kiểu negative floating-point là một ví dụ).

### Các thư viện dùng để sắp xếp ###

Ngày nay, đại đa số các ngôn ngữ lập trình đã bao gồm nhiều thư viện cung cáp các thuật toán tốt cho chúng ta. Như .NET framework, Java API, và C++ STL, tất cả đều đã có sẵn thuật toán sắp xếp. Và tốt nhất là cấu trúc cơ bản của nó giống nhau từ ngôn ngữ này đến ngôn ngữ khác.

Với các kiểu dữ liệu điển hình như scalars, floats, chuỗi, mọi thứ cần dùng để sắp xếp đã có sẵn. Nhưng nếu ta có dữ liệu cần thuật toán sắp xếp phức tạp hơn? Rất may, lập trình hướng đối tượng đã cho ta các thư viện kinh điển để giải quyết việc này.

Trong cả Java và C# (cũng như VB), có giao diện gọi là Comparable (IComparable in .NET). Bằng việc chạy giao diện IComparable trên một class đã khai báo, bạn thêm hàm ***int CompareTo (object other)***, hàm này sẽ trả về một kết quả, kết quả đó sẽ <=0, hoặc là một số dương lớn hơn tham số. Thư viện chứa hàm sort sẽ chạy tốt trên kiểu dữ liệu mới.

Ngoài ra, có một giao diện khác gọi là Comparator (IComparer in .NET), mà đã định nghĩa một hàm riêng biệt ***int Compare (object obj1, object obj2)***, nó sẽ trả về một giá trị chỉ ra kết quả của việc so sánh hai tham số.

Hạnh phúc nhất của các hàm sắp xếp được cung cấp trong thư viện là nó cứu ta rất nhiều thời gian khỏi việc code, đỡ rối hơn, không cần phải khó khăn nỗ lực. Tuy nhiên, dù tất cả mọi việc đã được chuẩn bị sẵn, biết được hoạt động của nó vẫn rất hay.