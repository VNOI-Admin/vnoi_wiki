# Thuật toán Knuth-Morris-Pratt (KMP)

**Nguồn**: [wcipeg](http://wcipeg.com/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)

**Người dịch**: Trần Kim Thạch

# Giới thiệu

Trước khi đọc bài này, bạn có thể đọc về các thuật ngữ trong xử lý xâu cũng như về bài toán so khớp chuỗi [[ở đây|algo/string/basic]]

Thuật toán Knuth-Morris-Pratt (KMP) là một thuật toán với thời gian chạy tuyến tính nhằm giải quyết bài toán so khớp chuỗi.

Thuật toán được xây dựng dựa vào quan sát rằng một xâu con chung của $S$ và $T$ sẽ đưa ra được thông tin $S$ có khớp với các vị trí sau của $T$ hay không. Bởi vì xâu con chung này đồng nghĩa với một phần của $T$ đã khớp với một phần của $S$, nên bằng việc khởi tạo trước một số thông tin với xâu $S$, ta sẽ thu được những kết luận về $T$ (nhờ xâu con chung) mà không cần quay ngược và so sánh lại những ký tự đã khớp.

Cụ thể hơn, ta muốn tính toán trước cách xâu $S$ tự khớp với chính nó. Nhờ vậy thuật toán sẽ *không quay nhìn lại* và chỉ duyệt qua $T$ một lần duy nhất.

Cùng với quá trình tiền xử lí tuyến tính $O(\|T\|)$ (với $\|T\|$ là độ dài xâu $T$), thuật toán có thời gian chạy tuyến tính.

## Cảm hứng

Cảm hứng của KMP có thể được minh họa rõ nhất qua 3 ví dụ dưới đây.

### Ví dụ 1

```
S = aaa
T = aaaaaaaaa
```

Ở ví dụ này, ta cần các lần xuất hiện của xâu $S$ trong xâu $T$ ($S$ xuất hiện 7 lần).

Ta có thể duyệt bình thường với độ phức tạp $O(\|S\| \* \|T\|)$ như sau:

- So $S_1$ với $T_1$, $S_2$ với $T_2$, $S_3$ với $T_3$, do đó vị trí số 1 là vị trí khớp của $S$ trong $T$.
- So $S_1$ với $T_2$, $S_2$ với $T_3$, $S_3$ với $T_4$, tìm được vị trí số 2 là vị trí khớp của $S$ trong $T$.
- So $S_1$ với $T_3$, $S_2$ với $T_4$, $S_3$ với $T_5$, tìm được vị trí số 3 là vị trí khớp của $S$ trong $T$.

Và cứ mãi như vậy cho đến khi đủ hết trường hợp.

Tuy nhiên ta có thể làm tốt hơn nếu ta tiền xử lý $S$ và để ý:

- $S_1$ giống $S_2$
- $S_2$ giống $S_3$.

Vậy **tiền tố** độ dài 2 của $S$ ($S_1 S_2$) khớp với **xâu con** độ dài 2 ở vị trí thứ 2 của $S$ ($S_2 S_3$) - nói cách khác, $S$ tự khớp một phần.

Sau khi kiểm tra khớp ở vị trí số 1 (so sánh $S$ với $T_1 T_2 T_3$), ta đã biết:

- $S_1 = T_1$
- $S_2 = T_2$
- $S_3 = T_3$

Khi ta kiểm tra khớp ở vị trí số 2 (so sánh $S$ với $T_2 T_3 T_4$), ta có:

- $S_2 = T_2$, $S_3 = T_3$
- $S_1 = S_2$, $S_2 = S_3$

Suy ra:

- $S_1 = T_2$
- $S_2 = T_3$.

Do vậy, việc so sánh với $T_2$, $T_3$ là không cần thiết nữa. Ta chỉ cần kiểm tra nốt $S_3 = T_4$ là đã kết luận được $S$ được tìm thấy ở vị trí 2 trong $T$. Như vậy, sau đáp án ở vị trí $1$, ta chỉ cần thêm $1$ thao tác để kết luận $S$ cũng có ở vị trí $2$ trong $T$, thay vì $3$ như thuật duyệt bình thường. Đến đây ta biết:

- $S_1 = T_2$
- $S_2 = T_3$
- $S_3 = T_4$

Và tương tự, lại kết luận được:

- $S_1 = T_3$
- $S_2 = T_4$.

Ta sau đó chỉ cần so $S_3$ với $T_5$, tìm được một đáp án nữa, cứ thế tiếp tục. Trong khi thuật toán duyệt cần đến $3$ phép tính cho mỗi lần so sánh $S$ với một xâu con của $T$, kĩ thuật của chúng ta chỉ cần $3$ phép tính ở lần lặp đầu và $1$ cho mỗi kết quả sau, và không xét lại các kí tự của $T$. (Đây cũng là cách con người giải quyết bài toán) 

### Ví dụ 2

```
S = aaa
T =  aabaabaaa
```

Như ở trên, ta bắt đầu như thuật toán duyệt, so sánh:

- $S_1$ với $T_1$
- $S_2$ với $T_2$
- $S_3$ với $T_3$

Ở đây ta thấy $S_3$ khác $T_3$, vậy $S$ **không** khớp với $T$ ở vị trí $1$. Đến bước này thuật duyệt sẽ tiếp tục bằng cách so $S_1$ với $T_2$ và $S_2$ với $T_3$, không khớp; rồi lại so $S_1$ với $T_3$, không khớp; cứ như vậy.

Thế nhưng chúng ta sẽ thấy ngay rằng sau kết quả không khớp ở vị trí đầu, khả năng tìm thấy $S$ ở các vị trí $2$ và $3$ của $T$ đã không còn. Lí do là vì, như đã trình bày ở ví dụ 1:

- $S_2 = S_3$
- $S_3 \neq T_3$

Do đó $S_2 \neq T_3$.

Tương tự như vậy, do:

- $S_1 = S_2$
- $S_2 \neq T_3$

Nên $S_1 \neq T_3$, ta không cần tìm $S$ ở vị trí thứ $3$ của $T$ làm gì. Sẽ hợp lí hơn khi bắt đầu tiếp ở vị trí số $4$ (do ta không thể chắc chắn có thể tìm được hay không $S_2 S_3 S_4 \, = \, T_4T_5T_6$).

Sau khi so sánh ở vị trí 4 và thấy tiếp tục không khớp, ta dùng lập luận tương tự loại bỏ vị trí số $5$ và $6$, và bắt đầu lại ở vị trí số $7$ (ở đây 2 xâu khớp nhau). Lần nữa, hãy chú ý các kí tự của $T$ được duyệt qua theo trình tự.

### Ví dụ 3

Đây là một ví dụ phức tạp hơn:

```
S = tartan
T = tartaric_acid
```

Ta quan sát thấy **tiền tố** độ dài $2$ của $S$ khớp với chính **xâu con** độ dài $2$ bắt đầu ở vị trí số $4$ của nó. Bây giờ lần lượt so sánh các vị trí từ $S_1$ đến $S_6$ với $T_1$ đến $T_6$. Ta thấy $S_6$ không khớp với $T_6$, vậy không có kết quả ở vị trí số $1$.

Ở đây hãy chú ý:

- $S_1 \neq S_2$
- $S_1 \neq S_3$
- $S_2 = T_2$
- $S_3 = T_3$

Nên ta có $S_1 \neq T_2$ và $S_1 \neq T_3$. Vậy không thể có trùng khớp ở vị trí số $2$ và $3$.

Tới đây hãy nhớ lại rằng:

- $S_1 = S_4$
- $S_2 = S_5$
- $S_4 = T_4$
- $S_5 = T_5$

Ta suy ra $S_1 = T_4$, $S_2 = T_5$. Vậy ta sẽ tiếp tục kiểm tra vị trí số 4 bằng việc so sánh $S_3$ với $T_6$. Làm theo cách này, ta loại bỏ được hai trường hợp và bắt đầu duyệt lại không phải ở đầu mà ở giữa xâu $S$, tránh được việc xét lại $T_4$ và $T_5$.

## Ý tưởng chính

*Gọi $S^i$ là tiền tố độ dài $i$ của xâu $S$.*

Các ví dụ trên chính là tư tưởng hoạt động của KMP: dựa trên quan sát rằng một số xâu con của xâu cần tìm có khớp với xâu con nào khác của xâu cần tìm hay không. Tuy nhiên định hướng chung, mang tính hệ thống của thuật toán thì chưa rõ ràng. Định hướng này được phát biểu như sau:

*Ở mỗi vị trí $i$ của $S$, tìm hậu tố chuẩn dài nhất của $S^i$ mà cũng là tiền tố của $S$.* (**Hậu tố chuẩn** của một xâu là hậu tố có độ dài bé hơn xâu đó.)

Ta sẽ gọi độ dài của xâu con này là $\pi_i$. Ta cũng có thể định nghĩa $\pi_i$ là số $j$ lớn nhất để $S^j \sqsupset S^i$. Ký hiệu $X \sqsupset Y$ nghĩa là $X$ là hậu tố của $Y$.

Bảng $\pi$, gọi là **hàm tiền tố**, chiếm bộ nhớ tuyến tính, và như sẽ trình bày dưới đây, có thể tính được trong thời gian tuyến tính. Bảng sẽ chứa *toàn bộ* các thông tin cần thiết để máy thực hiện những phương án "thông minh nhất" cho quá trình tìm kiếm. Cụ thể hơn:

- Trong ví dụ 1 và 2:
    - $\pi_1 = 0$, không có tiền tố chuẩn thỏa mãn.
    - $\pi_2 = 1$, tiền tố `a` khớp hậu tố `a`.
    - $\pi_3 = 2$, tiền tố `aa` khớp hậu tố `aa`.
- Trong ví dụ 3:
    - $\pi_1 = 0$
    - $\pi_2 = 0$
    - $\pi_3 = 0$
    - $\pi_4 = 1$, tiền tố `t` khớp với xâu con `t` kết thúc ở vị trí thứ $4$.
    - $\pi_5 = 2$, tiền tố `ta` khớp với xâu con `ta` kết thúc ở vị trí thứ $5$.
    - $\pi_6 = 0$.

Tổng quát, bảng $\pi$ cho ta biết, sau một lần khớp hoặc không khớp giữa "cây kim" và "đống rơm", vị trí tiếp theo trong "đống rơm" ta cần kiểm tra là gì. Các phép so sẽ tiếp tục ở các vị trí tiếp theo, không bao giờ quay ngược về các kí tự ta đã kiểm tra rồi.

## Tính toán độ phức tạp

Để tính độ phức tạp cho hàm tiền xử lí, trước tiên ta có quan sát:

- Dãy $\pi_i^{\*} = i, \pi_i, \pi_{\pi_i}, \pi_{\pi_{\pi_i}}, ... ,0$ chứa toàn bộ những giá trị $j$ thỏa mãn $S^j \sqsupset S^i$.

Vậy, ta có thể đếm toàn bộ những hậu tố của $S^i$ đồng thời là tiền tố của $S$ bằng cách bắt đầu với $i$, dò nó trong bảng $\pi$, dùng kết quả đó dò tiếp tục và tiếp tục, đến khi kết thúc bằng $0$. 

*Chứng minh:*

- Đầu tiên ta chứng minh chiều xuôi: nếu $j$ xuất hiện trong $\pi_i^{\*}$ thì $S^j \sqsupset S^i$.
    - Nếu $j$ là phần tử đầu trong $\pi_i^{\*}$. Vậy $j = i$ và hẳn nhiên $S^j \sqsupset S^i$.
    - Nếu $j$ không là phần tử đầu: Gọi phần tử trước nó là $k$. Vậy $\pi_k = j$. Theo định nghĩa, $S^j \sqsupset S^k$. Nhưng $S^k \sqsupset S^i$. Do quan hệ này có tính chất bắc cầu, $S^j \sqsupset S^i$.

- Giờ ta chứng minh chiều ngược: nếu $S^j \sqsupset S^i$, $j$ thuộc $\pi_i^{\*}$. Giả sử $j$ không xuất hiện trong dãy. Rõ ràng $0 < j < i$ do $i$ và $0$ đều có trong dãy. Do $\pi_i^{\*}$ luôn giảm, ta có thể tìm được một và chỉ một $k$ thuộc $\pi_i^{\*}$ sao cho $k>j$ và $\pi_k<j$. Nói cách khác, ta có thể tìm được một và chỉ một $k$ mà sau nó $j$ "có lẽ" sẽ xuất hiện (để giữ cho dãy luôn giảm). Ở phần đầu chứng minh ta đã biết $S^k \sqsupset S^i$. Do hậu tố độ dài $j$ của $S^i$ là một hậu tố của hậu tố độ dài $k$ của $S^i$, hậu tố độ dài $j$ của $S^i$ phải khớp với hậu tố độ dài $j$ của $S^k$. Nhưng hậu tố độ dài $j$ của $S^i$ cũng khớp với $S^j$, nên $S^j$ khớp với hậu tố độ dài $j$ của $S^k$. Vậy ta kết luận $\pi_k \ge j$. Thế nhưng $j \ge \pi_k$, mâu thuẫn.

Cũng chính nhờ việc chứng minh này, ta có thể xây dựng một thuật toán để tính bảng $\pi$. Với mỗi $i$:

- Đầu tiên ta tìm số $j > 0$ sao cho $S^j \sqsupset S^i$.
- Nếu không tìm được, ta kết luận $\pi_i = 0$ (như trường hợp $i=1$).
- Nếu có $j > 0$ thỏa mãn, vậy khi xóa bỏ kí tự cuối của hậu tố này, ta thu được một hậu tố của $S_{i-1}$ đồng thời là tiền tố của $S$, tức là $S^{j-1} \sqsupset S^{i-1}$. Vậy bước đầu ta đếm mọi hậu tố chuẩn và không-rỗng của $S^{i-1}$ đồng thời là tiền tố của $S$. Nếu ta tìm được một hậu tố độ dài $k$ đồng thời thỏa $S_k = S_i$, vậy $S^{k+1} \sqsupset S^i$, và $k+1$ là một giá trị khả dĩ của $j$. Vậy ta sẽ gán $k = \pi_{i-1}$ và tiếp tục lặp lại trong dãy $\pi_{\pi_i}, \pi_{\pi_{\pi_i}}, ... $ Quá trình sẽ dừng lại nếu gặp phải một phần tử $j$ trong dãy sao cho $S_{j+1} = S_i$, và gán $\pi_i = j+1$; cách này sẽ luôn cho kết quả tối ưu vì dãy $\pi_{i-1}^*$ luôn giảm và nó chứa toàn bộ giá trị $k$ khả dĩ. Nếu đi đến hết dãy, vậy $\pi_i = 0$.

Dưới đây là mã giả để tính $\pi$:

```
π[1] ← 0
for i ∈ [2..m]
    k ← π[i-1]
    while k > 0 and S[k+1] ≠ S[i]
        k ← π[k]
    if S[k+1] = S[i]
        π[i] ← 0
    else
        π[i] ← k+1
```

Hoặc có thể viết gọn lại như sau:

```
π[1] ← 0
k ← 0
for i ∈ [2..m]
    while k > 0 and S[k+1] ≠ S[i]
        k ← π[k]
    if S[k+1] = S[i]
        k ← k+1
    π[i] ← k
```

Thuật toán có độ phức tạp $O(m)$. Để hiểu tại sao thì hãy để ý, `k` không bao giờ âm; nó không thể giảm nhiều hơn mức nó tăng. `k` chỉ tăng ở dòng `k ← k+1`, vốn chỉ bị gọi nhiều nhất là $m-1$ lần. Vậy `k` giảm nhiều nhất là k lần. Nhưng `k` giảm ở mỗi lần lặp của vòng `while`, vậy tổng tất cả các bước trong vòng `while` không quá $O(m)$. Tất cả những câu lệnh trong vòng `for` đều có độ phức tạp là hằng số, nên cả thuật toán có độ phức tạp $O(m)$.


## So khớp

Coi như ta đã xây dựng xong bảng $\pi$. Đây là lúc ta sử dụng những thông tin cực khổ lấy được này. Giả sử rằng ta đã kiểm tra đang vị trí thứ $j$, và $k$ kí tự đầu của $S$ đã khớp. Nói cách khác:

- $S_1 = T_j$
- $S_2 = T_{j+1}$
- $S_3 = T_{j+2}$
- ...
- $S_k = T_{j+k-1}$.

Có 2 khả năng:

- Ta muốn tiếp tục chạy trên $S$ và $T$ để kiểm tra các cặp kí tự
- Ta kiểm tra ở một ví trị khác trên $T$.

Lí do cho trường hợp 2 là:

- hoặc $k = m$ (tức đã tìm thấy một vị trí trùng khớp của $S$ trên $T$ và ta cần tiếp tục ở vị trí khác)
- hoặc $S_{k+1} \neq T_{j+k}$ (loại bỏ vị trí hiện tại).

Nếu ta đã biết từ $S_1$ đến $S_k$ khớp với từ $T_j$ đến $T_{j+k-1}$, vị trí nào ta có thể bỏ qua? Đây là cốt lõi của thuật toán KMP:

- *Định lý*: Nếu $k > 0$ thì $p = k - \pi_k$ sẽ là giá trị $p$ nhỏ nhất sao cho $S_1,...,S_{k-p}$ khớp với $T_{j+p},...,T_{j+k-1}$. (Nếu $k=0$, $p=1$.)

Nói một cách dễ hình dung hơn, ta có thể bỏ qua tất cả các vị trí từ $0$ đến $p-1$.

Suy nghĩ thật kĩ lí thuyết này.

- Nếu $p > 0$ *không thỏa mãn* $S_1,...,S_{k-p}$ khớp với $T_{j+p},...,T_{j+k-1}$, vậy $S$ **không khớp** với $T$ ở vị trí $j+p$, tức ta có thể loại bỏ vị trí này.
- Mặt khác, nếu $p > 0$ *thỏa mãn* yêu cầu trên, xâu $S$ **có khả năng** khớp với $T$ ở vị trí $j+p$, và thực tế là các kí tự từ vị trí $j+p$ đến $j+k-1$ đều đã khớp với các vị trí tương ứng ở $S$. Ta chỉ cần tiếp tục bằng cách so $S_{k-p+1}$ với $T_{j+k}$, "không quay đầu lại" như đã hứa.

*Chứng minh:*

- Có $0 \le q < k$.
- Nếu $S^q \sqsupset S^k$, vậy theo định nghĩa ta có $S_1,...,S_q = S_{k-q+1},..., S_k$. Nhưng vì $S_1,..., S_k = T_j,...,T_{j+k-1}$, nên $S_{k-q+1},...,S_k = T_{j+k-q},...,T_{j+k-1}$. Vậy $S_1,...S_q = T_{j+k-q},...,T_{j+k-1}$.
- Ngược lại, nếu không có $S^q \sqsupset S^k$, vậy $S_1,...,S_q \neq S_{k-q+1},..., S_k$, dẫn đến $S_{k-q+1},...,S_k = T_{j+k-q},...,T_{j+k-1}$ là sai, và dẫn đến $S_1,...S_q = T_{j+k-q},...,T_{j+k-1}$ là sai.

Ta kết luận rằng $k-q$ là một giá trị khả dĩ của $p$ khi và chỉ khi $S^q \sqsupset S^k$. Do maximum của $q$ là $\pi_k$, minumum của $p$ được xác định bởi $k-\pi_k$.

Dưới đây là mã giả:

```
j ← 1
k ← 0
while j+m-1 ≤ n
    while k ≤ m and S[k+1] = T[j+k]
        k ← k+1
    if k = m
        print "Match at position " j
    if k = 0
        j ← j+1
    else
        j ← j+k-π[k]
        k ← π[k]
```

Ta dò trong xâu cần search một lần một kí tự; kí tự đang được xét là nằm ở vị trí $j+k$. Nếu xảy ra không trùng khớp, ta dùng bảng $\pi$ để tìm đến vị trí khả dĩ tiếp theo.

Đoạn code tương đương dưới đây thể hiện rõ hơn việc thuật toán xét một kí tự một lần và không quay ngược lại:

```
k ← 0
for i ∈ [1..n]
    while k > 0 and S[k+1] ≠ T[i]
        k ← π[k]
    if S[k+1] = T[i]
        k ← k+1
    if k = m
        print "Match at position " i-m+1
        k ← π[k]
```

Ở đây, `i` tương ứng với `j+k` ở đoạn code trên. Mỗi lần lặp của vòng lặp trong của một trong 2 đoạn code tương ứng với một lần lặp của vòng lặp ngoài ở đoạn còn lại. Ở đoạn thứ hai, ta cũng có thể chứng minh thuật có độ phức tạp $O(n)$; mỗi lần vòng `while` ở trong được thực hiện, giá trị của `k` giảm, nhưng nó không thể giảm nhiều hơn `n` lần bởi `k` khởi đầu là không và không bao giờ âm. `k` chỉ tăng nhiều nhất một lần ở vòng lặp ngoài (tức nhiều nhất tổng cộng `n` lần). Vậy vòng lặp trong chỉ lặp nhiều nhất `n` lần, và tất cả các câu lệnh khác có độ phức tạp hằng số.

## Bài tập áp dụng:

- [VNOJ - SUBSTR](https://oj.vnoi.info/problem/SUBSTR).
    - [Code C++](http://ideone.com/4E11f6)
- [VNOJ - TWOOPERS](https://oj.vnoi.info/problem/TWOOPERS/)