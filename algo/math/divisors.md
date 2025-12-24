---
title: Số các ước và Tổng các ước
description: 
published: true
date: 2025-02-07T16:21:57.369Z
tags: 
editor: markdown
dateCreated: 2024-04-06T13:23:44.674Z
---

# Số các ước và Tổng các ước
**Tác giả:**
- Nguyễn Đức Kiên, Trường Đại học Công nghệ, ĐHQGHN

**Reviewer:**
- Cao Thanh Hậu - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM
- Phạm Hoàng Hiệp - University of Georgia 
- Nguyễn Minh Nhật - THPT chuyên Khoa học Tự nhiên, ĐHQGHN

## Kiến thức cần biết

Để có thể hiểu được toàn bộ bài này, bạn nên nắm vững kiến thức và cài đặt được:
- [Sàng nguyên tố](https://wiki.vnoi.info/algo/algebra/prime_sieve.md)
- [Luỹ thừa nhanh](https://wiki.vnoi.info/algo/algebra/binary_exponentation.md)

## Một số ký hiệu được sử dụng

-   $b|a$: $b$ là ước của $a$. Ký hiệu này tương đương với ${a} \vdots b$.
-   $log(N)$: Logarit cơ số $2$ của $N$ (quy ước chỉ trong bài viết này).

## Bài toán đếm số ước

### Bài toán 1: Đếm số ước của một số

**Đề bài**: Cho một số nguyên dương $N$. Đếm số ước của $N$.

Với nhiều coder, đây là một trong những bài toán beginner không thể không làm qua. Đây là bài toán thường được sử dụng như một ví dụ về việc phải tìm cách để tối ưu số lần lặp.

#### Cách 1: Duyệt để tìm ước

Giải thuật ngây thơ nhất rất đơn giản: từ nhận xét mọi ước của $N$ đều không vượt quá $N$, ta duyệt mọi số nguyên dương trong đoạn $[1, N]$ và đếm số lượng ước của $N$ trong đó:

```cpp=
int divCount(int n) {
    int ret = 0;
    for (int i = 1; i <= n; i ++)
        ret += (n % i == 0);
    return ret;
}
```

##### Cải tiến

Ta nhận thấy rằng chỉ cần duyệt các ước tới $\sqrt{N}$ là đủ, do ứng với mọi ước $d$ của $N$ nhỏ hơn $\sqrt{N}$ ta có hai ước của $N$ là $d$ và $\frac{N}{d}$, và khi $N$ là số chính phương, ứng với ước $\sqrt{N}$ ta có một ước duy nhất là chính nó.

**Chứng minh**

Gọi $d$ là một ước của $N$, khi đó tồn tại một số nguyên $g$ sao cho $d \times g=N$. Nếu $d=g$, khi đó ta có $d=g=\sqrt{N}$. Trường hợp $d\neq g$, không mất tính tổng quát ta giả sử $d<g$. Dễ thấy $d<\sqrt{N}<g$, vì nếu $\sqrt{N}\leq d$ thì ta có $d \times g > \sqrt{N} \times \sqrt{N} = N$ và nếu $\sqrt{N}\geq g$ thì $d \times g < \sqrt{N} \times \sqrt{N} = N$, đều mâu thuẫn với giả thiết $d\times g=N$.

```cpp=
int divCount(long long n) {
    int ret = 0;
    for (int i = 1; 1ll * i * i <= n; i ++) {
        ret += 2 * (n % i == 0);
        if (1ll * i * i == n) ret --;
    }
    return ret;
}
```

Hai giải thuật trên có độ phức tạp thời gian lần lượt là $O(N)$ và $O(\sqrt{N})$, sẽ chạy tốt với $N \leq 10^6$ và $N \leq 10^{12}$. Rất khó để cải thiện độ phức tạp này để phù hợp với $N$ lớn hơn.

#### Cách 2: Sử dụng sàng nguyên tố

**Định lý**: Nếu một số $N$ được phân tích ra thừa số nguyên tố thành:
$$N = \prod_{i = 1}^{k}{p_i^{m_i}} = p_1^{m_1} \times p_2^{m_2} ... \times p_k^{m_k}$$

với $p_i$ là các số nguyên tố, $m_i$ là các số nguyên dương thì số ước của $N$ là:

$$\tau(N) = \prod_{i = 1}^{k}{(m_i + 1)}$$

(Chữ $\tau$ đọc là _tau_).

:::spoiler **Chứng minh (nhấn để hiện)**
Mọi ước $d$ của $N$ khi phân tích thành thừa số nguyên tố sẽ có dạng:
$$d = \prod_{i = 1}^{k}{p_i^{\mu_i}}$$
với $0 \leq \mu_i \leq m_i$.
Mỗi cách chọn số $d$ ứng với một cách chọn bộ số $\mu_i$ nên số cách chọn thoả mãn là $\prod_{i = 1}^{k}{(m_i + 1)}$.
:::

##### Thuật toán

Để giải bài toán này theo cách phân tích ra thừa số nguyên tố, đầu tiên ta sử dụng sàng nguyên tố để lưu lại các số nguyên tố nhỏ hơn $N$. Sau đó, lần lượt chia $N$ cho các số trên rồi thu lại số lần chia ứng với mỗi số; đó chính là số mũ của các thừa số nguyên tố tương ứng. Cuối cùng, áp dụng công thức trên để tính ra kết quả.

Cách làm này mất $O(N\log\log N)$ thời gian và không gian để chuẩn bị sàng, và $O(\pi(N)) \approx O(\frac{N}{\ln N})$ thời gian để phân tích, với $\pi(n)$ là số lượng số nguyên tố nhỏ hơn $N$. Tổng độ phức tạp là $O(N\log\log N)$.

##### Cải tiến 1

Sử dụng nhận xét sau, ta giảm được độ phức tạp xuống $O(\sqrt{N}\log\log\sqrt{n})$. Ta viết $N = X \times Y$. Trong đó, số $X=\prod_{p_i<\sqrt{N}}{p_i^{m_i}}$ là tích của tất cả các thừa số nguyên tố của $N$ đã nâng lên luỹ thừa có cơ số nhỏ hơn $\sqrt{N}$, còn $Y=\frac{N}{X}$. Xét hai trường hợp:
- $Y=1$. Trường hợp này hoàn toàn giống với thuật toán $O(N\log\log N)$ chưa được cải tiến.
- $Y\neq 1$. Lúc này, nếu phân tích $Y$ ra thừa số nguyên tố, ta sẽ không thu được một thừa số nào nhỏ hơn $\sqrt{N}$, vì các thừa số như vậy đều đã nằm trong $X$. Điều đó có nghĩa là $Y$ không có ước nguyên tố nào nhỏ hơn $\sqrt{Y}$, do đó $Y$ là một số nguyên tố.

Ví dụ:
- $N = 60$, với cách đặt trên ta có $X=60,Y=1$
- $N = 60\,000\,180$, với cách đặt trên ta sẽ có $X = 60$ và $Y = 1\,000\,003$.

Khi cài đặt, sau khi chia $N$ cho toàn bộ các số nguyên tố đã thu được sau khi sàng, giá trị $N$ còn lại chính là $Y$.

Một edge case nho nhỏ là $N = 1$. Do $1$ không thể phân tích được thành thừa số nguyên tố, ta trả về luôn $1$ cho trường hợp này.

```cpp=
const int MAXN = 1e6;

vector<int> primes;
vector<bool> isPrime;

void sieve() {
    isPrime.assign(MAXN + 1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i <= MAXN; i++) {
        if (!isPrime[i]) continue;
        primes.push_back(i);
        for (int j = i + i; j <= MAXN; j += i) {
            isPrime[j] = 0;
        }
    }
}

int countDiv(long long n) {
    if (n == 1) return 1;
    vector<int> powV;
    for (auto p : primes) {
        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            ++cnt;
        }
        if (cnt) powV.push_back(cnt);
    }
    if (n != 1) powV.push_back(1);
    int ret = 1;
    for (auto i : powV) ret *= (i + 1);
    return ret;
}

void solution() {
    sieve();
    long long n;
    cin >> n;
    cout << countDiv(n);
}
```

##### Cải tiến 2

Cho tới bước này, ta có thể giải được bài toán với $N \leq 10^{12}$. Ta sẽ cải tiến để bài toán giải được với $N \leq 10^{18}$, với độ phức tạp là khoảng $O(\sqrt[3]{N})$.

Vẫn viết $N$ dưới dạng $N = X \times Y$ như trên, $X$ được định nghĩa tương tự như trên, chỉ khác giới hạn các thừa số nguyên tố lúc này là $\sqrt[3]{N}$: $X=\prod_{p_i<\sqrt[3]{N}}{p_i^{m_i}}$. Lúc này ta không thể chắc chắn $Y$ là số nguyên tố nữa. Tuy nhiên, $Y$ lại chỉ có thể thuộc vào một trong bốn trường hợp:

-   $Y=1$. Hiển nhiên $\tau(N) = \tau(X)$
-   $Y$ là số nguyên tố. Khi đó nó chỉ có $2$ ước là $1$ và $Y$, và khi đó $\tau(N) = \tau(X) \times 2$.
-   $Y$ là bình phương của một số nguyên tố. Khi đó nó có $3$ ước là $1$, $\sqrt{Y}$ và $Y$, và $\tau(N) = \tau(X) \times 3$.
-   $Y$ là tích của hai số nguyên tố. Khi đó nó có $4$ ước và $\tau(N) = \tau(X) \times 4$.

Các trường hợp khác:
- $Y$ _không_ là tích của nhiều hơn hai số nguyên tố. Tất cả các số nguyên tố nhỏ hơn $\sqrt[3]{N}$ đã bị sàng nguyên tố loại bỏ và trở thành ước của $X$, vì vậy tích ba số nguyên tố bất kỳ còn lại sẽ lớn hơn $N$.
- $Y$ _không_ là tích của một hợp số với một số nguyên tố hoặc tích của hai hợp số. Ta biết (các) ước hợp số này không thể chứa các ước nguyên tố nhỏ hơn $\sqrt[3]{N}$ do chúng đã bị loại khỏi sàng, nghĩa là nếu trường hợp này xảy ra, $Y$ sẽ là tích của ít nhất 3 số nguyên tố.

Để kiểm tra trường hợp thứ nhất, ta có thể dùng [thuật toán Rabin-Miller](https://wiki.vnoi.info/algo/algebra/primality_check.md#3-thu%E1%BA%ADt-to%C3%A1n-rabin-miller). Để kiểm tra trường hợp thứ hai, ta kiểm tra xem $Y$ có phải số chính phương không. Các số còn lại sẽ rơi vào trường hợp thứ ba.

```cpp=
const int MAXN = 1e6;

vector<int> primes;
vector<bool> isPrime;

void sieve() {
    isPrime.assign(MAXN + 1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i <= MAXN; i++) {
        if (!isPrime[i]) continue;
        primes.push_back(i);
        for (int j = i + i; j <= MAXN; j += i) {
            isPrime[j] = 0;
        }
    }
}

long long binaryPower(long long a, long long k, long long n) {
    a = a % n;
    long long res = 1;
    while (k) {
        if (k & 1)
            res = (res * a) % n;
        a = (a * a) % n;
        k /= 2;
    }
    return res;
}

bool test(long long a, long long n, long long k, long long m) {
    long long mod = binaryPower(a, m, n);
    if (mod == 1 || mod == n - 1)
            return 1;
    for (int l = 1; l < k; ++l) {
        mod = (mod * mod) % n;
        if (mod == n - 1)
            return 1;
    }
    return 0;
}

bool isPrimeRabinMiller(long long n) {
    vector<int> checkSet = {2, 3, 5, 7,
                            11, 13, 17, 19,
                            23, 29, 31, 37};
    if (n <= 37) {
        for (int i : checkSet) {
            if (i == n) return 1;
        }
        return 0;
    }

    long long k = 0, m = n - 1;
    while (m % 2 == 0) {
        m /= 2;
        k++;
    }

    for (auto a : checkSet)
        if (!test(a, n, k, m))
            return 0;
    return 1;
}

bool isSquare(long long n){
    long long c = sqrt(n + 4);
    return c * c == n || (c - 1) * (c - 1) == n;
}

int countDiv(long long n) {
    if (n == 1) return 1;
    vector<int> powV;
    for (auto p : primes) {
        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            ++cnt;
        }
        if (cnt) powV.push_back(cnt);
    }
    if (n != 1) {
        if (isPrimeRabinMiller(n)) powV.push_back(1);
        else if (isSquare(n)) powV.push_back(2);
        else {
            powV.push_back(1);
            powV.push_back(1);
        }
    }
    int ret = 1;
    for (auto i : powV) ret *= (i + 1);
    return ret;
}

void solution() {
    sieve();
    long long n;
    cin >> n;
    cout << countDiv(n);
}
```

Phần Rabin-Miller có độ phức tạp là $O(12\log N)$. Phần kiểm tra số chính phương có độ phức tạp là $O(1)$, với chú ý rằng cần phải xét một vài số lân cận `sqrt(N)` để đưa ra kết quả chính xác. Tổng hợp lại, độ phức tạp của giải thuật trên là $O(\sqrt[3]{N}\log\log \sqrt[3]{N}+\log N)$.

Giải thuật này thậm chí [còn có thể tối ưu](https://codeforces.com/blog/entry/22317?#comment-797506) tới khoảng $O(\sqrt[4]{N})$. Tuy vậy số trường hợp được đặt ra là tương đối lớn và kiểm tra chúng cũng không hề dễ dàng.

Ngoài ra, nếu có thể phân tích $N$ ra thừa số nguyên tố bằng [thuật toán rho của Pollard](https://cp-algorithms.com/algebra/factorization.html#pollards-rho-algorithm), lời giải lúc này cũng có độ phức tạp là khoảng $O(\sqrt[4]{N})$.

### Bài toán 2: Đếm số ước của nhiều số

**Đề bài**: Cho $Q$ truy vấn. Ở truy vấn thứ $i$, cần tìm số các ước của số $A_i$ với $A_i < N$.

Bằng cách duyệt qua mọi ước của từng số một, độ phức tạp thời gian sẽ là $O(Q\sqrt{N})$. Còn với cách thứ hai giống như ở trên, độ phức tạp tốt nhất là $O(Q\sqrt[3]{N}\log\log \sqrt[3]{N}+Q\log N)$. Với $Q$ nhỏ, ta hoàn toàn có thể làm tương tự như trên.

Khi $Q$ đủ lớn $(Q \leq 10^6)$ và $N$ không quá lớn $(N \leq 10^6)$, các hướng làm trên tỏ ra khá tồi. 

Với cách thứ hai, ta có thể thay đổi một chút để có thể đưa ra kết quả của truy vấn nhanh hơn. Khi chuẩn bị, với mỗi số $x$, thay vì chỉ lưu `isPrime[x]`, ta lưu lại ước nguyên tố nhỏ nhất của $x$, là `minPDiv[x]`. Khi thực hiện truy vấn, thay vì chia $N$ cho toàn bộ các số nguyên tố, ta chỉ cần chia liên tục $N$ cho ước nguyên tố nhỏ nhất của nó tại thời điểm đó, ta sẽ dần thu được kết quả.

```cpp=
const int MAXN = 1e6;

vector<int> minPDiv;

void sieve() {
    minPDiv.resize(MAXN + 1);
    for (int i = 2; i <= MAXN; i++) {
        if (minPDiv[i]) continue;
        minPDiv[i] = i;
        for (int j = i + i; j <= MAXN; j += i) {
            minPDiv[j] = i;
        }
    }
}

int countDiv(int n) {
    if (n == 1) return 1;
    vector<int> powV;
    int lastDiv = 0;
    int cnt = 0;
    while (n != 1) {
        if (minPDiv[n] != lastDiv) {
            if (cnt) powV.push_back(cnt);
            cnt = 0;
        }
        ++cnt;
        lastDiv = minPDiv[n];
        n /= minPDiv[n];
    }
    if (cnt) powV.push_back(cnt);
    int ret = 1;
    for (auto i : powV) ret *= (i + 1);
    return ret;
}

void solution() {
    sieve();
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        cout << countDiv(n) << "\n";
    }
}
```

Phần chuẩn bị sàng nguyên tố mất $O(N)$ không gian và $O(N\log\log N)$ thời gian. Mỗi truy vấn, số phép tính được thực hiện bằng đúng tổng số mũ của các thừa số nguyên tố trong phân tích của $N$. Dễ thấy giá trị này không vượt quá $\log N$, và do đó độ phức tạp thời gian của phần này là $O(Q\log N)$. Độ phức tạp thời gian nói chung của cả giải thuật là $O(N\log\log N + Q\log N)$.

Ta cũng có thể lưu lại thêm cả số mũ của ước nguyên tố nhỏ nhất cùng với ước đó của từng số. Cách làm này sẽ có độ phức tạp là $O(N\log N + Q\log\log N)$ thời gian, và tốn thêm $O(N)$ không gian so với cách đã trình bày ở trên.

### Bài toán 3: Đếm tổng số lượng ước trên một khoảng

**Đề bài**: Cho một số nguyên dương $N$. Tính: $\sum_{i = 1}^{N}{\tau(i)}$ với $\tau(x)$ là số ước của $x$.

Thử áp dụng hai hướng giải quyết ở trên, ta thu được độ phức tạp lần lượt là $O(N\sqrt[3]{N})$ và $O(N\text{log }N)$. Tuy vậy, bài toán này còn có một lời giải tốt hơn, có thời gian chạy dưới mức tuyến tính.

Dễ thấy với mỗi số $d$, sẽ tồn tại $\left\lfloor\frac{N}{d}\right\rfloor$ bội của $d$ trong đoạn $[1, N]$. Vì vậy, nếu liệt kê tất cả các ước của các số từ $1$ tới $N$, số $d$ sẽ xuất hiện $\left\lfloor\frac{N}{d}\right\rfloor$ lần.

Do vậy, kết quả của bài toán sẽ trở thành:
$$\sum_{i = 1}^{N}{\tau(i)} = \sum_{d = 1}^{N}{\left\lfloor\frac{N}{d}\right\rfloor}$$

Tổng trên có thể được tính một cách dễ dàng trong $O(n)$. Tuy nhiên, dựa vào nhận xét sau, ta có thể tối ưu tính toán xuống $O(\sqrt{N})$:

**Nhận xét**: Với $d \leq \left\lfloor\sqrt{N}\right\rfloor$, phép tính $\left\lfloor\frac{N}{d}\right\rfloor$ nhận giá trị khác nhau với mỗi giá trị của $d$. Với $d > \left\lfloor\sqrt{N}\right\rfloor$, phép tính này nhận tổng cộng $\left\lfloor\sqrt{N}\right\rfloor$ hoặc $\left\lfloor\sqrt{N}\right\rfloor - 1$ giá trị khác nhau, các giá trị này không vượt quá $\left\lfloor\sqrt{N}\right\rfloor$ (Xem chứng minh nhận xét này tại [đây](https://math.stackexchange.com/questions/1069460/how-many-distinct-values-of-floorn-i-exists-for-i-1-to-n)).

Dựa vào nhận xét trên, ta chỉ cần tính tổng $\left\lfloor\frac{N}{d}\right\rfloor$ tới $d = \left\lfloor\sqrt{N}\right\rfloor$, còn lại với mỗi $\left\lfloor\frac{N}{d}\right\rfloor$ ta đếm xem có bao nhiêu lần giá trị này xuất hiện rồi cộng vào tổng tích luỹ.

```cpp=
long long accCountDiv(long long n) {
    long long ret = 0;
    for (int i = 1; 1ll * i * i <= n; i ++)
        ret += n / i;
    for (int i = 1; i < n / (int)sqrt(n); i ++)
        ret += 1ll * (n / i - n / (i + 1)) * i;
    return ret;
}

void solution() {
    long long n;
    cin >> n;
    cout << accCountDiv(n);
}
```

## Bài toán tính tổng các ước

**Đề bài 1**: Cho một số nguyên dương $N$. Tính tổng các ước của $N$.

**Đề bài 2**: Cho một số nguyên dương $N$. Cho $Q$ truy vấn. Ở truy vấn thứ $i$, cần tìm tổng các ước của số $A_i$ với $A_i < N$.

Một cách rất tự nhiên, ta có một lời giải đơn giản cho bài toán này giống như khi tìm số ước:

```cpp=
int divSum(int n) {
    int ret = 0;
    for (int i = 1; i * i <= n; i ++) {
        ret += (i + n / i) * (n % i == 0);
        if (i * i == n) ret -= i;
    }
    return ret;
}
```

Độ phức tạp thời gian của giải thuật trên là $O(\sqrt{N})$.

Tương ứng với cách thứ hai của bài toán trên, hàm tổng các ước cũng có một tính chất đặc biệt:

**Định lý**: Nếu một số $N$ được phân tích ra thừa số nguyên tố thành: $N = \prod_{i = 1}^{k}{p_i^{m_i}} = p_1^{m_1} \times p_2^{m_2} ... \times p_k^{m_k}$ với $p_i$ là các số nguyên tố, $m_i$ là các số nguyên dương thì tổng các ước của $N$ là:
$$\sigma(N) = \prod_{i = 1}^{k}{\frac{p_i^{m_i+1}-1}{p_i-1}}$$

:::spoiler **Chứng minh (nhấn để hiện)**:

Mọi ước $d$ của $N$ khi phân tích thành thừa số nguyên tố sẽ có dạng: 
$$d = \prod_{i = 1}^{k}{p_i^{\mu_i}}$$
với $0 \leq \mu_i \leq m_i$.
Ta có: 
$$\sigma(N) = \sum_{\mu_1=0}^{m_1}{\sum_{\mu_2=0}^{m_2}{\dots\sum_{\mu_k=0}^{m_k}{(p_1^{\mu_1}p_2^{\mu_2}\dots p_k^{\mu_k})}}}$$
$$\Rightarrow \sigma(N) = \sum_{\mu_1=0}^{m_1}{p_1^{m_1}}\times\sum_{\mu_2=0}^{m_2}{p_2^{m_2}}\times\dots\times\sum_{\mu_k=0}^{m_k}{p_k^{m_k}}$$
Biết rằng $a^n-1=(a-1)\sum\limits_{i=0}^{n-1}{a^i}$, do đó:
$$\sigma(N) = \left(\frac{p_1^{m_1+1}-1}{p_1-1}\right)\left(\frac{p_2^{m_2+1}-1}{p_2-1}\right)\dots\left(\frac{p_k^{m_k+1}-1}{p_k-1}\right)$$
$$\Rightarrow \sigma(N) = \prod_{i = 1}^{k}{\frac{p_i^{m_i+1}-1}{p_i-1}}$$

:::

Với tính chất này, ta dễ dàng sử dụng sàng nguyên tố để tính tích trên với từng thừa số nguyên tố. Tuỳ vào bài toán mà độ phức tạp phù hợp sẽ là $O(\sqrt{N}\log\log\sqrt{N})$ hoặc $O(N\log\log N + Q\log N)$.

Cải tiến $O(\sqrt[3]{N})$ không thể áp dụng để tính tổng do nó không cho ta biết cụ thể các ước. Tuy nhiên, bài toán tính tổng các ước của một số duy nhất cho trước vẫn có thể giải trong $O(\sqrt[4]{N})$ bằng [thuật toán rho của Pollard](https://cp-algorithms.com/algebra/factorization.html#pollards-rho-algorithm).

## Chú ý thêm

-   Độ phức tạp thời gian của các giải thuật cho cả hai bài toán cũng phụ thuộc vào các sàng nguyên tố được sử dụng. Một số cải tiến của sàng nguyên tố cũng làm tăng thêm hiệu quả của các thuật trên.
-   Hàm $\sigma(x)$ (tổng các ước) là một [hàm nhân tính](https://wiki.vnoi.info/algo/math/multiplicative-function). Cụ thể, với hai số nguyên dương $x$ và $y$ nguyên tố cùng nhau, ta có $\sigma(x)\sigma(y) = \sigma(xy)$. Dựa vào tính chất này, nếu gặp khó khăn trong việc nhớ công thức tính $\sigma(N)$ dựa vào phân tích thừa số nguyên tố của $N$, ta có thể thử suy nghĩ lại với hướng trong bài viết đã liên kết.
-   Hàm $\sigma_k(N) = \sum\limits_{d|N}{d^k}$ cũng là một hàm nhân tính và có thể tính được bằng cách phân tích ra thừa số nguyên tố. Họ hàm này gọi là [hàm ước số](https://en.wikipedia.org/wiki/Divisor_function) và cũng có một số tính chất đặc biệt. Với bài viết này, ta có $k=0$ (hàm đếm số ước) và $k=1$ (hàm tổng các ước).
-   Các số thoả mãn $N = 2\sigma(N)$ được gọi là [số hoàn thiện (perfect number)](https://en.wikipedia.org/wiki/Perfect_number) (hoặc hoàn chỉnh, hoàn hảo, ... tuỳ cách dịch). Một tính chất thú vị của loại số này là: Các số hoàn thiện chẵn có dạng $2^{p-1}(2^p - 1)$, với điều kiện $p$ và $2^p - 1$ đều là số nguyên tố.

## Bài tập áp dụng

-   [Codeforces - Divisions](https://codeforces.com/gym/100753/attachments) (Bài F)
-   [CSES - Counting Divisors](https://cses.fi/problemset/task/1713)
-   [CSES - Sum of Divisors](https://cses.fi/problemset/task/1082)
-   [CSES - Divisor Analysis](https://cses.fi/problemset/task/2182)
-   [VNOJ - Educational Backtracking: Số ước số](https://oj.vnoi.info/problem/backtrack_h)

## Tài liệu tham khảo

-   [himanshuaju (Codeforces) - Counting Divisors of a Number in [tutorial]](https://codeforces.com/blog/entry/22317).
-   [Toán học Việt Nam - Chứng minh định lí về hàm tổng các ước số nguyên dương](https://www.mathvn.com/2020/01/chung-minh-inh-li-ve-ham-tong-cac-uoc.html)
-   [USACO Guide - Solution - Sum of Divisors (CSES)](https://usaco.guide/problems/cses-1082-sum-of-divisors/solution)
