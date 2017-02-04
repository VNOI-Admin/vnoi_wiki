# Hàm Mobius

**Tác giả**: RR

[[_TOC_]]

Trong bài viết này mình sẽ tiếp tục giới thiệu về hàm Mobius. Ở trong bài viết về [[Hàm nhân tính|algo/math/multiplicative-function]] mình đã giới thiệu hàm Mobius là một hàm nhân tính và có ứng dụng trong những bài toán sử dụng nguyên lý bù trừ. Trong bài viết này mình sẽ đi sâu vào ứng dụng của hàm Mobius.

# Định nghĩa:

**Hàm Mobius** $\mu(n)$ được định nghĩa như sau:

- $\mu(1)=1$

- $\mu(n)=0$ nếu tồn tại $a_i>1$

- $\mu(n)=(-1)^r$ nếu $n={p_1}\*{p_2}\*{p_3}\*...\*{p_r}$, hay $a_i = 1$ với mọi $i$

- Có thể chứng minh được rằng $\mu(n)=\sum_{d|n,d < n}\mu(d)$ với $n>1$ và tính được $\mu(n)$ bằng cách sử dụng Sàng:

```cpp
mu[1] = 1;
for (int i = 1; i <= N; i++)
    for (int j = 2*i; j <= N; j += i)
        mu[j] -= mu[i];
```


# Ứng dụng

Ta xét bài toán [CF #305 - Div 1 C](http://codeforces.com/contest/547/problem/C)

**Tóm tắt đề bài**:

> Cho dãy A với N số. Ban đầu ta có một tập hợp S rỗng. Bạn cần thực hiện Q truy vấn. Mỗi truy vấn cần thêm 1 số A(x) vào S hoặc xoá A(x) khỏi S, sau đó in ra số cặp (x, y) trong tập S thoả mãn gcd(x, y) = 1. N, Q <= 10^5.

**Cách làm**:

Theo nguyên lý bù trừ, số cặp (x, y) trong tập S mà $gcd(x, y) = 1$ là:

```
(Số cặp (x, y) bất kỳ)
- (Số cặp (x, y) mà x và y cùng chia hết cho 2)
- (Số cặp (x, y) mà x và y cùng chia hết cho 3)
- (Số cặp (x, y) mà x và y cùng chia hết cho 5)
- (Số cặp (x, y) mà x và y cùng chia hết cho 7)
- ...
+ (Số cặp (x, y) mà x và y cùng chia hết cho 2 và 3)
+ (Số cặp (x, y) mà x và y cùng chia hết cho 2 và 5)
+ (Số cặp (x, y) mà x và y cùng chia hết cho 2 và 7)
+ (Số cặp (x, y) mà x và y cùng chia hết cho 3 và 5)
+ ...
- (Số cặp (x, y) mà x và y cùng chia hết cho 2 và 3 và 5)
```

Với mỗi tập hợp gồm chẵn số nguyên tố, ta cộng thêm vào kết quả số lượng cặp (x, y) mà cả x và y chia hết cho tất cả các số nguyên tố trong tập đó.

Với mỗi tập hợp gồm lẻ số nguyên tố, ta trừ khỏi kết quả số lượng cặp (x, y) mà cả x và y chia hết cho tất cả các số nguyên tố trong tập đó.


Gọi $cnt(k)$ là số lượng số trong tập $S$ mà là bội của $k$.

Đặt $f(k)$ là số cặp x, y mà cả x và y đều chia hết cho $k$, thì $f(k) = cnt(k) * (cnt(k) - 1) / 2$.

Theo phân tích ở trên,

$res = f(1) - f(2) - f(3) - f(5) - ... + f(2\*3) + f(2\*5) + f(2\*7) + ... - f(2\*3\*5) - f(2\*3\*7) - ...$

$res = sum(f(i) * mu(i))$

Khi ta thêm hoặc xoá 1 số $x$ khỏi tập S:

- Với mảng $cnt$, chỉ có những $cnt(k)$ với $k$ là ước của $x$ bị thay đổi. Do đó ta dễ dàng cập nhật $cnt$ với độ phức tạp tỉ lệ với số ước của $n$.
- Với kết quả, chỉ có các $f(k) * mu(k)$ với $k$ là ước của $x$ bị thay đổi. Do đó ta cũng có thể cập nhật kết quả với độ phức tạp tỉ lệ với số ước của $n$.

Do đó, ta thu được thuật toán với độ phức tạp $O(Q*x)$ với $x$ là số ước tối đa của 1 số trong mảng $A$.

Các bạn có thể tham khảo cài đặt [ở đây](http://codeforces.com/contest/547/submission/11299564)