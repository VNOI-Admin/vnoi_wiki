---
title: Hình học tính toán phần 3: Đa giác
description: 
published: true
date: 2026-01-16T10:44:37.023Z
tags: 
editor: markdown
dateCreated: 2025-03-24T16:51:02.046Z
---

# Hình học tính toán phần 3: Đa giác

**Tác giả:**
- Nguyễn Đức Kiên - Trường Đại học Công nghệ, ĐHQGHN

**Reviewers:**
- Nguyễn Tấn Minh – THPT Chuyên Lê Hồng Phong, TPHCM
- Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành - Kon Tum
- Nguyễn Minh Hiển – Trường Đại học Công nghệ, ĐHQGHN

Tiếp nối hai phần trước của series _Hình học tính toán_, trong bài viết này, ta sẽ tập trung vào các bài toán liên quan đến đa giác, diện tích đa giác và tính chất của các điểm thuộc đa giác.

Các bài viết trước thuộc series *Hình học tính toán*:
- [Phần 1: Các khái niệm cơ bản](/algo/geometry/basic-geometry-1)
- [Phần 2: Sự giao nhau của các đường thẳng](/algo/geometry/basic-geometry-2)

## Kiến thức cơ bản về đa giác

### Một số thuật ngữ

Phần dưới đây liệt kê một số thuật ngữ quen thuộc với đa giác:

- **Đa giác** (**polygon**) là một đường gấp khúc khép kín. Nghĩa là, nó là một tập hợp các đoạn thẳng, sao cho hai đoạn thẳng liên tiếp nhau (đoạn cuối cùng và đoạn đầu tiên cũng tính là hai đoạn liên tiếp) cắt nhau tại một đầu mút của hai đoạn thẳng đó.
- **Cạnh** (**edge** hoặc **side**) của đa giác là các đoạn thẳng tạo nên đa giác
- **Đỉnh** (**vertex**, số nhiều **vertices**) của đa giác là các đầu mút của các đoạn thẳng tạo nên đa giác. Hiển nhiên, đa giác có $n$ đỉnh thì sẽ có $n$ cạnh và ngược lại. Do vậy, người ta thường nhóm các loại đa giác lại theo số cạnh (cũng là số đỉnh) và gọi nó bằng những cái tên quen thuộc như tam giác (triangle), tứ giác (quadrilateral), ngũ giác (pentagon), lục giác (hexagon), ... cho đến hình $n$-cạnh ($n$-gon). Các đa giác được gọi tên bằng các đỉnh theo thứ tự cùng hoặc ngược chiều kim đồng hồ, chẳng hạn dưới đây ta có hình 7 cạnh $ABCDEFG$:
![geo1.png](/algo/geometry/p3/geo1.png)
- **Đa giác lồi** (**convex polygon**) là loại đa giác mà trong đó với hai đỉnh bất kỳ thuộc đa giác, đoạn thẳng nối hai đỉnh đó nằm hoàn toàn trong đa giác. Nói cách khác, nếu kéo dài tất cả các cạnh của đa giác ra thì chúng sẽ không cắt nhau ở vị trí nào nằm bên trong đa giác. $ABCDEFG$ trong hình trên là một đa giác lồi.
- **Đường chéo** (**diagonal**) của một đa giác là đoạn thẳng nối hai đỉnh không kề nhau của đa giác. Với đa giác trên, nếu nối $A$ và $E$ lại ta có một đường chéo
- **Đa giác đều** (**regular polygon**) là đa giác có tất cả các cạnh và các góc giữa hai cạnh kề nhau là bằng nhau. 

**Lưu ý**: Trong bài viết này, nếu không có chú thích gì thêm, khi nhắc đến "đa giác" chúng ta sẽ hiểu đó là đa giác lồi.

### Một số tính chất của đa giác

- Tổng các góc trong đa giác $n$ cạnh là $180(n-2)$ độ.
- Trong đa giác lồi $n$ cạnh, tại mỗi đỉnh ta vẽ được $n-3$ đường chéo, cùng với các cạnh chúng tạo ra $n-2$ tam giác con. Như vậy, từ các đỉnh trong đa giác, ta có thể vẽ được nhiều nhất $\frac{n(n-3)}{2}$ đường chéo.
- Các đa giác đều có chẵn cạnh vừa có tâm đối xứng vừa có trục đối xứng, còn các đa giác đều có lẻ cạnh thì chỉ có tâm đối xứng. 
- **Bất đẳng thức đa giác**: Độ dài một cạnh bất kỳ của một đa giác lồi luôn nhỏ hơn tổng độ dài các cạnh còn lại. Cụ thể, trong đa giác gồm $n$ cạnh có độ dài lần lượt là $a_1$, $a_2$, ..., $a_n$, ta có: 
$$\forall_i\in[1, n], a_i<\sum_{1\leq j\leq n, j\neq i}a_j$$ 
Bất đẳng thức cũng có thể được biểu diễn sử dụng cạnh lớn nhất trong đa giác: 
$$2\max_{1\leq i\leq n}a_i < \sum_{i = 1}^na_i$$

### CTDL biểu diễn

Để có thể giải quyết các bài toán hình học tính toán một cách hiệu quả, ta nên xây dựng các struct riêng cho từng đối tượng.

Trong bài này, các điểm, vector và đa giác sẽ được cài đặt bằng các CTDL sau: 

