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
![](https://i.imgur.com/F6MufFR.jpg)

## Phân tích

Tại sao cách làm với phương pháp hai con trỏ được nêu ở trên lại chính xác ?

Vì dãy $A$ là dãy số nguyên dương, nên tổng các phần tử trong đoạn $[l, r]$ sẽ nhỏ hơn các phần tử trong đoạn $[l', r]$ với mọi $(l' < l \leq r)$. 
Từ đó, khi $l$ là vị trị nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$(luôn tồn tại $l\leq r$ vì $A[r] \leq X$):
- Tổng các phần tử trong đoạn $[l', r]$ có giá trị lớn hơn $X$ với $1 \leq l' < l$.
- Tổng các phần tử trong đoạn $[l', r]$ có giá trị không quá $X$ với $l \leq l' \leq r$.

→ Nếu $l$ là vị trị nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$ thì đoạn con $[l, r]$ chính là đoạn con dài nhất có tổng các phần tử không quá $X$ với phần tử cuối cùng ở vị trí $r$. Bài toán sẽ được giải nếu ta biết tất cả các $l$ tương ứng với mỗi $r$ từ $1$ đến $N$. Để xác định được $l$ ta có một số nhận xét sau:
- $l$ là vị trí nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$
- $l'$ là vị trí nhỏ nhất sao cho $Sum(A[l']...A[r+1]) \leq X$
- $Sum(A[l']...A[r+1]) > Sum(A[l']...A[r])$ 
Mà $Sum(A[l']...A[r+1]) \leq X$ → $Sum(A[l']...A[r]) \leq X$. Nếu $l' < l$ thì sẽ mẫu thuần rằng $l$ là vị trị nhỏ nhất sao cho $Sum(A[l]...A[r]) \leq X$ → $l' \geq l$.

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

![](https://i.imgur.com/koxqUp7.jpg)

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
