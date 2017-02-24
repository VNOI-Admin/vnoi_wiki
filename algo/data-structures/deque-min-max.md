# Kĩ thuật sử dụng Deque tìm Min/Max trên đoạn tịnh tiến

**Nguồn bài**: [link](https://langocthuyan.wordpress.com/2014/08/12/ki-thuat-su-dung-deque-stack-2-dau-tim-minmax-tren-doan-tinh-tien/)

**Tác giả**: Yên Vũ

Kĩ thuật sử dụng Deque tìm Min/Max trên đoạn tịnh tiến xuất hiện nhiều trong các bài tập tin học, thông thường để cải tiến chương trình, làm giảm độ phức tạp. Chúng ta sẽ tìm hiểu kĩ thuật này qua một vài ví dụ cụ thể và xem xét khả năng mở rộng ứng dụng của nó trong các bài toán khác.

# Bài toán

Cho dãy số nguyên không âm $A$ có $N$ phần tử $(N \le 10^6)$. Ta cần xây dựng 2 mảng $L$ và $R$ có $N$ phần tử, được định nghĩa như sau:

- $1 \le L_i \le i \le R_i \le N$.
- $A_i = \min{ A[L_i], A[L_i + 1], ..., A[R_i]}$.
- $R_i - L_i$ là lớn nhất (nói cách khác là số phần tử trong đoạn $[L_i, R_i]$ là lớn nhất).

Nói một cách đơn giản hơn: Với mỗi phần tử $i$ của mảng $A$, ta cần tìm đoạn $[L_i, R_i]$ dài nhất, sao cho $i \in [L_i, R_i]$ và $A_i = \min{A_{L_i}, ..., A_{R_i}}$. Với $N$ nhỏ, ta có thể giải quyết bài toán một cách đơn giản như sau: Với mỗi $i$, ta kiểm tra các phần tử xung quanh $i$ để mở rộng phạm vi $L_i$, $R_i$. Cụ thể:

```cpp
for (int i = 1; i <= n; i++) {
	L[i] = i;
	while (L[i] > 0 && a[i] <= a[L[i]]) --L[i];
	++L[i];

	R[i] = i;
	while (R[i] < n && a[i] <= a[R[i]]) ++R[i];
	--R[i];
}
```

Cách làm trâu bò này có độ phức tạp là $\mathcal{O}(N^2)$. Ta có thể cải tiến dựa vào các nhận xét sau:

- `L[i] - 1` bằng 0 hoặc là số lớn nhất mà `L[i] - 1 < i` và `A[L[i] - 1] < A[i]` **(1)**
- `R[i] + 1` bằng n+1 hoặc là số nhỏ nhất mà `R[i] + 1 > i` và `A[R[i] + 1] < A[i]` **(2)**

Từ nhận xét này, ta xây dựng Deque bằng cách "lọc" lại dãy như sau: Trong quá trình duyệt dãy $A$, luôn đưa $i$ vào cuối Deque hiện tại, nhưng loại bỏ tất cả các vị trí $j$ đã được đưa vào trong Deque mà $A[j] \ge A[i]$. Như vậy, tại mọi thời điểm $i$, ta luôn có danh sách các vị trí trên Deque mà các giá trị tương ứng trên mảng $A$ là tăng dần.

**Ví dụ**

$A = [1, 3, 5, 4, 2, 8]$

```
i = 1: Deque = [1]
i = 2: Deque = [1, 2]
i = 3: Deque = [1, 2, 3]
i = 4: Deque = [1, 2, 4]
i = 5: Deque = [1, 5]
i = 6: Deque = [1, 5, 6]
```

**Code**

```cpp
for (int i = 1; i <= n; ++i){
   while (top > 0 && a[D[top]] >= a[i]) --top;  //cap nhat Deque
   D[++top] = i; //dua i vao cuoi Deque
}
```

Theo cách hoạt động của Deque, ta có:

Giả sử tại bước $i$, đã xác định được $i$ ở vị trí top trong Deque. Khi đó: `L[i] = Deque[top - 1] + 1`

**Chứng minh**

Từ **(1)** ta có: `A[L[i] – 1] < A[i]`, nên `L[i] - 1` không bị loại khỏi Deque trong quá trình cập nhật lại Deque. Mặt khác, cũng từ **(1)** ta có `L[i] - 1` lớn nhất, mọi số $j \in [L[i], i-1]$ đều đã bị loại khỏi Deque do $A[j] \ge A[i]$, nên $L[i] - 1$ sẽ đứng liền sát $i$ trong Deque. Ta đưa $i$ vào vị trí cuối (top) của Deque, nên $L[i] - 1$ chính bằng $Deque[top - 1]$, hay $L[i] = Deque[top - 1] + 1$.

Vậy, ta xác định được $L$ của một phần tử bất kỳ ngay khi đưa phần tử đó vào Deque.

Bên cạnh đó, gọi $t$ là vị trí các phần tử của $A$ bị loại khỏi Deque trong quá trình cập nhật Deque. $t$ bị loại khỏi Deque tại thời điểm $i$, chứng tỏ $i$ là số đầu tiên xuất hiện trong Deque mà $A[i] < A[t]$ (vì nếu tồn tại một số $k$ thỏa mãn $t < k < i$ mà $A[k] < A[t]$ thì $t$ đã bị loại tại thời điểm $k$).

```cpp
D[0] = 0;
for (int i = 1; i <= n; ++i){
    while (top > 0 && a[D[top]] >= a[i]) --top;
    L[i] = D[top] + 1;
    D[++top] = i;
}
```

Để tính mảng $R$, ta làm ngược lại:

```cpp
D[0] = n+1;
for (int i = n; i >= 1; --i) {
    while (top > 0 && a[D[top]] >= a[i]) --top;
    R[i] = D[top] - 1;
    D[++top] = i;
}
```

Độ phức tạp của đoạn chương trình trên có thể đánh giá như sau: Với mỗi số trong dãy $A$, ta chỉ đưa vào Deque 1 lần duy nhất và cũng chỉ lấy ra khỏi Deque 1 lần duy nhất. Do vậy chi phí thực hiện chỉ là $2*N$, hay độ phức tạp của chương trình là $\mathcal{O}(n)$.

# Áp dụng

Chúng ta xem các bài tập sau đây:

## Áp dụng 1:

[VOJ - KAGAIN](http://vnoi.info/problems/show/KAGAIN/)

**Tóm tắt đề**

Cho dãy $A$ gồm $n$ phần tử.

Ta chọn các đoạn liên tiếp $[i, j]$ bất kì. “Sức mạnh” của đoạn $[i, j]$ được định nghĩa như sau: $SM[i, j] = (j – i + 1) * \min{A_i,..., A_j}$.

Yêu cầu: Cho biết $SM$ lớn nhất có thể trong dãy $A$.

**Lời Giải**

Để tìm kết quả, ta xét tất cả $n$ trường hợp có $A_k$ chính bằng min của đoạn $[i, j]$. Do ta đã cố định $min$ của đoạn $[i, j]$, sức mạnh lớn nhất đạt được khi $j - i$ là lớn nhất, nói cách khác là khi dãy dài nhất. Rõ ràng, đây chính là ứng dụng trực tiếp của mảng $L$ và $R$.

Xây dựng mảng $L$, $R$ và cập nhật kết quả bằng $(R[i] – L[i]+1) * A[i]$.

## Áp dụng 2

[VOJ - QBRECT](http://vnoi.info/problems/show/QBRECT/)

**Tóm tắt đề**

Cho bảng số $A$ chỉ gồm các phần tử {0, 1} kích thước $m \* n$. Tìm diện tích hình chữ nhật lớn nhất chỉ gồm các số 1 có cạnh song song với bảng.

**Lời Giải**

Xét hàng $i$. Với mỗi ô $[i, j]$ có giá trị 1, ta xét các ô ngay bên trên nó: $[i-1, j]$, $[i-2, j]$, ..., $[1, j]$. Giả sử ô đầu tiên bằng 0 là $[k, j]$. Nói cách khác, tất cả các ô $[i, j]$, $[i-1, j]$, ..., $[k+1, j]$ đều bằng 1. Ta đặt $H[i,j] = k+1$.

Nếu $[i, j]$ có giá trị 0, ta đặt $H[i,j] = 0$.

Ví dụ:

```
A =
0 1 0 1
1 1 0 0
0 1 0 1
0 1 1 1

H =
0 1 0 1
1 2 0 0
0 3 0 1
0 4 1 2
```

Ta có thể tính bảng $H$ bằng quy hoạch động với độ phức tạp $\mathcal{O}(n^2)$ như sau:

- $H[i][j] = 0$ nếu $A[i][j] = 0$,
- Ngược lại $H[i][j] = H[i – 1][j] + 1$.

Tiếp đó, ta thấy rằng: Hình chữ nhật có cạnh đáy nằm ở hàng $i$, cột trái ở $j1$, cột phải ở $j2$ có độ cao tối đa là $\min{H_{i, j1}, .., H_{i, j2}}$. Và diện tích của hình chữ nhật này là: $(j - i + 1) \* \min{H_{i, j1}, ..., H_{i, j2}}$. Đến đây, ta làm tương tự bài KAGAIN: giả sử hình chữ nhật có cạnh đáy nằm ở hàng $i$, và có $H_{i, j}$ là min, tìm đoạn $[j1, j2]$ dài nhất để có được hình chữ nhật lớn nhất.

Áp dụng cách làm như bài KAGAIN, ta có thuật toán với độ phức tạp $\mathcal{O}(n^2)$ cho bước này.

Do đó, ta giải quyết được bài tập này với $\mathcal{O}(n^2)$. Chú ý đây là độ phức tạp tối ưu do phần đọc ma trận $A$ đã mất $\mathcal{O}(n^2)$ rồi.

##Áp dụng 3 
[VOJ-MINK](http://vnoi.info/problems/show/MINK/)

**Tóm tắt đề**

Với mỗi $1<=i<=n-k+1$ tính $min({a_{i}..a_{i+k-1}})$

**Lời giải**

Ta thấy rằng khi dùng deque tương tự bài KAGAIN thì ở mỗi vị trí $i$ , $D[1]$ là $min(a_{1}..a_{i})$. Vậy phần còn lại là loại đi các phần từ đầu deque có vị trí nhỏ hơn $i-k+1$. Sau đó, phần tử đầu deque sẽ là câu trả lời.  

Bài tập tương tự:

- [VOJ - CREC01](http://vnoi.info/problems/show/CREC01/)
- [VOJ - CRECT](http://vnoi.info/problems/show/CRECT/)
- [VOJ - NKGOLF](http://vnoi.info/problems/show/NKGOLF/)

Một vài bài tập khác sử dụng Kĩ thuật tịnh tiến Deque

- [VOJ - KDIFF](http://vnoi.info/problems/show/KDIFF/)
- [VOJ - BLAND](http://vnoi.info/problems/show/BLAND/)
- [VOJ - C11CIR](http://vnoi.info/problems/show/C11CIR/)
- [VOJ - VMQUABEO](http://vnoi.info/problems/show/VMQUABEO/)
