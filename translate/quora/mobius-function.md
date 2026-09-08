---
title: Hàm Mobius
description: 
published: true
date: 2024-09-23T05:12:53.289Z
tags: 
editor: markdown
dateCreated: 2023-12-25T11:06:46.145Z
---

# Hàm Mobius

Nguồn: [Quora](https://www.quora.com/profile/Surya-Kiran/Posts/A-Dance-with-Mobius-Function)

Trong bài viết này mình sẽ giới thiệu với các bạn một chủ đề vô cùng thú vị trong số học - Hàm nghịch đảo Mobius, cũng như cách ứng dụng để giải quyết một số bài toán.

Một lời khuyên dành cho bạn đọc là các bạn nên tự chứng minh những công thức được đề cập để hiểu rõ hơn bản chất bài toán.

# Các định nghĩa

Trước khi bắt đầu, các bạn hãy ghi nhớ một số định nghĩa sau đây để việc tiếp thu những kiến thức ở dưới được dễ dàng hơn.

Một hàm $f(n): \mathbb{N} \rightarrow \mathbb{C}$ được coi là **hàm nhân tính** ([Multiplicative Function](https://crypto.stanford.edu/pbc/notes/numbertheory/mult.html))  nếu với mọi cặp số nguyên tố cùng nhau $n, m \in \mathbb{N}$ ta có $f(mn)=f(m)f(n)$

Một số $n$ phân tích ra thừa số nguyên tố sẽ có dạng $n={p_1}^{a_1}{p_2}^{a_2}{p_3}^{a_3}\ldots{p_r}^{a_r}$, với $p_i$ là ước nguyên tố của $n$.

Ký hiệu $a \mid b$ có nghĩa là $a$ là ước của $b$, hay $b$ chia hết cho $a$

**Hàm định danh Dirichlet** $e(n)$ (Dirichlet identity function):

- $e(n)=1$ với $n=1$

- $e(n)=0$ với $n > 1$

$I(n)=1$ với mọi $n \in \mathbb{N}$

$\mathrm{id}(n)=n$ với mọi $n \in \mathbb{N}$

**Hàm Mobius** $\mu(n)$:

- $\mu(1)=1$

- $\mu(n)=0$ nếu tồn tại $a_i>1$

- $\mu(n)=(-1)^{r}$ nếu $n={p_1}{p_2}{p_3}\ldots{p_r}$, hay $a_i = 1$ với mọi $i$

- Có thể chứng minh được rằng $\mu(n)=\sum\limits_{d\mid n,d < n}\mu(d)$ với $n>1$ và tính được $\mu(n)$ bằng cách sử dụng một [thuật toán](http://codeforces.com/blog/entry/8989) tương tự với [Sàng nguyên tố](/algo/algebra/prime_sieve):
```cpp
mu[1] = 1;
for (int i = 1; i <= N; i++)
    for (int j = 2 * i; j <= N; j += i)
        mu[j] -= mu[i];
```

Vỡi mỗi $f(n)$, ta gọi hàm tổng $S_f(n)$ là tổng các $f(d)$ với $d$ là ước của $n$: $S_f(n)=\sum\limits_{d\mid n}{f(d)}$

**Phi hàm Euler** $\varphi(n)$ ([Euler totient function](https://vi.wikipedia.org/wiki/Phi_h%C3%A0m_Euler)): số lượng các số tự nhiên nhỏ hơn hoặc bằng $n$ và nguyên tố cùng nhau với $n$ (hay số lượng các số $d: 1 \leq d \leq n,\gcd(d,n)=1$). Các bạn cũng có thể sử dụng sàng để tính $\varphi(n)$:
```cpp
for (int i = 1; i <= N; i++)
    phi[i] = i;
for (int i = 2; i <= N; i++)
    if (phi[i] == i)
        for (int j = i; j <= N; j += i)
            phi[j] -= phi[j] / i;
```

# Công thức nghịch đảo Mobius (Möbius inversion formula)

Ta định nghĩa Dirichlet Convolution là một phép toán với 2 hàm $f(n)$ và $g(n)$:

$$
f * g(n)=\sum\limits_{d_1\times d_2=n}{f(d_1)g(d_2)}
$$

hay

$$
f * g(n)=\sum\limits_{d\mid n}{f(d)g\left(\frac{n}{d}\right)}
$$

Có thễ dễ dàng chứng minh phép toán này có tính giao hoán và kết hợp:

$$
f* g(n)=g* f(n)
$$

$$
(f* g)* h(n)=f*(g* h)(n)
$$

Ta có nhận xét rằng:

$$
S_f(n)=\sum\limits_{d\mid n}{f(d)}=\sum\limits_{d\mid n}{f(d)I\left(\frac{n}{d}\right)}=f* I(n)
$$

$$
S_{\varphi}(n)=\sum\limits_{d\mid n}{\varphi(d)}=\mathrm{id}(n)
$$

$$
S_{\mu}(n)=\sum\limits_{d\mid n}{\mu(d)}=I* \mu (n)=\mu * I(n)= e(n)
$$

$$
f * e(n)=\sum\limits_{d\mid n}{f\left(\frac{n}{d}\right)e(d)}=f(n)
$$

Từ đó suy ra:

$$
S_f * \mu(n)=(f * I)* \mu (n)=f* (I*\mu)(n)=f* e(n)=f(n)
$$

hay

$f(n)=\sum\limits_{d\mid n}{S_f(d)\mu \left(\frac{n}{d}\right)}$ - đây gọi là [Công thức nghịch đảo Mobius](https://en.wikipedia.org/wiki/M%C3%B6bius_inversion_formula)

# Ứng dụng

## [SPOJ - GCDEX](http://www.spoj.com/problems/GCDEX/)

Tính

$$
G=\sum\limits_{i=1}^{n} \sum\limits_{j=i+1}^{n}\gcd(i,j)\quad\quad (1)
$$

Dễ thấy cách tiếp cận đơn giản nhất cho bài toán này là duyệt tất cả các cặp $(i,j)$. Độ phức tạp của thuật toán này là $\mathcal{O}(k \times n^{2})$, với $k$ là số phép toán tối đa khi tính $\gcd$. Chúng ta sẽ đi tìm một lời giải tối ưu hơn sử dụng những kiến thức ở trên.

1. Nhận xét rằng $1 \leq \gcd(i,j) \leq n$ với mọi $1 \leq i < j \leq n$.

	Như vậy, biểu thức trên có thể viết lại thành

	$$
	G=\sum\limits_{g=1}^{n}(g\times \texttt{cnt}[g]) \quad\quad (2)
	$$

	Với $\texttt{cnt}[g]$ là số lượng cặp $(i,j)$ thỏa mãn $\gcd(i, j)=g$.

Công việc tính $\texttt{cnt}[g]$ thật sự không hề đơn giản.
Ta để ý rằng $\gcd(i,j)=g \Leftrightarrow \gcd\left(\frac{i}{g},\frac{j}{g}\right)=1$.

2. Ta viết lại $(2)$ thành

	$$
	G=\sum\limits_{g=1}^{n}(h(g)\times \texttt{cnt}[g])
	$$

	với $h(g)=g$

3. Giờ chúng ta sẽ tìm cách phân tích $h(n)$ thành hàm tổng $S$ của hàm $f(n)$ nào đó, tức là:

	$$
	h(n)=S_f(n)=\sum\limits_{d\mid n}f(d)
	$$

	Ứng dụng công thức nghịch đảo Mobius, bạn có thể tìm được:

	$$
	f(n)=h(d) * \mu(n)
	$$

	Một kết quả rất đẹp trong bài toán này là $f(n)=\varphi(n)$. Tuy nhiên, nếu không biết tính chất này thì	khi đã biết được $h(n)$ và $\mu(n)$, ta có thể tính $f(n)$ bằng sàng như sau:

  ```cpp
  for (int i = 1; i <= N; i++)
      for (int j = i; j <= N; j += i)
          f[j] += h[i] * mu[j / i];
  ```

  Đoạn code trên chạy trong thời gian $\mathcal{O}(N\log N)$ (tham khảo [Độ phức tạp thời gian](/algo/basic/computational-complexity))

4. Viết lại $(2)$ một lần nữa ta được:

	$$
	G=\sum\limits_{g=1}^{n}\left(\sum\limits_{d\mid g}f(d)\right)\times \texttt{cnt}[g]\quad\quad (3)
	$$

	$$
	\iff G=\sum\limits_{g=1}^{n}\left(\texttt{cnt}[g] \times\sum\limits_{d\mid g}f(d)\right)\quad\quad (3)
	$$

	$$
	\iff G=\sum\limits_{d=1}^{n}f(d)\times\left(\sum\limits_{g: \; d \mid g}\texttt{cnt}[g]\right)\quad\quad (4)
	$$

5. Đặt $\texttt{cnt2}[d]=\sum\limits_{g: \; d \mid g}\texttt{cnt}[g]$. Hàm này có ý nghĩa là số lượng cặp $(i,j)$ thỏa mãn $\gcd(i, j)$ là bội của $d$. Đến đây mọi việc đã đơn giản hơn rất nhiều. Các bạn chỉ cần tìm số lượng cặp $(i,j)$ mà $i$ và $j$ đều là bội của $d$. Từ $1$ đến $n$ có $\left\lfloor\frac{n}{d}\right\rfloor$ bội của $d$, nên sẽ có $\frac{\left\lfloor\frac{n}{d}\right\rfloor\left(\left\lfloor\frac{n}{d}\right\rfloor-1\right)}{2}$ cặp $(i, j)$ như vậy.

	Vậy (4) trở thành $G=\sum\limits_{d=1}^{n}\frac{\left\lfloor\frac{n}{d}\right\rfloor\left(\left\lfloor\frac{n}{d}\right\rfloor-1\right)}{2}f(d)$.

	Dễ dàng chứng minh là với $d$ chạy từ $1$ đến $n$ chỉ có $\sqrt{n}$ giá trị $\left\lfloor\frac{n}{d}\right\rfloor$ nên ta có thể duyệt từng giá trị của $\left\lfloor\frac{n}{d}\right\rfloor$ và cộng $\frac{\left\lfloor\frac{n}{d}\right\rfloor\left(\left\lfloor\frac{n}{d}\right\rfloor-1\right)}{2}\sum\limits_{k:\; \left\lfloor\frac{n}{k}\right\rfloor=\left\lfloor\frac{n}{d}\right\rfloor}f(k)$ vào kết quả. 
  Bằng tổng tiền tố các bạn có thể truy vấn được $\sum\limits_{k:\; \left\lfloor\frac{n}{k}\right\rfloor=\left\lfloor\frac{n}{d}\right\rfloor}f(k)$ trong $\mathcal{O}(1)$ và $G$ trong $\mathcal{O}(\sqrt{n})$:

```cpp
for (int i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);                                      //vị trí j xa i nhất mà n/i=n/j
    res += n / i * (n / i - 1) / 2 * (Sf[j] - Sf[i - 1]); //Sf[i]=f[1]+f[2]+f[3]+...+f[i]
}
```

Như vậy thuật toán trên có độ phức tạp $\mathcal{O}(N\log N+\sqrt{N} \times T)$ với $T$ là số test.

## Bài toán tổng quát

Bài toán tổng quát hơn của bài toán trên là tính $G=\sum\limits_{i=1}^{n} \sum\limits_{j=i+1}^{n}h(\gcd(i,j))$ với $h$ (nên) là một hàm nhân tính. Ví dụ muốn tính $G=\sum\limits_{i=1}^{n} \sum\limits_{j=i+1}^{n}\gcd^{3}(i,j)$ thì $h(n)=n^{3}$.

Các bước tính toán gần như giống với bài toán trên.

## Coprime Triples

[Đề bài](https://www.codechef.com/problems/COPRIME3)

Cho dãy số $a_1,a_2,\ldots,a_n$. Tìm số bộ ba $(i,j,k)$ ($1 \leq i < j < k \leq n$) có $\gcd(a_i,a_j,a_k)=1$. $n \leq 10^{5}$ và $a_i \leq 10^{6}$

Ta đưa đề bài này về bài toán: tính $G=\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}\sum\limits_{k=j+1}^{n}e(\gcd(a_i,a_j,a_k))$

1. Viết lại biểu thức trên:

	$G=\sum\limits_{g=1}^{\texttt{maxA}}h(g)\texttt{cnt}[g]$, ở đây $\texttt{cnt}[g]$ là số lượng bộ ba $(i,j,k)$ có $\gcd(a_i,a_j,a_k)=1$. $\texttt{maxA}=10^{6}$

2. Tìm $f(n)$ bằng công thức nghịch đảo Mobius.

	Ở bài toán này $f(n)$ chính bằng $\mu(n)$, việc chứng minh mình cũng xin nhường lại cho bạn đọc.

	Lúc này $G=\sum\limits_{g=1}^{\texttt{maxA}}\left(\sum\limits_{d\mid g}f(d)\right)\times\texttt{cnt}[g]$.

	$\Leftrightarrow G=\sum\limits_{d=1}^{\texttt{maxA}}f(d)\texttt{cnt2}[g]$.

3. Tính $\texttt{cnt2}[d]$ là số bộ ba $(i,j,k)$ có $\gcd(a_i,a_j,a_k)$ là bội của $d$.

4. Duyệt lại $d$ và tính $G$.

# Một số bài luyện tập

- [https://www.codechef.com/JULY10/problems/LCM/](https://www.codechef.com/JULY10/problems/LCM/)

- [http://www.codechef.com/COOK29/problems/EXGCD](http://www.codechef.com/COOK29/problems/EXGCD)

- [https://www.hackerrank.com/challenges/hyperrectangle-gcd](https://www.hackerrank.com/challenges/hyperrectangle-gcd)

- [http://www.spoj.com/problems/LCMSUM/](http://www.spoj.com/problems/LCMSUM/)

- [http://www.spoj.com/problems/GCDEX2/](http://www.spoj.com/problems/GCDEX2/)

Nếu các bạn muốn tìm hiểu sâu và đầy đủ hơn về các bài toán liên quan thì có thể tham khảo [http://mathcircle.berkeley.edu/original/Multiplicative.pdf](http://mathcircle.berkeley.edu/original/Multiplicative.pdf)
