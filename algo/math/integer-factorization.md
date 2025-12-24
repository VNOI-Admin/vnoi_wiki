---
title: Phân tích thừa số nguyên tố
description: 
published: true
date: 2024-12-10T04:21:10.984Z
tags: 
editor: markdown
dateCreated: 2024-09-29T08:06:13.356Z
---

# Phân tích thừa số nguyên tố

**Người viết:**

* Nguyễn Minh Hiển - Trường Đại học Công nghệ, ĐHQGHN

**Reviewer:**
* Lê Minh Hoàng - Trường Đại học Khoa học Tự nhiên - ĐHQG TP.HCM
* Nguyễn Minh Nhật - THPT chuyên Khoa học Tự nhiên, ĐHQGHN
* Võ Đức Đoàn - THPT Chuyên Nguyễn Tất Thành - Kon Tum

## Bài toán

Phân tích thừa số nguyên tố là một bài toán cơ bản với mục tiêu là phân tích một số nguyên dương thành tích của các thừa số nguyên tố.

Cụ thể, cho một số nguyên dương $n$ (với $n > 1$), ta cần tìm một dãy các số nguyên tố $p_1, p_2, \dots, p_k$ sao cho $n = p_1^{e_1} \times p_2^{e_2} \times \dots \times p_k^{e_k}$, trong đó:
  - $p_i$ là các số nguyên tố và đôi một phân biệt.
  - Mỗi $e_i$ là số mũ nguyên dương của $p_i$ trong phân tích thừa số của $n$,
  - Các số nguyên tố $p_1, p_2, \dots, p_k$ nên được sắp xếp theo thứ tự tăng dần.

Ví dụ: với $n = 60$, ta cần phân tích $60 = 2^2 \times 3^1 \times 5^1$


## Thuật toán ngây thơ
**Nhận xét**: Một số nguyên dương $n$ chỉ có tối đa một ước nguyên tố lớn hơn $\sqrt{n}$.

<details>
<summary><b>Chứng minh</b></summary>
    
Giả sử $n$ có hai ước nguyên tố lớn hơn $\sqrt{n}$, gọi là $p_1$ và $p_2$.
- Vì $p_1$ và $p_2$ đều là ước nguyên tố của $n$, nên $n$ phải chia hết cho $p_1$ và $p_2$. Điều này có nghĩa là: $n \geq p_1 \times p_2$
- Theo giả thiết, $p_1 > \sqrt{n}$ và $p_2 > \sqrt{n}$. Tích của hai số này là: $p_1 \times p_2 > \sqrt{n} \times \sqrt{n} = n$
- Như vậy sẽ dẫn đến mâu thuẫn $n \geq p_1 \times p_2 > n$
</details>


Do đó, ta chỉ cần duyệt tìm các ước nguyên tố $p$ của $n$ trong $\left[2;\sqrt n\right]$ và chia dần dần $n$ cho các ước số này *(Nếu $n \;\vdots\; d$ thì ta chỉ cần phân tích $\frac{n}{d}$)*. Sau khi duyệt xong, số còn lại sẽ là $1$ hoặc một số nguyên tố.

Trên thực tế, để đơn giản hóa mã nguồn khi triển khai thuật toán, ta sẽ duyệt qua tất cả các số nguyên từ 2 đến phần nguyên của căn bậc hai của $n$, bao gồm cả các số hợp.

> **Tại sao lại như vậy?**
Giả sử tại một thời điểm, ta duyệt đến một số hợp $d$ có dạng $d = p_1 \times p_2 \times ... \times p_k$, trong đó $p_i$ là các thừa số nguyên tố. Khi $n$ chia hết cho $d$, điều này có nghĩa là $n$ cũng đã chia hết cho một trong các thừa số nguyên tố $p_i$. Các thừa số này sẽ được xử lý bằng phép chia `n /= d` trong quá trình duyệt các số nhỏ hơn $d$.

Thuật toán này cho ta phân tích thừa số nguyên tố trong $\mathcal{O}\left(\sqrt n\right)$.

```cpp=
vector<long long> trial_division1(long long n) {

    vector<long long> factorization;
    for (long long d = 2; d * d <= n; d++) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;

}

```

## Bánh xe phân tích - Wheel Factorization

Bánh xe phân tích là một cải tiến cho thuật toán cơ bản ở trên.

Xem xét tối ưu sau: 
> Nếu $n$ lẻ thì chúng ta không cần duyệt các số chẵn trong $\left[2, \sqrt n\right]$. 

Điều này sẽ giảm được $50\%$ số lượng số cần kiểm tra.
Về cài đặt, sau khi kiểm tra $2$, chúng ta duyệt từ $3$ và bỏ qua các số chẵn.

```cpp=
vector<long long> trial_division2(long long n) {
    vector<long long> factorization;
    while (n % 2 == 0) {
        factorization.push_back(2);
        n /= 2;
    }
    for (long long d = 3; d * d <= n; d += 2) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
```

