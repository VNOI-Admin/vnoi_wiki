---
title: Định lý thặng dư Trung Hoa
description: 
published: true
date: 2025-11-29T11:34:23.250Z
tags: 
editor: markdown
dateCreated: 2025-01-05T09:26:30.948Z
---

# Định lý Thặng dư Trung Hoa (CRT)
**Tác giả:**
- Nguyễn Đức Kiên - Đại học Công nghệ - ĐHQGHN

**Reviewer:**
- Lê Minh Hoàng - Đại học Khoa học Tự nhiên, ĐHQG-HCM
- Nguyễn Minh Nhật - Trường THPT chuyên Khoa học Tự nhiên, ĐHQGHN
- Đoàn Gia Huy - Trường THPT chuyên Khoa học Tự nhiên, ĐHQGHN

## Kiến thức cần biết

Để có trải nghiệm tốt nhất khi đọc bài viết này, bạn đọc nên nắm vững kiến thức về:
- [Phép chia và modulo cơ bản](/algo/math/modulo)
- [Thuật toán Euclid và thuật toán Euclid mở rộng](/algo/algebra/euclid)

## Mở đầu
![crt1.jpg](/algo/math/crt1.jpg)
_Ảnh lấy từ báo Danviet_

Bài viết sẽ mở đầu bằng bài toán "Hàn Tín điểm binh", được chép lại trong quyển hạ sách "Tôn Tử toán kinh". Đây cũng là lý do cách giải bài toán lại được gọi là "Định lý Thặng dư Trung Hoa".

Hàn Tín là một danh tướng nổi tiếng của Trung Quốc thời Hán Sở tranh hùng. Tên tuổi ông gắn bó với nhiều câu chuyện thú vị, trong đó có một bài toán với tên gọi "Hàn Tín điểm binh". 

Tương truyền, để kiểm đếm số binh sĩ dưới quyền, Hàn Tín đã nghĩ ra một cách. Ông cho quân lính xếp hàng ba (mỗi hàng ba người), hàng năm, hàng bảy rồi ghi các số lẻ tương ứng và suy ra số lính. 

Giả sử số người lẻ ra khi xếp hàng ba, hàng năm, hàng bảy lần lượt là $a$, $b$, $c$. Gọi số lính cần tìm là $x$. Khi đó, sử dụng phép toán modulo hiện đại, ta biểu diễn được các điều kiện của $x$: 
$$
\begin{cases}x\equiv a\pmod 3\\ x\equiv b\pmod 5\\ x\equiv c\pmod 7\end{cases}
$$


Lời giải đơn giản nhất là ... mò các bội của $7$, cộng thêm $c$ rồi kiểm tra các điều kiện còn lại. Trình Đại Vỹ thời  Minh có nhắc đến một lời giải có thể tóm tắt lại bằng công thức $x = 35a+21b+15c+105k$ với $k$ là một số nguyên phù hợp với thực tế.

Trở về lập trình thi đấu, đôi khi ta sẽ gặp những bài toán kiểu như trên, nhưng với số điều kiện và dữ liệu đầu vào khủng khiếp hơn nhiều. Lúc này, ta không thể "mò" như cách làm trên, và cũng không thể trông đợi vào một công thức "trên trời rơi xuống" để tìm ra nghiệm. Sử dụng các công cụ hiện đại, ta sẽ có cách để giải bài toán này.

## Bài toán Giải hệ phương trình đồng dư

