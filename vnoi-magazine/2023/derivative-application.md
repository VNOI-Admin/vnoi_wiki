# Áp dụng bất ngờ của đạo hàm
**Người viết:** Nguyễn Thành Trung - Singapore

Lúc học môn Toán có lẽ chúng ta thường hay tự hỏi: Học đạo hàm, tích phân.. để làm gì? Hôm nay chúng ta sẽ cùng nghiên cứu một áp dụng vô cùng bất ngờ và ảo ma của đạo hàm trong 1 bài toán.

Bài toán như sau:
- Cho $N$ ngôi nhà trên 1 đường thẳng. Ngôi nhà thứ $i$ có $H_i$ tầng.
- Để khu phố nhìn đẹp hơn, người ta muốn sửa lại các ngôi nhà sao cho độ cao của tất cả các ngôi nhà đều bằng nhau, bằng cách xây thêm hoặc đập đi một số tầng của một số ngôi nhà.
- Với ngôi nhà thứ $i$, chi phí để xây thêm 1 tầng hoặc đập đi 1 tầng là $C_i$.
- Tìm chi phí nhỏ nhất.
- Giới hạn: $N \leq 10^7$, $0 \leq H(i) \leq 10^7$, $0 \leq C_i \leq 10^{11}$.

Ví dụ: với $N = 3$, $H = [10, 20, 15]$, $C = [1000, 1, 2]$. Cách tối ưu là đưa cả 3 nhà về độ cao $10$, với chi phí:
$$
|10 - 10| * 1000 + |20 - 10| * 1 + |15 - 10| * 2 = 20$$

