# Z Algorithm

**Nguồn bài**: [Codeforces](http://codeforces.com/blog/entry/3107)

[[_TOC_]]

Trước khi đọc bài này, các bạn có thể đọc bài [[Xử lý xâu|algo/string/basic]] để nắm được các thuật ngữ cơ bản.

**Z Algorithm** hay còn gọi là **Z Function** là thuật toán áp dụng cho các bài so khớp chuỗi.

# Bài toán

Cho một chuỗi $S$ có độ dài $n$, thuật toán Z Function tạo ra một mảng $Z$ mà tại mỗi vị trí $i$, ta có $Z_i$ là độ dài chuỗi con dài nhất là tiền tố của $S$ bắt đầu tại vị trí $S_i$, hay nói một cách khác $Z_i$ là một số nguyên $k$ lớn nhất mà $S_j=S_{i + j}$ với mọi $0 \le j < k$. Trường hợp $S_i \ne S_0$ thì $Z_i = 0$.

# Thuật toán

Ta duyệt qua tất cả các ký tự của $S$ (chỉ số $i$ từ 1 đến $n - 1$). Trong quá trình duyệt, ta duy trì một đoạn $[L, R]$ với $R$ là một số lớn nhất thỏa $1 \le L \le i \le R$ và $[L, R]$ là một tiền tố của $S$ (Nếu không xuất hiện các đoạn như vậy thì đặt $L = R = -1$).

Với $i = 1$ ta có thể dễ dàng tính $L$ và $R$ bằng phép so sánh $S[0..]$ với $S[1..]$. Đồng thời, ta có thể tính giá trị $Z_1$.

Giả sử ta đã xây dựng được đoạn $[L, R]$ và các giá trị $Z[1..i - 1]$, ta sẽ tính $Z_i$ và cập nhật đoạn $[L,R]$ mới như sau:

- Nếu $i > R$, khi đấy không tồn tại một chuỗi con là tiền tố của $S$ bắt đầu tại một vị trí trước $i$ và kết thúc tại ví trí $i$ hoặc sau $i$. Bởi nếu như có một tiền tố như vậy, thì đoạn $[L, i]$ sẽ là chuỗi tiền tố tối ưu chứ không phải $[L, R]$. Do đó, ta sẽ cập nhật lại đoạn $[L, R]$ bằng cách so sánh $S[0..]$ với $S[i..]$ và lấy giá trị $Z_i$ hiện tại ($Z_i = R - L + 1$).

- Ngược lại, $i \le R$ thì đoạn $[L, R]$ hiện tại kéo dài ít nhất đến $i$. Đặt $k = i - L$. Ta biết rằng $Z_i \ge min(Z_k, R - i + 1)$ bởi vì $S[i..]$ bằng với $S[k..]$ ít nhất là $R - i + 1$ ký tự. Xét các trường hợp sau:
    - Nếu $Z_k < R - i + 1$ thì sẽ không có chuỗi con nào là tiền tố của $S$ dài hơn $Z_k$ bắt đầu tại $S_i$. Nghĩa là $Z_i = Z_k$ và đoạn $[L, R]$ vẫn giữ nguyên (do đoạn $[L, R]$ chỉ thay đổi nếu chuỗi tiền tố bắt đầu tại $S_i$ vượt ra khỏi đoạn $[L, R]$).
    - Nếu $Z_k \ge R - i + 1$ thì chuỗi $S[i..]$ là tiền tố của $S$ và có nhiều hơn $R - i + 1$ ký tự (tức là kết thúc sau vị trí $R$). Như vậy ta cần cập nhật đoạn $[L, R]$ bằng cách đặt lại $L = i$ và so sánh từ vị trí $S[R + 1]$ trở đi để được một vị trí $R$ mới. Đồng thời, ta tính được giá trị của $Z_i$.

# Độ phức tạp:
Tại mỗi bước trong vòng lặp, chúng ta không cần so sánh ký tự tại các vị trí nhỏ hơn $R$, và mỗi lần ký tự $R$ phù hợp thì ta tăng $R$ lên một, vì thế ta sẽ tốn nhiều nhất $n$ phép so sánh. Ngoài ra, với mỗi giá trị $i$, ta chỉ tìm thấy một ký tự không phù hợp (điều kiện tăng $R$). Vì thế không thể có nhiều hơn $n$ phép so sánh cho kết quả sai. Đưa đến độ phức tạp thuật toán là $O(n)$.

# Cài đặt:

Có thể dễ dàng cài đặt. Chú ý việc tối ưu hóa $L = R = i$ được sử dụng khi $S_0 \ne S_i$ (Điều đó không làm ảnh hưởng đến thuật toán kể từ giá trị kế tiếp $i > R$ không phân biệt).

```cpp
int L = 0, R = 0;
Z[0] = n;
for (int i = 1; i < n; i++)
   if (i > R)
   {
      L = R = i;
      while (R < n && S[R] == S[R - L]) R++;
      Z[i] = R - L; R--;
   }
   else
   {
      int k = i - L;
      if (Z[k] < R - i + 1) Z[i] = Z[k];
      else
      {
          L = i;
          while (R < n && S[R] == S[R - L]) R++;
          Z[i] = R - L; R--;
      }
   }
```

# Áp dụng

[VOJ - SUBSTR](https://oj.vnoi.info/problem/SUBSTR/)

Có thể dùng ZFuntion để giải bài này. Ta tạo ra một chuỗi $S=B+A$, sao đó xây dựng mảng $Z$. Những vị trí có $Z_i \ge Length(B)$ (Với $Length(B) \le i < Length(A)+Length(B)$) là vị trí tương ứng của $B$ trong $A$.