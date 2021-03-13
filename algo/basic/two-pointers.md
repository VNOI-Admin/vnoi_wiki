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

Vì dãy $A$ là một dãy số không giảm nên ta có $1$ số tính chất:
- Nếu $A[i]+A[j] \leq M$ thì mọi $k=[1,j]$ thõa mãn $A[i]+A[k] \leq M$
- Nếu $A[i]+A[j] > M$ thì mọi $k=[j,N]$ thõa mãn $A[i]+A[k] > M$

Coi $j_{max}$ là giá trị lớn nhất của $j$ sao cho $A[i]+A[j]\leq M$ thì 
- mọi $k=[1,j_{max}]$ thõa mãn $A[i]+A[k] \leq M$
- mọi $k=[j_{max}+1,N]$ thõa mãn $A[i]+A[k] > M$

$\rightarrow$ Để tính số cặp $(i,j)$ của đề bài ta chỉ cần tính $j_{max}$ tương ứng với mỗi $i$. Nhưng ta tìm $j_{max}$ bằng cách nào?

Giả sử ta đã tìm được $j_{max}$ ứng với $i$. Khi $i$ tăng lên $1$ đơn vị thì $j_{max}$ luôn đứng yên hoặc sẽ giảm. Có thể thấy $i$ sẽ tăng không quá $N$ đơn vị, $j_{max}$ sẽ giảm không quá $N$ đơn vị. Vậy để tìm $j_{max}$ ta có thể dùng phương pháp **_hai con trỏ_**, cụ thể cách tìm sẽ được nêu ở mục dưới đây.

## Giải pháp

Từ những nhận xét vừa rồi, ta có thể tìm $j_{max}$ qua phương pháp *hai con trỏ*, trong đó $i$ sẽ đóng vai trò con trỏ $p1$ đặt ở $A[1]$ và $j_{max}$ sẽ đóng vai trò con trỏ $p2$ đặt ở $A[N]$.