Các bạn có thể đọc đề và nộp thử tại [SPOJ](https://www.spoj.com/problems/KOPC12A/) (tuy nhiên giới hạn trong bài SPOJ này khá nhỏ).

# Lời giải $O(N*log)$

Đầu tiên chúng ta hãy nghiên cứu 1 số lời giải "thông thường" cho bài toán này.

Đặt $f_i(x)$ là chi phí để sửa ngôi nhà thứ $i$ về độ cao $x$. Ta có công thức:
$$
f_i(x) = |x - H_i| * C_i$$

Đặt $F(x) = \sum_{i=1..n}{f_i(x)}$, nói cách khác $F(x)$ là chi phí để đưa tất cả các ngôi nhà về độ cao $x$. Đề bài yêu cầu ta tìm $min(F(x))$.

## Nhận xét 1:

Đặt $x_0$ là giá trị của $x$ để hàm $F(x)$ đạt giá trị nhỏ nhất, khi đó:
$$min(H_i) \leq x_0 \leq max(H_i)$$

Khá hiển nhiên, giả sử $x_0 < min(H_i)$, điều này chỉ xảy ra khi ta phải giảm độ cao của tất cả các ngôi nhà đi ít nhất 1 tầng. Với mỗi ngôi nhà ta giảm nó ít đi 1 tầng thì sẽ được chi phí nhỏ hơn. Do đó $x_0 \geq min(H_i)$.

Tương tự, ta cũng chứng minh được $x_0 \leq max(H_i)$

Với nhận xét này, ta có thuật toán $O(N*max_H)$, với $max_H$ là giá trị lớn nhất của $H$: duyệt tất cả các giá trị của $x$, với mỗi $x$, ta tính hàm $F(x)$ trong $O(N)$.

## Nhận xét 2:

Hàm $F(x)$ là tổng của các hàm lồi (strictly convex) nên nó cũng là hàm lồi.

Ví dụ: trong ảnh mình vẽ hàm $F(x)$ màu đỏ là tổng của 3 hàm $f_1(x)$, $f_2(x)$ và $f_3(x)$. Có thể thấy $F(x)$ là hàm lồi

[[/uploads/derivative-application_img1.png]]

Do đó ta có thể sử dụng [tìm kiếm tam phân](https://vnoi.info/wiki/translate/emaxx/Tim-kiem-tam-phan-Ternary-Search.md) để tìm giá trị nhỏ nhất của $F(x)$.

$\Rightarrow$ đến đây ta đã có thuật toán với độ phức tạp $O(N*log(max_H))$.

# Lời giải $O(N+max_H)$

Rất bất ngờ, bài này còn có thể giải được với độ phức tạp $O(N + max_H)$ sử dụng đạo hàm!

Ở bài viết này chúng ta ứng dụng đạo hàm của hàm trên số nguyên ($f(x)$ với $x$ chỉ nhận giá trị nguyên) - [discrete derivative](https://calculus.subwiki.org/wiki/Discrete_derivative). Định nghĩa:
$$
f'(x) = f(x) - f(x-1)$$

Áp dụng công thức trên vào bài toán ban đầu: ta tính đạo hàm của hàm chi phí:
$$
f'_i(x) = \left\lbrace \begin{array}{rl}
-C(i) & \text{nếu }x \leq H(i) \\
C(i) & \text{nếu }x > H(i)
\end{array} \right.$$.

Cũng theo tính chất của đạo hàm:

$F'(x) = \sum_{i=1..n}{f'_i(x)}$

Ví dụ: hàm màu tím là đạo hàm của hàm màu xanh

[[/uploads/derivative-application_img2.png]]

Ta tính đạo hàm thêm lần nữa:

$f''_i(x) = 2*C(i)$ nếu $x = H(i+1)$, ngược lại $f''_i(x) = 0$.

Cũng theo tính chất của đạo hàm:

$F''(x) = \sum_{i=1..n}{f''_i(x)}$

Hàm $f''_i(x)$ chính là mấu chốt để giải bài toán này: hàm $f''_i(x)$ chỉ khác $0$ tại đúng 1 điểm, do đó ta dễ dàng "tính" được $f''_i(x)$ trong $O(1)$.

$\Rightarrow$ ta có thể tính được $F''(x)$ trong $O(N)$ rất đơn giản như sau:

```cpp
vector<int> F2(MAX_H + 1);  // F2[x] = F''(x)
for (int i = 0; i < N; ++i) {
    // f''i(x) = 2*C(i) at x = H(i)+1
    F2[H[i] + 1] += 2 * C[i];
}
```

Dựa vào định nghĩa của đạo hàm ($f'(x) = f(x) - f(x-1)$), từ $F''(x)$ ta có thể dễ dàng tính được $F'(x)$ trong $O(max_H)$:

```cpp
vector<int> F1(MAX_H + 1);  // F1[x] = F'(x)
// Tính F'(0)
for (int i = 0; i < N; ++i) {
    F1[0] -= C[i];
}
// Tính F'(x)
for (int x = 1; x <= MAX_H; ++x) {
    F1[x] = F1[x-1] + F2[x];
}
```

Tương tự, ta có thể tính được $F(x)$ trong $O(max_H)$:

```cpp
vector<int> F(MAX_H + 1);
// Tính F(0)
for (int i = 0; i < N; ++i) {
    F[0] += H[i] * C[i];
}
// Tính F(x)
for (int x = 1; x <= MAX_H; ++x) {
    F[x] = F[x-1] + F1[x];
}
```

Đến đây ta đã thu được thuật toán với độ phức tạp $O(N+max_H)$!

# Bonus

Sử dụng đạo hàm, ta cũng có thể chứng minh hàm $F(x)$ là hàm lồi, và do đó cách chặt tam phân trình bày ở trên là chính xác.

Một hàm số là hàm lồi trong đoạn $[l, r]$ nếu đạo hàm bậc 2 của nó luôn lớn hơn hoặc bằng $0$ trong khoảng $[l, r]$. (Một cách hiểu trực quan: có thể thấy nếu đạo hàm bậc 2 không âm $\Rightarrow$ đạo hàm bậc 1 là hàm tăng dần $\Rightarrow$ hàm số luôn "cong cong" về phía trên). ([Xem thêm trên trang Wiki về hàm lồi](https://en.wikipedia.org/wiki/Convex_function))

Ở bài này, dễ thấy $f_i(x)$ luôn lớn hơn hoặc bằng $0$, do đó $F''(x) = \sum{f_i(x)}$ cũng luôn lớn hơn hoặc bằng $0$.

Hình vẽ chụp từ Geogebra: [https://www.geogebra.org/calculator/pcyur4yk](https://www.geogebra.org/calculator/pcyur4yk)
