---
title: Chia để trị (Divide and Conquer)
description: 
published: true
date: 2024-09-13T06:07:28.334Z
tags: 
editor: markdown
dateCreated: 2024-05-07T11:59:22.050Z
---

# Chia để trị (Divide and Conquer)
**Tác giả:**
- Nguyễn Đức Kiên, Trường Đại học Công nghệ, ĐHQGHN

**Reviewer:**
- Nguyễn Hoàng Vũ - Trường Đại học Công nghệ, ĐHQGHN
- Nguyễn Minh Nhật - THPT chuyên Khoa học Tự nhiên, ĐHQGHN

## Mở đầu

**Chia để trị (Divide and Conquer, DnC)** chỉ việc chia nhỏ bài toán thành các phần nhỏ có cùng dạng với nó, tới khi có thể giải được một cách dễ dàng (thường là có ngay kết quả), sau đó dùng các kết quả này kết hợp lại để giải được bài toán lớn. Các bước để giải một bài toán chia để trị bao gồm:

-   Chia bài toán thành các bài toán con (thường là chia đôi hoặc xấp xỉ như vậy).
-   Giải các bài toán con. Nếu vẫn gặp khó khăn với các bài toán con, ta lại tiếp tục chia nó thành các bài toán nhỏ hơn cho tới khi dễ dàng tìm được kết quả.
-   Tổng hợp kết quả các bài toán con lại để có kết quả của bài toán lớn nếu cần.

Bạn đọc có thể thấy những bước trên có phần tương đồng với quá trình làm các bài toán đệ quy cơ bản. Các bài toán đó cũng có thể coi là chia để trị, và đệ quy cũng là một cách để cài đặt các thuật chia để trị.

Tư tưởng chia để trị cũng xuất hiện rất đa dạng và phổ biến trong các bài toán, thuật toán và cấu trúc dữ liệu: tìm kiếm nhị phân, cấp trúc cây tìm kiếm nhị phân (BST), heap, cây phân đoạn (segment tree), cây BIT/Fenwick, mảng thưa, các thuật toán sắp xếp, luỹ thừa nhanh, ...

## Xác định độ phức tạp

Ta nhắc lại một vài ký hiệu trước khi vào phần này:

-   $\text{log}_a b$: Logarit cơ số $a$ của $b$, là số thực $k$ thoả mãn $a^k = b$. Bài viết này sẽ sử dụng ký hiệu $\text{log } b$ cho trường hợp $a = 2$.
-   $T(n)$: Thời gian chạy thuật toán với kích thước dữ liệu đầu vào là $n$, tính bằng số phép tính.
-   $O()$ (big-O): Các hàm độ phức tạp thuật toán. Chi tiết bạn đọc tham khảo [Độ phức tạp thời gian](/algo/basic/computational-complexity.md)

Chi tiết về các ký hiệu độ phức tạp và thời gian bạn đọc có thể tham khảo bài .

### Định lý Thợ (Master theorem)

Các công thức dưới đây được nhắc đến trong sách _Introduction to Algorithms_ (xem phần Tài liệu tham khảo). Chưa rõ tên tiếng Việt của thuật toán có nguồn gốc từ đâu.

Độ phức tạp của các thuật toán chia để trị cài đặt dưới dạng đệ quy được xác định bằng **Định lý Thợ**.

Giả sử có một bài toán $P$ với dữ liệu đầu vào có độ lớn là $n$ (mảng có độ dài $n$ chẳng hạn) được cài đặt bằng đệ quy, tại mỗi vòng đệ quy bài toán được chia thành $a$ bài toán con như sau:

```cpp=
void P(<input kích thước n>)
{
    if (n < k)  //k là một hằng số
    {
        <giải bài toán trực tiếp (base case)>
    }
    else
    {
        for (int i = 1; i <= a; i ++)
        {
            P(<input kích thước n/b>);
        }
        <kết hợp kết quả các bước trên>
    }
}
```

Nếu ta coi mỗi bài toán con là một nút trên một cây và mỗi lần gọi đệ quy từ một bài toán con ta nối thêm một nút con vào nút biểu diễn bài toán nói trên thì bài toán lớn của chúng ta sẽ có dạng như sau:

