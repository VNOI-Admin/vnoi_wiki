# ALAKE
Để đơn giản hóa bài toán, ta tạm coi $w_i = 1$ với mọi $i$ (mình sẽ gọi mỗi đoạn trong đề bài là mỗi cột cho dễ tưởng tượng), và ta chỉ tính thời gian ngập của vị trí $i$ khi nước chảy ở ngay vị trí $i$.
Để tính được thời gian vị trí $i$ bị ngập trong trường hợp này, ta làm như sau:
- Tìm hai cột cao hơn $H_i$ ở hai bên $i$ và gần $i$ nhất. Gọi vị trí của hai cột này trong mảng là $\texttt{prv}_i$ và $\texttt{nxt}_i$
- Tính phần nước trong hình chữ nhật có chiều dài từ $\texttt{prv}_i+1$ đến $\texttt{nxt}_i-1$ có chiều cao $H_i+1$, rồi trừ đi phần cột (tổng chiều cao trong đoạn đó)

Gọi thời gian tính được là $\texttt{orig}(i)$
Bây giờ để tính ra được đáp án cần tìm, ta cần phải tính thời điểm mà bắt đầu nước chảy vào vị trí trong khoảng từ $\texttt{prv}_i+1$ đến $\texttt{nxt}_i$ (bạn có thể thử tưởng tượng quá trình nước chảy để hiểu tại sao ta chỉ cần tính thêm cái này). Gọi thời điểm này là $\texttt{dp}(i)$, và vị trí nước chảy vào đầu tiên là $x$, ta có:
- $\texttt{dp}(x) = 0$
- Nếu đoạn $\texttt{prv}_i+1$ đến $\texttt{nxt}_i-1$ có điểm $x$, $\texttt{dp}(i) = 0$
- Nếu $i<x$, $\texttt{dp}(i) = \text{(thời gian để nước dâng lên đến độ cao } H_{\texttt{nxt}_i} \text{ tinh từ khi nước bắt đầu chảy vào đoạn } \texttt{prv}_{\texttt{nxt}_i} \text{ đến } \texttt{nxt}_{\texttt{nxt}_i}\text{)} + \text{(thời gian để nước bắt đầu chảy vào đoạn)} = \text{(bạn có thể tự tính)} + \texttt{dp}(\texttt{nxt}_i)$
- Nếu $i>x$, ta thay $\texttt{nxt}_i$ ở công thức trên thành $\texttt{prv}_i$ và xử lí tương tự trường hợp trên.

Ta thấy phần tính $\texttt{prv}_i$ và $\texttt{nxt}_i$ có thể mất $\mathcal{O}(N^{2})$, còn phần $\texttt{dp}$ do có $n$ trạng thái, mỗi trạng thái chỉ "di chuyển" $\mathcal{O}(1)$ lần nên độ phức tạp phần $\texttt{dp}$ chỉ là $\mathcal{O}(n)$. Vì vậy ta cần tối ưu phần tính $\texttt{prv}_i$ và $\texttt{nxt}_i$.

Giả sử ta đang tính $\texttt{prv}_i$, ta cần thực hiện truy vấn tìm $j$ thỏa mãn $H_j > H_i$, $j < i$ và $j$ lớn nhất có thể. 
- Do $H_i$ chỉ có $\mathcal{O}(N)$ giá trị có thể nên ta có thể tạm thời nén $H_i$ lại để sử dụng cấu trúc dữ liệu nào đó. Gọi $\texttt{index}(H_i)$ là giá trị đã được nén của $H_i$
- Điều kiện $j < i$ ta hoàn toàn có thể loại bỏ nếu ta duyệt các cột từ đầu đến cuối, và chỉ cho cột $i$ vào cấu trúc dữ liệu khi đã xét xong cột $i$
- Phần tính $j$ lớn nhất có thể trong đoạn $[H_i+1,\infty)$, ta có thể dùng cây phân đoạn (Segment Tree) để xử lí.

Do đó ta có thuật toán tính $\texttt{prv}_i$ trong $\mathcal{O}(N\log{N})$ như sau:
- Chèn giá trị $0$ vào vị trí $\texttt{index}(\infty)$ trong cây phân đoạn, vì đây là cột cao vô tận
- Với mỗi $i$ từ 1 đến $N$ (Độ phức tạp: $\mathcal{O}(N)$)
    - Truy vấn $\max(\texttt{index}(H_i)+1,\infty)$ trên cây phân đoạn để tìm $\texttt{prv}_i$
    - Chèn giá trị $i$ cho vị trí $\texttt{index}(H_i)$

Phần tính $\texttt{nxt}_i$, ta cũng giải quyết tương tự

Đến đây mình nghĩ các bạn có thể tự suy nghĩ cách xử lí khi $w_i$ không bằng nhau rồi.

Tổng kết: Độ phức tạp tính toán $\mathcal{O}(N\log{N} + N)$

[Code mẫu](https://ideone.com/ilUJku)

Note: Code mẫu hơi dài do mình chưa tận dụng được con trỏ dành cho hàm của C++. Nếu bạn tận dụng được, code có thể còn ngắn hơn và giảm thiểu rủi ro bị lỗi khi code.