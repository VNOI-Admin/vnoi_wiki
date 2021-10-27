# Hình học tính toán phần 1: Những khái niệm cơ bản

**Tác giả:** 
- Lê Minh Hoàng - Phổ thông Năng khiếu, ĐHQG-HCM

**Reviewer:**
- Trần Quang Lộc - ITMO University
- Hoàng Xuân Nhật - Đại học Khoa học Tự nhiên, ĐHQG-HCM
- Hồ Ngọc Vĩnh Phát - Đại học Khoa học Tự nhiên, ĐHQG-HCM

---

[[_TOC_]]

Hình học mặc dù là một chủ đề hết sức phổ biến, song vẫn còn rất nhiều người không thích giải các bài toán hình học vì chúng khá khó chịu và lằng nhằng. Do đó, trong bài viết này, ta sẽ cùng tìm hiểu một vài khái niệm nhằm giúp cho các bài toán hình học trở nên bớt đáng sợ hơn.

# Vector
Vector là một đối tượng có cả độ lớn và hướng. Hướng của vector là hướng từ điểm đầu đến điểm cuối của nó.

![](https://i.imgur.com/JdJPAOc.png)

Một vector thường được biểu diễn bằng một tia (một đoạn thẳng có hướng), hoặc bằng đồ thị dưới dạng một mũi tên nối từ điểm đầu $A$ tới điểm cuối $B$, và được ký hiệu là $\overrightarrow{\rm AB}$.

![](https://i.imgur.com/H7bIO9o.png)

Trong hình học phẳng, vector $\overrightarrow{\rm AB}$ có thể được biểu diễn bởi một cặp số $(x, y)$ cho biết tọa độ của vector, được xác định bằng hiệu các tọa độ tương ứng của điểm cuối $B$ với điểm đầu $A$:

$$\begin{cases}
x = x_B - x_A \\
y = y_B - y_A
\end{cases}$$

**Ví dụ:** một vector từ $A(3, 1)$ đến $B(2, 3)$ có thể được biểu diễn bởi $\overrightarrow{\rm u} = (-1, 2)$.

![](https://i.imgur.com/5ddR4P4.gif)

## Độ lớn của vector
Độ lớn của $1$ vector được xác định bằng khoảng cách giữa điểm đầu và điểm cuối của nó.
**Ví dụ:** Độ lớn của $\overrightarrow{\rm AB}(x,y)$ kí hiệu là $|\overrightarrow{\rm AB}|$ và được xác định bằng:

![](https://i.imgur.com/1rQrzkN.png)

# Phép cộng trừ vector
Có một số phép toán có thể thực hiện trên vector, đơn giản nhất là phép cộng trừ vector: bạn có thể cộng trừ 2 vector với nhau để được một vector mới.

Xuyên suốt bài viết, chúng ta sẽ dùng dấu cộng (**+**) và trừ (**-**) để biểu diễn cho phép cộng và trừ vector.

## Phép cộng 2 vector

![](https://i.imgur.com/Lblu42q.png)

Giả sử ta có $2$ vector $\overrightarrow{\rm u}(x_1, y_1)$ và $\overrightarrow{\rm v}(x_2, y_2)$, tổng $\overrightarrow{\rm u}$ và $\overrightarrow{\rm v}$ được tính bằng công thức: $\overrightarrow{\rm u} + \overrightarrow{\rm v} = (x_1+x_2,y_1+y_2)$.

![](https://i.imgur.com/PYkqiVG.gif)

**Lưu ý:** Thứ tự cộng các vector không quan trọng, cũng giống như phép cộng trên số (tính giao hoán). 

![](https://i.imgur.com/sKDldWR.png)

## Phép trừ 2 vector
![](https://i.imgur.com/p1QmwFb.png)

### Vector đối
Cho vector $\overrightarrow{\rm a}$, vector có cùng độ lớn và ngược hướng với vector $\overrightarrow{\rm a}$ được gọi là vector đối của vector $\overrightarrow{\rm a}$, kí hiệu là $-\overrightarrow{\rm a}$.
Mỗi vector đều có vector đối, chẳng hạn vector đối của $\overrightarrow{\rm AB}$ là $\overrightarrow{\rm BA}$, nghĩa là $-\overrightarrow{\rm AB} = \overrightarrow{\rm BA}$.

![](https://i.imgur.com/SY5FFFo.png)

### Định nghĩa hiệu của 2 vector
Hiệu của vector $\overrightarrow{\rm u}$ với vector $\overrightarrow{\rm v}$ chính là tổng của $\overrightarrow{\rm u}$ và $-\overrightarrow{\rm v}$.

![](https://i.imgur.com/z9pRvDQ.png)

Nếu 2 vector có chung điểm đầu thì vector hiệu có hướng từ điểm cuối của $\overrightarrow{\rm v}$ đến điểm cuối của $\overrightarrow{\rm u}$. **Ví dụ:** $\overrightarrow{\rm OA} - \overrightarrow{\rm OB} = \overrightarrow{\rm BA}$.
Nếu 2 vector có chung điểm cuối thì vector hiệu có hướng từ điểm đầu của $\overrightarrow{\rm u}$ đến điểm đầu của $\overrightarrow{\rm v}$. **Ví dụ:** $\overrightarrow{\rm AO} - \overrightarrow{\rm BO} = \overrightarrow{\rm AB}$.

![](https://i.imgur.com/Au2Yjk4.png)

Nhấn vào [**đây**](https://www.desmos.com/calculator/po7zxtgzxw) để tương tác với hình trên Desmos.

# Tích vô hướng (Dot product)
Không như phép cộng trừ vector là tương đối trực quan và dễ hiểu, vector có 2 phép toán kém trực quan hơn là tích vô hướng (dot product) và tích có hướng (cross product).

Tích vô hướng có thể được định nghĩa bằng đại số hoặc hình học. 2 định nghĩa này là tương đương khi sử dụng tọa độ Descartes.

- Theo đại số, tích vô hướng là tổng các tích tọa độ tương ứng giữa chúng. Ví dụ: tích vô hướng của $\overrightarrow{\rm u}(x_1, y_1)$ và $\overrightarrow{\rm v}(x_2, y_2)$ là $\overrightarrow{\rm u} \cdot \overrightarrow{\rm v} = x_1x_2+y_1y_2$.
- Theo hình học, tích vô hướng là tích độ lớn của $2$ vector và $\cos$ của góc giữa chúng. Ví dụ: tích vô hướng của $\overrightarrow{\rm u}(x_1, y_1)$ và $\overrightarrow{\rm v}(x_2, y_2)$ là
$$\overrightarrow{\rm u} \cdot \overrightarrow{\rm v} = | \overrightarrow{\rm u} | \cdot | \overrightarrow{\rm v} | \cdot \cos(\theta)$$ với $\theta$ là góc hợp bởi $\overrightarrow{\rm u}$ và $\overrightarrow{\rm v}$.

![](https://i.imgur.com/iHks23u.png)

## Ví dụ
Tính tích vô hướng của 2 vector $\overrightarrow{\rm u}(5,12)$ và $\overrightarrow{\rm v}(-6,8)$

![](https://i.imgur.com/Qm8P625.png)

$$\begin{align}
\overrightarrow{\rm u} \cdot \overrightarrow{\rm v} &= x_1x_2+y_1y_2 \\
&= (-6).5+8.12 \\
&= 66
\end{align}$$

$$\begin{align}
\overrightarrow{\rm u} \cdot \overrightarrow{\rm v} &= | \overrightarrow{\rm u} | \cdot | \overrightarrow{\rm v} | \cdot \cos(\theta) \\
&= 13.10.cos(59,49°) \\
&= 65.9995359254\ldots \approx 66
\end{align}$$

---

Từ $2$ định nghĩa, ta có thể tính góc $\theta$ giữa $\overrightarrow{\rm u}(x_1,y_1)$ và $\overrightarrow{\rm v}(x_2,y_2)$ như sau:
$$\cos(\theta) = \dfrac{\overrightarrow{\rm u} \cdot \overrightarrow{\rm v}}{|\overrightarrow{\rm u}| \cdot |\overrightarrow{\rm v}|}
\Longrightarrow \theta = \arccos\left(\dfrac{\overrightarrow{\rm u} \cdot \overrightarrow{\rm v}}{|\overrightarrow{\rm u}| \cdot |\overrightarrow{\rm v}|}\right) = \arccos\left(\dfrac{x_1x_2+y_1y_2}{\sqrt{x_1^2+y_1^2} \cdot \sqrt{x_2^2+y_2^2}}\right)$$

**Lưu ý:** tích vô hướng không chỉ giới hạn trong hình học phẳng, nghĩa là ta có thể sử dụng tích vô hướng cho các vector có số chiều tuỳ ý, và đẳng thức trên vẫn đúng.

# Tích có hướng (Cross product)
## Trong không gian 3 chiều
Tích có hướng là một phép nhân vector trong không gian ba chiều. Nó khác tích vô hướng ở chỗ kết quả thu được là một vector thay cho một vô hướng. Vector này **vuông góc** với mặt phẳng chứa 2 vector đầu vào của phép nhân.

Tích có hướng được định nghĩa bằng công thức: $\overrightarrow{\rm a} \times \overrightarrow{\rm b} = \overrightarrow{n} \cdot |\overrightarrow{\rm a}| \cdot |\overrightarrow{\rm b}| \cdot \sin(\theta)$ với:
- $\theta$ là góc giữa $\overrightarrow{\rm a}$ và $\overrightarrow{\rm b}$ $(0° \le \theta \le 180°)$
- $\overrightarrow{n}$ là vectơ đơn vị vuông góc với $\overrightarrow{\rm a}$ và $\overrightarrow{\rm b}$. Thực tế có 2 vector thỏa điều kiện vuông góc là $\overrightarrow{n}$ và $-\overrightarrow{n}$, do đó hướng của vector đơn vị $\overrightarrow{n}$ phụ thuộc vào quy tắc bàn tay phải.

|![](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b0/Cross_product_vector.svg/220px-Cross_product_vector.svg.png)|![](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Right_hand_rule_cross_product.svg/330px-Right_hand_rule_cross_product.svg.png)|

## Trong không gian 2 chiều (mặt phẳng)
Nếu xét trong hình học phẳng thì vector kết quả lúc này vuông góc và có hướng đi vào/ra mặt phẳng đang xét, do đó ta có thể bỏ qua đặc điểm về hướng, và sử dụng tích có hướng như là một đại lượng vô hướng.

Tương tự tích vô hướng, tích có hướng trong không gian 2 chiều cũng có thể được định nghĩa bằng 2 cách:
- Theo đại số, tích có hướng giữa 2 vector $\overrightarrow{\rm u}(x_1,y_1)$ và $\overrightarrow{\rm v}(x_2,y_2)$ được định nghĩa bằng công thức:

$$\overrightarrow{\rm u} \times \overrightarrow{\rm v} = \begin{vmatrix} x_1 & y_1 \\ x_2 & y_2 \end{vmatrix} = x_1y_2-x_2y_1$$

- Theo hình học, tích có hướng giữa 2 vector $\overrightarrow{\rm u}$ và $\overrightarrow{\rm v}$ được định nghĩa bằng công thức: $\overrightarrow{\rm u} \times \overrightarrow{\rm v} = |\overrightarrow{\rm u}| \cdot |\overrightarrow{\rm v}| \cdot \sin(\theta)$ với $\theta$ là góc hợp bởi 2 vector tính từ $\overrightarrow{\rm u}$ đến $\overrightarrow{\rm v}$ và **ngược chiều kim đồng hồ**.
Với góc $\alpha$ thỏa mãn $0° < \alpha < 180°$ thì $\sin(\alpha) > 0$ nên nếu $\theta < 180°$ thì tích có hướng **dương**, ngược lại tích có hướng **âm**.

![](https://i.imgur.com/idZv0Xz.png)

Ta cũng có thể xác định dấu của tích có hướng bằng quy tắc bàn tay phải nhưng về bản chất thì cũng giống với việc xét góc theo chiều ngược kim đồng hồ.

## Ví dụ
Tính tích có hướng của 2 vector $\overrightarrow{\rm u}(5,12)$ và $\overrightarrow{\rm v}(-6,8)$

![](https://i.imgur.com/Qm8P625.png)

$$\begin{align}
\overrightarrow{\rm u} \times \overrightarrow{\rm v} &= \begin{vmatrix} x_1 & y_1 \\ x_2 & y_2 \end{vmatrix} = x_1y_2-x_2y_1 \\
&= 5.8-(-6).12 \\
&= 112
\end{align}$$

$$\begin{align}
\overrightarrow{\rm u} \times \overrightarrow{\rm v} &= |\overrightarrow{\rm u}| \cdot |\overrightarrow{\rm v}| \cdot \sin(\theta) \\
&= 13.10.sin(59,49°) \\
&= 112.000273471\ldots \approx	112
\end{align}$$

---

**Lưu ý:** Một tích chất hữu dụng của tích có hướng trong hình học phẳng là
$$| \overrightarrow{\rm a} \times \overrightarrow{\rm b}| = | \overrightarrow{\rm a}| \cdot| \overrightarrow{\rm b}| \cdot\sin(\theta)$$ bằng diện tích của hình bình hành có 2 cạnh bên là $\overrightarrow{\rm a}$ và $\overrightarrow{\rm b}$.

![](https://i.imgur.com/50a2Cp7.png)

Do đó, **diện tích của một tam giác** còn bằng một nửa giá trị tuyệt đối của tích có hướng với 2 vector thành phần là 2 cạnh của tam giác.

# Khoảng cách giữa điểm và đường thẳng
Tìm khoảng cách giữa điểm và đường thẳng rất thường gặp trong các bài toán hình học.

![](https://i.imgur.com/WBPuzNU.png)

Ví dụ bạn có 3 điểm $A, B, C$ và bạn muốn tìm khoảng cách từ $C$ đến đường thẳng đi qua $A$ và $B$. Bước đầu tiên là tính $\overrightarrow{\rm AB}$ và $\overrightarrow{\rm AC}$. Tiếp theo tính tích có hướng $\overrightarrow{\rm AB}\times\overrightarrow{\rm AC}$ và lấy trị tuyệt đối, rồi chia cho $AB$. Kết quả có được là khoảng cách cần tìm. Công thức này được giải thích như sau:

- Xét $\Delta{ABC}$, đặt $h$ là đường cao kẻ từ $C$ (khoảng cách từ $C$ đến $AB$) và đáy tương ứng là $AB$, ta có công thức:

$$\begin{cases}
S_{\Delta{ABC}} = \dfrac{h.AB}{2} \iff 2S_{\Delta{ABC}} = h.AB \\
2S_{\Delta{ABC}} = |\overrightarrow{\rm AB}\times\overrightarrow{\rm AC}|
\end{cases} \\
\begin{array}{}
\implies h.AB = |\overrightarrow{\rm AB}\times\overrightarrow{\rm AC}| \\
\iff h = \dfrac{|\overrightarrow{\rm AB}\times\overrightarrow{\rm AC}|}{AB}
\end{array}$$

Mọi thứ trở nên phức tạp hơn một chút khi ta muốn tìm khoảng cách từ một đoạn thẳng đến một điểm. Trong trường hợp này, điểm gần nhất có thể là một trong hai đầu mút của đoạn thẳng thay vì là một điểm nào đó trên đường thẳng. Trong hình trên, điểm gần $C$ nhất trên đường thẳng $AB$ không nằm giữa $A$ và $B$ mà là tại $B$.

Có vài cách khác nhau để xử lý trường hợp này, một trong số đó là tích vô hướng. Đầu tiên, kiểm tra xem điểm gần nhất trên đường thẳng $AB$ có ra khỏi $B$ hay không bằng cách tính $\overrightarrow{\rm BA} \cdot \overrightarrow{\rm BC}$. Nếu tích này **âm**, nghĩa là góc giữa $\overrightarrow{\rm BA}$ và $\overrightarrow{\rm BC}$ là góc tù (do với góc $\alpha$ thỏa mãn $90° < \alpha < 270°$ thì $\cos(\alpha) < 0$ ), do đó điểm gần $C$ nhất trên đoạn $AB$ sẽ là $B$.

Tương tự, nếu $\overrightarrow{\rm AB} \cdot \overrightarrow{\rm AC} < 0$, điểm gần $C$ nhất là $A$. Nếu cả hai tích vô hướng đều $\ge 0$, thì điểm gần $C$ nhất sẽ nằm giữa $A$ và $B$.

```cpp
#define x first
#define y second
typedef pair<int, int> pii;

// Compute the dot product AB ⋅ AC
int dot(pii A, pii B, pii C) {
    pii AB, AC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    return AB.x * AC.x + AB.y * AC.y;
}

// Compute the cross product AB x AC
int cross(pii A, pii B, pii C) {
    pii AB, AC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    return AB.x * AC.y - AB.y * AC.x;
}

// Compute the distance from A to B
double distance(pii A, pii B) {
    int dx = A.x - B.x;
    int dy = A.y - B.y;
    return sqrt(dx * dx + dy * dy);
}

// Compute the distance from AB to C
// if isSegment is true, AB is a segment, not a line.
double linePointDist(pii A, pii B, pii C, bool isSegment) {
    double dist = abs(cross(A, B, C)) / distance(A, B);
    if (isSegment) {
        int dot1 = dot(B, A, C);
        if (dot1 < 0) return distance(B, C);
        int dot2 = dot(A, B, C);
        if (dot2 < 0) return distance(A, C);
    }
    return dist;
}
```

Đoạn code trên là cách mà mọi người thường dùng và có lẽ khá là dài, bên dưới là viết lại có sử dụng struct trong C++.

``` cpp
typedef double db;
struct vec {
    db x, y;
    vec(db _x = 0, db _y = 0) : x(_x), y(_y) {}
    db dot(const vec &other) { // Compute the dot product
        return x * other.x + y * other.y;
    }
    db cross(const vec &other) { // Compute the cross product
        return x * other.y - y * other.x;
    }
    db length() const {
        return sqrt(x * x + y * y);
    }
};
using point = vec; // or use 'typedef vec point'
vec operator - (const point &B, const point &A) { // vecAB = B - A
    return vec(B.x - A.x, B.y - A.y);
}

// if isSegment is true, AB is a segment, not a line.
db linePointDist(const point &A, const point &B, const point &C, bool isSegment) {
    db dist = abs((B - A).cross(C - A)) / (A - B).length();
    if (isSegment) {
        db dot1 = (A - B).dot(C - B);
        if (dot1 < 0) return (B - C).length();
        db dot2 = (B - A).dot(C - A);
        if (dot2 < 0) return (A - C).length();
    }
    return dist;
}
```
Nếu bạn sử dụng C++ thì bạn nên tìm hiểu về struct và tự viết class/struct geo_2D của riêng mình. Nó sẽ giúp các bài toán hình học trở nên đơn giản hơn nhiều.

# Luyện tập:
Học phải đi đôi với hành, do đó mình đề xuất cho các bạn [Codeforces Gym 100168](https://codeforces.com/gym/100168). Tuy đề bài trong gym được viết bằng tiếng Nga nhưng rất ngắn gọn và đi thẳng vào bài toán nên các bạn có thể dễ dàng [google translate](https://translate.google.com/?hl=vi&sl=ru&tl=en&text=%D0%9F%D1%80%D0%B8%D0%B2%D0%B5%D1%82%2C%20%D0%BC%D0%B8%D1%80&op=translate).

Bên dưới là một số bài tập có liên quan đến bài viết này, mình đã tóm tắt yêu cầu bài toán để các bạn có thể hiểu đề dễ dàng hơn.

- **Codeforces Gym - 100168L**: tính độ độ dài (độ lớn) vector
- **Codeforces Gym - 100168D**: tính diện tích tam giác
- [**CSES - Polygon Area**](https://cses.fi/problemset/task/2191): tính diện tích đa giác
- **Codeforces Gym - 100168F**: tính khoảng cách từ 1 điểm đến 1 đường thẳng có dạng $Ax+By+C=0$
- **Codeforces Gym - 100168G**: tính khoảng cách từ 1 điểm đến 1 đường thẳng đi qua 2 điểm
- **Codeforces Gym - 100168H**: tính khoảng cách từ 1 điểm đến 1 tia
- **Codeforces Gym - 100168I**: tính khoảng cách từ 1 điểm đến 1 đoạn thẳng