![problem tree](https://hackmd.io/_uploads/SJGSaKEk6.png)

Tại mỗi nút của cây trên, nếu việc kết hợp kết quả các bài toán con mất $f(n)$ thời gian, thì thời gian chạy tại một nút với kích thước dữ liệu là $n$ có thể được tính theo công thức truy hồi:

$$
T(n) = \begin{cases}
    a \times T(\frac{n}{b}) + f(n) &\text{khi } n \geq k\\
    O(1) &\text{khi } n < k
    \end{cases}
$$

với $k$ là một hằng số nào đó, tuỳ thuộc vào thuật toán.

Ví dụ, với thuật toán MergeSort, tại mỗi bước ta chia một đoạn có độ dài $n$ thành hai đoạn con có độ dài $n/2$ hoặc xấp xỉ số đó. Thuật toán sẽ có thời gian chạy là $T(n) = 2T(\frac{n}{2}) + O(n)$ khi $n > 1$ và $O(1)$ khi $n = 1$.

Bây giờ, ta lại xét giá trị $f(n)$. Giả sử $f(n)$ viết được dưới dạng $O(n^p\text{log}^qn)$ (Định lý Thợ chỉ áp dụng khi $f(n)$ có độ phức tạp đa thức). Chúng ta có thể tiếp tục thu gọn biểu thức như sau:
| Quan hệ $a$ và $b^p$ | Biểu thức $T(n)$ |
|---|---|
| $a > b^p$ | $T(n) = O(n^{\text{log}_b a})$ |
| $a = b^p$ | $T(n) = O(n^{\text{log}_b a}\text{log}^{q + 1}n)$ khi $q > -1$ <br> $T(n) = O(n^{\text{log}_b a}\text{log }\text{log }n)$ khi $q = -1$ <br> $T(n) = O(n^{\text{log}_b a})$ khi $q < -1$ |
| $a < b^p$ | $T(n) = O(n^p\text{log}_q n)$ khi $q \geq 0$ <br> $T(n) = O(n^p)$ khi $q < 0$ |

Một số ví dụ:

-   Thuật toán Tìm kiếm nhị phân (Binary search) mỗi lần chia bài toán thành 2 phần bằng nhau nhưng chỉ xét 1, không cần kết hợp kết quả sẽ có $T(n) = T(n / 2) + O(1)$. Thời gian chạy trung bình của thuật toán là $T(n) = O(\text{log }n)$, ứng với $a = 1, b = 2, p = 0, q = 0$.
-   Thuật toán MergeSort chia đôi dãy hiện tại thành 2 phần bằng nhau, lấy cả 2 và phải xét lại cả 2 phần để lấy kết quả sẽ có $T(n) = 2T(n / 2) + O(n)$. Thời gian chạy trung bình của thuật toán là $T(n) = O(n\text{log }n)$, ứng với $a = 2, b = 2, p = 1, q = 0$ (Chi tiết về thuật MergeSort bạn đọc có thể đọc phần dưới).
-   Một thuật toán chia để trị có $T(n) = 3T(n / 2) + \text{log}^2n$. Thời gian chạy trung bình của thuật toán là $T(n) = O(n^{\text{log}_2 3})$, tương ứng với $a = 3, b = 2, p = 0, q = 2$.

Định lý Thợ là một công cụ hữu hiệu để xác định độ phức tạp của một thuật toán chia để trị. Chỉ cần xác định được số bài toán con, kích thước dữ liệu các bài toán con và độ phức tạp của việc kết hợp dữ liệu, ta dễ dàng tìm ra độ phức tạp chung của bài toán.

## Một số ví dụ áp dụng Chia để trị

Các bài toán áp dụng Chia để trị chỉ có chung một phương pháp như đã nói ở trên. Khi sử dụng, thứ mà ta quan tâm chủ yếu là độ phức tạp; thông thường, chia để trị là công cụ tối ưu độ phức tạp khá hiệu quả.

### MergeSort

**Đề bài**: Sắp xếp một dãy gồm $n$ số nguyên $(n \leq 10^6)$.

#### Phân tích thuật toán

Đây là một thuật toán sắp xếp nổi tiếng và cũng hay được áp dụng (nếu không được phép sử dụng các thư viện có sẵn). Thuật toán này sử dụng phương pháp đệ quy. Tại mỗi vòng đệ quy, giả sử đang cần sắp xếp một đoạn $[l, r]$ ta chia dãy làm hai phần bằng nhau, $[l, mid]$ và $[mid + 1, r]$ với $mid = \left\lfloor \dfrac{l + r}{2} \right\rfloor$. Sau khi đã gọi đệ quy các đoạn con, ta tiến hành hợp nhất hai đoạn này. Việc hợp nhất hai đoạn đã sắp xếp được tiến hành bằng phương pháp [hai con trỏ](/algo/basic/two-pointers.md), có độ phức tạp là $O(n)$. Trong trường hợp một đoạn chỉ có một phần tử duy nhất, ta coi như nó đã được sắp xếp.

![Minh hoạ MergeSort](https://hackmd.io/_uploads/Skh8YzQxa.png)


#### Cài đặt

:::spoiler **Nhấn để hiện code**

```cpp=
//Ghép hai đoạn [l1, r1], [l2, r2] thành một đoạn bắt đầu từ l1
void merge(int a[], int l1, int r1, int l2, int r2)
{
    int cur = l2;
    vector <int> newArr;
    for (int i = l1; i <= r1; i++)
    {
        while (cur <= r2 && a[cur] < a[i])
        {
            newArr.push_back(a[cur]);
            cur++;
        }
        newArr.push_back(a[i]);
    }
    for (int j = cur; j <= r2; j ++) newArr.push_back(a[j]);
    for (int i = 0; i < newArr.size(); i ++) a[l1 + i] = newArr[i];
}

void mergeSort(int a[], int l, int r)
{
    if (l == r) return;
    int mid = (l + r) / 2;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    merge(a, l, mid, mid + 1, r);
}
```

Hàm `merge()` trong đoạn code trên có thể thay thế bằng hàm `merge()` trong thư viện `algorithm`.
:::

#### Đánh giá

Theo như phân tích độ phức tạp đã đề cập ở trên, độ phức tạp trung bình của MergeSort là $O(n\text{log }n)$. Thực tế thì trong mọi trường hợp, độ phức tạp của MergeSort luôn là $O(n\text{log }n)$.

### Cặp điểm gần nhất

**Đề bài**: Cho $n$ điểm trên mặt phẳng $(2 \leq n \leq 10^5)$. Hãy tìm khoảng cách nhỏ nhất giữa hai điểm bất kỳ trong đó.

_Đề bài VNOI_: [NEAREST](https://vnoi.info/problems/NEAREST/)

#### Phân tích

Giả sử có $n$ điểm $A_1, A_2, ..., A_n$.

Ta có thể sử dụng một thuật toán "ngây thơ" cho bài này: xét tất cả mọi cặp điểm, kiểm tra xem khoảng cách giữa hai cặp điểm nào là gần nhau nhất. Độ phức tạp khi đó sẽ là $O(n^2)$ trong mọi trường hợp, chưa đủ để vượt qua giới hạn của bài toán này.

Ta nghĩ đến việc sử dụng chia để trị. Trước hết, ta sắp xếp các điểm trong tập hợp theo hoành độ $x$. Tại mỗi vòng đệ quy, ta chia tập điểm hiện tại thành hai phần bên trái và bên phải vị trí $mid$ ta chọn. Base case (trường hợp cơ bản) lúc này thay vì là $l = r$ thì sẽ là $r - l \leq 2$, do ta không thể xác định khoảng cách với $1$ điểm, và cũng cần đảm bảo rằng khi chạy đệ quy không tồn tại tập nào có độ lớn như vậy. Ngoài trường hợp đó, ta thu được kết quả của 2 tập trái và phải. Tuy nhiên, việc kết hợp kết quả không đơn giản, vì một điểm ở bên trái $A_{mid}$ vẫn có thể tạo ra khoảng cách ngắn nhất với một điểm bên phải. Ta cũng không thể chạy hết từng cặp điểm một trong hai tập này, vì khi đó theo Định lý Thợ độ phức tạp trung bình sẽ lên đến $O(n^2)$.

![nearest1](https://hackmd.io/_uploads/ryCGGq4kT.png)

Ở hình vẽ trên, hai màu xanh và đỏ tượng trưng cho hai nửa phải và trái. Điểm $A_4$ đóng vai trò là $A_{mid}$, thuộc tập bên phải.

Gọi $d$ là giá trị nhỏ hơn giữa khoảng cách ngắn nhất giữa hai điểm ta vừa thu được ở tập bên phải và tập bên trái. Cụ thể:
$$d = min\{nearest(l, mid), nearest(mid + 1, r)\}$$ 
Khi đó, trong cùng một tập hợp, không tồn tại một cặp điểm nào có khoảng cách ngắn hơn $d$. Giữa hai tập hợp lúc này ta sẽ chỉ quan tâm đến các cặp điểm có khoảng cách nhỏ hơn $d$.

Xét các điểm có hoành độ cách $A_{mid}$ một khoảng không vượt quá $d$. Các điểm này nằm giữa các đường thẳng $x = x_{mid} - d$ và $x = x_{mid} + d$:

![nearest2](https://hackmd.io/_uploads/rysgQc4yT.png)

Đến đây, ta có một nhận xét quan trọng: Với mỗi điểm $A_m$ nằm trong miền nằm giữa hai đường thẳng nói trên (vùng được tô màu), tồn tại không quá 7 điểm khác $A_m$ có tung độ $y$ lớn hơn không quá $d$ so với $y_m$.

:::spoiler _Chứng minh (nhấn để hiện)_

Khoảng các điểm thoả mãn điều kiện trên được giới hạn bởi hình vẽ sau:

![window](https://hackmd.io/_uploads/rkqqL9V1p.png)

Khoảng trên là hình tạo bởi hai hình vuông có cạnh là $d$ nằm cạnh nhau. Các điểm thoả mãn nằm trong hoặc trên cạnh của hai hình vuông này, và khoảng cách giữa hai điểm bất kỳ trong cùng một hình vuông không nhỏ hơn $d$. Không thể xếp quá $4$ điểm như vậy vào trong một hình vuông. Thật vậy, với mỗi điểm ta vẽ một đường tròn có tâm tại điểm đó và bán kính bằng $d / 2$. Hai đường tròn bất kỳ không thể có nhiều hơn 1 điểm chung, vì nếu không khoảng cách giữa chúng sẽ nhỏ hơn $d$.

![window2](https://hackmd.io/_uploads/BJaKDqE16.png)

Ta thấy mỗi hình tròn có diện tích giao với hình vuông là $\geq \frac{\pi d^2}{4} = \frac{\pi}{16} d^2$, do khi tịnh tiến hình tròn dọc theo cả hai phương $x$ và $y$ ta đều thu được các hình có diện tích lớn hơn. Vì hình vuông có diện tích là $d^2$, số miền diện tích như vậy có thể đặt vào hình tròn là $d^2 : \frac{\pi}{16}d^2 \approx 5.1$. Tuy nhiên, không tồn tại cách đặt 5 điểm vào hình vuông thoả mãn yêu cầu của đề bài, nên số điểm đặt được tối đa là 4.

Với 4 điểm ở mỗi hình vuông, số điểm đặt được tối đa là 8, tính cả điểm mà chúng ta đã xét ban đầu. Do vậy có tối đa 7 điểm thoả mãn tung độ lớn hơn $y_m$ không quá $d$.

:::

Nếu ta sắp xếp các điểm trong miền này theo thứ tự $y$ tăng dần, với một điểm bất kỳ ta chỉ cần xét một số điểm lân cận thoả mãn chênh lệch tung độ không vượt quá $d$, rồi tính khoảng cách giữa chúng.

![nearest3](https://hackmd.io/_uploads/r1deOc4kp.png)

Khi cài đặt, sau khi tiến hành tìm khoảng cách ngắn nhất giữa hai điểm ta có thể giữ nguyên trạng thái sau khi sắp xếp theo $y$ của đoạn đó, rồi dùng phép `merge()` như bài MergeSort ở trên để sắp xếp nhanh đoạn lớn trong $O(n)$.

#### Cài đặt

:::spoiler **Nhấn để hiện code**

```cpp=
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const long long INF = LLONG_MAX;

struct Point
{
    double x, y;

    void inp()
    {
        cin >> x >> y;
    }

    bool operator < (Point other)
    {
        if (x == other.x) return (y < other.y);
        return (x < other.x);
    }
}a[MAXN], middleArea[MAXN];

bool ascendingY(Point p1, Point p2) {return make_pair(p1.y, p1.x) < make_pair(p2.y, p2.x);}

double dist(Point p1, Point p2)
{
    return hypot(1.0 * p1.x - p2.x, 1.0 * p1.y - p2.y);
}

//Tìm cặp điểm gần nhất trong các điểm thuộc middleAreaa
double nearestMiddle(int middleAreaSize, double d)
{
    double ret = INT_MAX;
    for (int i = 1; i <= middleAreaSize; i++)
        for (int j = i + 1; j <= middleAreaSize; j++)
        {
            if (middleArea[j].y - middleArea[i].y >= d) break;
            ret = min(ret, dist(middleArea[i], middleArea[j]));
        }
    return ret;
}

//Tìm cặp điểm gần nhất trong các điểm thuộc mảng a độ dài n
double nearest(Point a[], int n)
{
    if (n <= 3)
    {
        sort(a + 1, a + n + 1, ascendingY);
        double ret = INF;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                ret = min(ret, dist(a[i], a[j]));
        return ret;
    }

    int mid = n / 2;
    auto midPoint = a[mid];
    double dL = nearest(a, mid);
    double dR = nearest(a + mid, n - mid);
    double d = min(dL, dR);

    int middleAreaSize = 0;
    merge(a + 1, a + mid + 1, a + mid + 1, a + n + 1, middleArea + 1, ascendingY);
    for (int i = 1; i <= n; i ++)
    {
        a[i] = middleArea[i];
        if (abs(middleArea[i].x - midPoint.x) < d) middleArea[++middleAreaSize] = middleArea[i];
    }
    return min(d, nearestMiddle(middleAreaSize, d));
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) a[i].inp();
    sort(a + 1, a + n + 1);
    cout << fixed << setprecision(3) << nearest(a, n);

    return 0;
}

```

Mảng `middleArea[]` lưu các điểm nằm ở giữa miền tạo bởi hai đường thẳng $x = x_{mid} - m$ và $x = x_{mid} + m$.
Hàm `hypot(a, b)` trả về cạnh huyền của tam giác vuông có hai cạnh góc vuông là $a$ và $b$, tức giá trị $\sqrt{a^2 + b^2}$; hàm này có sẵn trong thư viện `cmath`.
:::

#### Đánh giá

Mỗi tập $[l, r]$ được chia thành hai tập con, mỗi tập con có bộ dữ liệu bằng đúng một nửa tập lớn. Việc tìm kết quả của đoạn lớn bao gồm việc ghép đoạn để sắp xếp lại mất $O(n)$ và tính khoảng cách nhỏ nhất giữa các điểm ở giữa hết $O(7n) = O(n)$. Do vậy thuật này có $T(n) = 2T(\frac{n}{2}) + O(n)$ và có độ phức tạp trung bình là $O(n\text{log }n)$ theo Định lý Thợ. Trong mọi trường hợp, thuật toán đều thực hiện những bước tương tự và độ phức tạp là $O(n\text{log }n)$.

#### Bonus

Bài toán này còn một lời giải khác bằng cách sử dụng kỹ thuật đường quét (sweep-line) kết hợp với cấu trúc `set`. Lời giải này có cùng độ phức tạp nhưng ngắn gọn và dễ cài đặt hơn lời giải bằng chia để trị. Bạn đọc tự cài đặt và tìm hiểu thêm, tham khảo [code của skyvn97](https://vnoi.info/problems/show_solution/NEAREST/1389230/).

## Bài toán Truy vấn trên mảng cố định

### Bài toán

Bài toán **Truy vấn trên mảng cố định (SRQ - Static Array Queries)** được mô tả như sau:

Xét phép toán bất kỳ $\star$ và mảng $a$ gồm các số $a_1, a_2, ..., a_n$. Ta phải trả lời $q$ truy vấn, mỗi truy vấn yêu cầu ta tính $a_l \star a_{l + 1} \star ... \star a_r$, với $l, r$ là các giá trị cho trước, $l, r \in [1, n]$.

Trong trường hợp $\star$ là phép toán có tính chất kết hợp, cụ thể hơn, phép toán này áp dụng được trên các giá trị (không nhất thiết là số) $a, b, c$ sao cho $(a \star b) \star c = a \star (b \star c)$, ta có thể sử dụng chia để trị để giải. Một số ví dụ cho phép toán này là phép cộng, phép nhân, phép lấy $\text{min}$.

### Thuật toán giải

Có rất nhiều cách giải bài toán này với độ phức tạp không gian và thời gian logarit tuyến tính ($O(n\text{log }n)$), như cây phân đoạn, BIT, mảng thưa, ... Chia để trị cũng là một cách hiệu quả để giải quyết bài toán, đặc biệt trong trường hợp độ phức tạp cho mỗi truy vấn cần rất thấp.

Giả sử tất cả các truy vấn $(lq, rq)$ đều thoả mãn điều kiện $l \leq lq \leq rq \leq r$. Ban đầu, ta có $l = 1, r = n$. Đặt $mid = \lfloor \frac{l + r}{2} \rfloor$ (tuỳ trường hợp, để tính toán thuận lợi, $mid$ có thể nhận các giá trị khác nhau, nhưng thường ta lấy vị trí chính giữa). Gọi $leftAcc[i]$ là "tổng" hậu tố tính từ $mid$ tới $i$ hay:
$$leftAcc[i] = a[i] \star a[i + 1] \star ... \star a[mid]$$

Tương tự, ta gọi $rightAcc[i]$ là "tổng" tiền tố tính từ $mid + 1$ tới $i$:
$$rightAcc[i] = a[mid + 1] \star a[mid + 2] \star ... \star a[i]$$

Với các truy vấn thoả mãn $lq \leq mid \leq rq$, kết quả của truy vấn đó sẽ là $leftAcc[i] \star rightAcc[i]$. Điều này là hiển nhiên theo tính chất kết hợp. Với các truy vấn còn lại, hiển nhiên chúng chỉ nằm hoàn toàn ở một trong hai bên của $mid$. Ta thay đổi các giá trị $l, r$ và tính các giá trị $leftAcc, rightAcc$ theo $l, r$ mới. Cứ như vậy tới khi $l = r$.

Về độ phức tạp, ở mỗi bước ta chia mảng độ dài $n$ thành 2 phần đều nhau có kích thước dữ liệu là $\frac{n}{2}$. Sau khi có hai đoạn này, ta mất $O(n)$ để tính $leftAcc, rightAcc$, và $O(1)$ cho mỗi truy vấn, tổng cộng là $O(n + q)$. Độ phức tạp thời gian của thuật toán là $O((n + q)\text{log }n)$, chạy ổn định, còn về không gian chỉ cần $O(n + q)$.

Hai mảng $leftAcc$ và $rightAcc$ không có chung nhau một vị trí nào, vậy nên ta có thể kết hợp lại thành một mảng $acc$. Khi đó với một đoạn $[l, r]$ có phần tử ở giữa là $mid$, các giá trị từ $acc[l]$ đến $acc[mid]$ tương đương với $leftAcc$, và các giá trị $acc[mid + 1]$ đến $acc[r]$ tương đương với $rightAcc$.

Nếu phải sử dụng các truy vấn online, ta lưu lại $acc$ của mỗi lần đệ quy dưới dạng một mảng hai chiều giống như mảng thưa, ví dụ $acc[j][i]$ là kết quả $acc[i]$ ở vòng đệ quy với độ sâu $j$ (xem ví dụ để hiểu rõ hơn). Bằng cách này, ta vẫn có thể trả lời mọi truy vấn trong $O(1)$, và độ phức tạp trở thành $O(n\text{log }n + q)$ cho thời gian và $O(n\text{log }n + q)$ cho không gian.

### Ví dụ

**Đề bài**: [SEGPROD](https://www.codechef.com/problems/SEGPROD)

_Tóm tắt_: Cho dãy $A$ gồm $N$ số nguyên dương và một số nguyên dương $P$. Có $Q \leq 2\times10^7$ truy vấn, truy vấn thứ $i$ yêu cầu tìm tích của các số $A_j$ với $L_i \leq j \leq R_i$, lấy số dư khi chia cho $P$. Chú ý rằng các truy vấn phải được xử lý online và số $P$ có thể không là số nguyên tố.

#### Phân tích

Đây là một bài toán SRQ khá "thẳng", chỉ yêu cầu ta tính tích trên một đoạn bất kỳ. Ý tưởng "ngây thơ" nhất là duyệt qua mọi đoạn con được truy vấn để tìm tích của nó, mất $O(n^2)$. Ta cũng nghĩ đến việc áp dụng tích tiền tố đơn giản, tuy nhiên việc lấy ra một đoạn sẽ gặp khó khăn nếu $P$ không phải là số nguyên tố. Các ý tưởng khác cho bài toán SRQ như cây phân đoạn và mảng thưa đều mất $O(\text{log n})$ cho mỗi truy vấn, khó qua được giới hạn của bài toán này. May mắn thay, sử dụng chia để trị vừa khít với bộ dữ liệu của bài toán.

Bằng cách sử dụng cách chia để trị như đã nói ở trên, ta dễ dàng khởi tạo mảng $acc$ trong $O(n\text{log }n)$. Khi trả lời một truy vấn `lq rq`, như đã nói ở trường hợp truy vấn offline, $lq$ và $rq$ phải thoả mãn $l \leq lq \leq mid$ và $mid + 1 \leq rq \leq r$ tại một vòng đệ quy.

Giả sử độ sâu $lvl$ của một vòng đệ quy là số lần phải gọi đệ quy từ đoạn $[1, n]$, ta thấy hai đoạn có cùng độ sâu không có điểm chung. Do đó ta có thể lưu các giá trị $acc$ đi kèm với độ sâu mà không sợ bị trùng lặp.

![srq1](https://hackmd.io/_uploads/H1ZBwmiJp.png)

Quay lại với truy vấn `lq rq`, ta cần phải tìm một độ sâu sao cho $lq$ và $rq$ nằm về hai phía của $mid$ của độ sâu này. Để giải quyết vấn đề này, ta gọi $mask[i]$ là một dãy bit, sao cho bit thứ $j$ của dãy này bằng $0$ nếu vị trí $i$ nằm về bên trái $mid$ (tính cả $mid$) ở độ sâu $j$, và $1$ nếu vị trí này nằm về bên phải của $mid$ (không tính $mid$). Ví dụ với dãy bằng $8$ như trên hình, $mask[3] = (010)_2$, $mask[7] = (011)_2$. Như vậy, độ sâu thoả mãn $lq$ và $rq$ nằm về hai phía của $mid$ ở độ sâu này là vị trí của bit đầu tiên bằng $1$ từ phải qua trái trong dãy $mask[lq] \oplus mask[rq]$, với $\oplus$ là phép xor.

#### Cài đặt

:::spoiler **Nhấn để hiện code**

```cpp=
const int MAXN = 1e6;

int n, a[MAXN], b[MAXN], mod, acc[21][MAXN], mask[MAXN];

/// Khởi tạo acc
void calc(int l, int r, int level)
{
    if (l == r) return;
    int mid = (l + r) / 2;
    calc(l, mid, level + 1);
    calc(mid + 1, r, level + 1);

    acc[level][mid] = a[mid];
    for (int i = mid - 1; i >= l; i --)
        acc[level][i] = 1ll * acc[level][i + 1] * a[i] % mod;
    acc[level][mid + 1] = a[mid + 1];
    for (int i = mid + 2; i <= r; i ++)
        acc[level][i] = 1ll * acc[level][i - 1] * a[i] % mod;

    for (int i = mid + 1; i <= r; i ++) mask[i] |= (1 << level);
}

/// Giải quyết 1 truy vấn
void solve()
{
    int q;
    cin >> n >> mod >> q;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++)
        for (int l = 0; (1 << l) < n; l++)
            acc[l][i] = 1;
    for (int i = 0; i < n; i ++) mask[i] = 0;
    calc(0, n - 1, 0);

    int res = 0;
    for (int i = 0; i < q / 64 + 2; i++)
    {
        cin >> b[i];
    }
    for (int i = 0, lq = 0, rq = 0; i < q; i++)
    {
        // Nhận truy vấn tiếp theo theo cách đề bài mô tả
        if (i % 64 == 0)
        {
            lq = (b[i / 64] + res) % n;
            rq = (b[i / 64 + 1] + res) % n;
        }
        else
        {
            lq = (lq + res) % n;
            rq = (rq + res) % n;
        }
        if (lq > rq) swap(lq, rq);

        // Tìm kết quả cho đoạn [lq, rq] vừa tìm được
        if (lq == rq) res = a[lq];
        else
        {
            int lvl = __builtin_ctz(mask[lq] ^ mask[rq]);
            res = 1ll * acc[lvl][lq] * acc[lvl][rq] % mod;
        }
        (res += 1) %= mod;
    }
    cout << res << "\n";
}
```

Hàm `__builtin_ctz(x)` trả về số bit $0$ ở cuối dãy nhị phân có giá trị bằng $x$. Giá trị này chính là vị trí của bit $1$ đầu tiên từ phải qua trái của dãy. Bạn đọc có thể xem bài [Phép toán bit](/algo/basic/bitwise-operators.md) để biết thêm chi tiết.
:::

## Chú ý thêm

-   Kỹ thuật chia để trị có thể làm tối ưu khá tốt lời giải của một thuật toán. Đặc biệt trong các bài toán quy hoạch động, chia để trị là một trick tối ưu khá hiệu quả. Bạn đọc có thể tham khảo thêm tại [bài viết này](/algo/dp/Mot-so-ky-thuat-toi-uu-hoa-thuat-toan-Quy-Hoach-Dong.md).
-   Đối với các bài toán SRQ, còn một phương pháp hiệu quả vượt trội các phương pháp đã nói trên về độ phức tạp thời gian, đó là cấu trúc Sqrt Tree. Bạn đọc có thể tìm hiểu thêm về cấu trúc này tại [đây](https://cp-algorithms.com/data_structures/sqrt-tree.html).

## Bài tập

Các bài chia để trị nói chung:

-   [CERC 17 - I](https://codeforces.com/gym/101620/attachments)
-   [VNOJ - NORMA](https://oj.vnoi.info/problem/norma)
-   [VNOJ - LIS2VN](https://oj.vnoi.info/problem/lis2vn)
-   [UVA - Bit Maps](https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=119)
-   [IOI 2011 - Race](https://oj.uz/problem/view/IOI11_race)

Các bài toán SRQ:

-   [VNOJ - XORSHIFT](https://oj.vnoi.info/problem/mofkcup_r1_e)
-   [Duyên hải Bắc Bộ 2023 - HKDATA](https://lqdoj.edu.vn/problem/dhbb23hkdata) (Bạn cần tham gia [contest](https://lqdoj.edu.vn/contest/dhbb23) để xem được đề bài)
-   [DMOJ - Continued Fractions](https://dmoj.ca/problem/dmopc19c7p4)
-   [USACO - Non-Decreasing Subsequences](http://www.usaco.org/index.php?page=viewproblem2&cpid=997)
-   [Codeforces - Destiny](https://codeforces.com/problemset/problem/840/D)
-   [Codeforces - Timofey and our friends animals](https://codeforces.com/problemset/problem/763/E)

## Tài liệu tham khảo

-   Steven Halim, Felix Halim (2013), _Competitive Programing 3_
-   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein (2022), _Introduction to Algorithms_, 4th edition
-   Mark Berg , Otfried Cheong , Marc Kreveld , Mark Overmars (2008), _Computational Geometry - Algorithms and Applications_
-   Wikipedia (Master's Theorem)
-   [Bài giảng của Piotr Indyk tại MIT](http://people.csail.mit.edu/indyk/6.838-old/handouts/lec17.pdf) (bài NEAREST)
-   USACO Guide Platinium, [Divide and Conquer - SRQ](https://usaco.guide/plat/DC-SRQ?lang=cpp)
-   Codeforces, [Post của Wind_Eagle](https://codeforces.com/blog/entry/104443)
-   Codeforces, [Post của steveonalex](https://codeforces.com/blog/entry/119104)