**Đề bài**: [LQDOJ - Hàn Tín điểm binh](https://lqdoj.edu.vn/problem/hantin)

Giải hệ gồm $n$ phương trình đồng dư ẩn $x$ như sau: 
$$
\begin{cases}x\equiv a_1\pmod{m_1}\\ x\equiv a_2\pmod{m_2}\\ ...\\x\equiv a_n\pmod{m_n}\end{cases}\tag{*}
$$
 trong đó $a_1, ..., a_n, m_1, m_2, ..., m_n$ là các số nguyên bất kỳ sao cho  $\gcd(m_i, m_j) = 1$ với mọi $i, j\in[1, n], i \neq j$.

Dễ thấy nếu $x$ là một nghiệm của (\*) thì các giá trị $x + k\times\text{lcm}(m_1, m_2, ..., m_n)$ cũng là nghiệm của (\*). Vì vậy, thông thường các bài toán chỉ yêu cầu ta tìm nghiệm dương nhỏ nhất thoả mãn phương trình.

## Định lý thặng dư Trung Hoa

### Các biến phụ được sử dụng

Để thuận tiện, trong toàn bộ bài viết này tác giả sẽ sử dụng các ký hiệu sau:
- $M$ là tích của các $m_i$ với $\forall i\in[1, n]$: $M = \prod\limits_{i = 1}^nm_i$
- $M^*$ là bội chung nhỏ nhất của các $m_i$ với $\forall i\in[1, n]$: $M^* = \text{lcm}(m_1, m_2, ..., m_n)$.
- $p_i = \frac{M}{m_i}$ với $\forall i\in[1, n]$. Nói cách khác, $p_i$ là tích của các $m_j$ với $j\in[1, n], j\neq i$
- $p_i'$ là một giá trị nghịch đảo modulo $m_i$ của $p_i$ với $\forall i\in[1, n]$: $p_i' \equiv p_i^{-1}\pmod{m_i}$

### Ý tưởng

Ta có thể xây dựng nghiệm của phương trình theo hướng sau: Tạo ra một tổng gồm nhiều số hạng, sao cho các số hạng này thoả mãn cả hai điều kiện:
- Mỗi số hạng chỉ thoả mãn một phương trình tương ứng với nó
- Mỗi số hạng đều chia hết cho tất cả các modulo của các phương trình khác. Như vậy nó sẽ không gây ảnh hưởng đến số dư của các phương trình còn lại

Nói cách khác, nghiệm $x$ của ta sẽ có dạng $x = \sum\limits_{i = 1}^nf_i$ , trong đó mỗi $f_i$ đều thoả mãn: 
$$
\begin{cases}f_i\equiv a_i \pmod{m_i} & \\ f_i\equiv 0 \pmod{m_j} & \forall j\in[1, n], j\neq i\end{cases}
$$
 

#### Xây dựng các số hạng $f_i$ thoả mãn điều kiện thứ nhất

Xét phương trình 
$$
x\equiv a_i\pmod{m_i}\tag{1}
$$
 

Với ý tưởng xây dựng nghiệm như đã nói ở trên, $f_i$ cần phải thoả mãn (1). Dễ thấy $x = a_i$ thoả mãn (1), nên ta sẽ bắt đầu với $f_i = a_i$.

#### Xây dựng các số hạng $f_i$ thoả mãn điều kiện thứ hai

Để $f_i$ thoả mãn điều kiện thứ hai, cách đơn giản nhất là nhân hết các modulo $m_i$ khác vào nghiệm. Như vậy ta thu được 
$$
f_i = a_i\prod\limits_{j\in[1, n], j\neq i}m_j = a_ip_i
$$


Sau khi nhân xong, sẽ không có gì xảy ra nếu $a_i = 0$. Nhưng nếu $a_i \neq 0$, số dư của $f_i$ khi chia cho $m_i$ cũng bị nhân lên một lượng tương ứng và không còn là $a_i$ nữa. Lúc này, ta cần tìm được một số nguyên $k$ sao cho: 
$$
\begin{align} && a_ip_ik & \equiv   a_i && \pmod{m_i}\\\Leftrightarrow && p_ik & \equiv   1 &&\pmod{m_i} \end{align}
$$


Do $\gcd(p_i, m_i) = 1$, số $k$ như vậy chắc chắn tồn tại; số đó chính là $p'_i$. Việc nhân thêm $p'_i$ vào $f_i$ không làm thay đổi tính chia hết của $f_i$ với các modulo $m_j$ khác $m_i$. Tới bước này, ta đã có $f_i = p_ip'_ia_i$.

#### Xây dựng nghiệm của hệ

Bằng cách làm hoàn toàn tương tự như trên cho các phương trình khác trong hệ, ta sẽ xây dựng các số hạng $f_i$ còn lại. Cộng các số hạng đó lại, ta sẽ được một nghiệm $x$ thoả mãn phương trình là 
$$
x = \sum_{i = 1}^nf_i= \sum_{i = 1}^np_ip_i'a_i
$$


Nhắc lại, nếu một số $x$ là nghiệm của (\*) thì mọi số $x + kM^*$ cũng sẽ là nghiệm của (\*). Thêm vào đó, do các modulo nguyên tố cùng nhau đôi một nên $M^* = M$. Như vậy, (\*) sẽ có nghiệm là: 
$$
x \equiv \sum_{i = 1}^np_ip_i'a_i\pmod{M}
$$


Đây chính là công thức nghiệm được đưa ra bởi định lý Thặng dư Trung Hoa.

#### Nội dung định lý thặng dư Trung Hoa

Ngoài đưa ra công thức nghiệm, định lý thặng dư Trung hoa cũng khẳng định công thức nghiệm trên là duy nhất:

**Định lý Thặng dư Trung Hoa** (Chinese Remainder Theorem, CRT): Hệ phương trình (\*) có họ nghiệm duy nhất là: 
$$
x \equiv \sum_{i = 1}^np_ip_i'a_i\pmod{M}
$$
 

:::spoiler **Chứng minh** (nhấn để hiện)
_Chứng minh sự tồn tại_: Do $m_1, m_2, .., m_n$ là các số đôi một nguyên tố cùng nhau nên dễ thấy với mọi $i$ thì $\gcd(p_i, m_i) = 1$. Do $p_i$ và $m_i$ nguyên tố cùng nhau nên tồn tại nghịch đảo modulo $m_i$ của p_i, chính là $p_i'$. Vì $p_ip_i'\equiv 1\pmod{m_i}$ nên 
$$
p_ip_i'a_i\equiv a_i\pmod{m_i}
$$


Xét $x = \sum\limits_{i = 1}^np_ip_i'a_i$. Ta thấy với mọi $i\neq j$ thì $p_j\ \vdots\ m_i$ do $p_j$ là tích của tất cả các $m_{i'}$ với ${i'}$ khác $j$. Vì vậy, với mọi $i$ ta có 
$$
x\equiv a_i\pmod{m_i}
$$


Vậy $x$ là một nghiệm của (\*).

_Chứng minh sự duy nhất_: Giả sử $x$ và $y$ là hai số nguyên thoả mãn (\*). Với mọi $i$, ta đều có $x\equiv y\equiv a_i\pmod{m_i}$. Lấy bội chung nhỏ nhất của tất cả các đồng dư thức dạng trên ta được 
$$
x\equiv y\pmod{M^*}
$$
 Do các số $m_i$ nguyên tố cùng nhau đôi một nên $M^* = M$. Như vậy 
$$
x\equiv y\pmod{M}
$$
 Vậy (\*) có nghiệm duy nhất theo modulo $M$.

:::

### Cài đặt

Với định lý Thặng dư Trung Hoa trong tay, để giải hệ phương trình đồng dư ta chỉ cần tính các giá trị $M, p_i, p'_i$ là xong.

Lưu ý rằng, không phải lúc nào $m_i$ cũng là một số nguyên tố, nên ta không thể áp dụng định lý Fermat nhỏ để tìm $p'_i$. Thay vào đó, ta phải [giải phương trình Diophantus tuyến tính](/algo/algebra/euclid#ph%C6%B0%C6%A1ng-tr%C3%ACnh-diophantus-tuy%E1%BA%BFn-t%C3%ADnh-hai-%E1%BA%A9n) sau với hai ẩn $p', y$ bằng thuật toán Euclid mở rộng: 
$$
p_ip'_i+m_iy=1
$$


```cpp=
const int MAXN = 8;
const pair <long long, long long> 
    INVALID_ROOT = {LLONG_MAX, LLONG_MAX};

// CTDL biểu diễn đồng dư thức, gồm số dư và modulo
struct Congruence {
    long long rem;
    long long mod;

    Congruence(long long __rem, long long __mod) {
        rem = __rem;
        mod = __mod;
        if (mod) {
            rem %= mod;
            if (rem < 0) {
                rem += mod;
            }
        }
    }
};

// Hàm trả về ƯCLN của a và b, biến đổi x, y thoả mãn ax + by = gcd(a, b)
long long extEuclid(long long a, long long b, 
                    long long &x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long q = a / b;
    long long r = a - b * q;
    long long x1 = 0, y1 = 0;
    long long d = extEuclid(b, r, x1, y1);
    x = y1;
    y = x1 - q * y1;
    return d;
}

// Tính nghịch đảo modulo bằng cách giải phương trình Diophantus
long long invMod(long long num, long long mod) {
    long long inv = 0;
    long long y = 0;
    extEuclid(num, mod, inv, y);
    inv %= mod;
    if (inv < 0) {
        inv += mod;
    }
    return inv;
}

// Nghiệm của phương trình là một đồng dư thức mà, đúng không?
Congruence solveCongruenceEqSet(vector <Congruence>& eqSet) {
    Congruence sol(0, 1);

    for (int i = 0; i < (int)eqSet.size(); i++) {
        sol.mod *= eqSet[i].mod;
    }

    vector <long long> p;
    vector <long long> pInv;
    for (int i = 0; i < (int)eqSet.size(); i++) {
        p.push_back(sol.mod / eqSet[i].mod);
        pInv.push_back(invMod(p[i], eqSet[i].mod));
    }

    for (int i = 0; i < (int)eqSet.size(); i++) {
        long long prod = 1;
        prod = prod * p[i] % sol.mod;
        prod = prod * pInv[i] % sol.mod;
        prod = prod * eqSet[i].rem % sol.mod;
        sol.rem += prod;
    }
    sol.rem %= sol.mod;

    return sol;
}

```

### Độ phức tạp

Với các tham số đã nêu trên, thì độ phức tạp không gian của thuật toán là $\mathcal{O}(n)$. 

Về thời gian, với mỗi phương trình ta mất $\mathcal{O}(\log(\max\{p_i, m_i\})) = \mathcal{O}(\log M)$ (vì $p_i = \frac{M}{m_i}$) cho mỗi lần giải phương trình Diophantus và $\mathcal{O}(1)$ cho các việc còn lại, do vậy ta sẽ mất $\mathcal{O}(n\log M)$ để giải hệ phương trình.

## Trường hợp modulo không nguyên tố cùng nhau

Tất cả nhưng gì ta vừa làm đều chỉ đúng với các modulo nguyên tố cùng nhau đôi một. Khi các modulo không còn nguyên tố cùng nhau, giá trị $p_i^{-1}\pmod{m_i}$ không chắc chắn tồn tại nữa, và cũng không còn khẳng định được phương trình có nghiệm.

Ta đã biết đồng dư thức có hai tính chất sau với các số nguyên $a, b, m$ bất kỳ sao cho $m\neq 0$:
- $a\equiv b\pmod{m}$ thì $a\equiv b\pmod{\frac{m}{\delta}}$, với $\delta$ là một ước bất kỳ của $m$
- $\forall i\in[1, n], a\equiv b\pmod{m_i} \Rightarrow a\equiv b\pmod{\text{lcm}(m_1, m_2, ..., m_n)}$

Do đó, ta có thể tách một phương trình thành nhiều phương trình sao cho tích các modulo của chúng bằng đúng modulo của phương trình ban đầu. Cụ thể, giả sử $m_i$ được phân tích thành $m_i = \prod_{j = 1}^k\mu_{ij}^{\pi_{ij}}$ với $\mu_{ij}$ là các số nguyên tố. Khi đó, phương trình $x\equiv a_i\pmod{m_i}$ sẽ tương đương với hệ các phương trình sau: 
$$
\begin{cases} x\equiv a_i\pmod{\mu_{i1}^{\pi_{i1}}}\\x\equiv a_i\pmod{\mu_{i2}^{\pi_{i2}}}\\...\\x\equiv a_i\pmod{\mu_{ik}^{\pi_{ik}}}\end{cases}
$$


Thực hiện tương tự với các phương trình còn lại, ta sẽ thu được một hệ các phương trình có modulo là luỹ thừa của các số nguyên tố. Lúc này, việc kiểm tra tính mâu thuẫn của các điều kiện là tương đối dễ dàng: nếu có $x\equiv r_1\pmod{\mu^{\pi_1}}$, $x\equiv r_2\pmod{\mu^{\pi_2}}$ trong đó $\mu$ là một số nguyên tố và $\pi_1 < \pi_2$, thì hệ gồm hai phương trình trên sẽ chỉ có nghiệm nếu 
$$
r_1\bmod \mu^{\pi_1} = r_2 \bmod \mu^{\pi_1}
$$
 Ngược lại, ta có thể kết luận ngay là hệ vô nghiệm.

Nếu không có cặp phương trình nào xung đột với nhau, hệ phương trình chắc chắn có nghiệm. Lúc này, dễ thấy các phương trình có modulo thuộc cùng một cơ số, chẳng hạn $\mu^1, \mu^2, ...$ kết hợp lại sẽ tương đương với phương trình có số mũ lớn nhất (xem phần ví dụ để hiểu thêm). Ta chỉ cần giữ lại phương trình này. Sau khi thực hiện bước này, ta đã có một hệ gồm các phương trình có modulo nguyên tố cùng nhau. Việc cần làm lúc này là áp dụng định lý Thặng dư Trung Hoa để giải hệ.

Chẳng hạn, xét hệ phương trình: 
$$
\begin{cases}x\equiv 1 \pmod{10} \\ x \equiv{7}\pmod{12}\end{cases}
$$
 Ta phân tích các modulo ra được: 
$$
\begin{cases}x\equiv 1 \pmod{2} \\ x\equiv 1 \pmod{5} \\ x \equiv{7}\pmod{2^2} \\ x \equiv{7}\pmod{3}\end{cases}
$$
 Xét phương trình thứ nhất và phương trình thứ ba, với $r_1 = 1, r_2 = 7, \mu = 2, \pi_1 = 1, \pi_2 = 2$, ta có $r_1\bmod \mu^{\pi_1} = r_2 \bmod \mu^{\pi_1}$. Như vậy không có mâu thuẫn nào xảy ra. Ta loại đi phương trình thứ nhất do đã có modulo $2^2$. Áp dụng định lý Thặng dư Trung Hoa cho hệ này, ta có nghiệm của phương trình là $x\equiv 31\pmod {60}$.

Đoạn chương trình dưới đây cài đặt các ý tưởng trên, sử dụng phép phân tích bằng sàng nguyên tố và lưu lại ước nhỏ nhất của các số.

```cpp=
const int MAXX = 1e6 + 1;

int minPDiv[MAXX];

// Sàng nguyên tố (nhớ gọi hàm này trước khi làm bất cứ việc gì)
void sieve() {
    for (int i = 2; i < MAXX; i ++) {
        if (minPDiv[i]) {
            continue;
        }
        minPDiv[i] = i;
        for (int j = i + i; j < MAXX; j += i) {
            minPDiv[j] = (minPDiv[j] ? minPDiv[j] : i);
        }
    }
}

// Phân tích một số ra TSNT dưới dạng tích của các luỹ thừa
vector<int> poweredPrimeDivisors(int x) {
    vector<int> ret;
    int pp = 1;
    int curPDiv = minPDiv[x];
    while (x != 1) {
        if (minPDiv[x] != curPDiv) {
            ret.push_back(pp);
            curPDiv = minPDiv[x];
            pp = curPDiv;
        } else {
            pp *= minPDiv[x];
        }
        x /= minPDiv[x];
    }
    ret.push_back(pp);
    return ret;
}

// Hàm sắp xếp các phương trình theo cơ số của modulo,
// dùng trong sort
bool compCongruenceByModuloBase(
    Congruence eq1, Congruence eq2) {
    if (minPDiv[eq1.mod] == minPDiv[eq2.mod]) {
        return eq1.mod < eq2.mod;
    }
    return minPDiv[eq1.mod] < minPDiv[eq2.mod];
}

// Tách các phương trình thành các phương trình nhỏ hơn với modulo
// nguyên tố cùng nhau
bool factor(vector<Congruence>& eqSet) {
    // Phân tích các modulo ra thừa số nguyên tố
    vector<Congruence> pEqSet;
    for (auto eq : eqSet) {
        vector<int> ppDivs = poweredPrimeDivisors(eq.mod);
        for (auto d : ppDivs) {
            pEqSet.push_back(Congruence(eq.rem, d));
        }
    }
    
    // Sắp xếp các phương trình theo cơ số của modulo
    sort(pEqSet.begin(), pEqSet.end(),
         compCongruenceByModuloBase);
    
    // Kiểm tra hệ phương trình vô nghiệm
    for (int i = 1; i < (int)pEqSet.size(); i++) {
        auto eq1 = pEqSet[i - 1];
        auto eq2 = pEqSet[i];
        if (minPDiv[eq1.mod] == minPDiv[eq2.mod]) {
            if (eq2.rem % eq1.mod != eq1.rem) {
                return 0;
            }
        }
    }
    
    // Loại bỏ các modulo nhỏ
    eqSet.clear();
    for (int i = pEqSet.size() - 1; i >= 0; i--) {
        if (eqSet.empty() || minPDiv[pEqSet[i].mod] 
            != minPDiv[eqSet.back().mod]) {
            eqSet.push_back(pEqSet[i]);
        }
    }
    return 1;
}

Congruence solveCongruenceEqSet(vector<Congruence>& eqSet) {
    if (!factor(eqSet)) {
        return Congruence(0, 0);
    }

    Congruence sol(0, 1);

    for (int i = 0; i < (int)eqSet.size(); i++) {
        sol.mod *= eqSet[i].mod;
    }

    vector <long long> p;
    vector <long long> pInv;
    for (int i = 0; i < (int)eqSet.size(); i++) {
        p.push_back(sol.mod / eqSet[i].mod);
        pInv.push_back(invMod(p[i], eqSet[i].mod));
    }

    for (int i = 0; i < (int)eqSet.size(); i++) {
        long long prod = 1;
        prod = prod * p[i] % sol.mod;
        prod = prod * pInv[i] % sol.mod;
        prod = prod * eqSet[i].rem % sol.mod;
        sol.rem += prod;
    }
    sol.rem %= sol.mod;

    return sol;
}

```

Nói về độ phức tạp, ta xét các công việc con:
- Để phân tích các modulo ra thừa số nguyên tố, sẽ có rất nhiều cách khác nhau. Nếu đặt $m = \max\limits_{i \in[1, n]}(m_i)$, cách làm trên có độ phức tạp thời gian là $\mathcal{O}(m\log\log m + n\log m)$. Còn nếu ta chỉ chuẩn bị các ước nguyên tố nhỏ nhất cho $\sqrt{m}$ số nguyên đầu tiên, ta sẽ mất $\mathcal{O}(\sqrt{m}\log\log \sqrt{m} + n\sqrt{m})$. Độ phức tạp không gian cũng vậy, hoàn toàn tuỳ thuộc vào cách chọn thuật toán phân tích. Về các thuật toán phân tích, có thể tham khảo tại [đây](/algo/math/integer-factorization).
- Sau khi phân tích, mỗi phương trình sẽ "nở" ra thành $\mathcal{O}(\log m)$ phương trình khác. Chúng ta có $\mathcal{O}(n\log m)$ phương trình. Lúc này, sẽ xuất hiện các phương trình có modulo với cơ số giống nhau (cùng giá trị $\mu$) và có thể sẽ xuất hiện mâu thuẫn. Cách tốt nhất để kiểm tra và loại trừ các cặp phương trình mâu thuẫn là sắp xếp lại các phương trình có cùng cơ số theo độ lớn của số mũ và xét từng cặp kề nhau. Độ phức tạp của bước này cũng tuỳ vào cách bạn chọn thuật sắp xếp nhưng theo cách "phổ thông" nhất (`std::sort`) là $\mathcal{O}(n\log m\log (n\log m))$ thời gian và $\mathcal{O}(n\log m)$ không gian.
- Sau khi sắp xếp và thu gọn hệ xong, trong trường hợp tệ nhất ta vẫn có $\mathcal{O}(n\log m)$ phương trình (tuy nhiên thực tế số phương trình còn lại là nhỏ hơn rất nhiều). Như vậy, độ phức tạp của công việc này sẽ là $\mathcal{O}(\sum_{i = 1}^n n\log m\log m_i) = \mathcal{O}\left(n\log m\sum_{i = 1}^n\log m_i\right) = \mathcal{O}(n\log m\log M)$ thời gian và $O(n\log m)$ không gian.

## Cách tiếp cận khác

Nếu không nhớ công thức nghiệm của hệ phương trình, ta vẫn có thể giải được hệ phương trình đồng dư chỉ bằng các phương trình Diophantus. Đặc biệt, cách làm này không hề bị ảnh hưởng bởi việc các modulo có nguyên tố cùng nhau đôi một hay không.

Với $n = 2$, ta có hệ phương trình: 
$$
\begin{cases}x\equiv a_1\pmod{m_1}\\ x\equiv a_2\pmod{m_2}\end{cases}\tag{**}
$$


Theo định lý Thặng dư Trung Hoa và những gì ta đã làm ở trường hợp modulo không nguyên tố cùng nhau đôi một, (\*\*) có thể không có nghiệm có một họ nghiệm duy nhất theo modulo $[m_1, m_2]$. Như vậy, nghiệm ta cần tìm có dạng 
$$
x\equiv a_{12}\pmod{\text{lcm}(m_1, m_2)}
$$


Dựa vào hai phương trình thành phần của (\*\*), ta có: 
$$
x = m_1t_1 + a_1 = m_2t_2 + a_2
$$
 
$$
\Leftrightarrow m_1t_1 - m_2t_2 = a_2 - a_1\tag{1}
$$


(1) là một [phương trình Diophantus tuyến tính](/algo/algebra/euclid#ph%C6%B0%C6%A1ng-tr%C3%ACnh-diophantus-tuy%E1%BA%BFn-t%C3%ADnh-hai-%E1%BA%A9n) với hai ẩn là $t_1$ và $t_2$. Nếu nó có nghiệm, 
$$
x \equiv m_1t_1 + a_1\pmod{\text{lcm}(m_1, m_2)}
$$
 là một nghiệm của (\*\*).

Với $n$ lớn, ta giải từng cặp phương trình một bằng cách quy nạp. Chẳng hạn, giả sử ta đã giải xong $i$ phương trình đầu tiên và tìm được nghiệm $x\equiv a_{1..i}\pmod{\text{lcm}(m_1, m_2, ..., m_i)}$. Khi đó ta sẽ giải hệ 
$$
\begin{cases} x & \equiv a_{1..i} & \pmod{\text{lcm}(m_1, m_2, ..., m_i)} \\ x & \equiv a_{i + 1} & \pmod{m_{i + 1}}\end{cases}\tag{***}
$$


Để ý dạng của (\*\*\*) chẳng khác gì (\*\*) cả. Ta có thể áp dụng mọi biện pháp giải (\*\*) để giải hệ này. Ta cứ tiếp tục như vậy tới khi toàn bộ phương trình đã được giải.

```cpp=
const pair <long long, long long> 
    INVALID_ROOT = {LLONG_MAX, LLONG_MAX};

Congruence solveInduction(vector <Congruence>& eqSet, int solved) {
    Congruence sol(0, 1), lastSol(0, 1);
    if (solved == 1) {
        lastSol = eqSet[0];
    } else {
        lastSol = solveInduction(eqSet, solved - 1);
    }
    if (!lastSol.mod) {
        return Congruence(0, 0);
    }
    
    // Tìm cặp số x, y để ax + by = gcd(a, b)
    pair<long long, long long> p = {0, 0};
    long long d = extEuclid(lastSol.mod, eqSet[solved].mod, 
                            p.first, p.second);
    
    // Điều kiện vô nghiệm của phương trình Diophantus
    if ((eqSet[solved].rem - lastSol.rem) % d) {
        return Congruence(0, 0);
    }

    // Đưa ra nghiệm đúng của phương trình Diophantus và
    // tìm nghiệm của hệ đến phương trình hiện tại
    sol.rem = p.first * (eqSet[solved].rem - lastSol.rem) / d 
        % (eqSet[solved].mod / d) * lastSol.mod 
        + lastSol.rem;
    sol.mod = lastSol.mod * eqSet[solved].mod / d;
    sol.rem %= sol.mod;
    if (sol.rem < 0) {
        sol.rem += sol.mod;
    }
    return sol;
}

Congruence solveCongruenceEqSet(vector <Congruence>& eqSet) {
    if (eqSet.size() == 1) {
        return eqSet.front();
    }
    return solveInduction(eqSet, eqSet.size() - 1);
}
```

Về độ phức tạp, ta đã thực hiện giải $n - 1$ phương trình Diophantus. Làm như vậy sẽ tốn $\mathcal{O}(n\log M^*)$ thời gian và $\mathcal{O}(n)$ bộ nhớ.

Nhìn chung, cách làm này có vẻ tự nhiên hơn so với việc sử dụng công thức trực tiếp. Tuy nhiên, khi cài đặt, cần phải đặc biệt chú ý xử lý các phép toán lấy số dư, đặc biệt khi giải phương trình Diophantus để tìm nghiệm.

## Chú ý thêm

- Định lý thặng dư Trung Hoa được ứng dụng trong các thuật toán sau:
    - [Tính tổ hợp moldulo $M$ với $M$ không nguyên tố](/algo/algebra/nCk#s%E1%BB%AD-d%E1%BB%A5ng-%C4%91%E1%BB%8Bnh-l%C3%BD-th%E1%BA%B7ng-d%C6%B0-trung-hoa) bằng cách phân tích modulo ra thừa số nguyên tố, tính modulo cho các thừa số nguyên tố rồi kết hợp lại.
    - [Thuật toán Garner](https://cp-algorithms.com/algebra/garners-algorithm.html): cho phép biểu diễn và tính toán trên các số rất lớn

## Bài tập áp dụng

- [Kattis - Chinese Remainder Theorem (non-relatively prime moduli)](https://open.kattis.com/problems/generalchineseremainder): bài toán chỉ có hai phương trình với modulo không nguyên tố
- [LightOJ - Monkey tradition](https://lightoj.com/problem/monkey-tradition)
- [Hackerank - Number of sequences](https://www.hackerrank.com/contests/w22/challenges/number-of-sequences)
- [Hackerank - nCr](https://www.hackerrank.com/challenges/ncr/problem): áp dụng định lý Thặng dư Trung Hoa để tính tổ hợp modulo $M$
- [Codeforces - Billards](https://codeforces.com/contest/982/problem/E)
- [UVa Online Judge - Code Feat](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2854)
- [POI 2016 - Arkanoid](https://szkopul.edu.pl/problemset/problem/O730xgZEVynTWBmscBinhMbD/site/?key=statement)
- [Codeforces - Remainders Game](https://codeforces.com/problemset/problem/687/B)
- [Google Code Jam - Golf Gopher](https://github.com/google/coding-competitions-archive/blob/main/codejam/2019/round_1a/golf_gophers/statement.pdf)

## Tài liệu tham khảo

- [CP Algorithms - Chinese Remainder Theorem](https://cp-algorithms.com/algebra/chinese-remainder-theorem.html)
- [USACO Guide - Extended Euclidean Algorithm](https://usaco.guide/adv/extend-euclid?lang=cpp)
- [Codeforces - [Tutorial] Chinese Remainder Theorem](https://codeforces.com/blog/entry/61290) (Tác giả: Valiors)
- [Tạp chí Pi](https://pi.edu.vn/detail-news/toan-phap-dai-thanh-cuon-sach-toan-viet-nam-dau-tien-113.html) (cho phần lịch sử của thuật toán)

