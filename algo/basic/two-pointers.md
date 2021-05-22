# Kĩ thuật hai con trỏ

**Tác giả:** Phan Đình Khôi - Đại học Bách Khoa Đà Nẵng

**Reviewer:** Nguyễn Khánh

[[_TOC_]]

# Lời mở đầu 
 
Bài viết này sẽ giúp bạn tìm hiểu thêm về **kỹ thuật hai con trỏ**. Kỹ thuật này không những được sử dụng khá phổ biến mà còn giúp chương trình tiết kiệm thời gian và không gian xử lý.  

# Bài toán 1

Cho hai mảng số nguyên đã được **sắp xếp không giảm** $a$ và $b$ lần lượt có $n$ và $m$ phần tử. Hãy ghép chúng thành mảng $c$ được bố trí theo thứ tự **không giảm**.

Giới hạn: $n, m \leq 10^5$ và $0 \leq a_i, b_i \leq 10^{9}$.

Xem chi tiết [tại đây](https://lqdoj.edu.vn/problem/twopointeria)
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
    * Bằng cách so sánh phần tử nhỏ nhất chưa được chọn ở dãy $a$ và phần tử nhỏ nhất chưa được chọn ở dãy $b$, phần tử nhỏ hơn sẽ được chọn vào dãy $c$.  
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
vector<int> c;
while (i <= n || j <= m){
    if (j == m + 1 || (i <= m && a[i] <= b[j]))
        c.push_back(a[i++]);
    else 
        c.push_back(b[j++]);
}
for (auto it: c)
    cout << it << " ";
```
**Độ phức tạp**

Vị trí con trỏ $i$ luôn tăng và tăng quá không quá $n$ lần, vị trí con trỏ $j$ cũng luôn tăng và tăng không quá $m$ lần. Vì thế độ phức tạp của giải pháp là $O(n+m)$.

## Luyện tập

[VNOJ - NKSGAME](https://oj.vnoi.info/problem/nksgame)\\
[CODEFORCES - 1251C](https://codeforces.com/problemset/problem/1251/C)\\
[CODEFORCES - 1036D](https://codeforces.com/problemset/problem/1036/D)


# Bài toán 2

Cho một mảng số nguyên $a$ có $n$ phần tử, mảng này đã được **sắp xếp tăng dần**. Hãy tìm vị trí của hai phần tử **khác nhau** **bất kỳ** sao cho tổng của chúng có giá trị là $x$.

Giới hạn: $2 \leq n \leq 10^6$ và $0 \leq a_i, x \leq 10^9$

Xem chi tiết [tại đây](https://lqdoj.edu.vn/problem/findpair)

## Phân tích

Hãy cùng xem ví dụ sau đây. 

Cho trước dãy số $a$ được sắp xếp tăng dần và $x=16$:

$$a=[2,5,6,8,10,12,15]$$

Làm cách nào để có thể tìm hai vị trí khác nhau mà tổng hai phần tử ở hai vị trí đó có tổng là $x$ ?

$$a=[\overset{\downarrow}{2},5,6,8,10,12,\overset{\downarrow}{15}]$$

Trước tiên, ta có một chút nhận xét sau:
* $a[1]<a[2]<a[3]<a[4]<a[5]<a[6]<a[7]$ vì dãy $a$ tăng dần.
* $a[1]+a[7]=17>X \Rightarrow X<a[1]+a[7]<a[2]+a[7]<a[3]+a[7]<a[4]+a[7]<a[5]+a[7]<a[6]+a[7]$.

Có thể thấy, tổng của $a[7]$ với các phần tử khác trong dãy đều lớn hơn $X$. Vì thế ta không quan tâm đến $a[7]$ nữa.

$$a=[\overset{\downarrow}{2},5,6,8,10,\overset{\downarrow}{12},{\color{red}15}]$$

* $a[1]+a[6]=14<X \Rightarrow a[1]+a[2]<a[1]+a[3]<a[1]+a[4]<a[1]+a[5]<a[1]+a[6]<X$ vì dãy $a$ tăng dần.

Có thể thấy, tổng của $a[1]$ với các phần tử khác trong dãy đều nhỏ hơn $x$. Vì thế ta không quan tâm đến $a[1]$ nữa.

$$a=[{\color{red}2},\overset{\downarrow}{5},6,8,10,\overset{\downarrow}{12},{\color{red}15}]$$

Như vậy, tại một thời điểm bất kỳ, những phần tử chúng ta cần quan tâm đến sẽ là các phần tử trong đoạn $[i,j]$ nào đó.

Ta có một số nhận xét sau:
* Nếu $i=j$, trong dãy $A$ ban đầu không tồn tại hai vị trí khác nhau mà tổng hai phần tử ở đó có giá trị là $X$.
* Ngược lại:
    * Nếu $a[i]+a[j]=X$, ta đã tìm được hai vị trí cần tìm ($i$ và $j$).
    * Nếu $a[i]+a[j]<X$, không quan tâm đến $a[i]$ nữa và các phần tử chúng ta cần quan tâm đó là các phần tử trong đoạn $[i+1,j]$.
    * Nếu $a[i]+a[j]>X$, không quan tâm đến $a[j]$ nữa và các phần tử chúng ta cần quan tâm đó là các phần tử trong đoạn $[i,j-1]$.

## Giải pháp

Từ những phân tích vừa rồi ta có giải pháp sử dụng hai con trỏ như sau:

* Một con trỏ $(i)$ được đặt ở đầu mảng $A$, con trỏ còn lại $(j)$ được đặt ở cuối mảng $A$.
* Nếu tổng của hai phần tử ở hai vị trí con trỏ 
    * Nhỏ hơn $X$: tăng vị trí con trỏ $i$ lên một đơn vị.
    * Lớn hơn $X$: giảm vị trí con trỏ $j$ đi một đơn vị.
* Tiếp tục di chuyển cho đến khi hai con trỏ gặp nhau.
* Khi con trỏ chưa gặp nhau nhưng tổng ở hai vị trí con trỏ có giá trị là $X$ thì ta đã tìm được hai vị trí cần tìm ($i$ và $j$), kết thúc chương trình.

Để hiểu rõ hơn, ta hãy cùng xem qua một số ví dụ sau đây:

**Ví dụ 1:** $a = [2, 3, 5, 7, 9, 12]$ và $x = 16$.

* Đặt $i=1$ và $j=N$. \\
$a = [\overset{\underset{\downarrow}{\color{red}i}}{\color{red}2}, 3, 5, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $a[i]+a[j]=2+12=14<x$ nên tăng vị trí $i$ lên một đơn vị.\\
$a = [2,\overset{\underset{\downarrow}{\color{red}i}}{\color{red}3}, 5, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $a[i]+a[j]=3+12=15<x$ nên tăng vị trí $i$ lên một đơn vị.\\
$a = [2, 3, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $a[i]+a[j]=5+12=17>x$ nên giảm vị trí $j$ đi một đơn vị.\\
$a = [2, 3, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $a[i]+a[j]=5+9<x$ nên tăng vị trí $i$ lên một đơn vị.\\
$a = [2, 3, 5, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}7}, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $a[i]+a[j]=7+9=x$ nên hai vị trí cần tìm là hai vị trí $i$ và $j$.

**Ví dụ 2:** $a = [2, 5, 7, 9, 12]$ và $x = 15$.

* Đặt $i=1$ và $j=N$. \\
$a = [\overset{\underset{\downarrow}{\color{red}i}}{\color{red}2}, 5, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $a[i]+a[j]=2+12=14<x$ tăng vị trí $i$ lên một đơn vị. \\
$a = [2, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, 9, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}12}]$

* Vì $a[i]+a[j]=5+12=17>x$ nên giảm vị trí $j$ đi một đơn vị. \\
$a = [2, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}5}, 7, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $a[i]+a[j]=5+9=14<x$ tăng vị trí $i$ lên một đơn vị. \\
$a = [2, 5, \overset{\underset{\downarrow}{\color{red}i}}{\color{red}7}, \underset{\overset{\uparrow}{\color{blue}j}}{\color{blue}9}, 12]$

* Vì $a[i]+a[j]=7+9=16>x$ giảm vị trí $j$ đi một đơn vị. \\
$a = [2, 5, \overset{\underset{\downarrow}{\color{red}i}}{ \underset{\overset{\uparrow}{\color{blue}j}}{\color{purple}7}}, 9, 12]$

* Vì $i=j$ nên không tìm được hai vị trí cần tìm.

**Cài đặt**
```cpp
int i = 1, j = N;
while (i < j) {
    if (a[i] + a[j] == x) {
        cout << i << " " << j;
        return 0;
    }
    if (a[i] + a[j] < x)
        i += 1;
    else
        j -= 1;
}
cout << "No solution";
```
**Độ phức tạp**

Vị trí con trỏ $i$ luôn tăng, vị trí con trỏ $j$ thì luôn giảm. Hơn nữa, sự thay đổi vị trí hai con trỏ này sẽ dừng lại khi tổng hai phần tử ở hai vị trí con trỏ có tổng là $X$ hay khi vị trí $i$ bằng vị trí $j$. Vì thế, việc thay đổi vị trí hai con trỏ sẽ không quá $n$ lần, độ phức tạp của giải pháp là $O(n)$.

## Luyện tập
[LQDOJ - CNTPAIR02](https://lqdoj.edu.vn/problem/cntpair02) \\
[VNOJ - NDCCARD](https://oj.vnoi.info/problem/ndccard) \\
[VNOJ - TWOSUM](https://oj.vnoi.info/problem/twosum)

# Bài toán 3
Cho dãy số nguyên dương $a$ có $n$ phần tử. Hãy tìm độ dài đoạn con dài nhất trong dãy sao cho tổng các phần tử trong đoạn này không quá $s$.

Dữ liệu đảm bảo các phần tử trong dãy $a$ đều có giá trị không quá $s$.

Giới hạn: $1\leq n \leq 10^6$, $1 \leq a_i \leq 10^9$ và $s \leq 10^{18}$.

## Phân tích

Để dễ dàng phân tích, ta tạm gọi 
* $sum(l,r)$ là tổng các phần tử trong đoạn $[l,r]$.
* Một đoạn con $[l,r]$ là đoạn con "tốt" nếu $sum(l,r) \leq s$

Qua đây, bài toán của chúng ta sẽ là tìm độ dài đoạn con "tốt" dài nhất.

Vì dãy $a$ là một dãy số nguyên dương cho nên

* $sum(1,r)>sum(2,r)>...>sum(r-1,r)>sum(r,r)$.
* Nếu đoạn con $[l,r]$ là đoạn con "tốt" thì với mọi $x\geq l$, đoạn $[x,r]$ là đoạn con "tốt".
* Nếu đoạn con $[l,r]$ không là đoạn con "tốt" thì với mọi $x \leq l$, đoạn $[x,r]$ không là đoạn con "tốt".

Với $r$ là một vị trí bất kỳ, nếu như $l$ là vị trí nhỏ nhất sao cho đoạn $[l,r]$ là một đoạn "tốt" thì
* mọi $x \geq l$ thì đoạn con $[x,r]$ là một đoạn "tốt".
* mọi $x < l$ thì đoạn con $[x,r]$ không là một đoạn "tốt".
* đoạn con $[l,r]$ là một đoạn con "tốt" dài nhất trong các đoạn con "tốt" có vị trí kết thúc tại $r$.

Từ đó, với mỗi $r$ từ $1$ đến $n$, nếu ta xác định được vị trí $l$, ta có thể biết được độ dài của đoạn con "tốt" dài nhất của dãy $a$.

Hãy cùng nhận xét vị trí của $l$ với mỗi $r$ từ $1$ đến $n$ qua ví dụ sau đây:

Cho trước dãy $a = [2, 6, 4, 3, 6, 8, 9]$ và $s=20$
* $r=1 \rightarrow l=1$
    * $a = [\overset{\underset{\downarrow}{{\color{red}l},{\color{blue}r}}}{\color{green}2}, 6, 4, 3, 6, 8, 9]$
    * $sum(l,r)=2$
* $r=2 \rightarrow l=1$
    * $a = [\overset{\underset{\downarrow}{\color{red}l}}{\color{green}2}, \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}6}, 4, 3, 6, 8, 9]$
    * $sum(l,r)=8$
* $r=3 \rightarrow l=1$
    * $a = [\overset{\underset{\downarrow}{\color{red}l}}{\color{green}2}, {\color{green}6},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}4}, 3, 6, 8, 9]$
    * $sum(l,r)=12$
* $r=4 \rightarrow l=1$
    * $a = [\overset{\underset{\downarrow}{\color{red}l}}{\color{green}2}, {\color{green}6}, {\color{green}4},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}3}, 6, 8, 9]$
    * $sum(l,r)=15$
* $r=5 \rightarrow l=2$
    * $a = [2, \overset{\underset{\downarrow}{\color{red}l}}{\color{green}6}, {\color{green}4}, {\color{green}3},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}6}, 8, 9]$
    * $sum(l,r)=19$
* $r=6 \rightarrow l=4$
    * $a = [2, 6, 4, \overset{\underset{\downarrow}{\color{red}l}}{\color{green}3}, {\color{green}6},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}8}, 9]$
    * $sum(l,r)=17$
* $r=7 \rightarrow l=6$
    * $a = [2, 6, 4, 3, 6, \overset{\underset{\downarrow}{\color{red}l}}{\color{green}8}, \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}9}]$
    * $sum(l,r)=17$

Có thể thấy rằng, vị trí $l$ đối với các giá trị $r$ từ $1$ đến $n$ có giá trị không giảm.

Thật vậy, với mọi $x<l$ thì $sum(x,r)>s \Rightarrow sum(x,r+1)>s$, vì thế giá trị $l$ đối với $r+1$ phải không quá giá trị $l$ đối với $r$.

Hơn nữa vì các phần tử trong dãy $a$ đều có giá trị không quá $s$ cho nên luôn tồn tại vị trí $l \leq r$ sao cho đoạn $[l,r]$ là một đoạn "tốt". 
## Giải pháp

Với những phân tích như trên, ta có giải quyết bài toán với phương pháp hai con trỏ như sau:
* Hai con trỏ $l$ và $r$ sẽ đặt ở vị trí $1$.
    * Hai con trỏ này được thể hiện như hai vị trí $l$, $r$ như ở trên phần phân tích. 
* Di chuyển lần lượt con trỏ $r$ từ $1$ đến $n$.
    * Sau mỗi lần di chuyển con trỏ $r$, nếu
        *  $sum(l,r) \leq s$: giữ nguyên vị trí con trỏ $l$.
        *  $sum(l,r) > s$: tăng dần vị trí con trỏ $l$ cho đến khi $sum(l,r) \leq s$.
    * Hiện tại với vị trí con trỏ $l$ và $r$, ta biết đoạn "tốt" dài nhất với vị trí kết thúc tại $r$ là đoạn $[l,r]$.
* Độ dài đoạn con "tốt" dài nhất chính là giá trị độ dài lớn nhất của các đoạn "tốt" dài nhất với vị trí kết thúc tại $r$, với mỗi $r$ từ $1$ đến $n$.

Để hiểu rõ hơn, ta hãy cùng xem qua một số ví dụ sau đây:

$a = [2, 6, 4, 3, 6, 8, 9]$ và $s=20$

* Sử dụng biến $ans$ để lưu lại giá trị lớn nhất của độ dài đoạn "tốt" có vị trí kết thúc tại $r$, với $r$ từ $1$ đến $n$.

* Đặt $l=1$ và $r=1$
    * $a = [\overset{\underset{\downarrow}{{\color{red}l},{\color{blue}r}}}{\color{green}2}, 6, 4, 3, 6, 8, 9]$
    * vì $a[1] \leq s$ nên đoạn $[1,1]$ là một đoạn "tốt".
    * $ans = max(ans, r - l + 1)$
    
* Tăng vị trí $r$ lên $1$ đơn vị
    * $a = [\overset{\underset{\downarrow}{\color{red}l}}{\color{green}2}, \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}6}, 4, 3, 6, 8, 9]$
    * vì $sum(l,r) = 8 \leq s$ nên đoạn $[l,r]$ là một đoạn tốt.
    * $ans = max(ans, r - l + 1)$
    
* Tăng vị trí $r$ lên $1$ đơn vị
    * $a = [\overset{\underset{\downarrow}{\color{red}l}}{\color{green}2}, {\color{green}6},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}4}, 3, 6, 8, 9]$
    * vì $sum(l,r) = 12 \leq s$ nên đoạn $[l,r]$ là một đoạn tốt.
    * $ans = max(ans, r - l + 1)$
    
* Tăng vị trí $r$ lên $1$ đơn vị
    * $a = [\overset{\underset{\downarrow}{\color{red}l}}{\color{green}2}, {\color{green}6}, {\color{green}4},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}3}, 6, 8, 9]$
    * vì $sum(l,r) = 15 \leq s$ nên đoạn $[l,r]$ là một đoạn tốt.
    * $ans = max(ans, r - l + 1)$
    
* Tăng vị trí $r$ lên $1$ đơn vị
    * $a = [\overset{\underset{\downarrow}{\color{red}l}}{\color{orange}2}, {\color{orange}6}, {\color{orange}4}, {\color{orange}3}, \overset{\underset{\downarrow}{\color{blue}r}}{\color{orange}6}, 8, 9]$
    * vì $sum(l,r) = 21 > s$ nên tăng vị trí $l$.

* Tăng vị trí $l$ lên $1$ đơn vị
    * $a = [2, \overset{\underset{\downarrow}{\color{red}l}}{\color{green}6}, {\color{green}4}, {\color{green}3},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}6}, 8, 9]$
    * vì $sum(l,r) = 19 \leq s$ nên đoạn $[l,r]$ là một đoạn tốt.
    * $ans = max(ans, r - l + 1)$

* Tăng vị trí $r$ lên $1$ đơn vị
    * $a = [2, \overset{\underset{\downarrow}{\color{red}l}}{\color{orange}6}, {\color{orange}4}, {\color{orange}3}, {\color{orange}6},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{orange}8}, 9]$
    * vì $sum(l,r) = 27 > s$ nên tăng vị trí $l$.

* Tăng vị trí $l$ lên $1$ đơn vị
    * $a = [2, 6, \overset{\underset{\downarrow}{\color{red}l}}{\color{orange}4}, {\color{orange}3}, {\color{orange}6},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{orange}8}, 9]$
    * vì $sum(l,r) = 21 > s$ nên tăng vị trí $l$.

* Tăng vị trí $l$ lên $1$ đơn vị
    * $a = [2, 6, 4, \overset{\underset{\downarrow}{\color{red}l}}{\color{green}3}, {\color{green}6},  \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}8}, 9]$
    * vì $sum(l,r) = 17 \leq s$ nên đoạn $[l,r]$ là một đoạn tốt.
    * $ans = max(ans, r - l + 1)$

* Tăng vị trí $r$ lên $1$ đơn vị
    * $a = [2, 6, 4, \overset{\underset{\downarrow}{\color{red}l}}{\color{orange}3}, {\color{orange}6}, {\color{orange}8}, \overset{\underset{\downarrow}{\color{blue}r}}{\color{orange}9}]$
    * vì $sum(l,r) = 26 > s$ nên tăng vị trí $l$.

* Tăng vị trí $l$ lên $1$ đơn vị
    * $a = [2, 6, 4, 3, \overset{\underset{\downarrow}{\color{red}l}}{\color{orange}6}, {\color{orange}8}, \overset{\underset{\downarrow}{\color{blue}r}}{\color{orange}9}]$
    * vì $sum(l,r) = 23 > s$ nên tăng vị trí $l$.

* Tăng vị trí $l$ lên $1$ đơn vị
    * $a = [2, 6, 4, 3, 6, \overset{\underset{\downarrow}{\color{red}l}}{\color{green}8}, \overset{\underset{\downarrow}{\color{blue}r}}{\color{green}9}]$
    * vì $sum(l,r) = 17 \leq s$ nên đoạn $[l,r]$ là một đoạn tốt.
    * $ans = max(ans, r - l + 1)$

**Cài đặt**

Để có thể tính được tổng các phần tử từ $l$ đến $r$ trong khi $l$ và $r$ đang di động, ta sẽ sử dụng biến $sum$ để lưu lại tổng của đoạn $[l,r]$ hiện tại. Sau khi di chuyên $r$ sang phải, biến $sum$ sẽ cộng thêm giá trị $a[r]$. Trước khi di chuyển $l$ sang phải, biến $sum$ sẽ trừ đi giá trị $a[l]$.

```cpp
int ans = 0, sum = 0;
for (int l = 1, r = 1; r <= n; r++) {
    sum += a[r];
    while (sum > s) {
      sum -= a[l];
      l++;
    }
    ans = max(ans, r - l + 1);
}
cout << ans;
```
**Độ phức tạp**

Vị trí con trỏ $r$ luôn tăng, vị trí con trỏ $l$ luôn tăng và luôn tăng không giá trị $r$. Hơn nữa, mỗi vị trí $l$ và $r$ tăng không quá $n$ lần. Vì thế độ phức tạp của giải pháp là $O(n)$.

## Luyện tập
[VNOJ - SOPENP](https://oj.vnoi.info/problem/sopenp)\\
[VNOJ - PRODUCT](https://oj.vnoi.info/problem/product)\\
[VNOJ - KRECT](https://oj.vnoi.info/problem/krect)\\
[VNOJ - VMQUABEO](https://oj.vnoi.info/problem/vmquabeo)

# Bài toán 4
Cho hai số nguyên dương $x, y (x, y\leq 10^{18})$, tìm số thứ $k$ của phân số $\frac{x}{y}$ khi biểu diễn dưới dạng thập phân.

Biết rằng, phân số $\frac{x}{y}$ khi biểu diễn dưới dạng tuần hoàn có không quá $10^7$ ký tự.

## Phân tích

## Giải pháp

## Luyện tập
[CODEFORCES - D.Sequence analysis](https://codeforces.com/gym/100503/problem/D)\\
[CODEFORCES - H. Pseudo-Random Number Generator](https://codeforces.com/gym/102501/problem/H)\\
[CODEFORCES - D. Cooperative Game](https://codeforces.com/contest/1137/problem/D)
