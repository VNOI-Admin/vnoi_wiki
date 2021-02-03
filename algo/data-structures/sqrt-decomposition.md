# Chia căn (sqrt decomposition) và ứng dụng

**Tác giả**: Hoàng Xuân Nhật & Vương Hoàng Long

[[_TOC_]]

Chia căn là tên gọi chung của một nhóm các thuật toán thường liên quan đến việc chia mảng độ dài $N$ ra làm $\sqrt{N}$ đoạn, dùng để giải quyết các bài toán truy vấn. 

Sau đây ta sẽ xét một dạng đơn giản nhất: chia mảng ra làm $\sqrt{N}$ đoạn.


# Bài toán

Cho một mảng $A$ gồm $N$ phần tử là các số nguyên không âm. Bạn cần trả lời $Q$ truy vấn, mỗi truy vấn có dạng $(l, r, k)$ yêu cầu tìm đếm số phần tử của A nằm trong đoạn $[l..r]$ có giá trị bằng $k$. Giới hạn: $N, Q, A_i \le 10^5$.

Giả sử ta luôn có $l = 1$ và $r = N$, bài toán trên có thể giải đơn giản bằng cách tạo một mảng $cnt[x] = $ số phần tử của mảng có giá trị **bằng** $x$.

Ta áp dụng ý tưởng này để giải bài toán tổng quát, bằng cách tạo ra $\sqrt{N}$ mảng *cnt*, mỗi mảng quản lý một đoạn $\sqrt{N}$ phần tử liên tiếp của $A$. Để hiểu rõ hơn, ta có thể xem ví dụ sau.

Ta có mảng A gốm 13 phần tử, chỉ số được đánh bắt đầu từ 0. Ta sẽ chia mảng A thành các đoạn có độ dài 4, đoạn cuối cùng sẽ chỉ chứa 1 phần tử. Nội dung mảng $A$ và các mảng $cnt$ đã được tính sẵn như trong hình sau:

[[/uploads/sqrt_problem1_1.PNG]]

Với cấu trúc trên, ta có thể dễ dàng trả lời các truy vấn. Ví dụ, xét truy vấn $(1, 11, 0)$.

[[/uploads/sqrt_problem1_2.PNG]]

Có thể thấy, đoạn truy vấn sẽ luôn được chia thành các đoạn chứa đủ $\sqrt{N}$ phần tử (trong trường hợp này là đoạn $[4..7]$ và $[8..11]$), và có thể thêm một số đoạn không đầy đủ ở hai đầu (ở đây là đoạn $[1..3]$).

Với những đoạn đầy đủ, ta cộng $cnt[0]$ của chúng vào kết quả. Với những đoạn không đầy đủ, ta xét từng phần tử. Phần tử nào bằng 0, ta sẽ tăng biến đếm kết quả lên 1. Với truy vấn $(1, 11, 0)$, ta có kết quả là $2 + 3 + 1 + 1 = 7$.

[[/uploads/sqrt_problem1_3.PNG]]