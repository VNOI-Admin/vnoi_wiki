# Kĩ thuật hai con trỏ

**Tác giả:** Phan Đình Khôi - Đại học Bách Khoa Đà Nẵng

**Reviewer:** Nguyễn Khánh

[[_TOC_]]

# Lời mở đầu 
 
Bài viết này sẽ giúp bạn tìm hiểu thêm về **kỹ thuật hai con trỏ**. Kỹ thuật này không những được sử dụng khá phổ biến mà còn giúp chương trình tiết kiệm thời gian và không gian xử lý.  

# Bài toán 1
Cho một mảng số nguyên dương **tăng dần** $A$ gồm $N$ phần tử và số nguyên dương $X$, kiểm tra xem có hai phần tử trong dãy $A$ có tổng là $X$ hay không?

Giới hạn $2 \leq N \leq 10^5$ và $1 \leq X, A[i] \leq 10^9$

## Tiếp cận 

### Tiếp cận 1

Duyệt tất cả các cặp phần tử có trong dãy $A$.

```cpp
for (int i = 1; i < N; i++)
    for (int j = i + 1; j <= N; j++)
        if (A[i] + A[j] == X){
            cout << "True";
            return 0;
        }
cout << "False";
```

Cách làm này có độ phức tạp là $O(N^2)$.

### Tiếp cận 2

Sử dụng phương pháp **hai con trỏ** để giải quyết bài toán như sau:

- Con trỏ $i$ bắt đầu từ vị trí đầu tiên của dãy, con trỏ $j$ bắt đầu từ vị trí cuối cùng của dãy.
- Nếu tổng hai phần tử ở hai vị trí con trỏ có giá trị:
    - Nhỏ hơn $X$: tăng vị trí con trỏ $i$ lên $1$ đơn vị
    - Lớn hơn $X$: giảm vị trí con trỏ $j$ đi $1$ đơn vị
- Ta tiếp tục di chuyển vị trí hai con trỏ cho đến khi tổng hai phần tử ở hai vị trí đó có giá trị là $X$, hoặc cho đến khi hai con trỏ gặp nhau ở cùng một vị trí.
- Trong trường hợp hai con trỏ có cùng vị trí thì trong dãy $A$ không tồn tại hai phần tử có tổng là $X$. Ngược lại, trong dãy $A$ tồn tại hai phần tử có tổng là $X$.

Để hiểu rõ hơn, ta hãy cùng xem qua một số ví dụ sau đây:

**_Ví dụ 1:_** 

$A = [2, 5, 6, 8, 10, 12, 15], X = 16$

