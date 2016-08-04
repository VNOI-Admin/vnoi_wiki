# Mo algorithm

**Tác giả**: Nguyễn *RR* Thành Trung

# Bài toán

Cho một dãy số $A$ gồm $N$ phần tử. Cần thực hiện $Q$ truy vấn, mỗi truy vấn $(i, j)$ yêu cầu tìm $mode(Ai, ..., Aj)$. (Mode của một tập hợp là giá trị xuất hiện nhiều lần nhất trong tập hợp đó). Giới hạn: $N, Q, A_i \le 10^5$.

Khi đọc đề một bài toán truy vấn kiểu này, có lẽ CTDL đầu tiên mà các bạn nghĩ đến là Interval Tree. Nhưng có điều gì đó không ổn trong bài này: Khi có thông tin của 2 nút con $[l, mid]$ và $[mid+1, r]$, rất khó để tìm được bất kỳ thông tin hữu ích nào của $[l, r]$.

# Duyệt

Chúng ta xuất phát từ thuật toán duyệt hồn nhiên như sau:

- Với mỗi truy vấn, ta for từ trái sang phải, đếm số lần xuất hiện.
- Trong khi đếm thì ta cập nhật kết quả.

Code đơn giản như sau:

```
function mode(l, r):
  // Khởi tạo mảng count = toàn 0
  res = -1
  for i = l .. r:
    count[A[i]] += 1
    if res == -1 or count[A[i]] > count[res]:
      res = A[i]
  return res
```

Dễ thấy, thuật toán duyệt này có độ phức tạp $O(N \* Q)$. Có 2 lý do chính khiến thuật toán này chạy chậm:

1. Khởi tạo mảng count mỗi lần mất $O(N)$
2. Với mỗi truy vấn, phải tính lại count từ đầu

Ta có thể cải tiến được như sau:

Sau khi trả lời truy vấn $[l_1, r_1]$, để trả lời truy vấn $[l_2, r_2]$, bạn chỉ cần thay đổi mảng đếm một cách phù hợp. Cụ thể:

- Nếu $l_2 > l_1$, giảm số lần xuất hiện của $A(l_1), ..., A(l_2-1)$
- Nếu $l_2 < l_1$, tăng số lần xuất hiện của $A(l_2), ..., A(l_1-1)$
- Tương tự với $r_1$ và $r_2$.

Để cập nhật số lần xuất hiện lớn nhất thì có thể dùng thêm set.

Như vậy, độ phức tạp của ta là tổng $|l_i - l_{i-1}| + |r_i - r_{i-1}|$, nhân thêm log để đếm và tìm phần tử lớn nhất của mảng đếm.

# Thuật toán Mo

Thuật toán Mo là một cách sắp xếp lại các truy vấn, sao cho tổng $|l_i - l_{i-1}| + |r_i - r_{i-1}|$ không quá $O(N \* sqrt(N) + Q \* sqrt(N))$.

```
S = sqrt(N);
bool cmp(Query A, Query B) // so sánh 2 truy vấn
{
  if (A.l / S ！= B.l / S) {
    return A.l / S < B.l / S;
  }
  return A.r < B.r
}

```

**Giải thích**:

- Ta chia dãy thành các block (nhóm) độ dài $S = \sqrt{N}$
- Nếu đầu trái của truy vấn nằm ở 2 phần khác nhau, ta sắp xếp theo đầu trái
- Ngược lại (đầu trái của truy vấn nằm ở cùng 1 phần), ta sắp xếp theo đầu phải

**Chứng minh**:

Mo's algorithm có độ phức tạp là $O(N \* \sqrt{N} + Q \* \sqrt{N})$. Để hiểu tại sao độ phức tạp của thuật toán đạt được như vậy, chúng ta hãy cùng xem việc di chuyển các đoạn $[l_1,r_1]$ thành $[l_2,r_2]$:

- Di chuyển $l_1 \rightarrow l_2$:
    - Nếu $l_1$ và $l_2$ cùng phần: Với mỗi thao tác, độ phức tạp không quá $\sqrt{N}$. Do đó, độ phức tạp trong trường hợp này của cả $Q$ thao tác là $O(Q \* \sqrt{N})$.
    - Nếu $l_1$ và $l_2$ khác block: Vì ta ưu tiên sort theo phần chứa $l$, nên trường hợp này chỉ xảy ra không quá $\sqrt{N}$ lần. Ở trường hợp này, ta mất độ phức tạp tối đa là $O(N)$, nên với tất cả các thao tác trong trường hợp này, độ phức tạp là $O(N \* \sqrt{N})$.
- Di chuyển $r_1 \rightarrow r_2$:
    - Nếu $l_1$ và $l_2$ cùng block: Vì ta sort tăng theo $r$, nên với mỗi block của $l$, ta chỉ mất độ phức tạp tổng là O(N). Do có sqrt(N) block khác nhau của l, nên tổng độ phức tạp trong trường hợp này là O(N*sqrt(N))
Nếu l1 và l2 khác block: Như trên đã phân tích, ta chỉ có sqrt(N) lần đổi block, môi lần đổi block ta mất độ phức tạp O(N) để di chuyển r. Do đó tổng độ phức tạp của trường hợp này là O(N*sqrt(N)).
Vậy, độ phức tạp tổng là O(N*sqrt(N) + Q*sqrt(N)).