```cpp=
#include <vector>

using namespace std;

struct Point{
    int x;
    int y;

    // Khởi tạo mặc định
    Point();

    // Khởi tạo điểm từ toạ độ
    Point(int __x, int __y): x(__x), y(__y) {}
};

struct Vector {
    int x;
    int y;

    // Khởi tạo mặc định vector
    Vector();

    // Khởi tạo vector từ điểm đầu và điểm cuối
    Vector(Point p, Point q): x(q.x - p.x), y(q.y - p.y) {}
    
    // Tích có hướng của vector hiện tại và một vector khác
    long long operator ^ (const Vector &v2) const {
        return 1ll * x * v2.y - 1ll * y * v2.x;
    }
};

struct Polygon {
    // Số đỉnh thuộc đa giác
    int nVertices;
    
    // Danh sách các đỉnh thuộc đa giác
    vector <Point> vertices;

    // Khởi tạo mặc định
    Polygon();
    
    // Khởi tạo tam giác từ các đỉnh
    Polygon(Point A, Point B, Point C) : vertices({A, B, C}), nVertices(3) {}

    // Khởi tạo đa giác từ danh sách đỉnh
    Polygon(const vector <Point> &__vertices) : vertices(__vertices), nVertices(__vertices.size()) {}
    
    // Diện tích, được cài đặt tại phần Diện tích đa giác
    double area();

    // Hai lần diện tích, được cài đặt tại phần Diện tích đa giác
    long long area2();
};
```

## Diện tích đa giác

Độ lớn của phần mặt phẳng bị chiếm chỗ bởi một đa giác được gọi là diện tích của đa giác đó. Người ta thường dùng chữ $S$ để ký hiệu diện tích, chẳng hạn diện tích ngũ giác $ABCDE$ có thể được ký hiệu là $S_{ABCDE}$.

