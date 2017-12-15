# Số học 4.5 - Nghịch đảo modulo

[[_TOC_]]

# Định nghĩa:

Xét số nguyên dương $m$. Xét các số nguyên trên modulo $m$ (từ 0 đến $m-1$).

Với một số nguyên $a$, ta gọi nghịch đảo modulo $m$ (modular multiplicative inverse) của $a$ là $a^{-1}$ là số nguyên thoả mãn:

$a \* a^{-1} \equiv 1 \; \pmod{m}$

Ta cần chú ý rằng không phải lúc nào $a^{-1}$ cũng tồn tại. Ví dụ, với $m = 4, a = 2$, ta không thể tìm được $a^{-1}$ thoả mãn đẳng thức trên.

Có thể chứng minh rằng $a^{-1}$ luôn luôn tồn tại nếu $gcd(a, m) = 1$.

Trong bài viết này, mình sẽ trình bày 2 cách khác nhau để tìm nghịch đảo modulo, dựa trên 2 thuật toán đã được trình bày ở các bài viết trên VNOI:

- [[Extended Euclid|translate/he/So-hoc-Phan-1-Modulo-gcd]]
- [[Tính a^b % c bằng chia để trị|translate/he/Number-Theory-3]]

# Extended Euclid

Như đã trình bày trong bài viết [[Số học 1|translate/he/So-hoc-Phan-1-Modulo-gcd]], nếu $gcd(a, m) = 1$, ta luôn luôn tìm được 2 số nguyên x và y thoả mãn:

$a \*x + m \* y = 1$.

Vì ta đang làm việc trên modulo $m$, ta có thể bỏ $m \* y$ và viết lại đẳng thức trên như sau:

$a \* x \equiv 1 \pmod{m}$.

Do đó, $x$ chính là $a^{-1}$.

Cài đặt:

```cpp
int x, y;
int g = extended_euclidean(a, m, x, y);
if (g != 1) cout << "No solution!";
else {
    x = (x % m + m) % m;
    cout << x << endl;
}
```

# Tính nghịch đảo modulo bằng a^b % c

Khi $gcd(a, m) = 1$, theo định lý Euler, ta có:

$a^{phi(m)} \equiv 1 \pmod{m}$.

Với hàm Euler đã được giải thích ở bài viết [[Số học 4|translate/he/Number-Theory-4]].

Trong trường hợp $m$ là số nguyên tố, $phi(m) = m - 1$, nên ta có:

$a^{m-1} \equiv 1 \pmod{m}$.

Nhân cả 2 vế với $a^{-1}$, ta được:

- Với $m$ bất kỳ, $a^{phi(m) - 1} \equiv a^{-1} \pmod{m}$,
- Với $m$ nguyên tố, $a^{m-2} \equiv a^{-1} \pmod{m}$.

Như vậy, ta có thể dùng thuật toán [[Tính a^b % c bằng chia để trị|translate/he/Number-Theory-3]] để tính nghịch đảo modulo với độ phức tạp $O(\log{m})$.