![](https://i.imgur.com/4kDvgwj.gif)

→ Dãy $A$ **tồn tại** hai phần tử có tổng là $X$.

---
**_Ví dụ 2:_** 

$A = [2, 3, 7, 8, 10, 12, 15], X = 16$

![](https://i.imgur.com/1KUtV6g.gif)

→ Dãy $A$ **không tồn tại** hai phần tử có tổng là $X$.

## Phân tích

Tại sao cách làm với phương pháp hai con trỏ được nêu ở trên lại chính xác ?

Trước tiên, ta sẽ xem xét bài toán sau: Kiểm tra trong đoạn con $[i, j]$ có tồn tại hai phần tử khác nhau có tổng là $X$ hay không. 

- Nếu đoạn con $[i, j]$ có **một** phần tử, tức $i=j$, thì chắc chắn trong đoạn sẽ không có hai phần tử khác nhau có tổng là $X$.
- Ngược lại, nếu đoạn con $[i, j]$ có ít nhất hai phần tử $(i<j)$
    - $A[i]+A[j]=X$, trong đoạn $[i,j]$ tồn tại hai phần tử khác nhau là $A[i]$ và $A[j]$ có tổng là $X$.
    - $A[i]+A[j]<X$, dãy $A$ được sắp xếp tăng dần nên các phần tử trong đoạn $[i,j]$ đều nhỏ hơn phần tử $A[j]$. Vậy tổng của $A[i]$ với mỗi phần tử trong đoạn $[i,j]$ đều có giá trị nhỏ hơn $X$. Từ đó ta không cần quan tâm đến $A[i]$ nữa mà chỉ quan tâm đến đoạn con $[i+1, j]$ mà thôi
    - $A[i]+A[j]>X$, dãy $A$ được sắp xếp tăng dần nên các phần tử trong đoạn $[i,j]$ đều lớn hơn phần tử $A[i]$. Vậy tổng của $A[j]$ với mỗi phần tử trong đoạn $[i,j]$ đều có giá trị lớn hơn $X$. Từ đó ta không cần quan tâm đến $A[j]$ nữa mà chỉ quan tâm đến đoạn con $[i, j-1]$ mà thôi.

Từ những nhận xét này, ta có được phương pháp hai con trỏ được nêu ở trên. Trong đó hai con trỏ $i$ và $j$ thể hiện thay cho đoạn con $[i, j]$. 

Ban đầu, ta đặt $i=1$ và $j=N$, vậy ta sẽ kiểm tra được sự tồn tại hai phần tử khác nhau có tổng là $X$ trong đoạn $[1, n]$, cũng chính là dãy $A$.

Ta thấy rằng độ dài của đoạn con $[i, j]$ luôn giảm, và luôn giảm không quá $N$ lần. Cho nên độ phức tạp của bài này là $O(N)$.

## Cài đặt
Các bạn có thể tham khảo cách cài đặt bài toán với phương pháp hai con trỏ sau đây:

```cpp
int i = 1, j = N;
while (i < j){
    if (A[i] + A[j] == X) {
        cout << "True";
        return 0;
    }
    if (A[i] + A[j] < X)
        i++;
    else
        j--;
}
cout << "False";
```

## Bài tập
*Bài 1:* Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên dương $M$, tìm cặp số $(i, j, k)$ sao cho $1 \leq i < j < k \leq N$ và $A_i + A_j + A_K = M$. Giới hạn: $N \leq 5000$ và $A_i, M \leq 10^9$.
[Submit](https://cses.fi/problemset/task/1641)

*Bài 2:* Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên dương $M$, tìm cặp số $(i, j, k, l)$ sao cho $1 \leq i < j < k < l \leq N$ và $A_i + A_j + A_K + A_l = M$. Giới hạn: $N \leq 1000$ và $A_i, M \leq 10^9$.
[Submit](https://cses.fi/problemset/task/1642)

# Bài toán 2
Cho một mảng số **nguyên dương** $A$ gồm $N$ phần tử và số nguyên dương $X$. Tìm độ dài đoạn con $[l, r]$ dài nhất sao cho tổng các phần tử trong đoạn có giá trị không quá $X$. 
Giới hạn: $N \leq 10^5$, $A_i \leq X \leq 10^{9}$. 

## Tiếp cận 

### Tiếp cận 1

Cách làm đơn giản với bài toán này là duyệt tất cả các cặp $(l, r)$ và dùng biến $sum$ để lưu trữ tổng các phần tử từ $l$ đến $r$. 

```cpp
int ans = 0;
for (int l = 1; l <= N; l++)
{
    int sum = 0;
    for (int r = l; r <= N; r++)
    {
        sum += A[r];
        if (sum <= X)
            ans = max(ans, r - l + 1);
    }
}
```
Cách làm này có độ phức tạp $O(N^2)$.

### Tiếp cận 2

Sử dụng phương pháp **hai con trỏ** để giải quyết bài toán như sau:

- Con trỏ $l$ và $r$ đều bắt đầu từ vị trí đầu tiên của dãy.
- Tăng dần vị trí con trỏ $r$ mỗi lần $1$ đơn vị cho đến khi con trỏ $r$ nằm ở vị trí cuối dãy.
- Mỗi khi tăng vị trí con trỏ $r$ lên $1$ đơn vị:
    - Nếu tổng các phần tử từ vị trí $l$ đến $r$ có giá trị:
        - Không quá $X$: giữ nguyên vị trí con trỏ $l$.
        - Lớn hơn $X$: tăng vị trí con trỏ $l$ cho đến khi tổng các phần tử từ vị trí $l$ đến $r$ có giá trị không quá $X$.
    - Sau khi cập nhật vị trí của con trỏ $l$, ta sẽ có một đoạn con $[l, r]$. Đoạn con này chính là đoạn con dài nhất có phần tử cuối ở vị trí $r$ và tổng các phần tử không quá $X$.
- Với mỗi $r$ từ $1$ đến $n$, ta đã biết được đoạn con dài nhất kết thúc tại $r$ với tổng các phần tử không quá $X$, từ đó kết quả của chúng ta sẽ là đoạn dài nhất trong các đoạn con này. 

Để hiểu rõ hơn, ta hãy cùng xem qua ví dụ sau đây:
$A = [3, 1, 5, 2, 5], X = 9$

![](https://i.imgur.com/AbRDNQd.gif)

## Phân tích

Tại sao cách làm với phương pháp hai con trỏ được nêu ở trên lại chính xác ?

Vì dãy $A$ là dãy số nguyên dương, nên tổng các phần tử trong đoạn $[l, r]$ sẽ nhỏ hơn các phần tử trong đoạn $[l', r]$ với mọi $(l' < l \leq r)$.

![](https://i.imgur.com/cm6ZJfw.png)

Từ đó, khi $l$ là vị trị nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$(luôn tồn tại $l\leq r$ vì $A[r] \leq X$):
- Tổng các phần tử trong đoạn $[l', r]$ có giá trị lớn hơn $X$ với $1 \leq l' < l$.
- Tổng các phần tử trong đoạn $[l', r]$ có giá trị không quá $X$ với $l \leq l' \leq r$.

→ Nếu $l$ là vị trị nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$ thì đoạn con $[l, r]$ chính là đoạn con dài nhất có tổng các phần tử không quá $X$ với phần tử cuối cùng ở vị trí $r$. Bài toán sẽ được giải nếu ta biết tất cả các $l$ tương ứng với mỗi $r$ từ $1$ đến $N$. 

Đặt $l$ là vị trí nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$. Đặt $l'$ là vị trí nhỏ nhất sao cho $Sum(A[l']...A[r+1]) \leq X$.

$Sum(A[l']...A[r+1]) > Sum(A[l']...A[r])$ trong khi đó $Sum(A[l']...A[r+1]) \leq X$. Vậy $Sum(A[l']...A[r]) \leq X$. 

Ta có nhận xét sau: Nếu $l' < l$ thì sẽ mẫu thuẫn rằng $l$ là vị trị nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$ → $l' \geq l$. Vậy các giá trị $l$ tương ứng với mỗi $r$ từ $1$ đến $N$ sẽ có giá trị **không giảm**.

Từ những nhận xét này, ta có được phương pháp hai con trỏ được nêu ở trên. Nhận thấy rằng con trỏ $l$ và con trỏ $r$ luôn tăng và tăng không quá $N$ lần, cho nên độ phức tạp của bài này là $O(N)$.

## Cài đặt

Các bạn có thể tham khảo cách cài đặt bài toán với phương pháp hai con trỏ sau đây:

```cpp
for (int l = 1, r = 1; r <= N; r++){
    sum += A[r];
    while (sum > X){
        sum -= A[l];
        l++;
    }
    ans = max(ans, r - l + 1);
}
cout << ans;
```

## Bài tập:
Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên không âm $K$. Tìm đoạn con $[l, r]$ dài nhất sao cho có không có quá $K$ giá trị phân biệt. 
Giới hạn: $N \leq 10^5$, $0 \leq K \leq N$ và $A_i \leq 10^{5}$.

Luyện tập thêm [tại đây](https://vnoi.info/problems/SOPENP/) và [tại đây](https://vnoi.info/problems/KRECT/)


# Bài toán 3 
Cho hai mảng số nguyên đã được **sắp xếp tăng dần** $A$ và $B$ lần lượt có $N$ và $M$ phần tử. Hãy ghép chúng thành mảng $C$ được bố trí theo thứ tự tăng dần.
Giới hạn: $N, M \leq 10^5$ và $-10^9 \leq A_i, B_i \leq 10^{9}$.

## Tiếp cận

### Tiếp cận 1
Đưa từng phần tử trong mảng $A$ và mảng $B$ vào mảng $C$. Sau đó sử dụng hàm $sort$ trong $C++$ để sắp xếp.
```cpp
for (int i = 1; i <= N; i++)
    C[i] = A[i];
for (int i = 1; i <= M; i++)
    C[i + N] = B[i];
sort(C + 1, C + N + M + 1);
```
Độ phức tạp của cách làm này là: $O((N+M)log(N+M))$.

### Tiếp cận 2

Sử dụng phương pháp **hai con trỏ** để giải quyết bài toán như sau:

- Mảng $A$ có con trỏ $i$, con trỏ này bắt đầu ở vị trí đầu dãy $A$.
- Mảng $B$ có con trỏ $j$, con trỏ này bắt đầu ở vị trí đầu dãy $B$.
- Ta sẽ lập lại công việc này, cho đến khi đưa hết các phần tử trong mảng $A$ và $B$ vào mảng $C$:
    - Khi các phần tử trong một dãy nào đó, dãy $A$ hoặc dãy $B$, đều đã được đưa vào dãy $C$: Đưa các phần tử trong dãy còn lại vào dãy $C$.
    - Ngược lại: 
        - So sánh hai phần tử ở hai con trỏ,
        - Đưa phần tử có giá trị nhỏ hơn vào dãy $C$, nếu hai phần tử có giá trị như nhau thì chọn $1$ trong $2$.
        - Tăng vị trí con trỏ ở phần tử đó lên $1$ đơn vị.

Để hiểu rõ hơn, ta hãy cùng xem qua ví dụ sau đây:

$A = [3, 5, 6, 9], B = [2, 6, 10]$

![](https://i.imgur.com/xsfppEM.gif)

## Phân tích
Tại sao cách làm với phương pháp hai con trỏ được nêu ở trên lại chính xác ?

Ta cần xây dựng mảng $C$ là một mảng tăng dần nên mỗi phần tử đưa vào mảng $C$ chính là phần tử nhỏ nhất trong các phần tử chưa được đưa vào trong hai mảng $A$ và $B$. Với phương pháp hai con trỏ được nêu trên, con trỏ $i$ chính là phần tử dãy $A$ nhỏ nhất chưa được đưa vào $C$, con trỏ $j$ chính là phần tử dãy $B$ nhỏ nhất chưa được đưa vào $C$. 

Để biết được phần tử tiếp theo ta cần thêm vào, ta chỉ cần so sánh hai phần tử chưa được đưa vào nhỏ nhất mỗi mảng $A$ và $B$ và đưa phần tử có giá trị nhỏ hơn vào. Vì dãy $A$ đã được sắp xếp tăng dần cho nên khi ta đưa $A[i]$ vào mảng $C$ thì $A[i+1]$ sẽ là phần tử dãy $A$ nhỏ nhất chưa được đưa vào $C$. Tương tự, dãy $B$ đã được sắp xếp tăng dần cho nên khi ta đưa $B[j]$ vào mảng $C$ thì $B[j+1]$ sẽ là phần tử dãy $B$ nhỏ nhất chưa được đưa vào $C$. Khi thêm các phần tử như vậy vào mảng $C$, ta sẽ được một mảng $C$ được ghép từ mảng $A$ và mảng $B$ và các phần tử $C$ được bố trí theo thứ tự tăng dần.

Nhận thấy, con trỏ $i$, $j$ đều tăng, trong đó $i$ luôn tăng không quá $N$ lần, $j$ tăng không quá $M$ lần. Vì vậy độ phức tạp của bài toán là $O(N+M)$.

## Cài đặt

Các bạn có thể tham khảo cách cài đặt bài toán với phương pháp hai con trỏ sau đây:

```cpp
int i = 1, j = 1;
vector<int> C;
while (i <= N || j <= M){
    if (j == M + 1 || (i <= N && A[i] < B[j]))
        C.push_back(A[i++]);
    else 
        C.push_back(B[j++]);
}
```

## Bài tập

Cho $4$ mảng số nguyên dương $A, B, C, D$ có lần lượt $NA, NB, NC, ND$ phần tử. Hãy tìm giá trị nhỏ nhất của $S = max(A_i, B_j, C_k, D_l) - min((A_i, B_j, C_k, D_l).$
Giới hạn: $NA, NB, NC, ND \leq 10^5$ và $1 \leq A_i, B_j, C_k, D_l \leq 10^{9}$.

# Floyd's tortoise and hare
## Vấn đề
Bạn được cho một danh sách liên kết đơn (Singly linked list) **có chu kỳ**, bạn hãy xác định node bắt đầu chu kỳ.

![](https://i.imgur.com/nFttOjY.png)

## Phát biểu thuật toán

Đặt 2 con trỏ ở đầu danh sách liên kết. Trong đó một con trỏ tương trưng cho con rùa (tortoise), một con trỏ tương trưng cho con thỏ (hare).

![](https://i.imgur.com/NfhJ6xm.png)

Trong mỗi lần di chuyển, con rùa sẽ di chuyển đến node kề với nó.

![](https://i.imgur.com/UNh9n0T.png)

Với con thỏ, nó sẽ di chuyển nhanh hơn con rùa. Trong mỗi lần di chuyển con thỏ sẽ đi đến node kề với node kề nó.

![](https://i.imgur.com/gyZ1TQY.png)

Thỏ và rùa cùng di chuyển với nhau. Mặc dù, Thỏ luôn di chuyển nhanh hơn rùa nhưng rùa và thỏ sẽ gặp nhau tại một node nào đó trong chu kỳ.

Thật vậy, đặt $T$ là số bước đi mà rùa đến với node bắt đầu chu kỳ, $C$ là độ dài của chu kỳ và đánh số các node trong chu kỳ như sau.

![](https://i.imgur.com/S2Y1N7g.png)

Khi con rùa đi được $X$ bước $(X \geq T)$ thì con rùa sẽ đi tới một trong các node của chu kỳ, và nó ở node đánh dấu $(X-T)\%C$. Và con thỏ cũng tới một trong các node của chu kỳ, và nó ở node đánh dấu $(2X-T)\%C$. Khi rùa và thỏ gặp nhau thì $(X-T)\%C=(2X-T)\%C → X\%C=0$. Vì thế khi rùa đi được $X$ bước trong đó $X \geq T$ và $X\%C=0$ thì rùa sẽ gặp được thỏ, và chúng sẽ luôn gặp ở node đánh dấu $(C-T\%C)\%C$.

Lúc rùa và thỏ gặp nhau, nếu con rùa đi tiếp $T$ bước thì con rùa sẽ luôn ở node $0$ (node bắt đầu chu trình). Vì vậy, sau khi rùa và thỏ gặp nhau, ta chỉ cần đặt thêm một con trỏ $p$ ở đầu danh sách liên kết (con trỏ này di chuyển tương tự con rùa). Để con trỏ $p$ cùng di chuyển với con rùa. Con trỏ $p$ và con rùa sẽ gặp nhau lần đầu tiên tại node $0$ vì cần $T$ bước để con trỏ $p$ đi chuyển từ node đầu danh sách đến node $0$.

![](https://i.imgur.com/Pba7UKt.gif)

# Bài tập áp dụng

Các bạn có thể luyện tập thêm [tại đây](https://vnoi.info/problems/list/?tag=73&page=1).
