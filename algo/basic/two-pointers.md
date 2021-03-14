# Kĩ thuật hai con trỏ

[[_TOC_]]

# Lời mở đầu 
 
Bài viết chưa hoàn thiện

# Bài toán 1
Cho một mảng số nguyên dương **tăng dần** $ A $ gồm $ N $ phần tử và số nguyên dương $ M $, đếm số cặp $ (i, j) $ sao cho $ 1 \leq i < j \leq N $ và $ A_i + A_j \leq M $. 
Giới hạn: $ N \leq 10^6 $ và $ A_i, M \leq 10^9 $. 

## Tiếp cận 1

Cách làm đơn giản với bài toán này là duyệt tất cả các cặp $(i, j)$. 
```cpp
int ans = 0;
for (int i = 1; i < N; i++)
    for (int j = i + 1; j <= N; j++)
    {
        if (A[i] + A[j] <= M) 
            ans++;
    }
```
Độ phức tạp của cách làm này là: $O(N^2)$.
Vậy có cách nào để chúng ta có thể giảm độ phức tạp không?

## Tiếp cận 2 
Nhận thấy dãy rằng $A$ được cho là một dãy số nguyên **tăng dần**. Từ đó có thể rút ra được một số tính chất quan trọng và có thể giải quyết bài toán trong độ phức tạp ***nhỏ hơn*** với phương pháp ***hai con trỏ***. 
### Phân tích
Bởi vì $A[i] + A[j] \leq M \Leftrightarrow A[j] \leq M - A[i]$ cho nên bài toán có thể giải theo cách như sau: "Với mỗi $i$ từ $1$ đến $N$, ta tính có bao nhiêu phần tử có giá trị **không quá** $M - A[i]$ và có vị trí **lớn hơn** $i$". Để giải bài toán này, ta sẽ cùng phân tích một số tính chất của dãy $A$.
- $A[i] < A[i+1], \forall 1 \leq i < N$. Vậy thì để giải quyết bài toán trên, ta thực sự chỉ cần biết **_vị trí_** của phần tử **_lớn nhất_** có giá trị **không quá** $M-A[i]$, vị trí này phải có giá trị **lớn hơn** $i$. Bởi vì mọi phần tử **nhỏ hơn** phần tử này đều sẽ có giá trị không quá $M-A[i]$. Ta gọi vị trí của phần tử **_lớn nhất_** này là $j$.
- $M-A[i] > M-A[i+1], \forall 1 \leq i < N$. Có thể nhận thấy rằng khi $i$ **tăng lên** $1$ đơn vị thì $j$ luôn **không đổi hoặc sẽ giảm**.
Từ những phân tích trên, ta sẽ dùng phương pháp **_hai con trỏ_** để tìm giá trị của $j$, cụ thể cách tìm sẽ được nêu ở dưới đây.

