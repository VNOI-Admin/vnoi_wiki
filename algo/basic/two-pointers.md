# Kĩ thuật hai con trỏ

**Tác giả:** Phan Đình Khôi - Đại học Bách Khoa Đà Nẵng

**Reviewer:** Nguyễn Khánh

[[_TOC_]]

# Lời mở đầu 
 
Bài viết này sẽ giúp bạn tìm hiểu thêm về **kỹ thuật hai con trỏ**. Kỹ thuật này không những được sử dụng khá phổ biến mà còn giúp chương trình tiết kiệm thời gian và không gian xử lý.  

# Bài toán 1
[LQDOJ - TWOPOINTERIA](https://lqdoj.edu.vn/problem/twopointeria)

Cho hai mảng số nguyên đã được **sắp xếp không giảm** $a$ và $b$ lần lượt có $n$ và $m$ phần tử. Hãy ghép chúng thành mảng $c$ được bố trí theo thứ tự **không giảm**.

Giới hạn: $n, m \leq 10^5$ và $0 \leq a_i, b_i \leq 10^{9}$.

## Phân tích

Hãy cùng xem ví dụ sau đây. 

Cho trước hai dãy số $a$ và $b$ được sắp xếp không giảm:

$$a=[1,3,6,8,10]$$

$$b=[2,6,7,12,14]$$

Làm cách nào để có thể ghép chúng thành một dãy số $c$ cũng được sắp xếp không giảm ?

Trước tiên, hãy cùng xác định phần tử đầu tiên của dãy $c$. Cần xây dựng dãy $c$ theo thứ tự không giảm, cho nên phần tử đầu tiên của dãy $c$ phải là phần tử có giá trị nhỏ nhất trong cả hai dãy $a$ và $b$. 

Ta có thể so sánh hai phần tử nhỏ nhất (đầu tiên) của hai dãy $a$, $b$ và đưa phần tử có giá trị nhỏ hơn vào vị trí đầu tiên của dãy $c$.

$$a=[\overset{\downarrow}{\color{red}1},3,6,8,10]$$

$$b=[\overset{\downarrow}{2},6,7,12,14]$$

$$c=[1]$$

Bây giờ, phần tử tiếp theo của dãy $c$ sẽ là phần tử nhỏ nhất trong các phần tử chưa được đưa vào dãy $c$.

Vì $a[1]$ đã được chọn vào dãy $c$ cho nên phần tử nhỏ nhất chưa được chọn trong dãy $a$ sẽ là phần tử $a[2]$ (dãy số $a$ được sắp xếp tăng dần).

So sánh phần tử nhỏ nhất chưa được chọn ở dãy $a$ với phần tử nhỏ nhất chưa được chọn ở dãy $b$. Đưa phần tử nhỏ hơn vào vị trí tiếp theo của dãy $c$.

$$a=[{\color{red}1},\overset{\downarrow}{3},6,8,10]$$

$$b=[\overset{\downarrow}{\color{red}2},6,7,12,14]$$

$$c=[1,2]$$

Vì $b[1]$ đã được chọn vào dãy $c$ cho nên phần tử nhỏ nhất chưa được chọn trong dãy $b$ sẽ là phần tử $b[2]$ (dãy số $b$ được sắp xếp tăng dần).

Ta nhận thấy rằng
* Tại mọi thời điểm, phần tử tiếp theo được đưa vào dãy $c$ sẽ là phần tử có giá trị nhỏ nhất trong các phần tử chưa được chọn.
* Ban đầu, lúc dãy $c$ chưa có phần tử nào
    * $a[1]$ là phần tử nhỏ nhất chưa được chọn trong dãy $a$.
    * $b[1]$ là phần tử nhỏ nhất chưa được chọn trong dãy $b$.
* Khi đưa phần tử $a[i]$ vào dãy $c$ thì phần tử nhỏ nhất chưa được chọn trong dãy $a$ sẽ là $a[i+1]$.
* Khi đưa phần tử $b[j]$ vào dãy $c$ thì phần tử nhỏ nhất chưa được chọn trong dãy $b$ sẽ là $b[j+1]$.


## Giải pháp

Dựa vào những phân tích ta có giải pháp sử dụng **hai con trỏ** như sau:

- Mảng $a$ có con trỏ $i$, con trỏ này bắt đầu ở vị trí đầu dãy $a$.
    - Con trỏ $i$ này được thể hiện như phần tử nhỏ nhất chưa được chọn trong dãy $a$.
- Mảng $b$ có con trỏ $j$, con trỏ này bắt đầu ở vị trí đầu dãy $b$.
    - Con trỏ $j$ này được thể hiện như phần tử nhỏ nhất chưa được chọn trong dãy $b$. 
- Ta sẽ lặp lại công việc này, cho đến khi đưa hết các phần tử trong mảng $a$ và $b$ vào mảng $c$:
    - Khi các phần tử trong một dãy nào đó, dãy $a$ hoặc dãy $b$, đều đã được đưa vào dãy $c$: đưa lần lượt các phần tử trong dãy còn lại vào dãy $c$.
    - Ngược lại: 
        - So sánh hai phần tử ở hai con trỏ.
        - Đưa phần tử có giá trị nhỏ hơn vào dãy $c$, nếu hai phần tử có giá trị như nhau thì chọn một trong hai.
        - Tăng vị trí con trỏ ở phần tử được đưa vào lên một đơn vị.

Để hiểu rõ hơn, ta hãy cùng xem qua ví dụ sau đây:

$a = [1, 3, 6, 8, 10], b = [2, 6, 7, 12, 14]$

* Đặt $i = 1$ và $j = 1$. \\
$a = [\overset{\underset{\downarrow}{\color{red}i}}{\color{red}1}, 3, 6, 8, 10]$\\
$b = [\underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}2}, 6, 7, 12, 14]$\\
$c = []$

