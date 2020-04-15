# ALAKE
Để đơn giản hóa bài toán, ta tạm coi $w_i = 1$ với mọi $i$ (mình sẽ gọi mỗi đoạn trong đề bài là mỗi cột cho dễ tưởng tượng), và ta chỉ tính thời gian ngập của vị trí $i$ khi nước chảy ở ngay vị trí $i$.
Để tính được thời gian vị trí $i$ bị ngập trong trường hợp này, ta làm như sau:
- Tìm hai cột cao hơn $H_i$ ở hai bên $i$ và gần $i$ nhất. Gọi vị trí của hai cột này trong mảng là $prv_i$ và $nxt_i$
- Tính phần nước trong hình chữ nhật có chiều dài từ $prv_i+1$ đến $nxt_i-1$ có chiều cao $H_i+1$, rồi trừ đi phần cột (tổng chiều cao trong đoạn đó)

Gọi thời gian tính được là $orig(i)$
Bây giờ để tính ra được đáp án cần tìm, ta cần phải tính thời điểm mà bắt đầu nước chảy vào vị trí trong khoảng từ $prv_i+1$ đến $nxt_i$ (bạn có thể thử tưởng tượng quá trình nước chảy để hiểu tại sao ta chỉ cần tính thêm cái này). Gọi thời điểm này là $dp(i)$, và vị trí nước chảy vào đầu tiên là $x$, ta có:
- $dp(x) = 0$
- Nếu đoạn $prv_i+1$ đến $nxt_i-1$ có điểm $x$, $dp(i) = 0$
- Nếu $i<x$, $dp(i) =$ (thời gian để nước dâng lên đến độ cao $H_{nxt_i}$ tinh từ khi nước bắt đầu chảy vào đoạn $prv_{nxt_i}$ đến $nxt_{nxt_i}$) + (thời gian để nước bắt đầu chảy vào đoạn) $=$ (bạn có thể tự tính) + $dp(nxt_i)$
- Nếu $i>x$, ta thay $nxt_i$ ở công thức trên thành $prv_i$ và xử lí tương tự trường hợp trên.

Ta thấy phần tính $prv_i$ và $nxt_i$ có thể mất $O(N^2)$, còn phần $dp$ do có $n$ trạng thái, mỗi trạng thái chỉ "di chuyển" $O(1)$ lần nên độ phức tạp phần $dp$ chỉ là $O(n)$. Vì vậy ta cần tối ưu phần tính $prv_i$ và $nxt_i$.

Giả sử ta đang tính $prv_i$, ta cần thực hiện truy vấn tìm $j$ thỏa mãn $H_j > H_i$, $j < i$ và $j$ lớn nhất có thể. 
- Do $H_i$ chỉ có $O(N)$ giá trị có thể nên ta có thể tạm thời nén $H_i$ lại để sử dụng cấu trúc dữ liệu nào đó. Gọi $index(H_i)$ là giá trị đã được nén của $H_i$
- Điều kiện $j < i$ ta hoàn toàn có thể loại bỏ nếu ta duyệt các cột từ đầu đến cuối, và chỉ cho cột $i$ vào cấu trúc dữ liệu khi đã xét xong cột $i$
- Phần tính $j$ lớn nhất có thể trong đoạn $[H_i+1,\infty)$, ta có thể dùng cây phân đoạn (Segment Tree) để xử lí.

Do đó ta có thuật toán tính $prv_i$ trong $O(N\log{N})$ như sau:
- Chèn giá trị $0$ vào vị trí $index(\infty)$ trong cây phân đoạn, vì đây là cột cao vô tận
- Với mỗi $i$ từ 1 đến $N$ (Độ phức tạp: $O(N)$)
    - Truy vấn $max(index(H_i)+1,\infty)$ trên cây phân đoạn để tìm $prv_i$
    - Chèn giá trị $i$ cho vị trí $index(H_i)$

Phần tính $nxt_i$, ta cũng giải quyết tương tự

Đến đây mình nghĩ các bạn có thể tự suy nghĩ cách xử lí khi $w_i$ không bằng nhau rồi.

Tổng kết: Độ phức tạp tính toán $O(N\log{N} + N)$

[Code mẫu](https://ideone.com/ilUJku)

Note: Code mẫu hơi dài do mình chưa tận dụng được con trỏ dành cho hàm của C++. Nếu bạn tận dụng được, code có thể còn ngắn hơn và giảm thiểu rủi ro bị lỗi khi code.