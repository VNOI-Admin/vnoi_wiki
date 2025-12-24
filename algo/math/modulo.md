---
title: Modulo cơ bản
description: 
published: true
date: 2025-01-22T09:58:58.045Z
tags: math, number theory
editor: markdown
dateCreated: 2024-09-26T03:19:31.643Z
---

# Modulo cơ bản
**Tác giả:**
- Nguyễn Đức Kiên - Trường Đại học Công nghệ - ĐHQGHN

**Reviewer:**
- Nguyễn Minh Nhật - THPT chuyên Khoa học Tự nhiên, ĐHQGHN
- Nguyễn Minh Hiển - Trường Đại học Công nghệ - ĐHQGHN

Lớp bài toán liên quan đến số học là một lớp bài toán thường hay xuất hiện trong các kỳ thi học sinh giỏi môn Tin học. Để giải quyết hiệu quả những bài tập này, cần phải nắm vững những kiến thức toán học có liên quan. Bài viết sau đây sẽ cung cấp một số thông tin cơ bản nhất về modulo.

## Phép chia

Dưới đây là một số khái niệm cơ bản liên quan đến phép chia
- **Phép chia**: Với hai số nguyên $a$ và $b$ với $b\neq 0$, tồn tại duy nhất một số nguyên $q$ và một số tự nhiên $r$ sao cho $a = bq + r$ với $0\leq r < |b|$. Khi đó ta viết: $a : b = q$ (dư $r$) Trong phép toán trên:
    - $a$ là **số bị chia**
    - $b$ là **số chia**
    - $q$ là **thương** 
    - $r$ là **số dư**
- **Phép lấy số dư**: Nếu phép chia $a$ cho $b$ có số dư là $r$, ta có thể viết $a\bmod b = r$
- **Phép chia hết**: Nếu $r = 0$, ta có **phép chia hết**. Khi đó:
    - **$a$ chia hết cho $b$** hoặc **$a$ là bội của $b$** ($a\ \vdots\ b$) 
    - **$b$ chia hết $a$** hoặc **$b$ là ước của $a$** ($b\mid a$)
- **Ước chung lớn nhất** ($\gcd(a, b)$ hoặc $(a, b)$): Số nguyên $d$ lớn nhất thoả mãn $d\mid a$ và $d\mid b$ gọi là **ước chung lớn nhất** của $a$ và $b$. Bạn đọc có thể tham khảo bài [Thuật toán Euclid](/algo/algebra/euclid.md ) để biết thêm tính chất của ước chung lớn nhất.
- **Bội chung nhỏ nhất** ($\text{lcm}(a, b)$ hoặc $[a, b]$): Số nguyên dương $m$ nhỏ nhất thoả mãn $a\mid m$ và $b\mid m$


Trong ngôn ngữ C++, phép chia được biểu diễn bằng toán tử `/`, còn phép lấy dư được biểu diễn bởi toán tử `%`. Nếu hai toán hạng trong phép tính đều ở kiểu dữ liệu `int`, kết quả cũng sẽ là kết quả `int`, do đó `a / b` là phép lấy thương (hay phần nguyên) của phép chia `a` cho `b`, còn `a % b` là phép lấy phần dư.

## Đồng dư thức

Số học modulo hiện đại được nghiên cứu lần đầu bởi C.Gauss năm 1801. Hiện tượng đồng dư cũng thường xuất hiện trong đời sống, chẳng hạn trên chiếc đồng hồ, 15 giờ và 3 giờ cùng được biểu diễn bởi một vị trí kim giờ/phút.

Cho số nguyên $m \geq 1$. Nếu có hai số nguyên $a, b$ thoả mãn: $m \mid (a-b)$ thì ta nói $a$ và $b$ đồng dư theo modulo $m$. Ký hiệu là $a \equiv b \pmod m$. 

Nói cách khác, nếu $a \bmod m = b\bmod m$ thì $a \equiv b \pmod m$.