* Vì $a[i]<b[j]$ nên ta đưa $a[i]$ vào mảng $c$ và tăng vị trí $i$ lên một. \\
$a = [1,\overset{\underset{\downarrow}{\color{red}i}}{\color{red}3}, 6, 8, 10]$\\
$b = [\underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}2}, 6, 7, 12, 14]$\\
$c = [1]$

* Vì $b[j]<a[i]$ nên ta đưa $b[j]$ vào mảng $c$ và tăng vị trí $j$ lên một. \\
$a = [1, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}3}, 6, 8, 10]$\\
$b = [2, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}6}, 7, 12, 14]$\\
$c = [1, 2]$

* Vì $a[i]<b[j]$ nên ta đưa $a[i]$ vào mảng $c$ và tăng vị trí $i$ lên một. \\
$a = [1, 3, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}6}, 8, 10]$\\
$b = [2, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}6}, 7, 12, 14]$\\
$c = [1, 2, 3]$

* Vì $a[i]=b[j]$ nên ta có thể đưa bất kỳ một trong hai phần tử. Ở đây ta đưa phần tử $a[i]$ vào $c$ và tăng vị trí $i$ lên một.\\
$a = [1, 3, 6, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}8}, 10]$\\
$b = [2, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}6}, 7, 12, 14]$\\
$c = [1, 2, 3, 6]$

* Vì $b[j]<a[i]$ nên ta đưa $b[j]$ vào mảng $c$ và tăng vị trí $j$ lên một. \\
$a = [1, 3, 6, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}8}, 10]$\\
$b = [2, 6, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}7}, 12, 14]$\\
$c = [1, 2, 3, 6, 6]$

* Vì $b[j]<a[i]$ nên ta đưa $b[j]$ vào mảng $c$ và tăng vị trí $j$ lên một. \\
$a = [1, 3, 6, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}8}, 10]$\\
$b = [2, 6, 7, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}, 14]$\\
$c = [1, 2, 3, 6, 6, 7]$

* Vì $a[i]<b[j]$ nên ta đưa $a[i]$ vào mảng $c$ và tăng vị trí $i$ lên một. \\
$a = [1, 3, 6, 8, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}10}]$\\
$b = [2, 6, 7, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}, 14]$\\
$c = [1, 2, 3, 6, 6, 7, 8]$

* Vì $a[i]<b[j]$ nên ta đưa $a[i]$ vào mảng $c$ và tăng vị trí $i$ lên một. \\
$a = [1, 3, 6, 8, 10]\overset{\underset{\downarrow}{\color{red}i}}{ }$\\
$b = [2, 6, 7, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}, 14]$\\
$c = [1, 2, 3, 6, 6, 7, 8, 10]$