![](https://i.imgur.com/caX1sWH.png)

***

Ban đầu, đặt $i$ có giá trị là $1$, $j$ có giá trị là $N$.

![](https://i.imgur.com/gf4yUcr.png)

***

Vì $A[j] > M - A[i]$ nên ta giảm $j$ đi $1$ đơn vị.

![](https://i.imgur.com/IQGV1Ne.png)

***

Vì $A[j] > M - A[i]$ nên ta giảm $j$ đi $1$ đơn vị.

![](https://i.imgur.com/HVhIBmM.png)

***

Vì $A[j] \leq M - A[i]$ nên ta sẽ cập nhật kết quả. Cụ thể là sẽ có $j$ phần tử có giá trị không quá $M-A[i]$, tuy nhiên chúng ta chỉ lấy các phần tử có vị trí lớn hơn $i$ cho nên ta cộng $j-i=4$ vào kết quả.

![](https://i.imgur.com/Ie5iYpP.png)

***

Sau khi cập nhật kết quả, ta sẽ tăng $i$ lên $1$ đơn vị.

![](https://i.imgur.com/uQu2nPq.png)

***

Vì $A[j] > M - A[i]$ nên ta giảm $j$ đi $1$ đơn vị.

![](https://i.imgur.com/rr3V0MD.png)

***

Vì $A[j] \leq M - A[i]$ nên ta sẽ cập nhật kết quả.

![](https://i.imgur.com/tRzL37B.png)

***

Sau khi cập nhật kết quả, ta sẽ tăng $i$ lên $1$ đơn vị.

![](https://i.imgur.com/o7DpiM7.png)

***

Vì $A[j] \leq M - A[i]$ nên ta sẽ cập nhật kết quả.

![](https://i.imgur.com/TOoU0H0.png)

***

Sau khi cập nhật kết quả, ta sẽ tăng $i$ lên $1$ đơn vị.

![](https://i.imgur.com/Yp7E0yu.png)

***

Vì $i$ luôn tăng, $j$ thì luôn giảm hoặc giữ nguyên, hơn nữa bây giờ $i$ đang có giá trị bằng $j$, cho nên sẽ không tồn tại thêm $i < j$ cho nên chương trình kết thúc.

![](https://i.imgur.com/L0k3MKQ.png)

### Cài đặt
```cpp
int ans = 0;
for (int i = 1, j = N; i < j; i++)
{
    while (j > i && A[j] > M - A[i])
        j--;
    ans += j - i;
}
```
**_Nhận xét:_** Con trỏ $j$ luôn luôn giảm hoặc không đổi với mỗi $i$ chạy từ $1$ đến $N$, và giảm không không quá $N$.

Vậy độ phức tạp của giải pháp là: $O(N)$

## Bài tập
*Bài 1:* Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên dương $M$, tìm cặp số $(i, j)$ sao cho $1 \leq i < j \leq N$ và $A_i + A_j = M$. Giới hạn: $N \leq 200000$ và $A_i, M \leq 10^9$. 
[Submit](https://cses.fi/problemset/task/1640)

*Bài 2:* Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên dương $M$, tìm cặp số $(i, j, k)$ sao cho $1 \leq i < j < k \leq N$ và $A_i + A_j + A_K = M$. Giới hạn: $N \leq 5000$ và $A_i, M \leq 10^9$.
[Submit](https://cses.fi/problemset/task/1641)

*Bài 3:* Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên dương $M$, tìm cặp số $(i, j, k, l)$ sao cho $1 \leq i < j < k < l \leq N$ và $A_i + A_j + A_K + A_l = M$. Giới hạn: $N \leq 1000$ và $A_i, M \leq 10^9$.
[Submit](https://cses.fi/problemset/task/1642)

# Bài toán 2
Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên dương $X$. Tìm đoạn con $[l, r]$ dài nhất sao cho tổng các phần tử trong đoạn có giá trị không quá $X$. 
Giới hạn: $N \leq 10^5$, $A_i \leq 10^9$ và $X \leq 10^{18}$. 

## Tiếp cận 1
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
Độ phức tạp của cách làm này là: $O(N^2)$.

Vậy có cách nào để chúng ta có thể giảm độ phức tạp không?
## Tiếp cận 2

Nhận thấy dãy rằng $A$ được cho là một dãy số **nguyên dương**. Từ đó có thể rút ra được một số tính chất quan trọng và có thể giải quyết bài toán trong độ phức tạp ***nhỏ hơn*** với phương pháp ***hai con trỏ***. 

### Phân tích

Để áp dụng phương pháp $2$ con trỏ cho bài toán này, ta sẽ phân tích một số điều sau:
- Vì dãy $A$ là một dãy số **nguyên dương** cho nên tổng các phần tử tử $l-1$ đến $r$ sẽ **lớn hơn** tổng các phần tử tử $l$ đến $r$. Từ đó, thay vì ta tìm đoạn $[l, r]$ **dài nhất** có tổng không quá $X$ thì ta có thể giải bài toán theo hướng này: "Với mỗi $r$ từ $1$ đến $N$, ta tìm vị trí **nhỏ nhất** $l$ sao cho tổng các phần tử từ $l$ đến $r$ có giá trị không quá $X$". 
- Ta nhận thấy khi $r$ **tăng lên** $1$ đơn vị thì $l$ sẽ **không đổi hoặc tăng lên.**

Từ những phân tích trên, ta sẽ dùng phương pháp **_hai con trỏ_** để tìm giá trị của $l$, cụ thể cách tìm sẽ được nêu ở dưới đây.

**Minh họa lại**

### Cài đặt

```cpp
for (int l = 1, r = 1; r <= N; r++){
    sum += A[r];
    while (sum > X){
        sum -= A[l];
        l++;
    }
    res = max(res, r - l + 1);
}
```
Vì $l$ luôn tăng với mỗi $r$ chạy từ $1$ đến $N$ và luôn có giá trị không quá $r+1$.

Cho nên độ phức tạp của giải pháp là: $O(N)$.

## Bài tập:
Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên không âm $K$. Tìm đoạn con $[l, r]$ dài nhất sao cho có không có quá $K$ giá trị phân biệt. 
Giới hạn: $N \leq 10^5$, $0 \leq K \leq N$ và $A_i \leq 10^{5}$.

Luyện tập thêm [tại đây](https://vnoi.info/problems/SOPENP/) và [tại đây](https://vnoi.info/problems/KRECT/)


# Bài toán 3 (Merge Sort)
Cho hai mảng số nguyên đã được **sắp xếp tăng dần** $A$ và $B$ lần lượt có $N$ và $M$ phần tử. Hãy ghép chúng thành mảng $C$ được bố trí theo thứ tự tăng dần.
Giới hạn: $N, M \leq 10^5$ và $-10^9 \leq A_i, B_i \leq 10^{9}$.

## Tiếp cận 1
Đưa từng phần tử trong mảng $A$ và mảng $B$ vào mảng $C$. Sau đó sử dụng hàm $sort$ trong $C++$ để sắp xếp.
```
for (int i = 1; i <= N; i++)
    C[i] = A[i];
for (int i = 1; i <= M; i++)
    C[i + N] = B[i];
sort(C + 1, C + N + M + 1);
```
Độ phức tạp của cách làm này là: $O((N+M)log(N+M))$.

Vậy có cách nào để chúng ta có thể giảm độ phức tạp không?

## Tiêp cận 2

Nhận thấy dãy rằng $A, B$ được cho là một dãy số **tăng dần** và cần xây dựng mảng $C$ cũng **tăng dần**. Từ đó có thể rút ra được một số tính chất quan trọng và có thể giải quyết bài toán trong độ phức tạp ***nhỏ hơn*** với phương pháp ***hai con trỏ***. 

### Phân tích

Vì cả dãy $A$, $B$ là dãy số **tăng dần** và mảng $C$ được ghép từ $A, B$ cũng là dãy **tăng dần** nên ta có một số tính chất sau:
- Tất cả các phần tử trong dãy $A$, $B$ đều xuất hiện trong dãy $C$.
- Nếu $i < j$ thì trong dãy $C$ phần tử $A[i]$ sẽ đứng trước phần tử $A[j]$.
- Nếu $i < j$ thì trong dãy $C$ phần tử $B[i]$ sẽ đứng trước phần tử $B[j]$.

Từ những tính chất trên ta có thể giải quyết bài toán với phương pháp **_hai con trỏ_**, cụ thể cách tìm sẽ được nêu ở mục dưới đây.

## Minh họa

**Minh họa lại**

## Cài đặt

```cpp
for (int i = 1, j = 1; i <= N || j <= M; ) {
    if (j == M + 1 || i <= N && A[i] < B[j]) 
        C.push_back(A[i++]);
    else
        C.push_back(B[j++]);
}
```
Vì $i, j$ luôn tăng trong đó $i$ tăng không quá $N$ đơn vị, $j$ tăng không quá $M$ đơn vị, cho nên độ phức tạp của cách làm này là $O(N+M)$, 

## Bài tập

Cho $4$ mảng số nguyên dương $A, B, C, D$ có lần lượt $NA, NB, NC, ND$ phần tử. Hãy tìm giá trị nhỏ nhất của $S = max(A_i, B_j, C_k, D_l) - min((A_i, B_j, C_k, D_l).$
Giới hạn: $NA, NB, NC, ND \leq 10^5$ và $1 \leq A_i, B_j, C_k, D_l \leq 10^{9}$.

# Bài tập 4 (Floyd's tortoise and hare)
Cho một mảng số nguyên có độ dài $n+1$ có có các giá trị nằm trong khoảng $[1, n]$. Biết rằng trong mảng có chính xác $1$ số lặp lại, hãy tìm số đó.

*Input:* $nums = [1,3,4,2,2]$
*Output:* $2$

Giới hạn : $n \leq 10^5$
Các bạn có thể tự code và submit [tại đây](https://leetcode.com/problems/find-the-duplicate-number/) 

## Tiếp cận 1
Nhận thấy rằng các số trong mảng đều có giá trị từ $1$ đến $n$. Cho nên ta có thể phương pháp đếm phân phối để giải quyết bài toán

```
for (int i = 0; i < nums.size(); i++)
    c[nums[i]]++;
for (int i = 1; i <= n; i++)
    if (nums[i] > 1){
        ans = i;
        break;
    }
```

Độ phức tạp: $O(n)$
Bộ nhớ: $O(n)$
Bộ nhớ thêm: $O(n)$

Vậy có cách nào để chúng ta có thể giảm _bộ nhớ thêm_ hay không?

### Tiếp cận 2

Để có thể giảm _bộ nhớ thêm_ ta sẽ áp dụng thuật toán _** Floyd's tortoise and hare**_.
## Phân tích
Khi ta xây dựng một đồ thị có hướng, mỗi số từ $1$ đến $n$ tương ứng với $1$ nút của đồ thị. Đồ thị có nút gốc là $nums[0]$. Từ nút gốc ta xây các cạnh có hướng như sau: Nếu trong đồ thị có nút $x$ thì sẽ một có cạnh hướng từ nút $x$ đến nút $nums[x]$. Vì trong dãy tồn tại một số được xuất hiện nhiều lần cho nên đồ thi sẽ luôn có chu trình. Dưới đây là $2$ trường hợp của đồ thị khi ta xây dựng theo cách này.
![](https://i.imgur.com/RrEww3W.png)
Bây giờ chúng ta sẽ cho $2$ con trỏ, một con trỏ có tên là con rùa(tortoise) và con trỏ còn lại tên là con thỏ(hare).

Ban đầu, cho con rùa và con thỏ đứng ở đỉnh gốc. 
![](https://i.imgur.com/p7a1PJ4.png)

Con rùa mỗi bước nó sẽ đi đến nút kề với nó.
![](https://i.imgur.com/tug84Bx.png)

Con thỏ mỗi bước nó sẽ đi đến nút kề với nút kề với nó.
![](https://i.imgur.com/vPx5ZrD.png)

Đánh dấu các đỉnh chu trình như sau:
![](https://i.imgur.com/LeN8SJJ.png)

Trong câu truyện Rùa và Thỏ, có một lúc rùa sẽ đuổi kịp Thỏ. Vậy khi sau khi bước một số bước liệu con rùa có thể bắt kịp con Thỏ hay không? 

Câu trả lời là có. Nguyên nhân xảy ra điều này chính là do đồ thị có chu trình. Cụ thể như sau:

Ta gọi $T$ là độ dài đường đi từ nút gốc đến nút đánh dấu số $0$. $C$ là độ dài chu trình. 
Vậy sau $X=T+C-T%C$ bước đi. Rùa sẽ ở nút đánh dấu số $(X-T)\%C=(C - T\%C)\%C$, Thỏ sẽ ở nút đánh dấu số $(2X-T)\%C=(T+2C-2T\%C)\%C=(C - T\%C)\%C$. Rùa sẽ gặp Thỏ tại thời điểm này tại nút $(C - T\%C)\%C$.

Tuy nhiên bài toán đặt ra là cần phải biết số ở nút $0$. Thế nên ta sẽ có $1$ thủ thuật sau. Đặt một con trỏ ở nút $(C - T\%C)\%C$, con trỏ còn lại ở nút gốc. Ta cho hai con trỏ di chuyển như con rùa ban nãy. Từ đó, hai con trỏ sẽ gặp nhau ở nút $0$. 
## Minh họa


## Cài đặt
```cpp
int findDuplicate(vector<int>& nums) {
    int tortoise = nums[0], hare = nums[0];
    while (true){
        tortoise = nums[tortoise];
        hare = nums[nums[hare]];
        if (tortoise == hare)
            break;
    }
    int p1 = nums[0], p2 = hare;
    while (p1 != p2){
        p1 = nums[p1];
        p2 = nums[p2];
    }
    return p1;
}
```

Độ phức tạp: $O(n)$
Bộ nhớ: $O(n)$
Bộ nhớ thêm: $O(1)$

# Bài tập áp dụng

Các bạn có thể thử sức [tại đây](https://vnoi.info/problems/list/?tag=73&page=1).

# Lưu ý
