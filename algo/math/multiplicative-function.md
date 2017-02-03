# Hàm nhân tính

**Tác giả**: RR

[[_TOC_]]

Trong bài viết này, mình sẽ giới thiệu về hàm nhân tính cũng như ứng dụng của nó trong Competitive Programming (lập trình thi đấu).


# Định nghĩa

Một hàm $f(n), n \in N$ được coi là **hàm nhân tính** ([Multiplicative Function](https://crypto.stanford.edu/pbc/notes/numbertheory/mult.html)) nếu:
Với mọi cặp số nguyên tố cùng nhau $n, m \in N$ ta có $f(mn)=f(m)f(n)$.


# Ví dụ

## Số ước

Đặt $f(n)$ là số ước của $n$. Ta có:

```
f(1) = 1
f(2) = 2
f(3) = 2
f(4) = 3
f(5) = 2
f(6) = 4
f(7) = 2
f(8) = 4
f(9) = 3
f(10) = 4
```

Giờ ta xét bài toán sau:

> Cho số N không quá 10^5. Tính tất cả các f(i) với i <= N.

Để làm những bài dạng này, ta sẽ có 3 bước:

1. Chứng minh $f$ là hàm nhân tính.
2. Tìm công thức cho $f(p^k)$ với p là số nguyên tố.
3. Dùng sàng để tính $f$ trong $O(N*logN)$.

Nếu bạn chưa biết sàng có thể đọc [[ở đây|translate/topcoder/Mathematics-for-Topcoders]].


### Bước 1

Ta có thể chứng minh hàm $f$ là hàm nhân tính như sau:

- Xét $m$ và $n$ nguyên tố cùng nhau.
- Xét $a$ là một ước của $m$ và $b$ là một ước của $n$. Như vậy $a \* b$ là một ước của $m \* n$.
- Với 2 cặp ước khác nhau: $(a1, b1)$ và $(a2, b2)$, ta có thể chứng minh $a1 \* b1$ khác $a2 \* b2$ do $m$ và $n$ nguyên tố cùng nhau.

Do đó, $f(m \* n) = f(m) \* f(n)$.


### Bước 2

Với một số nguyên tố $p$, ta có $f(p^k) = k + 1$, do các ước của $p^k$ là $1, p, p^2, ..., p^k$.


### Bước 3

Đầu tiên, ta dùng sàng để:

1. Biết được số nào là số nguyên tố.
2. Với mỗi số không phải nguyên tố, tìm được 1 ước nguyên tố.
3. Từ 2, ta nhanh chóng kiểm tra được 1 số có dạng $p^k$ hay không.

Như vậy, ta có thể cài đặt như sau:

```cpp
const int MN = 1e6 + 11;

int sieve[MN];         // Sàng số nguyên tố. Sau khi sàng:
                       // - sieve[i] = 0 nếu i là số nguyên tố
                       // - ngược lại sieve[i] = một ước bất kỳ của i.
pair<int,int> pk[MN];  // Nếu i có dạng p^k, pk[i] = {p, k}.
                       // Ngược lại, pk[i] = {-1, 0}
int ndiv[MN];          // ndiv[i] = Số ước của i.

int main() {
    // Sàng số nguyên tố
    for (int i = 2; i <= 1000; i++)  // số không nguyên tố có 1 ước <= 10^3.
        if (!sieve[i]) {
            for (int j = i*i; j <= 1000000; j += i)
                sieve[j] = i;
        }

    ndiv[1] = 1;

    for (int i = 2; i <= 1000000; i++) {
        if (!sieve[i]) {
            // i là số nguyên tố.
            pk[i] = make_pair(i, 1);
            ndiv[i] = 2;
        }
        else {
            int p = sieve[i];  // p là ước bất kỳ của i.

            if (pk[i/p].first == p) {  // i = p^k
                pk[i] = make_pair(p, pk[i/p].second + 1);
                ndiv[i] = pk[i].second + 1;  // ndiv[p^k] = k+1.
            }
            else {
                pk[i] = make_pair(-1, 0);
                // Phân tích i = u*v, với gcd(u, v) = 1.
                int u = i, v = 1;
                while (u % p == 0) {
                    u /= p;
                    v = v * p;
                }
                ndiv[i] = ndiv[u] * ndiv[v];
            }
        }
    }
}

```


# Dirichlet Convolution

Việc chứng minh trực tiếp một hàm là hàm nhân tính như ví dụ trên không hề đơn giản. Chẳng hạn, bạn hãy thử chứng minh hàm $f(n)$ là hàm nhân tính, với $f(n)$ là tổng các ước của số $n$. Dĩ nhiên bạn có thể chứng minh trâu bò bằng cách viết ra một đống công thức, tuy nhiên ở mục này mình sẽ hướng dẫn các bạn một phương pháp kỳ diệu hơn.

Với 2 hàm $f$ và $g$ là hàm nhân tính, ta có một hàm nhân tính mới $f \* g$:

$$
(f \* g)(n) = \sum_{d_1\*d_2=n}{f(d_1)\*g(d_2)}
$$

Một cách biểu diễn khác là:

$$
(f \* g)(n) = \sum_{d | n}{f(d)\*g(n/d)}
$$

Các bạn chú ý kí hiệu $d | n$ nghĩa là $n$ chia hết cho $d$.

Để hiểu thêm về công thức trên, ta xét vài ví dụ:

## Ví dụ 1

Xét hàm $f(n) = 1$ và $g(n) = 1$. Rõ ràng $f$ và $g$ đều là hàm nhân tính.

$$
(f \* g)(n) = \sum_{d | n}{f(d) * g(n/d)} = \sum_{d | n}{1}
$$

Như vậy $(f \* g)(n)$ là số ước của số $n$ và là hàm nhân tính.

## Ví dụ 2

Xét hàm $f(n) = n$ và $g(n) = 1$. Rõ ràng $f$ và $g$ đều là hàm nhân tính.

$$
(f \* g)(n) = \sum_{d | n}{f(d) * g(n/d)} = \sum_{d | n}{d}
$$

Như vậy $(f \* g)(n)$ là tổng các ước của $n$ và là hàm nhân tính.

Tổng quát hơn, với hằng số $k$ bất kỳ, hàm $f(n) = \sum_{d | n}{d^k}$ là hàm nhân tính.


# Tổng kết

Như vậy, nếu bạn chứng minh được một hàm $f$ là hàm nhân tính, và tìm được công thức $O(1)$ cho $f(p^k)$ thì sẽ dễ dàng tính được tất cả các giá trị $f(i), i \le N$ trong $O(N*logN)$.

Mình xin đưa ra một danh sách những hàm nhân tính thường gặp:

- $f(n) = 1$
- $id(n) = n$
- $id_k(n) = n^k$
- $gcd(n, k)$ với k là hằng số
- $phi(n)$: số số nguyên tố cùng nhau với $n$ và nhỏ hơn hoặc bằng $n$ (Phi hàm Euler)
- $mobius(n)$: Hàm mobius thường được dùng trong các bài toán đếm sử dụng nguyên lý bù trừ:
  - Nếu $n$ là số chính phương, $mobius(n) = 0$.
  - Nếu $n$ có lẻ ước nguyên tố, $mobius(n) = -1$.
  - Nếu $n$ có chẵn ước nguyên tố, $mobius(n) = 1$. Chú ý $mobius(1) = 1$.
- $f(n) = \sum{d |n}{d}$ là tổng các ước của $n$.
- $f_k(n) = \sum{d | n}{d^k}$ với $k$ là hằng số.

# Bài luyện tập

- [CF #391 - E](http://codeforces.com/contest/757/problem/E)


# Reference

- [Wikipedia](https://en.wikipedia.org/wiki/Multiplicative_function)