Trong ví dụ về đồng hồ nói trên, ta có $3 \equiv 15 \pmod{12}$.

### Các tính chất của phép đồng dư

Phép đồng dư có một số tính chất sau đây:
- $a\equiv a\pmod m$
- $a\equiv b\pmod m \Leftrightarrow m\mid(a - b)$
- $a\equiv b\pmod m \Rightarrow b\equiv a\pmod m$
- $\begin{cases}a\equiv b\pmod m\\ b \equiv c\pmod m \end{cases} \Rightarrow a\equiv c\pmod m$
- Cộng hoặc trừ theo vế các đồng dư thức cùng modullo:
$$\forall i\in\overline{1..n}, a_i\equiv b_i\pmod m\Rightarrow \sum\limits_{i = 1}^na_i \equiv \sum\limits_{i = 1}^nb_i\pmod m$$
- Cộng hoặc trừ cả hai vế của đồng dư thức với một hằng số:
$$a\equiv b\pmod m \Rightarrow a\pm c\equiv b\pm c\pmod m$$
- Nhân theo vế các đồng dư thức cùng modullo:
$$\forall i\in\overline{1..n}, a_i\equiv b_i\pmod m\Rightarrow \prod\limits_{i = 1}^na_i \equiv \prod\limits_{i = 1}^nb_i\pmod m$$
- Nhân cả hai vế của đồng dư thức với một số nguyên:
$$a\equiv b\pmod m \Rightarrow ca\equiv cb\pmod m$$
- Nếu $c$ là số nguyên dương ta còn có:
$$a\equiv b\pmod m \Rightarrow ca\equiv cb\pmod {cm}$$
- Nâng cả hai vế lên luỹ thừa với số mũ tự nhiên:
$$a\equiv b\pmod m \Rightarrow a^n\equiv b^n\pmod m$$
- Chia cả hai vế cho một số nguyên tố cùng nhau với modulo:
$$\begin{cases}a\equiv b\pmod m \\ d\mid a \\ d\mid b \\ (m, d) = 1\end{cases} \Rightarrow \frac{a}{d}\equiv \frac{b}{d}\pmod m$$
- Chia cả hai vế và modulo cho một số:
$$a\equiv b\pmod m \Rightarrow \frac{a}{d}\equiv \frac{b}{d}\pmod{\frac{m}{d}}$$
- Lấy bội chung nhỏ nhất các modulo:
$$\forall i\in\overline{1..n}, a\equiv b\pmod{m_i} \Rightarrow a\equiv b\pmod{[m_1, m_2, ..., m_n]}$$

Về mặt cài đặt, đồng dư thức không có nhiều ý nghĩa thiết thực, tuy nhiên nó có vai trò quan trọng trong việc xây dựng lời giải và là nền tảng cho các định lý tiếp sau đây.

## Các bài toán liên quan

### Phép cộng, trừ, nhân và luỹ thừa modulo M

Số dư của một phép chia tất nhiên sẽ đồng dư với số bị chia theo modulo là số chia. Vì vậy, mọi tính chất của đồng dư thức đều áp dụng được cho phép toán lấy số dư:
$$(a + b)\bmod M = (a\bmod M + b\bmod M)\bmod M$$
$$(a \times b)\bmod M = ((a\bmod M) \times (b\bmod M))\bmod M$$ 

Khi tính hiệu modulo, sẽ xảy ra tình trạng $a - b < 0$. Để khắc phục, ta cộng thêm một lần $M$ vào kết quả để chắc chắn có một số dương (tất nhiên sau đó vẫn lấy mod M):
$$(a - b)\bmod M = (a\bmod M - b\bmod M + M)\bmod M$$

Với phép luỹ thừa, ta sử dụng [luỹ thừa nhị phân](/algo/algebra/binary_exponentation.md) thông qua các phép nhân modulo để tính.

#### Tránh tràn số trong phép tính với modulo