Tương tự, nếu $3$ không phải là ước của $n$, ta có thể loại bỏ tất cả các số chia hết cho $3$ khỏi danh sách xét duyệt. Khi kết hợp với giả thiết rằng $n$ là số lẻ, ta chỉ cần xét những số $d \equiv 1, 5 \pmod{6}$, từ đó giảm số lượng trường hợp cần kiểm tra xuống còn $33.3%$.

Ta hoàn toàn có thể mở rộng thêm với nhiều số nguyên tố hơn để tối ưu hóa hơn nữa việc tìm kiếm các ước số nguyên tố.

Để thuận tiện cho việc cài đặt, ta định nghĩa mảng $\text{increments}$ để nhảy đến số "nghi ngờ là số nguyên tố" tiếp theo.

**Ví dụ:** Xét các modulo $2$, $3$, $5$. Bỏ qua $1,2 ,3 ,5$, các số nguyên $d$ cần duyệt phải thỏa mãn:

<center>
  
![wheelfactorizationgrid.gif](/algo/math/wheelfactorizationgrid.gif)

$d \bmod 30 \in \{1, 7, 11, 13, 17, 19, 23, 29\}$
hay $d = 7, 11, 13, 17, 19, 23, 29,\quad 31, 37, 41, ...$
</center>

Như vậy, ta có thể thiết lập các khoảng cách để nhảy đến các số cần duyệt tiếp theo là:
<center>

$\{11-7,\quad 13-11,\quad 17-13,\quad 19-23,\quad 29-23,\quad 31-29,\quad 37 - 31\}$
hay $\{4, 2, 4, 2, 4, 6, 2, 6\}$
</center>

Dưới đây là cài đặt cho ví dụ trên.

```cpp=
vector<long long> trial_division3(long long n) {

    vector<long long> factorization;
    for (int d : {2, 3, 5}) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    
    const int increments[] = {4, 2, 4, 2, 4, 6, 2, 6};
    
    int i = 0;
    for (long long d = 7; d * d <= n; d += increments[i++]) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
        if (i == 8)
            i = 0;
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
```

Mở rộng cho càng nhiều số nguyên tố thì thuật toán càng tốt hơn. Tuy nhiên mảng $\text{increments}$ sẽ càng dài hơn trong khi tỷ lệ phần tử cần xét so với ban đầu cũng không giảm nhiều:
![prime_wheel.png](/algo/math/prime_wheel.png)

