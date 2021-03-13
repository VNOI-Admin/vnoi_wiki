# Kĩ thuật hai con trỏ

# Lời mở đầu 
 
Bài viết chưa hoàn thiện

# Bài toán 1
Cho một mảng số nguyên dương **không giảm** $ A $ gồm $ N $ phần tử và số nguyên dương $ M $, đếm số cặp $ (i, j) $ sao cho $ 1 \leq i < j \leq N $ và $ A_i + A_j \leq M $. 
Giới hạn: $ N \leq 10^6 $ và $ A_i, M \leq 10^9 $. 

## Tiếp cận

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

Nhận thấy dãy rằng $A$ được cho là một dãy số nguyên **không giảm**. Từ đó có thể rút ra được một số tính chất quan trọng và có thể giải quyết bài toán trong độ phức tạp ***nhỏ hơn*** với phương pháp ***hai con trỏ***. 

## Phân tích 

Vì dãy $A$ là một dãy số **không giảm** nên ta có $1$ số tính chất:
- Nếu $A[i]+A[j] \leq M$ thì mọi $k=[1,j]$ thõa mãn $A[i]+A[k] \leq M$
- Nếu $A[i]+A[j] > M$ thì mọi $k=[j,N]$ thõa mãn $A[i]+A[k] > M$

Coi $j_{max}$ là giá trị lớn nhất của $j$ sao cho $A[i]+A[j]\leq M$ thì 
- mọi $k=[i+1,j_{max}]$ thõa mãn $A[i]+A[k] \leq M$
- mọi $k=[j_{max}+1,N]$ thõa mãn $A[i]+A[k] > M$

$\rightarrow$ Để tính số cặp $(i,j)$ của đề bài ta chỉ cần tính $j_{max}$ tương ứng với mỗi $i$. Nhưng ta tìm $j_{max}$ bằng cách nào?

Giả sử ta đã tìm được $j_{max}$ ứng với $i$. Khi $i$ tăng lên $1$ đơn vị thì $j_{max}$ luôn đứng yên hoặc sẽ giảm. Có thể thấy $i$ sẽ tăng không quá $N$ đơn vị, $j_{max}$ sẽ giảm không quá $N$ đơn vị. Vậy để tìm $j_{max}$ ta có thể dùng phương pháp **_hai con trỏ_**, cụ thể cách tìm sẽ được nêu ở mục dưới đây.

## Minh họa

Phương pháp ***hai con trỏ*** áp dụng trong bài toán này sẽ được minh họa chi tiết qua ví dụ sau đây:

![](https://i.imgur.com/DZNoTA0.png)

Ta đặt con trỏ $p1$ làm vai trò của $i$, con trỏ $p2$ làm vai trò của $j_{max}$. Con trỏ $p1$ được đặt ở đầu danh sách và nó sẽ được tịnh tiến đến cuối danh sách. Con trỏ $p2$ được đặt ở cuối danh sách và nó sẽ được tịnh tiến đến đầu danh sách. 
![](https://i.imgur.com/jm4Sbq1.png)

***
Vì $A[p_1] + A[p_2] = 1 + 10 = 11 > 9$ nên ta sẽ di chuyển $p2$ sang trái. 
![](https://i.imgur.com/LPWVjpy.png)

***
$A[p_1] + A[p_2] = 10 > 9$ nên ta sẽ di chuyển $p2$ sang trái. 
![](https://i.imgur.com/oyBGZUv.png)

***
$A[p_1] + A[p_2] = 9 \leq 9$ nên ta cập nhật kết quả.
![](https://i.imgur.com/xGnKLwu.png)

***
Sau khi cập nhật ta sẽ di chuyển $p1$ sang phải.
![](https://i.imgur.com/Xp5WEhz.png)

***
Vì $A[p_1] + A[p_2] = 2 + 8 = 10 > 9$ nên ta sẽ di chuyển $p2$ sang trái. 
![](https://i.imgur.com/2dp6e90.png)

***
$A[p_1] + A[p_2] = 8 \leq 9$ nên ta cập nhật kết quả.
![](https://i.imgur.com/VUPSWMa.png)

***
Sau khi cập nhật ta sẽ di chuyển $p1$ sang phải.
![](https://i.imgur.com/0BipPQc.png)

***
$A[p_1] + A[p_2] = 9 \leq 9$ nên ta cập nhật kết quả.
![](https://i.imgur.com/1TaCCfP.png)

***
Di chuyển $p1$ sang phải.
![](https://i.imgur.com/TGHFl4s.png)

***
Hiện tại $p1=p2$, tuy nhiên mình cần quan tâm các trước 
![](https://i.imgur.com/ONCVJjU.png)
  
## Cài đặt
```cpp
int p2 = N;
for (int p1 = 1; p1 < p2; p1++){
    while (p2 > p1 && A[p2] + A[p1] > M)
        p2--;
    ans += p2 - p1;
}
```
Độ phức tạp: $O(N)$
Bộ nhớ: $O(N)$
Bộ nhớ thêm: $O(1)$

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

## Tiếp cận
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

Nhận thấy dãy rằng $A$ được cho là một dãy số **nguyên dương**. Từ đó có thể rút ra được một số tính chất quan trọng và có thể giải quyết bài toán trong độ phức tạp ***nhỏ hơn*** với phương pháp ***hai con trỏ***. 

## Phân tích

Vì dãy $A$ là một dãy số **nguyên dương** nên ta có $1$ số tính chất:
- Tổng các phần tử từ $l-1$ đến $r$ luôn lớn hơn tổng các phần tử từ $l$ đến $r$
- Nếu $\sum_{i=l}^{r} A[i] \leq X$ thì mọi $k=[l,r]$ thõa mãn $\sum_{i=l}^{r} A[i] \leq X$
- Nếu $\sum_{i=l}^{r} A[i] > X$ thì mọi $k=[1,l]$ thõa mãn $\sum_{i=l}^{r} A[i] > X$

Coi $l_{min}$ là giá trị nhỏ nhất của $l$ sao cho $\sum_{i=l}^{r} A[i] \leq X$ thì 
- mọi $k=[l_{min},r]$ thõa mãn $A[i]+A[k] \leq M$
- mọi $k=[1,l_{min}-1]$ thõa mãn $A[i]+A[k] > M$

$\rightarrow$ Để tính đoạn con dài nhất thõa mãn đề bài ta chỉ cần tính $l_{min}$ tương ứng với mỗi $r$. Nhưng ta tìm $l_{min}$ bằng cách nào?

Giả sử ta đã tìm được $l_{min}$ ứng với $r$. Khi $r$ tăng lên $1$ đơn vị thì $l_{min}$ luôn đứng yên hoặc sẽ tăng. Có thể thấy $r$ sẽ tăng không quá $N$ đơn vị, $l_{min}$ sẽ tăng không quá $N$ đơn vị. Vậy để tìm $l_{min}$ ta có thể dùng phương pháp **_hai con trỏ_**, cụ thể cách tìm sẽ được nêu ở mục dưới đây.

## Minh họa
$A = [2, 6, 4, 3, 6, 8, 9], X = 20$.

Khi $\sum_{i=p2}^{p1} A[i] > X$ ta dịch chuyển $p2$ sang phải, và tất nhiên $p2$ sẽ không vượt quá $p1$.

![](https://i.imgur.com/3EBmYUf.png)
Lúc đầu gán $p1 = p2 = 1$. Mỗi khi tìm $p2$ tương ứng thì chúng ta đều cập nhật kết quả.
![](https://i.imgur.com/STRMl3K.png)
Tiếp tục tịnh tiên $p1$ sang phải cho đến khi $\sum_{i=p2}^{p1} A[i] > X$
![](https://i.imgur.com/m0hXVlt.png)
Tịnh tiến $p2$ sang phải để $\sum_{i=p2}^{p1} A[i] \leq X$
![](https://i.imgur.com/GPwCVPQ.png)
Ta lặp lại quá trình này đến khi $p1$ tới cuối danh sách
![](https://i.imgur.com/C66d283.png)
![](https://i.imgur.com/DEDHvAy.png)
![](https://i.imgur.com/50MqwPk.png)
![](https://i.imgur.com/Gs1lXHk.png)
## Cài đặt

```cpp
int p2 = 1, sum = 0, res = 0;
for (int p1 = 1; p1 <= N; p1++){
    sum += A[p1];
    while (sum > X){
        sum -= A[p2];
        p2++;
    }
    res = max(res, p1 - p2 + 1);
}
```
Độ phức tạp: $O(N)$.
Bộ nhớ: $O(N)$.
Bộ nhớ thêm: $O(1)$.

## Bài tập:
Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên không âm $K$. Tìm đoạn con $[l, r]$ dài nhất sao cho có không có quá $K$ giá trị phân biệt. 
Giới hạn: $N \leq 10^5$, $0 \leq K \leq N$ và $A_i \leq 10^{5}$.

Luyện tập thêm [tại đây](https://vnoi.info/problems/SOPENP/) và [tại đây](https://vnoi.info/problems/KRECT/)


# Bài toán 3 (Merge Sort)
Cho hai mảng số nguyên đã được **sắp xếp tăng dần** $A$ và $B$ lần lượt có $N$ và $M$ phần tử. Hãy ghép chúng thành mảng $C$ được bố trí theo thứ tự tăng dần.
Giới hạn: $N, M \leq 10^5$ và $-10^9 \leq A_i, B_i \leq 10^{9}$.

## Tiếp cận
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

Nhận thấy dãy rằng $A, B$ được cho là một dãy số **tăng dần** và cần xây dựng mảng $C$ cũng **tăng dần**. Từ đó có thể rút ra được một số tính chất quan trọng và có thể giải quyết bài toán trong độ phức tạp ***nhỏ hơn*** với phương pháp ***hai con trỏ***. 

## Phân tích

Vì cả dãy $A$, $B$ là dãy số **tăng dần** và mảng $C$ được ghép từ $A, B$ cũng là dãy **tăng dần** nên ta có một số tính chất sau:
- Tất cả các phần tử trong dãy $A$, $B$ đều xuất hiện trong dãy $C$.
- Nếu $i < j$ thì trong dãy $C$ phần tử $A[i]$ sẽ đứng trước phần tử $A[j]$.
- Nếu $i < j$ thì trong dãy $C$ phần tử $B[i]$ sẽ đứng trước phần tử $B[j]$.

Từ những tính chất trên ta có thể giải quyết bài toán với phương pháp **_hai con trỏ_**, cụ thể cách tìm sẽ được nêu ở mục dưới đây.

## Minh họa

Đặt $p1$ là con trỏ sẽ tịnh tiến trên mảng $A$, $p2$ là con trỏ trên mảng $B$. Khi đó ta chỉ cần so sánh $A[p1]$ và $B[p2]$, lấy phần tử nhỏ hơn đẩy vào mảng $C$ và tịnh tiến phần tử đó trên con trỏ.

$A=[1,5,8], B=[2,3,7]$

![](https://i.imgur.com/Ztu1p5d.png)

![](https://i.imgur.com/fGhX30u.png)

## Cài đặt

Thuật toán có độ phức tạp $O(N + M)$.
```cpp
for (int i = 1, j = 1; i <= N || j <= M; ) {
    if (j == M + 1 || i <= N && A[i] < B[j]) 
        C.push_back(A[i++]);
    else
        C.push_back(B[j++]);
}
```
## Bài tập

Cho $4$ mảng số nguyên dương $A, B, C, D$ có lần lượt $NA, NB, NC, ND$ phần tử. Hãy tìm giá trị nhỏ nhất của $S = max(A_i, B_j, C_k, D_l) - min((A_i, B_j, C_k, D_l).$
Giới hạn: $NA, NB, NC, ND \leq 10^5$ và $1 \leq A_i, B_j, C_k, D_l \leq 10^{9}$.

# Bài tập 4 (Floyd's tortoise and hare)
Cho một mảng số nguyên có độ dài $n+1$ có có các giá trị nằm trong khoảng $[1, n]$. Biết rằng trong mảng có chính xác $1$ số lặp lại, hãy tìm số đó.

*Input:* $nums = [1,3,4,2,2]$
*Output:* $2$

Giới hạn : $n \leq 10^5$
Các bạn có thể tự submit [tại đây](https://leetcode.com/problems/find-the-duplicate-number/) 

## Tiếp cận
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
Vậy sau $X=T+C-T%C$ bước đi. Rùa sẽ ở nút đánh dấu số $(X-T)%C=(C - T%C)%C$, Thỏ sẽ ở nút đánh dấu số $(2X-T)%C=(T+2C-2T%C)%C=(C - T%C)%C$. Rùa sẽ gặp Thỏ tại thời điểm này tại nút $(C - T%C)%C$.

Tuy nhiên bài toán đặt ra là cần phải biết số ở nút $0$. Thế nên ta sẽ có $1$ thủ thuật sau. Đặt một con trỏ ở nút $(C - T%C)%C$, con trỏ còn lại ở nút gốc. Ta cho hai con trỏ di chuyển như con rùa ban nãy. Từ đó, hai con trỏ sẽ gặp nhau ở nút $0$. 
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


# Bài tập áp dụng

Các bạn có thể thử sức [tại đây](https://vnoi.info/problems/list/?tag=73&page=1).

# Lưu ý