**Bài toán**: [VNOJ - Diện tích đa giác](https://oj.vnoi.info/problem/geo_c)

**Tóm tắt đề bài**: Cho đa giác lồi được tạo thành từ $n$ điểm cho trước theo đúng thứ tự đó, điểm thứ $i$ trong số đó có toạ độ là $(x_i, y_i)$. Tính diện tích đa giác trên.

![geo1.png](/algo/geometry/p3/geo2.png)

### Ý tưởng

Gọi $n$ điểm thuộc đa giác theo đúng thứ tự trên là $A_1, A_2, ..., A_n$, trong đó $A_1$ là điểm có tung độ nhỏ nhất trong số các điểm cùng có hoành độ nhỏ nhất. Để tiện biểu diễn các công thức, trong bài viết này ta sẽ quy ước thêm $A_{n + 1} \equiv A_1$.

Các công thức tính diện tích cho tam giác và một số dạng tứ giác đặc biệt vốn đã rất phổ biến. Tuy vậy, gần như chẳng có công thức nào cho phép ta tính ngay diện tích của một đa giác bất kỳ (ngay cả tứ giác đã khó rồi). Chỉ có một cách duy nhất để giải bài toán này: chia hình này thành những hình có thể tính được diện tích.

#### Công thức Shoelace (công thức tam giác)

Nếu bài toán trên xuất hiện trong đề thi vào THPT, với một hình vẽ chẳng có tính chất gì đặc biệt cả, ta đành phải chọn cách chia đơn giản nhất: đường chéo. Tại một đỉnh của đa giác, vẽ các đường chéo đến tất cả các đỉnh không kề với nó: 
![geo1.png](/algo/geometry/p3/geo3.png)

Bây giờ, hình đa giác đã chuyển thành một loạt các tam giác. Mà tam giác thì số công thức tính diện tích nhiều vô kể:
- $S_{ABC} = \frac{1}{2} \times BC \times d(A, BC)$, trong đó $d(M, l)$ là khoảng cách từ điểm $M$ đến đường thẳng $l$.
- $S_{ABC} = \sqrt{p(p - BC)(p - CA)(p - AB)}$, với $p$ là nửa chu vi của tam giác $ABC$
- $S_{ABC} = \frac{1}{2}AB\times AC\times\sin{\hat{A}} = \frac{1}{2}|\overrightarrow{AB}\times\overrightarrow{AC}|$, trong đó $\vec{u}\times\vec{v}$ là [phép nhân có hướng hai vector](https://wiki.vnoi.info/algo/geometry/basic-geometry-1#trong-kh%C3%B4ng-gian-2-chi%E1%BB%81u-m%E1%BA%B7t-ph%E1%BA%B3ng)
- $S_{ABC} = pr$, với $r$ là bán kính đường tròn nội tiếp tam giác (nếu bạn tính được nó).
- ...


Sau khi áp dụng các công thức để tính diện tích tam giác, việc còn lại chỉ là cộng các kết quả lại. Tổng nhận được chắc chắn là diện tích của đa giác cần tính.

Trong các công thức trên, hai công thức đầu ít nhiều phải sử dụng phép căn bậc hai, còn công thức thứ ba với phép toán vector thì đơn giản hơn cả. Khi các đỉnh của đa giác được cho ngược chiều kim đồng hồ, ta có thể bỏ giá trị tuyệt đối của công thức trên: 
$$S=\frac{1}{2}\sum_{i = 2}^{n-1}\overrightarrow{A_1A_i}\times \overrightarrow{A_1A_{i+1}}\tag{1}$$

Đến đây, ta đã có một công thức khá đẹp để tính diện tích đa giác. Tuy nhiên, ta vẫn có thể tiếp tục biến đổi $(1)$ để có công thức đẹp hơn. Ta thấy với $i = 1$ và $i = n$, $\overrightarrow{A_1A_i}\times \overrightarrow{A_1A_{i+1}}$ nhận giá trị bằng $0$. Vì vậy:   
$$\begin{align}S &= \frac{1}{2}\sum_{i = 1}^{n} \overrightarrow{A_1A_i}\times \overrightarrow{A_1A_{i+1}}\\ &= \frac{1}{2}\sum_{i = 1}^{n}((x_i-x_1)(y_{i+1}-y_1) - (y_i-y_1)(x_{i+1}-x_1))\\&=\frac{1}{2}\sum_{i = 1}^{n}(x_iy_{i+1}-x_iy_1-x_1y_{i+1}-x_{i+1}y_i+x_1y_i+x_{i+1}y_1)\tag{2}\end{align}$$

Ta áp dụng lại phép chia đa giác và tính diện tích, nhưng lần này với các đỉnh từ $A_2$ đến $A_n$ và thu được các đẳng thức giống như $(2)$. Cộng các kết quả trên lại, ta được: 
$$\begin{align}nS &= \frac{1}{2}\sum_{j = 1}^n\sum_{i = 1}^n(x_iy_{i+1}-x_iy_j-x_jy_{i+1}-x_{i+1}y_i+x_jy_i+x_{i+1}y_j)\\&=\frac{n}{2}\sum_{i = 1}^n(x_iy_{i+1}-x_{i+1}y_i) \\&\quad+ \frac{1}{2}\sum_{i = 1}^n\sum_{j = 1}^n(-x_iy_j + x_jy_i - x_jy_{i+1}+x_{i+1}y_j)\\&=\frac{n}{2}\sum_{i = 1}^n(x_iy_{i+1}-x_{i+1}y_i)\tag{3}\end{align}$$

Suy ra: 
$$S=\frac{1}{2}\sum_{i = 1}^n{(x_iy_{i+1}-x_{i+1}y_i)}\tag{4}$$

Trong trường hợp các đỉnh được cho theo thứ tự ngược lại, $(1)$ sẽ phải viết lại thành 
$$S=-\frac{1}{2}\sum_{i = 2}^{n-1}\overrightarrow{A_1A_i}\times \overrightarrow{A_1A_{i+1}}$$ 
Hoàn toàn tương tự, ta biến đổi được thành công thức giống như $(4)$: 
$$S=-\frac{1}{2}\sum_{i = 1}^n{(x_iy_{i+1}-x_{i+1}y_i)}$$ 
Như vậy, diện tích của một đa giác với các đỉnh được cho lần lượt theo thứ tự, không phân biệt cùng chiều hay ngược chiều kim đồng hồ là: 
$$S=\frac{1}{2}\left|\sum_{i = 1}^n{(x_iy_{i+1}-x_{i+1}y_i)}\right|\tag{5}$$

Công thức này được gọi là **công thức tam giác**.

Người ta cũng hay viết $(5)$ thành dạng định thức như sau: 
$$S=\frac{1}{2}\left|\det\begin{bmatrix}x_1 & x_2 & ... & x_n & x_1 \\ y_1 & y_2 & ... & y_n & y_1\end{bmatrix}\right|\tag{6}$$

Do khi tính định thức, ta lấy tổng của các hiệu giữa hai phần tử chéo nhau, người ta cũng gọi công thức tam giác là **công thức Shoelace (Shoelace Formula)** (shoelace nghĩa là dây giày).

Công thức tam giác $(5)$ cũng có thể biến đổi một lần nữa thành dạng vector: 
$$S=\frac{1}{2}\left|\sum_{i = 1}^n\overrightarrow{OA_i}\times \overrightarrow{OA_{i + 1}}\right|\tag{7}$$ 
trong đó $O(0, 0)$ là gốc toạ độ.

#### Công thức hình thang

Bằng một hướng tiếp cận khác, chúng ta cũng có công thức sau: 

**Định lý**: Diện tích đa giác $A_1A_2...A_n$ với các đỉnh được sắp xếp theo thứ tự cùng chiều hoặc ngược chiều kim đồng hồ là: 
$$S = \frac{1}{2}\left|\sum_{i = 1}^n(x_i-x_{i+1})(y_i + y_{i+1})\right|\tag{8}$$

Công thức $(8)$ được gọi là **công thức hình thang (Trapezoid Formula)**.

Về cơ bản, nếu ta khai triển công thức hình thang, ta vẫn sẽ thu được công thức tam giác. Tuy nhiên, có một cách chứng minh chỉ sử dụng phép chia hình và diện tích của những hình cơ bản, bạn đọc tham khảo bên dưới.

:::spoiler **Chứng minh (nhấn để hiện)**

Xét trường hợp các đỉnh được cho ngược chiều kim đồng hồ. Với mọi $A_i$, gọi $H_i$ là hình chiếu của $A_i$ lên trục hoành $Ox$. Khi đó có các tình huống sau xảy ra:

**Trường hợp 1**: $Ox$ có không quá 1 giao điểm với các cạnh của đa giác

![geo1.png](/algo/geometry/p3/geo4.png)

Xét hình thang $A_1H_1H_2A_2$ (đây là hình thang vì $A_1H_1$ song song với $A_2H_2$ do cùng vuông góc với $Ox$). Diện tích hình thang trên là: 
$$\begin{align}S_{A_1H_1H_2A_2} &=\frac{A_1H_1+A_2H_2}{2}\\ &=\frac{(x_2 - x_1)(y_2+y_1)}{2}\end{align}$$

Hoàn toàn tương tự, ta tính được diện tích của các hình thang $A_iH_iH_{i+1}A_{i+1}$: 
$$\begin{align}S_{A_iH_iH_{i+1}A_{i+1}} &=\frac{|x_{i+1}-x_i|(y_{i+1}+y_i)}{2}\end{align}$$ 

Ta có thể thấy trên đa giác, tồn tại một điểm $A_k$ nào đó sao cho, $x_{i+1} \geq x_i$ với $i \leq k$ và $x_{i+1} \leq x_i$ với $i > k$, do các điểm đã được sắp theo thứ tự ngược chiều kim đồng hồ. Như vậy, diện tích đa giác đã cho bằng hiệu giữa diện tích đa giác $A_kA_{k+1}...A_1H_1H_k$ (phần phía trên) và đa giác $A_1A_2...A_kH_kH_1$ (phần phía dưới). Diện tích của hai đa giác này lại được tính bằng tổng diện tích các hình thang. Như vậy, diện tích đa giác $A_1A_2...A_n$ được tính như sau: 
$$\begin{align}S &= S_{A_kA_{k+1}...A_1H_1H_k} - S_{A_1A_2...A_kH_kH_1} \\ &= \sum_{i = k + 1}^n\frac{|x_i-x_{i+1}|(y_i + y_{i+1})}{2} - \sum_{i = 1}^k\frac{|x_i-x_{i+1}|(y_i + y_{i+1})}{2} \\ &= \sum_{i = k + 1}^n\frac{(x_i-x_{i+1})(y_i + y_{i+1})}{2} + \sum_{i = 1}^k\frac{(x_i-x_{i+1})(y_i + y_{i+1})}{2} \\ &= \sum_{i = 1}^n\frac{(x_i-x_{i+1})(y_i + y_{i+1})}{2} \\&=\frac{1}{2}\sum_{i = 1}^n(x_i-x_{i+1})(y_i + y_{i+1})\end{align}$$

**Trường hợp 2**: $Ox$ có 2 giao điểm với các cạnh của đa giác

![geo1.png](/algo/geometry/p3/geo5.png)

Giả sử giá trị $y_i$ nhỏ nhất trong tất cả các điểm $A_i$ là $\zeta$. Ta tịnh tiến đa giác theo vector có toạ độ $(0, Y)$, trong đó $Y > \zeta$. Tức là, ta biến đa giác $A_1A_2...A_n$ thành đa giác $B_1B_2...B_n$, trong đó $B_i$ có toạ độ là $(x_i, y_i + Y)$. Do $Y > \zeta$, có thể khẳng định mọi giá trị $y_i + Y$ đều dương. Như vậy, đa giác $B_1B_2...B_n$ không có cạnh nào cắt trục $Ox$. Theo trường hợp thứ nhất, diện tích của đa giác mới tạo thành là: 
$$\begin{align}S' &= \frac{1}{2}\sum_{i = 1}^n(x_i-x_{i+1})(y_i + Y + y_{i+1} + Y)\\&=\frac{1}{2}\times2Y\sum_{i=1}^n(x_i-x_{i+1}) + \frac{1}{2}\sum_{i = 1}^n(x_i-x_{i+1})(y_i + y_{i+1})\\&=\frac{1}{2}\sum_{i = 1}^n(x_i-x_{i+1})(y_i + y_{i+1})\end{align}$$ 
Ta cũng biết rằng, phép tịnh tiến tạo ra hình mới bằng với hình cũ, và diện tích của chúng là giống nhau. Vậy diện tích hình $A_1A_2...A_n$ là $S = S'$.

Như vậy, trong cả hai trường hợp, diện tích của đa giác với các đỉnh được cho ngược chiều kim đồng hồ được tính theo công thức sau: 
$$S = \frac{1}{2}\sum_{i = 1}^n(x_i-x_{i+1})(y_i + y_{i+1})$$

Hoàn toàn tương tự, khi các đỉnh được cho cùng chiều kim đồng hồ, diện tích của đa giác là: 
$$S = -\frac{1}{2}\sum_{i = 1}^n(x_i-x_{i+1})(y_i + y_{i+1})$$ 

Hai công thức trên đều cho kết quả không âm. Vậy ta có điều phải chứng minh.

_Chú ý_: Cách chứng minh trên mô phỏng phép tính tích phân. Sử dụng phép tính tích phân, chứng minh trên sẽ còn đơn giản hơn nữa.

:::

### Cài đặt

Dưới đây là cài đặt của công thức tam giác $(5)$:

```cpp=
double Polygon::area() {
    long long s = 0;
    for (int i = 0; i < nVertices; i ++) {
        int i1 = (i + 1) % nVertices;
        s += 1ll * vertices[i].x * vertices[i1].y
            - 1ll * vertices[i].y * vertices[i1].x;
    }
    return abs(1.0 * s / 2);
}
```

Nếu nộp thử đoạn code trên, ta sẽ thấy kết quả chưa được đẹp lắm. Về mặt lý thuyết, phương pháp này không có gì sai. Vấn đề nằm ở kiểu dữ liệu `double`. Đối với kiểu này, các số được biểu diễn dưới dạng dấu phẩy động $\pm\overline{1.????...??}\times 10^{\pm\overline{???}}$, bao gồm 1 bit dấu $\pm$, 11 bit cho phần luỹ thừa và 52 bit cho phần sau dấu thập phân. Với số lượng bit để biểu diễn phần thập phân hạn chế như vậy, ta không thể biểu diễn chính xác tất cả các số trên miền giá trị của kết quả. Chẳng hạn, xét tam giác có toạ độ các đỉnh là $(-10^9 - 1, -10^9 - 1)$, $(10^9 + 1, -10^9 - 1)$, $(-10^9 - 1, 10^9 + 1)$, diện tích của nó sẽ là $2\times 10^{18} + 4\times 10^9 + 2$. Số này muốn biểu diễn chính xác ở dạng số nguyên phải dùng tới 61 bit (chưa tính dấu), do vậy ta không thể có kết quả đúng tới từng chữ số bằng `double` được.`long double` có vẻ cũng là một lựa chọn, tuy nhiên trên phần lớn hệ máy, đó cũng chỉ là `double` mà thôi.

Để ý thấy hai lần diện tích của đa giác là một số nguyên. Lợi dụng điều đó, với bài toán yêu cầu in ra chính xác diện tích đa giác, ta làm như sau:
```cpp=
long long Polygon::area2() {
    long long s = 0;
    for (int i = 0; i < nVertices; i ++) {
        int i1 = (i + 1) % nVertices;
        s += 1ll * vertices[i].x * vertices[i1].y
            - 1ll * vertices[i].y * vertices[i1].x;
    }
    return abs(s);
}

int main() {
    Polygon plg;
    // ...
    auto s = plg.area2();
    cout << s / 2 << "." << 5 * (s % 2);
    return 0;
}
```


Nếu bạn thích dùng tích có hướng như công thức $(7)$ thì có thể làm như sau: 

```cpp=
long long Polygon::area2() {
    long long s = 0;
    Point o(0, 0);
    for (int i = 0; i < nVertices; i ++) {
        int i1 = (i + 1) % nVertices;
        Vector vi(o, vertices[i]);
        Vector vi1(o, vertices[i1]);
        s += (vi ^ vi1);
    }
    return abs(s);
}
```


### Đánh giá

Rất dễ dàng để nhận ra rằng độ phức tạp về cả không gian và thời gian cần để cài đặt tất cả các công thức đã nói trên là $\mathcal{O}(n)$

### Chú ý

- Trong các ví dụ trên, các điểm đã được cho theo đúng thứ tự tạo thành các đỉnh của đa giác lồi. Nếu các điểm không được cho theo một thứ tự nào cả và biết rằng đa giác cần tính diện tích là đa giác lồi, thì ta cần sắp xếp chúng theo thứ tự bằng các thuật toán tìm [bao lồi](/translate/wcipeg/Convex-Hull).
- Các công thức tam giác $(5)$, $(6)$, $(7)$ và công thức hình thang $(8)$ vẫn đúng với đa giác không lồi và không tự cắt. Bạn đọc có thể thử tự chứng minh các khẳng định này.
- Khi cài đặt các công thức diện tích trên với bài toán có toạ độ nguyên, để hạn chế tối đa làm việc với số thực, ta thường chỉ dừng lại ở việc tính hai lần diện tích, và nếu được hỏi thì mới lấy kết quả sau khi chia cho $2$, giống như cách cài đặt ở trên

## Vị trí tương đối của điểm và đa giác

C.Jordan đã chứng minh rằng: Mọi đa giác không tự cắt đều chia mặt phẳng thành hai miền, một miền bên trong đa giác và một miền bên ngoài đa giác. Như vậy, một điểm có thể nằm ở một trong ba vị trí tương đối sau với một đa giác:
- Nằm trong đa giác
- Nằm ngoài đa giác
- Nằm trên cạnh của đa giác

```cpp=
enum PointPolygonPosition {
    INSIDE,    // điểm nằm trong đa giác
    OUTSIDE,   // điểm nằm ngoài đa giác
    BOUNDARY   // điểm nằm trên cạnh đa giác
};
```

**Bài toán**: Cho đa giác $n$ đỉnh $A_1A_2...A_n$ không tự cắt, điểm thứ $i$ có toạ độ $(x_i, y_i)$ theo thứ tự ngược chiều kim đồng hồ. Cho $m$ điểm $P_1, P_2, ..., P_m$, với mỗi điểm $P_j$ hãy kiểm tra xem điểm này nằm trong, nằm trên cạnh hay nằm ngoài đa giác, biết rằng:
a) Đa giác đã cho là đa giác lồi
b) Đa giác đã cho là đa giác không tự cắt bất kỳ (tức là có thể không lồi)

