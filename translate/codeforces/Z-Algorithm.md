# Z Algorithm

**Nguồn:** [Codeforces](http://codeforces.com/blog/entry/3107)

**Tác giả:** [paladin8](http://codeforces.com/profile/paladin8)


Đây là bài viết đầu tiên của tôi trên blog Codeforces! Tôi dự định sẽ dùng nơi này để viết về những thuật toán mới mà mình học được, những bài toán mà tôi cho là thú vị, hay những sai lầm ngớ ngẩn mà tôi mắc phải trong các kì thị.

Chủ đề của ngày hôm nay sẽ là Z Algorithm, là thứ mà tôi học được sau khi không thể giải [Problem B ở Beta Round 93](http://codeforces.com/contest/126/problem/B). Có vài lời giải khác cho bài toán này như *tìm kiếm nhị phân + hashing*, nhưng lời giải mà chúng ta bàn ở đây là khá đẹp. Không chần chừ nữa, đầu tiên là một miêu tả về thuật toán và cách mà nó hoạt động; khá là đơn giản nhưng hiệu quả (như tất cả những thuật toán tốt khác vậy).

## Thuật toán

Cho một xâu $S$ có độ dài $n$, Z Algorithm tạo ra một mảng $Z$ trong đó $Z[i]$ là độ dài của xâu con dài nhất của $S$ bắt đầu từ $S[i]$ mà $S$ nhận làm tiền tố, nghĩa là $k$ lớn nhất sao cho $S[j]=S[i+j]$ với mọi $0 \leq j<k$. Để ý rằng $Z[i]=0$ đồng nghĩa với $S[0] \neq S[i]$. Để có được định nghĩa dễ hiểu hơn, chúng ta sẽ gọi xâu con đồng thời là tiền tố là *xâu con tiền tố*. 

Thuật toán dựa trên một bất biến quan trọng duy nhất. Khi ta duyệt qua các ký tự trong xâu (chỉ số $i$ từ $1$ tới $n-1$), ta duy trì một đoạn $[L,R]$ là đoạn có $R$ lớn nhất sao cho $1 \leq L \leq i \leq R$ và $S[L...R]$ là một xâu con tiền tố (nếu không tồn tại đoạn thỏa điều kiện, ta gán $L=R=-1$). Với $i=1$, ta có thể dễ dàng tính $L$ và $R$ bằng cách so sánh $S[0...]$ với $S[1...]$. Ta cũng sẽ có được $Z[1]$ sau bước này.

Giả sử ta đã có được đoạn $[L,R]$ đúng cho $i-1$ và tất cả giá trị $Z$ tính đến $i-1$. Ta sẽ tính $Z[i]$ và đoạn $[L,R]$ mới theo những bước sau:

- Nếu $i>R$, dễ thấy không tồn tại xâu con tiền tố của $S$ bắt đầu trước $i$ và kết thúc tại hoặc sau $i$. Nếu tồn tại xâu con như trên, theo định nghĩa, $[L,R]$ sẽ phải là đoạn chứa xâu con đó chứ không phải là giá trị hiện tại. Do vậy, ta "reset" và tính một đoạn $[L,R]$ mới bằng cách so sánh $S[0...]$ với $S[i...]$ và cùng lúc đó tính luôn $Z[i] = R-L+1$.
- Ngược lại, $i \leq R$, nghĩa là đoạn $[L,R]$ hiện tại mở rộng ít nhất đến $i$. Gọi $k=i-L$. Ta biết rằng $Z[i] \geq min(Z[k],R-i+1)$ vì $S[i...]$ khớp $S[k...]$ ít nhất $R-i+1$ kí tự (chúng thuộc đoạn $[L,R]$ mà ta biết chắc là một xâu con tiền tố). Bây giờ ta cần xem xét hai trường hợp con.
  - Nếu $Z[k]<R-i+1$ thì không có xâu con tiền tố dài hơn nào bắt đầu tại $S[i]$ (nếu không $Z[k]$ sẽ lớn hơn), nghĩa là $Z[i]=Z[k]$ và $[L,R]$ được giữ nguyên. Vế sau là đúng do $[L,R]$ chỉ thay đổi nếu tồn tại một xâu con tiền tố bắt đầu tại $S[i]$ mở rộng khỏi $R$, điều mà ta biết là không phải trường hợp đang xét.
  - Nếu $Z[k] \geq  R-i+1$ thì có thể $S[i...]$ khớp với $S[0...]$ nhiều hơn $R-i+1$ kí tự (tức là vượt quá vị trí $R$). Do vậy ta cần cập nhật $[L,R]$ bằng cách đặt $L=i$ và đối chiếu từ $S[i+1]$ trở đi để tính $R$ mới. Nhắc lại, ta cũng tính được $Z[i]$ ở bước này.

Quá trình tính tất cả giá trị $Z$ trong một lần duyệt qua xâu, do vậy việc của ta đã xong. Tính đúng đắn của quá trình gắn liền với thuật toán và tương đối trực quan để thấy.

## Phân tích

Ta khẳng định thuật toán chạy trong thời gian $O(n)$, điều này là hiển nhiên. Ta không so sánh các kí tự có vị trí nhỏ hơn $R$, và mỗi lần ta khớp được một kí tự, $R$ tăng lên một, nghĩa là có nhiều nhất $n$ phép so sánh. Cuối cùng, ta chỉ có thể so sánh sai một lần với mỗi $i$  (khiến $R$ dừng tăng lên), nên ta có nhiều nhất $n$ phép so sánh nữa, từ đó ta được tổng thời gian $O(n)$.

## Code

Đơn giản và ngắn gọn. Để ý rằng phép tối ưu $L=R=i$ được dùng khi $S[0] \neq S[i]$ (điều này không ảnh hưởng thuật toán vì ở lần duyệt tiếp theo $i>R$).

```c++
int L = 0, R = 0;
for (int i = 1; i<n; i++) {
  if (i>R) {
    L = R = i;
    while (R< n && s[R-L] == s[R]) R++;
    z[i] = R-L; R--;
  } else {
    int k = i-L;
    if (z[k] < R-i+1) z[i] = z[k];
    else {
      L = i;
      while (R< n && s[R-L] == s[R]) R++;
      z[i] = R-L; R--;
    }
  }
}
    
```



## Ứng dụng

Một ứng dung của Z Algorithm là bài toán toán so sánh xâu mẫu mực: tìm xâu khuôn $T$ có độ dài $m$ trong một xâu $S$ có độ dài $n$. Ta có thể thực hiện điều này trong thời gian $O(n+m)$ bằng cách dùng Z Algorithm trên xâu $T \Phi S$ (nghĩa là nối $T$, $\Phi$, và  $S$) với $\Phi$ là kí tự không khớp với bất kì kí tự nào. Những chỉ số $i$ với $Z[i]=m$ tương ứng với các khuôn $T$ trong xâu $S$.

Cuối cùng, để giải  [Problem B ở Beta Round 93](http://codeforces.com/contest/126/problem/B), ta chỉ việc tính $Z$ cho mảng $S$, sau đó duyệt từ $i$ tới $n-1$. Nếu $Z[i] = n-i$ thì ta biết hậu tố của $S[i]$ là một tiền tố, và nếu giá trị $Z$ lớn nhất chúng ta đã biết là lớn hơn hoặc bằng $n-i$, thì ta biết một số xâu bên trong cũng khớp với tiền tố đó. Từ đó ta được kết quả.

```c++
int maxz = 0, res =0;
for (int i = 1; i < n; i++) {
  if (z[i] == n-i && maxz >= n-i) { res = n-i; break; }
  maxz = max(maxz, z[i]);
}
```