Thuật toán này cũng đã được đề cập đến trong bài viết về [Sàng nguyên tố - VNOI](/algo/algebra/prime_sieve.md#b%C3%A1nh-xe-ph%C3%A2n-t%C3%ADch-wheel-factorization). 

## Sử dụng sàng nguyên tố

Sử dụng [Sàng nguyên tố](/algo/algebra/prime_sieve.md), ta chỉ cần duyệt các số nguyên tố trong $\left[2, \sqrt n\right]$. Từ đó, độ phức tạp cho việc phân tích mỗi lần giảm chỉ còn $\mathcal{O}\left(\frac{\sqrt n}{\log \sqrt n}\right)$(do số lượng số nguyên tố nhỏ hơn $n$ xấp xỉ $\frac{n}{\log n}$ - theo [Định lý số nguyên tố](https://vi.wikipedia.org/wiki/%C4%90%E1%BB%8Bnh_l%C3%BD_s%E1%BB%91_nguy%C3%AAn_t%E1%BB%91)). Tuy nhiên, ta sẽ tốn thêm bộ nhớ lưu mảng $\text{primes[]}$ và độ phức tạp thời gian của cài đặt sẽ cần tính thêm thời gian chuẩn bị sàng.

```cpp=
vector<long long> primes;

vector<pair<unsigned long long, int>> trial_division4(unsigned long long n){
  vector<pair<unsigned long long, int>> result;
  for (auto p: primes) {
    if (p * p > n) break;
    if (n % p) continue;

    int cnt = 0;
    while (n % p == 0) {
      cnt++;
      n /= p;
    }
    result.emplace_back(p, n);
  }
  return result;
}
```

## Thuật toán Pollard's Rho

> Thuật toán Pollard's Rho sẽ giúp ta tìm một ước khác một của $N$ với độ phức tạp thời gian trung bình $\mathcal{O}\left(\sqrt[4] N\log N\right)$.
> Do số nhân tử của $N$ tối đa là $O(\log N)$, toàn bộ thuật toán phân tích $N$ bằng thuật Pollard's Rho có độ phức tạp trung bình là là $\mathcal{O} \left( \sqrt[4] N \log^2 N \right)$. Do thuật toán sử dụng yếu tố ngẫu nhiên, cài đặt sử dụng Pollard's Rho sẽ không có độ phức tạp chính xác.
> Thuật toán có độ phức tạp không gian $\mathcal{O}(\log N)$ (Chỉ tốn duy nhất 1 mảng lưu kết quả).

### Ý tưởng lớn

* **Nếu $N$ là số nguyên tố** thì ta không cần phân tích nữa. (Có thể kiểm tra bằng [thuật toán Miller-Rabin](/algo/algebra/primality_check.md#3-thu%E1%BA%ADt-to%C3%A1n-rabin-miller) với độ phức tạp $\mathcal{O}(\log^2 N)$).
* **Nếu $N$ không là số nguyên tố.**
  Ta sẽ sinh một dãy $\{x_i\}$ và tìm hai chỉ số $s, t$ sao cho:
    $$p = \gcd(|x_s - x_t|, N) > 1$$
    Như vậy, ta tìm được $p$ là một ước của $N$.
    Nếu $p = N$ thì chúng ta cần lặp lại thuật toán với một dãy $\{x_i\}$ khác.
    Tiếp tục tách $p$ và $\frac{N}{p}$ theo cách trên đến khi tách được hết các ước nguyên tố.
    
    <details> <summary><b>Liệu có chắc chắn tồn tại s, t không?</b> </summary>
    
    Giả sử $p$ là một ước khác $1$ của $N$. Theo [nguyên lý Dirichlet](https://vi.wikipedia.org/wiki/Nguy%C3%AAn_l%C3%BD_ng%C4%83n_k%C3%A9o_Dirichlet), cho một dãy số $x$ có ít nhất $p+1$ phần tử, ta chắc chắn tìm được hai chỉ số $s, t$ thỏa $x_s \equiv x_t \pmod p$ hay $p=\gcd(|x_s - x_t|, N) > 1$.
    Ta cũng quy ước $\gcd(0, N)=N$.
    </details>

Đến đây, chúng ta có ba vấn đề cần giải quyết:

&emsp;$1.$ Dãy $\{x_i\}$ cần ít nhất bao nhiêu phần tử để tồn tại hai chỉ số $s, t$ ?
&emsp;&emsp;*Nghịch lý ngày sinh nhật*
&emsp;$2.$ Làm sao để sinh dãy $\{x_i\}$ hiệu quả ?
&emsp;&emsp;*Đề xuất của Pollard*
&emsp;$3.$ Làm sao để tìm được $s, t$ nếu đã có dãy $\{x_i\}$ ?
&emsp;&emsp;*Thuật toán phát hiện chu trình*


Chúng ta sẽ giải quyết lần lượt ba vấn đề trên.

### 1. Nghịch lý ngày sinh nhật

Theo [_Nghịch lý ngày sinh nhật (Birthday paradox)_](https://en.wikipedia.org/wiki/Birthday_problem#Approximations):

> Trong một tập $k$ số nguyên chọn ra từ $[0; p)$ với $k \ll p$, thì xác suất tồn tại hai số bằng nhau xấp xỉ $1-e^{-\frac{k^2}{2p}}$.

$\implies$ Nếu chọn dãy $x$ khoảng $4\sqrt{p}$ phần tử thì từ dãy $\{x_i \bmod p\}$ sẽ lấy được hai số bằng nhau với xác suất $99.97\%$.

Giả sử ta đang cố gắng tìm một ước $p$ của $N$ thỏa mãn $p<\sqrt{N}$, thì số phần tử cần lấy xấp xỉ $\mathcal{O}(\sqrt[4]{N})$.

Như vậy, tiếp theo ta sẽ đến với cách để sinh ngẫu nhiên một dãy để lấy được khoảng $\mathcal{O}(\sqrt[4]{N})$ phần tử này.

### 2. Đề xuất của Pollard
Pollard đã đề xuất sử dụng một hàm giả ngẫu nhiên $f$ để sinh dãy $\{x_i\}$. 

Định nghĩa hàm $f(x)$ là
$$f(x)=\left(x^2 + c \right) \bmod N \quad{\text{với}} \quad c \ge 1$$

Ta sinh dãy $x_i$ như sau:
<center>

$x_0$ bất kỳ
$x_i = f(x_{i-1})$
</center>

**Nhận xét:** Với một số nguyên $m$ bất kỳ, theo nguyên lý Dirichlet, luôn tồn tại $s, t$ sao cho $x_s \equiv x_t \pmod m$.

Khi đã tìm được $s, t$, có 2 trường hợp xảy ra:
- **TH1:** $1 < \gcd(|x_s - x_t|, N) < N$ thì ta đã tìm được một ước của $N$. Chia liên tục $N$ cho ước này rồi sau đó, lặp lại thuật toán để tìm ước khác.
- **TH2:** $\gcd(|x_s - x_t|, N) = N$ thì ta sẽ lặp lại thuật toán với $x_0$ khác và/hoặc $c$ khác.
Để tránh gặp phải trường hợp **TH2** quá nhiều, ta có thể xét trước các ước nguyên tố nhỏ như $2, 3, 5, 7, 11, 13, 17, 19$ do các modulo nhỏ như vậy có xác suất cao gặp phải **TH2**.

Dưới đây là minh họa cho dãy $\{x_i \bmod p\}$ với $N = 2206637$, $p = 317$, $x_0 = 2$ và $f(x) = x^2 + 1$. Đây cũng chính là lý do Pollard đặt tên cho Thuật toán $\rho$ của ông (Pollard's $\rho$ algorithm, theo [Wikipedia](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm)).

<center>

![pollardrho.png](/algo/math/pollardrho.png)

</center>

### 3. Thuật toán phát hiện chu trình
Qua hình minh họa trên, ta thấy rõ ràng rằng dãy $\{x_i \bmod p\}$ là tuần hoàn.

<details><summary>Chứng minh</summary>

Khi đó $f(x_s) \equiv f(x_t) \pmod m$ hay $x_{s+1} \equiv x_{t+1} \pmod m$.
Bằng phương pháp quy nạp, dễ thấy rằng dãy $(x_n \bmod m)$ sẽ tuần hoàn theo chu kỳ $s-t$.
</details>

Do đó, việc tìm hai số $x_s$ và $x_t$ cũng chính là xác định một chu kỳ của dãy số $\{x_i \bmod p\}$.

Cũng từ hình minh họa, ta có thể coi $(x_i \bmod p)$ là một đỉnh của đồ thị và có cạnh có hướng đến đỉnh $(x_{i+1} \bmod p)$. Từ đó, bài toán được đưa về tìm chu trình của đồ thị này.

Xét $\lambda$ là độ dài chu trình và $\mu$ là vị trí đầu tiên xuất hiện chu trình.
Dưới đây là hai thuật toán có Độ phức tạp thời gian $\mathcal{O}(\lambda+\mu)$ và không gian $\mathcal{O}(1)$.

#### **3.1. Thuật toán rùa và thỏ (Thuật toán Floyd)**

Thuật toán này rất đơn giản: Sử dụng hai con trỏ "Rùa" và "Thỏ". Mỗi lần "Rùa" sẽ nhảy $1$ bước, "Thỏ" sẽ nhảy $2$ bước.
Nếu "Thỏ" gặp "Rùa" thì đường chúng đã đi có chu trình. Nếu không tồn tại chu trình, "Thỏ" sẽ đến hết điểm hết đồ thị trước "Rùa".

<details><summary>Chứng minh thuật toán trên khả thi</summary>

- Nếu đồ thị không có chu trình, rõ ràng Thỏ luôn đi nhanh hơn Rùa và không bao giờ gặp được Rùa.
- Nếu đồ thị có chu trình độ dài $\lambda$, xét tại một thời điểm mà Thỏ ở trước Rùa $k$ bước trong chu trình. 
Giả sử $k \ge 1$. Gọi vị trí của Rùa là $x$, suy ra Thỏ ở vị trí $x+k$. Sau khoảng thời gian $\lambda-k$, Rùa sẽ ở vị trí $x+\lambda-k$, còn Thỏ ở vị trí $x+k+2(\lambda-k) = x+2\lambda-k$. Do đồ thị có chu trình dài $\lambda$ bước nên Rùa và Thỏ đang ở cùng vị trí (đpcm).
</details>


##### Mã giả tìm chu trình:

```cpp
int Floyd(int x0){
    int tortoise = f(x0);
    int hare = f(f(x0));
    while (tortoise != hare){
        tortoise = f(tortoise);
        hare = f(f(hare));
    }
    return hare;
}
```

ĐPT của _Thuật toán Floyd_ là $\mathcal{O} \left( \sqrt[4] N \log N \right)$ do sử dụng $\gcd(x, N)$ sau mỗi bước nhảy của Rùa và Thỏ.

<details>
<summary> <strong>Code C++ minh họa:</strong> </summary>
    

```cpp=
long long mult(long long a, long long b, long long mod) {
    return (__int128_t)a * b % mod;
}

long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod; 
}

long long rho(long long n, long long x0 = 2, long long c = 1) {
    long long tortoise = x0; 
    long long hare = x0; 
    long long g = 1; 
    while (g == 1) {
        tortoise = f(tortoise, c, n); 
        hare = f(hare, c, n); 
        hare = f(hare, c, n); 
        g = gcd(abs(tortoise - hare), n); 
    }
    return g; 
}
```
Chú ý rằng, không phải kỳ thi nào cũng có thể sử dụng `__int128_t` (do máy chấm) nên có thể sử dụng hàm mult thay thế sau ([nhân Ấn Độ](/algo/algebra/binary_exponentation.md#nh%C3%A2n-l%E1%BA%A5y-d%C6%B0) với độ phức tạp $O(\log b)$):
```cpp=
long long mult(long long a, long long b, long long mod){
    if (!b) return 0;
    long long x = mult(a, b / 2);
    if (b % 2 == 0) 
        return 2 * x % mod;
    else 
        return (2 * x + a) % mod;
}
```
</details>

<center>

Minh họa cho $N = 2206637$, $x_0 = 2$ và $f(x) = (x^2 + 1) \bmod N$:

  ![floyd.gif](/algo/math/floyd.gif)

</center>

Bảng minh họa cho **Thuật toán Floyd** trong trường hợp trên:
<center>
  
| Step  | Rua     | Tho      | $\gcd(\mid Tho-Rua\mid, N)$ |
|------|-----------|------------|:------------------:|
| $0$  | $2$       | $2$        | -                  |
| $1$  | $5$       | $26$       | $1$                |
| $2$  | $26$      | $458330$   | $1$                |
| $3$  | $677$     | $1671573$  | $1$                |
| $4$  | $458330$  | $641379$   | $1$                |
| $5$  | $1166412$ | $351937$   | $1$                |
| $6$  | $1671573$ | $1264682$  | $1$                |
| $7$  | $2193080$ | $2088470$  | $317$              |

</center>

Như vậy, sau Step 7, ta kết luận được $317$ là một ước của $N$
  
#### **3.2. Thuật toán Brent**

Năm $1980$, Brent đã cải tiến **Thuật toán Rho** tìm ước bằng cách sử dụng một cách tìm chu trình khác (tạm gọi là [**Thuật toán Brent**](https://en.wikipedia.org/wiki/Cycle_detection#Brent's_algorithm)).

Gọi $\lambda$ là độ dài chu trình và $\mu$ là vị trí đầu tiên xuất hiện chu trình. Vẫn ý tưởng sử dụng hai con trỏ, nhưng ta sẽ tìm $\text{power} = 2^k$ nhỏ nhất mà lớn hơn cả $\lambda$ và $\mu$.
Sau đó, ta sẽ tìm $x_s, x_t$ bằng cách cho $s=\text{power}$ và tìm vị trí $t$ sao cho $x_s=x_t$.


<center>

Minh họa cho $N = 2206637$, $x_0 = 2$ và $f(x) = (x^2 + 1) \bmod N$:

  ![brent.gif](/algo/math/brent.gif)
</center>

**Mô tả:**

Duyệt $i$ từ $1$:
- Cho Rùa chạy đến $x_{2^i-1}$
- Cho Thỏ chạy từ $x_{2^i}$ đến $x_{2^{i+1}-1}$ xem có tồn tại giá trị bằng Rùa không. Nếu tồn tại thì kết thúc thuật toán.

**Mã giả tìm chu trình:**
```cpp
int f(int x, int c = 1){
    return x * x + c;
}

int Brent(int x0){
    int tortoise = x0;
    int hare = f(x0);
    int power = 1;
    while (tortoise != hare){
        tortoise = hare;
        for (int i = 1; i <= power; ++i){
            hare = f(hare);
            if (tortoise == hare){
                break;
            }
        }
        power *= 2;
    }
    return hare;
}
```

Để tăng tốc thuật toán, chúng ta có các nhận xét:
- Không cần xét các vị trí $s < t < \frac{3s}{2}$
$\implies$ *Loại được khoảng 50\% số trường hợp*
<details><summary>Chứng minh</summary>

<!-- Xét đến vòng duyệt $i$ hiện tại, có hai nguyên nhân chưa tìm được chu trình ở vòng duyệt trước:
- **TH1:** Ở vòng duyệt trước, Rùa ở vị trí chưa bắt đầu chu trình hay $\mu > \text{power}$. Khi này ta chỉ cần tăng $\text{power}$ lên là có thể tìm được chu trình. Giả sử việc bỏ qua $s < t < \frac{3s}{2}$ vô tình làm bỏ qua $t=s+\lambda$ thì suy ra $\lambda < \frac{s}{2}$ và suy ra $s+2\lambda < 2s$... Cứ tiếp tục làm như vậy ta có thể chắc chắn rằng tồn tại $\alpha$ để $\frac{3s}{2} \le s+2^\alpha \cdot \lambda < 2s$ và ta tìm được đây là vị trí của thỏ.
- **TH2:** Ở vòng lặp trước ta không tìm được chu trình nào có độ dài $\le \text{power_prev} = 2^{i-1}$ nên phải tìm một chu kỳ có độ dài lớn hơn $\text{power_prev} = \frac{\text{power_now}}{2} = \frac{s}{2}$. Mà ở vòng lặp hiện tại, ta đã cố định $s = 2^i-1$, và cho $t$ chạy từ $s+1$ đến $2s+1$ nên ta bỏ qua $s < t < \frac{3s}{2}$.  -->
Khi duyệt đến $\text{power}=2^i > \max\{\mu, \lambda\}$, cho Rùa đứng ở vị trí $s=2^i-1$. Xét việc bỏ qua các giá trị $t$ mà $s < t < \frac{3s}{2}$.
- Nếu $t=s+\lambda$ không bị bỏ qua, ta có đpcm.
- Nếu $t=s+\lambda$ bị bỏ qua thì suy ra $\lambda < \frac{s}{2}$ và suy ra $2\lambda < s$. Nếu $2\lambda < \frac{s}{2}$ thì $4\lambda < s$... Cứ tiếp tục làm như vậy $\alpha$ nào đó để $2^\alpha \cdot \lambda > \frac{s}{2}$ và $2^{\alpha-1} \cdot \lambda < \frac{s}{2}$ thì chốt lại ta có $\frac{s}{2} < 2^\alpha \cdot \lambda < s$. Như vậy khi duyệt đến $t=s+2^\alpha \cdot \lambda$ $\frac{3s}{2} \le t < 2s$, ta chắc chắn tìm được vị trí của thỏ (đpcm).
</details>

- Nếu $g = \gcd(u_{t+1} \cdot u_{t+2} \cdots, N) > 1$ thì chắc chắn một trong các số $u_{t+1}, u_{t+2}, \;\ldots$ sẽ thỏa mãn $\gcd(u_j, N) > 1$ (dễ dàng chứng minh bằng phản chứng). 
    - Để so sánh, trong thuật toán gốc, ta gọi $\gcd(u, N)$ theo mỗi bước Thỏ chạy, tức là vào khoảng $2 \cdot \max (\lambda, \mu) \sim 2\sqrt[4] N$ lần. Xét hai trường hợp sau:
        - Nếu $g \neq N$ thì $g$ chính là một ước cần tìm của $N$.
        $\implies$ *Cả thuật toán gọi $\gcd(u, N)$ khoảng $\log (\lambda+ \mu) \sim \frac{1}{4}\log N$ lần*.
        - Nếu $g = N$, ta cần một lần duyệt $\lambda$ bước để tìm vị trí Thỏ gặp Rùa và tính $\gcd(|x_s-x_t|,N)$ mỗi bước.
        $\implies$ *Cả thuật toán gọi $\gcd(u, N)$ khoảng $\lambda + \log (\lambda+ \mu) \sim \sqrt[4]N$* lần.
    - **Chú ý:** Để tích $u_{t+1} \cdot u_{t+2} \cdots$ không quá to, ta sử dụng $\gcd(A, B) = \gcd(A \bmod B, B)$

Độ phức tạp thời gian của **Thuật toán Brent** vẫn là $O \left( \sqrt[4] N \log N\right)$.
Tuy nhiên, **Thuật toán Brent** lại có số lần sử dụng $f(x)$ ít hơn **Thuật toán Floyd** rất nhiều nên đã tăng tốc thuật toán tìm chu trình khoảng $36\%$ và thuật toán phân tích số nguyên khoảng $24\%$ - [theo Brent](https://maths-people.anu.edu.au/~brent/pd/rpb051i.pdf).

<details>
<summary> <strong>Code C++ minh họa</strong></summary>
    

```cpp=
// CP- Algorithms
long long brent(long long n, long long x0 = 2, long long c = 1) {

    long long tortoise = x0;
    long long g = 1;
    long long q = 1;
    long long hare, xs;

    int m = 128;
    int l = 1;
    while (g == 1) {
        hare = tortoise;
        for (int i = 1; i < l; i++)
            tortoise = f(tortoise, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = tortoise;
            for (int i = 0; i < m && i < l - k; i++) {
                tortoise = f(tortoise, c, n);
                q = mult(q, abs(hare - tortoise), n);
            }
            g = gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = gcd(abs(xs - hare), n);
        } while (g == 1);
    }
    return g;

}

`

```
</details>

Bảng dưới đây là minh họa cho thuật toán Brent với $N = 143$, $x_0 = 2$ và $c = 1$.
<small>

Dãy số: $2, 5, 26, 105, 15, 83, 26, 105, \ldots$ Ở bước $\text{i}=2$, ta không xét $15$ do $s < t < \frac{3s}{2}$</small>
<center>
  
| $i$  | $s=2^i-1$ | $x_{s} \mod N$ | $x_{2^i} \rightarrow x_{2^{i+1}-1} \mod N$  | $\mid x_{t} - x_{s}\mid$  | $\gcd(\mid x_t - x_{s}\mid, N)$ |
|----|---------|-----------------|-----------------------------------------------|---------------------|---------------------------|
| $0$  | $0$       | $2$           | $5$                                             | $3$                   | -                         |
| $1$  | $1$       | $5$           | $26$ , $105$                                      | $21, 100$             | $1$                         |
| $2$  | $3$       | $105$         | ~~15~~, $\underline{83}, 26, 105$        | $\underline{22}, 79, 0$ | $11$              |

</center>
  
### Code C++ phân tích thừa số nguyên tố tham khảo

Dưới đây là code được tham khảo từ [RR Code](https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Math/NumberTheory/Pollard_factorize.h). Code đã xét trước các nhân tử $2, 3, 5, 7, 11, 13, 17, 19$ trước khi sử dụng **Thuật toán Pollard's Rho** với **cải tiến của Brent**.
Như đã nói ở trên, dưới đây là ước lượng độ phức tạp của thuật toán:
- Thời gian trung bình: $O\left(\sqrt[4]N \log^2 N\right)$.
- Không gian: $O(\log N)$ (để lưu kết quả phân tích).

Code đã vượt qua $100$ test với $N \le 10^{18}$ trong khoảng $100\text{ms}$ tại [Library Checker - Factorize](https://judge.yosupo.jp/problem/factorize).

**Code C++ minh họa**

```cpp!
#include <bits/stdc++.h>
using namespace std;
// Copied from
// https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Math/NumberTheory/Pollard_factorize.h
using ll = long long;
using ull = unsigned long long;
using ld = long double;
// Dưới đây là hàm mult nhanh gấp đôi sử dụng __int128_t
/* License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$.
 * Time: O(1) for \texttt{modmul}, O(\log b) for \texttt{modpow}
 * Status: stress-tested, proven correct
 * Details:
 * This runs ~2x faster than the naive (__int128_t)a * b % M.
 * A proof of correctness is in doc/modmul-proof.tex. An earlier version of the proof,
 * from when the code used a * b / (long double)M, is in doc/modmul-proof.md.
 * The proof assumes that long doubles are implemented as x87 80-bit floats; if they
 * are 64-bit, as on e.g. MSVC, the implementation is only valid for
 * $0 \le a, b \le c < 2^{52} \approx 4.5 \cdot 10^{15}$.
 */
ll mult(ll x, ll y, ll md) {
    ull q = (ld)x * y / md;
    ll res = ((ull)x * y - q * md);
    if (res >= md) res -= md;
    if (res < 0) res += md;
    return res;
}

// Hàm tính lũy thừa nhanh
ll powMod(ll x, ll p, ll md) {
    if (p == 0) return 1;
    if (p & 1) return mult(x, powMod(x, p - 1, md), md);
    return powMod(mult(x, x, md), p / 2, md);
}

// Thuật toán Rabin Miller hỗ trợ kiểm tra các số nguyên tố lớn
bool checkMillerRabin(ll x, ll md, ll s, int k) {
    x = powMod(x, s, md);
    if (x == 1) return true;
    while (k--) {
        if (x == md - 1) return true;
        x = mult(x, x, md);
        if (x == 1) return false;
    }
    return false;
}

// Hàm kiểm tra nhanh một số có nguyên tố hay không
bool isPrime(ll x) {
    if (x == 2 || x == 3 || x == 5 || x == 7) return true;
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    if (x < 121) return x > 1;
    ll s = x - 1;
    int k = 0;
    while (s % 2 == 0) {
        s >>= 1;
        k++;
    }
    if (x < 1LL << 32) {
        for (ll z : {2, 7, 61}) {
            if (!checkMillerRabin(z, x, s, k)) return false;
        }
    } else {
        for (ll z : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if (!checkMillerRabin(z, x, s, k)) return false;
        }
    }
    return true;
}

ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long get_rand(long long r) {
    return uniform_int_distribution<long long>(0, r - 1)(rng);
}

void pollard(ll x, vector<ll> &ans) {
    if (isPrime(x)) {
        ans.push_back(x);
        return;
    }
    ll c = 1;
    while (true) {
        // Định nghĩa hàm f sử dụng cú pháp lambda function
        c = 1 + get_rand(x - 1);
        auto f = [&](ll y) {
            ll res = mult(y, y, x) + c;
            if (res >= x) res -= x;
            return res;
        };
        ll y = 2;
        int B = 100;
        int len = 1;
        ll g = 1;
        // Sử dụng thuật cải tiến của Brent ở đây
        while (g == 1) {
            ll z = y;
            for (int i = 0; i < len; i++) {
                z = f(z);
            }
            ll zs = -1;
            int lft = len;
            while (g == 1 && lft > 0) {
                zs = z;
                ll p = 1;
                for (int i = 0; i < B && i < lft; i++) {
                    p = mult(p, abs(z - y), x);
                    z = f(z);
                }
                g = gcd(p, x);
                lft -= B;
            }
            if (g == 1) {
                y = z;
                len <<= 1;
                continue;
            }
            if (g == x) {
                g = 1;
                z = zs;
                while (g == 1) {
                    g = gcd(abs(z - y), x);
                    z = f(z);
                }
            }
            if (g == x) break;
            assert(g != 1);
            // Thay vì kết thúc như thuật toán Brent,
            // tiếp tục phân tích hai phần g và x / g
            pollard(g, ans);
            pollard(x / g, ans);
            return;
        }
    }
}

// return list of all prime factors of x (can have duplicates)
vector<ll> factorize(ll x) {
    vector<ll> ans;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19}) {
        while (x % p == 0) {
            x /= p;
            ans.push_back(p);
        }
    }
    if (x != 1) {
        pollard(x, ans);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// return pairs of (p, k) where x = product(p^k)
vector<pair<ll, int>> factorize_pk(ll x) {
    auto ps = factorize(x);
    ll last = -1, cnt = 0;
    vector<pair<ll, int>> res;
    for (auto p : ps) {
        if (p == last)
            ++cnt;
        else {
            if (last > 0) res.emplace_back(last, cnt);
            last = p;
            cnt = 1;
        }
    }
    if (cnt > 0) {
        res.emplace_back(last, cnt);
    }
    return res;
}
````

## Các thuật toán khác

Phân tích thừa số nguyên tố là một bài toán quan trọng trong khoa học máy tính và đã có rất nhiều thuật toán cải tiến cho bài toán này.
Trong từng trường hợp, các thuật toán phân tích nhân tử (*PTNT*) có thể kể đến như sau:
Dưới đây là bảng đã tách riêng cột ĐPT:

|         Bộ dữ liệu (N)         |<center> Thuật toán </center>                                                                                                                                                                                                                                                                                                                                                                               | <center>Độ phức tạp</center>                                                                                                                                                                           |
|:------------------------------:|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|    $1 \rightarrow 10^{12}$     | <p>PTNT sử dụng các [sàng nguyên tố](/algo/algebra/prime_sieve.md).                                                                                                                                                                                                                                                                                                   | $\mathcal{O}(\log N)$ hoặc $\mathcal{O}\left(\frac{\sqrt N}{\log\log N}\right)$ tùy cách cài đặt.                                                                              |
|   $10^9 \rightarrow 10^{19}$   | <p>★ [Thuật toán Pollard's Rho](#Thuật-toán-Rho-Pollard) ([Pollard's Rho algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm)).<br>★ Thuật toán PTNT dạng bình phương của Shanks ([Shanks's square forms factorization](https://en.wikipedia.org/wiki/Shanks%27s_square_forms_factorization)) (SQUFOF)                              | $\mathcal{O}\left(N^{1/4}\right)$ cho cả hai thuật toán, nhưng Pollard's Rho thường được sử dụng phổ biến hơn do dễ cài đặt hơn.                                               |
| $10^{19} \rightarrow 10^{25}$  | Thuật toán PTNT đường cong elliptic Lenstra ([Lenstra elliptic-curve factorization](https://en.wikipedia.org/wiki/Lenstra_elliptic-curve_factorization)) (ECM)                                                                                                                                                                                        | $\sum e^{\left(\sqrt2 + \mathcal{O}(1)\right)\sqrt{\log P\log\log P} }$, với $P$ là các ước nguyên tố của $N$.                                                                |
| $10^{25} \rightarrow 10^{100}$ | Thuật toán sàng bậc hai ([Quadratic Sieve](https://en.wikipedia.org/wiki/Quadratic_sieve)) (QS)                                                                                                                                                                                                                                                       | $\sum e^{\big(1 + \mathcal{O}(1)\big)\sqrt{\log P\log\log P}}$, với $P$ là các ước nguyên tố của $N$.                                                                         |
|       Lớn hơn $10^{100}$       | Sàng trường số tổng quát ([General number field Sieve](https://en.wikipedia.org/wiki/General_number_field_sieve)) (GNFS)                                                                                                                                                                                                                                                                    | $e^{\left(\sqrt[3]2 + \mathcal{O}(1)\right)(\log N)^{1/3} (\log\log N)^{2/3} }$.                                                                                               |

\* Về độ phức tạp $e^{\big(\beta + \mathcal{O}(1)\big)(\log N)^{\alpha} (\log\log N)^{1-\alpha} }$ hay trong ký hiệu [L-notation](https://en.wikipedia.org/wiki/L-notation) là $L_N[\alpha, \beta]$:
- $\big(\beta + \mathcal{O}(1)\big)$ là một hằng số.
- Còn $e^{\log\log N} < e^{(\log N)^{\alpha} (\log\log N)^{1-\alpha} } < e^{\epsilon \log N}$ hay :

<center>

$\log N < e^{(\log N)^{\alpha} (\log\log N)^{1-\alpha} } < N^\epsilon$ với $\epsilon=\left(\frac{\log\log N}{\log N}\right)^{1-\alpha}$</center>

&nbsp; &nbsp; &nbsp; &nbsp; Do hệ số $\epsilon$ giảm khi $N$ tăng nên khi $N$ càng lớn, các ĐPT này càng nhỏ so với $N$.
&nbsp; &nbsp; &nbsp; &nbsp; Ví dụ khi $\alpha=1/2, \beta=1$ và $N\sim 10^{100}$ thì độ phức tạp khoảng $\mathcal{O}(N^{0.154})$.

## Luyện tập

- [Codechef - MLTDVD](https://www.codechef.com/problems/MLTDVD)
- [Codechef - STABLE](https://www.codechef.com/problems/STABLE)
- [SPOJ - FACT0](https://www.spoj.com/problems/FACT0/)
- [SPOJ - FACT1](https://www.spoj.com/problems/FACT1/)
- [SPOJ - FACT2](https://www.spoj.com/problems/FACT2/)
- [Codechef - FACTORIZ](https://www.codechef.com/problems/FACTORIZ/)
- [GCPC 15 - Divisions](https://codeforces.com/gym/100753)
- [Library Checker - Factorize](https://judge.yosupo.jp/problem/factorize)

## Nguồn tham khảo

* [Wikipedia](https://en.wikipedia.org/wiki/Main_Page)
* [CP-Algorithms - Integer factorization](https://cp-algorithms.com/algebra/factorization.html)
<!--* [Giải thuật Pollard Rho](https://www.giaithuatlaptrinh.com/?p=393)-->
* J.M. Pollard, "A Monte Carlo Method for Factorization", BIT Numerical Mathematics, 1975.
* Teske, E., "On Random Walks for Pollard’s Rho Method", Mathematics of Computation, 2001 ([SpringerLink](https://link.springer.com/chapter/10.1007/3-540-45537-X_17)).
* Kuhn, F. & Struik, R., "Random Walks Revisited: Extensions of Pollard’s Rho Algorithm for Computing Multiple Discrete Logarithms", SpringerLink, 2023 ([SpringerLink](https://link.springer.com/chapter/10.1007/3-540-45537-X_17)).
- [Richard P Brent. An improved monte carlo factorization algorithm. BIT Numerical Mathematics, 20(2):176–184, 1980](https://maths-people.anu.edu.au/~brent/pd/rpb051i.pdf)

