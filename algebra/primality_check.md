# Kiểm tra số nguyên tố
**Người viết:** Nguyễn Anh Bảo - Đại học Bách Khoa Hà Nội

**Reviewer:**
* Ngô Nhật Quang - Trường THPT chuyên Khoa học Tự Nhiên, ĐHQGHN
* Phạm Hoàng Hiệp - Đại học Công Nghệ, ĐHQGHN

## Giới thiệu

Trong bài viết này, chúng ta sẽ cùng tìm hiểu một số thuật toán và phương pháp kiểm tra một số tự nhiên bất kì có là số nguyên tố hay không.
## Số nguyên tố
Một số tự nhiên $n$ được gọi là số nguyên tố khi và chỉ khi $n$ có đúng $2$ ước dương là $1$ và chính nó.

Ví dụ: $2,3,5,101$ là các số nguyên tố. $0,1,10,12$ không là số nguyên tố.

Trong bài viết này, chúng ta sẽ tập trung vào việc kiểm tra **một** số nguyên dương có phải số nguyên tố hay không. Để kiểm tra tính nguyên tố của nhiều số nguyên trên một đoạn $\left[a,b\right]$, bạn đọc có thể tham khảo bài viết [Số nguyên tố và sàng Eratosthenes](https://vnoi.info/wiki/translate/he/Number-Theory-2.md).

## 1. Thuật toán ngây thơ

### 1.1. Ngây thơ 1

Cách đơn giản nhất để kiểm tra tính nguyên tố của số tự nhiên $n$ là trực tiếp sử dụng định nghĩa số nguyên tố: 

> Số tự nhiên $n\ge 2$ là số nguyên tố khi và chỉ khi $n$ không chia hết cho các số tự nhiên $2,3,\ldots,n-1$.

Ta có thể cài đặt như sau:

```cpp=
bool primeCheck(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i < n; ++i)
        if (n % i == 0)
            return false;
    return true;
}
```
Độ phức tạp thuật toán: $\mathcal{O}\left(n\right)$.

### 1.2. Ngây thơ 2

Để tối ưu thuật toán trên, nhận xét rằng nếu $n$ có một ước $d$ sao cho $n-1\ge d\ge\sqrt{n}$ thì $\frac{n}{d}$ cũng là ước của $n$ và có $1<\frac{n}{d} \le \sqrt{n}$. Suy ra nếu $n$ không chia hết cho các số tự nhiên lớn hơn $1$ và không vượt quá $\sqrt{n}$ thì $n$ cũng không chia hết cho các số tự nhiên lớn hơn $\sqrt{n}$. Từ đó, thay vì xét tính chia hết của $n$ cho $i=2,3,\ldots,n-1$ ta chỉ cần xét $i=2,3,\ldots,\left[\sqrt{n}\right]$.

Cài đặt thuật toán:

```cpp=
bool primeCheck(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}
```

Độ phức tạp thuật toán: $\mathcal{O}\left(\sqrt{n}\right)$.

Ta có thể mở rộng thuật toán trên thành thuật toán phân tích một số nguyên dương ra thừa số nguyên tố:

```cpp=
void primeFactorization(int n)
{
    for (int i = 2; i * i <= n; ++i)
        while (n % i == 0)
        {
            n /= i;
            cout << i << ' ';
        }
    if (n > 1)
        cout << n;
}
```

### 1.3. Ngây thơ 2.5

Để ý nếu số nguyên tố $n$ lẻ thì $n$ không chia hết cho một số chẵn bất kì. Do đó nếu $n>2$, ta chỉ cần xét các số $i$ lẻ thuộc đoạn $\left[2,\left[\sqrt{n}\right]\right]$. Tương tự, nếu $n>3$ thì ta chỉ cần xét $i$ là các số không chia hết cho $3$. Từ hai nhận xét trên, nếu $n>3$ thì ta chỉ cần xét các số $i$ sao cho $i$ chia $6$ dư $1$ hoặc $5$.

```cpp=
bool primeCheck(int n)
{
    if (n == 2 || n == 3)
        return true;
    if (n < 3 || n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
```
**Chú ý:** Có thể sử dụng nhiều số nguyên tố đầu tiên để tối ưu thuật toán hơn. Về lý thuyết, nếu $k$ là số số nguyên tố được dùng càng lớn thì vòng lặp chạy càng nhanh. Tuy nhiên, với $k=50$, độ phức tạp vòng lặp `for` là $\mathcal{O}\left(\frac{\sqrt{n}}{10}\right)$. Và kể cả với $k=6.10^5$ thì độ phức tạp thuật của vòng lặp `for` vẫn là $\mathcal{O}\left(\frac{\sqrt{n}}{30}\right)$.

Do đó thuật toán này có thể không đủ nhanh để giải quyết giới hạn $n\le10^{18}$, hoặc $n\le10^9$ nhưng phải kiểm tra $10^6$ số $n$ trở lên. Để giải quyết các bài toán có giới hạn lớn như thế, ta phải sử dụng đến các phương pháp xác suất.

## 2. Phép thử Fermat (Định lí Fermat nhỏ)

### 2.1. Ý tưởng

Theo định lí Fermat nhỏ, nếu $p$ là một số nguyên tố thì với mọi số nguyên $a$ thỏa mãn $\gcd\left(a,p\right)=1$, ta có: 
$$
a^{p-1}\equiv 1\mod{p} 
$$

Từ định lý Fermat ta có ý tưởng kiểm tra tính nguyên tố của số nguyên dương $n$ như sau: 

* Xét số nguyên $a\in\left[2,n-1\right]$, nếu $a^{n-1}\not\equiv1\mod{n}$ thì ta **chắc chắn** $n$ là hợp số hoặc $n<2$. 
* Ngược lại, nếu $a^{n-1}\equiv 1\mod{n}$ thì $n$ **có thể** là số nguyên tố.

**Chú ý:** Phần in đậm của phép thử nghĩa là tồn tại các giá trị của $n$ và $a$ sao cho $n$ là hợp số và $a^{n-1}\equiv 1 \mod{n}$. Ví dụ, nếu $n=15$ và $a=4$ thì $4^{14}\equiv 1 \mod{15}$. Trong trường hợp này, $n$ được gọi là số giả nguyên tố cơ sở $a$, hoặc số nguyên tố xác suất cơ sở $a$.

Về lý thuyết, nếu ta kiểm tra đẳng thức Fermat với mọi số $a$, ta có thể kết luận chắc chắn tính nguyên tố của $n$. Tuy nhiên, việc kiểm tra đẳng thức với mọi $a$ sẽ phức tạp hơn cả thuật toán ngây thơ. Do đó, phép thử Fermat sẽ thực hiện một số lần thử với các số $a$ được lấy ngẫu nhiên. Trong các bài toán lập trình thi đấu, phép thử vẫn có độ chính xác đủ tốt. 

### 2.2. Cài đặt
Ta có thể cài đặt kết quả của phép tính $a^{n-1}\mod{n}$ bằng lũy thừa nhị phân.

```cpp=
// Tính a^k (mod n)
int binaryPower(long long a, int k, int n)
{
    a = a % n;
    long long res = 1;
    while (k)
    {
        if (k & 1)
            res = (res * a) % n;
        a = (a * a) % n;
        k /= 2;
    }
    return res;
}
```

Cài đặt phép thử Fermat:

```cpp=
bool isProbablyPrime(int n)
{
    if (n < 7)
        return n == 2 || n == 3 || n == 5;
    
    static const int repeatNum = 5;
    for (int i = 0; i < repeatNum; ++i)
    {
        int a = rand() % (n - 3) + 2;
        if (binaryPower(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
```

Độ phức tạp phép thử là $\mathcal{O}\left(c\log{n}\right)$ với $c$ là số cơ số $a$ được thử.

Do thuật toán `binaryPower` có sử dụng phép tính `(a * a) % n` nên nếu $n\ge2^{32}$ sẽ có thể bị tràn số. Phiên bản được trình bày ở trên xử lí $n<2^{32}$. Để áp dụng thuật toán lũy thừa nhị phân với $10^{18}\ge n$, bạn phải dùng kiểu số nguyên $128-bit$ nếu ngôn ngữ lập trình cho phép. Nếu ngôn ngữ lập trình chỉ có loại số nguyên $64-bit$, bạn có thể tham khảo thuật toán được chỉnh sửa như sau:

```cpp=
// Tính a * b mod n
long long binaryMul(long long a, long long b, long long n)
{
    a = a % n;
    long long res = 0;
    while (b)
    {
        if (b & 1)
            res = (res + a) % n;
        a = (2 * a) % n;
        b /= 2;
    }
    return res;
}

// Tính a^b mod n
long long binaryPow(long long a, long long k, long long n)
{
    a = a % n;
    long long res = 1;
    while (k)
    {
        if (k & 1)
            res = binaryMul(res, a, n);
        a = binaryMul(a, a, n) % n;
        k /= 2;
    }
    return res;
}
```

Khi đó độ phức tạp thuật toán là $\mathcal{O}\left(c\log^2{n}\right)$.


**Chú ý:** Do không có tính chính xác tuyệt đối nên phép thử Fermat không phải là một thuật toán.

Tuy tốc độ cao và dễ cài đặt, vẫn có những trường hợp xác suất phép thử Fermat thất bại là rất cao. Ví dụ xét số $n=561 = 3 \times 11 \times 17$. Số này có tính chất với mọi số nguyên $a$ mà $\gcd(a,n)=1$ thì $a^{n-1}\equiv 1\mod n$. Do đó, trừ khi trong các lần thử ngẫu nhiên ta chọn được $a$ chia hết cho $3,11$ hoặc $17$ thì phép thử sẽ cho kết quả sai.

Các số có tính chất trên được gọi là số *Carmichael*. 

### 2.3. Vấn đề với số Carmichael

Xét $n$ là một số Carmichael có $k$ ước nguyên tố, $c$ là số lần chọn cơ số $a$ (`repeatNum`). Nếu $k=3$ thì số $n$ nhỏ nhất là $561$. Xác suất phép thử kết luận đúng với $k=3$ do đó bị chặn bởi $T(c)$. $T(c)$ cho bởi bảng sau:

$c$    |$1$|$2$|$3$|$4$|$5$|$\ldots$
-------|-|-|-|-|-|-------
$T(c)$ |$49\%$|$74\%$|$86\%$|$93\%$|$97\%$|$\ldots$

Từ bảng trên có thể thấy để có độ chính xác $\ge90\%$ thì ta phải thử ít nhất $4$ lần, và có thể nhiều hơn. Trong khi nếu ta chỉ thử $1$ lần duy nhất thì xác suất phép thử kết luận sai là $>\frac{1}{2}$.

Với $k=4$, số Carmichael nhỏ nhất có $4$ ước nguyên tố là $41041$$= 7 \times 11 \times 13 \times 41$. Tương tự, xét xác suất phép thử cho kết quả đúng với $n$ là số Carmichael dạng này bị chặn bởi $T(c)$. $T(c)$ được cho bởi bảng sau:

$c$    |$1$|$2$|$3$|$4$|$5$|$\ldots$
-------|-|-|-|-|-|-------
$T(c)$ |$34\%$|$56\%$|$71\%$|$81\%$|$88\%$|$\ldots$

Tức là kể cả ta có thử đến $5$ lần thì xác suất phép thử kết luận đúng vẫn không thể quá $90\%$.

Một điều khá thú vị là các số Carmichael phân bố rất ít trong tập các số tự nhiên. Theo [OEIS-A055553](https://oeis.org/A055553):
* Số các số Carmichael nhỏ hơn $10^6$ là $43$
* Số các số Carmichael nhỏ hơn $10^9$ là $646$
* Số các số Carmichael nhỏ hơn $10^{18}$ là $1401644$

Do đó, các bạn có thể yên tâm khi sử dụng phép thử Fermat nếu test được sinh ngẫu nhiên, vì xác suất gặp số Carmichael rất thấp. Nếu test cố tình chọn số Carmichael thì phép thử không còn đáng tin cậy. Rất may là có những phép thử hiệu quả và chính xác hơn phép thử Fermat. Trong phần tiếp theo chúng ta sẽ cùng tìm hiểu thuật toán Rabin-Miller.

## 3. Thuật toán Rabin-Miller

### 3.1. Ý tưởng

Thuật toán Rabin-Miller là phiên bản mở rộng và mạnh hơn của phép thử Fermat. Thuật toán dựa vào nhận xét sau:

> Với mọi số nguyên dương $x$, ta tìm được duy nhất hai số tự nhiên $k,m$ sao cho $x=2^k\times m$ và $m$ lẻ.

Ví dụ: $6=2^1\times3,100=2^2\times25, 9=2^0\times9,\ldots$

Do đó, xét số $n$, ta có thể phân tích $n-1$ thành $2^k\times m$, với $m$ là số lẻ.

Theo định lý nhỏ Fermat, nếu $n$ là số nguyên tố thì với mọi $a$ sao cho $\gcd(a,n)=1$ ta có: 

$$
a^{n-1}\equiv1\mod{n}\Leftrightarrow a^{2^k.m}-1\equiv0\mod{n} \\
\Leftrightarrow \left(a^{2^{k-1}m}+1\right)\left(a^{2^{k-2}m}+1\right)\ldots\left(a^{m}+1\right)\left(a^m-1\right)\equiv0 \mod{n}
$$

Vì $n$ là số nguyên tố nên tồn tại ít nhất một trong các nhân tử của vế trái chia hết cho $n$. Do đó, thay vì kiểm tra kết luận của định lý Fermat nhỏ, ta sẽ kiểm tra điều kiện sau:

* $a^m\equiv1\mod{n}$ hoặc
* Tồn tại $0\le l \le k-1$ sao cho $a^{{2^l}m}\equiv-1\mod{n}$

Nếu cả hai điều kiện không được thỏa mãn thì chắc chắn $n$ là hợp số.

Nhưng nếu cả hai điều kiện được thỏa mãn thì $n$ có phải số nguyên tố không?

Câu trả lời là **không**. Ví dụ: với $n=28,a=19$ thì $n-1=2^0\times27$ và $19^{27}\equiv-1\mod{28}$.

Do đó, để áp dụng ý tưởng trên, ta có thể triển khai theo hai cách sau:

### 3.2. Phép thử xác suất (Probabilistic)

Để tăng tính chính xác của thuật toán ta có thể lặp lại bước kiểm tra với nhiều cơ số $a$, giống như phép thử Fermat. Hơn thế nữa, chứng minh được nếu $n$ là hợp số, chỉ có $\approx25\%$ số cơ số $a$ trong đoạn $\left[2,n-1\right]$ thỏa mãn một trong hai điều kiện. 

Nghĩa là với hợp số $n$ bất kì, xác suất để thuật toán chứng minh được $n$ là hợp số sau lần kiểm tra đầu tiên là $\ge75\%$, lần thứ hai là $\ge93.75\%$, lần thứ ba là $\ge98.43\%$, lần thứ $x$ là $\left(1-\frac{1}{4^x}\right)\times 100\%$. Có thể thấy độ chính xác của thuật toán Rabin-Miller cao hơn nhiều so với phép thử Fermat, và tất nhiên là đủ tốt cho các bài toán lập trình thi đấu.

**Cài đặt thuật toán:**

```cpp=
// Tính a^k mod n
long long binaryPower(long long a, long long k, long long n)
{
    a = a % n;
    long long res = 1;
    while (k)
    {
        if (k & 1)
            res = (res * a) % n;
        a = (a * a) % n;
        k /= 2;
    }
    return res;
}

// Kiểm tra điều kiện thuật toán với a cố định
bool test(long long a, long long n, long long k, long long m)
{
    long long mod = binaryPower(a, m, n);
    if (mod == 1 || mod == n - 1)
            return true;
    for (int l = 1; l < k; ++l)
    {
        mod = (mod * mod) % n;
        if (mod == n - 1)
            return true;
    }
    return false;
}

bool RabinMiller(long long n)
{
    // Kiểm tra với các giá trị nhỏ
    if (n == 2 || n == 3 || n == 5 || n == 7)
        return true;
    if (n < 11)
        return false;

    // Tính m và k
    long long k = 0, m = n - 1;
    while (m % 2 == 0)
    {
        m /= 2;
        k++;
    }

    // Lặp lại bước kiểm tra với a ngẫu nhiên
    const static int repeatTime = 3;
    for (int i = 0; i < repeatTime; ++i)
    {
        long long a = rand() % (n - 3) + 2;
        if (!test(a, n, k, m))
            return false;
    }
    return true;
}
```
Độ phức tạp là $\mathcal{O}\left(c\log{n}\right)$.

### 3.3. Thuật toán đơn định (Deterministic)

Phép thử xác suất có thể trở thành thuật toán bằng cách thay vì xét $a$ ngẫu nhiên, ta sẽ xét tất cả $a$ bị chặn bởi một hàm theo $n$. Miller chứng minh được nếu [Định đề Riemann tổng quát (GRH)](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Deterministic_variants) là đúng thì ta chỉ cần kiểm tra $a\in\left[2,\mathcal{O}\left(\ln^2 n\right)\right]$. Sau đó, Bach chứng minh được chỉ cần xét $a\in\left[2,2\ln^2 n\right]$.

Với $n$ đủ lớn thì vẫn có rất nhiều giá trị cần kiểm tra. Nhưng người ta cũng chứng minh được rằng:

* Nếu $n\le 3.10^9$, chỉ cần xét $a\in\{2;3;5;7\}$
* Nếu $n\le 2^{64}$, chỉ cần xét $a\in\{2;3;5;7;11;13;17;19;23;29;31;37\}$

Do đó, ta có phiên bản thuật toán (độ chính xác $100\%$) của phép thử như sau:

```cpp=
bool MillerRabin(long long n)
{
    if (n == 2 || n == 3 || n == 5 || n == 7)
        return true;
    if (n < 11)
        return false;

    long long k = 0, m = n - 1;
    while (m % 2 == 0)
    {
        m /= 2;
        k++;
    }

    static vector<int> checkSet = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (auto a : checkSet)
        if (!test(a, n, k, m))
            return false;
    return true;
}
```

## 4. Bài tập luyện tập:

* [**SPOJ - Prime Or Not**](https://www.spoj.com/problems/PON/)

## 5. Tham khảo:

* [CP Algorithm - Primality Test](https://cp-algorithms.com/algebra/primality_tests.html#fermat-primality-test)
* [Wikipedia - Primality Miller-Rabin test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)
* [Wikipedia - Primality test](https://en.wikipedia.org/wiki/Primality_test)
* [Wikipedia - Carmichael numbers](https://en.wikipedia.org/wiki/Carmichael_number)