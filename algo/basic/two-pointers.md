# Kĩ thuật hai con trỏ

[[_TOC_]]

# Lời mở đầu 
 
Bài viết chưa hoàn thiện

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

Sử dụng phương pháp **hai con trỏ** để giải quyết bài toán.

Cụ thể thuật toán như sau:

**Bước 1:** 
Con trỏ $i$ được đặt ở vị trí thứ $1$. Con trỏ $j$ được đặt ở vị trí thứ $N$. 

**Bước 2:** 
Nếu $A[i] + A[j] = X$ thì thông báo đã tìm được hai phần tử có tổng là $X$ và kết thúc chương trình.
Ngược lại, nếu $A[i] + A[j] > X$ thì con trỏ $j$ di chuyển sang trái ($j = j - 1$).
Ngược lại, nếu $A[i] + A[j] < X$ thì con trỏ $i$ di chuyển sang phải ($i = i + 1$).

**Bước 3:** Nếu $i < j$ thì quay lại bước $2$.

**Bước 4:** Thông báo không tìm được hai phần tử có tổng là $X$, kết thúc chương trình.

Cách làm này có độ phức tạp là $O(N)$.

Để hiểu rõ hơn, ta hãy cùng xem qua một số ví dụ sau đây:

![](https://i.imgur.com/RFoXIJJ.png)



![](https://i.imgur.com/QWyuRgv.png)



![](https://i.imgur.com/ztzQg4x.png)


![](https://i.imgur.com/Imwt359.png)



![](https://i.imgur.com/t9Wu3OV.png)



![](https://i.imgur.com/oXOBnLE.png)



![](https://i.imgur.com/MtF7ecN.png)



![](https://i.imgur.com/tPIaNKv.png)



![](https://i.imgur.com/xF8WUue.png)



![](https://i.imgur.com/1Pvslcv.png)



![](https://i.imgur.com/2yzAB4l.png)



![](https://i.imgur.com/wD3KLUr.png)




## Phân tích

Tại sao cách làm với phương pháp hai con trỏ được nêu ở trên lại chính xác ?


## Cài đặt

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
Cho một mảng số nguyên dương $A$ gồm $N$ phần tử và số nguyên dương $X$. Tìm đoạn con $[l, r]$ dài nhất sao cho tổng các phần tử trong đoạn có giá trị không quá $X$. 
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

Sử dụng phương pháp **hai con trỏ** để giải quyết bài toán.

Cụ thể thuật toán như sau:
**Bước 1:** 
Con trỏ $l$ được đặt ở vị trí thứ $1$. Con trỏ $r$ được đặt ở vị trí thứ $1$. 
**Bước 2:** 
Di duyển $l$ sang phải ($l = l + 1$) cho đến khi tổng các phần tử từ $l$ đến $r$ có giá trị không quá $X$.
**Bước 3:**
Cập nhật kết quả ($ans = max (ans, r - l + 1)$).
**Bước 4:**
Nếu $r < N$ thì di chuyển $r$ sang phải ($r = r + 1$) và quay lại bước $2$.
**Bước 5:** In ra kết quả và kết thúc chương trình.

Cách làm này có độ phức tạp là $O(N)$.

Để hiểu rõ hơn, ta hãy cùng xem qua một số ví dụ sau đây:

## Phân tích

Tại sao cách làm với phương pháp hai con trỏ được nêu ở trên lại chính xác ?


## Cài đặt
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


# Bài toán 3 (Merge Sort)
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

Sử dụng phương pháp **hai con trỏ** để giải quyết bài toán.

Cụ thể thuật toán như sau:
**Bước 1:** 
Con trỏ $i$ được đặt ở vị trí thứ $1$ của mảng $A$. Con trỏ $j$ được đặt ở vị trí thứ $1$ của mảng $B$. 
**Bước 2:** 
Nếu $j = M + 1$ hoặc ($i \leq N$ và $A[i] < B[j]$) thì lấy $A[i]$ vào mảng $C$, và di chuyển $i$ sang phải ($i = i + 1$).
Ngược lại, lấy $B[j]$ vào mảng $C$ và  di chuyển $j$ sang phải ($j = j + 1$).
**Bước 3:**
Nếu $i \leq N$ hoặc $j \leq M$ thì quay lại bước $2$.
**Bước 4:**
In ra mảng $C$ và kết thúc chương trình.

Cách làm này có độ phức tạp là $O(N + M)$.

Để hiểu rõ hơn, ta hãy cùng xem qua một số ví dụ sau đây:

## Phân tích
Tại sao cách làm với phương pháp hai con trỏ được nêu ở trên lại chính xác ?


## Cài đặt
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