### Trường hợp đa giác lồi

Để thực hành trường hợp này, bạn đọc tham khảo bài [Codeforces - Theodore Roosevelt](https://codeforces.com/problemsets/acmsguru/problem/99999/253).

#### Kiểm tra bằng diện tích

![geo1.png](/algo/geometry/p3/geo6.png)

Kiểm tra bằng diện tích là phương pháp đơn giản nhất để xem một điểm có nằm trong đa giác không. 

Với mỗi điểm $P_j$, nối $P_j$ với các đỉnh $A_i$ của tam giác. Ta tính tổng diện tích các tam giác $P_jA_iA_{i+1}$. Sẽ có các trường hợp sau xảy ra (xem hình minh hoạ ở trên để hiểu rõ hơn):
- Nếu tổng trên có diện tích bằng đúng diện tích đa giác, và tất cả các tam giác đều có diện tích khác $0$, ta kết luận điểm $P_j$ nằm bên trong đa giác
- Nếu tổng trên có diện tích bằng đúng diện tích đa giác, và trong số các tam giác $P_jA_iA_{i+1}$ tồn tại ít nhất một tam giác có diện tích bằng $0$ thì ta kết luận điểm $P_j$ nằm trên một cạnh của đa giác
- Nếu tổng trên khác diện tích của đa giác $A_1A_2...A_n$ thì ta kết luận điểm $P_j$ nằm ngoài đa giác.

```cpp=
PointPolygonPosition position(Polygon plg, Point p) {
    long long sSumTris = 0;
    for (int i = 0; i < plg.nVertices; i++) {
        int i1 = (i + 1) % plg.nVertices;
        Polygon tri(p, plg.vertices[i], plg.vertices[i1]);
        auto sTri = tri.area2();
        if (!sTri) {
            return BOUNDARY;
        }
        sSumTris += sTri;
    }
    return (sSumTris == plg.area2() ? INSIDE : OUTSIDE);
}

```

Cách kiểm tra này có độ phức tạp không gian là $\mathcal{O}(n)$, còn độ phức tạp thời gian là $\mathcal{O}(mn)$.

#### Kiểm tra bằng cách chia nhị phân

Do đa giác đã cho là đa giác lồi, nên nếu một điểm $P_j$ nằm trong đa giác, sẽ xảy ra hai trường hợp:
- Tồn tại một giá trị $k < n$ để $P_j$ nằm trong hoặc nằm trên cạnh của tam giác $A_1A_kA_{k + 1}$
- Điểm $P_j$ nằm trên cạnh $A_nA_1$.

![geo1.png](/algo/geometry/p3/geo7.png)

Ta có thể dễ dàng kiểm tra trường hợp thứ hai bằng cách kiểm tra xem hai vector $\overrightarrow{P_jA_1}$ và $\overrightarrow{P_jA_n}$ có cùng phương không (hoặc bất kỳ cách nào bạn thích để kiểm tra ba điểm thẳng hàng).

Xét trường hợp thứ nhất. Ta biết tất cả các đỉnh của đa giác được sắp xếp theo thứ tự ngược chiều kim đồng hồ. Do vậy, nếu điểm $P_j$ nằm bên trong đa giác, sẽ tồn tại một đỉnh $A_k$ ($k \leq n$) của đa giác để $P_j$ nằm trong góc $\widehat{A_kA_1A_{k+1}}$. Lúc này, các vector $\overrightarrow{A_1A_i}$ ứng với các đường chéo từ $A_1A_2$ đến $A_1A_k$ sẽ nằm bên trái hoặc cùng phương với $\overrightarrow{A_1P_j}$, và các vector ứng với các đường chéo còn lại nằm bên phải $\overrightarrow{A_1P_j}$. Tính chất này làm ta nghĩ ngay đến việc sử dụng chia nhị phân để tìm kiếm điểm $A_k$ nói trên.

Về kiểm tra tính chất "trái, phải", ta sử dụng phép nhân có hướng vector (xem [phần 2](/algo/geometry/basic-geometry-2#ki%E1%BB%83m-tra-giao-%C4%91i%E1%BB%83m-c%E1%BB%A7a-2-%C4%91o%E1%BA%A1n-th%E1%BA%B3ng-s%E1%BB%AD-d%E1%BB%A5ng-t%C3%ADch-c%C3%B3-h%C6%B0%E1%BB%9Bng) của series này)
- "$\overrightarrow{A_1A_i}$ nằm bên trái hoặc cùng phương với $\overrightarrow{A_1P_j}$" đồng nghĩa với "$A_1, P_j, A_i$ nằm ngược chiều kim đồng hồ hoặc thẳng hàng", tương đương với điều kiện $\overrightarrow{A_1P_j}\times\overrightarrow{A_1A_i} \geq 0$
- "$\overrightarrow{A_1A_i}$ nằm bên phải $\overrightarrow{A_1P_j}$" đồng nghĩa với "$A_1, P_j, A_i$ nằm cùng chiều kim đồng hồ", tương đương với điều kiện $\overrightarrow{A_1P_j}\times\overrightarrow{A_1A_i} < 0$

Tóm lại, để kiểm tra vị trí tương đối của một điểm $P_j$, ta làm như sau:
- Kiểm tra $P_j$ có nằm trên đường thẳng $A_nA_1$ không. Nếu có, kết luận $P_j$ nằm trên cạnh nếu nó nằm giữa hoặc trùng với $A_n$ và $A_1$, hoặc nằm ngoài đa giác nếu nó không nằm giữa hai điểm trên. Nếu không, tiếp tục sang bước thứ hai.
- Với mỗi điểm $P_j$, tìm số $k$ nhỏ nhất sao cho $A_1A_k$ nằm bên trái hoặc trùng với $A_1P_j$, sử dụng tìm kiếm nhị phân và tích có hướng. Nếu $P_j$ đã được sắp xếp theo thứ tự ngược chiều kim đồng hồ với $A_1$, có thể sử dụng phương pháp hai con trỏ. Nếu không có số $k$ như vậy thì kết luận $P_j$ nằm ngoài đa giác.
- Kiểm tra xem điểm $P_j$ có nằm trên cạnh $A_kA_{k-1}$ không, nếu có thì kết luận điểm $P_j$ nằm trên cạnh của đa giác. Nếu không, kiểm tra xem điểm $P_j$ có nằm trong tam giác $A_1A_kA_{k-1}$ không, nếu nằm bên trong thì ta kết luận $P_j$ nằm trong đa giác, còn nếu không thì ta kết luận $P_j$ nằm ngoài đa giác.

![geo1.png](/algo/geometry/p3/geo8.png)


```cpp=
bool isCW(Point a, Point b, Point c) {
    return (Vector(a, b) ^ Vector(a, c)) < 0;
}

PointPolygonPosition position(Polygon plg, Point p) {
    // Kiểm tra P có thuộc A1An không
    Vector pa1(p, plg.vertices[0]);
    Vector pan(p, plg.vertices[plg.nVertices - 1]);
    if (pa1 ^ pan == 0) {
        if (1ll * pa1.x * pan.x <= 0) {
            return BOUNDARY;
        }
        return OUTSIDE;
    }

    // Tìm kiếm nhị phân điểm k
    int l = 1, r = plg.nVertices;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (isCW(plg.vertices[0], p, plg.vertices[mid])) {
            l = mid;
        } else {
            r = mid;
        }
    }
    int k = l;
    if (k == plg.nVertices - 1) {
        return OUTSIDE;
    }
    
    // Kiểm tra xem P có thuộc tam giác không
    if (Vector(p, plg.vertices[k]) ^ Vector(p, plg.vertices[k + 1]) == 0) {
        return BOUNDARY;
    }
    long long ss = 0;
    ss += Polygon(p, plg.vertices[0], plg.vertices[k]).area2();
    ss += Polygon(p, plg.vertices[k], plg.vertices[k + 1]).area2();
    ss += Polygon(p, plg.vertices[k + 1], plg.vertices[0]).area2();
    if (ss == Polygon(plg.vertices[0], plg.vertices[k], 
                      plg.vertices[k + 1]).area2()) {
        return INSIDE;
    }
    return OUTSIDE;
}
```

Cách làm trên có độ phức tạp không gian là $\mathcal{O}(n)$ và độ phức tạp thời gian là $\mathcal{O}(n + m\log(n))$. Nếu được phép xử lý offline và sử dụng hai con trỏ, độ phức tạp không gian và thời gian lần lượt chuyển thành $\mathcal{O}(n + m)$ và $\mathcal{O}(m\log m + n)$.

### Trường hợp đa giác không tự cắt bất kỳ

Để thực hành trường hợp này, bạn đọc tham khảo bài [CSES - Point in Polygon](https://cses.fi/problemset/task/2192).

Nếu đa giác có "góc lõm", hai phương pháp trên sẽ không sử dụng được nữa. 

Đề kiểm tra điểm thuộc miền trong hay ngoài đa giác đơn (không tự cắt), có một thuật toán rất nổi tiếng. Đó là thuật toán **chiếu tia** (**ray casting**). Theo đó, từ mỗi điểm $P_j$, ta dựng một tia theo một hướng bất kỳ. Sau đó, ta đếm số giao điểm của tia này với các cạnh thuộc đa giác. Nếu số giao điểm là chẵn, điểm này bên ngoài đa giác, ngược lại nó nằm trong đa giác. Trường hợp điểm thuộc cạnh đa giác được xét riêng.

![geo1.png](/algo/geometry/p3/geo9.png)

Với dữ kiện đầu vào của bài toán, các đỉnh của đa giác đã được cho theo thứ tự. Như vậy, ta chỉ cần duyệt qua toàn bộ các cặp đỉnh để đểm số giao điểm. Về phần điểm $P_j$, ta sẽ sử dụng tia theo phương song song với trục hoành, chiều hướng về chiều dương. 

Giả sử ta có tia $P_jt$. Tia $P_jt$ sẽ cắt cạnh $A_iA_{i+1}$ nếu $P_jt$ nằm giữa hai đoạn thẳng $P_jA_i$ và $P_jA_{i+1}$. Ta chỉ cần kiểm tra xem $P_j$, $A_i$ và $A_{i+1}$ có cùng hướng (theo chiều kim đồng hồ) với thứ tự cho các điểm của đa giác không là được.

Khi chiếu tia $P_jt$, sẽ có thể xảy ra khả năng tia này đi qua một đỉnh của đa giác. Trong trường hợp này, ta có thể hình dung tia của ta bị dịch lên trên một khoảng rất nhỏ, và do vậy chỉ giao điểm của tia với cạnh nằm phía dưới (ứng với đỉnh có tung độ nhỏ hơn) được xét. 

```cpp=
PointPolygonPosition position(Polygon plg, Point p) {
    bool isIn = false;
    for (int i = 0; i < plg.nVertices; i++) {
        int i1 = (i + 1) % plg.nVertices;
        auto vpi = Vector(p, plg.vertices[i]);
        auto vpj = Vector(p, plg.vertices[i1]);
        
        // Trường hợp nằm trên cạnh
        if ((vpi ^ vpj) == 0) {
            int xl = min(plg.vertices[i].x, plg.vertices[i1].x);
            int xh = max(plg.vertices[i].x, plg.vertices[i1].x);
            int yl = min(plg.vertices[i].y, plg.vertices[i1].y);
            int yh = max(plg.vertices[i].y, plg.vertices[i1].y);
            if (p.x >= xl && p.x <= xh && p.y >= yl && p.y <= yh) {
                return BOUNDARY;
            }
        }
        
        // Trường hợp các đỉnh của đa giác ngược chiều kim đồng hồ
        // Chú ý rằng chỉ có một bên của bất đẳng thức có dấu bằng
        isIn ^= (plg.vertices[i].y <= p.y 
                 && p.y < plg.vertices[i1].y && (vpi ^ vpj) > 0);
        
        // Trường hợp các đỉnh của đa giác cùng chiều kim đồng hồ
        isIn ^= (plg.vertices[i1].y <= p.y 
                 && p.y < plg.vertices[i].y && (vpj ^ vpi) > 0);
    }
    if (isIn) {
        return INSIDE;
    }
    return OUTSIDE;
}
```

Độ phức tạp của cài đặt trên là $\mathcal{O}(n)$ về không gian và $\mathcal{O}(mn)$ về thời gian.

## Số điểm nguyên nằm trong đa giác

**Bài toán**: [CSES - Polygon Lattice Points](https://cses.fi/problemset/task/2193)
**Tóm tắt đề bài**: Cho đa giác $A_1A_2...A_n$ với các đỉnh có toạ độ nguyên cho trước. Đếm số điểm có toạ độ nguyên nằm bên trong và trên các cạnh của đa giác.

![geo1.png](/algo/geometry/p3/geo10.png)


### Đếm số điểm nguyên nằm trên cạnh của đa giác

Xét đường thẳng đi qua hai điểm $A$ và $B$. Phương trình đường thẳng trên có dạng: 
$$y = y_A + \frac{y_B-y_A}{x_B-x_A}(x-x_A)$$ 

Khi $x$ nguyên, để $y$ nguyên thì $(y_B-y_A)(x-x_A)\ \vdots\ x_B-x_A$. Để điều này xảy ra thì $x-x_A$ phải là các bội của $\frac{\text{lcm}(y_B-y_A, x_B-x_A)}{x_B-x_A}$. Có $\gcd(y_B-y_A, x_B-x_A)$ giá trị $x$ nằm giữa $0$ và $x_B - 1$ thoả mãn tính chất trên.

Như vậy, số điểm nguyên nằm trên mỗi cạnh $A_iA_{i+1}$ (chỉ tính một đầu mút) sẽ là $\gcd(y_i-y_{i+1}, x_i-x_{i+1})$. Cộng các kết quả này lại ta sẽ được số điểm nguyên trên cạnh của đa giác.

_Lưu ý_: Về mặt định nghĩa, ta vẫn có $\gcd(a, b) > 0$ với mọi $a, b$ cùng khác $0$. Tuy nhiên, khi cài đặt, kết quả của phép toán có thể là âm nếu ta dùng thuật toán Euclid hoặc hàm `__gcd()`. Do đó, để chắc chắn có một kết quả dương, ta sẽ sử dụng giá trị $\gcd(|y_i-y_{i+1}|, |x_i-x_{i+1}|)$

### Định lý Pick và số điểm nguyên nằm trong đa giác 

**Định lý Pick**: Cho một đa giác không tự cắt với các đỉnh có toạ độ nguyên và diện tích khác không. Gọi diện tích đa giác là $S$, số điểm nguyên nằm bên trong đa giác là $I$ và số điểm nguyên nằm trên cạnh đa giác là $B$. Khi đó diện tích đa giác là: 
$$S = I + \frac{B}{2}-1\tag{9}$$ 

Do độ dài của bài viết cũng như độ dài của chứng minh, tác giả sẽ không trình bày phần chứng minh trong bài viết này. Bạn đọc tham khảo chứng minh ở [đây](http://www.geometer.org/mathcircles/pick.pdf).

Trong $(9)$, ta đã tính được $B$ ở phần trên, và tính được $S$ bằng công thức tam giác $(5)$. Ngay lập tức ta suy ra được $I$.

### Cài đặt

Tác giả cũng sẽ không trình bày cài đặt cho bài toán này do độ dài của bài viết.

Độ phức tạp không gian cần cho bài toán này là $\mathcal{O}(n)$. Về thời gian, ta mất $\mathcal{O}(n)$ để tính diện tích (sử dụng các công thức đã được nói ở trên), $\mathcal{O}(n\log\max_{i\in[1, n]}(x_i, y_i))$ cho việc đếm số điểm trên cạnh, và $\mathcal{O}(1)$ để đếm số điểm trong đa giác. Tổng cộng là $\mathcal{O}(n\log\max_{i\in[1, n]}(x_i, y_i))$.

## Bài tập áp dụng

- [CSES - Polygon Area](https://cses.fi/problemset/task/2191)
- [Codeforces - Very simple problem](https://codeforces.com/contest/55/problem/E)
- [VNOJ - Growing Carrot](https://oj.vnoi.info/problem/bedao_r18_f)
- [VNOJ - Maximum Triangle Area](https://oj.vnoi.info/problem/mtriarea)
- [VNOJ - Câu chuyện người lính](https://oj.vnoi.info/problem/military)

## Tham khảo

- [CP Algorithms - Polygons](https://cp-algorithms.com/geometry/oriented-triangle-area.html)
- [USACO Guide - Geometry Primitives](https://usaco.guide/plat/geo-pri?lang=cpp)