Một vấn đề thường gặp phải khi tính toán các bài có modulo là hiện tượng tràn số. Với $M\approx 10^9$, dễ thấy khi $a, b\leq 10^9$ thì $a\times b$ có thể vượt quá giới hạn của `int`. Vấn đề này có thể được giải quyết một cách đơn giản bằng cách dùng `long long`; tuy nhiên nếu vẫn muốn sử dụng `int` để tiết kiệm bộ nhớ, ta có thể sử dụng: 
```cpp
int ans = 1ll * a * b % M
```

Ngoài ra, ta có thể ép kiểu để $a$ trở thành `long long` bằng cách dùng `(long long)a`, miễn sao phần tử đầu tiên của phép tính là một số kiểu `long long`. 

Nhìn chung, nên cố gắng thêm `% MOD` và `1ll * ` vào mọi phép tính để tránh những sai lầm đáng tiếc.

### Nghịch đảo modulo và phép chia modulo M

**Bài toán**: Tính $\frac{a}{b} \bmod M$ với $a, b, M$ là các số nguyên dương và $b\mid a$.

Khác với phép cộng, trừ và nhân, dễ thấy không thể có $a\equiv b\pmod{m}\Rightarrow \frac{a}{c}\equiv\frac{b}{c}\pmod{m})$ với mọi $a, b$ nguyên. Chẳng hạn, $16\equiv 1\pmod{5}$, nhưng đương nhiên không có $\frac{16}{2}\equiv\frac{1}{2}\pmod{5}$.

Để giải quyết bài toán này, chúng ta cần một hướng tiếp cận khác. Trong nhiều trường hợp, $M$ sẽ là một số nguyên tố, khi đó ta có thể sử dụng phép nghịch đảo modulo để tính kết quả của phép chia.

#### Tính nghịch đảo modulo với modulo nguyên tố

**Nghịch đảo modulo**: Số tự nhiên $\gamma$ được gọi là [**nghịch đảo modulo**](/algo/math/modular-inverse.md) theo modulo $m$ của một số tự nhiên $a$ nếu $a\gamma \equiv 1 \space(\text{mod } m)$. Ký hiệu là $a^{-1} \pmod m$.

Ví dụ: $3 \equiv 7^{-1} \pmod{10}$

Nghịch đảo modulo $m$ của số tự nhiên $a$ chỉ tồn tại nếu $(a, m) = 1$. 

Ta có thể dùng nghịch đảo modulo để tính kết quả của phép chia modulo như sau:
$$\frac{a}{b}\bmod M = ab^{-1}\bmod M$$

Một cách làm phổ biến để tính nghịch đảo modulo là áp dụng định lý Euler (hoặc định lý Fermat nhỏ), sẽ được trình bày ở dưới đây.

**Hàm phi Euler**: Đây là khái niệm cốt lõi của định lý Euler.

[Hàm phi Euler](/translate/he/Number-Theory-4.md) của số tự nhiên $x$, ký hiệu $\phi(x)$, là số lượng số tự nhiên nhỏ hơn hoặc bằng $x$ mà nguyên tố cùng nhau với $x$
$$\phi(x) = |\{k\in\mathbb{N}^*, k\leq x\mid (x,k)=1\}|$$
Nếu $N$ phân tích được thành thừa số nguyên tố dưới dạng $N=p_1^{\alpha_1}p_2^{\alpha_2}...p_m^{\alpha_m}$ thì ta có thể tính $\phi(N)$ như sau:
$$\phi(N) = N\prod_{i = 1}^m\left(1-\frac{1}{p_i}\right)$$

**Định lý Euler**: Nếu $a$ và $m$ là các số tự nhiên thoả mãn $(a, m) = 1$ thì ta có $a^{\phi(m)}\equiv 1\pmod{m}$

**Định lý Fermat nhỏ**: Với $p$ là số nguyên tố bất kỳ và $n$ là số tự nhiên bất kỳ thoả mãn $(n, p) = 1$, ta có $n^{p-1} \equiv 1 \pmod p$. Đây là trường hợp đặc biệt của định lý Euler đối với số nguyên tố, khi đó $\phi(p) = p-1$.