![](https://i.imgur.com/bFbQe2O.png)

Đối với mỗi $p_1$ chúng ta sẽ đi tìm $p_2$ tương  ứng với nó(tìm $j_{max}$ tương ứng với $i$). Khi gặp điều kiện $A[p_1] + A[p_2] > M$, ta sẽ di chuyển $p2$ sang trái cho đến khi $A[p_1]+A[p_2] \leq M$. Sau khi tìm được $p2$, hãy di chuyển $p_1$ sang phải. 

Lặp lại quá trình này cho đến khi ***không tồn tại*** $p_2$ sao cho $p_2>p_1$ và $A[p_1]+A[p_2]\leq M.$ Bởi vì, khi gặp điều kiện này thì mọi $p = [p1, N]$ sẽ đều ***không tồn tại*** $p_2$ sao cho $p_2>p$ và $A[p]+A[p_2]\leq M.$


Cụ thể cách giải quyết sẽ được nêu dưới đây:

$A = [1, 2, 3, 6, 8, 9, 10], M = 9, p_1=1, p_2=N$.
___
Vì $A[p_1] + A[p_2] = 1 + 10 = 11 > 9$ nên ta sẽ di chuyển $p2$ sang trái. 
![](https://i.imgur.com/LPWVjpy.png)
___
$A[p_1] + A[p_2] = 10 > 9$ nên ta sẽ di chuyển $p2$ sang trái. 
![](https://i.imgur.com/oyBGZUv.png)
___
$A[p_1] + A[p_2] = 9 \leq 9$ nên ta cập nhật kết quả.
![](https://i.imgur.com/xGnKLwu.png)
___
Sau khi cập nhật ta sẽ di chuyển $p1$ sang phải.
![](https://i.imgur.com/Xp5WEhz.png)
___
Vì $A[p_1] + A[p_2] = 2 + 8 = 10 > 9$ nên ta sẽ di chuyển $p2$ sang trái. 
![](https://i.imgur.com/2dp6e90.png)
___
$A[p_1] + A[p_2] = 8 \leq 9$ nên ta cập nhật kết quả.
![](https://i.imgur.com/VUPSWMa.png)
___
Sau khi cập nhật ta sẽ di chuyển $p1$ sang phải.
![](https://i.imgur.com/0BipPQc.png)
___
$A[p_1] + A[p_2] = 9 \leq 9$ nên ta cập nhật kết quả.
![](https://i.imgur.com/1TaCCfP.png)
___
Di chuyển $p1$ sang phải.
![](https://i.imgur.com/TGHFl4s.png)
___
Bây giờ chúng ta có thể dừng chương trình bởi vì ***không tồn tại*** $p_2$ sao cho $p_2>p_1$ và $A[p_1]+A[p_2]\leq M.$ Kết quả của chúng ta là $ans =7$.
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

## Cách giải
Nhận xét bài toán như sau:
* Duyệt $r$ từ $1$ đến $N$ và tìm $l_{min}$ sao cho $\sum_{i=l_{min}}^{r} A[i] \leq X$
* $l_{min}$ luôn nhận giá trị tăng dần từ $1 \rightarrow N$ và luôn không vượt quá $r$. 

Sử dụng phương pháp hai con trỏ, trong đó $r$ sẽ đóng vai trò con trỏ $p1$ và $l_{min}$ sẽ đóng vai trò con trỏ $p2$. Cụ thể như sau: 

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

Vì $p2$ luôn tăng dần từ $1$ đến $N$ cho nên độ phức tạp của thuật toán là $O(N)$.
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
## Bài tập:
Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên không âm $K$. Tìm đoạn con $[l, r]$ dài nhất sao cho có không có quá $K$ giá trị phân biệt. 
Giới hạn: $N \leq 10^5$, $0 \leq K \leq N$ và $A_i \leq 10^{5}$.

Luyện tập thêm [tại đây](https://vnoi.info/problems/SOPENP/) và [tại đây](https://vnoi.info/problems/KRECT/)


# Bài toán 3 (Merge Sort)
Cho hai mảng số nguyên đã được **sắp xếp tăng dần** $A$ và $B$ lần lượt có $N$ và $M$ phần tử. Hãy ghép chúng thành mảng $C$ được bố trí theo thứ tự tăng dần.
Giới hạn: $N, M \leq 10^5$ và $-10^9 \leq A_i, B_i \leq 10^{9}$.

## Cách giải

Đặt $p1$ là con trỏ sẽ tịnh tiến trên mảng $A$, $p2$ là con trỏ trên mảng $B$. Khi đó ta chỉ cần so sánh $A[p1]$ và $B[p2]$, lấy phần tử nhỏ hơn đẩy vào mảng $C$ và tịnh tiến phần tử đó trên con trỏ.

$A=[1,5,8], B=[2,3,7]$

![](https://i.imgur.com/Ztu1p5d.png)

![](https://i.imgur.com/fGhX30u.png)

## Cài đặt

Thuật toán có độ phức tạp $O(N)$.
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

Các bạn có thể tự submit [tại đây](https://leetcode.com/problems/find-the-duplicate-number/) 

## Cách giải, phân tích

[Theo nguyên lý Dirichlet](https://vi.wikipedia.org/wiki/Nguy%C3%AAn_l%C3%BD_ng%C4%83n_k%C3%A9o_Dirichlet), trong mảng $n+1$ phần tử nhận các giá trị từ $1$ đến $n$ thì luôn xuất hiện ít nhất một số lặp lại. Tuy nhiên dữ liệu vào luôn nhận chỉ có chính xác $1$ số lặp lại và có thể lặp lại nhiều lần.

Bài toán này có rất nhiều cách giải khác nhau, ta hãy so sánh một số cách giải sau đây:

**Cách 1**
Sau khi sắp xếp dãy số này theo thứ tự tăng dần, thì các số lặp lại sẽ đứng sát nhau. Từ đó ta chỉ cần so sánh hai phần tử liền kề để biết được kết quả.

Thời gian: $O(nlog(n))$
Bộ nhớ thêm: $O(1)$

**Cách 2**
Đếm phân phối giá trị trong mảng, từ đó dễ dàng tìm được kết quả.

Thời gian: $O(n)$
Bộ nhớ thêm: $O(n)$

**Cách 3**
Sử dụng thuật toán **Floyd's tortoise and hare**

Thời gian: $O(n)$
Bộ nhớ thêm: $O(1)$

Cụ thể như sau:

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
