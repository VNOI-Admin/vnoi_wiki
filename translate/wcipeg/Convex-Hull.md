# Bao lồi (Convex Hull)

Nguồn: [wcipeg](http://wcipeg.com/wiki/Convex_hull)

[[_TOC_]]

Trong **hình học tính toán** (**computational geometry**), **bao lồi** (**convex hull**) của một tập điểm là tập lồi nhỏ nhất (theo diện tích, thể tích, ...) mà tất cả các điểm đều nằm trong tập đó.

[[/uploads/algo_geometry_convex_hull_illustration.gif]]


# Giải thích trực quan về bao lồi trên mặt phẳng

- Nếu ta coi các điểm trong một tập hợp là các cái đinh đóng trên một tấm gỗ, bao lồi của tập điểm đó có viền ngoài tạo bởi sợi dây chun mắc vào các cái đinh sau khi bị kéo căng về các phía.

[[/uploads/algo_geometry_convex_hull_nail.png]]

- Nếu ta coi các điểm trong một tập hợp là các con cừu trên đồng cỏ, bao lồi của tập điểm đó có viền ngoài là hàng rào có độ dài nhỏ nhất bao quanh tất cả các con cừu

- Nếu ta coi các điểm trong một tập hợp là các đầu mút có thể của các hàng rào, bao lồi của tập điểm đó có viền ngoài là các hàng rào thẳng có điểm đầu và điểm cuối thuộc tập điểm đó và bao quanh diện tích lớn nhất.

- Nếu ta coi các điểm trong một tập hợp là các cái cây, chu vi của bao lồi là độ dài tối thiểu của dải ruy băng bao quanh tất cả các cây đó.


# Thuật toán tìm bao lồi trên mặt phẳng

Bài toán tìm bao lồi của một tập điểm trên mặt phẳng là một trong những bài toán được nghiên cứu nhiều nhất trong hình học tính toán và có rất nhiều thuật toán để giải bài toán này. Sau đây là ba thuật toán phổ biến nhất, được giới thiệu theo thứ tự tăng dần về độ khó.

## Thuật toán bọc gói

**Thuật toán bọc gói** (**Gift wrapping algorithm**) hay còn gọi là thuật toán **Jarvis march** là một trong những thuật toán tìm bao lồi đơn giản và dễ hiểu nhất. Tên thuật toán xuất phát từ sự tương tự của thuật toán với việc đi bộ xung quanh các điểm và cầm theo một dải băng gói quà.

- Bước đầu tiên của thuật toán là chọn một điểm chắc chắn nằm trong bao lồi, ví dụ, điểm có tung độ lớn nhất (nếu có nhiều điểm cùng có tung độ lớn nhất thì có thể chọn điểm tung độ lớn nhất và hoành độ lớn nhất).
- Xuất phát từ điểm này, mục tiêu của ta là sẽ lần lượt đi đến các điểm khác cho đến khi quay trở lại điểm ta chọn lúc đầu.
- Ban đầu, ta nhìn về phía bên phải. Khi đi đến các điểm khác, ta sẽ lưu lại:
  - Điểm $P$ mà ta đang chọn
  - vector $\vec{v}$ chỉ hướng ta đang nhìn.
- Tiếp theo, thuật toán sẽ lặp lại liên tục các bước sau cho đến khi tìm được bao lồi.
  - Ta quay mặt theo chiều kim đồng hồ cho đến khi ta nhìn thấy một điểm, gọi điểm đó là $Q$.
  - Rồi ta cầm theo dải băng và đi đến điểm $Q$. Khi ta đến điểm đấy, ta thay:
    - $\vec{v}$ thành $\vec{PQ}$
    - $P$ thành $Q$.
- Thuật toán kết thúc, khi ta quay trở về điểm ban đầu. Lúc này ta đã đi đến tất cả các đỉnh của bao lồi theo chiều kim đồng hồ.

Để xác định điểm ta nhìn thấy đầu tiên khi ta quay mặt theo chiều kim đồng hồ, ta duyệt tất cả các điểm $R$ trong tập, ngoại trừ điểm $P$. Với mỗi điểm, ta xét vector $\vec{u}=\vec{PR}$; $\vec{u}$ tạo với $\vec{v}$  một góc $\theta$ nhỏ nhất sẽ tương ứng với điểm $Q$ (dễ dàng chứng minh được điều này). Để tìm $\theta$ nhỏ nhất, ta tìm $\cos{\theta}$ lớn nhất, mà ta lại dễ dàng tính được $\cos{\theta}$ bằng công thức $\frac{\vec{u}.\vec{v}}{\|\vec{u}\|\|\vec{v}\|}$.

Với mỗi lần tìm điểm tiếp theo, ta cần duyệt qua tất cả các điểm trong tập, vì vậy độ phức tạp của mỗi lần tìm điểm là $O(n)$ với $n$ là số lượng điểm trong tập. Số lần tìm điểm tiếp theo phụ thuộc vào số lượng điểm là đỉnh của bao lồi, gọi số lượng điểm đó là $h$, khi đó độ phức tạp của cả thuật toán là $O(nh)$. Trong trường hợp xấu nhất, $h=n$ hay tất cả các điểm trong dữ liệu vào tạo thành một đa giác lồi, độ phức tạp của thuật toán là $O(n^2)$, không đủ nhanh khi $n>5000$.

## Thuật toán Graham

Thuật toán Graham có độ phức tạp trong trường hợp xấu nhất nhỏ hơn thuật toán bọc gói, song thuật toán Graham lại phức tạp hơn.

- Đầu tiên, ta xác định một điểm mà chắc chắn thuộc bao lồi. Thông thường, khi cài đặt người ta chọn điểm có tung độ nhỏ nhất (nếu có nhiều điểm như vậy thì chọn điểm trái nhất). Gọi điểm này là điểm $O$.
- Chọn hệ trục tọa độ có gốc là điểm vừa chọn, đổi các tọa độ các điểm còn lại theo hệ trục tọa độ mới (chú ý lúc cài đặt thường ta không đổi trục tọa độ, nhưng khi tính góc hoặc sắp xếp ở bước tiếp theo cần chú ý tránh nhầm lẫn).
- Tiếp theo, ta sắp xếp các điểm còn lại theo thứ tự tăng dần của góc tạo bởi trục hoành theo chiều dương và $\vec{OI}$ với $I$ là một trong các điểm còn lại.
- Ta xét các điểm theo thứ tự ta vừa sắp xếp, với mỗi điểm ta sửa lại bao lồi $H$. Gọi điểm đầu tiên được cho vào bao lồi $H$ là $H_1$, điểm cuối cùng là $H_h$ (ban đầu $h = 0$). Khi xét mỗi điểm ta làm như sau:
  1. Thêm điểm $P$ vào cuối bao lồi $H$. Tức là ta tăng $h$ lên 1 và đặt $H_h=P$.
  2. Nếu $h<3$, xét tiếp điểm tiếp theo, ngược lại làm bước 3.
  3. Xét 3 điểm $H_h,H_{h−1}$ và $H_{h−2}$. Có thể sau khi cho thêm điểm $H_h$, ta biết được điểm $H_{h−1}$ chắc chắn không nằm trong bao. Gọi $\vec{u} =\overrightarrow{H_{h−2}H_{h−1}}$ và $\vec{v} =\overrightarrow{H_{h−1}H_h}$. Nếu khi đi theo hướng $\vec{v}$ rồi đi theo hướng $\vec{u}$  là ta đã bẻ góc ngược chiều kim đồng hồ, hay $\vec{u} \times \vec{v} > 0$, thì cả ba điểm đều tạm thuộc bao, và ta xét tiếp điểm tiếp theo. Nhưng nếu $\vec{u} \times \vec{v} < 0$, thì góc $\widehat{H_{h−2}H_{h−1}H_h}$ sẽ tạo ra đa giác lõm và điểm $H_{h−1}$ phải bị loại bỏ, có nghĩa là $H_{h−1}$ được đặt là $H_h$ và $h$ giảm đi 1. Sau đó quay lại bước 2 cho đến khi xét hết các điểm.

[[/uploads/algo_geometry_convex_hull_graham.png]]

Hình minh họa:

- Ta đang xây dựng bao lồi, đến vị trí $h = 4$
- Góc $\widehat{H_{h−2}H_{h−1}H_h}$ lõm, nên ta cần bỏ điểm $H_3$ khỏi bao lồi

Sau quá trình trên, ta đã có một bao lồi $H_1,H_2,...,H_h$ sắp xếp ngược chiều kim đồng hồ.

Để đảm bảo ta loại bỏ điểm và thêm điểm với độ phức tạp $O(1)$, ta có thể dùng cấu trúc dữ liệu [stack](http://vnoi.info/wiki/algo/data-structures/data-structures-overview#1-ctdl-l%C6%B0u-tr%E1%BB%AF_1-2-stack-queue-deque).

Về độ phức tạp của thuật toán, ta thấy bước sắp xếp các điểm có độ phức tạp $O(n \log{n})$. Mỗi điểm được cho vào bao nhiều nhất một lần nên tổng độ phức tạp của các bước thêm điểm là $O(n)$, và mỗi điểm bị loại ra khỏi bao nhiều nhất một lần nên tổng độ phức tạp của các bước xóa điểm là $O(n)$, do đó độ phức tạp của bước xét các điểm là $O(n)$. Vậy, độ phức tạp của thuật toán Graham là $O(n \log{n})$, phù hợp cho hầu hết các bài toán.

### Cài đặt

```pascal
type
  Point = record  // Kiểu dữ liệu điểm
    x,y: real;
    ind: integer; // chỉ số trong mảng ban đầu
  end;

var
  n: integer; // số điểm
  a, b: array[1..maxn] of Point; // a: mảng input, b: bao lồi

Procedure Swap(var p1, p2: Point); // Hàm đổi chỗ 2 điểm
Var
  temp: Point;
Begin
  temp:=p1; p1:=p2; p2:=temp;
End;

Function CCW(p1,p2,p3:Point):integer; // Xem từ p1 --> p2 --> p3 là rẽ trái (1), đi thẳng (0) hay rẽ phải (-1)
Var
  t, a1, a2, b1, b2: real;
Begin
  a1 := p2.x - p1.x;
  b1 := p2.y - p1.y;
  a2 := p3.x - p2.x;
  b2 := p3.y - p2.y;
  t  := a1*b2 - a2*b1;
  If abs(t) < esp then CCW:=0
  else if t<0 then CCW:=-1
  else CCW:=1;
End;

Function Lower(p1, p2: Point):boolean; // So sánh để sắp xếp các điểm theo góc
Var
  c: integer;
Begin
  c := CCW(a[1], p1, p2);
  Lower:=false;
  If (c > 0) then Lower:=true
  else If (c = 0) and ((p1.x<p2.x) or ((p1.x=p2.x) and (p1.y<p2.y)))
       then Lower:=true;
End;

Procedure QuickSort; // Sắp xếp các điểm của mảng a theo góc
  Procedure Sort(l, r: integer);
  Var
    i, j: integer;
    x: Point;
  Begin
    i := l; j := r; x := a[(l+r) div 2];
    repeat
      while lower(a[i], x) do inc(i);
      while lower(x, a[j]) do dec(j);
      if i <= j then
        begin
          Swap(a[i], a[j]);
          inc(i); dec(j);
        end;
    until i>j;
    if i<r then Sort(i, r);
    if l<j then Sort(l, j);
  End;
Begin
  If n > 2 then Sort(2, n);
End;

Procedure Graham;
Var
  i, c: integer;
Begin
  // Tìm điểm có tung độ nhỏ nhất
  c := 1;
  For i := 2 to n do
    If (a[i].y < a[c].y) or ((a[i].y = a[c].y) and (a[i].x < a[c].x)) then
      c := i;
  // Đổi chỗ điểm tung độ nhỏ nhất về a[1]
  Swap(a[c], a[1]);

  m := 2; b[1] := a[1]; b[2] := a[2];
  b[1].ind := 1; b[2].ind := 2;
  For i := 3 to n do
    begin
      // Loại bỏ b[m] nếu ta xác định được nó không thuộc bao lồi
      while (m > 1) and (CCW(b[m-1], b[m], a[i]) = -1) do dec(m);

      // Thêm điểm a[i] vào bao lồi
      inc(m);
      b[m] := a[i];
      b[m].ind := i;
    end;
End;
```

Bạn cũng có thể tham khảo thêm cài đặt C++ [ở đây](https://sites.google.com/site/kc97ble/arithmetic/graham-cpp-2/graham-cpp)

## Thuật toán chuỗi đơn điệu

Thuật toán **chuỗi đơn điệu** (**Monotone chain**) vừa dễ cài đặt, vừa là thuật toán nhanh nhất trong số 3 thuật toán được giới thiệu trong bài viết này. Thuật toán dựa trên việc tìm hai chuỗi đơn điệu của bao lồi: chuỗi trên và chuỗi dưới. Ta thấy điểm ở xa về phía bên phải nhất (từ đây gọi là điểm phải nhất) và điểm ở xa về phía bên trái nhất (từ đây gọi là điểm trái nhất) trong dữ liệu vào luôn là hai đỉnh của bao lồi. Phần bao lồi theo chiều kim đồng hồ tính từ điểm trái nhất và ngược chiều kim đồng hồ tính từ điểm phải nhất gọi là chuỗi trên, phần còn lại của bao lồi gọi là chuỗi dưới. Ta sẽ tìm chuỗi trên và chuỗi dưới độc lập với nhau.

- Bước đầu tiên là sắp xếp các điểm được cho theo thứ tự tăng dần theo hoành độ. Nếu hai điểm có cùng hoành độ, điểm có tung độ nhỏ hơn sẽ đứng trước.
- Ta xét việc xây dựng chuỗi trên. Gọi $H$ là chuỗi trên hiện tại và độ lớn của bao là $h$. Điểm đầu của chuỗi là $H_1$ và điểm cuối là $H_h$. Với mỗi điểm được xét:
  1. Thêm điểm này vào $H$.
  2. Nếu $h<3$, xét tiếp điểm tiếp theo.
  3. Gọi $\vec{u}=\overrightarrow{H_{h-2}H_{h-1}}$ và $\vec{v}=\overrightarrow{H_{h-1}H_h}$. Lần này, do ta đang di chuyển theo chiều kim đồng hồ để tìm chuỗi trên, ta kiểm tra xem $\vec{u} \times \vec{v}$ có nhỏ hơn 0 hay không. Nếu có, ta xét tiếp điểm tiếp theo. Nếu không, ta loại bỏ $H_{h-1}$ và quay lại bước 2.

Sau khi xét hết các điểm, $H$ sẽ chứa toàn bộ các điểm ở chuỗi trên. Sau đó, ta tìm chuỗi dưới bằng cách tương tự, chỉ khác là ta xét các điểm theo thứ tự ngược lại (tức là ta xét điểm trái nhất trước). Lưu ý không thêm điểm phải nhất hai lần. Khi thuật toán kết thúc, $H$ sẽ chứa tất cả các đỉnh của bao lồi, với điểm đầu được lặp lại ở cuối.

Thuật toán này cũng có độ phức tạp $O(n \log{n})$. Thuật toán chuỗi đơn điệu được khuyên dùng ở mọi bài toán tìm bao lồi, do nó đơn giản hơn thuật toán Graham và nhanh hơn một chút (do ta không phải tính góc).

### Cài đặt

```cpp
struct pt { // Kiểu điểm
  double x, y;
};

bool cmp (pt a, pt b) { // So sánh theo tọa độ x, trong trường hợp bằng nhau so sánh theo y
  return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw (pt a, pt b, pt c) { // a -> b -> c đi theo thứ tự xuôi chiều kim đồng hồ
  return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw (pt a, pt b, pt c) { // a -> b -> c đi theo thứ tự ngược chiều kim đồng hồ
  return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull (vector<pt> & a) {
  if (a.size() == 1) { // chỉ có 1 điểm
    return;
  }

  // Sắp xếp các điểm theo tọa độ x, nếu bằng nhau sắp xếp theo y
  sort (a.begin(), a.end(), &cmp);

  pt p1 = a[0],  p2 = a.back();

  vector<pt> up, down; // chuỗi trên và chuỗi dưới
  up.push_back (p1);
  down.push_back (p1);

  for (size_t i=1; i<a.size(); ++i) { // xét lần lượt các điểm
    // Thêm vào chuỗi trên
    if (i==a.size()-1 || cw (p1, a[i], p2)) {
      while (up.size()>=2 && !cw (up[up.size()-2], up[up.size()-1], a[i]))
        up.pop_back();
      up.push_back (a[i]);
    }

    // Thêm vào chuỗi dưới
    if (i==a.size()-1 || ccw (p1, a[i], p2)) {
      while (down.size()>=2 && !ccw (down[down.size()-2], down[down.size()-1], a[i]))
        down.pop_back();
      down.push_back (a[i]);
    }
  }

  // Gộp 2 chuỗi trên và dưới để lấy bao lồi
  a.clear();
  for (size_t i=0; i<up.size(); ++i)
    a.push_back (up[i]);
  for (size_t i=down.size()-2; i>0; --i)
    a.push_back (down[i]);
}
```

Bạn cũng có thể tham khảo thêm cài đặt C++ [ở đây](https://sites.google.com/site/kc97ble/arithmetic/monotonechain-cpp)

## Xử lí trường hợp suy biến

Các thuật toán trên hoạt động tốt trong trường hợp lí tưởng, tức là không có hai điểm nào trùng nhau và không có ba điểm nào thẳng hàng. Tuy nhiên, trong hầu hết các bài toán, ta sẽ phải xử lí các điểm trùng nhau và các bộ ba điểm thẳng hàng. Biện luận tất cả các trường hợp sẽ là một công việc khó nhằn và nhàm chán. Vì vậy, hãy ghi nhớ những điều sau:

- Đọc kĩ đề bài để biết được dữ liệu vào có bị suy biến hay không, nếu có thì rơi vào trường hợp nào. (Lưu ý rằng không phải đề bài nào cũng nói rõ rằng dữ liệu bị suy biến).

- Nếu tồn tại các điểm trùng nhau
  - Thuật toán bọc gói sẽ thực hiện phép chia cho số không. Ta cần tránh điều này để thuật toán chạy đúng.
  - Nếu ta chỉ cần tính chu vi hoặc diện tích của bao lồi, thuật toán Graham và thuật toán chuỗi đơn điệu sẽ không gặp vấn đề gì.
  - Nếu ta phải in ra các đỉnh của bao lồi, có ba thứ tự in các đỉnh mà đề bài có thể hỏi: cùng chiều kim đồng hồ, ngược chiều kim đồng hồ, hoặc theo thứ tự xuất hiện trong dữ liệu vào. Rõ ràng hai thứ tự in các đỉnh đầu tiên không có ý nghĩa gì khi có các điểm trùng nhau. Nếu đề bài yêu cầu in các đỉnh theo thứ tự xuất hiện trong dữ liệu vào, đề bài có thể yêu cầu in ra đỉnh đầu tiên xuất hiện trong dữ liệu vào nếu các đỉnh trùng nhau, hoặc in ra tất cả các đỉnh. Hãy đọc đề bài thật kĩ. Trong mọi trường hợp, ta đều có thể dễ dàng xử lí kết quả sau khi chạy thuật toán tìm bao lồi để phù hợp với yêu cầu bài toán, và ta nên làm như vậy vì kết hợp xử lí kết quả với thuật toán tìm bao lồi không những khó hơn mà có thể tạo ra sai sót không đáng có

- Nếu có các bộ ba điểm thẳng hàng
  - Ta cần biết đề bài yêu cầu bao lồi có số lượng đỉnh tối đa hay tối thiểu, từ đó, ta suy ra ta có nên cho thêm các điểm thuộc cạnh của bao lồi hay không. Nếu chỉ có các bộ ba điểm thẳng hàng mà không có các điểm trùng nhau, ta có thể sửa dấu $<$ thành dấu $\leq$ trong thuật toán Graham và thuật toán chuỗi đơn điệu nếu bài toán yêu cầu bao lồi có số lượng đỉnh tối đa. Còn trong thuật toán bọc gói, ta sẽ chọn điểm ở xa nhất hoặc điểm ở gần nhất nếu có hai điểm cùng có số đo góc nhỏ nhất tùy vào yêu cầu bài toán.
  - Thứ tự các đỉnh không phải là vấn đề, trừ khi đề bài yêu cầu in ra thứ tự các đỉnh của bao lồi có số đỉnh lớn nhất, trong đó các đỉnh thuộc cùng một cạnh được sắp xếp theo thứ tự xuất hiện trong dữ liệu vào. Khi đó, xử lí kết quả sau khi tìm bao lồi là lựa chọn tốt nhất.

- Trường hợp xấu nhất trên lí thuyết là khi diện tích bao lồi bằng 0. Có hai trường hợp như vậy, và ta có thể dễ dàng xử lí hai trường hợp đó: tất cả các điểm đều trùng nhau, hoặc tất cả điểm đều thẳng hàng.
  - Thuật toán chuỗi đơn điệu vẫn hoạt động bình thường nếu ta chỉ cần biết diện tích hoặc chu vi bao lồi.
  - Nếu ta cần in ra các đỉnh của bao lồi, ta không nên chỉnh sửa thuật toán mà nên xét riêng hai trường hợp trên.

# Ứng dụng

Ngoại trừ các ứng dụng hiển nhiên, tìm bao lồi còn giúp ta giải các bài toán sau:

- Cặp điểm xa nhất
- (Bài toán trộn màu): Bạn có một số hộp sơn, mỗi hộp sơn có tỉ lệ thành phần ba màu cơ bản xanh:đỏ:vàng là $x:d:v$, với $x,d,v$ dương. Giả sử màu của hộp sơn chỉ phụ thuộc vào tỉ lệ ba màu cơ bản. Bằng cách pha trộn các loại sơn, liệu ta có thể thu được màu mục tiêu hay không (màu mục tiêu cũng được cho bằng tỉ lệ ba màu cơ bản), biết rằng lượng sơn trong hộp là vô tận. Bài toán này hóa ra lại có thể giải bằng cách tìm bao lồi trên mặt phẳng. Bước đầu tiên, ta chuẩn hóa dữ liệu bằng cách chia tỉ lệ ba màu cơ bản với lượng màu xanh (tức là nếu tỉ lệ bằng $x:d:v$ thì ta chuẩn hóa còn $1:\frac{d}{x}:\frac{v}{x}$). Ta làm tương tự với màu mục tiêu. Sau đó ta bỏ qua lượng màu xanh do lượng màu xanh ở tất cả các hộp lẫn màu mục tiêu đều bằng 1, và tập trung xử lí hai màu kia. Mỗi màu của hộp sơn đều có thể biểu diễn bằng một điểm trên mặt phẳng. Khi đó, các màu mà các hộp sơn đó có thể pha trộn được sẽ nằm trong bao lồi. Đó là do khi trộn hai màu có điểm biểu diễn trên mặt phẳng lần lượt là $A$ và $B$, màu ta thu được sẽ có điểm biểu diễn nằm trên đoạn $AB$, nên ta dễ dàng tìm được một dãy các bước trộn màu để có được màu mục tiêu nếu điểm biểu diễn màu mục tiêu nằm trong bao lồi.

# Bao lồi 3D

[[/uploads/algo_geometry_convex_hull_3d.gif]]

Tim bao lồi trong 3D thực sự là một bài toán khó. Bài toán này chắc chắn sẽ không bao giờ được ra trong IOI, và học sinh trung học không cần phải đi sâu vào vấn đề này. Tuy nhiên, có một thuật toán $O(n^2)$ khá là đơn giản: đầu tiên, ta tìm hình chiếu của các điểm trên mặt phẳng $xy$, và tìm một các chắc chắn thuộc bao bằng cách lấy một điểm có tung độ lớn nhất rồi tìm điểm kia bằng cách chạy vòng lặp của thuật toán bọc gói một lần. Đây là phần đầu tiên của bao lồi. Sau đó, xét cạnh vừa tìm được, tìm một điểm thứ ba để tạo thành một mặt tam giác của bao lồi. Ta chọn điểm thứ ba bằng cách tìm điểm để tất cả các điểm khác nằm ở phía bên phải của mặt tam giác đó (giống như thuật toán bọc gói, ta tìm cạnh để tất cả các điểm khác đều nằm về phía bên phải cạnh đó). Bây giờ ta đã có ba cạnh trong bao lồi, ta chọn ngẫu nhiên một trong ba cạnh đó, rồi tìm tiếp một tam giác với cạnh này, rồi tiếp tục cho đến khi không còn cạnh nào nữa (Khi ta tìm thêm một mặt tam giác, ta phải thêm hai cạnh vào bao, tuy vậy hai cạnh này phải chưa có trong bao, nếu không ta phải đi tìm hai cạnh khác). Có tổng cộng $O(n)$ mặt, và mỗi lần duyệt các điểm ta mất thời gian $O(n)$ vì ta phải duyệt tất cả các điểm còn lại, do đó độ phức tạp của thuật toán là $O(n^2)$. (Nếu bạn nghĩ bạn có thể cài đặt được thuật toán này, hãy nộp bài tại [SPOJ - CH3D](http://www.spoj.com/problems/CH3D/)). Ta có thể tăng tốc độ thuật toán này bằng các loại bỏ các điểm chắc chắn không phải đỉnh của bao, bằng cách tìm các điểm cực theo các trục tọa độ, rồi loại bỏ các điểm nằm trong bát diện mà các đỉnh đấy tạo ra.

Ta có thể tìm bao lồi trong không gian với độ phức tạp $O(n \log{n})$ bằng phương pháp chia để trị, tuy nhiên việc cài đặt thuật toán này là vô cùng khó.

# Bài tập áp dụng

- [Kattis - convexhull](https://open.kattis.com/problems/convexhull)
- [ACM ICPC Vietnam National 2017 - K](https://open.kattis.com/contests/vietnam-national17-open/problems/parade)
- [VNOJ - MILITARY](https://oj.vnoi.info/problem/military/)
- [VNOJ - HEADQRT](https://oj.vnoi.info/problem/headqrt/)
- [VNOJ - KMIX](https://oj.vnoi.info/problem/kmix/)
- [USACO - Cow Curling](http://usaco.org/index.php?page=viewproblem2&cpid=382)