* Vì tất cả các phần tử trong mảng $a$ đều đã được đưa vào mảng $c$ nên từ đưa lần lượt các phần tử chưa được chọn trong mảng $b$ vào trong mảng $c$ 
$c = [1, 2, 3, 6, 6, 7, 8, 10, 12, 14]$

**Cài đặt**
```cpp
int i = 1, j = 1;
vector<int> C;
while (i <= N || j <= M){
    if (j == M + 1 || (i <= N && A[i] <= B[j]))
        C.push_back(A[i++]);
    else 
        C.push_back(B[j++]);
}
for (auto it: C)
    cout << it << " ";
```
**Độ phức tạp**

Vị trí con trỏ $i$ luôn tăng và tăng quá không quá $N$ lần, vị trí con trỏ $j$ cũng luôn tăng và tăng không quá $M$ lần. Vì thế độ phức tạp của giải pháp là $O(N+M)$.

## Luyện tập

[VNOJ - NKSGAME](https://oj.vnoi.info/problem/nksgame)\\
[CODEFORCES - 1251C](https://codeforces.com/problemset/problem/1251/C)\\
[CODEFORCES - 1036D](https://codeforces.com/problemset/problem/1036/D)


# Bài toán 2
[LQDOJ - FINDPAIR](https://lqdoj.edu.vn/problem/findpair)

Cho một mảng số nguyên $A$ có $N$ phần tử, mảng này đã được **sắp xếp tăng dần**. Hãy tìm vị trí của hai phần tử **khác nhau** **bất kỳ** sao cho tổng của chúng có giá trị là $X$.

Giới hạn: $2 \leq N \leq 10^6$ và $0 \leq A_i, X \leq 10^9$

## Phân tích

Hãy cùng xem ví dụ sau đây. 

Cho trước dãy số $A$ được sắp xếp tăng dần và $X=16$:

$$A=[2,5,6,8,10,12,15]$$

Làm cách nào để có thể tìm hai vị trí khác nhau mà tổng hai phần tử ở hai vị trí đó có tổng là $X$ ?

$$A=[\overset{\downarrow}{2},5,6,8,10,12,\overset{\downarrow}{15}]$$

Trước tiên, ta có một chút nhận xét sau:
* $A[1]<A[2]<A[3]<A[4]<A[5]<A[6]<A[7]$ vì dãy $a$ tăng dần.
* $A[1]+A[7]=17>X \Rightarrow X<A[1]+A[7]<A[2]+A[7]<A[3]+A[7]<A[4]+A[7]<A[5]+A[7]<A[6]+A[7]$.

Có thể thấy, tổng của $A[7]$ với các phần tử khác trong dãy đều lớn hơn $X$. Vì thế ta loại bỏ $A[7]$ khỏi dãy.

$$A=[\overset{\downarrow}{2},5,6,8,10,\overset{\downarrow}{12},{\color{red}15}]$$

* $A[1]+A[6]=14<X \Rightarrow A[1]+A[2]<A[1]+A[3]<A[1]+A[4]<A[1]+A[5]<A[1]+A[6]<X$ vì dãy $a$ tăng dần.

Có thể thấy, tổng của $A[1]$ với các phần tử khác trong dãy đều nhỏ hơn $X$. Vì thế ta loại bỏ $A[1]$ khỏi dãy.

$$A=[{\color{red}2},\overset{\downarrow}{5},6,8,10,\overset{\downarrow}{12},{\color{red}15}]$$

Tại một thời điểm nào, dãy $A$ còn lại các phần tử trong đoạn $[i,j]$, ta có nhận xét sau:
* Nếu $i=j$, trong dãy $A$ ban đầu không tồn tại hai vị trí khác nhau mà tổng hai phần tử ở đó có giá trị là $X$.
* Ngược lại:
    * Nếu $A[i]+A[j]=X$, ta đã tìm được hai vị trí cần tìm ($i$ và $j$).
    * Nếu $A[i]+A[j]<X$, loại bỏ phần tử $i$ và tiếp tục xét các phần tử trong đoạn $[i+1,j]$.
    * Nếu $A[i]+A[j]>X$, loại bỏ phần tử $j$ và tiếp tục xét các phần tử trong đoạn $[i,j-1]$.

## Giải pháp

Từ những phân tích vừa rồi ta có giải pháp sử dụng hai con trỏ như sau:

* Một con trỏ $(i)$ được đặt ở đầu mảng $A$, con trỏ còn lại $(j)$ được đặt ở cuối mảng $A$. 
* Nếu tổng của hai phần tử ở hai vị trí con trỏ 
    * Nhỏ hơn $X$: tăng vị trí con trỏ $i$ lên một đơn vị.
    * Lớn hơn $X$: giảm vị trí con trỏ $j$ đi một đơn vị.
* Tiếp tục di chuyển cho đến khi hai con trỏ gặp nhau.
* Khi con trỏ chưa gặp nhau nhưng tổng ở hai vị trí con trỏ có giá trị là $X$ thì ta đã tìm được hai vị trí cần tìm ($i$ và $j$), kết thúc chương trình.

Để hiểu rõ hơn, ta hãy cùng xem qua một số ví dụ sau đây:

**Ví dụ 1:** $A = [2, 3, 5, 7, 9, 12]$ và $X = 16$.

* Đặt $i=1$ và $j=N$. \\
$A = [\overset{\underset{\downarrow}{\color{red}i}}{\color{red}2}, 3, 5, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $A[i]+A[j]=2+12=14<X$ nên tăng vị trí $i$ lên một đơn vị.\\
$A = [2,\overset{\underset{\downarrow}{\color{red}i}}{\color{red}3}, 5, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $A[i]+A[j]=3+12=15<X$ nên tăng vị trí $i$ lên một đơn vị.\\
$A = [2, 3, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $A[i]+A[j]=5+12=17>X$ nên giảm vị trí $j$ đi một đơn vị.\\
$A = [2, 3, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $A[i]+A[j]=5+9<X$ nên tăng vị trí $i$ lên một đơn vị.\\
$A = [2, 3, 5, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}7}, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $A[i]+A[j]=7+9=X$ nên hai vị trí cần tìm là hai vị trí $i$ và $j$.

**Ví dụ 2:** $A = [2, 5, 7, 9, 12]$ và $X = 15$.

* Đặt $i=1$ và $j=N$. \\
$A = [\overset{\underset{\downarrow}{\color{red}i}}{\color{red}2}, 5, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $A[i]+A[j]=2+12=14<X$ tăng vị trí $i$ lên một đơn vị. \\
$A = [2, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $A[i]+A[j]=5+12=17>X$ nên giảm vị trí $j$ đi một đơn vị. \\
$A = [2, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $A[i]+A[j]=5+9=14<X$ tăng vị trí $i$ lên một đơn vị. \\
$A = [2, 5, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}7}, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $A[i]+A[j]=7+9=16>X$ giảm vị trí $j$ đi một đơn vị. \\
$A = [2, 5, \overset{\underset{\downarrow}{\color{red}i}}{ \underset{\overset{\uparrow}{\color{blue}j}}{\color{purple}7}}, 9, 12]$

* Vì $i=j$ nên không tìm được hai vị trí cần tìm.

**Cài đặt**
```cpp
int i = 1, j = N;
while (i < j) {
    if (A[i] + A[j] == X) {
        cout << i << " " << j;
        return 0;
    }
    if (A[i] + A[j] < X)
        i += 1;
    else
        j -= 1;
}
cout << "No solution";
```
**Độ phức tạp**

Vị trí con trỏ $i$ luôn tăng, vị trí con trỏ $j$ thì luôn giảm. Hơn nữa, sự thay đổi vị trí hai con trỏ này sẽ dừng lại khi tổng hai phần tử ở hai vị trí con trỏ có tổng là $X$ hay khi vị trí $i$ bằng vị trí $j$. Vì thế, việc thay đổi vị trí hai con trỏ sẽ không quá $N$ lần, độ phức tạp của giải pháp là $O(N)$.

## Luyện tập
[VNOJ - NDCCARD](https://oj.vnoi.info/problem/ndccard) \\
[LQDOJ - CNTPAIR02](https://lqdoj.edu.vn/problem/cntpair02) \\
[VNOJ - TWOSUM](https://oj.vnoi.info/problem/twosum)


# Bài toán 3
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