**Tính nghịch đảo modulo**: Để tính nghịch đảo modulo $x^{-1}\pmod{M}$ khi $M$ là số nguyên tố, ta áp dụng định lý Fermat nhỏ. Do $M$ là số nguyên tố, $x^{M - 1} \equiv 1\pmod{M}$. Do $(x, M) = 1$, chia cả hai vế của đồng dư thức trên cho $x$ ta được:
$$x^{-1}\equiv x^{M-2}\pmod{M}$$
Như vậy, $x^{M-2}$ là nghịch đảo modulo $M$ của $x$. Theo cách này, ta mất $\mathcal{O}(\log{M})$ thời gian để tìm một nghịch đảo modulo bằng phương pháp [luỹ thừa nhị phân](/algo/algebra/binary_exponentation.md).

```cpp=
//Luỹ thừa nhị phân
int binPow(int x, int y, int mod) {
    int ret = 0;
    for (; y; y /= 2, x = 1ll * x * x % mod) {
        if (y % 2) ret = 1ll * ret * x % mod;
    }
    return ret;
}

//Nghịch đảo modulo
int inv(int x, int mod) {
    return binPow(x, mod - 2, mod);
}

//Phép chia modulo
int divMod(int a, int b, int mod) {
    return 1ll * a * inv(b) % mod;
}
```

**Chú ý**: Kết quả của $\frac{a}{b}\bmod M$ theo công thức trên vẫn đúng nếu ta thay $b^{-1}\pmod M$ bằng $(b\bmod M)^{-1}\pmod{M}$. Do vậy, ta có thể thực hiện modulo $M$ trước khi áp dụng công thức mà không sợ ảnh hưởng đến kết quả.

#### Trường hợp modulo không nguyên tố

**Trường hợp $(b, M) = 1$**: Trong trường hợp $M$ không phải là số nguyên tố, nếu đã biết $(b, M) = 1$ ta vẫn có thể tính nghịch đảo modulo bằng cách áp dụng [thuật toán Euclid mở rộng](/algo/algebra/euclid.md#Thuật-toán-Euclid-mở-rộng) để giải phương trình Diophantus $ax + My = 1$. Nghiệm $x$ của phương trình trên chính là nghịch đảo modulo $M$ của $a$. 

**Trường hợp $(b, M) \neq 1$**: Nghịch đảo modulo chỉ tồn tại nếu $(b, M) = 1$, do vậy ta cần dùng một cách khác. Lúc này ta có thể sử dụng công thức:
$$\frac{a}{b}\bmod M = \frac{a\bmod (b\times M)}{b}$$

:::spoiler **Chứng minh**
Giả sử $a\equiv r\pmod{b\times M}$. Khi đó $(a - r)\ \vdots\ (b\times M)$, mà $a\ \vdots\ b$ nên $r\ \vdots\ b$. Chia hai vế của đồng dư thức và modulo cho $b$ ta được:
$$\frac{a}{b}\equiv\frac{r}{b}\pmod{M}$$
Nếu ta chọn $0 \leq r < b\times M$ thì $0\leq\frac{r}{b}<M$. Khi đó $r$ là số dư trong phép chia $a$ cho $b\times m$, còn $\frac{r}{b}$ là số dư trong phép chia $\frac{a}{b}$ cho $m$. Vậy:
$$\frac{a}{b}\bmod M = \frac{r}{b} = \frac{a\bmod (b\times M)}{b}$$
:::

```cpp=
//Vẫn là phép chia modulo
int divMod(int a, int b, int mod) {
    return a % (1ll * b * mod) / b;
}
```

Một số lưu ý khi sử dụng công thức trên:
- Công thức ở trên vẫn có thể áp dụng được khi $M$ là một số nguyên tố, hoặc $(b, M) = 1$. Điều kiện duy nhất cần được thoả mãn là $b\mid a$.
- Công thức này cho kết quả hoàn toàn khác nếu thay $b$ ở vế phải thành $b\bmod M$. Chẳng hạn, $(64 : 8) \bmod 5 = (64\bmod 40) : 5$ nhưng không bằng $(64\bmod 15) : 5$. Điều này có nghĩa là bạn không thể áp dụng công thức với số chia đã bị modulo mà chỉ dùng được nếu số chia vẫn được giữ như ban đầu.
- Việc áp dụng công thức này tiềm ẩn nguy cơ tràn số qua cả `long long` nếu $M$ là một số rất lớn, do xuất hiện phép nhân $b\times M$.

### Các phép toán khác modulo M

Thông thường, cứ khi nào gặp số to hơn `long long`, đề bài thường bắt chúng ta lấy kết quả $\bmod$ một số nào đó, thường là số nguyên tố.

Bạn đọc có thể tham khảo thêm các phép toán sau:
- [Giai thừa](/algo/math/factorial-modulo-prime)
- [Tổ hợp](/algo/algebra/nCk)
- [Căn bậc hai modulo](/algo/math/sqrt-mod-p)
- [Logarit rời rạc](/algo/math/discrete-log)

### Thuật toán Euclid mở rộng

Thuật toán Euclid mở rộng dùng để tìm các bộ số nguyên $x, y$ sao cho $ax + by = (a, b)$, với $a, b$ là các số nguyên. Áp dụng thuật toán này, ta có thể giải các phương trình Diophantus tuyến tính hai ẩn có dạng $ax + by = c$ (hay $ax \equiv c \pmod b$), với $a, b, c$ là các số nguyên.

Bạn đọc có thể tham khảo chi tiết về thuật toán Euclid mở rộng tại [bài viết này](/algo/algebra/euclid.md).

### Định lý thặng dư Trung Hoa (CRT)

#### Nội dung định lý

**Định lý**: Cho $2n$ số nguyên dương $a_1, a_2, ..., a_n$ và $m_1, m_2, ..., m_n$ sao cho các số $m_1, m_2, ..., m_m$ nguyên tố cùng nhau đôi một. Hệ phương trình đồng dư (hoặc thặng dư) ẩn $x$:
$$\begin{cases}x\equiv a_1\pmod{m_1}\\x\equiv a_2\pmod{m_2}\\...\\x\equiv a_n\pmod{m_n}\end{cases}$$
có họ nghiệm duy nhất  là:
$$x \equiv \sum_{i = 1}^np_ip_i^{-1}a_i\pmod{M}$$
trong đó $M = \prod\limits_{i = 1}^nm_i$, $p_i=\frac{M}{m_i}$ và $p_i^{-1}$ là nghịch đảo modulo $m_i$ của $p_i$.

:::spoiler **Chứng minh**
_Chứng minh sự tồn tại_: Do $m_1, m_2, .., m_n$ là các số đôi một nguyên tố cùng nhau nên dễ thấy $(p_i, m_i) = 1$, dẫn đến sự tồn tại của $p_i^{-1}\pmod{m_i}$. Vì $p_ip_i^{-1}\equiv 1\pmod{m_i}$ nên 
$$p_ip_i^{-1}a_i\equiv a_i\pmod{m_i}$$ 
Xét $x = \sum\limits_{i = 1}^np_ip_i^{-1}a_i$. Ta thấy với mọi $i\neq j$ thì $m_i\mid p_j$ do $p_j$ là tích của tất cả các $m_{i'}$ với ${i'}$ khác $j$. Vì vậy với mọi $i$ ta có 
$$x\equiv a_i\pmod{m_i}$$

Vậy $x$ là một nghiệm của hệ phương trình.

_Chứng minh sự duy nhất_: Giả sử phương trình có hai nghiệm là $x$ và $y$. Với mọi $i$, ta đều có $x\equiv y\equiv a_i\pmod{m_i}$. Lấy bội chung nhỏ nhất của tất cả các đồng dư thức dạng trên ta được 
$$x\equiv y\pmod{[m_1, m_2, ..., m_n]}$$ 
Do $(m_1, m_2, ..., m_n) = 1$ nên 
$$x\equiv y\pmod{\prod_{i = 1}^nm_i}$$ 
hay $x\equiv y\pmod{M}$. Nghĩa là, nghiệm theo modulo $M$ là duy nhất.
:::

Rất nhiều bài toán đố vui hay dân gian dẫn đến việc phải giải hệ phương trình đồng dư và dẫn đến định lý này, chẳng hạn có bài Hàn Tín điểm binh nổi tiếng. Còn trong lập trình thi đấu, ta không thường xuyên gặp những bài toán với yêu cầu rõ ràng như vậy. Tuy nhiên, định lý này và các kết quả trung gian sử dụng để chứng minh định lý lại là nền tảng để giải rất nhiều bài toán số học, như những bài có tag `chinese remainder theorem` trên Codeforces.

#### Giải hệ phương trình đồng dư

Định lý thặng dư Trung Hoa cho phép ta nhanh chóng giải một hệ phương trình đồng dư với các modulo đôi một nguyên tố cùng nhau. Chỉ cần tính các $p_i=\frac{M}{m_i}$ và $p_i^{-1}$, ta dễ dàng giải được hệ phương trình đồng dư.

Đôi khi, ta gặp phải các bài toán mà trong đó các modulo không nguyên tố cùng nhau với nhau. Trong trường hợp này, ta xét từng cặp phương trình một. Giả sử ta có hệ 
$$\begin{cases}x\equiv a_1\pmod{m_1}\\x\equiv a_2\pmod{m_2}\end{cases}$$ 
Từ hệ này, ta có thể đặt $x = m_1y + a_1 = m_2z + a_2$ và giải phương trình Diophantus tuyến tính sau bằng thuật toán Euclid mở rộng
$$m_1y-m_2z = a_2 - a_1$$ 
Khi đã tìm được $y$ và $z$, ta tính $x^* = m_1y + a_1$ hoặc $m_2z + a_2$. Nghiệm của hệ sẽ là 
$$x\equiv x^*\pmod{[m_1, m_2]}$$

## Bài tập áp dụng

Bài rất dễ vận dụng phép chia và đồng dư cơ bản: 
- [VNOJ - Đếm đi các bạn ơiiii](https://oj.vnoi.info/problem/bedao_m22_b)
- [VNOJ - Phi hàm Euler](https://oj.vnoi.info/problem/etf)
- [Codeforces - Competitive Programmer](https://codeforces.com/problemset/problem/1266/A)

Bài cần suy luận nhiều hơn bằng các định lý và kết quả đồng dư:
- [VNOJ - Số nguyên](https://oj.vnoi.info/problem/integer7)
- [Hackerank - Number of Sequences](https://www.hackerrank.com/contests/w22/challenges/number-of-sequences)
- [Codeforces - Remainders Game](https://codeforces.com/problemset/problem/687/B)
- [Codeforces - Congruence Equations](https://codeforces.com/problemset/problem/919/E)
- [Codeforces - Two Chandeliers](https://codeforces.com/problemset/problem/1500/B)
- [VNOJ - Tổ hợp chẵn](https://oj.vnoi.info/problem/bedao_oi4_b)
- [VNOJ - Hình vuông](https://oj.vnoi.info/problem/squares)

## Nguồn tham khảo

- [Diễn đàn toán học](https://diendantoanhoc.org/)
- Các bài dịch cũ trên VNOI Wiki ([Modulo & gcd](/translate/he/So-hoc-Phan-1-Modulo-gcd.md), [Phi hàm Euler](/translate/he/Number-Theory-4.md))
- Wikipedia (lịch sử các thuật toán)
- CP-Algorithms